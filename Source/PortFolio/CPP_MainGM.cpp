// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainGM.h"
#include "BaseCharacter.h"
#include "CPP_CharacterController.h"
#include "UObject/ConstructorHelpers.h"

ACPP_MainGM::ACPP_MainGM() {
	
	DefaultPawnClass = ConstructorHelpers::FClassFinder<ABaseCharacter>(TEXT("Blueprint'/Game/BluePrint/Character/BP_Character.BP_Character_C'")).Class;
	
	PlayerControllerClass = ConstructorHelpers::FClassFinder<ACPP_CharacterController>(TEXT("Blueprint'/Game/BluePrint/Character/PlayerController.PlayerController_C'")).Class;

}