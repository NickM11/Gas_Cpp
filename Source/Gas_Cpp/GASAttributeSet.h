#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASAttributeSet.generated.h"

// Helper macro - auto-generates Getter/Setter/Initter
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAS_CPP_API UGASAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UGASAttributeSet();

    // Health
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health)

        UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxHealth)

        // Meta attribute — damage/heal applied through this
        UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData IncomingDamage;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, IncomingDamage)

        UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData IncomingHeal;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, IncomingHeal)

        virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

protected:
    UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
    UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
};