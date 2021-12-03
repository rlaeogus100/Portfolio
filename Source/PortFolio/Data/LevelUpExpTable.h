// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "LevelUpExpTable.generated.h"


USTRUCT(BlueprintType)
struct FLevelUpEXPTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUpExp")
		int32 ExpToNextLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUpExp")
		int32 TotalExp;
};


UCLASS()
class PORTFOLIO_API ALevelUpExpTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelUpExpTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
