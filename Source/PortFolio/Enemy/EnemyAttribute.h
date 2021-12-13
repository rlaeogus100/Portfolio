// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttribute.generated.h"

// AttributeSet���� ������
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class PORTFOLIO_API UEnemyAttribute : public UAttributeSet
{
	GENERATED_BODY()


public:
	int a;
	UEnemyAttribute();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	// ü�� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Enemy", ReplicatedUsing = OnRep_HP)
		FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UEnemyAttribute, HP)

		UFUNCTION()
		virtual void OnRep_HP(const FGameplayAttributeData& OldHP);

	// ���ݷ� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Enemy", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UEnemyAttribute, AttackPower)

		UFUNCTION()
		virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);


};
