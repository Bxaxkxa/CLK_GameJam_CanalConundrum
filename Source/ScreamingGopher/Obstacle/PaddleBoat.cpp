// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddleBoat.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
APaddleBoat::APaddleBoat()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    BoatCollision = CreateDefaultSubobject<UBoxComponent>("BoatCollider");
    BoatCollision->SetCollisionProfileName("BlockAll");
    SetRootComponent(BoatCollision);

    Boat = CreateDefaultSubobject<UStaticMeshComponent>("Boat");
    Boat->SetCollisionProfileName("NoCollision");
    Boat->SetupAttachment(BoatCollision);

    Paddler = CreateDefaultSubobject<USkeletalMeshComponent>("Paddler");
    Paddler->SetCollisionProfileName("NoCollision");
    Paddler->SetupAttachment(BoatCollision);
}

// Called when the game starts or when spawned
void APaddleBoat::BeginPlay()
{
    Super::BeginPlay();

    if (FirstTarget)
    {
        CurrentTarget = FirstTarget;
    }
}

// Called every frame
void APaddleBoat::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

