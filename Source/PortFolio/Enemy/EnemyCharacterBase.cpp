// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterBase.h"
#include "kismet/GameplayStatics.h"
#include "../CharacterBase.h"
#include "kismet/KismetMathLibrary.h"

#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"


AEnemyCharacterBase::AEnemyCharacterBase() {

	EnemyHPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHPBar"));

	EnemyHPBar->SetupAttachment(RootComponent);
}


void AEnemyCharacterBase::NameWidgetRotationUpdate()
{
	if (bHPVisible) {

		ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (character != nullptr) {
			ACharacterBase* base = Cast<ACharacterBase>(character);
			if (base != nullptr) {
				//USceneComponent* CamTran = base->Camera->GetTransformComponent();
				FRotator CamRot = base->Camera->GetComponentRotation();
				FRotator TempRot = FRotator(CamRot.Pitch * -1.f, CamRot.Yaw, CamRot.Roll);
				FRotator Rot = UKismetMathLibrary::ComposeRotators(TempRot, FRotator(-180, 0, -180));
				EnemyHPBar->SetWorldRotation(Rot);
			}
		}
	}
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NameWidgetRotationUpdate();
}

// 리턴은 값을 변경했냐 안했냐를 보내는 거지 Bar의 visible값을 보내는게 아님
bool AEnemyCharacterBase::SetHPBarVisible(bool a)
{
	if (EnemyHPBar) {
		EnemyHPBar->SetVisibility(a);
		bHPVisible = a;
		return true;
	}

	return false;
}


