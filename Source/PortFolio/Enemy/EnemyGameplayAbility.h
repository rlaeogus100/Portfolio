// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../PortFolio.h"
#include "EnemyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UEnemyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	

public:
	// �Է��� �Ǹ� �ڵ����� Ȱ��ȭ
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		EGASAbilityInputID AbilityInputID = EGASAbilityInputID::None;
};
