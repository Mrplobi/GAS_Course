// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "GASCharacterBase.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UAuraAbilitySystemComponent;
class UAuraAttributeSet;
class UAuraGameplayAbility;

UCLASS(Abstract)
class AURA_API AGASCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AGASCharacterBase();
	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAuraAttributeSet* GetAttributeSet() const { return AttributeSet; };

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();

	void InitializeDefaultAttributes() const;
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultAttributes, float Level) const;

	void AddCharacterStartingAbilities();

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UAuraGameplayAbility>> StartupAbilities;



};
