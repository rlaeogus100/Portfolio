// Fill out your copyright notice in the Description page of Project Settings.


#include "SharedCharacter.h"

#include "Materials/MaterialInterface.h"
#include "kismet/GameplayStatics.h"
#include "../CPP_GameplayEffect.h"
#include "../GASAttributeSet.h"
#include "../GASComponent.h"
#include "../GASGameplayAbility.h"

#include "kismet/KismetMathLibrary.h"
#include "../CPP_CharacterController.h"

#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASharedCharacter::ASharedCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UGASComponent>(TEXT("AbilitySystemComp"));

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
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* ASharedCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ASharedCharacter::InitializeAttributes()
{
	if (HasAuthority() && AbilitySystemComp && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GHandle = AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		// Now apply passives / 패시브 적용
		for (TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectSpecHandle NewHandle = AbilitySystemComp->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComp->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComp);
				ActiveGEHandles.Add(ActiveGEHandle);
			}
		}
	}
}

void ASharedCharacter::RemovePassive()
{
	if (HasAuthority() && AbilitySystemComp && DefaultAttributeEffect) {
		for (auto handle : ActiveGEHandles) {
			AbilitySystemComp->RemoveActiveGameplayEffect(handle);
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

	if (AbilitySystemComp) {
		AbilitySystemComp->InitAbilityActorInfo(this, this);

		InitializeAttributes();
		GiveAbilities();
	}
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

float ASharedCharacter::GetMaxHelth()
{
	if (Attributes)
		return Attributes->GetMaxHealth();
	else
		return -1;
}

float ASharedCharacter::GetCurrentHelth()
{
	if (Attributes)
		return Attributes->GetHealth();
	else
		return -1;
}

float ASharedCharacter::GetAttackPower()
{
	if (Attributes)
		return Attributes->GetAttackPower();
	else
		return -1;
}

float ASharedCharacter::GetMagicPower()
{
	if (Attributes)
		return Attributes->GetAttackMagic();
	else
		return -1;
}

float ASharedCharacter::GetDefenseMelee()
{
	if (Attributes)
		return Attributes->GetMeleeDefence();
	else
		return -1;
}

float ASharedCharacter::GetDefenseMagic()
{
	if (Attributes)
		return Attributes->GetMagicDefence();
	else
		return -1;
}

void ASharedCharacter::DeathCloseInventoryToServer_Implementation()
{
	DeathCloseInventoryToMultiCast();
}

void ASharedCharacter::DeathCloseInventoryToMultiCast_Implementation()
{
	if (Controller) {
		ACPP_CharacterController* CharacterController = Cast<ACPP_CharacterController>(Controller);
		if (CharacterController)
			CharacterController->DeathInventoryClose();
	}
}

float ASharedCharacter::ElementDamage(EElementEnum enemy, float OriginDamage)
{
	float damage = 0.0f;
	switch (enemy) {
	case EElementEnum::Fire:
		if (Element == EElementEnum::Lightning) {
			damage = OriginDamage * 0.5;
		}
		break;
	case EElementEnum::Aqua:
		if (Element == EElementEnum::Fire) {
			damage = OriginDamage * 0.5;
		}
		break;
	case EElementEnum::Lightning:
		if (Element == EElementEnum::Aqua) {
			damage = OriginDamage * 0.5;
		}
		break;
	}
	return damage;
}

void ASharedCharacter::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const FGameplayTagContainer& DamageTags, ASharedCharacter* InstigatorCharacter, AActor* DamageCauser, float HPPersent)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser, HPPersent);
}

//int32 ASharedCharacter::GetCharacterLevel() const
//{
//	return CharacterLevel;
//}

