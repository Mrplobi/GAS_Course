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

#pragma region Attributes
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
#pragma endregion
#pragma region Inputs
	FGameplayTag Input_LMB;
	FGameplayTag Input_RMB;
	FGameplayTag Input_1;
	FGameplayTag Input_2;
	FGameplayTag Input_3;
	FGameplayTag Input_4;
#pragma endregion

#pragma region Damage Related
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lighting;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Magic;

	FGameplayTag Weakness_Fire;
	FGameplayTag Weakness_Lightning;
	FGameplayTag Weakness_Physical;
	FGameplayTag Weakness_Magic;

	FGameplayTag Resistance_Fire;
	FGameplayTag Resistance_Lightning;
	FGameplayTag Resistance_Physical;
	FGameplayTag Resistance_Magic;

	TMap<FGameplayTag, FGameplayTag> ResistancePerDamageType;

	FGameplayTag Effects_HitStun;
#pragma endregion

protected:

private:
	static FAuraGameplayTags AuraGameplayTags;
};