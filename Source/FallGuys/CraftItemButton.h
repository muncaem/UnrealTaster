// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UMG.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftItemButton.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API UCraftItemButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftListItemSelected, int32, Index);

public:
    UPROPERTY(meta = (BindWidget))
    UButton* CraftItemButton;

    UPROPERTY(meta = (BindWidget))
    UImage* CraftItemIcon;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* CraftItemNameText;

    UPROPERTY()
    int32 CraftItemIndex;

    UPROPERTY(BlueprintAssignable)
    FOnCraftListItemSelected OnCraftListItemSelected;  // Delegate

    void SetRecipeData(FName ItemID, UTexture2D* Icon, int32 Index);

private:
    UFUNCTION()
    void HandleButtonClicked();
};
