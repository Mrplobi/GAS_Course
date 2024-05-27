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

		const UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), AbilitySystemComponent->MakeEffectContext());
		const FAuraGameplayTags AuraTags = FAuraGameplayTags::Get();
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AuraTags.Damage, Power.GetValueAtLevel(GetAbilityLevel()));

		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
