// By Plobindustries


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraGameplayTags.h"
#include <AbilitySystem/Data/AuraCharacterInfo.h>
#include "AuraBlueprintLibrary.h"
#include <Interaction/CombatInterface.h>
#include <AuraAbilityTypes.h>

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagToCaptureDef;

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MagicResistance, Target, false);

		const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

		TagToCaptureDef.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagToCaptureDef.Add(Tags.Attributes_Secondary_BlockChance, BlockChanceDef);
		TagToCaptureDef.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
		TagToCaptureDef.Add(Tags.Attributes_Secondary_CritChance, CritChanceDef);
		TagToCaptureDef.Add(Tags.Attributes_Secondary_CritDamage, CritDamageDef);

		TagToCaptureDef.Add(Tags.Resistance_Fire, FireResistanceDef);
		TagToCaptureDef.Add(Tags.Resistance_Lightning, LightningResistanceDef);
		TagToCaptureDef.Add(Tags.Resistance_Physical, PhysicalResistanceDef);
		TagToCaptureDef.Add(Tags.Resistance_Magic, MagicResistanceDef);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC == nullptr ? nullptr : SourceASC->GetAvatarActor();
	const AActor* TargetAvatar = SourceASC == nullptr ? nullptr : TargetASC->GetAvatarActor();
	const ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	const ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	//Get Damage Set by Caller Mag
	float IncDamage = 0.f;
	for (const TPair<FGameplayTag, FGameplayTag>& DamageTagInfo : FAuraGameplayTags::Get().ResistancePerDamageType)
	{
		const FGameplayTag DamageTag = DamageTagInfo.Key;
		const FGameplayTag ResistanceTag = DamageTagInfo.Value;
		const FGameplayEffectAttributeCaptureDefinition ResistanceDef = AuraDamageStatics().TagToCaptureDef[ResistanceTag];

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ResistanceDef, EvaluationParams, Resistance);
		Resistance = FMath::Clamp(Resistance,-100, 100);

		float TypeIncDamage = Spec.GetSetByCallerMagnitude(DamageTag, false);
		TypeIncDamage *= 1 - (Resistance/100);

		IncDamage += TypeIncDamage;
	}

	float TargetBlockChance;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParams, TargetBlockChance);

	float TargetArmor;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParams, TargetArmor);

	float SourceArmorPenetration;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParams, SourceArmorPenetration);

	float SourceCritChance;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritChanceDef, EvaluationParams, SourceCritChance);

	float SourceCritDamage;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, EvaluationParams, SourceCritDamage);

	//Prepare data for calculation
	const UAuraCharacterInfo* CharacterInfo = UAuraBlueprintLibrary::GetCharacterInfo(SourceAvatar);
	const UCurveTable* DamageCalcCoeffs = CharacterInfo->DamageCalculationCoefficients;

	const float ArmorCoeff = DamageCalcCoeffs->FindCurve(FName("ArmorCoeff"), FString())->Eval(TargetCombatInterface->GetCharacterLevel());
	const float ArmorPenetrationCoeff = DamageCalcCoeffs->FindCurve(FName("ArmorPenetrationCoeff"), FString())->Eval(SourceCombatInterface->GetCharacterLevel());


	//Reduce Armor based on Penetration
	const float EffectiveArmor = TargetArmor * FMath::Max((100 - SourceArmorPenetration * ArmorPenetrationCoeff) / 100.f, 0);
	//Reduce Damage based on remaining armor
	const float PostArmorDamage = IncDamage * FMath::Max((100 - EffectiveArmor * ArmorCoeff) / 100.f, 0);

	//Check Random damage behaviours
	float FinalDamage = PostArmorDamage;

	float CritRoll = FMath::RandRange(0, 100);
	bool bHasCrit = CritRoll < SourceCritChance;
	UAuraBlueprintLibrary::SetCriticalHit(EffectContextHandle, bHasCrit);

	//A crit can't be blocked
	if (!bHasCrit)
	{
		//Check Block Sucess (halve damage is sucess)
		float BlockRoll = FMath::RandRange(0, 100);
		bool bHasBlocked = BlockRoll < TargetBlockChance;
		UAuraBlueprintLibrary::SetBlockedHit(EffectContextHandle, bHasBlocked);
		if (bHasBlocked)
		{
			FinalDamage /= 2.f;
		}
	}
	else
	{
		FinalDamage = FinalDamage * 2.f + SourceCritDamage;
	}

	FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, FinalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
