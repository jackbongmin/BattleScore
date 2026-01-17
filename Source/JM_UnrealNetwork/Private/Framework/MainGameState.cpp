// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainGameState.h"
#include "Net/UnrealNetwork.h"
#include "UI/EndingWidget.h" 
#include "Framework/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/MainHUD.h"
#include "UI/MainHUDWidget.h"

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
		if (!bIsGameOver && RemainingTime > 0.0f)
		{
			RemainingTime -= DeltaTime;

			if (RemainingTime <= 0.0f)
			{
				RemainingTime = 0.0f;

				bIsGameOver = true;

				OnRep_GameOver();
			}
		}
	}
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, RemainingTime);
	DOREPLIFETIME(AMainGameState, bIsGameOver);
}

int32 AMainGameState::GetRemainingTime() const
{
	return FMath::CeilToInt(RemainingTime);
}

void AMainGameState::OnRep_GameOver()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		AMainHUD* MainHUD = Cast<AMainHUD>(PC->GetHUD());
		if (MainHUD)
		{
			UMainHUDWidget* Widget = MainHUD->GetMainHUDWidget();
			if (Widget)
			{
				int32 Score1P = -1;
				int32 Score2P = -1;

				for (APlayerState* PS : PlayerArray)
				{
					AMainPlayerState* MainPS = Cast<AMainPlayerState>(PS);
					if (MainPS)
					{
						if (MainPS->GetTeamIndex() == 0)
						{
							Score1P = MainPS->GetGameScore();
						}
						else if (MainPS->GetTeamIndex() == 1)
						{
							Score2P = MainPS->GetGameScore();
						}
					}
				}

				FString WinnerText = TEXT("Draw");

				if (Score1P > Score2P)
				{
					WinnerText = TEXT("Winer : 1P");
				}
				else if (Score2P > Score1P)
				{
					WinnerText = TEXT("Winer : 2P");
				}

				Widget->ShowGameOver(WinnerText);
			}
		}
	}
}
