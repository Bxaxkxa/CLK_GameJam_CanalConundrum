// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerCharacter/CanoePawn.h"

void ATimeGameState::Tick(float DeltaTime)
{
    MiliSecond++;

    if (MiliSecond >= 60)
    {
        AddSecond();
    }
}

void ATimeGameState::AddSecond()
{
    MiliSecond = 0;
    Second++;
    if (MiliSecond >= 60)
    {
        AddSecond();
    }
}

void ATimeGameState::AddMinute()
{
    Second = 0;
    Minute++;
    if (Second >= 60)
    {
        AddHour();
    }
}

void ATimeGameState::AddHour()
{
    Minute = 0;
    Hour++;
}

void ATimeGameState::BeginPlay()
{
    ACanoePawn* Player = Cast<ACanoePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (Player->bGameStarted)
    {
        bGameStarted = Player->bGameStarted;
    }
}

