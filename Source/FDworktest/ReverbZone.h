// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FMODEvent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReverbZone.generated.h"

UCLASS()
class FDWORKTEST_API AReverbZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReverbZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
