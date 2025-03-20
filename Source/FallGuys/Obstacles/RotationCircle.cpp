// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationCircle.h"

// Sets default values
ARotationCircle::ARotationCircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mRotationMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));

	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Meshes/Shape_Cylinder.Shape_Cylinder'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

	mMesh->SetRelativeScale3D(FVector(8, 8, 1));
}

// Called when the game starts or when spawned
void ARotationCircle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotationCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mRotationMovement->RotationRate.Yaw = RotRate;
}

