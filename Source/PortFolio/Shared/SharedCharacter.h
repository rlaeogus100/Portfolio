// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "../GASComponent.h"
#include "../GASAttributeSet.h"



#include "SharedCharacter.generated.h"

UENUM(BlueprintType)
enum class EElementEnum : uint8
{
	None UMETA(DisplayName = "None"),
	Fire UMETA(DisplayName = "Fire"),
	Aqua UMETA(DisplayName = "Aqua"),
	Lightning UMETA(DisplayName = "Lightning")
};


UCLASS()
class PORTFOLIO_API ASharedCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASharedCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Abilities")
		UGASAttributeSet* Attributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
		UGASComponent* AbilitySystemComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effects")
		TArray<TSubclassOf<class UGASGameplayAbility>> DefaultAbilities;

	/** Passive gameplay effects applied on creation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	TArray<FActiveGameplayEffectHandle> ActiveGEHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Abilities")
		EElementEnum Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "State", replicated)
		bool bIsAlive = true;

	bool bInventory = false;
	///** The level of this character, should not be modified directly once it has already spawned */
	//UPROPERTY(EditAnywhere, Replicated, Category = "Abilities")
	//	int32 CharacterLevel = 1;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual void InitializeAttributes();

	virtual void RemovePassive();

	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Death();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void WidgetHPUpdate(float persent);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ChangeHP(float hp, EElementEnum damageElement = EElementEnum::None);

	UFUNCTION(BlueprintCallable)
		void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<class UGASGameplayAbility*>& ActiveAbilities);

	UFUNCTION(BlueprintCallable)
		float GetMaxHelth();

	UFUNCTION(BlueprintCallable)
		float GetCurrentHelth();

	UFUNCTION(BlueprintCallable)
		float GetAttackPower();

	UFUNCTION(BlueprintCallable)
		float GetMagicPower();

	UFUNCTION(BlueprintCallable)
		float GetDefenseMelee();

	UFUNCTION(BlueprintCallable)
		float GetDefenseMagic();



	UFUNCTION(BlueprintCallable)
		float ElementDamage(EElementEnum enemy, float OriginDamage);

	UFUNCTION(BlueprintImplementableEvent)
		void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ASharedCharacter* InstigatorCharacter, AActor* DamageCauser, float HPPersent);

	void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ASharedCharacter* InstigatorCharacter, AActor* DamageCauser, float HPPersent);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeStateHandle();
	
	///** Returns the character level that is passed to the ability system */
	//UFUNCTION(BlueprintCallable)
	//	virtual int32 GetCharacterLevel() const;
};
