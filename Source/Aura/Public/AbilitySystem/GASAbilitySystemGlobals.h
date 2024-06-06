// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GASAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UGASAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
