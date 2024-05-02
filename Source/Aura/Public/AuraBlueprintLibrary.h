// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraBlueprintLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class AURA_API UAuraBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "AuraBlueprintLibrary|Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "AuraBlueprintLibrary|Widget Controller")
	static UAttributeMenuWidgetController* GetAttributeWidgetController(const UObject* WorldContextObject);
	
};
