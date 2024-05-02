// By Plobindustries


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);

	for (FAuraAttributeInfo info : AttributeInfo->AttributeInfos)
	{
		BroadcastAttributeInfo(info.AttributeTag);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	for (FAuraAttributeInfo info : AttributeInfo->AttributeInfos)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(info.Attribute).AddLambda(
			[this, info](const FOnAttributeChangeData& Data) {
				BroadcastAttributeInfo(info.AttributeTag);
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag)
{
	FAuraAttributeInfo info = AttributeInfo->FindAttributeInfoByTag(Tag);
	info.UpdateAttributeInfoValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(info);
}
