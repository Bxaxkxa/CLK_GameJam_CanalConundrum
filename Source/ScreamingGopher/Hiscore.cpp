// Fill out your copyright notice in the Description page of Project Settings.

#include "Hiscore.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Interfaces/IHttpResponse.h"

void UHiscore::fetchHiscores()
{
	if (cachedScores.Num() > 0) {
		return;
	}

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL("https://clkjam.uc.r.appspot.com/hiscores");
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHiscore::OnGetResponseReceived);
	HttpRequest->ProcessRequest();
}

void UHiscore::uploadHiscore(FString name, int time)
{
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("name", name);
	JsonWriter->WriteValue("time", time);
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "multipart/form-data");
	HttpRequest->SetURL("https://clkjam.uc.r.appspot.com/hiscores");
	HttpRequest->SetContentAsString(JsonString);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHiscore::OnPostResponseReceived);
	HttpRequest->ProcessRequest();
}

void UHiscore::OnGetResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response->GetContentType() == "application/json")
	{
		cachedScores.Empty();
		
		TArray<TSharedPtr<FJsonValue>> JsonArr;

		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());

		FJsonSerializer::Deserialize(JsonReader, JsonArr);

		for (auto csr : JsonArr) {
			const TSharedPtr<FJsonObject> score = csr.Get()->AsObject();
			Hiscore hScore;

			hScore.name = score->GetStringField("name");
			hScore.time = score->GetIntegerField("time");

			cachedScores.Add(hScore);
		}
	}

	OnHiscoresReady.Broadcast();
}

void UHiscore::OnPostResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// TODO something useful
	}
	else 
	{
		// TODO something useful
	}

	OnHiscoreUploaded.Broadcast();

}

TArray<FString> UHiscore::getHiscoreNames()
{
	auto arr = TArray<FString>();

	for (auto& csr : cachedScores) {
		arr.Add(csr.name);
	}

	return arr;
}

TArray<int> UHiscore::getHiscoreTimes()
{
	auto arr = TArray<int>();

	for (auto& csr : cachedScores) {
		arr.Add(csr.time);
	}

	return arr;
}
