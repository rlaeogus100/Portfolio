// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Shared/SharedCharacter.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AEnemyCharacterBase : public ASharedCharacter
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetAttackPower();
};
