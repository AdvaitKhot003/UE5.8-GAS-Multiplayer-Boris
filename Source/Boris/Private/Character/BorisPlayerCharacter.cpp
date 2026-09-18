// No Copyright.

#include "Character/BorisPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BorisPlayerState.h"
#include "AbilitySystemComponent.h"

ABorisPlayerCharacter::ABorisPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoomComp");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 15.0f;
	CameraBoom->CameraLagMaxDistance = 50.0f;
	CameraBoom->CameraLagMaxTimeStep = 1.0f / 60.0f;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 15.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCameraComp");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
}

void ABorisPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	/** Server **/
	InitAbilityPlayerInfo();
}

void ABorisPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	/** Clinet **/
	InitAbilityPlayerInfo();
}

ABorisPlayerState* ABorisPlayerCharacter::GetBorisPlayerState() const
{
	return GetPlayerState<ABorisPlayerState>();
}

UAbilitySystemComponent* ABorisPlayerCharacter::GetAbilitySystemComponent() const
{
	const ABorisPlayerState* BorisPlayerState = GetBorisPlayerState();
	check(BorisPlayerState);
	
	return BorisPlayerState->GetAbilitySystemComponent();
}

void ABorisPlayerCharacter::InitAbilityPlayerInfo()
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	check(AbilitySystemComponent);
	
	AbilitySystemComponent->InitAbilityActorInfo(GetBorisPlayerState(), this);
}
