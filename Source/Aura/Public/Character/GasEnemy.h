// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "Interaction/HoverInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include <AbilitySystem/Data/AuraCharacterInfo.h>
#include "GasEnemy.generated.h"

class UWidgetComponent;
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

	virtual void InitializeDefaultAttributes() const override;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthWidget;

};
