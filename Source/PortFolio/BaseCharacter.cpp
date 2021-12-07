// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInterface.h"
#include "kismet/GameplayStatics.h"
#include "CPP_GameplayEffect.h"
#include "GASAttributeSet.h"
#include "GASComponent.h"
#include "GASGameplayAbility.h"
#include "kismet/KismetMathLibrary.h"
#include "CPP_CharacterController.h"

#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));

	Attributes = CreateDefaultSubobject<UGASAttributeSet>(TEXT("Attributes"));

	Cursor = CreateDefaultSubobject<UDecalComponent>(TEXT("Cursor"));

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


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<ACPP_CharacterController>((UGameplayStatics::GetPlayerController(GetWorld(), 0)));
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!controller->bInventory) {
		// 마우스 커서 위치로 데칼 옮기기
		FHitResult result;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, result);
		if (result.bBlockingHit) {
			auto a = UKismetMathLibrary::MakeRotationFromAxes(result.ImpactNormal, FVector(0.f, 0.f, 0.f), FVector(0.f, 0.f, 0.f));
			Cursor->SetWorldLocationAndRotation(result.Location, a);
		}
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (AbilitySystemComp && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGASAbilityInputID", static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
		AbilitySystemComp->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}

}

void ABaseCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if (AbilitySystemComp)
	{
		if (HasAuthority() && AbilityToGet)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return  AbilitySystemComp;
}

void ABaseCharacter::InitializeAttributes()
{
	if (AbilitySystemComp && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GHandle = AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ABaseCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComp)
	{
		for (TSubclassOf<UGASGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComp->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));

		}
	}
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComp->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComp->InitAbilityActorInfo(this, this);
	InitializeAttributes();

	if (AbilitySystemComp && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGASAbilityInputID", static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
		AbilitySystemComp->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ABaseCharacter::cursorVisible(bool value)
{
	Cursor->SetVisibleFlag(value);
}

