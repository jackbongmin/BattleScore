// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class JM_UNREALNETWORK_API AMainGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMainGameState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	int32 GetRemainingTime() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameRule")
	float MaxGameTime = 60.0f;

	UPROPERTY(Replicated)
	float RemainingTime;

public:
	UPROPERTY(ReplicatedUsing = OnRep_GameOver)
	bool bIsGameOver = false;

	UFUNCTION()
	void OnRep_GameOver();


};
