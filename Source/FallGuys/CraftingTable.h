// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CraftingSystem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CraftingTable.generated.h"

UCLASS()
class FALLGUYS_API ACraftingTable : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UCraftingSystem* CraftingSystem; // CraftingSystem내부에서 생성

	// 플레이어가 상호작용하면 호출
	void OpenCraftUI();
	// 실제 제작 실행
	bool TryCraft();


public:	
	// Sets default values for this actor's properties
	ACraftingTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
