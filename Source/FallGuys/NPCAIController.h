// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
