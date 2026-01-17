// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MainPlayer.generated.h"

class UInputAction;

UCLASS()
class JM_UNREALNETWORK_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SprintAction;

	void InputSprintPressed(const FInputActionValue& Value);
	void InputSprintReleased(const FInputActionValue& Value);

	void SetRunState(bool bIsRunning);

	UFUNCTION(Server, Reliable)
	void Server_StartRun();

	UFUNCTION(Server, Reliable)
	void Server_StopRun();

	float WalkSpeed = 300.0f;
	float RunSpeed = 800.0f;

	UFUNCTION(BlueprintCallable)
	void SetTeamColor();

protected:
	FTimerHandle TimerHandle;

};
