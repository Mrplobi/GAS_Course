// By Plobindustries


#include "AbilitySystem/GASAbilitySystemGlobals.h"
#include "AuraAbilityTypes.h"

FGameplayEffectContext* UGASAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
