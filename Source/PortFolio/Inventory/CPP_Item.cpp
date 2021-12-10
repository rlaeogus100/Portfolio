// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Item.h"
#include "CPP_ItemNameBroadcastUW.h"
#include "../BaseCharacter.h"

#include "kismet/GameplayStatics.h"
#include "kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"

#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACPP_Item::ACPP_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));

	ItemNameBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ItemNameBar"));

	RootComponent = staticMesh;
	ItemNameBar->SetupAttachment(staticMesh);
	
}

// Called when the game starts or when spawned
void ACPP_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NameWidgetRotationUpdate();

}

void ACPP_Item::NameWidgetRotationUpdate()
{
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ABaseCharacter* base = Cast<ABaseCharacter>(character);
	//USceneComponent* CamTran = base->Camera->GetTransformComponent();
	FRotator CamRot = base->Camera->GetComponentRotation();
	FRotator TempRot = FRotator(CamRot.Pitch * -1.f, CamRot.Yaw, CamRot.Roll);
	FRotator Rot = UKismetMathLibrary::ComposeRotators(TempRot, FRotator(-180, 0, -180));
	ItemNameBar->SetWorldRotation(Rot);

}

