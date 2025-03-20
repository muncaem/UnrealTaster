// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "PlayerCharacter.h"
#include "MyCharacter.h"

ADefaultGameMode::ADefaultGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}