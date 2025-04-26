// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftItemButton.h"

void UCraftItemButton::SetRecipeData()
{
    //RecipeData = InData;
    //RecipeNameText->SetText(FText::FromName(InData.CraftID));
    //if (RecipeIcon && InData.Icon)
    //{
    //    RecipeIcon->SetBrushFromTexture(InData.Icon);
    //}

    //if (RecipeButton)
    //{
    //    RecipeButton->OnClicked.AddDynamic(this, &URecipeButtonWidget::HandleButtonClicked);
    //}
}

void UCraftItemButton::HandleButtonClicked()
{
    //OnRecipeSelected.Broadcast(RecipeData);  // CraftWidget에게 선택 알림
    //CraftingSystem CanCraft 결과 바탕으로 bool 값 CraftWidget으로 전달 => 델리게이트로 처리.
}
