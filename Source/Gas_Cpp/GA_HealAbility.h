#pragma once
#include "CoreMinimal.h"
#include "GASGameplayAbility.h"
#include "GA_HealAbility.generated.h"

UCLASS()
class GAS_CPP_API UGA_HealAbility : public UGASGameplayAbility
{
    GENERATED_BODY()

public:
    UGA_HealAbility();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

protected:
    // GE that applies IncomingHeal
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal")
    TSubclassOf<UGameplayEffect> HealEffectClass;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal")
    float HealAmount = 30.f;

    // How far the healer can reach
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal")
    float HealRange = 1000.f;
};