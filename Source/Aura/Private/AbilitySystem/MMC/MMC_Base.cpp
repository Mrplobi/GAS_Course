// By Plobindustries


#include "AbilitySystem/MMC/MMC_Base.h"
#include <Interaction/CombatInterface.h>

UMMC_Base::UMMC_Base()
{
}

float UMMC_Base::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// We can gather Tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvalutaionParametters;
	EvalutaionParametters.SourceTags = SourceTags;
	EvalutaionParametters.TargetTags = TargetTags;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 CharacterLevel = CombatInterface->GetCharacterLevel();

	float MagnitudeResult = BaseValue;

	for (FAttributeCoefficient AttributeCoef : RelevantAttributes)
	{
		const FGameplayEffectAttributeCaptureDefinition* CapturedAttribute = RelevantAttributesToCapture.
			FindByPredicate([AttributeCoef](const FGameplayEffectAttributeCaptureDefinition& Item)
				{
					return Item.AttributeToCapture.AttributeName == AttributeCoef.Attribute.AttributeName;
				});

		float AttributeMag = 0;

		if (CapturedAttribute)
		{
			GetCapturedAttributeMagnitude(*CapturedAttribute, Spec, EvalutaionParametters, AttributeMag);
			switch (AttributeCoef.GlobalOperationType)
			{
				case EGameplayModOp::Additive:
					MagnitudeResult += AttributeCoef.GetInsideCalculationResult(AttributeMag);
					break;
				case EGameplayModOp::Multiplicitive:
					MagnitudeResult *= AttributeCoef.GetInsideCalculationResult(AttributeMag); 
					break;
				case EGameplayModOp::Division:
					if (AttributeCoef.GetInsideCalculationResult(AttributeMag) != 0)
					{
						MagnitudeResult /= AttributeCoef.GetInsideCalculationResult(AttributeMag);
					}
					break;
				default:
					break;
			}
		}
	}
	return MagnitudeResult + LevelMultiplier * CharacterLevel;
}
