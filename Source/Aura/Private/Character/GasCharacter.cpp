// By Plobindustries


#include "Character/GasCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"
#include <Player/AuraPlayerController.h>
#include <UI/HUD/AuraHUD.h>

AGasCharacter::AGasCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AGasCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}
void AGasCharacter::OnRep_PlayerState()
{
	InitAbilityActorInfo();
}

int32 AGasCharacter::GetCharacterLevel() const
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetCharacterLevel();
}

void AGasCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent());
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent->AbilityActorInfoSet();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	if (AAuraPlayerController* AuraController = GetController<AAuraPlayerController>())
	{
		if (AAuraHUD* HUD = Cast<AAuraHUD>(AuraController->GetHUD()))
		{
			HUD->InitOverlay(AuraController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}



