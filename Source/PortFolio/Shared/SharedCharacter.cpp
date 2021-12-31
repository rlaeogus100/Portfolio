// Fill out your copyright notice in the Description page of Project Settings.


#include "SharedCharacter.h"

#include "Materials/MaterialInterface.h"
#include "kismet/GameplayStatics.h"
#include "../CPP_GameplayEffect.h"
#include "../GASAttributeSet.h"
#include "../GASComponent.h"
#include "../GASGameplayAbility.h"
#include "kismet/KismetMathLibrary.h"


#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASharedCharacter::ASharedCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComp->SetIsReplicated(true);

	Attributes = CreateDefaultSubobject<UGASAttributeSet>(TEXT("Attributes"));

}

// Called when the game starts or when spawned
void ASharedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASharedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASharedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASharedCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if (HasAuthority() && AbilitySystemComp)
	{

		if (AbilityToGet)
		{
			UE_LOG(LogTemp, Error, TEXT("inteializeability"), 0);
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* ASharedCharacter::GetAbilitySystemComponent() const
{
	return  AbilitySystemComp;
}

void ASharedCharacter::InitializeAttributes()
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

void ASharedCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComp && DefaultAbilities.Num() > 0)
	{
		for (TSubclassOf<UGASGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComp->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));

		}
	}
}

void ASharedCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComp->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void ASharedCharacter::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<class UGASGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	AbilitySystemComp->GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<UGASGameplayAbility>(ActiveAbility));
		}
	}
}

