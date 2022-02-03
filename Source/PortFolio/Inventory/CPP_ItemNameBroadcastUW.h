// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_ItemNameBroadcastUW.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCPP_ItemNameBroadcastUW : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 FString ItemName;
};
