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
    UPROPERTY(meta = (BindWidget))
    UButton* CraftItemButton;

    UPROPERTY(meta = (BindWidget))
    UImage* CraftItemIcon;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* CraftItemNameText;

    //FCraftBaseData RecipeData;

    //UPROPERTY(BlueprintAssignable)
    //FOnRecipeSelected OnRecipeSelected;  // Delegate

    void SetRecipeData(/*const FCraftBaseData& InData*/);

private:
    UFUNCTION()
    void HandleButtonClicked();
};
