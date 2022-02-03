// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_InventoryUW.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCPP_InventoryUW : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void InvisibleSelf();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnInventory();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ChangeItem();

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void CloseDropMenu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RefreshState();
};
