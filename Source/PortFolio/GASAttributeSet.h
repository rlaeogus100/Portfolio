// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASAttributeSet.generated.h"

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
class PORTFOLIO_API UGASAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
	int a;
	UGASAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	// ü�� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health)

		UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	// �ִ� ü�� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxHealth)

		UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	// ��� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Stamina)

		UFUNCTION()
		virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	// ���� ���ݷ� �߰�
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackPower)

		UFUNCTION()
		virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);

	// ���� ���ݷ� �߰�.
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackMagic)
		FGameplayAttributeData AttackMagic;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackMagic)

		UFUNCTION()
		virtual void OnRep_AttackMagic(const FGameplayAttributeData& OldValue);

	// ���� ���� �߰�.
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_MeleeDefence)
		FGameplayAttributeData MeleeDefence;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MeleeDefence)

		UFUNCTION()
		virtual void OnRep_MeleeDefence(const FGameplayAttributeData& OldValue);

	// ���� ���� �߰�.
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_MagicDefence)
		FGameplayAttributeData MagicDefence;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MagicDefence)

		UFUNCTION()
		virtual void OnRep_MagicDefence(const FGameplayAttributeData& OldValue);

	// ���⿡�� ������ ���� ��
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Damage)

};
