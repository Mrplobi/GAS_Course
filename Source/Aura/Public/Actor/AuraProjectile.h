// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UMetaSound;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AAuraProjectile();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Destroyed() override;
	virtual void HandleDestructionEffects();

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

private:
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed = 100;
	UPROPERTY(EditDefaultsOnly)
	float MaxSpeed = 0;

	bool bHasHit = false;

#pragma region Cosmetics of explosion
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ExplosionVFX;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ExplosionSFX;
#pragma endregion

};
