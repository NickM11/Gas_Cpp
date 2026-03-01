#pragma once
#include "CoreMinimal.h"
#include "GASBaseActor.h"
#include "GameplayTagContainer.h"
#include "HealerActor.generated.h"

UCLASS()
class GAS_CPP_API AHealerActor : public AGASBaseActor
{
    GENERATED_BODY()

public:
    AHealerActor();

    // Call this to trigger the heal (bind to input or AI)
    UFUNCTION(BlueprintCallable, Category = "Healer")
    void TryHeal();

protected:
    // Tag for the heal ability
    FGameplayTag HealAbilityTag;
};