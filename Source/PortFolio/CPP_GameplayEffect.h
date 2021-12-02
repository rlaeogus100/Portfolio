// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "CPP_GameplayEffect.generated.h"

/**
 *
 */
UCLASS()
class PORTFOLIO_API UCPP_GameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Effects")
		FName EffectId;
};
