// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
//#include "Input/DefaultInputData.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mRotation = CreateDefaultSubobject<USceneComponent>(TEXT("Rotation"));
	mRotationMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationMovement"));

	mRotation->SetupAttachment(RootComponent);

	mRotationMovement->SetUpdatedComponent(mRotation); ///계속 업데이트해라
	mRotationMovement->RotationRate.Yaw = 180.0; ///초당 180정도로 돌려라

	mArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mArm);

	mArm->TargetArmLength = 400;
	mArm->SetRelativeLocation(FVector(0.0, 0.0, 70.0));
	mArm->SetRelativeRotation(FRotator(-10.0, 0.0, 0.0));
	
	/// 자식 객체에 넣어도 되는 부분 =>
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonBoris/Characters/Heroes/Boris/Meshes/Boris.Boris'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/ParagonBoris/ABP_Boris.ABP_Boris_C'"));
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	GetCapsuleComponent()->SetCapsuleHalfHeight(100);
	GetCapsuleComponent()->SetCapsuleRadius(50);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -102));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	bUseControllerRotationYaw = true;

	mArm->bInheritYaw = true; // 좌우 회전
	mArm->bInheritPitch = false; // 상하 회전
	mArm->bInheritRoll = false;

	GetCharacterMovement()->JumpZVelocity = 500;



	/// input 매핑
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		Context(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Player.IMC_Player'"));
	if (Context.Succeeded())
		mDefaultContext = Context.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));
	if (Move.Succeeded())
		mMove = Move.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Look(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Look.IA_Look'"));
	if (Look.Succeeded())
		mLook = Look.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Jump(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));
	if (Jump.Succeeded())
		mJump = Jump.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Grab(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Grab.IA_Grab'"));
	if (Grab.Succeeded())
		mGrab = Grab.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Dive(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Dive.IA_Dive'"));
	if (Dive.Succeeded())
		mDive = Dive.Object;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	mCameraRotation = mArm->GetRelativeRotation();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(mDefaultContext, 0);
		}
	}
	/*APlayerCharacter* PlayerController = GetController<APlayerController>();
	if (nullptr != PlayerController)
	{
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		/// LocalPlayer를 이용해서 EnhancedInputLocalPlayerSubsystem을 얻어온다.
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		/// UDefaultInputData의 CDO를 꺼내온다.
		const UDefaultInputData* InputData = GetDefault<UDefaultInputData>();

		Subsystem->AddMappingContext(InputData->mDefaultContext, 0);
	}*/
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(mMove, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMove);
		EnhancedInputComponent->BindAction(mLook, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMove);
		EnhancedInputComponent->BindAction(mJump, ETriggerEvent::Started, this, &APlayerCharacter::OnJump);
		EnhancedInputComponent->BindAction(mGrab, ETriggerEvent::Started, this, &APlayerCharacter::OnGrab);
		EnhancedInputComponent->BindAction(mDive, ETriggerEvent::Triggered, this, &APlayerCharacter::OnDive);
	}
	/*UEnhacedInputComponent* EnhancedInput = Cast<UEnhacedInputComponent>(PlayerInputComponent);
	const UDefaultInputData* InputData = GetDefault<UDefaultInputData>();

	EnhacnedInput->BindAction(InputData->mMove, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMove);*/

}

void APlayerCharacter::OnMove(const FInputActionValue& InputValue)
{
	const FVector ActionValue = InputValue.Get<FVector>();

	AddMovementInput(GetActorForwardVector(), ActionValue.Y);
	AddMovementInput(GetActorRightVector(), ActionValue.X);

	/*if (IsValid(mAnimInst))
		mAnimInst->ComputeMoveDir(ActionValue);*/

	//// 이동에 사용될 방향과 속도를 나타냄
	//const FVector2D MovementVector = InputValue.Get<FVector2D>();
	//// 플레이어의 현재 방향
	//const FRotator Rotation = Controller->GetControlRotation();
	//// Yaw만을 사용해 새로운 회전 생성
	//const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//// Yaw회전을 기준으로 전방 방향 계산
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//// 전방 방향과 Y값(전방 이동속도)을 사용하여 이동
	//AddMovementInput(ForwardDirection, MovementVector.Y);
	//// Yaw회전을 기준으로 우측 방향 계산
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//// 우측 방향과 X값(우측 이동속도)을 사용하여 이동
	//AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::OnLook(const FInputActionValue& InputValue)
{
	const FVector ActionValue = InputValue.Get<FVector>();

	float PitchDelta = 90 * GetWorld()->GetDeltaSeconds() * ActionValue.Y;
	float YawDelta = 90 * GetWorld()->GetDeltaSeconds() * ActionValue.X;

	mCameraRotation.Pitch += PitchDelta;
	mCameraRotation.Yaw += YawDelta; //좌/우 회전 한쪽으로만 돌아가는 용도

	//mCameraRotation.Yaw = mArm->GetRelativeRotation().Yaw; //좌/우 회전 끝까지 넘어갔을 때 한 번에 다른쪽 보는 용도

	/// 카메라 회전 각도 제어
	if (mCameraRotation.Yaw < -180)
	{
		/// Yaw = -180.9일 경우 => 180 - (180.9 - 180) = 179.1
		mCameraRotation.Yaw = 180.f - (mCameraRotation.Yaw * -1.f - 180.f);
	}
	else if (mCameraRotation.Yaw > 180)
	{
		/// Yaw = 180.9일 경우 => -180 + (180.9 - 180) = -179.1
		mCameraRotation.Yaw = -180.f + (mCameraRotation.Yaw - 180.f);
	}

	if (mCameraRotation.Pitch < -89.9f)
	{
		mCameraRotation.Pitch = -89.9f;
	}
	else if (mCameraRotation.Pitch > 89.9f)
	{
		mCameraRotation.Pitch = 89.9f;
	}

	mArm->SetRelativeRotation(mCameraRotation);

	//// 회전량
	//const FVector2D LookVector = InputValue.Get<FVector2D>();
	//// X값(수평 회전량)을 사용해 yaw회전 추가 > 수평 시선 회전
	//AddControllerYawInput(LookVector.X);
	//// Y값(수직 회전량)을 사용해 pitch회전 추가 > 수직 시선 회전
	//AddControllerPitchInput(LookVector.Y);
}

void APlayerCharacter::OnJump(const FInputActionValue& InputValue)
{
	if (CanJump())
	{
		Jump();

	}
}

void APlayerCharacter::OnGrab(const FInputActionValue& InputValue)
{

}

void APlayerCharacter::OnDive(const FInputActionValue& InputValue)
{

}

