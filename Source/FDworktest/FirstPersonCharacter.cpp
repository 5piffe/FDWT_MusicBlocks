#include "FirstPersonCharacter.h"
#include "FMODBlueprintStatics.h"
#include "DrawDebugHelpers.h"

AFirstPersonCharacter::AFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(RootComponent);

	HandPos = CreateDefaultSubobject<USceneComponent>(TEXT("HandPos"));

	CurrentItem = NULL;
}

void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	HandPos->SetRelativeLocation(FVector(HeldItemForwardOffset, HeldItemRightOffset, HeldItemHeight));
}

void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MovementWalk);
	InputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MovementStrafe);
	InputComponent->BindAxis("LookUp", this, &AFirstPersonCharacter::MouseLook);
	InputComponent->BindAxis("Turn", this, &AFirstPersonCharacter::MouseTurn);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPersonCharacter::OnJump);
	InputComponent->BindAction("Use", IE_Pressed, this, &AFirstPersonCharacter::PickupItem);
}

void AFirstPersonCharacter::MovementWalk(float InputValue)
{
	if (InputValue)
	AddMovementInput(GetActorForwardVector(), InputValue);
}

void AFirstPersonCharacter::MovementStrafe(float InputValue)
{
	if (InputValue)
		AddMovementInput(GetActorRightVector(), InputValue);
}

void AFirstPersonCharacter::MouseLook(float InputValue)
{
	if (InputValue)
	{
		InputValue = bInvertLook ? InputValue : -InputValue;
		float CurrentPitch = Camera->GetRelativeRotation().Pitch + InputValue;

		if (CurrentPitch < MaxLookUp && CurrentPitch > -MaxLookDown)
			Camera->AddLocalRotation(FRotator(InputValue * Sensitivity, 0, 0));
	}
}

void AFirstPersonCharacter::MouseTurn(float InputValue)
{
	if (bHoldingItem)
		CurrentItem->SetActorLocationAndRotation(HandPos->GetComponentLocation(), HandPos->GetComponentRotation());
	
	if (InputValue)
		AddActorLocalRotation(FRotator(0.f, InputValue * Sensitivity, 0.f));
}

void AFirstPersonCharacter::OnJump()
{
	ACharacter::Jump();
	
	if (!bIsJumping)
	{
		FFMODEventInstance InstanceWrapper = UFMODBlueprintStatics::PlayEventAtLocation(this, JumpEvent, GetActorTransform(), true);
		bIsJumping = true;
	}
}


void AFirstPersonCharacter::PickupItem()
{
	 FVector TraceStart = Camera->GetComponentLocation();
	 FVector TraceEnd = ((Camera->GetForwardVector() * PickItemRange) + TraceStart);
	 FHitResult TraceHit;

	if (!bHoldingItem)
	{
		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility,
		FComponentQueryParams::DefaultComponentQueryParams, FCollisionResponseParams::DefaultResponseParam))
			CurrentItem = Cast<APickup>(TraceHit.GetActor());
		
		else
			CurrentItem = NULL;
	}

	if (CurrentItem)
	{
		bHoldingItem = !bHoldingItem;
		CurrentItem->Pickup();

		if (!bHoldingItem)
			CurrentItem = NULL;
	}
}