// By Plobindustries


#include "AuraAssetManager.h"
#include <AuraGameplayTags.h>	
#include "AbilitySystemGlobals.h"

const UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager.Get());
	check(AuraAssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::InitializeGameplayTags();
	
	//Required for use of TargetData
	UAbilitySystemGlobals::Get().InitGlobalData();
}
