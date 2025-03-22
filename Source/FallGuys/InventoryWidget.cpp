// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

void UInventoryWidget::SetWidgetImage(UTexture2D* NewTexture)
{
	if (NewTexture && ItemWidget.IsValidIndex(ItemValue))
	{
	    FSlateBrush Brush;
	    Brush.SetResourceObject(NewTexture);

	    if (ItemValue < MaxItem)
	    {
	        ItemWidget[ItemValue]->SetBrush(Brush);
	        ItemValue++;
	    }
	}
	else
	{
	    GEngine->AddOnScreenDebugMessage(
	        -1,
	        5.0f,
	        FColor::Red,
	        FString::Printf(TEXT("ItemWidget[%d] is invalid or null!"), ItemValue)
	    );
	}
}

void UInventoryWidget::OnVisibleChanged(ESlateVisibility InVisibility, APlayerController* PC)
{
	if (!PC) return;
	
	if (InVisibility == ESlateVisibility::Visible)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false); // 마우스 유지
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
	else
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 배열 초기화 (기존 값 삭제 후 다시 추가)
	ItemWidget.Empty();

	// 15개의 UImage 위젯을 찾아서 배열에 추가
	for (int32 i = 1; i <= 15; i++)
	{
		FString WidgetName = FString::Printf(TEXT("Item%d"), i);
		UImage* FoundImage = Cast<UImage>(GetWidgetFromName(FName(*WidgetName)));

		if (FoundImage)
		{
			ItemWidget.Add(FoundImage);
			//// 성공적으로 찾은 경우
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("UImage found: %s"), *WidgetName));
		}
		else
		{
			// 찾지 못한 경우
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("UImage not found: %s"), *WidgetName));
		}
	}
}