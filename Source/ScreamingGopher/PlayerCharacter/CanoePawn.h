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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Component")
		class UBoxComponent* PlayerCollision;

#pragma region Mesh Component

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Canoe")
		class UStaticMeshComponent* CanoeMesh;

	//Six Racer Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racers")
		class USkeletalMeshComponent* FirstRowRacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racers")
		class USkeletalMeshComponent* SecondRowRacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racers")
		class USkeletalMeshComponent* ThirdRowRacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racers")
		class USkeletalMeshComponent* FourthRowRacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racers")
		class USkeletalMeshComponent* FifthRowRacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Racers")
		class USkeletalMeshComponent* SixthRowRacer;

#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
		class UFloatingPawnMovement* PawnMovement;

#pragma region Customable Variable

	UPROPERTY(EditAnywhere, Category = "Paddle Power")
		float StrongRowAngularValue;

	UPROPERTY(EditAnywhere, Category = "Paddle Power")
		float ModerateRowAngularValue;

	UPROPERTY(EditAnywhere, Category = "Paddle Power")
		float WeakRowAngularValue;

	UPROPERTY(EditAnywhere, Category = "Paddle Power")
		float StrongRowForwardValue;

	UPROPERTY(EditAnywhere, Category = "Paddle Power")
		float ModerateRowForwardValue;

	UPROPERTY(EditAnywhere, Category = "Paddle Power")
		float WeakRowForwardValue;

	UPROPERTY(EditAnywhere, Category = "Canoe Movement")
		float RotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Canoe Movement")
		float AngularFrictionRate;

#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skin")
		TArray<UMaterialInterface*> CanoeSkins;

	UPROPERTY(BlueprintReadWrite, Category = "Skin")
		int SkinIndex = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bGameStarted;

#pragma region Animation State

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bFirstRowAnimation = false;
	float fFirstRowAnimTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bSecondRowAnimation = false;
	float fSecondRowAnimTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bThirdRowAnimation = false;
	float fThirdRowAnimTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bFourthRowAnimation = false;
	float fFourthRowAnimTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bFifthRowAnimation = false;
	float fFifthRowAnimTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bSixthRowAnimation = false;
	float fSixthRowAnimTime = 0;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bStaggered = false;
	float fStaggeredAnimTime = 0;

#pragma endregion

#pragma region Timer
	UPROPERTY(BlueprintReadOnly)
		float MiliSecond = 0;
	UPROPERTY(BlueprintReadOnly)
		float Second = 0;
	UPROPERTY(BlueprintReadOnly)
		int Minute = 0;
	UPROPERTY(BlueprintReadOnly)
		int Hour = 0;
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Movement Input

	void RowStrongRight();
	void RowModerateRight();
	void RowWeakRight();

	void RowStrongLeft();
	void RowModerateLeft();
	void RowWeakLeft();

	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
		void ApplyImpulseForRotation(float Value);

#pragma endregion

	void AngularFriction(float DeltaTime);
	void UpdateAnimations(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void HandleTimer(float DeltaTime);

	void AddSecond();
	void AddMinute();
	void AddHour();
};

