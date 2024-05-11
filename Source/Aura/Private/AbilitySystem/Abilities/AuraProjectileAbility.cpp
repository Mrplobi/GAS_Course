// By Plobindustries


#include "AbilitySystem/Abilities/AuraProjectileAbility.h"
#include "Actor/AuraProjectile.h"
#include "Kismet/GameplayStatics.h"
#include <Interaction/CombatInterface.h>

void UAuraProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	ICombatInterface* CallingInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (bIsServer && CallingInterface != nullptr)
	{
		FVector SpawnLoc = CallingInterface->GetProjectileSpawnSocketLocation();

		FRotator SpawnRot = (ProjectileTargetLocation - SpawnLoc).Rotation();
		SpawnRot.Pitch = 0; //Ensure projectile flies parralele to ground

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnLoc);
		SpawnTransform.SetRotation(SpawnRot.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
			ESpawnActorScaleMethod::OverrideRootScale
		);

		//TODO : Set Projectile effect spec

		Projectile->FinishSpawning(SpawnTransform);
	}
}
