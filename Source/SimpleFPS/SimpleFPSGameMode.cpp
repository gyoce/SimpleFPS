// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleFPSGameMode.h"
#include "SimpleFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASimpleFPSGameMode::ASimpleFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
