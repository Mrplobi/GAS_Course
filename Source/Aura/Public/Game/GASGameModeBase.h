// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GASGameModeBase.generated.h"

class UAuraCharacterInfo;

/**
 * 
 */
UCLASS()
class AURA_API AGASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	FORCEINLINE UAuraCharacterInfo* GetCharacterInfo() { return CharacterInfo; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Character Defaults")
	TObjectPtr<UAuraCharacterInfo> CharacterInfo;
};
