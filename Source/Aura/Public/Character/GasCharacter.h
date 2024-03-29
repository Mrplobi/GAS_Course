// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "GasCharacter.generated.h"

class uhduhd;

/**
 * 
 */
UCLASS()
class AURA_API AGasCharacter : public AGASCharacterBase
{
	GENERATED_BODY()

public:
	AGasCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	void InitAbilityActorInfo();
	
};
