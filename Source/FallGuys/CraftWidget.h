// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CraftingSystem.h"
#include "CraftItemButton.h"
#include "UMG.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftWidget.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API UCraftWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* RecipesContainer;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* DetailContentCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCraftItemButton> CraftItemButtonClass;

	UPROPERTY()
	UCraftingSystem* CraftingSystem;

public:
	void InitWidget(UCraftingSystem* CraftingSystem);
private:
	void CreateCraftRecipeButtons();
	
private:
	void SetDetailData();
	void SetMakeActivate();
	void OnMakeButtonClicked();
	void OnExitButtonClicked();
};
