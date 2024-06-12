// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	float BaseHealth = 50.f;
	UPROPERTY(EditDefaultsOnly)
	float AttributeMultiplier = 2.5f;
	UPROPERTY(EditDefaultsOnly)
	float LevelBonus = 10.f;

private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
