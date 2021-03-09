// Copyright Epic Games, Inc. All Rights Reserved.

#include "FDworktestGameMode.h"
#include "FDworktestHUD.h"
#include "FDworktestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFDworktestGameMode::AFDworktestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFDworktestHUD::StaticClass();
}
