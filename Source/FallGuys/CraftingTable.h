// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CraftWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CraftingTable.generated.h"

UCLASS()
class FALLGUYS_API ACraftingTable : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

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
