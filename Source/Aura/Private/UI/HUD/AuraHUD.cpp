// By Plobindustries


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI//WidgetController/OverlayWidgetController.h"
#include "UI//WidgetController/AttributeMenuWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
    if (OverlayWidgetController == nullptr)
    {
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControlerClass);
        OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
        OverlayWidgetController->BindCallbacksToDependencies();
    }
    return OverlayWidgetController;


}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAuraAbilitySystemComponent* ASC, UAuraAttributeSet* AS)
{
    checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass was not set, Check BP_AuraHUD"));
    checkf(OverlayWidgetControlerClass, TEXT("OverlayWidgetControllerClass was not set, Check BP_AuraHUD"));

    OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

    OverlayWidget->SetWidgetController(GetOverlayWidgetController(WidgetControllerParams));

    OverlayWidgetController->BroadcastInitialValues();

    OverlayWidget->AddToViewport();
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
    if (AttributeWidgetController == nullptr)
    {
        AttributeWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeWidgetControlerClass);
        AttributeWidgetController->SetWidgetControllerParams(WidgetControllerParams);
        AttributeWidgetController->BindCallbacksToDependencies();
    }
    return AttributeWidgetController;
}
