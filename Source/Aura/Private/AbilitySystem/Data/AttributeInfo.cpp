// By Plobindustries


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& Tag, bool bLogNotFound)
{
	const FAuraAttributeInfo* InfoFound = AttributeInfos.FindByPredicate([Tag](FAuraAttributeInfo info) {return info.AttributeTag.MatchesTagExact(Tag); });

	if (InfoFound == nullptr && bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for AttributeTag [%s]"), *Tag.ToString());
		return FAuraAttributeInfo();
	}

	return *InfoFound;
}


float FAuraAttributeInfo::UpdateAttributeInfoValue(const UAttributeSet* Src)
{
	Value = Attribute.GetNumericValue(Src);
	return Value;
}
