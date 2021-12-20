// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBaseAttributeSet.h"

#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/PlayerController.h"
#include "../BaseCharacter.h"

// ��Ʈ����Ʈ��Ʈ�� ���� �Ǿ��� �� ��� ���� �ʱ�ȭ ��.
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
	// �� �Լ��� ȣ��� �� ���� ü�°� ������ �ִ밪���� �ٲ�.
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

	//// ��� ������ ��� ������ �� ������ ��Ÿ ���
	//float DeltaValue = 0;
	//if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	//{
	//	// �� ���� �������� ��� ���߿� ������ ���� ��Ÿ ���� �����մϴ�.
	//	DeltaValue = Data.EvaluatedData.Magnitude;
	//}

	//// Ÿ�� ���͸� ���Ͻʽÿ�. �� ���ʹ� �츮�� �����ڰ� �Ǿ�� �մϴ�.
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
	//	// ���� ���� ��������
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

	//		// ��Ʈ�ѷ��� ����Ͽ� �ҽ� �� ã��
	//		if (SourceController)
	//		{
	//			SourceCharacter = Cast<ABaseCharacter>(SourceController->GetPawn());
	//		}
	//		else
	//		{
	//			SourceCharacter = Cast<ABaseCharacter>(SourceActor);
	//		}

	//		// ������ ��� ���ؽ�Ʈ�� ���� ���� ���� ����
	//		if (Context.GetEffectCauser())
	//		{
	//			SourceActor = Context.GetEffectCauser();
	//		}
	//	}

	//	// ���� ��� ���� �õ�
	//	FHitResult HitResult;
	//	if (Context.GetHitResult())
	//	{
	//		HitResult = *Context.GetHitResult();
	//	}

	//	// ������ ������ ���ÿ� �����ϰ� ������ �Ӽ��� ����
	//	const float LocalDamageDone = GetDamage();
	//	SetDamage(0.f);

	//	if (LocalDamageDone > 0)
	//	{
	//		// ���� ��ȭ�� ������ �� �����մϴ�.
	//		const float OldHealth = GetHealth();
	//		SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

	//		if (TargetCharacter)
	//		{
	//			// ������ ������.
	//			TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);

	//			// ��� Health ���� ��û
	//			TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
	//		}
	//	}
	//}
	//else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	//{
	//	// Handle other health changes such as from healing or direct modifiers ġ�� �Ǵ� ���� ������ ���� �ٸ� �ǰ� ���� ó��
	//	// First clamp it ó�� ������ ��
	//	SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

	//	if (TargetCharacter)
	//	{
	//		// Call for all health changes ��� Health ���� ��û
	//		TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
	//	}
	//}
	//else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	//{
	//	// Clamp mana /���� ����
	//	SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

	//	if (TargetCharacter)
	//	{
	//		// Call for all mana changes / ��� ���� ���� ��û
	//		TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
	//	}
	//}
	//else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	//{
	//	if (TargetCharacter)
	//	{
	//		// Call for all movespeed changes / ��� ���ǵ� ���� ��û
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

// �������� ������ �ִ� ü���� ������ ������ ����ؼ� ü���� �������� �ϴ� �Լ�. (ü���� �ƴ� �ٸ� �͵� ����)
void UCharacterBaseAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		// ���� ���� �����Ͽ� ���� Val/Max ������� �����մϴ�.
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
