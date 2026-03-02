#pragma once
#include "CoreMinimal.h"
#include "GASGameplayAbility.h"
#include "GA_DamageAbility.generated.h"

UCLASS()
class GAS_CPP_API UGA_DamageAbility : public UGASGameplayAbility
{
    GENERATED_BODY()

public:
    UGA_DamageAbility();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
    TSubclassOf<UGameplayEffect> DamageEffectClass;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
    float DamageAmount = 25.f;

    // Raycast range for hit target
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Damage")
    float AttackRange = 1500.f;
};