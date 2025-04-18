// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingTable.h"

// [ ACraftingTable(게임 월드 담당) ]
// 씬에 배치되는 제작대
// 플레이어가 접근하면 UI 열기
// 버튼 누르면 CraftingSystem에 위임

void ACraftingTable::OpenCraftUI()
{
	//OpenCraftUI(Player);
}

bool ACraftingTable::TryCraft()
{
	//if (CraftingSystem->CanCraft(RecipeID, PlayerInventory->Items))
	//{
	//	CraftingSystem->Craft(RecipeID, PlayerInventory);
	//	return true;
	//}
	//return false;
	return false;
}

// Sets default values
ACraftingTable::ACraftingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACraftingTable::BeginPlay()
{
	Super::BeginPlay();
	
	CraftingSystem = NewObject<UCraftingSystem>(this);
	//CraftingSystem->AllRecipes = ConvertDataTableToArray(CraftingTableData); // 필요시
}

// Called every frame
void ACraftingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

