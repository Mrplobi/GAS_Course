// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "Character/GASCharacterBase.h"
#include "Interaction/HoverInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include <AbilitySystem/Data/AuraCharacterInfo.h>
#include "GasEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AGASAIController;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class AURA_API AGasEnemy : public AGASCharacterBase, public IHoverInterface
{
	GENERATED_BODY()
	
public:
	AGasEnemy();

	virtual void PossessedBy(AController* NewController) override;

	// Inherited via IHoverInterface
	void HighlightActor() override;
	void UnhighlightActor() override;

	// Inherited via ICombatInterface
	virtual int32 GetCharacterLevel() const override;
	virtual void Die() override;

	void HitStunStatusChanged(const FGameplayTag TagChanged, int32 tagCount);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float DeathLifeSpan = 5.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bShouldbeStunned = false;
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

#pragma region AI Behavior
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY()
	TObjectPtr<AGASAIController> GASAIController;
#pragma endregion
};