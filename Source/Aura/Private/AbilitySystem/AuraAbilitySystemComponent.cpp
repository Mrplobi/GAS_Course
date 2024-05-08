// By Plobindustries


#include "AbilitySystem/AuraAbilitySystemComponent.h"	
#include "GameplayTagContainer.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);
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
	if (const UAuraGameplayAbility* Ability = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.DynamicAbilityTags.AddTag(Ability->StartupInputTag);
		GiveAbility(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::AbilityInputHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& Ability : GetActivatableAbilities())
	{
		if (Ability.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Ability);
			if (!Ability.IsActive())
			{
				TryActivateAbility(Ability.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& Ability : GetActivatableAbilities())
	{
		if (Ability.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Ability);
		}
	}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsReceived.Broadcast(TagContainer);	
}
