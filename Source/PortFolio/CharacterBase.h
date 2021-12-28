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

UCLASS()
class PORTFOLIO_API ACharacterBase : public ASharedCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	ACharacterBase();


	// 컨트롤러
	ACPP_CharacterController* controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDecalComponent* Cursor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera;


public:

	virtual void OnRep_PlayerState() override;

	void cursorVisible(bool value);
};
