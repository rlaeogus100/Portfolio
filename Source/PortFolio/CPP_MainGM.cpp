// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MainGM.h"
#include "BaseCharacter.h"

ACPP_MainGM::ACPP_MainGM() {
	
	DefaultPawnClass = ConstructorHelpers::FClassFinder<ABaseCharacter>(TEXT("Blueprint'/Game/BluePrint/Character/BP_Character.BP_Character_C'")).Class;


}