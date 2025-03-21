// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tool.h"
//UKismetMathLibrary 클래스는 수학 계산과 관련된 다양한 유용한 함수들을 제공.

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400;
	SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (InventoryWidgetClass)
	{
		InventoryClass = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass/*UInventoryWidget::StaticClass()*/);
		InventoryWidgetInst = Cast<UInventoryWidget>(InventoryClass);

		if (/*InventoryClass*/InventoryWidgetInst)
		{
			/*InventoryClass*/InventoryWidgetInst->AddToViewport();
			/*InventoryClass*/InventoryWidgetInst->SetVisibility(ESlateVisibility::Hidden); // 처음에는 숨김

			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("InvenClass: %s"), *InventoryClass->GetName()));
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("InvenClass Failed")));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("WidgetClass Failed")));
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		UIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		UIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::OnJump);
		UIC->BindAction(GrabAction, ETriggerEvent::Started, this, &AMyCharacter::Grab);
		UIC->BindAction(InvenAction, ETriggerEvent::Started, this, &AMyCharacter::Inven);
	}
}


void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Data = Value.Get<FVector2D>();

	AddControllerYawInput(Data.Y);
	AddControllerPitchInput(Data.X);

	// 돌아다니면서 히트 오브젝트 있으면 액터 색 바꾸기
	CheckForSweepHit();
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Data = Value.Get<FVector2D>();

	// 캐릭터의 현재 회전값을 가져온다
	const FRotator Rotation = GetControlRotation();

	// 캐릭터의 Yaw 회전값을 유지하고 나머지 Pitch와 Roll을 0으로 설정한 ForwardRotation을 계산한다.
	// 이를 통해 캐릭터가 현재 바라보는 방향의 회전값을 얻는다
	const FRotator ForwordRotation = FRotator(0, Rotation.Yaw, 0);

	// 각각 전방, 오른쪽으로 향하는 벡터를 얻는다.
	const FVector ForwordVector = UKismetMathLibrary::GetForwardVector(ForwordRotation);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(ForwordRotation);

	// 전방으로 Y만큼 이동
	AddMovementInput(ForwordVector, Data.Y);

	// 좌우로 X만큼 이동
	AddMovementInput(RightVector, Data.X);



	// 메시 회전
	MeshRotationDegree = FMath::RadiansToDegrees(FMath::Atan2(-Data.Y, Data.X));
	FRotator CharacterRotation(0, GetMesh()->GetRelativeRotation().Yaw, 0);
	FRotator MeshRotation = FMath::RInterpTo(CharacterRotation, FRotator(0, MeshRotationDegree, 0), GetWorld()->GetDeltaSeconds(), 10);
	GetMesh()->SetRelativeRotation(MeshRotation);
}

void AMyCharacter::CheckForSweepHit()
{
	const FVector Start = GetActorLocation();
	const FVector End = Start + GetActorForwardVector() * SearchDistance;
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 10);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(50.f);
	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 제외

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere,
		QueryParams
	);

	if (HasHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));
		
		ATool* Tool = Cast<ATool>(HitResult.GetActor());
		if (!Tool) return;
		Tool->ApplyOverlay();
	}
}

void AMyCharacter::OnJump(const FInputActionValue& Value)
{
	if (CanJump())
	{
		Jump();
	}
}

void AMyCharacter::Grab(const FInputActionValue& Value)
{
	if (isGrab)
	{
		ToolInstance->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		ATool* Tool = Cast<ATool>(ToolInstance);
		if (!Tool) return;
		Tool->EquipGrabInit();
		ToolInstance == nullptr;
		isGrab = false;
		return;
	}
	const FVector Start = GetActorLocation();
	const FVector End = Start + GetActorForwardVector() * SearchDistance;
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 10);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(50.f);
	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 제외

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere,
		QueryParams
	);

	if (!HasHit) return;

	// 충돌 확인 디버그 출력
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));

	// 소켓에 액터 장착 구현하기
	HitResult.GetComponent()->SetMobility(EComponentMobility::Movable);

	ATool* Tool = Cast<ATool>(HitResult.GetActor());
	if (!Tool) return;
	Tool->EquipInitialize();

	FName Socket(TEXT("hand_rSocket"));
	HitResult.GetActor()->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		Socket
	);

	ToolInstance = HitResult.GetActor();
	isGrab = true;

	/*UInventoryWidget* Widget = Cast<UInventoryWidget>(InventoryWidgetClass);*/
	if (nullptr != Tool->GetTexture())
		InventoryWidgetInst->SetWidgetImage(Tool->GetTexture());

	//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 10);
}

void AMyCharacter::Inven(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("InvenClass: %s"), *InventoryClass->GetName()));
	
	if (/*InventoryClass*/InventoryWidgetInst)
	{
		/*InventoryClass*/InventoryWidgetInst->SetVisibility(
			/*InventoryClass*/InventoryWidgetInst->IsVisible() ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
}
