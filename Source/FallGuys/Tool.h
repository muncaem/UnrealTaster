// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Tool.generated.h"

UCLASS()
class FALLGUYS_API ATool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATool();
	void EquipInitialize();
	void EquipGrabInit();
	void ApplyOverlay();
	void ResetOverlay();
	UTexture2D* GetTexture();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UBoxComponent> Collider;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterialInterface> OverlayMaterial;

	UPROPERTY(EditAnywhere)
	UTexture2D* ToolTexture;


private:
	FName DefaultCollisionPreset;
	FTimerHandle OverlayTimerHandle;
	bool isGrab = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void PostInitializeComponents() override;

protected:

};
