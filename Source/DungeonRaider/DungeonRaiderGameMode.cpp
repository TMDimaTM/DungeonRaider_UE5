// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonRaiderGameMode.h"
#include "DungeonRaiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeonRaiderGameMode::ADungeonRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
