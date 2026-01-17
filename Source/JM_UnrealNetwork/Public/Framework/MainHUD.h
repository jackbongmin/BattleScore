// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class JM_UNREALNETWORK_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	inline class UMainHUDWidget* GetMainHUDWidget() const { return MainHUDWidget; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUDWidget> MainHUDWidgetClass;

private:
	UPROPERTY()
	class UMainHUDWidget* MainHUDWidget;

};
