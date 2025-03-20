// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AMyPlayerController::AMyPlayerController()
{
	/*/// input ╦егн
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		Context(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Player.IMC_Player'"));
	if (Context.Succeeded())
		CharacterIMC = Context.Object;*/
}

void AMyPlayerController::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem && CharacterIMC)
		SubSystem->AddMappingContext(CharacterIMC, 0);
}
