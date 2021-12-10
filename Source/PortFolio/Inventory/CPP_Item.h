// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Item.generated.h"


class UWidgetComponent;
class UStaticMeshComponent;

UCLASS()
class PORTFOLIO_API ACPP_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void NameWidgetRotationUpdate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetComponent* ItemNameBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* staticMesh;
};
