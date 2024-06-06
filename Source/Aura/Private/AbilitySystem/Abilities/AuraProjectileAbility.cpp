// By Plobindustries


#include "AbilitySystem/Abilities/AuraProjectileAbility.h"
#include "Actor/AuraProjectile.h"
#include "Kismet/GameplayStatics.h"
#include <Interaction/CombatInterface.h>
#include "AbilitySystemBlueprintLibrary.h"
#include "Aura/Public/AuraGameplayTags.h"
#include "AbilitySystemComponent.h"

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

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		const FAuraGameplayTags AuraTags = FAuraGameplayTags::Get();

		for (auto& Pair : PowerPerDamageType)
		{
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Pair.Value.GetValueAtLevel(GetAbilityLevel()));
		}

		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
