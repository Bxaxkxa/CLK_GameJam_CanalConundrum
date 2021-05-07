// Fill out your copyright notice in the Description page of Project Settings.

#include "Hiscore.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Interfaces/IHttpResponse.h"
#include "picosha2.h"

void UHiscore::fetchHiscores()
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL("https://clkjam.uc.r.appspot.com/hiscores");
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHiscore::OnGetResponseReceived);
	HttpRequest->ProcessRequest();
}

void UHiscore::uploadHiscore(FString name, int time)
{
	FString hashInputF = name + "," + FString::FromInt(time) + ",this_is_a_magic_string5828177577217725";
	std::string hashInputStr = TCHAR_TO_UTF8(&hashInputF);
	std::string hash_hex_str;
	picosha2::hash256_hex_string(hashInputStr, hash_hex_str);
	FString hash_hex_fstr = FString::FromBlob((const uint8*)hash_hex_str.c_str(), hash_hex_str.size());

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("name"), *FString::Printf(TEXT("%s"), *name));
	JsonObject->SetNumberField(TEXT("time"), time);
	JsonObject->SetStringField(TEXT("magic"), *FString::Printf(TEXT("%s"), *hash_hex_fstr));
	FString JsonString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/json");
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
