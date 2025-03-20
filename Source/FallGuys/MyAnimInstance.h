// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYS_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class ACharacter> Owner;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
