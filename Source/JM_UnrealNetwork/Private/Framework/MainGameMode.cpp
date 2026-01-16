// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AMainGameMode::AMainGameMode()
{
}

AActor* AMainGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);


	FName TargetTag = (LoginCount == 0) ? FName("Spawn1") : FName("Spawn2");

	for (AActor* Actor : FoundActors)
	{
		if (Actor->ActorHasTag(TargetTag))
		{
			LoginCount++;

			UE_LOG(LogTemp, Warning, TEXT("Found Spawn Point: %s for Player %d"), *TargetTag.ToString(), LoginCount);
			return Actor;
		}
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}
