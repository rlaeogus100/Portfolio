// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExcutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UDamageExcutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UDamageExcutionCalculation();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
