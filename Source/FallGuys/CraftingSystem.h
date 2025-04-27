// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InventorySystem.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CraftingSystem.generated.h"

USTRUCT(BlueprintType)
struct FReceiptItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReceiptItem")
	FName ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReceiptItem")
	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReceiptItem")
	UTexture2D* Icon;
};

USTRUCT(BlueprintType)
struct FCraftBaseData : public FTableRowBase 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	FName CraftID = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	TArray<FReceiptItem> Ingredients;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	int32 MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	float ShowCraftingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	float RealCraftingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	FName RequiredEquipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	bool bNeedHighCraft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	FString Effection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CraftBase")
	UTexture2D* Icon;
};

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew)
class FALLGUYS_API UCraftingSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCraftBaseData> AllRecipes;

public:
	TArray<FCraftBaseData> GetCraftList();

private:
	FCraftBaseData GetCraftItemData(int32 Index);
	bool CanCraft(int32 Index, const TArray<FInventoryItem>& Inventory);
	void Craft(int32 Index, UInventorySystem* Inventory);
};
