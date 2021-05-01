// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CanoePawn.generated.h"

UCLASS()
class SCREAMINGGOPHER_API ACanoePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACanoePawn();

	UPROPERTY(EditAnywhere, Category = "Collision Component")
		class UBoxComponent* PlayerCollision;

#pragma region Mesh Component

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Canoe")
		class UStaticMeshComponent* CanoeMesh;

	//Six Racer Mesh
	UPROPERTY(EditAnywhere, Category = "Racers")
		class USkeletalMeshComponent* FirstRowRacer;

	UPROPERTY(EditAnywhere, Category = "Racers")
		class USkeletalMeshComponent* SecondRowRacer;

	UPROPERTY(EditAnywhere, Category = "Racers")
		class USkeletalMeshComponent* ThirdRowRacer;

	UPROPERTY(EditAnywhere, Category = "Racers")
		class USkeletalMeshComponent* FourthRowRacer;

	UPROPERTY(EditAnywhere, Category = "Racers")
		class USkeletalMeshComponent* FifthRowRacer;

	UPROPERTY(EditAnywhere, Category = "Racers")
		class USkeletalMeshComponent* SixthRowRacer;

#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraComponent* FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RowRight(float RowPower);

	void RowLeft(float RowPower);

};
