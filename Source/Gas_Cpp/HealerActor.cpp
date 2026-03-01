#include "HealerActor.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"

AHealerActor::AHealerActor()
{
    HealAbilityTag = FGameplayTag::RequestGameplayTag(FName("Ability.Heal"));
}

void AHealerActor::TryHeal()
{
    if (AbilitySystemComponent)
    {
        FGameplayTagContainer AbilityTags;
        AbilityTags.AddTag(HealAbilityTag);
        AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags);
    }
}