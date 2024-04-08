// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuminusGameGameMode.h"
#include "LuminusGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALuminusGameGameMode::ALuminusGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
