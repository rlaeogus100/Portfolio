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

FCoolDownStruct UGASComponent::GetGameplayEffectDurationPersent(TSubclassOf<UGameplayEffect> SourceGameplayEffect, UAbilitySystemComponent* OptionalInstigatorFilterComponent, bool bEnforceOnGoingCheck)
{
	FCoolDownStruct coolDownStruct;
	float duration = 0;
	float remaining = 0;
	if (SourceGameplayEffect)
	{
		FGameplayEffectQuery Query;
		Query.CustomMatchDelegate.BindLambda([&](const FActiveGameplayEffect& CurEffect)
			{
				bool bMatches = false;

				// First check at matching: backing GE class must be the exact same
				if (CurEffect.Spec.Def && SourceGameplayEffect == CurEffect.Spec.Def->GetClass())
				{
					// If an instigator is specified, matching is dependent upon it
					if (OptionalInstigatorFilterComponent)
					{
						bMatches = (OptionalInstigatorFilterComponent == CurEffect.Spec.GetEffectContext().GetInstigatorAbilitySystemComponent());
					}
					else
					{
						bMatches = true;
					}
				}

				return bMatches;
			});

		for (auto a : ActiveGameplayEffects.GetActiveEffectsDuration(Query)) {
			coolDownStruct.duration += a;
		}
		for (auto a : ActiveGameplayEffects.GetActiveEffectsTimeRemaining(Query)) {
			coolDownStruct.remaining += a;
		}

	}
	coolDownStruct.persent = coolDownStruct.remaining / coolDownStruct.duration;

	return coolDownStruct;
}