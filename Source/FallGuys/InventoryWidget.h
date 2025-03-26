// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG.h"
#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_TwoParams(FOnInventorySlotClicked, int32 /*SlotIndex*/, FVector /*DropLocation*/)


UCLASS()
class FALLGUYS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*UFUNCTION(BlueprintCallable, Category = "UI")*/
	UFUNCTION()
	void SetWidgetImage(/*UTexture2D* NewTexture*/const TArray<UTexture2D*> Icons);

	void OnVisibleChanged(ESlateVisibility InVisibility, APlayerController* InPlayerController);

	// 외부에서 바인딩할 델리게이트
	FOnInventorySlotClicked OnSlotClicked;

	void OnItemClicked(int32 SlotIdx);

protected:
	int32 GetSlotClickIndex(int32 idx);
	/*UFUNCTION()
	void OnItemClicked(int32 SlotIdx);*/

	UFUNCTION() void OnSlot0Clicked();
	UFUNCTION() void OnSlot1Clicked();
	UFUNCTION() void OnSlot2Clicked();
	UFUNCTION() void OnSlot3Clicked();
	UFUNCTION() void OnSlot4Clicked();
	UFUNCTION() void OnSlot5Clicked();
	UFUNCTION() void OnSlot6Clicked();
	UFUNCTION() void OnSlot7Clicked();
	UFUNCTION() void OnSlot8Clicked();
	UFUNCTION() void OnSlot9Clicked();
	UFUNCTION() void OnSlot10Clicked();
	UFUNCTION() void OnSlot11Clicked();
	UFUNCTION() void OnSlot12Clicked();
	UFUNCTION() void OnSlot13Clicked();
	UFUNCTION() void OnSlot14Clicked();
	

protected:
	UPROPERTY(VisibleAnywhere)
	int32 ItemValue = 0;

	UPROPERTY(VisibleAnywhere)
	int32 MaxItem = 15;

	TArray<UImage*> ItemWidget;
	TArray<UButton*> ItemButton;

	// 슬롯 버튼 → 인덱스를 찾아서 처리
	TMap<UButton*, int32> SlotIndexMap;
	
public:
	virtual void NativeConstruct() override;
};
