// Fill out your copyright notice in the Description page of Project Settings.


#include "CanoePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ACanoePawn::ACanoePawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    PlayerCollision = CreateDefaultSubobject<UBoxComponent>("Box Collider");
    PlayerCollision->SetCollisionProfileName("BlockAll");
    PlayerCollision->SetSimulatePhysics(true);
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

    FVector CurrentAngularVelocity = PlayerCollision->GetPhysicsAngularVelocityInDegrees();

    if (CurrentAngularVelocity.Z != 0)
    {
        CurrentAngularVelocity.Z = CurrentAngularVelocity.Z > 0 ? CurrentAngularVelocity.Z - (DeltaTime * 5) : CurrentAngularVelocity.Z + (DeltaTime * 5);
        if (FMath::Abs(CurrentAngularVelocity.Z) < 1.0f)
        {
            CurrentAngularVelocity.Z = 0;
        }
    }

    PlayerCollision->SetPhysicsAngularVelocityInDegrees(CurrentAngularVelocity);
}

// Called to bind functionality to input
void ACanoePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("StrongRight", EInputEvent::IE_Pressed, this, &ACanoePawn::RowStrongRight);
    PlayerInputComponent->BindAction("MediumRight", EInputEvent::IE_Pressed, this, &ACanoePawn::RowMediumRight);
    PlayerInputComponent->BindAction("LowRight", EInputEvent::IE_Pressed, this, &ACanoePawn::RowWeakRight);

    PlayerInputComponent->BindAction("StrongLeft", EInputEvent::IE_Pressed, this, &ACanoePawn::RowStrongLeft);
    PlayerInputComponent->BindAction("MediumLeft", EInputEvent::IE_Pressed, this, &ACanoePawn::RowMediumLeft);
    PlayerInputComponent->BindAction("LowLeft", EInputEvent::IE_Pressed, this, &ACanoePawn::RowWeakLeft);

}

void ACanoePawn::RowStrongRight()
{
    FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), -GetActorRightVector());

    PlayerCollision->AddAngularImpulseInDegrees(RowDirection * 1.0f * 3000000);
    //AddControllerYawInput(1.0f * 100000);

    if ((Controller != nullptr))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        //const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        const FVector Direction = GetActorRightVector();
        AddMovementInput(Direction, 1.0f);
    }

}

void ACanoePawn::RowMediumRight()
{
    FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), -GetActorRightVector());

    PlayerCollision->AddAngularImpulseInDegrees(RowDirection * 0.5f * 3000000);

    if ((Controller != nullptr) && (0.5f != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = GetActorRightVector();
        AddMovementInput(Direction, 0.5f);
    }

}

void ACanoePawn::RowWeakRight()
{
    FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), -GetActorRightVector());

    PlayerCollision->AddAngularImpulseInDegrees(RowDirection * 0.3f * 3000000);
    AddControllerYawInput(1.0f * 1500);

    if ((Controller != nullptr))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        //const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        const FVector Direction = GetActorRightVector();
        AddMovementInput(Direction, 0.3f);
    }

}

void ACanoePawn::RowStrongLeft()
{
    FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

    PlayerCollision->AddAngularImpulseInDegrees(RowDirection * 1.0f * 3000000);
    //AddControllerYawInput(-1.0f * 100000);
    if ((Controller != nullptr))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        //const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        const FVector Direction = GetActorRightVector();
        AddMovementInput(Direction, 1.0f);
    }
}

void ACanoePawn::RowMediumLeft()
{
    FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

    PlayerCollision->AddAngularImpulseInDegrees(RowDirection * 0.5f * 3000000);

    if ((Controller != nullptr))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        //const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        const FVector Direction = GetActorRightVector();
        AddMovementInput(Direction, 0.5f);
    }
}

void ACanoePawn::RowWeakLeft()
{
    FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

    PlayerCollision->AddAngularImpulseInDegrees(RowDirection * 0.3f * 3000000);

    if ((Controller != nullptr) && (0.3f != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        //const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        const FVector Direction = GetActorRightVector();
        AddMovementInput(Direction, 0.3f);
    }
}

//void ACanoePawn::RowRight(float RowPower)
//{
//	FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(),-GetActorRightVector());
//
//	PlayerCollision->AddAngularImpulseInDegrees(RowDirection * RowPower * 150000);
//	
//	if ((Controller != nullptr) && (RowPower != 0.0f))
//	{
//		// find out which way is forward
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		// get forward vector
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//		AddMovementInput(Direction, RowPower);
//	}
//
//}
//
//void ACanoePawn::RowLeft(float RowPower)
//{
//	FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());
//
//	PlayerCollision->AddAngularImpulseInDegrees(RowDirection * RowPower * 150000);
//	
//	if ((Controller != nullptr) && (RowPower != 0.0f))
//	{
//		// find out which way is forward
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		// get forward vector
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//		AddMovementInput(Direction, RowPower);
//	}
//
//	//PlayerCollision->AddImpulse(GetActorRightVector() * RowPower * 500);
//}

