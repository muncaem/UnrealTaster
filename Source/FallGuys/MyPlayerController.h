// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputMappingContext.h"
#include "EngineMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* CharacterIMC = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
