// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "EnemyAttributeSet.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{

}

void UEnemyAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSet, MeleeDefence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttributeSet, MagicDefence, COND_None, REPNOTIFY_Always);
}

void UEnemyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSet, Health, OldHealth)
}
void UEnemyAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSet, AttackPower, OldAttackPower)
}

void UEnemyAttributeSet::OnRep_MeleeDefence(const FGameplayAttributeData& OldMeleeDefence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSet, MeleeDefence, OldMeleeDefence)
}

void UEnemyAttributeSet::OnRep_MagicDefence(const FGameplayAttributeData& OldMagicDefence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttributeSet, MeleeDefence, OldMagicDefence)
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Health.GetBaseValue() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("deaasdfth"), 0);
	}
}
