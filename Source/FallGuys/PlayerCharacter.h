// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FALLGUYS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> mArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> mCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> mRotation;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent> mRotationMovement;


	FRotator mCameraRotation = FRotator::ZeroRotator;

private:
	UInputMappingContext* mDefaultContext = nullptr;
	UInputAction* mMove = nullptr;
	UInputAction* mLook = nullptr;
	UInputAction* mJump = nullptr;
	UInputAction* mGrab = nullptr;
	UInputAction* mDive = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	void OnMove(const FInputActionValue& InputValue);
	void OnLook(const FInputActionValue& InputValue);
	void OnJump(const FInputActionValue& InputValue);
	void OnGrab(const FInputActionValue& InputValue);
	void OnDive(const FInputActionValue& InputValue);
};
