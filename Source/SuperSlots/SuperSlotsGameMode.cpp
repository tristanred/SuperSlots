// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SuperSlotsGameMode.h"
#include "SuperSlotsHUD.h"
#include "SuperSlotsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASuperSlotsGameMode::ASuperSlotsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASuperSlotsHUD::StaticClass();
}
