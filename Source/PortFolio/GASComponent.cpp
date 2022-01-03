// Fill out your copyright notice in the Description page of Project Settings.


#include "GASComponent.h"


UGASComponent::UGASComponent() {}


FAbilityResultStruct UGASComponent::TryActiveAbilitiesByTagAndReturn(const FGameplayTagContainer& GameplayTagContainer, bool bAllowRemoteActivation)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate);

	bool bSuccess = false;
	FGameplayAbilitySpec* spec;
	UGameplayAbility* ability;
	FAbilityResultStruct resultStruct = FAbilityResultStruct();
	for (auto GameplayAbilitySpec : AbilitiesToActivate)
	{
		bSuccess |= TryActivateAbility(GameplayAbilitySpec->Handle, bAllowRemoteActivation);
		spec = FindAbilitySpecFromHandle(GameplayAbilitySpec->Handle);
		ability = spec->Ability;

		resultStruct.ability = ability;
		resultStruct.bSuccess = bSuccess;
	}



	return resultStruct;

}
