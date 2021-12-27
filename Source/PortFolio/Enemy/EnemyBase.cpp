// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "EnemyGameplayAbility.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComp->SetIsReplicated(true);

	Attributes = CreateDefaultSubobject<UGASAttributeSet>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AEnemyBase::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if (AbilitySystemComp)
	{
		if (AbilityToGet)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}



UAbilitySystemComponent* AEnemyBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AEnemyBase::InitializeAttributes()
{
	if (AbilitySystemComp && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		UE_LOG( LogTemp, Error, TEXT("asdf"), 0);
		if (SpecHandle.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("IsValid()"), 0);
			FActiveGameplayEffectHandle GHandle = AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void AEnemyBase::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComp)
	{
		for (auto StartupAbility : DefaultAbilities)
		{
			UE_LOG(LogTemp, Error, TEXT("GiveAbilitiesEnemy"), 0);
			AbilitySystemComp->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1));
		}
	}
}

void AEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComp->InitAbilityActorInfo(this, this);
	UE_LOG(LogTemp, Error, TEXT("PossessedBy"), 0);
	if (AbilitySystemComp == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Abilitysystem is Null"), 0);
	}
	InitializeAttributes();
	GiveAbilities();
}



float AEnemyBase::GetHealth()
{
	if (!Attributes)
		return -1.f;

	return Attributes->GetHealth();
}

float AEnemyBase::GetAttackPower()
{

	if (!Attributes)
		return -1.f;

	return Attributes->GetAttackPower();
}

