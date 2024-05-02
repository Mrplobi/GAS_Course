// By Plobindustries


#include "AbilitySystem/AuraAbilitySystemComponent.h"	
#include "GameplayTagContainer.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UAuraGameplayAbility>>& AbilitiesToAdd)
{
	for (TSubclassOf<UAuraGameplayAbility> AbilityClass : AbilitiesToAdd)
	{
		AddCharacterAbility(AbilityClass);
	}
}

void UAuraAbilitySystemComponent::AddCharacterAbility(const TSubclassOf<UAuraGameplayAbility>& AbilityToAdd, int32 level)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityToAdd, level);
	//GiveAbility(AbilitySpec);
	GiveAbilityAndActivateOnce(AbilitySpec);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsReceived.Broadcast(TagContainer);
	
}
