// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EndingWidget.h"
#include "Components/TextBlock.h"


void UEndingWidget::UpdateWinner(FString WinnerName)
{
	if (ResultText)
	{
		FString FinalStr = FString::Printf(TEXT("★%s★"), *WinnerName);
		ResultText->SetText(FText::FromString(FinalStr));
	}
}
