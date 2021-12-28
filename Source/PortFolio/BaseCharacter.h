// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GASAttributeSet.h"
#include "Shared/SharedCharacter.h"

#include "BaseCharacter.generated.h"



class UDecalComponent;
class UCPP_GameplayEffect;
class ACPP_CharacterController;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PORTFOLIO_API ABaseCharacter : public ASharedCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// 컨트롤러
	ACPP_CharacterController* controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDecalComponent* Cursor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;


protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	virtual void OnRep_PlayerState() override;

	void cursorVisible(bool value);

};
