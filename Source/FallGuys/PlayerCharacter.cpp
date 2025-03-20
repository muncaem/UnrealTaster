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

	mRotationMovement->SetUpdatedComponent(mRotation); ///��� ������Ʈ�ض�
	mRotationMovement->RotationRate.Yaw = 180.0; ///�ʴ� 180������ ������

	mArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mArm);

	mArm->TargetArmLength = 400;
	mArm->SetRelativeLocation(FVector(0.0, 0.0, 70.0));
	mArm->SetRelativeRotation(FRotator(-10.0, 0.0, 0.0));
	
	/// �ڽ� ��ü�� �־ �Ǵ� �κ� =>
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

	mArm->bInheritYaw = true; // �¿� ȸ��
	mArm->bInheritPitch = false; // ���� ȸ��
	mArm->bInheritRoll = false;

	GetCharacterMovement()->JumpZVelocity = 500;



	/// input ����
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

		/// LocalPlayer�� �̿��ؼ� EnhancedInputLocalPlayerSubsystem�� ���´�.
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		/// UDefaultInputData�� CDO�� �����´�.
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

	//// �̵��� ���� ����� �ӵ��� ��Ÿ��
	//const FVector2D MovementVector = InputValue.Get<FVector2D>();
	//// �÷��̾��� ���� ����
	//const FRotator Rotation = Controller->GetControlRotation();
	//// Yaw���� ����� ���ο� ȸ�� ����
	//const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//// Yawȸ���� �������� ���� ���� ���
	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//// ���� ����� Y��(���� �̵��ӵ�)�� ����Ͽ� �̵�
	//AddMovementInput(ForwardDirection, MovementVector.Y);
	//// Yawȸ���� �������� ���� ���� ���
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//// ���� ����� X��(���� �̵��ӵ�)�� ����Ͽ� �̵�
	//AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::OnLook(const FInputActionValue& InputValue)
{
	const FVector ActionValue = InputValue.Get<FVector>();

	float PitchDelta = 90 * GetWorld()->GetDeltaSeconds() * ActionValue.Y;
	float YawDelta = 90 * GetWorld()->GetDeltaSeconds() * ActionValue.X;

	mCameraRotation.Pitch += PitchDelta;
	mCameraRotation.Yaw += YawDelta; //��/�� ȸ�� �������θ� ���ư��� �뵵

	//mCameraRotation.Yaw = mArm->GetRelativeRotation().Yaw; //��/�� ȸ�� ������ �Ѿ�� �� �� ���� �ٸ��� ���� �뵵

	/// ī�޶� ȸ�� ���� ����
	if (mCameraRotation.Yaw < -180)
	{
		/// Yaw = -180.9�� ��� => 180 - (180.9 - 180) = 179.1
		mCameraRotation.Yaw = 180.f - (mCameraRotation.Yaw * -1.f - 180.f);
	}
	else if (mCameraRotation.Yaw > 180)
	{
		/// Yaw = 180.9�� ��� => -180 + (180.9 - 180) = -179.1
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

	//// ȸ����
	//const FVector2D LookVector = InputValue.Get<FVector2D>();
	//// X��(���� ȸ����)�� ����� yawȸ�� �߰� > ���� �ü� ȸ��
	//AddControllerYawInput(LookVector.X);
	//// Y��(���� ȸ����)�� ����� pitchȸ�� �߰� > ���� �ü� ȸ��
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

