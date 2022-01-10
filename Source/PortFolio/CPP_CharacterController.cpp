// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CharacterController.h"
#include "Inventory/CPP_InventoryUW.h"
#include "CharacterBase.h"

#include "kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "kismet/GameplayStatics.h"

// 마우스 커서 숨기기 위해 임포트
#include "Components/DecalComponent.h"


ACPP_CharacterController::ACPP_CharacterController()
{
	// 틱 활성화
	PrimaryActorTick.bCanEverTick = true;

}

// 마우스 커서로 캐릭터를 이동하는 함수
void ACPP_CharacterController::MoveToHitLocation_Implementation(FHitResult Hit)
{
	// VectorLength 대용
	if (GetPawn()) {
		if (MinClickDinstance <= ((GetPawn()->GetActorLocation()) - Hit.Location).Size())
		{
			FVector Target = Hit.Location;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Target);
			this->GetPawn()->AddMovementInput(UKismetMathLibrary::GetDirectionUnitVector(GetPawn()->GetActorLocation(), Target), (GetPawn()->GetActorLocation() - Hit.Location).Size());
		}
	}
}

void ACPP_CharacterController::EventMoveToHitLocation_Implementation(FHitResult Hit)
{
	MoveToHitLocation(Hit);
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
			// 마우스 커서 위치로 히트리절트를 구함
			FHitResult Hit;
			GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
			if (HasAuthority)
				EventMoveToHitLocation(Hit);
			else {
				EventMoveToHitLocation(Hit);

			}
		}
	}
}

void ACPP_CharacterController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	character = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ACPP_CharacterController::OnSetDestination_Pressed()
{
	// 우클릭을 누르고 있음.
	bSetDestination = true;
}

void ACPP_CharacterController::OnSetDestination_Released()
{
	// 우클릭을 누르고 있지 않음.
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
				Inventory->SpawnInventory();
				Inventory->AddToViewport();
				Inventory->SetFocus();


				if (character != nullptr) {
					//character->cursorVisible(false);
				}
				bInventory = true;
			}
		}
	}

}

void ACPP_CharacterController::InvisibleInventory()
{
	if (character != nullptr) {
		//character->cursorVisible(true);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Nusadfll"), 0);
	}
	bInventory = false;

}

void ACPP_CharacterController::ChangeItem()
{
	if (Inventory != nullptr)
	{
		Inventory->ChangeItem();
	}
}

void ACPP_CharacterController::ChangeEquip()
{
	if (Inventory != nullptr)
	{
		Inventory->ChangeEquip();
	}
}

void ACPP_CharacterController::InventoryDropMenuClose()
{
	if (Inventory != nullptr)
	{
		Inventory->CloseDropMenu();
	}
}

