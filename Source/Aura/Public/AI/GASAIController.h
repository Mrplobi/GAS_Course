// By Plobindustries

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GASAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class AURA_API AGASAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AGASAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
