// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExcutionCalculation.h"

#include "AbilitySystemComponent.h"
#include "../GASAttributeSet.h"


// 캡처를 하기 위해 구조체를 선언함.
struct DamageCalcStruct {
	// 데미지 계산에 필요해 캡처 할 속성을 선언함.
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MeleeDefence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackMagic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicDefence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	DamageCalcStruct()
	{
		// 위에 선언되었던 속성을 정의함.

			// 타격당했을 때의 방어력으로 계산해야 하기 때문에 스냅샷은 하지 않음.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, MeleeDefence, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, MagicDefence, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, Health, Target, false);

		// 공격했을 때 투사체일 수 있기 때문에 공격력은 스냅샷을 함.
		// 별개로 지금 만드는 프로젝트에서는 혹시 버프가 존재한다면 공격 중에 버프가 끝났을 시 공격을 시작했던 값 그대로 사용하고자 사격용 계산기를 따로 만들지 않아서 근접공격 또한 스냅샷을 함.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, AttackPower, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, AttackMagic, Source, true);


	}

};

static const DamageCalcStruct& DamageStatic() {
	static DamageCalcStruct damageStatic;
	return damageStatic;
};

// 생성될 때 캡처할 관련 속성을 정의함.
UDamageExcutionCalculation::UDamageExcutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatic().MeleeDefenceDef);
	RelevantAttributesToCapture.Add(DamageStatic().MagicDefenceDef);
	RelevantAttributesToCapture.Add(DamageStatic().AttackPowerDef);
	RelevantAttributesToCapture.Add(DamageStatic().AttackMagicDef);
	RelevantAttributesToCapture.Add(DamageStatic().HealthDef);
}

void UDamageExcutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	// 타겟 (공격 당한 액터)의 어빌리티시스템 컴포넌트를 가져옴
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	// 소스 (공격을 한 주체)의 어빌리티시스템 컴포넌트를 가져옴 
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	// 어빌리티시스템 컴포넌트를 제대로 가져왔다면 avatarActor(능력을 사용하는 폰)을 아니라면 nullptr을 지닌다.
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
	// 게임플레이이펙트, 이펙트의 핸들 등을 지니고 있음. 사양이라는 spec에 맞게 태그 등 게임플레이 이펙트에 관련된 정보들을 지니고 있음.
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	// 어떤 버프를 사용해야 하는지에 영향을 줄 수 있으므로 소스 및 대상에서 태그를 수집합니다
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// --------------------------------------
	//	Damage Done = AttackPower > AttackMagic? AttackPower - MeleeDefence : AttackMagic - MagicDefence;
	// 스태프는 마법데미지만 지니고 있고 검, 총 등은 물리 데미지만 지니고 있으므로 둘 중 높은 쪽의 데미지만 취급한다.
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
		UE_LOG(LogTemp, Error, TEXT("AttackPower%.f"), AttackPower);
		UE_LOG(LogTemp, Error, TEXT("MeleeDefence%.f"), MeleeDefence);
	}
	else 
	{
		DamageDone = AttackMagic - MagicDefence;
	}
	if (DamageDone > 0.f)
	{
		UE_LOG(LogTemp, Error, TEXT("%.f"), DamageDone);
		// 데미지를 HP에 Add함 Property는 직접적인 대상의 주소값을 지칭함.
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatic().HealthProperty, EGameplayModOp::Additive, -DamageDone));
	}

}
