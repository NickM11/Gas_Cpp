#pragma once
#include "CoreMinimal.h"
#include "GASGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
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

    virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        bool bReplicateCancelAbility) override;

protected:
    // Assign your heal montage here in Blueprint subclass
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal|Animation")
    UAnimMontage* HealMontage;

    // Optional: which montage section to play
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal|Animation")
    FName MontageSectionName = NAME_None;

    // Playback rate of the montage
    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal|Animation")
    float MontagePlayRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal")
    TSubclassOf<UGameplayEffect> HealEffectClass;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal")
    float HealAmount = 30.f;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Heal")
    float HealRange = 1000.f;

private:
    void ApplyHealToTargets(const FGameplayAbilityActorInfo* ActorInfo);

    UFUNCTION()
    void OnMontageCompleted();

    UFUNCTION()
    void OnMontageInterrupted();

    UFUNCTION()
    void OnMontageCancelled();
};