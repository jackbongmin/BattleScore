// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUDWidget.h"
#include "Components/TextBlock.h"
#include "Framework/MainPlayerState.h" 
#include "Framework/MainGameState.h" 
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "UI/EndingWidget.h"


void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	AMainGameState* GS = Cast<AMainGameState>(UGameplayStatics::GetGameState(GetWorld()));

	if (GS && TimerText)
	{
		int32 Time = GS->GetRemainingTime();
		TimerText->SetText(FText::AsNumber(Time));
	}
}

void UMainHUDWidget::UpdateScore(int32 PlayerIndex, int32 NewScore)
{
	if (PlayerIndex == 0 && Score1PText)
	{
		Score1PText->SetText(FText::AsNumber(NewScore));
	}
	else if (PlayerIndex == 1 && Score2PText)
	{
		Score2PText->SetText(FText::AsNumber(NewScore));
	}
}

void UMainHUDWidget::ShowGameOver(FString WinnerName)
{
	if (EndingScreen)
	{
		EndingScreen->SetVisibility(ESlateVisibility::Visible);

		EndingScreen->UpdateWinner(WinnerName);
	}
}
