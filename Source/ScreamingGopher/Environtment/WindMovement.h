// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindMovement.generated.h"

UCLASS()
class SCREAMINGGOPHER_API AWindMovement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindMovement();

	UPROPERTY(EditAnywhere, Category = "Wind Direction")
		FVector WindDirection;

	UPROPERTY(EditAnywhere, Category = "Wind Power")
		float WindPower;

	UPROPERTY(EditAnywhere, Category = "Timer")
		float ChangingWindDelay = 2;

private:
	APawn* pPlayer;

	FTimerHandle ChangingWindTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DriftPlayer(float DeltaTime);

	void ChangeWindDirection();

};
