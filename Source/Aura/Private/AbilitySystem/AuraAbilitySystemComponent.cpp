// By Plobindustries


#include "AbilitySystem/AuraAbilitySystemComponent.h"	
#include "GameplayTagContainer.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::AffectApplied);
}

void UAuraAbilitySystemComponent::AffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE Tag : %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, Msg);
	}
}
