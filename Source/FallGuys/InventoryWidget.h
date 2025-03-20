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
	virtual void NativeConstruct() override;
};
