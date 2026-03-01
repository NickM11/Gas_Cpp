#include "GASAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UGASAttributeSet::UGASAttributeSet()
{
    InitHealth(100.f);
    InitMaxHealth(100.f);
    InitIncomingDamage(0.f);
    InitIncomingHeal(0.f);
}

void UGASAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UGASAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (Attribute == GetHealthAttribute())
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
}

void UGASAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
    {
        float Damage = GetIncomingDamage();
        SetIncomingDamage(0.f);
        if (Damage > 0.f)
        {
            float NewHealth = FMath::Clamp(GetHealth() - Damage, 0.f, GetMaxHealth());
            SetHealth(NewHealth);
            UE_LOG(LogTemp, Log, TEXT("[GAS] Damage applied: %.1f | Health: %.1f"), Damage, NewHealth);
        }
    }
    else if (Data.EvaluatedData.Attribute == GetIncomingHealAttribute())
    {
        float Heal = GetIncomingHeal();
        SetIncomingHeal(0.f);
        if (Heal > 0.f)
        {
            float NewHealth = FMath::Clamp(GetHealth() + Heal, 0.f, GetMaxHealth());
            SetHealth(NewHealth);
            UE_LOG(LogTemp, Log, TEXT("[GAS] Heal applied: %.1f | Health: %.1f"), Heal, NewHealth);
        }
    }
}

void UGASAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Health, OldHealth);
}

void UGASAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MaxHealth, OldMaxHealth);
}