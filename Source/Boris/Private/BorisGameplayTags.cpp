// No Copyright.

#include "BorisGameplayTags.h"

namespace BorisGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_Move,
		"Input.Move",
		"Input tag for controlling character movement."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_Look,
		"Input.Look",
		"Input tag for controlling character look and camera rotation."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_Jump,
		"Input.Jump",
		"Input tag for triggering the character jump."
	);
	
	/** Ability Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_Ability_Primary,
		"Input.Ability.Primary",
		"Input tag for activating the primary ability."
	);

	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_Ability_Secondary,
		"Input.Ability.Secondary",
		"Input tag for activating the secondary ability."
	);
}
