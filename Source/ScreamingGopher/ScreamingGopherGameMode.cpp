// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScreamingGopherGameMode.h"
#include "ScreamingGopherCharacter.h"
#include "UObject/ConstructorHelpers.h"

AScreamingGopherGameMode::AScreamingGopherGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
