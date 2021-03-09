// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FDworktestHUD.generated.h"

UCLASS()
class AFDworktestHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFDworktestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

