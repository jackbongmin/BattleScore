// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class JM_UNREALNETWORK_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby Setting")
	TSoftObjectPtr<UWorld> GameLevelAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lobby Setting")
	int32 MaxPlayers = 2;

};
