// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TimeGameState.generated.h"

/**
 *
 */
UCLASS()
class SCREAMINGGOPHER_API ATimeGameState : public AGameStateBase
{
    GENERATED_BODY()

private:
    bool bGameStarted;

public:
    UPROPERTY(BlueprintReadOnly)
        int MiliSecond = 0;
    UPROPERTY(BlueprintReadOnly)
        int Second = 0;
    UPROPERTY(BlueprintReadOnly)
        int Minute = 0;
    UPROPERTY(BlueprintReadOnly)
        int Hour = 0;

    virtual void Tick(float DeltaTime) override;

    void AddSecond();
    void AddMinute();
    void AddHour();

protected:
    virtual void BeginPlay() override;
};
