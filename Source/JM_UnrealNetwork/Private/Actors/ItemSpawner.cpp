// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;

	SpawnArea->SetBoxExtent(FVector(1000.0f, 1000.0f, 100.0f));
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AItemSpawner::SpawnScoreItem, SpawnInterval, true);
	}
}

void AItemSpawner::SpawnScoreItem()
{
	if (SpawnActorClass)
	{
		FVector Origin = SpawnArea->GetComponentLocation();
		FVector Extent = SpawnArea->GetScaledBoxExtent();

		FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

		FRotator SpawnRotation = FRotator::ZeroRotator;

		GetWorld()->SpawnActor<AActor>(SpawnActorClass, RandomLocation, SpawnRotation);
	}
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

