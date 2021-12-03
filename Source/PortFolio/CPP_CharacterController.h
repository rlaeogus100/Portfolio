// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API ACPP_CharacterController : public APlayerController
{
	GENERATED_BODY()
	


public:
	UPROPERTY(EditAnywhere, Blueprintreadonly)
		float MinDinstanceClick = 120.0f;
	
	bool bSetDestination = false;

public:
	ACPP_CharacterController();
	


	UFUNCTION()
		void MoveToHitLocation(FHitResult Hit);

	virtual void Tick(float DeltaSeconds);

	void OnSetDestination_Pressed();
	void OnSetDestination_Released();

};
