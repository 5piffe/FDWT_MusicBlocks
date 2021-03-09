#pragma once

#include "FMODEvent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Pickup.generated.h"

UCLASS()
class FDWORKTEST_API APickup : public AActor
{
	GENERATED_BODY()
	
public:
	APickup();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float ThrowForce = 100000.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HandComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMOD")
	UFMODEvent* Music3D;

	UPROPERTY(EditAnywhere, Category = "FMOD")
	UFMODEvent* PickupEvent;

	UPROPERTY(EditAnywhere, Category = "FMOD")
	UFMODEvent* DropEvent;

	ACharacter* Player;
	UCameraComponent* PlayerCamera;

	bool bIsHolding;
	bool bUseGravity;

	void Pickup();
};
