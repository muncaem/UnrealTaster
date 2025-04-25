// Fill out your copyright notice in the Description page of Project Settings.

#include "CraftingSystem.h"
#include "InventorySystem.h"
#include "Tool.h"

// [ UCraftingSystem(논리 담당) ]
// 전체 제작 레시피 목록 보관(CSV 불러오기 포함)
// 제작 가능 여부 검사(재료 충분한지)
// 재료 차감, 아이템 반환 등 로직


// 제작 리스트 RETURN
TArray<FCraftBaseData> UCraftingSystem::GetCraftList()
{
	return TArray<FCraftBaseData>();
}

// 제작 리스트에서 아이템 클릭/호버 시 아이템 데이터 정보 RETURN
FCraftBaseData UCraftingSystem::GetCraftItemData(int32 Index)
{
	if (AllRecipes.IsValidIndex(Index))
		return AllRecipes[Index];

	return FCraftBaseData();
}


// 제작 가능한지 체크 - 제작 리스트 아이템 누를 때마다 체크해서 '만들기' 아이콘 상태 변경 t/f 처리
bool UCraftingSystem::CanCraft(int32 Index, const TArray<FInventoryItem>& Inventory)
{
	if (AllRecipes.IsValidIndex(Index))
		return false;

	// 인벤토리를 Map으로 변환 (ID → Quantity)
	TMap<FName, int32> InventoryMap;
	for (const FInventoryItem& HavedItem : Inventory)
	{
		InventoryMap.Add(HavedItem.ItemID, HavedItem.Quantity);
	}

	// 재료 확인
	for (const FReceiptItem& RecipeDatas : AllRecipes[Index].Ingredients)
	{
		const int32* FoundQuantity = InventoryMap.Find(RecipeDatas.ItemID);
		if (FoundQuantity == nullptr || *FoundQuantity < RecipeDatas.Quantity)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
				FString::Printf(TEXT("제작 아이템 %s 수량 부족"), *RecipeDatas.ItemID.ToString()));

			return false;
		}
	}

	return false;
}

// CanCraft 체크 이후 실제 제작
void UCraftingSystem::Craft(int32 Index, UInventorySystem* Inventory)
{
	// 인벤토리에서 필요했던 아이템들 다 제거하고 만들어진 아이템 인벤토리로 반환
	if (!Inventory || !AllRecipes.IsValidIndex(Index))
	{
		return;
	}

	// 재료로 사용된 아이템 제거
	for (const FReceiptItem& RecipeDatas : AllRecipes[Index].Ingredients)
	{
		Inventory->RemoveItemByID(RecipeDatas.ItemID, RecipeDatas.Quantity);
	}

	// 새로운 아이템 인벤토리로 반환 (액터 생성은 인벤토리 시스템에서 처리)
	FInventoryItem CraftedItem(
		AllRecipes[Index].CraftID,
		1,
		ATool::StaticClass(),  // TSubclassOf<AActor>
		AllRecipes[Index].Icon
	);
	Inventory->AddItem(CraftedItem);

}
