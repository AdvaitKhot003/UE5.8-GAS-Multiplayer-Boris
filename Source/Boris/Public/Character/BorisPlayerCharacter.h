// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "BorisCharacterBase.h"
#include "BorisPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABorisPlayerState;
/**
 * 
 */
UCLASS()
class BORIS_API ABorisPlayerCharacter : public ABorisCharacterBase
{
	GENERATED_BODY()

public:
	ABorisPlayerCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	/** Ability System Interface - Start **/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/** Ability System Interface - End **/
	
	ABorisPlayerState* GetBorisPlayerState() const;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Boris|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Boris|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
private:
	void InitAbilityPlayerInfo();
};
