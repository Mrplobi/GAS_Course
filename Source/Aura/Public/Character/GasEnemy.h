// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "Interaction/HoverInterface.h"
#include "GasEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AGasEnemy : public AGASCharacterBase, public IHoverInterface
{
	GENERATED_BODY()
	
public:
	AGasEnemy();
	// Inherited via IHoverInterface
	void HighlightActor() override;
	void UnhighlightActor() override;

	// Inherited via ICombatInterface
	virtual int32 GetCharacterLevel() const override;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

};
