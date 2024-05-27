// By Plobindustries


#include "AuraBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include <Player/AuraPlayerState.h>
#include <UI/HUD/AuraHUD.h>
#include <Game/GASGameModeBase.h>
#include "Abilities/GameplayAbility.h"

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

void UAuraBlueprintLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, UAuraAbilitySystemComponent* ASCToInit, ECharacterClass CharacterClass, float Level)
{
	if (AGASGameModeBase* GM = Cast<AGASGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		UAuraCharacterInfo* CharacterInfo = GM->GetCharacterInfo();
		const FCharacterClassDefaultInfo ClassDefault = CharacterInfo->GetCharacterInfoFromClass(CharacterClass);

		AActor* SourceActor = ASCToInit->GetAvatarActor();

		FGameplayEffectContextHandle PrimaryContext = ASCToInit->MakeEffectContext();
		PrimaryContext.AddSourceObject(SourceActor);
		const FGameplayEffectSpecHandle PrimaryHandle = ASCToInit->MakeOutgoingSpec(ClassDefault.PrimarySetEffect, Level, PrimaryContext);
		ASCToInit->ApplyGameplayEffectSpecToSelf(*PrimaryHandle.Data.Get());

		FGameplayEffectContextHandle SecondaryContext = ASCToInit->MakeEffectContext();
		SecondaryContext.AddSourceObject(SourceActor);
		const FGameplayEffectSpecHandle SecondaryHandle = ASCToInit->MakeOutgoingSpec(CharacterInfo->SecondarySetEffect, Level, SecondaryContext);
		ASCToInit->ApplyGameplayEffectSpecToSelf(*SecondaryHandle.Data.Get());

		FGameplayEffectContextHandle VitalContext = ASCToInit->MakeEffectContext();
		VitalContext.AddSourceObject(SourceActor);
		const FGameplayEffectSpecHandle VitalHandle = ASCToInit->MakeOutgoingSpec(CharacterInfo->VitalSetEffect, Level, VitalContext);
		ASCToInit->ApplyGameplayEffectSpecToSelf(*VitalHandle.Data.Get());
	}
}

void UAuraBlueprintLibrary::InitializeAbilities(const UObject* WorldContextObject, UAuraAbilitySystemComponent* ASCToInit, ECharacterClass CharacterClass, float Level)
{
	if (AGASGameModeBase* GM = Cast<AGASGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		UAuraCharacterInfo* CharacterInfo = GM->GetCharacterInfo();
		//const FCharacterClassDefaultInfo ClassDefault = CharacterInfo->GetCharacterInfoFromClass(CharacterClass);

		for (TSubclassOf<UGameplayAbility> Ability : CharacterInfo->CommonAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, Level);
			ASCToInit->GiveAbility(Ability);
		}
	}
}
