#include "ReverbZone.h"
#include "FMODBlueprintStatics.h"


AReverbZone::AReverbZone()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AReverbZone::BeginPlay()
{
	Super::BeginPlay();

	
}

void AReverbZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}