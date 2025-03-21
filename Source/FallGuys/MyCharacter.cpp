// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tool.h"
//UKismetMathLibrary Ŭ������ ���� ���� ���õ� �پ��� ������ �Լ����� ����.

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
			/*InventoryClass*/InventoryWidgetInst->SetVisibility(ESlateVisibility::Hidden); // ó������ ����

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

	// ���ƴٴϸ鼭 ��Ʈ ������Ʈ ������ ���� �� �ٲٱ�
	CheckForSweepHit();
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Data = Value.Get<FVector2D>();

	// ĳ������ ���� ȸ������ �����´�
	const FRotator Rotation = GetControlRotation();

	// ĳ������ Yaw ȸ������ �����ϰ� ������ Pitch�� Roll�� 0���� ������ ForwardRotation�� ����Ѵ�.
	// �̸� ���� ĳ���Ͱ� ���� �ٶ󺸴� ������ ȸ������ ��´�
	const FRotator ForwordRotation = FRotator(0, Rotation.Yaw, 0);

	// ���� ����, ���������� ���ϴ� ���͸� ��´�.
	const FVector ForwordVector = UKismetMathLibrary::GetForwardVector(ForwordRotation);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(ForwordRotation);

	// �������� Y��ŭ �̵�
	AddMovementInput(ForwordVector, Data.Y);

	// �¿�� X��ŭ �̵�
	AddMovementInput(RightVector, Data.X);



	// �޽� ȸ��
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
	QueryParams.AddIgnoredActor(this); // �ڱ� �ڽ� ����

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
	QueryParams.AddIgnoredActor(this); // �ڱ� �ڽ� ����

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

	// �浹 Ȯ�� ����� ���
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));

	// ���Ͽ� ���� ���� �����ϱ�
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
