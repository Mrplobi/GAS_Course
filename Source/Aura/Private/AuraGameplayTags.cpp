// By Plobindustries

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::AuraGameplayTags;

void FAuraGameplayTags::InitializeGameplayTags()
{
	AuraGameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("The current Health of the character"));
	AuraGameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("The current Mana of the character"));

	AuraGameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Increases physical damage"));
	AuraGameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases magical damage and mana related stats"));
	AuraGameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increases total health"));
	AuraGameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Increases Armor and defense related stats"));
	AuraGameplayTags.Attributes_Primary_Finesse = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Finesse"), FString("Increases Crit and crit resistance"));

	AuraGameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Decreases Damage taken"));
	AuraGameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Allows partial bypass of enemy armor"));
	AuraGameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Chance to divide damage by 2"));
	AuraGameplayTags.Attributes_Secondary_CritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritChance"), FString("Chance to deal extra damage"));
	AuraGameplayTags.Attributes_Secondary_CritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritDamage"), FString("Value of extra damage"));
	AuraGameplayTags.Attributes_Secondary_CritResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritResistance"), FString("Resilience to taking extra damage"));
	AuraGameplayTags.Attributes_Secondary_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegen"), FString("Health recovered every second"));
	AuraGameplayTags.Attributes_Secondary_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegen"), FString("Mana recovered every second"));
	AuraGameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"));
	AuraGameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"));

	
	AuraGameplayTags.Input_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"));
	AuraGameplayTags.Input_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.RMB"));
	AuraGameplayTags.Input_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.1"));
	AuraGameplayTags.Input_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.2"));
	AuraGameplayTags.Input_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.3"));
	AuraGameplayTags.Input_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.4"));
	/*
	Damage types
	*/
	AuraGameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DamageType.Fire"));
	AuraGameplayTags.Damage_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DamageType.Lightning"));
	AuraGameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DamageType.Physical"));
	AuraGameplayTags.Damage_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DamageType.Magic"));
	/*
	Damage Resistances
	*/
	AuraGameplayTags.Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Resistance.Fire"));
	AuraGameplayTags.Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Resistance.Lightning"));
	AuraGameplayTags.Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Resistance.Physical"));
	AuraGameplayTags.Resistance_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Resistance.Magic"));


	AuraGameplayTags.ResistancePerDamageType.Add(AuraGameplayTags.Damage_Fire, AuraGameplayTags.Resistance_Fire);
	AuraGameplayTags.ResistancePerDamageType.Add(AuraGameplayTags.Damage_Lighting, AuraGameplayTags.Resistance_Lightning);
	AuraGameplayTags.ResistancePerDamageType.Add(AuraGameplayTags.Damage_Physical, AuraGameplayTags.Resistance_Physical);
	AuraGameplayTags.ResistancePerDamageType.Add(AuraGameplayTags.Damage_Magic, AuraGameplayTags.Resistance_Magic);

	AuraGameplayTags.Effects_HitStun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitStun"));

}