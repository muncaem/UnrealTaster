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


	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
	//	FString::Printf(TEXT("Before SetBrush - ItemWidget.Num(): %d"), ItemWidget.Num()));

	//if (!ItemWidget.IsValidIndex(ItemValue))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ItemWidget Index is out of bounds!"));
	//	return;
	//}

	//if (ItemWidget[ItemValue] == nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ItemWidget is nullptr! Something cleared it!"));
	//	return;
	//}

	if (NewTexture)
	{
		FSlateBrush Brush;
		Brush.SetResourceObject(NewTexture);

		Item1->SetBrush(Brush);
		/*if (ItemWidget.IsValidIndex(ItemValue) && ItemWidget[ItemValue] != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
				FString::Printf(TEXT("Setting brush for ItemWidget[%d]: %s"), ItemValue, *ItemWidget[ItemValue]->GetName()));

			ItemWidget[ItemValue]->SetBrush(Brush);
			ItemValue++;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
				FString::Printf(TEXT("ItemWidget[%d] is invalid or nullptr!"), ItemValue));
		}*/
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 배열 초기화 (기존 값 삭제 후 다시 추가)
	ItemWidget.Empty();

	// 개별 바인딩된 위젯을 배열에 추가
	ItemWidget.Add(Item1);
	ItemWidget.Add(Item2);
	ItemWidget.Add(Item3);
	ItemWidget.Add(Item4);
	ItemWidget.Add(Item5);
	ItemWidget.Add(Item6);
	ItemWidget.Add(Item7);
	ItemWidget.Add(Item8);
	ItemWidget.Add(Item9);
	ItemWidget.Add(Item10);
	ItemWidget.Add(Item11);
	ItemWidget.Add(Item12);
	ItemWidget.Add(Item13);
	ItemWidget.Add(Item14);
	ItemWidget.Add(Item15);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
		FString::Printf(TEXT("Inventory Widget Initialized! ItemWidget Num: %d"), ItemWidget.Num()));

	for (int32 i = 0; i < ItemWidget.Num(); i++)
	{
		if (ItemWidget[i] == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ItemWidget[%d] is nullptr!"), i));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("ItemWidget[%d] is valid."), i));
		}
	}

	//// 15개의 UImage 위젯을 찾아서 배열에 추가
	//for (int32 i = 1; i <= 15; i++)
	//{
	//	FString WidgetName = FString::Printf(TEXT("Item%d"), i);
	//	UImage* FoundImage = Cast<UImage>(GetWidgetFromName(FName(*WidgetName)));

	//	if (FoundImage)
	//	{
	//		ItemWidget.Add(FoundImage);
	//		//// 성공적으로 찾은 경우
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("UImage found: %s"), *WidgetName));
	//	}
	//	else
	//	{
	//		// 찾지 못한 경우
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("UImage not found: %s"), *WidgetName));
	//	}
	//}

	///*GEngine->AddOnScreenDebugMessage(
	//	-1, 5.0f, FColor::Red,
	//	FString::Printf(TEXT("Final ItemWidget Num: %d"), ItemWidget.Num())
	//);*/

	//// **배열 내부 요소가 올바르게 할당됐는지 확인**
	//for (int32 i = 0; i < ItemWidget.Num(); i++)
	//{
	//	if (ItemWidget[i] == nullptr)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ItemWidget[%d] is nullptr!"), i));
	//	}
	//	else
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
	//			FString::Printf(TEXT("ItemWidget[%d] found: %s"), i, *ItemWidget[i]->GetName()));
	//	}
	//}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
	//	FString::Printf(TEXT("ItemValue: %d, MaxItem: %d, ItemWidget.Num(): %d"),
	//		ItemValue, MaxItem, ItemWidget.Num()));

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
	//	FString::Printf(TEXT("NativeConstruct - ItemWidget.Num(): %d"), ItemWidget.Num()));
}