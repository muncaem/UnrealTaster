// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CraftingSystem.h"
#include "InventorySystem.h"
#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
public:
	UPROPERTY()
	UInventorySystem* PublicInventory;

	UPROPERTY()
	UCraftingSystem* PublicCraftingSystem;

	// CSV 파싱 전까지 임시 데이터 할당한 BP 클래스
	UPROPERTY()
	TSubclassOf<UCraftingSystem> CraftingSystemBPClass;
};
