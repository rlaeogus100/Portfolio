// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

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
class PORTFOLIO_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	

public:
	int a;
	UEnemyAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	// ü�� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health)

		UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	// ���ݷ� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, AttackPower)

		UFUNCTION()
		virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);


};
