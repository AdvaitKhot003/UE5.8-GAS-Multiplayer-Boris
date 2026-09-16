// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "BorisPlayerController.generated.h"

class UBorisInputData;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class BORIS_API ABorisPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABorisPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boris|Data")
	TObjectPtr<UBorisInputData> BorisInputData;
	
private:
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	
	void Jump();
	void StopJumping();
	
	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputHeld(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);
};
