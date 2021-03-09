#pragma once

#include "FMODEvent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Pickup.h"
#include "FirstPersonCharacter.generated.h"

UCLASS()
class FDWORKTEST_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* HandPos;

public:
	AFirstPersonCharacter();

	class APickup* CurrentItem;

	bool bCanMove;
	bool bHoldingItem;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Pick item")
	float PickItemRange = 350.0f;

	UPROPERTY(EditAnywhere, Category = "Pick item")
	float HeldItemForwardOffset = 120.0f;

	UPROPERTY(EditAnywhere, Category = "Pick item")
	float HeldItemHeight = -20.0f;

	UPROPERTY(EditAnywhere, Category = "Pick item")
	float HeldItemRightOffset = -20.0f;

	void PickupItem();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsJumping = false;

	UPROPERTY(EditAnywhere)
	float MaxLookUp;

	UPROPERTY(EditAnywhere)
	float MaxLookDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMOD", meta = (ClampMin = "0", ClampMax = "1"))
	float AmbienceLoPass;

	UPROPERTY(EditAnywhere, Category = "FMOD")
	UFMODEvent* JumpEvent;

private:
	UPROPERTY(EditAnywhere, Category = "MouseSettings")
	float Sensitivity = 1.0f;

	UPROPERTY(EditAnywhere, Category = "MouseSettings")
	bool bInvertLook = false;

	void MovementWalk(float InputValue);
	void MovementStrafe(float InputValue);
	void MouseLook(float InputValue);
	void MouseTurn(float InputValue);
	void OnJump();

	void TeleportSkill();
	
};
