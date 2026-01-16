// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class JM_UNREALNETWORK_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainGameMode();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	int32 LoginCount = 0;

};
