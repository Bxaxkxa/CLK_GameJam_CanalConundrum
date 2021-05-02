// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalLine.h"
#include "../Hiscore.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerCharacter/CanoePawn.h"


// Sets default values
AGoalLine::AGoalLine()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    GoalCollision = CreateDefaultSubobject<UBoxComponent>("GoalCollider");
    GoalCollision->SetCollisionProfileName("OverlapAll");
    GoalCollision->SetGenerateOverlapEvents(true);
    GoalCollision->OnComponentBeginOverlap.AddDynamic(this, &AGoalLine::OverlapBegin);
    SetRootComponent(GoalCollision);

}

// Called when the game starts or when spawned
void AGoalLine::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AGoalLine::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AGoalLine::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    APawn* Player = Cast<APawn>(OtherActor);
    if (Player)
    {
        ACanoePawn* CanoePlayer = Cast<ACanoePawn>(Player);
        if (CanoePlayer)
        {
            CanoePlayer->bGameStarted = false;

            int MinuteToSecond = CanoePlayer->Minute * 60;
            int HourToSecond = CanoePlayer->Hour * 360;

            int EndScore = MinuteToSecond + HourToSecond + CanoePlayer->Second;

            UHiscore* GameInstance = Cast<UHiscore>(GetGameInstance());
            if (GameInstance)
            {
                GameInstance->uploadHiscore("Bob", EndScore);
                GameInstance->OnHiscoreUploaded.Broadcast();
            }
        }
    }
}

