// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Framework/LobbyGameInstance.h"
#include "Kismet/GameplayStatics.h"


void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CreateButton)
	{
		CreateButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnCreateButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnJoinButtonClicked);
	}

	if (DisconnectButton)
	{
		DisconnectButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnDisconnectButtonClicked);
	}
}

void ULobbyWidget::OnCreateButtonClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
	RemoveFromParent(); 

	ULobbyGameInstance* GI = Cast<ULobbyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->CreateServer();
	}
}

void ULobbyWidget::OnJoinButtonClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
	RemoveFromParent(); 

	ULobbyGameInstance* GI = Cast<ULobbyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		FString IPAddress = GI->GetIPAddress();
		if (InputIPAddress)
		{
			FString InputIP = InputIPAddress->GetText().ToString();
			if (!InputIP.IsEmpty())
			{
				IPAddress = InputIP;
			}
		}

		GI->JoinServer(IPAddress);
	}
}

void ULobbyWidget::OnDisconnectButtonClicked()
{
	ULobbyGameInstance* GI = Cast<ULobbyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->DisconnectServer();
	}
}
