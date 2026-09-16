// No Copyright.

#include "Input/BorisInputData.h"

UInputAction* UBorisInputData::FindNativeInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound) const
{
	for (const FInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.IsValid() && InputActionConfig.InputTag.MatchesTagExact(InInputTag))
		{
			return InputActionConfig.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Could not find NativeInputAction for InputTag: [%s] on InputDataAsset: [%s]"),
			*InInputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}

UInputAction* UBorisInputData::FindAbilityInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound) const
{
	for (const FInputActionConfig& InputActionConfig : AbilityInputActions)
	{
		if (InputActionConfig.IsValid() && InputActionConfig.InputTag.MatchesTagExact(InInputTag))
		{
			return InputActionConfig.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Could not find AbilityInputAction for InputTag: [%s] on InputDataAsset: [%s]"),
			*InInputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
