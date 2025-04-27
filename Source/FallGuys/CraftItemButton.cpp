// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftItemButton.h"

void UCraftItemButton::SetRecipeData(FName ItemID, UTexture2D* Icon, int32 Index)
{
    CraftItemIndex = Index;

    CraftItemNameText->SetText(FText::FromName(ItemID));
    CraftItemIcon->SetBrushFromTexture(Icon);

    if (CraftItemButton)
    {
        CraftItemButton->OnClicked.AddDynamic(this, &UCraftItemButton::HandleButtonClicked);
    }
}

void UCraftItemButton::HandleButtonClicked()
{
    OnCraftListItemSelected.Broadcast(CraftItemIndex);
    
    // CraftingSystem CanCraft 결과 바탕으로 bool 값 CraftWidget으로 전달 => 델리게이트로 처리.
    // CraftWidget에서 브로드 캐스트 값 받아서 디테일 값 처리
    

}
