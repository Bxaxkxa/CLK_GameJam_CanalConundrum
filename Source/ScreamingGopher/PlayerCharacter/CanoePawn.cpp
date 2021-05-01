// Fill out your copyright notice in the Description page of Project Settings.


#include "CanoePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

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

}

// Called to bind functionality to input
void ACanoePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("RowRight", this, &ACanoePawn::RowRight);
	PlayerInputComponent->BindAxis("RowLeft", this, &ACanoePawn::RowLeft);

}

void ACanoePawn::RowRight(float RowPower)
{
	FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(),-GetActorRightVector());

	PlayerCollision->AddAngularImpulseInDegrees(RowDirection * RowPower * 150000);
	PlayerCollision->AddImpulse(GetActorRightVector() * RowPower * 500);
}

void ACanoePawn::RowLeft(float RowPower)
{
	FVector RowDirection = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

	PlayerCollision->AddAngularImpulseInDegrees(RowDirection * RowPower * 150000);
	PlayerCollision->AddImpulse(GetActorRightVector() * RowPower * 500);
}

