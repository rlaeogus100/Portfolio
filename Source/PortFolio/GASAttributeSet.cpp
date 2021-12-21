// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UGASAttributeSet::UGASAttributeSet()
{

}

void UGASAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// �� �Լ��� ȣ��� �� ���� ü���� �ִ밪���� �ٲ�.
	Super::PreAttributeChange(Attribute, NewValue);
	UE_LOG(LogTemp, Error, TEXT("asdfsadfsadfsdfsfsafsdfsadfsdfasdf"), 0);
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UGASAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Error, TEXT("deasdfath"), 0);

	// ������ ������ ���ÿ� �����ϰ� ������ �Ӽ��� ����
	const float LocalDamageDone = GetDamage();
	SetDamage(0.f);

	if (LocalDamageDone > 0)
	{
		// ���� ��ȭ�� ������ �� �����մϴ�.
		const float OldHealth = GetHealth();
		SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));
	}

	// hp�� 0 ���Ϸ� �������� �� �׾��ٴ� �Լ��� ȣ���ϱ� ���� if��.
	if (Health.GetBaseValue() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("deasdfath"), 0);
	}
}

void UGASAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, AttackMagic, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MeleeDefence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MagicDefence, COND_None, REPNOTIFY_Always);
}

// �� �Լ��� ȣ��Ǹ� ������ �������� ���� ������.
void UGASAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
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
