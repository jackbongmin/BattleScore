// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LobbyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JM_UNREALNETWORK_API ULobbyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	ULobbyGameInstance();

	virtual void Init() override;

	void CreateServer();
	void JoinServer(FString IPAddress);
	void DisconnectServer();

	inline const FString& GetIPAddress() const { return ServerIP; }

private:
	UFUNCTION()
	void HandleNetworkFailure(UWorld* World, UNetDriver* NetDirever, ENetworkFailure::Type FailureType, const FString& ErrorString);

	UFUNCTION()
	void HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString);

protected:
	// 접속할 서버 IP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby")
	FString ServerIP;

	// 서버 생성시 로드할 맵
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby")
	TSoftObjectPtr<UWorld> ServerLevelAsset = nullptr;

	// 서버 생성시 로드할 맵
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby")
	TSoftObjectPtr<UWorld> MainLevelAsset = nullptr;

	// 최대 접속 가능한 플레이어 수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby")
	int32 MaxPlayers = 2;


};
