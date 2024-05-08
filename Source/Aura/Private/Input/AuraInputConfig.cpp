// By Plobindustries


#include "Input/AuraInputConfig.h"
#include "InputAction.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound) const
{
	const FAuraInputAction* Action = AbilityInputActions.FindByPredicate(
		[Tag](FAuraInputAction action) {
			return action.GameplayTag.MatchesTagExact(Tag);
		}
	);
	if (Action)
	{
		return Action->InputAction;
	}
	else 
	{
		if (bLogNotFound) UE_LOG(LogTemp, Error, TEXT("Could not find Input action for Tag : [%s]"), *Tag.ToString());
		return nullptr;
	}
}

//#if WITH_EDITOR
//#include "Misc/DataValidation.h"
//EDataValidationResult UAuraInputConfig::IsDataValid(FDataValidationContext& Context, const int Index) const
//{
//	EDataValidationResult Result = EDataValidationResult::Valid;
//	unsigned i = 0;
//	for (FAuraInputAction InputAction : AbilityInputActions)
//	{
//		CombineDataValidationResults(Result, InputAction.IsDataValid(Context, i));
//		i++;
//	}
//	return Result;
//}
//
//EDataValidationResult FAuraInputAction::IsDataValid(FDataValidationContext& Context, const int Index) const
//{
//	EDataValidationResult Result = EDataValidationResult::Valid;
//
//	if (InputAction == nullptr)
//	{
//		Result = EDataValidationResult::Invalid;
//		const FText ErrorMessage = FText::FromString(FString::Printf(TEXT("No Input Action found at index [%i]. Please fill the DataAsset"), Index));
//
//		Context.AddError(ErrorMessage);
//	}
//	if (!GameplayTag.IsValid())
//	{
//		Result = EDataValidationResult::Invalid;
//		const FText ErrorMessage = FText::FromString(FString::Printf(TEXT("No Gameplay Tag found at index [%i]. Please fill the DataAsset"), Index));
//
//		Context.AddError(ErrorMessage);
//	}
//	return EDataValidationResult();
//}
//
//#endif