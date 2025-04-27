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
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailItemID;
	UPROPERTY(meta = (BindWidget))
	UImage* DetailItemICon;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailItemDescription;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DetailItemCraftTime;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonExit;
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonMake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCraftItemButton> CraftItemButtonClass;

	UPROPERTY()
	UCraftingSystem* CraftingSystem;

	UPROPERTY()
	APlayerController* PlayerController;

private:
	TArray<FCraftBaseData> CraftLists;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnCraftItemButtonClicked(int32 ButtonIndex);

public:
	void InitWidget(UCraftingSystem* CraftingSystem, APlayerController* Controller);
private:
	void CreateCraftRecipeButtons();
	
private:
	void SetMakeActivate();

	UFUNCTION()
	void OnMakeButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();
};
