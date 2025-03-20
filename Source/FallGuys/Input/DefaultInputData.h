// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputMappingContext.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DefaultInputData.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API UDefaultInputData : public UObject
{
	GENERATED_BODY()

public:
	UDefaultInputData();
	
public:
	UInputMappingContext* mDefaultContext = nullptr;

public:
	UInputAction* mMove = nullptr;
	UInputAction* mJump = nullptr;
	UInputAction* mGrab = nullptr;
	UInputAction* mDive = nullptr;
};
