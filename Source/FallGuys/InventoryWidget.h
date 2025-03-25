// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG.h"
#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetWidgetImage(UTexture2D* NewTexture);

	void OnVisibleChanged(ESlateVisibility InVisibility, APlayerController* InPlayerController);

	int32 GetSlotClickIndex(int32 idx);

protected:
	void BindSlotClickHandler();

	UFUNCTION()
	void OnItemClicked(int32 SlotIdx);

protected:
	UPROPERTY(VisibleAnywhere)
	int32 ItemValue = 0;

	UPROPERTY(VisibleAnywhere)
	int32 MaxItem = 15;

	TArray<UImage*> ItemWidget;
	TArray<UButton*> ItemButton;
	
public:
	virtual void NativeConstruct() override;
};
