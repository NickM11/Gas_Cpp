#pragma once
#include "CoreMinimal.h"
#include "GASBaseActor.h"
#include "DamagerActor.generated.h"

UCLASS()
class GAS_CPP_API ADamagerActor : public AGASBaseActor
{
    GENERATED_BODY()

public:
    ADamagerActor();

    UFUNCTION(BlueprintCallable, Category = "Damager")
    void TryAttack();

protected:
    FGameplayTag DamageAbilityTag;
};