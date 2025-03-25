// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

void UInventorySystem::ToggleInventoryUI(AController* OwningController)
{
    if (!InventoryWidget || !OwningController) return;

    bIsUIOpen = !bIsUIOpen;

    ESlateVisibility NewVisibility = bIsUIOpen
        ? ESlateVisibility::Visible
        : ESlateVisibility::Hidden;

    InventoryWidget->SetVisibility(NewVisibility);
    InventoryWidget->OnVisibleChanged(NewVisibility, Cast<APlayerController>(OwningController));
}

void UInventorySystem::AddItem(const FInventoryItem& NewItem)
{
    for (FInventoryItem& Item : Items)
    {
        if (Item.ItemID == NewItem.ItemID)
        {
            Item.Quantity += NewItem.Quantity;
            return;
        }
    }

    Items.Add(NewItem);
    SetSlotImage(NewItem.Icon);
}

bool UInventorySystem::GetItem(int32 Index, FInventoryItem& OutItem) const
{
    if (Items.IsValidIndex(Index))
    {
        OutItem = Items[Index];
        return true;
    }
    return false;
}

const TArray<FInventoryItem>& UInventorySystem::GetAllItems() const
{
    return Items;
}

void UInventorySystem::SetSlotImage(UTexture2D* Icon)
{
    if (InventoryWidget)
    {
        InventoryWidget->SetWidgetImage(Icon);
    }
}
