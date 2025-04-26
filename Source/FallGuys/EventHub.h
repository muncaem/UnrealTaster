// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventHub.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API UEventHub : public UObject
{
	GENERATED_BODY()

public:
	static UEventHub* Get();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionHitCraftTable);

public:
	UPROPERTY(BlueprintAssignable)
	FOnActionHitCraftTable OnActionHitCraftTable;
};
