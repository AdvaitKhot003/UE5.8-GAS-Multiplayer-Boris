// No Copyright.

#include "Player/BorisPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/BorisInputData.h"
#include "Input/BorisInputComponent.h"
#include "GameFramework/Character.h"
#include "BorisGameplayTags.h"

ABorisPlayerController::ABorisPlayerController()
{
	bReplicates = true;
}

void ABorisPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalController()) return;
	
	check(BorisInputData);
	
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem);
	for (const UInputMappingContext* Context : BorisInputData->InputMappingContexts)
	{
		if (!Context) continue;
		Subsystem->AddMappingContext(Context, 0);
	}
}

void ABorisPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	check(BorisInputData);
	UBorisInputComponent* BorisInputComponent = CastChecked<UBorisInputComponent>(InputComponent);
	
	BorisInputComponent->BindNativeInputAction(BorisInputData, BorisGameplayTags::Input_Move,
		ETriggerEvent::Triggered, this, &ThisClass::Move);
	
	BorisInputComponent->BindNativeInputAction(BorisInputData, BorisGameplayTags::Input_Look,
		ETriggerEvent::Triggered, this, &ThisClass::Look);
	
	BorisInputComponent->BindNativeInputAction(BorisInputData, BorisGameplayTags::Input_Jump,
		ETriggerEvent::Started, this, &ThisClass::Jump);
	
	BorisInputComponent->BindNativeInputAction(BorisInputData, BorisGameplayTags::Input_Jump,
		ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	
	BorisInputComponent->BindAbilityInputAction(BorisInputData, this,
		&ThisClass::AbilityInputPressed, &ThisClass::AbilityInputHeld, &ThisClass::AbilityInputReleased);
}

void ABorisPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	APawn* ControlledPawn = GetPawn<APawn>();
	if (!IsValid(ControlledPawn)) return;
	
	if (!FMath::IsNearlyZero(InputAxisValue.X))
	{
		const FVector RightDirection = YawRotation.RotateVector(FVector::RightVector);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}
	
	if (!FMath::IsNearlyZero(InputAxisValue.Y))
	{
		const FVector ForwardDirection = YawRotation.RotateVector(FVector::ForwardVector);
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
	}
}

void ABorisPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	
	if (!FMath::IsNearlyZero(InputAxisValue.X))
	{
		AddYawInput(InputAxisValue.X);
	}
	
	if (!FMath::IsNearlyZero(InputAxisValue.Y))
	{
		AddPitchInput(InputAxisValue.Y);
	}
}

void ABorisPlayerController::Jump()
{
	ACharacter* BorisCharacter = GetCharacter();
	if (!IsValid(BorisCharacter)) return;
	
	BorisCharacter->Jump();
}

void ABorisPlayerController::StopJumping()
{
	ACharacter* BorisCharacter = GetCharacter();
	if (!IsValid(BorisCharacter)) return;
	
	BorisCharacter->StopJumping();
}

void ABorisPlayerController::AbilityInputPressed(FGameplayTag InInputTag)
{
	if (InInputTag.MatchesTagExact(BorisGameplayTags::Input_Ability_Primary))
	{
		UE_LOG(LogTemp, Log, TEXT("Ability Input Pressed: Primary"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
			TEXT("Ability Input Pressed: Primary"));
	}

	if (InInputTag.MatchesTagExact(BorisGameplayTags::Input_Ability_Secondary))
	{
		UE_LOG(LogTemp, Log, TEXT("Ability Input Pressed: Secondary"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
			TEXT("Ability Input Pressed: Secondary"));
	}
}

void ABorisPlayerController::AbilityInputHeld(FGameplayTag InInputTag)
{
	if (InInputTag.MatchesTagExact(BorisGameplayTags::Input_Ability_Primary))
	{
		UE_LOG(LogTemp, Log, TEXT("Ability Input Held: Primary"));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow,
			TEXT("Ability Input Held: Primary"));
	}

	if (InInputTag.MatchesTagExact(BorisGameplayTags::Input_Ability_Secondary))
	{
		UE_LOG(LogTemp, Log, TEXT("Ability Input Held: Secondary"));
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow,
			TEXT("Ability Input Held: Secondary"));
	}
}

void ABorisPlayerController::AbilityInputReleased(FGameplayTag InInputTag)
{
	if (InInputTag.MatchesTagExact(BorisGameplayTags::Input_Ability_Primary))
	{
		UE_LOG(LogTemp, Log, TEXT("Ability Input Released: Primary"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			TEXT("Ability Input Released: Primary"));
	}

	if (InInputTag.MatchesTagExact(BorisGameplayTags::Input_Ability_Secondary))
	{
		UE_LOG(LogTemp, Log, TEXT("Ability Input Released: Secondary"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			TEXT("Ability Input Released: Secondary"));
	}
}
