// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GASAttributeSet.h"
#include "BaseCharacter.generated.h"


class UDecalComponent;
class UCPP_GameplayEffect;

UCLASS()
class PORTFOLIO_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{

	GENERATED_BODY()



public:
	// Sets default values for this character's properties
	ABaseCharacter();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Abilities")
	UGASAttributeSet* Attributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDecalComponent* Cursor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Abilities")
		class UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effects")
		TArray<TSubclassOf<class UGASGameplayAbility>> DefaultAbilities;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		void InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual void InitializeAttributes();

	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

};
