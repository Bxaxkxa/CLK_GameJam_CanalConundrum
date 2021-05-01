// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScreamingGopherGameMode.h"
#include "UObject/ConstructorHelpers.h"

AScreamingGopherGameMode::AScreamingGopherGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/UnrealContent/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
