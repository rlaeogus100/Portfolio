// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterBase.h"

AEnemyCharacterBase::AEnemyCharacterBase() {}


float AEnemyCharacterBase::GetHealth()
{
	if (!Attributes)
		return -1.f;

	return Attributes->GetHealth();
}

float AEnemyCharacterBase::GetAttackPower()
{

	if (!Attributes)
		return -1.f;

	return Attributes->GetAttackPower();
}


