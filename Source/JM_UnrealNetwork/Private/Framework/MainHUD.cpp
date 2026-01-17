// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainHUD.h"
#include "UI/MainHUDWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainHUDWidgetClass)
	{
		MainHUDWidget = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDWidgetClass);

		if (MainHUDWidget)
		{
			MainHUDWidget->AddToViewport();
		}
	}
}

