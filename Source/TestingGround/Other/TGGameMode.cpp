// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TGGameMode.h"
#include "Character/MannequinHUD.h"
#include "Character/Mannequin.h"
#include "UObject/ConstructorHelpers.h"

ATGGameMode::ATGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/NPC/TP_Character/BP_TP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
    HUDClass = AMannequinHUD::StaticClass();
}
