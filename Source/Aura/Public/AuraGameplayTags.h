// By Plobindustries

#pragma once

#include "GameplayTagContainer.h"
#include "CoreMinimal.h"

/**
 * AuraGameplayTags
 * 
 * Singleton containing Gameplay Tags created in C++
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return AuraGameplayTags; }
	static void InitializeGameplayTags();

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Finesse;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CritChance;
	FGameplayTag Attributes_Secondary_CritDamage;
	FGameplayTag Attributes_Secondary_CritResistance;
	FGameplayTag Attributes_Secondary_HealthRegen;
	FGameplayTag Attributes_Secondary_ManaRegen;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

protected:

private:
	static FAuraGameplayTags AuraGameplayTags;
};