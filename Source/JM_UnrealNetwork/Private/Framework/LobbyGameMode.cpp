// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/LobbyGameMode.h"

ALobbyGameMode::ALobbyGameMode()
{
	DefaultPawnClass = NULL;

	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 CurrentPlayerCount = GetNumPlayers();
	UE_LOG(LogTemp, Warning, TEXT("Lobby: Player Joined. Current: %d / %d"), CurrentPlayerCount, MaxPlayers);

	if (CurrentPlayerCount >= MaxPlayers)
	{
		if (!GameLevelAsset.IsNull())
		{
			FString MapPath = GameLevelAsset.GetLongPackageName();

			FString TravelURL = FString::Printf(TEXT("%s?listen"), *MapPath);

			UE_LOG(LogTemp, Warning, TEXT("Moving to Game Level: %s"), *TravelURL);

			GetWorld()->ServerTravel(TravelURL);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GameLevelAsset이 설정되지 않았습니다! 블루프린트를 확인하세요."));
		}
	}
}
