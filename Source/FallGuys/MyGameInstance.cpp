// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "EventHub.h"

void UMyGameInstance::Init()
{
	Super::Init();

	PublicInventory = NewObject<UInventorySystem>(this);

	// CSV 파싱 전까지 임시 데이터 할당한 BP 클래스
	CraftingSystemBPClass = StaticLoadClass(UCraftingSystem::StaticClass(), nullptr, TEXT("/Game/BP_CraftingSystem.BP_CraftingSystem_C"));
	if (CraftingSystemBPClass)
		PublicCraftingSystem = NewObject<UCraftingSystem>(this, CraftingSystemBPClass);

	// CSV 로드 이후 PublicCraftingSystem UCraftingSystem으로 변경
	//PublicCraftingSystem = NewObject<UCraftingSystem>(this);

	UEventHub::Get();
}
