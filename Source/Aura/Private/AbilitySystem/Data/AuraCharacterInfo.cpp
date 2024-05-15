// By Plobindustries


#include "AbilitySystem/Data/AuraCharacterInfo.h"

FCharacterClassDefaultInfo UAuraCharacterInfo::GetCharacterInfoFromClass(ECharacterClass Class)
{
	return CharacterInfo.FindChecked(Class);
}
