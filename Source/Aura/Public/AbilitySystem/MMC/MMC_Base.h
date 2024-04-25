// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Base.generated.h"

USTRUCT()
struct FAttributeCoefficient
{
	GENERATED_BODY()
public:
	FAttributeCoefficient() {};

	float GetInsideCalculationResult(const float& AttributeMagnitude)
	{
		float result = AttributeMagnitude;
		switch (CoefOperationType)
		{
		case EGameplayModOp::Additive:
			result = AttributeMagnitude + Coefficient;
			break;
		case EGameplayModOp::Multiplicitive:
			result = AttributeMagnitude * Coefficient;
			break;
		case EGameplayModOp::Division:
			if (Coefficient != 0)
			{
				result = AttributeMagnitude / Coefficient;
			}
			break;
		default:
			break;
		}
		return result;
	}

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(EditDefaultsOnly)
	float Coefficient = 1;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Internal operation used to calculate the value to impact the chain of Attributes"), meta = (ValidEnumValues = "Additive, Multiplicitive, Division"))
	TEnumAsByte<EGameplayModOp::Type> CoefOperationType = EGameplayModOp::Additive;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "External operation applied on the previous chain of attributes"), meta = (ValidEnumValues = "Additive, Multiplicitive, Division"))
	TEnumAsByte<EGameplayModOp::Type> GlobalOperationType = EGameplayModOp::Additive;

};

/**
 * 
 */
UCLASS(Abstract)
class AURA_API UMMC_Base : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_Base();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	UPROPERTY(EditDefaultsOnly)
	float BaseValue = 0;

	UPROPERTY(EditDefaultsOnly)
	TArray<FAttributeCoefficient> RelevantAttributes;

	UPROPERTY(EditDefaultsOnly)
	float LevelMultiplier = 0;
};
