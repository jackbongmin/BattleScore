// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ScoreActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Framework/MainPlayerState.h" 
#include "GameFramework/Character.h"

// Sets default values
AScoreActor::AScoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    RootComponent = SphereComp;
    SphereComp->SetSphereRadius(50.0f);
    SphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionProfileName(TEXT("NoCollision"));

}

void AScoreActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScoreActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (!HasAuthority())
    {
        return;
    }

    if (HasAuthority())
    {
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            AMainPlayerState* PS = Character->GetPlayerState<AMainPlayerState>();
            if (PS)
            {
                PS->AddScore(PointValue);

                Destroy();
            }
        }
    }
}
