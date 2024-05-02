// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class UAuraAbilitySystemComponent;
class UAuraAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams&);

	void InitOverlay(APlayerController* PlayerC, APlayerState* PS, UAuraAbilitySystemComponent* ASC, UAuraAttributeSet* AS);

	UAttributeMenuWidgetController* GetAttributeWidgetController(const FWidgetControllerParams&);

private:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere, Category = "Overlay")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere, Category = "Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControlerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeWidgetController;
	UPROPERTY(EditAnywhere, Category = "Attributes Menu")
	TSubclassOf<UAttributeMenuWidgetController> AttributeWidgetControlerClass;
};
