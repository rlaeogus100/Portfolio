// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "CPP_CharacterController.h"

#include "Shared/SharedCharacter.h"



UGASAttributeSet::UGASAttributeSet()
{

}

void UGASAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// 이 함수가 호출될 때 마다 체력을 최대값으로 바꿈.
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}

	// 체력이 최대 체력을 넘어가는지.
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxHealthAttribute().GetNumericValueChecked(this));
	}
}

void UGASAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// 사용 가능한 경우 이전과 새 사이의 델타 계산
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// 이 값이 가법적인 경우 나중에 전달할 원시 델타 값을 저장합니다.
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// 타겟 액터를 구하십시오. 이 액터는 우리의 소유자가 되어야 합니다.
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ASharedCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ASharedCharacter>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		float persent = GetHealth() / GetMaxHealth();
		TargetCharacter->ChangeHP(DeltaValue);
		TargetCharacter->WidgetHPUpdate(persent);
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// 원본 액터 가져오기
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		ASharedCharacter* SourceCharacter = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			// 컨트롤러를 사용하여 소스 폰 찾기
			if (SourceController)
			{
				SourceCharacter = Cast<ASharedCharacter>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<ASharedCharacter>(SourceActor);
			}

			// 설정된 경우 컨텍스트에 따라 원인 액터 설정
			if (Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}
		}

		// 적중 결과 추출 시도
		FHitResult HitResult;
		if (Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		// 데미지 정도를 로컬에 저장하고 데미지 속성을 삭제
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// 상태 변화를 적용한 후 고정합니다.
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

			if (TargetCharacter)
			{
				// 적절한 데미지.
				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);
				TargetCharacter->ChangeHP(-LocalDamageDone);
				float elementDamage = TargetCharacter->ElementDamage(SourceCharacter->Element, LocalDamageDone);
				if (elementDamage > 0) {
					UE_LOG(LogTemp, Error, TEXT("Critical"), 0);
					SetHealth(FMath::Clamp(OldHealth - LocalDamageDone - elementDamage, 0.0f, GetMaxHealth()));
					TargetCharacter->ChangeHP(-elementDamage, SourceCharacter->Element);
				}
			}
		}
	}

	if (Health.GetBaseValue() <= 0)
	{
		TargetCharacter->Death();
		TargetCharacter->RemovePassive();

	}

}

void UGASAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UGASAttributeSet, Health);
	DOREPLIFETIME(UGASAttributeSet, MaxHealth);
	DOREPLIFETIME(UGASAttributeSet, Stamina);
	DOREPLIFETIME(UGASAttributeSet, AttackPower);
	DOREPLIFETIME(UGASAttributeSet, AttackMagic);
	DOREPLIFETIME(UGASAttributeSet, MeleeDefence);
	DOREPLIFETIME(UGASAttributeSet, MagicDefence);
}

// 이 함수가 호출되면 비율을 바탕으로 값을 조절함.
void UGASAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	//if (GetOwningActor()) {
	//	UE_LOG(LogTemp, Error, TEXT("GetOwningActor Is True : %s"), *GetOwningActor()->GetName());
	//}

	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%.f GASAttributeSet"), NewMaxValue);
		// Change current value to maintain the current Val / Max percent
		// 현재 값을 변경하여 현재 Val/Max 백분율을 유지합니다.
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UGASAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Health, OldHealth)
}

void UGASAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MaxHealth, OldValue)
}

void UGASAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Stamina, OldStamina)
}

void UGASAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, AttackPower, OldAttackPower)
}

void UGASAttributeSet::OnRep_AttackMagic(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, AttackMagic, OldValue)
}

void UGASAttributeSet::OnRep_MeleeDefence(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MeleeDefence, OldValue)
}

void UGASAttributeSet::OnRep_MagicDefence(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MagicDefence, OldValue)
}
