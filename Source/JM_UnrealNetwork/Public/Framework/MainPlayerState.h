// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class JM_UNREALNETWORK_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMainPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetTeamIndex(int32 NewTeamIndex);

	void AddScore(int32 Amount);

public:
	int32 GetGameScore() const { return GameScore; }

	int32 GetTeamIndex() const { return TeamIndex; }

protected:
	UPROPERTY(ReplicatedUsing = OnRep_TeamIndex)
	int32 TeamIndex;

	UPROPERTY(ReplicatedUsing = OnRep_GameScore)
	int32 GameScore = 0;

public:
	UFUNCTION()
	void OnRep_TeamIndex();

	UFUNCTION()
	void OnRep_GameScore();

};
