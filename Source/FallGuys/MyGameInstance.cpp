// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "EventHub.h"

void UMyGameInstance::Init()
{
	Super::Init();

	PublicInventory = NewObject<UInventorySystem>(this);
	PublicCraftingSystem = NewObject<UCraftingSystem>(this);
	UEventHub::Get();
}
