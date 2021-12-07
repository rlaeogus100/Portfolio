// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CharacterController.h"
#include "Inventory/CPP_InventoryUW.h"
#include "BaseCharacter.h"

#include "kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "kismet/GameplayStatics.h"

// ���콺 Ŀ�� ����� ���� ����Ʈ
#include "Components/DecalComponent.h"


ACPP_CharacterController::ACPP_CharacterController()
{
	// ƽ Ȱ��ȭ
	PrimaryActorTick.bCanEverTick = true;

}

// ���콺 Ŀ���� ĳ���͸� �̵��ϴ� �Լ�
void ACPP_CharacterController::MoveToHitLocation(FHitResult Hit)
{
	// VectorLength ���
	if (MinClickDinstance <= ((GetPawn()->GetActorLocation()) - Hit.Location).Size())
	{
		FVector Target = Hit.Location;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Target);
	}

}

void ACPP_CharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ACPP_CharacterController::OnSetDestination_Pressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ACPP_CharacterController::OnSetDestination_Released);
	InputComponent->BindAction("OnInventory", IE_Pressed, this, &ACPP_CharacterController::OnInventory_Pressed);

}

void ACPP_CharacterController::Tick(float DeltaSeconds)
{
	if (bSetDestination)
	{
		if (!bInventory)
		{
			// ���콺 Ŀ�� ��ġ�� ��Ʈ����Ʈ�� ����
			FHitResult Hit;
			GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
			MoveToHitLocation(Hit);
		}
	}
}

void ACPP_CharacterController::BeginPlay()
{
	Super::BeginPlay();
	character = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ACPP_CharacterController::OnSetDestination_Pressed()
{
	// ��Ŭ���� ������ ����.
	bSetDestination = true;
}

void ACPP_CharacterController::OnSetDestination_Released()
{
	// ��Ŭ���� ������ ���� ����.
	bSetDestination = false;
}

void ACPP_CharacterController::OnInventory_Pressed()
{
	if (bInventory)
	{
		if (Inventory != nullptr)
		{
			Inventory->InvisibleSelf();
		}
	}
	else
	{
		if (Inventory_Widget != nullptr)
		{
			Inventory = CreateWidget< UCPP_InventoryUW>(this, Inventory_Widget);
			if (Inventory != nullptr)
			{
				Inventory->AddToViewport();
				UWidgetBlueprintLibrary::SetInputMode_GameAndUI(this);
				bShowMouseCursor = true;

				if (character != nullptr) {
					character->cursorVisible(false);
					UE_LOG(LogTemp, Log, TEXT("Null"), 0);
				}
				bInventory = true;
			}
		}
	}

}

void ACPP_CharacterController::InvisibleInventory()
{
	bShowMouseCursor = false;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	if (character != nullptr) {
		character->cursorVisible(true);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Nusadfll"), 0);
	}
	bInventory = false;

}

