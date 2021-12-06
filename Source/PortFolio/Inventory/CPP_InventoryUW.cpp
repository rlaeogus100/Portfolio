// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_InventoryUW.h"
#include "../CPP_CharacterController.h"

void UCPP_InventoryUW::InvisibleSelf()
{
	RemoveFromParent();
	Cast<ACPP_CharacterController>(GetOwningPlayer())->InvisibleInventory();
}
