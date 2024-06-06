// By Plobindustries


#include "Character/GasEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include <Aura/Aura.h>
#include "Components/WidgetComponent.h"
#include "UI/Widget/AuraUserWidget.h"
#include <AuraBlueprintLibrary.h>
#include <AuraGameplayTags.h>

AGasEnemy::AGasEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthWidget->SetupAttachment(GetRootComponent());

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AGasEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AGasEnemy::UnhighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AGasEnemy::GetCharacterLevel() const
{
	return Level;
}
void AGasEnemy::Die()
{
	SetLifeSpan(DeathLifeSpan);
	Super::Die();
}

void AGasEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AGasEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->AbilityActorInfoSet();
	if (HasAuthority())
	{
		UAuraBlueprintLibrary::InitializeAbilities(this, AbilitySystemComponent);
		InitializeDefaultAttributes();
	}

	if (UAuraUserWidget* AuraWidget = Cast<UAuraUserWidget>(HealthWidget->GetUserWidgetObject()))
	{
		AuraWidget->SetWidgetController(this);
	};

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
		});


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitStun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AGasEnemy::HitStunStatusChanged);

}

void AGasEnemy::HitStunStatusChanged(const FGameplayTag TagChanged, int32 tagCount)
{
	bShouldbeStunned = tagCount > 0;

}

void AGasEnemy::InitializeDefaultAttributes() const
{
	UAuraBlueprintLibrary::InitializeDefaultAttributes(this, AbilitySystemComponent, CharacterClass, Level);
}
