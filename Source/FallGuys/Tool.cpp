#include "Tool.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"


// Sets default values
ATool::ATool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	OverlayMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MT_ToolsOutline_Inst.MT_ToolsOutline_Inst'"));
}

// Called when the game starts or when spawned
void ATool::BeginPlay()
{
	Super::BeginPlay();
	OnDroppedActivities();
}

void ATool::EquipInitialize()
{
	Collider->SetMobility(EComponentMobility::Movable);
	Collider->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetRelativeLocation(FVector(0, 0, 0));

	isGrab = true;
	ResetOverlay();
	OnEquippedActivities();
}

void ATool::EquipGrabInit()
{
	//UE_LOG(LogTemp, Warning, TEXT("Applying Collision Profile: %s"), *DefaultCollisionPreset.ToString());

	Collider->SetCollisionProfileName(TEXT("Tools"));
	Collider->SetBoxExtent(FVector(44.5f, 64.5f, 14.7f));
	Mesh->SetRelativeLocation(FVector(-20, 0, 0));

	isGrab = false;
	OnDroppedActivities();
}

void ATool::ApplyOverlay()
{
	if (isGrab) return;

	Mesh->SetOverlayMaterial(OverlayMaterial);

	// 1초 후 원래 머터리얼로 되돌리기
	GetWorld()->GetTimerManager().SetTimer(
		OverlayTimerHandle,
		this,
		&ATool::ResetOverlay,
		1.0f,
		false
	);
}

void ATool::ResetOverlay()
{
	if (!Mesh) return;

	Mesh->SetOverlayMaterial(nullptr);
}

UTexture2D* ATool::GetTexture()
{
	return ToolTexture;
}

USpotLightComponent*  ATool::ToggleFlashlight()
{
	USpotLightComponent* Flashlight = FindComponentByClass<USpotLightComponent>();
	if (Flashlight)
		return Flashlight;
	else return nullptr;
}

void ATool::OnEquippedActivities()
{
	if (USpotLightComponent * Flashlight = ToggleFlashlight())
		Flashlight->SetVisibility(true);
}

void ATool::OnDroppedActivities()
{
	if (USpotLightComponent* Flashlight = ToggleFlashlight())
		Flashlight->SetVisibility(false);
}

