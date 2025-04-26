// Fill out your copyright notice in the Description page of Project Settings.

#include "CraftingTable.h"
#include "EventHub.h"

// [ ACraftingTable(게임 월드 담당) ]
// 씬에 배치되는 제작대
// 플레이어가 접근하면 UI 열기

void ACraftingTable::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	if (APawn* Pawn = Cast<APawn>(OtherActor))
	{
		if (Pawn->IsPlayerControlled())
		{
			UEventHub::Get()->OnActionHitCraftTable.Broadcast();
		}
	}
}

// Called when the game starts or when spawned
void ACraftingTable::BeginPlay()
{
	Super::BeginPlay();


}

// Sets default values
ACraftingTable::ACraftingTable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ACraftingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

