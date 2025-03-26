// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "InventoryWidget.h"
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
	UPROPERTY()
	AActor* SourceActor = nullptr;  // 아이템 줍기 전 존재하던 액터

	// 생성자
	FInventoryItem()
		: ItemID(NAME_None), Icon(nullptr), Quantity(1), ItemActorClass(nullptr), SourceActor(nullptr)
	{
	}

	FInventoryItem(FName InID, int32 InQty, TSubclassOf<AActor> InClass, UTexture2D* InIcon = nullptr, AActor* InActor = nullptr)
		: ItemID(InID), Quantity(InQty), ItemActorClass(InClass), Icon(InIcon), SourceActor(InActor)
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

private:
	UPROPERTY()
	UInventoryWidget* InventoryWidget = nullptr;

	bool bIsUIOpen = false;

public:
	void ToggleInventoryUI(AController* OwningController);
	void SetInventoryWidget(UInventoryWidget* InWidget);
	void DropItemByIndex(int32 SlotIndex, FVector DropLocation);

	void AddItem(const FInventoryItem& NewItem);
	//void RemoveItem(int32 Index);
	bool GetItem(int32 Index, FInventoryItem& OutItem) const;
	const TArray<FInventoryItem>& GetAllItems() const;

	void DropItem(int32 Index, const FVector& DropLocation, UWorld* World);
};
