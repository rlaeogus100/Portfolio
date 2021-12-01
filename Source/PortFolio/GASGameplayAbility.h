// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PortFolio.h"
#include "GASGameplayAbility.generated.h"


/**
 * 
 */
UCLASS()
class PORTFOLIO_API UGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UGASGameplayAbility();
	
	// 입력이 되면 자동으로 활성화
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		EGASAbilityInputID AbilityInputID = EGASAbilityInputID::None;
	
};
