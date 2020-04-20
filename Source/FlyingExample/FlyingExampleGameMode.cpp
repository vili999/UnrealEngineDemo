// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FlyingExampleGameMode.h"
#include "FlyingExamplePawn.h"

AFlyingExampleGameMode::AFlyingExampleGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AFlyingExamplePawn::StaticClass();
}
