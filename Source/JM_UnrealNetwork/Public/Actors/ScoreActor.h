// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreActor.generated.h"

UCLASS()
class JM_UNREALNETWORK_API AScoreActor : public AActor
{
	GENERATED_BODY()
	
public:
    AScoreActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
    UPROPERTY(EditAnywhere, Category = "Score")
    int32 PointValue = 10;

    UPROPERTY(VisibleAnywhere)
    class USphereComponent* SphereComp;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MeshComp;

};
