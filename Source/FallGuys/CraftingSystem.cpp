// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingSystem.h"

// [ UCraftingSystem(논리 담당) ]
// 전체 제작 레시피 목록 보관(CSV 불러오기 포함)
// 제작 가능 여부 검사(재료 충분한지)
// 재료 차감, 아이템 반환 등 로직

bool UCraftingSystem::CanCraft(FName RecipeID, const TArray<FInventoryItem>& Inventory)
{
	return false;
}

void UCraftingSystem::Craft(FName RecipeID, UInventorySystem* Inventory)
{
}
