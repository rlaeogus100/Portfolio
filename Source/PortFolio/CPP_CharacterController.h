// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_CharacterController.generated.h"

/**
 * 
 */
class UCPP_InventoryUW;
class ABaseCharacter;

UCLASS()
class PORTFOLIO_API ACPP_CharacterController : public APlayerController
{
	GENERATED_BODY()
	


public:
	UPROPERTY(EditAnywhere, Blueprintreadonly)
		float MinClickDinstance = 120.0f;
	
	bool bSetDestination = false;

	bool bInventory = false;

	UCPP_InventoryUW* Inventory;

	ABaseCharacter* character;
	

public:
	ACPP_CharacterController();
	

	// 마우스 커서로 캐릭터를 이동하는 함수
	UFUNCTION()
		void MoveToHitLocation(FHitResult Hit);

	virtual void SetupInputComponent();

	virtual void Tick(float DeltaSeconds);

	virtual void BeginPlay() override;

	// 우클릭 버튼 누르면 그 위치로 이동
	void OnSetDestination_Pressed();
	void OnSetDestination_Released();

	// I키를 누르면 인벤토리를 보여주거나 사라지게 함
	void OnInventory_Pressed();
	
	void InvisibleInventory();

	UFUNCTION(BlueprintCallable)
		void ChangeItem();

	UFUNCTION(BlueprintCallable)
		void ChangeEquip();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", Meta = (AllowPrivateAccess = true))
		TSubclassOf<UCPP_InventoryUW> Inventory_Widget;
};
