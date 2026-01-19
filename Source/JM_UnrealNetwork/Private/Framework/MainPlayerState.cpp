// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainPlayerState.h"
#include "Net/UnrealNetwork.h"            
#include "GameFramework/Character.h"       
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/MainHUD.h"
#include "UI/MainHUDWidget.h"

AMainPlayerState::AMainPlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
	TeamIndex = -1;
	GameScore = 0;

	NetUpdateFrequency = 100.0f;
}


void AMainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerState, TeamIndex);
	DOREPLIFETIME(AMainPlayerState, GameScore);

}

void AMainPlayerState::SetTeamIndex(int32 NewTeamIndex)
{
	if (HasAuthority())
	{
		TeamIndex = NewTeamIndex;
		OnRep_TeamIndex();
	}
}

void AMainPlayerState::AddScore(int32 Amount)
{
	if (HasAuthority())
	{
		GameScore += Amount;

		OnRep_GameScore();

		ForceNetUpdate();

		UE_LOG(LogTemp, Warning, TEXT("Player %d Score Updated: %d"), TeamIndex, GameScore);
	}
}

void AMainPlayerState::OnRep_TeamIndex()
{
	ACharacter* MyCharacter = GetPawn<ACharacter>();

	if (MyCharacter)
	{
		USkeletalMeshComponent* CharacterMesh = MyCharacter->GetMesh();

		if (CharacterMesh)
		{
			if (TeamIndex == 1)
			{
				UMaterialInterface* Material_01 = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/M/MI_Quinn_03.MI_Quinn_03"));
				UMaterialInterface* Material_02 = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/M/MI_Quinn_04.MI_Quinn_04"));

				if (Material_01)
				{
					CharacterMesh->SetMaterial(0, Material_01);
				}

				if (Material_02)
				{
					CharacterMesh->SetMaterial(1, Material_02);
				}
			}
		}
	}
}

void AMainPlayerState::OnRep_GameScore()
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
				Widget->UpdateScore(TeamIndex, GameScore);
			}
		}
	}
}
