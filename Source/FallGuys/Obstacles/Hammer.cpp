// Fill out your copyright notice in the Description page of Project Settings.


#include "Hammer.h"

// Sets default values
AHammer::AHammer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mRotationMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));

	SetRootComponent(mMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Fab/Fantasy_Hammer/fantasy_hammer.fantasy_hammer'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

	mMesh->SetRelativeRotation(FRotator(180, 0, 180));
	mMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
}

// Called when the game starts or when spawned
void AHammer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mRotationMovement->RotationRate.Pitch = 75.0;
}

