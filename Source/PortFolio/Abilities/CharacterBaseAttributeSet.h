// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterBaseAttributeSet.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 *
 */
UCLASS()
class PORTFOLIO_API UCharacterBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	// Constructor and overrides
	UCharacterBaseAttributeSet();
	// ��Ʈ����Ʈ���� �ٲ�� ���� ����Ǵ� �Լ�.
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// �����÷��� ����Ʈ�� ����� �� ���� ����Ǵ� �Լ�.
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
	// Health �� ������ �� OnRep_Health�� �����.
	//  FGameplayAttributeData : �⺻���� ��� �������� ���� ���� ���簪�� ����.
	//  Abilitysystemcompont�� ���� �� ��Ʈ����Ʈ���� Health ���� ������. (�⺻��, ���簪 ��� �ʱ�ȭ)
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, Health)

		/** MaxHealth is its own attribute, since GameplayEffects may modify it */
		UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, MaxHealth)

		/** Current Mana, used to execute special abilities. Capped by MaxMana */
		UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana)
		FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, Mana)

		/** MaxMana is its own attribute, since GameplayEffects may modify it */
		UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_MaxMana)
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, MaxMana)

		// ���� ������.
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, AttackPower)

		// ���� ������.
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackMagic;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, AttackMagic)

		// ���� ����.
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
		FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, DefensePower)

		// ���� ����
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
		FGameplayAttributeData DefenseMagic;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, DefenseMagic)

		// ���ǵ�
		UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
		FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, MoveSpeed)

		/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
		UPROPERTY(BlueprintReadOnly, Category = "Damage")
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, Damage)

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	//����� �ִ� Ư�� ���� �� Ư�� ���� ��������� �����ϴ� ����� �Լ��Դϴ�. (��, MaxHealth�� �����ϸ� �ǰ��� ������ ������ ������ �����ϴ� �縸ŭ �����մϴ�.)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	// OnRep �Լ����� ����ȭ�� ���� ���.
	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_DefensePower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_AttackMagic(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_DefenseMagic(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);

};
