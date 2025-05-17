// Copyright Epic Games, Inc. All Rights Reserved.

#include "EternalStrikerGameMode.h"
#include "EternalStrikerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEternalStrikerGameMode::AEternalStrikerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
