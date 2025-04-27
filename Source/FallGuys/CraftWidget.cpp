// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftWidget.h"

void UCraftWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonExit)
		ButtonExit->OnClicked.AddDynamic(this, &UCraftWidget::OnExitButtonClicked);

	if (ButtonMake)
		ButtonMake->OnClicked.AddDynamic(this, &UCraftWidget::OnMakeButtonClicked);
}

void UCraftWidget::InitWidget(UCraftingSystem* System, APlayerController* PC)
{
	CraftingSystem = System;
	PlayerController = PC;
	DetailContentCanvas->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 1; i <= 3; i++)
	{
		FString TextWidgetName = FString::Printf(TEXT("IngredientsText%d"), i);
		FString ImageWidgetName = FString::Printf(TEXT("IngredientsImage%d"), i);
		UTextBlock* FoundTextWidget = Cast<UTextBlock>(GetWidgetFromName(FName(*TextWidgetName)));
		UImage* FoundImageWidget = Cast<UImage>(GetWidgetFromName(FName(*ImageWidgetName)));

		FoundTextWidget->SetVisibility(ESlateVisibility::Hidden);
		FoundImageWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	CreateCraftRecipeButtons();
}

void UCraftWidget::CreateCraftRecipeButtons()
{
	if (!RecipesContainer) return;

	RecipesContainer->ClearChildren();

	// 제작 데이터들 가져오기
	CraftLists = CraftingSystem->GetCraftList();

	int32 Index = 0;
	// 제작 리스트 버튼 생성 및 데이터 할당
	for (const FCraftBaseData& Recipe : CraftLists)
	{
		UCraftItemButton* NewButton = CreateWidget<UCraftItemButton>(this, CraftItemButtonClass);
		if (NewButton)
		{
			NewButton->SetRecipeData(Recipe.CraftID, Recipe.Icon, Index);
			NewButton->OnCraftListItemSelected.AddDynamic(this, &UCraftWidget::OnCraftItemButtonClicked);

			RecipesContainer->AddChild(NewButton);
			Index++;
		}
	}

}

void UCraftWidget::OnCraftItemButtonClicked(int32 ButtonIndex)
{
	if (!CraftLists.IsValidIndex(ButtonIndex)) return;

	DetailContentCanvas->SetVisibility(ESlateVisibility::Visible);

	FCraftBaseData DetailData = CraftLists[ButtonIndex];

	DetailItemID->SetText(FText::FromName(DetailData.CraftID));
	DetailItemICon->SetBrushFromTexture(DetailData.Icon);
	DetailItemDescription->SetText(FText::FromString(DetailData.Description));

	for (int i = 0; i < DetailData.Ingredients.Num(); i++)
	{
		FString TextWidgetName = FString::Printf(TEXT("IngredientsText%d"), i + 1);
		FString ImageWidgetName = FString::Printf(TEXT("IngredientsImage%d"), i + 1);
		UTextBlock* FoundTextWidget = Cast<UTextBlock>(GetWidgetFromName(FName(*TextWidgetName)));
		UImage* FoundImageWidget = Cast<UImage>(GetWidgetFromName(FName(*ImageWidgetName)));
		//"0 / " + DetailData.Ingredients[i].Quantity
		FoundTextWidget->SetText(FText::FromString(FString::Printf(TEXT("0/%d"), DetailData.Ingredients[i].Quantity)));
		FoundImageWidget->SetBrushFromTexture(DetailData.Ingredients[i].Icon);

		FoundTextWidget->SetVisibility(ESlateVisibility::Visible);
		FoundImageWidget->SetVisibility(ESlateVisibility::Visible);
	}

	DetailItemCraftTime->SetText(FText::FromString(FString::Printf(TEXT("%.1f h"), DetailData.ShowCraftingTime)));
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
	this->SetVisibility(ESlateVisibility::Hidden);

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;
}
