// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PortFolio.h"
#include "GASGameplayAbility.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	FGameplayEffectContainerSpec() {}

	/** Computed target data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
		FGameplayAbilityTargetDataHandle TargetData;

	/** List of gameplay effects to apply to the targets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
		TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	/** Returns true if this has any valid effect specs */
	bool HasValidEffects() const;

	/** Returns true if this has any valid targets */
	bool HasValidTargets() const;

	/** Adds new targets to target data */
	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};

UCLASS()
class PORTFOLIO_API UGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UGASGameplayAbility();


	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
		virtual FGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FActiveGameplayEffectsContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
};