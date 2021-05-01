// Fill out your copyright notice in the Description page of Project Settings.


#include "CanoePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GamePlayStatic.h"

// Sets default values
ACanoePawn::ACanoePawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    PlayerCollision = CreateDefaultSubobject<UBoxComponent>("Box Collider");
    PlayerCollision->SetCollisionProfileName("BlockAll");
    PlayerCollision->SetSimulatePhysics(true);
    PlayerCollision->SetEnableGravity(false);
    SetRootComponent(PlayerCollision);

    CanoeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Canoe");
    CanoeMesh->SetCollisionProfileName("NoCollision");
    CanoeMesh->SetupAttachment(PlayerCollision);

    FirstRowRacer = CreateDefaultSubobject<USkeletalMeshComponent>("FirstRowRacer");
    FirstRowRacer->SetCollisionProfileName("NoCollision");
    FirstRowRacer->SetupAttachment(PlayerCollision);

    SecondRowRacer = CreateDefaultSubobject<USkeletalMeshComponent>("SecondRowRacer");
    SecondRowRacer->SetCollisionProfileName("NoCollision");
    SecondRowRacer->SetupAttachment(PlayerCollision);

    ThirdRowRacer = CreateDefaultSubobject<USkeletalMeshComponent>("ThirdRowRacer");
    ThirdRowRacer->SetCollisionProfileName("NoCollision");
    ThirdRowRacer->SetupAttachment(PlayerCollision);

    FourthRowRacer = CreateDefaultSubobject<USkeletalMeshComponent>("FourthRowRacer");
    FourthRowRacer->SetCollisionProfileName("NoCollision");
    FourthRowRacer->SetupAttachment(PlayerCollision);

    FifthRowRacer = CreateDefaultSubobject<USkeletalMeshComponent>("FifthRowRacer");
    FifthRowRacer->SetCollisionProfileName("NoCollision");
    FifthRowRacer->SetupAttachment(PlayerCollision);

    SixthRowRacer = CreateDefaultSubobject<USkeletalMeshComponent>("SixthRowRacer");
    SixthRowRacer->SetCollisionProfileName("NoCollision");
    SixthRowRacer->SetupAttachment(PlayerCollision);

    FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
    FollowCamera->SetupAttachment(PlayerCollision);

    PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

}

// Called when the game starts or when spawned
void ACanoePawn::BeginPlay()
{
    Super::BeginPlay();

    //GetPlayercontroller

}

// Called every frame
void ACanoePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //AngularFriction(DeltaTime);

}

// Called to bind functionality to input
void ACanoePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("StrongRight", EInputEvent::IE_Pressed, this, &ACanoePawn::RowStrongRight);
    PlayerInputComponent->BindAction("MediumRight", EInputEvent::IE_Pressed, this, &ACanoePawn::RowModerateRight);
    PlayerInputComponent->BindAction("LowRight", EInputEvent::IE_Pressed, this, &ACanoePawn::RowWeakRight);

    PlayerInputComponent->BindAction("StrongLeft", EInputEvent::IE_Pressed, this, &ACanoePawn::RowStrongLeft);
    PlayerInputComponent->BindAction("MediumLeft", EInputEvent::IE_Pressed, this, &ACanoePawn::RowModerateLeft);
    PlayerInputComponent->BindAction("LowLeft", EInputEvent::IE_Pressed, this, &ACanoePawn::RowWeakLeft);

}

void ACanoePawn::RowStrongRight()
{
    ApplyImpulseForRotation(-StrongRowAngularValue);

    MoveForward(StrongRowForwardValue);
}

void ACanoePawn::RowModerateRight()
{
    ApplyImpulseForRotation(-ModerateRowAngularValue);

    MoveForward(ModerateRowForwardValue);
}

void ACanoePawn::RowWeakRight()
{
    ApplyImpulseForRotation(-WeakRowAngularValue);

    MoveForward(WeakRowForwardValue);
}

void ACanoePawn::RowStrongLeft()
{
    ApplyImpulseForRotation(StrongRowAngularValue);

    MoveForward(StrongRowForwardValue);
}

void ACanoePawn::RowModerateLeft()
{
    ApplyImpulseForRotation(ModerateRowAngularValue);

    MoveForward(ModerateRowForwardValue);
}

void ACanoePawn::RowWeakLeft()
{
    ApplyImpulseForRotation(WeakRowAngularValue);

    MoveForward(WeakRowForwardValue);
}

void ACanoePawn::MoveForward(float Value)
{
    if (PawnMovement != nullptr)
    {
        //Get forward vector for the movement direction
        const FVector Direction = GetActorForwardVector();
        AddMovementInput(Direction, Value);
    }
}

void ACanoePawn::ApplyImpulseForRotation(float Value)
{
    FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

    PlayerCollision->AddAngularImpulseInDegrees(RowDirection * Value * RotationSpeed);
}

void ACanoePawn::AngularFriction(float DeltaTime)
{
    FVector CurrentAngularVelocity = PlayerCollision->GetPhysicsAngularVelocityInDegrees();

    if (CurrentAngularVelocity.Z != 0)
    {
        CurrentAngularVelocity.Z = CurrentAngularVelocity.Z > 0 ? CurrentAngularVelocity.Z - (DeltaTime * AngularFrictionRate) : CurrentAngularVelocity.Z + (DeltaTime * AngularFrictionRate);
        if (FMath::Abs(CurrentAngularVelocity.Z) < 1.0f)
        {
            CurrentAngularVelocity.Z = 0;
        }
    }

    PlayerCollision->SetPhysicsAngularVelocityInDegrees(CurrentAngularVelocity);
}

