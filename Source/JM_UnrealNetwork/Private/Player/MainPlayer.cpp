// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Framework/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"	

AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetShowMouseCursor(false);

		FInputModeGameOnly GameInputMode;
		PC->SetInputMode(GameInputMode);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMainPlayer::SetTeamColor, 0.1f, false);


}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMainPlayer::InputSprintPressed);

			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMainPlayer::InputSprintReleased);
		}
	}
}

void AMainPlayer::InputSprintPressed(const FInputActionValue& Value)
{
	SetRunState(true);
	if (!HasAuthority())
	{
		Server_StartRun();
	}
}

void AMainPlayer::InputSprintReleased(const FInputActionValue& Value)
{
	SetRunState(false);
	if (!HasAuthority())
	{
		Server_StopRun();
	}
}

void AMainPlayer::SetRunState(bool bIsRunning)
{
	if (bIsRunning)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AMainPlayer::SetTeamColor()
{
	AMainPlayerState* PS = GetPlayerState<AMainPlayerState>();

	if (PS && PS->GetTeamIndex() != -1)
	{
		PS->OnRep_TeamIndex();

		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	}
}

void AMainPlayer::Server_StopRun_Implementation()
{
	SetRunState(false);
}

void AMainPlayer::Server_StartRun_Implementation()
{
	SetRunState(true);
}

