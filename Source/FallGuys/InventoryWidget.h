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

protected:
	UPROPERTY(VisibleAnywhere)
	int32 ItemValue = 0;

	UPROPERTY(VisibleAnywhere)
	int32 MaxItem = 15;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TArray<UImage*> ImageWidgets;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Item3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item11;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item13;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item14;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
	UImage* Item15;

	// 바인딩된 개별 항목을 배열로 관리할 변수
	TArray<UImage*> ItemWidget;
	
public:
	virtual void NativeConstruct() override;
};
