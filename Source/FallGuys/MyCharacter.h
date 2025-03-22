// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InventoryWidget.h"
#include "InputActionValue.h"
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class FALLGUYS_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* GrabAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InvenAction;

	// 클래스 설정용
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	// 실제 UI 인스턴스 담을 곳
	UPROPERTY()
	UUserWidget* InventoryClass;

	UPROPERTY()
	UInventoryWidget* InventoryWidgetInst;

private:
	float MeshRotationDegree = 0;
	float SearchDistance = 500;
	bool isGrab = false;
	bool isOpenUI = false;

	TObjectPtr<AActor> ToolInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void CheckForSweepHit();
	void OnJump(const FInputActionValue& Value);
	void Grab(const FInputActionValue& Value);
	void Inven(const FInputActionValue& Value);
};
