// Fill out your copyright notice in the Description page of Project Settings.


#include "CanoePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

const float STAGGER_ANIM_TIME = 2.0f;
const float PADDLE_ANIM_TIME = 2.0f;

// Sets default values
ACanoePawn::ACanoePawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    PlayerCollision = CreateDefaultSubobject<UBoxComponent>("Box Collider");
    PlayerCollision->SetCollisionProfileName("BlockAll");
    PlayerCollision->SetSimulatePhysics(true);
    PlayerCollision->OnComponentHit.AddDynamic(this, &ACanoePawn::OnHit);
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

}

// Called every frame
void ACanoePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateAnimations(DeltaTime);
    AngularFriction(DeltaTime);

    if (bGameStarted)
    {
        HandleTimer(DeltaTime);
    }

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
    if (bGameStarted && !bStaggered && !bSecondRowAnimation)
    {
        bSecondRowAnimation = true;

        ApplyImpulseForRotation(StrongRowAngularValue);

        MoveForward(StrongRowForwardValue);
    }
}

void ACanoePawn::RowModerateRight()
{
    if (bGameStarted && !bStaggered && !bFourthRowAnimation)
    {
        bFourthRowAnimation = true;

        ApplyImpulseForRotation(ModerateRowAngularValue);

        MoveForward(ModerateRowForwardValue);
    }
}

void ACanoePawn::RowWeakRight()
{
    if (bGameStarted && !bStaggered && !bSixthRowAnimation)
    {
        bSixthRowAnimation = true;

        ApplyImpulseForRotation(WeakRowAngularValue);

        MoveForward(WeakRowForwardValue);
    }
}

void ACanoePawn::RowStrongLeft()
{
    if (bGameStarted && !bStaggered && !bFirstRowAnimation)
    {
        bFirstRowAnimation = true;

        ApplyImpulseForRotation(-StrongRowAngularValue);

        MoveForward(StrongRowForwardValue);
    }
}

void ACanoePawn::RowModerateLeft()
{
    if (bGameStarted && !bStaggered && !bThirdRowAnimation)
    {
        bThirdRowAnimation = true;

        ApplyImpulseForRotation(-ModerateRowAngularValue);

        MoveForward(ModerateRowForwardValue);
    }
}

void ACanoePawn::RowWeakLeft()
{
    if (bGameStarted && !bStaggered && !bFifthRowAnimation)
    {
        bFifthRowAnimation = true;

        ApplyImpulseForRotation(-WeakRowAngularValue);

        MoveForward(WeakRowForwardValue);
    }
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

    //AngularFriction
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

void ACanoePawn::UpdateAnimations(float DeltaTime)
{
    if (bFirstRowAnimation) {
        fFirstRowAnimTime += DeltaTime;
        if (fFirstRowAnimTime >= PADDLE_ANIM_TIME)
        {
            fFirstRowAnimTime = 0;
            bFirstRowAnimation = false;
        }
    }

    if (bSecondRowAnimation) {
        fSecondRowAnimTime += DeltaTime;
        if (fSecondRowAnimTime >= PADDLE_ANIM_TIME)
        {
            fSecondRowAnimTime = 0;
            bSecondRowAnimation = false;
        }
    }

    if (bThirdRowAnimation) {
        fThirdRowAnimTime += DeltaTime;
        if (fThirdRowAnimTime >= PADDLE_ANIM_TIME)
        {
            fThirdRowAnimTime = 0;
            bThirdRowAnimation = false;
        }
    }

    if (bFourthRowAnimation) {
        fFourthRowAnimTime += DeltaTime;
        if (fFourthRowAnimTime >= PADDLE_ANIM_TIME)
        {
            fFourthRowAnimTime = 0;
            bFourthRowAnimation = false;
        }
    }

    if (bFifthRowAnimation) {
        fFifthRowAnimTime += DeltaTime;
        if (fFifthRowAnimTime >= PADDLE_ANIM_TIME)
        {
            fFifthRowAnimTime = 0;
            bFifthRowAnimation = false;
        }
    }

    if (bSixthRowAnimation) {
        fSixthRowAnimTime += DeltaTime;
        if (fSixthRowAnimTime >= PADDLE_ANIM_TIME)
        {
            fSixthRowAnimTime = 0;
            bSixthRowAnimation = false;
        }
    }

    if (bStaggered) {
        fStaggeredAnimTime += DeltaTime;
        if (fStaggeredAnimTime >= STAGGER_ANIM_TIME)
        {
            fStaggeredAnimTime = 0;
            bStaggered = false;
        }
    }
}

void ACanoePawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    FVector PlayerVelocity = GetMovementComponent()->Velocity;

    if (PlayerVelocity.X > 250 || PlayerVelocity.Y > 250)
    {
        bStaggered = true;
    }
}

void ACanoePawn::HandleTimer(float DeltaTime)
{
    //MiliSecond += DeltaTime;
    ////MiliSecond += 1;

    //if (MiliSecond >= 60)
    //{
    //    AddSecond();
    //}

    Second += DeltaTime;
    if (Second >= 60)
    {
        AddMinute();
    }
}

void ACanoePawn::AddSecond()
{
    /*MiliSecond = 0;
    Second++;
    if (Second >= 60)
    {
        AddMinute();
    }*/
}

void ACanoePawn::AddMinute()
{
    Second = 0;
    Minute++;
    if (Minute >= 60)
    {
        AddHour();
    }
}

void ACanoePawn::AddHour()
{
    Minute = 0;
    Hour++;
}

