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

protected:
	UPROPERTY(VisibleAnywhere)
	int32 ItemValue = 0;

	UPROPERTY(VisibleAnywhere)
	int32 MaxItem = 15;

	TArray<UImage*> ItemWidget;
	
public:
	virtual void NativeConstruct() override;
};
