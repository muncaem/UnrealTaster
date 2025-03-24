// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventorySystem.generated.h"

/**
 * 
 */

USTRUCT()
struct FInventoryItem
{
	GENERATED_BODY()

	FName ItemID;
	UTexture2D* Icon = nullptr;
	int32 Quantity = 1;
	TSubclassOf<AActor> ItemActorClass = nullptr;

	// »ý¼ºÀÚ
	FInventoryItem()
		: ItemID(NAME_None), Icon(nullptr), Quantity(1), ItemActorClass(nullptr)
	{
	}

	FInventoryItem(FName InID, int32 InQty, TSubclassOf<AActor> InClass, UTexture2D* InIcon = nullptr)
		: ItemID(InID), Quantity(InQty), ItemActorClass(InClass), Icon(InIcon)
	{
	}
};
UCLASS()
class FALLGUYS_API UInventorySystem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<FInventoryItem> Items;

public:
	void AddItem(const FInventoryItem& NewItem);
	//void RemoveItem(int32 Index);
	bool GetItem(int32 Index, FInventoryItem& OutItem) const;
	const TArray<FInventoryItem>& GetAllItems() const;
};
