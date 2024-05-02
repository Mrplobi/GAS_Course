// By Plobindustries


#include "AuraBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <Player/AuraPlayerState.h>
#include <UI/HUD/AuraHUD.h>

UOverlayWidgetController* UAuraBlueprintLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* Hud = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PS = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAuraAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams ControllerParams(PlayerController, PS, ASC, AS);

			return Hud->GetOverlayWidgetController(ControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraBlueprintLibrary::GetAttributeWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* Hud = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PS = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAuraAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams ControllerParams(PlayerController, PS, ASC, AS);

			return Hud->GetAttributeWidgetController(ControllerParams);
		}
	}
	return nullptr;
}