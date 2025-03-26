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

void UInventorySystem::SetInventoryWidget(UInventoryWidget* InWidget)
{
    InventoryWidget = InWidget;

    if (InventoryWidget)
    {
        InventoryWidget->OnSlotClicked.BindUObject(this, &UInventorySystem::DropItemByIndex);
    }
}

void UInventorySystem::DropItemByIndex(int32 SlotIndex, FVector DropLocation)
{
    DropItem(SlotIndex, DropLocation, GetWorld());
}

void UInventorySystem::AddItem(const FInventoryItem& NewItem)
{
    for (FInventoryItem& Item : Items)
    {
        if (Item.ItemID == NewItem.ItemID)
        {
            Item.Quantity += NewItem.Quantity;

            // 액터 제거
            if (IsValid(NewItem.SourceActor))
                NewItem.SourceActor->Destroy();

            return;
        }
    }

    Items.Add(NewItem);

    // 액터 제거 (새로 추가된 경우도)
    if (IsValid(NewItem.SourceActor))
    {
        NewItem.SourceActor->Destroy();
    }

    GEngine->AddOnScreenDebugMessage(
        -1,
        5.0f,
        FColor::Red,
        FString::Printf(TEXT("Added Item: %s"), *NewItem.ItemID.ToString())
    );

    // 새로고침
    if (InventoryWidget)
    {
        TArray<UTexture2D*> IconArray;

        for (const FInventoryItem& Item : Items)
        {
            if (Item.Icon)
            {
                IconArray.Add(Item.Icon);
            }
        }

        InventoryWidget->SetWidgetImage(IconArray);
    }
    /*SetSlotImage(NewItem.Icon);*/
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

void UInventorySystem::DropItem(int32 Index, const FVector& DropLocation, UWorld* World)
{
    if (!Items.IsValidIndex(Index) || !World) return;

    const FInventoryItem& Item = Items[Index];
    if (!Item.ItemActorClass) return;

    // 아이템 액터 생성
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AActor* DroppedActor = World->SpawnActor<AActor>(
        Item.ItemActorClass,
        DropLocation,
        FRotator::ZeroRotator,
        SpawnParams
    );

    // 수량 감소
    if (Item.Quantity <= 1)
    {
        Items.RemoveAt(Index);
    }
    else
    {
        Items[Index].Quantity--;
    }

    // 위젯 갱신
    if (InventoryWidget)
    {
        TArray<UTexture2D*> IconArray;
        for (const FInventoryItem& I : Items)
        {
            if (I.Icon)
                IconArray.Add(I.Icon);
        }
        InventoryWidget->SetWidgetImage(IconArray);
    }
}
