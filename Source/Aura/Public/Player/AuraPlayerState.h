// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAuraAbilitySystemComponent;
class UAbilitySystemComponent;
class UAuraAttributeSet;

/**
 *
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAuraAttributeSet* GetAttributeSet() const { return AttributeSet; };

	FORCEINLINE int32 GetCharacterLevel() const { return Level; };

private:
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

protected:

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing = OnRep_Level, Category = "Character Class Defaults")
	int32 Level = 1;

};