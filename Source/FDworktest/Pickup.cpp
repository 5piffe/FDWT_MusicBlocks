#include "Pickup.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "FMODBlueprintStatics.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(true);
	RootComponent = PickupMesh;

	bIsHolding = false;
	bUseGravity = true;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerCamera = Player->FindComponentByClass<UCameraComponent>();

	TArray<USceneComponent*> Components;
	Player->GetComponents(Components);

	if (Components.Num() > 0)
	{
		for (auto& Comp : Components)
		{
			if (Comp->GetName() == "HandPos")
				HandComponent = Cast<USceneComponent>(Comp);
		}
	}

	if (Music3D)
		UFMODBlueprintStatics::PlayEventAttached(Music3D, RootComponent, "null", GetActorLocation(), EAttachLocation::KeepWorldPosition, true, true, false);
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::Pickup()
{

	bIsHolding = !bIsHolding;
	bUseGravity = !bUseGravity;
	PickupMesh->SetEnableGravity(bUseGravity);
	PickupMesh->SetSimulatePhysics(bIsHolding ? false : true);
	PickupMesh->SetCollisionEnabled(bIsHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);

	if (!bIsHolding)
	{
		FVector PlayerForward = PlayerCamera->GetForwardVector();
		PickupMesh->AddImpulse(PlayerForward * ThrowForce);
		UFMODBlueprintStatics::PlayEventAtLocation(GetWorld(), DropEvent, GetActorTransform(), true);
	}
	else
		UFMODBlueprintStatics::PlayEventAtLocation(GetWorld(), PickupEvent, GetActorTransform(), true);
}