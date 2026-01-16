// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainPlayerState.h"
#include "Net/UnrealNetwork.h"            
#include "GameFramework/Character.h"       
#include "Components/SkeletalMeshComponent.h"

AMainPlayerState::AMainPlayerState()
{
	TeamIndex = -1;
}

void AMainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerState, TeamIndex);
}

void AMainPlayerState::SetTeamIndex(int32 NewTeamIndex)
{
	if (HasAuthority())
	{
		TeamIndex = NewTeamIndex;
		OnRep_TeamIndex();
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
