// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericPlatform/GenericPlatformProcess.h"
#include "HttpModule.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Hiscore.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHiscoresReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHiscoreUploaded);

struct Hiscore
{
	FString name;
	int time;
};

/**
 * 
 */
UCLASS()
class SCREAMINGGOPHER_API UHiscore : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnHiscoresReady OnHiscoresReady;

	UPROPERTY(BlueprintAssignable)
	FOnHiscoreUploaded OnHiscoreUploaded;

	UFUNCTION(BlueprintCallable)
	void fetchHiscores();

	UFUNCTION(BlueprintCallable)
	TArray<FString> getHiscoreNames();
	
	UFUNCTION(BlueprintCallable)
	TArray<int> getHiscoreTimes();

	UFUNCTION(BlueprintCallable)
	void uploadHiscore(FString name, int time);

	void OnGetResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnPostResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	TArray<Hiscore> cachedScores;
};
