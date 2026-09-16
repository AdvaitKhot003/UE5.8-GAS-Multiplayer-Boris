// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "BorisInputData.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "BorisInputComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BORIS_API UBorisInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UBorisInputData* InInputData, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Function);
	
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UBorisInputData* InInputData, UserObject* ContextObject,
		CallbackFunc InputPressedFunc, CallbackFunc InputHeldFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UBorisInputComponent::BindNativeInputAction(const UBorisInputData* InInputData, const FGameplayTag& InInputTag,
	ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Function)
{
	check(InInputData);
	
	if (UInputAction* InputAction = InInputData->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(InputAction, TriggerEvent, ContextObject, Function);
	}
}

template <class UserObject, typename CallbackFunc>
void UBorisInputComponent::BindAbilityInputAction(const UBorisInputData* InInputData, UserObject* ContextObject,
	CallbackFunc InputPressedFunc, CallbackFunc InputHeldFunc, CallbackFunc InputReleasedFunc)
{
	check(InInputData);
	
	for (const FInputActionConfig& Config : InInputData->AbilityInputActions)
	{
		if (!Config.IsValid()) continue;
		
		if (InputPressedFunc)
		{
			BindAction(Config.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, Config.InputTag);
		}
		
		if (InputHeldFunc)
		{
			BindAction(Config.InputAction, ETriggerEvent::Triggered, ContextObject, InputHeldFunc, Config.InputTag);
		}
		
		if (InputReleasedFunc)
		{
			BindAction(Config.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, Config.InputTag);
		}
	}
}
