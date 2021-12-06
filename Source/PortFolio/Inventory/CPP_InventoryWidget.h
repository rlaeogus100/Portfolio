// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "CPP_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCPP_InventoryWidget : public UWidgetBlueprint
{
	GENERATED_BODY()
	

public:
	int a;
	void InvisibleSelf();
};
