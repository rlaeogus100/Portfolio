// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/SharedCharacter.h"
#include "CharacterBase.generated.h"

/**
 * 
 */

class UDecalComponent;
class UCPP_GameplayEffect;
class ACPP_CharacterController;
class UCameraComponent;
class USpringArmComponent;
class UCPP_InventoryUW;

UCLASS()
class PORTFOLIO_API ACharacterBase : public ASharedCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	ACharacterBase();


	// ??Ʈ?ѷ?
	ACPP_CharacterController* controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDecalComponent* Cursor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, replicated)
	UCPP_InventoryUW* Inventory;


public:

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void OnRep_PlayerState() override;

	void cursorVisible(bool value);

	UFUNCTION(BlueprintCallable)
	float ChangeAttackPower(float value);

	UFUNCTION(BlueprintCallable)
		float ChangeAttackMagic(float value);


};
