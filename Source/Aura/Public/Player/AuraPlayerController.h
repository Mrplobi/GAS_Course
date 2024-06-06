// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction; 
struct FInputActionValue;
class IHoverInterface;
class UAuraInputConfig;
struct FGameplayTag;
class UAuraAbilitySystemComponent;
class USplineComponent;
class UWidgetComponent;
class UDamageTextComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(ACharacter* TargetCharacter, float Damage, bool bIsCrit, bool bIsBlock);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();

	void AbilityInputPressed(FGameplayTag GameplayTag);
	void AbilityInputReleased(FGameplayTag GameplayTag);
	void AbilityInputHeld(FGameplayTag GameplayTag);

	UAuraAbilitySystemComponent* GetASC();

#pragma region CLick To Move
	void PlayerClickMove(FGameplayTag GameplayTag);
	void PlayerHoldMove(FGameplayTag GameplayTag);
	void PlayerAutoRun(FGameplayTag GameplayTag);
	void AutoRunTick();
#pragma endregion


private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	TObjectPtr<IHoverInterface> LastHover;
	TObjectPtr<IHoverInterface> CurrentHover;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextClass;

#pragma region Click To Move Behavior
	FVector CachedDestination = FVector::Zero();
	float FollowTime = 0;
	bool bIsAutoRunning = false;
	bool bStartedMovement = false;
	UPROPERTY(EditDefaultsOnly)
	float ShortPressThreshold = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float DestinationAcceptanceRadius = 100;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

#pragma endregion


};
