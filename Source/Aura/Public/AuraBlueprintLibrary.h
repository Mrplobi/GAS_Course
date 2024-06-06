// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <AbilitySystem/Data/AuraCharacterInfo.h>
#include "AuraBlueprintLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;
struct FWidgetControllerParams;
class UAuraAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class AURA_API UAuraBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "AuraBlueprintLibrary|Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "AuraBlueprintLibrary|Widget Controller")
	static UAttributeMenuWidgetController* GetAttributeWidgetController(const UObject* WorldContextObject);

	/// <summary>
	/// Initializes the rpg attibutes for the enemies on spawn
	/// </summary>
	/// <param name="WorldContextObject"></param>
	/// <param name="ASCToInit"></param>
	/// <param name="CharacterClass"></param>
	/// <param name="Level"></param>
	UFUNCTION(BlueprintCallable, Category = "AuraBlueprintLibrary|Class Defaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, UAuraAbilitySystemComponent* ASCToInit, ECharacterClass CharacterClass, float Level);

	/// <summary>
	/// Initializes the abilities for the ennemies on spawn
	/// </summary>
	/// <param name="WorldContextObject"></param>
	/// <param name="Level"></param>
	UFUNCTION(BlueprintCallable, Category = "AuraBlueprintLibrary|Class Defaults")
	static void InitializeAbilities(const UObject* WorldContextObject, UAuraAbilitySystemComponent* ASCToInit, ECharacterClass CharacterClass = ECharacterClass::Default, float Level = 1);

	UFUNCTION(BlueprintCallable, Category = "AuraBlueprintLibrary|Class Data")
	static UAuraCharacterInfo* GetCharacterInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraBlueprintLibrary|Gameplay Effects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "AuraBlueprintLibrary|Gameplay Effects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION()
	static void SetBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlock);

	UFUNCTION()
	static void SetCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCrit);
};
