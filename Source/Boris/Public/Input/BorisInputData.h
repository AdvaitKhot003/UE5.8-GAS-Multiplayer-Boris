// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "BorisInputData.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputActionConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Input"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
	
	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};

UCLASS()
class BORIS_API UBorisInputData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boris|Input|IMC")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boris|Input|IA", meta = (TitleProperty = "InputTag"))
	TArray<FInputActionConfig> NativeInputActions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boris|Input|IA", meta = (TitleProperty = "InputTag"))
	TArray<FInputActionConfig> AbilityInputActions;
	
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound = false) const;
	UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound = false) const;
};
