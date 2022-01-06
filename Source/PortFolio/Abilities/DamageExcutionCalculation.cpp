// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExcutionCalculation.h"

#include "AbilitySystemComponent.h"
#include "../GASAttributeSet.h"


// ĸó�� �ϱ� ���� ����ü�� ������.
struct DamageCalcStruct {
	// ������ ��꿡 �ʿ��� ĸó �� �Ӽ��� ������.
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MeleeDefence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackMagic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicDefence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	DamageCalcStruct()
	{
		// ���� ����Ǿ��� �Ӽ��� ������.

			// Ÿ�ݴ����� ���� �������� ����ؾ� �ϱ� ������ �������� ���� ����.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, MeleeDefence, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, MagicDefence, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, Health, Target, false);

		// �������� �� ����ü�� �� �ֱ� ������ ���ݷ��� �������� ��.
		// ������ ���� ����� ������Ʈ������ Ȥ�� ������ �����Ѵٸ� ���� �߿� ������ ������ �� ������ �����ߴ� �� �״�� ����ϰ��� ��ݿ� ���⸦ ���� ������ �ʾƼ� �������� ���� �������� ��.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, AttackPower, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, AttackMagic, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, Damage, Source, true);


	}

};

static const DamageCalcStruct& DamageStatic() {
	static DamageCalcStruct damageStatic;
	return damageStatic;
};

// ������ �� ĸó�� ���� �Ӽ��� ������.
UDamageExcutionCalculation::UDamageExcutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatic().MeleeDefenceDef);
	RelevantAttributesToCapture.Add(DamageStatic().MagicDefenceDef);
	RelevantAttributesToCapture.Add(DamageStatic().AttackPowerDef);
	RelevantAttributesToCapture.Add(DamageStatic().AttackMagicDef);
	RelevantAttributesToCapture.Add(DamageStatic().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatic().DamageDef);
}

void UDamageExcutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	// Ÿ�� (���� ���� ����)�� �����Ƽ�ý��� ������Ʈ�� ������
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	// �ҽ� (������ �� ��ü)�� �����Ƽ�ý��� ������Ʈ�� ������ 
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	// �����Ƽ�ý��� ������Ʈ�� ����� �����Դٸ� avatarActor(�ɷ��� ����ϴ� ��)�� �ƴ϶�� nullptr�� ���Ѵ�.
	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor_Direct() : nullptr;
	if (SourceAbilitySystemComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("SourceAbilitySystemComponent Null"), 0);
	}
	if (SourceActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("SourceActor Null"), 0);
	}
	if (TargetActor == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TargetActor Null"), 0);
	}
	// �����÷�������Ʈ, ����Ʈ�� �ڵ� ���� ���ϰ� ����. ����̶�� spec�� �°� �±� �� �����÷��� ����Ʈ�� ���õ� �������� ���ϰ� ����.
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	// � ������ ����ؾ� �ϴ����� ������ �� �� �����Ƿ� �ҽ� �� ��󿡼� �±׸� �����մϴ�
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// --------------------------------------
	//	Damage Done = AttackPower > AttackMagic? AttackPower - MeleeDefence : AttackMagic - MagicDefence;
	// �������� ������������ ���ϰ� �ְ� ��, �� ���� ���� �������� ���ϰ� �����Ƿ� �� �� ���� ���� �������� ����Ѵ�.
	// --------------------------------------

	float MeleeDefence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().MeleeDefenceDef, EvaluationParameters, MeleeDefence);

	float MagicDefence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().MeleeDefenceDef, EvaluationParameters, MagicDefence);

	float AttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().AttackPowerDef, EvaluationParameters, AttackPower);

	float AttackMagic = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().AttackMagicDef, EvaluationParameters, AttackMagic);

	float DamageDone = 0.f;

	if (AttackPower >= AttackMagic) 
	{

		DamageDone = AttackPower - MeleeDefence;
	}
	else 
	{
		DamageDone = AttackMagic - MagicDefence;
	}
	if (DamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatic().DamageProperty, EGameplayModOp::Additive, DamageDone));
	}

}
