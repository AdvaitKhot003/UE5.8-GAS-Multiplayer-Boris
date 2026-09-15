// No Copyright.

#include "Character/BorisCharacterBase.h"

ABorisCharacterBase::ABorisCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bone transforms whether rendered or not rendered for bone updates on dedicated server.
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}
