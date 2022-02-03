// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASGameplayAbility.h"
#include "Data/LevelUpExpTable.h"
#include "GASComponent.generated.h"

/**
 *
 */



UCLASS()
class PORTFOLIO_API UGASComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UGASComponent();

	UFUNCTION(BlueprintCallable)
		FAbilityResultStruct TryActiveAbilitiesByTagAndReturn(const FGameplayTagContainer& GameplayTagContainer, bool bAllowRemoteActivation = true);

	UFUNCTION(BlueprintCallable)
		FCoolDownStruct GetGameplayEffectDurationPersent(TSubclassOf<UGameplayEffect> SourceGameplayEffect, UAbilitySystemComponent* OptionalInstigatorFilterComponent, bool bEnforceOnGoingCheck = true);
};


