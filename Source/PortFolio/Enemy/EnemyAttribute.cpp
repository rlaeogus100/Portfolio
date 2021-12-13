// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttribute.h"
#include "Net/UnrealNetwork.h"

UEnemyAttribute::UEnemyAttribute() {

}

void UEnemyAttribute::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttribute, HP, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UEnemyAttribute, AttackPower, COND_None, REPNOTIFY_Always)
}

void UEnemyAttribute::OnRep_HP(const FGameplayAttributeData& OldHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttribute, HP, OldHP)
}

void UEnemyAttribute::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnemyAttribute, AttackPower, OldAttackPower)
}

