// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GASComponent.h"
#include "CPP_CharacterController.h"
#include "kismet/GameplayStatics.h"


ACharacterBase::ACharacterBase() {


	Cursor = CreateDefaultSubobject<UDecalComponent>(TEXT("Cursor"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 1200;
	SpringArm->SetWorldRotation(FRotator(-60.0f, 0.0f, 0.0f));
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;

	ConstructorHelpers::FObjectFinder<UMaterialInterface>MI_Cursor(TEXT("Material'/Game/BluePrint/Character/M_Cursor_Decal.M_Cursor_Decal'"));
	if (MI_Cursor.Succeeded())
	{
		Cursor->SetupAttachment(RootComponent);
		Cursor->SetDecalMaterial(MI_Cursor.Object);
		Cursor->DecalSize = FVector(16.0f, 32.0f, 32.0f);
		Cursor->SetWorldLocation(FVector(-10, 0, -90));
		Cursor->SetWorldRotation(FRotator(0.f, 0.f, 0.f));

	}
}

void ACharacterBase::BeginPlay() {
	Super::BeginPlay();

	controller = Cast<ACPP_CharacterController>((UGameplayStatics::GetPlayerController(GetWorld(), 0)));

}

void ACharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (AbilitySystemComp) {
		AbilitySystemComp->InitAbilityActorInfo(this, this);
		InitializeAttributes();
	}

}


void ACharacterBase::cursorVisible(bool value)
{
	Cursor->SetVisibleFlag(value);
}

float ACharacterBase::ChangeAttackPower(float value)
{
	Attributes->SetAttackPower(value);
	return Attributes->GetAttackPower();
}


float ACharacterBase::ChangeAttackMagic(float value)
{
	Attributes->SetAttackMagic(value);
	return Attributes->GetAttackMagic();
}