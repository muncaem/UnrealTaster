// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"

void UInventoryWidget::SetWidgetImage(const TArray<UTexture2D*> Icons)
{
	// 모든 슬롯 초기화
	// 슬롯을 초기화해주고 넣어야 인식된다.
	for (int32 i = 0; i < ItemWidget.Num(); i++)
	{
		if (ItemWidget[i])
			ItemWidget[i]->SetBrush(FSlateBrush()); // 비우기
	}

	// 새로 채우기
	for (int32 i = 0; i < Icons.Num() && i < ItemWidget.Num(); i++)
	{
		if (Icons[i] && ItemWidget[i])
		{
			FSlateBrush Brush;
			Brush.SetResourceObject(Icons[i]);
			ItemWidget[i]->SetBrush(Brush);
		}
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

int32 UInventoryWidget::GetSlotClickIndex(int32 idx)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.0f,
		FColor::Red,
		FString::Printf(TEXT("Clicked Index [%d]"), idx)
	);
	return idx;
}

//버튼 누르면 호출
void UInventoryWidget::OnItemClicked(int32 SlotIdx)
{
	GetSlotClickIndex(SlotIdx);

	APawn* OwnerPawn = GetOwningPlayerPawn();
	if (!OwnerPawn) return;

	FVector DropLocation = OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * 150.f;

	if (OnSlotClicked.IsBound())
	{
		OnSlotClicked.Execute(SlotIdx, DropLocation);
	}
}

void UInventoryWidget::OnSlot0Clicked() { OnItemClicked(0); }
void UInventoryWidget::OnSlot1Clicked() { OnItemClicked(1); }
void UInventoryWidget::OnSlot2Clicked() { OnItemClicked(2); }
void UInventoryWidget::OnSlot3Clicked() { OnItemClicked(3); }
void UInventoryWidget::OnSlot4Clicked() { OnItemClicked(4); }
void UInventoryWidget::OnSlot5Clicked() { OnItemClicked(5); }
void UInventoryWidget::OnSlot6Clicked() { OnItemClicked(6); }
void UInventoryWidget::OnSlot7Clicked() { OnItemClicked(7); }
void UInventoryWidget::OnSlot8Clicked() { OnItemClicked(8); }
void UInventoryWidget::OnSlot9Clicked() { OnItemClicked(9); }
void UInventoryWidget::OnSlot10Clicked() { OnItemClicked(10); }
void UInventoryWidget::OnSlot11Clicked() { OnItemClicked(11); }
void UInventoryWidget::OnSlot12Clicked() { OnItemClicked(12); }
void UInventoryWidget::OnSlot13Clicked() { OnItemClicked(13); }
void UInventoryWidget::OnSlot14Clicked() { OnItemClicked(14); }



void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 배열 초기화 (기존 값 삭제 후 다시 추가)
	ItemWidget.Empty();
	ItemButton.Empty();
	SlotIndexMap.Empty();

	// 15개의 UImage 위젯을 찾아서 배열에 추가
	for (int32 i = 1; i <= MaxItem; i++)
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

	// 버튼 바인딩
	for (int32 i = 1; i <= MaxItem; i++)
	{
		FString WidgetName = FString::Printf(TEXT("Button%d"), i);
		UButton* FoundButton = Cast<UButton>(GetWidgetFromName(FName(*WidgetName)));

		if (FoundButton)
		{
			switch (i - 1)
			{
			case 0: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot0Clicked); break;
			case 1: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot1Clicked); break;
			case 2: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot2Clicked); break;
			case 3: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot3Clicked); break;
			case 4: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot4Clicked); break;
			case 5: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot5Clicked); break;
			case 6: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot6Clicked); break;
			case 7: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot7Clicked); break;
			case 8: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot8Clicked); break;
			case 9: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot9Clicked); break;
			case 10: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot10Clicked); break;
			case 11: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot11Clicked); break;
			case 12: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot12Clicked); break;
			case 13: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot13Clicked); break;
			case 14: FoundButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnSlot14Clicked); break;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UButton not found: %s"), *WidgetName);
		}
	}
}