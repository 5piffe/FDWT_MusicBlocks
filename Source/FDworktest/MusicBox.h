#pragma once

#include "FMODEvent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicBox.generated.h"

UCLASS()
class FDWORKTEST_API AMusicBox : public AActor
{
	GENERATED_BODY()
	
public:
	AMusicBox();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAllBlocksFound = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMOD")
	UFMODEvent* Music2D;

	UFUNCTION(BlueprintCallable, Category = "FMOD")
	void Start2DMusic();

	bool bPlaying = false;
};
