// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaddleBoat.generated.h"

UCLASS()
class SCREAMINGGOPHER_API APaddleBoat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaddleBoat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Component")
		class UBoxComponent* BoatCollision;

	UPROPERTY(EditAnywhere, Category = "Boat")
		class UStaticMeshComponent* Boat;

	UPROPERTY(EditAnywhere, Category = "Boat")
		class USkeletalMeshComponent* Paddler;

	UPROPERTY(EditAnywhere, Category = "DestinationPoint")
		class ATargetPoint* FirstTarget;

	UPROPERTY(EditAnywhere, Category = "DestinationPoint")
		class ATargetPoint* SecondTarget;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed;

	ATargetPoint* CurrentTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveToTarget();
	void ChangeTarget();
};
