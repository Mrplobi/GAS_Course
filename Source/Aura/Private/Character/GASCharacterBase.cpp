// By Plobindustries

#include "Character/GASCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"	

AGASCharacterBase::AGASCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGASCharacterBase::InitAbilityActorInfo()
{
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

UAbilitySystemComponent* AGASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}
