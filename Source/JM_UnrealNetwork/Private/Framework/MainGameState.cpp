// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainGameState.h"
#include "Net/UnrealNetwork.h"

AMainGameState::AMainGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		RemainingTime = MaxGameTime;
	}
}

void AMainGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (RemainingTime > 0.0f)
		{
			RemainingTime -= DeltaTime;

			if (RemainingTime <= 0.0f)
			{
				RemainingTime = 0.0f;
				UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
			}
		}
	}
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, RemainingTime);
}

int32 AMainGameState::GetRemainingTime() const
{
	return FMath::CeilToInt(RemainingTime);
}
