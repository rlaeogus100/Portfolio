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
	// 어트리뷰트값이 바뀌기 전에 실행되는 함수.
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// 게임플레이 이펙트가 실행된 후 따라 실행되는 함수.
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
	// Health 를 복제할 때 OnRep_Health를 사용함.
	//  FGameplayAttributeData : 기본값과 어떠한 현상으로 인해 변한 현재값을 가짐.
	//  Abilitysystemcompont를 통해 이 어트리뷰트셋의 Health 값을 변경함. (기본값, 현재값 모두 초기화)
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

		// 물리 데미지.
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, AttackPower)

		// 마법 데미지.
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackMagic;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, AttackMagic)

		// 물리 방어력.
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
		FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, DefensePower)

		// 마법 방어력
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
		FGameplayAttributeData DefenseMagic;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, DefenseMagic)

		// 스피드
		UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
		FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, MoveSpeed)

		/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
		UPROPERTY(BlueprintReadOnly, Category = "Damage")
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCharacterBaseAttributeSet, Damage)

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	//연결된 최대 특성 변경 시 특성 값을 비례적으로 조정하는 도우미 함수입니다. (즉, MaxHealth가 증가하면 건강은 이전과 동일한 비율을 유지하는 양만큼 증가합니다.)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	// OnRep 함수들은 동기화를 위해 사용.
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
