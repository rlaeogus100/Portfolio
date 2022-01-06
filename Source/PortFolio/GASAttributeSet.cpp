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
	// �� �Լ��� ȣ��� �� ���� ü���� �ִ밪���� �ٲ�.
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}

	// ü���� �ִ� ü���� �Ѿ����.
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

	// ��� ������ ��� ������ �� ������ ��Ÿ ���
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// �� ���� �������� ��� ���߿� ������ ���� ��Ÿ ���� �����մϴ�.
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// Ÿ�� ���͸� ���Ͻʽÿ�. �� ���ʹ� �츮�� �����ڰ� �Ǿ�� �մϴ�.
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
		// ���� ���� ��������
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

			// ��Ʈ�ѷ��� ����Ͽ� �ҽ� �� ã��
			if (SourceController)
			{
				SourceCharacter = Cast<ASharedCharacter>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<ASharedCharacter>(SourceActor);
			}

			// ������ ��� ���ؽ�Ʈ�� ���� ���� ���� ����
			if (Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}
		}

		// ���� ��� ���� �õ�
		FHitResult HitResult;
		if (Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		// ������ ������ ���ÿ� �����ϰ� ������ �Ӽ��� ����
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// ���� ��ȭ�� ������ �� �����մϴ�.
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

			if (TargetCharacter)
			{
				// ������ ������.
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

// �� �Լ��� ȣ��Ǹ� ������ �������� ���� ������.
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
		// ���� ���� �����Ͽ� ���� Val/Max ������� �����մϴ�.
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
