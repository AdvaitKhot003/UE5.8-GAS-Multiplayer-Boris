// No Copyright.

#include "Player/BorisPlayerState.h"
#include "AbilitySystem/BorisAbilitySystemComponent.h"
#include "AbilitySystem/BorisAttributeSet.h"

ABorisPlayerState::ABorisPlayerState()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UBorisAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UBorisAttributeSet>("AttributeSetComp");
}

UAbilitySystemComponent* ABorisPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
