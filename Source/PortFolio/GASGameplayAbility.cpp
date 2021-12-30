// Fill out your copyright notice in the Description page of Project Settings.


#include "GASGameplayAbility.h"
#include "Shared/SharedCharacter.h"
#include "AbilitySystemGlobals.h"

UGASGameplayAbility::UGASGameplayAbility()
{

}

FGameplayEffectContainerSpec UGASGameplayAbility::MakeEffectContainerSpecFromContainer(const FActiveGameplayEffectsContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	// First figure out our actor info
	FGameplayEffectContainerSpec ReturnSpec;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	ASharedCharacter* OwningCharacter = Cast<ASharedCharacter>(OwningActor);
	UAbilitySystemComponent* OwningASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor);

	if (OwningASC)
	{
		// If we have a target type, run the targeting logic. This is optional, targets can be added later
		//if (Container.TargetType.Get())
		//{
		//	TArray<FHitResult> HitResults;
		//	TArray<AActor*> TargetActors;
		//	const URPGTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
		//	AActor* AvatarActor = GetAvatarActorFromActorInfo();
		//	TargetTypeCDO->GetTargets(OwningCharacter, AvatarActor, EventData, HitResults, TargetActors);
		//	ReturnSpec.AddTargets(HitResults, TargetActors);
		//}

		//// If we don't have an override level, use the default on the ability itself
		//if (OverrideGameplayLevel == INDEX_NONE)
		//{
		//	OverrideGameplayLevel = OverrideGameplayLevel = this->GetAbilityLevel(); //OwningASC->GetDefaultAbilityLevel();
		//}

		//// Build GameplayEffectSpecs for each applied effect
		//for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.TargetGameplayEffectClasses)
		//{
		//	ReturnSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass, OverrideGameplayLevel));
		//}
	}
	return ReturnSpec;
}
