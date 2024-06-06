// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageAbility.h"
#include "AuraProjectileAbility.generated.h"

class AAuraProjectile;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileAbility : public UAuraDamageAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
