// By Plobindustries

#include "Character/GASCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include <Aura/Aura.h>

AGASCharacterBase::AGASCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGASCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

void AGASCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();
}

void AGASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGASCharacterBase::InitAbilityActorInfo()
{
}

FVector AGASCharacterBase::GetProjectileSpawnSocketLocation() const
{
	return Weapon->GetSocketLocation(WeaponProjectileSocket);
}

UAnimMontage* AGASCharacterBase::GetHitStunMontage_Implementation()
{
	return HitStunMontage;
}

void AGASCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1);
	ApplyEffectToSelf(DefaultVitalAttributes, 1);
}

void AGASCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectToApply, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(EffectToApply);
	FGameplayEffectContextHandle Context = GetAbilitySystemComponent()->MakeEffectContext();
	Context.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectToApply, Level, Context);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), GetAbilitySystemComponent());
}

void AGASCharacterBase::AddCharacterStartingAbilities()
{
	if (!HasAuthority())
		return;

	AbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}

void AGASCharacterBase::Dissolve()
{
	if (IsValid(DissolveMatInst))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMatInst, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		UMaterialInstanceDynamic* WeaponDynamicMatInst = nullptr;
		if (IsValid(WeaponDissolveMatInst))
		{
			WeaponDynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMatInst, this);
			Weapon->SetMaterial(0, WeaponDynamicMatInst);
		}
		StartDissolveTimeline(DynamicMatInst, WeaponDynamicMatInst);
	}
}

UAbilitySystemComponent* AGASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}
