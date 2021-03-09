#include "MusicBox.h"
#include "FMODBlueprintStatics.h"

AMusicBox::AMusicBox()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMusicBox::BeginPlay()
{
	Super::BeginPlay();
}

void AMusicBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlaying)
		return;
	
	if (bAllBlocksFound)
		Start2DMusic();
}

void AMusicBox::Start2DMusic()
{
	bPlaying = true;
	UFMODBlueprintStatics::PlayEvent2D(GetWorld(), Music2D, true);
}