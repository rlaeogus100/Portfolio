// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBaseAttributeSet.h"

#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/PlayerController.h"
#include "../BaseCharacter.h"

// 어트리뷰트세트가 생성 되었을 때 모든 값을 초기화 함.
UCharacterBaseAttributeSet::UCharacterBaseAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, Mana(0.f)
	, MaxMana(0.f)
	, AttackPower(1.0f)
	, DefensePower(1.0f)
	, MoveSpeed(1.0f)
	, Damage(0.0f)
{
}

void UCharacterBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// 이 함수가 호출될 때 마다 체력과 마나를 최대값으로 바꿈.
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
}

void UCharacterBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	//UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	//const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	//// 사용 가능한 경우 이전과 새 사이의 델타 계산
	//float DeltaValue = 0;
	//if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	//{
	//	// 이 값이 가법적인 경우 나중에 전달할 원시 델타 값을 저장합니다.
	//	DeltaValue = Data.EvaluatedData.Magnitude;
	//}

	//// 타겟 액터를 구하십시오. 이 액터는 우리의 소유자가 되어야 합니다.
	//AActor* TargetActor = nullptr;
	//AController* TargetController = nullptr;
	//ABaseCharacter* TargetCharacter = nullptr;
	//if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	//{
	//	TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	//	TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
	//	TargetCharacter = Cast<ABaseCharacter>(TargetActor);
	//}

	//if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	//{
	//	// 원본 액터 가져오기
	//	AActor* SourceActor = nullptr;
	//	AController* SourceController = nullptr;
	//	ABaseCharacter* SourceCharacter = nullptr;
	//	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	//	{
	//		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
	//		SourceController = Source->AbilityActorInfo->PlayerController.Get();
	//		if (SourceController == nullptr && SourceActor != nullptr)
	//		{
	//			if (APawn* Pawn = Cast<APawn>(SourceActor))
	//			{
	//				SourceController = Pawn->GetController();
	//			}
	//		}

	//		// 컨트롤러를 사용하여 소스 폰 찾기
	//		if (SourceController)
	//		{
	//			SourceCharacter = Cast<ABaseCharacter>(SourceController->GetPawn());
	//		}
	//		else
	//		{
	//			SourceCharacter = Cast<ABaseCharacter>(SourceActor);
	//		}

	//		// 설정된 경우 컨텍스트에 따라 원인 액터 설정
	//		if (Context.GetEffectCauser())
	//		{
	//			SourceActor = Context.GetEffectCauser();
	//		}
	//	}

	//	// 적중 결과 추출 시도
	//	FHitResult HitResult;
	//	if (Context.GetHitResult())
	//	{
	//		HitResult = *Context.GetHitResult();
	//	}

	//	// 데미지 정도를 로컬에 저장하고 데미지 속성을 삭제
	//	const float LocalDamageDone = GetDamage();
	//	SetDamage(0.f);

	//	if (LocalDamageDone > 0)
	//	{
	//		// 상태 변화를 적용한 후 고정합니다.
	//		const float OldHealth = GetHealth();
	//		SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

	//		if (TargetCharacter)
	//		{
	//			// 적절한 데미지.
	//			TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);

	//			// 모든 Health 변경 요청
	//			TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
	//		}
	//	}
	//}
	//else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	//{
	//	// Handle other health changes such as from healing or direct modifiers 치유 또는 직접 수정과 같은 다른 건강 변경 처리
	//	// First clamp it 처음 고정된 것
	//	SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

	//	if (TargetCharacter)
	//	{
	//		// Call for all health changes 모든 Health 변경 요청
	//		TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
	//	}
	//}
	//else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	//{
	//	// Clamp mana /마나 고정
	//	SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

	//	if (TargetCharacter)
	//	{
	//		// Call for all mana changes / 모든 마나 변경 요청
	//		TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
	//	}
	//}
	//else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	//{
	//	if (TargetCharacter)
	//	{
	//		// Call for all movespeed changes / 모든 스피드 변경 요청
	//		TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
	//	}
	//}
}

void UCharacterBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterBaseAttributeSet, Health);
	DOREPLIFETIME(UCharacterBaseAttributeSet, MaxHealth);
	DOREPLIFETIME(UCharacterBaseAttributeSet, Mana);
	DOREPLIFETIME(UCharacterBaseAttributeSet, MaxMana);
	DOREPLIFETIME(UCharacterBaseAttributeSet, AttackPower);
	DOREPLIFETIME(UCharacterBaseAttributeSet, DefensePower);
	DOREPLIFETIME(UCharacterBaseAttributeSet, MoveSpeed);
}

// 버프같은 것으로 최대 체력이 오르면 기존과 비례해서 체력이 오르도록 하는 함수. (체력이 아닌 다른 것도 가능)
void UCharacterBaseAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		// 현재 값을 변경하여 현재 Val/Max 백분율을 유지합니다.
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UCharacterBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, Health, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, MaxHealth, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, Mana, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, MaxMana, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, AttackPower, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, DefensePower, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_AttackMagic(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, AttackMagic, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_DefenseMagic(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, DefenseMagic, OldValue);
}

void UCharacterBaseAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterBaseAttributeSet, MoveSpeed, OldValue);
}
