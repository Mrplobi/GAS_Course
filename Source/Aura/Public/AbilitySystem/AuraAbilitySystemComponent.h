// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTag, const FGameplayTagContainer& /*AssetTags*/)

class UAuraGameplayAbility;
class UGameplayAbility;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	FEffectAssetTag EffectAssetTagsReceived;

	void AddCharacterAbilities(const TArray<TSubclassOf<UAuraGameplayAbility>>& AbilitiesToAdd);
	void AddCharacterAbility(const TSubclassOf<UAuraGameplayAbility>& AbilityToAdd, int32 level = 1);

protected:
	void EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
