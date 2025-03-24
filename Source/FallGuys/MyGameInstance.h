// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
};
