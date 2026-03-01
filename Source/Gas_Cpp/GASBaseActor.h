#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h" 
#include "GASBaseActor.generated.h"

class UAbilitySystemComponent;
class UGASAttributeSet;
class UGASGameplayAbility;

UCLASS()
class GAS_CPP_API AGASBaseActor : public AActor, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AGASBaseActor();

    // IAbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable)
    float GetHealth() const;

    UFUNCTION(BlueprintCallable)
    float GetMaxHealth() const;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY()
    UGASAttributeSet* AttributeSet;

    // Abilities granted at start
    UPROPERTY(EditDefaultsOnly, Category = "GAS")
    TArray<TSubclassOf<UGASGameplayAbility>> DefaultAbilities;

    // Gameplay Effects applied at start (e.g., initialize stats)
    UPROPERTY(EditDefaultsOnly, Category = "GAS")
    TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

    void GrantDefaultAbilities();
    void ApplyDefaultEffects();
};