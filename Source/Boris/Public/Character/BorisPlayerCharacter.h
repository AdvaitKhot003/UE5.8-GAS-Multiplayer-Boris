// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "BorisCharacterBase.h"
#include "BorisPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class BORIS_API ABorisPlayerCharacter : public ABorisCharacterBase
{
	GENERATED_BODY()

public:
	ABorisPlayerCharacter();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Boris|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Boris|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
