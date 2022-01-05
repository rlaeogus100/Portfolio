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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHPVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* EnemyHPBar;

public:
	AEnemyCharacterBase();

	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetAttackPower();

	void NameWidgetRotationUpdate();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "HPBar")
	bool SetHPBarVisible(bool a);
};
