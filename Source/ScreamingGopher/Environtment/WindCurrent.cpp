// Fill out your copyright notice in the Description page of Project Settings.


#include "WindCurrent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TimerManager.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

// Sets default values
AWindMovement::AWindMovement()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWindMovement::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AWindMovement::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (pPlayer)
    {
        DriftPlayer(DeltaTime);
    }

}

void AWindMovement::DriftPlayer(float DeltaTime)
{
    if (pPlayer)
    {
        UPrimitiveComponent* PhysicsSimulatedComponent = Cast<UPrimitiveComponent>(pPlayer->GetRootComponent());
        if (PhysicsSimulatedComponent)
        {
            PhysicsSimulatedComponent->AddForce(WindDirection * WindPower);
        }
    }
}

void AWindMovement::ChangeWindDirection()
{
    //Change the WindDirection on X and Y axis
    WindDirection.X = float((rand() % 200) - 100) / 100.0f;
    WindDirection.Y = float((rand() % 200) - 100) / 100.0f;

    ChangingWindDelay = float((rand() % 50) + 50) / 10.0f;

    //Set new timer with a new delay time
    GetWorldTimerManager().SetTimer(ChangingWindTimer, this, &AWindMovement::ChangeWindDirection, ChangingWindDelay, false);
}

void AWindMovement::StartBlowing()
{
    WindDirection = FVector(-1, 0, 0);

    pPlayer = UGameplayStatics::GetPlayerPawn(Cast<UObject>(GetWorld()), 0);

    GetWorldTimerManager().SetTimer(ChangingWindTimer, this, &AWindMovement::ChangeWindDirection, ChangingWindDelay, false);
}

