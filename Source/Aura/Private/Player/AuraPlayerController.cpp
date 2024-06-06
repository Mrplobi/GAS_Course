// By Plobindustries
#define ECC_NavCLick ECC_GameTraceChannel1

#include "Player/AuraPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <Interaction/HoverInterface.h>
#include <Input/AuraInputComponent.h>
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "AuraGameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRunTick();
}

void AAuraPlayerController::ShowDamageNumber_Implementation(ACharacter* TargetCharacter, float Damage, bool bIsCrit, bool bIsBlock)
{
	if (IsValid(TargetCharacter) && DamageTextClass)
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(Damage, bIsCrit, bIsBlock);
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, &ThisClass::AbilityInputHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	bIsAutoRunning = false;
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (CursorHit.bBlockingHit)
	{
		LastHover = CurrentHover;
		CurrentHover = Cast<IHoverInterface>(CursorHit.GetActor());
	}
	else
	{
		LastHover = CurrentHover;
		CurrentHover = nullptr;
	}

	if (LastHover != nullptr)
	{
		LastHover->UnhighlightActor();
	}

	if (CurrentHover != nullptr)
	{
		CurrentHover->HighlightActor();
	}
}

void AAuraPlayerController::AbilityInputPressed(FGameplayTag GameplayTag)
{
	PlayerClickMove(GameplayTag);
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputHeld(GameplayTag);
}

void AAuraPlayerController::AbilityInputReleased(FGameplayTag GameplayTag)
{
	PlayerAutoRun(GameplayTag);
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputReleased(GameplayTag);
}

void AAuraPlayerController::AbilityInputHeld(FGameplayTag GameplayTag)
{
	PlayerHoldMove(GameplayTag);
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputHeld(GameplayTag);
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AbilitySystemComponent;
}

void AAuraPlayerController::PlayerClickMove(FGameplayTag GameplayTag)
{
	if (CurrentHover != NULL) return;
	if (!GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB)) return;

	bStartedMovement = true;
	bIsAutoRunning = false;
	FollowTime = 0;

}

void AAuraPlayerController::PlayerHoldMove(FGameplayTag GameplayTag)
{
	if (!GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB) || !bStartedMovement) return;

	FollowTime += GetWorld()->GetDeltaSeconds();
	FHitResult Hit = FHitResult();
	GetHitResultUnderCursor(ECC_NavCLick, false, Hit);
	if (Hit.bBlockingHit)
	{
		CachedDestination = Hit.ImpactPoint;
		if (APawn* ControllerPawn = GetPawn<APawn>())
		{
			FVector Direction = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(Direction);
		}
	}
}


void AAuraPlayerController::PlayerAutoRun(FGameplayTag GameplayTag)
{
	if (!GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB)) return;

	bStartedMovement = false;
	if (FollowTime <= ShortPressThreshold)
	{
		FHitResult Hit = FHitResult();
		GetHitResultUnderCursor(ECC_NavCLick, false, Hit);

		if (Hit.bBlockingHit)
		{
			CachedDestination = Hit.ImpactPoint;
			if (const APawn* ControllerPawn = GetPawn<APawn>())
			{
				if (UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControllerPawn->GetActorLocation(), CachedDestination))
				{
					Spline->ClearSplinePoints();
					for (const FVector& Point : Path->PathPoints)
					{
						Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
					}
					if (!Path->PathPoints.IsEmpty())
					{
						CachedDestination = Path->PathPoints.Last();
					}
				}

			}
			bIsAutoRunning = true;
		}
	}
}

void AAuraPlayerController::AutoRunTick()
{
	if (!bIsAutoRunning) return;
	
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToTarget = (CachedDestination - ControlledPawn->GetActorLocation()).Length();
		if (DistanceToTarget < DestinationAcceptanceRadius)
		{
			bIsAutoRunning = false;
		}
	}
}
