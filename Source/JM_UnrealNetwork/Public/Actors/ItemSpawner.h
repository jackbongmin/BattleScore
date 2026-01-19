// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class JM_UNREALNETWORK_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnScoreItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	TSubclassOf<class AActor> SpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float SpawnInterval = 3.0f;

	FTimerHandle SpawnTimerHandle;


};
