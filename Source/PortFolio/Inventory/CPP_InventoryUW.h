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
	int a;
	void InvisibleSelf();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnInventory();

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeItem();

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeEquip();
};
