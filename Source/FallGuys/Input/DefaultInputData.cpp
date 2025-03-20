// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultInputData.h"

UDefaultInputData::UDefaultInputData()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		Context(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Player.IMC_Player'"));
	if (Context.Succeeded())
		mDefaultContext = Context.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));
	if (Move.Succeeded())
		mMove = Move.Object;

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
