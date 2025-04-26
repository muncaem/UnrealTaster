// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftWidget.h"

void UCraftWidget::InitWidget(UCraftingSystem* System)
{
	CraftingSystem = System;
	CreateCraftRecipeButtons();
}

void UCraftWidget::CreateCraftRecipeButtons()
{
	if (!RecipesContainer) return;

	RecipesContainer->ClearChildren();

	// 제작 데이터들 가져오기
	TArray<FCraftBaseData> CraftLists = CraftingSystem->GetCraftList();

	// 제작 리스트 버튼 생성 및 데이터 할당
	for (const FCraftBaseData& Recipe : CraftLists)
	{
		UCraftItemButton* NewButton = CreateWidget<UCraftItemButton>(this, CraftItemButtonClass);
		if (NewButton)
		{
			//NewButton->SetRecipeData(Recipe);
			RecipesContainer->AddChild(NewButton);
		}
	}

}

void UCraftWidget::SetDetailData()
{
	// 제작 디테일 Panel에 데이터 할당
}

void UCraftWidget::SetMakeActivate()
{
	// CraftItemButton 눌렀을 때 활/비활 여부 받아서 버튼 활성화 처리
}

void UCraftWidget::OnMakeButtonClicked()
{
	// 제작 버튼 눌렀을 때 실제 제작 -> CraftingSystme의 Craft 연결
}

void UCraftWidget::OnExitButtonClicked()
{
	// 플레이어 뷰포트에서 CraftWidget 내리기
}
