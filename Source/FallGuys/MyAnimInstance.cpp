// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(TryGetPawnOwner());
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Owner)
	{
		Owner = Cast<ACharacter>(TryGetPawnOwner());
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Owner is still NULL!"));
	}
	else
	{
		Speed = Owner->GetCharacterMovement()->Velocity.Size2D();
		/*GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Speed: %.2f"), Speed));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Owner: %s"), *Owner->GetName()));*/
	}
}
