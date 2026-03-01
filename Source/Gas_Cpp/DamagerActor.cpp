#include "DamagerActor.h"
#include "AbilitySystemComponent.h"

ADamagerActor::ADamagerActor()
{
    DamageAbilityTag = FGameplayTag::RequestGameplayTag(FName("Ability.Damage"));
}

void ADamagerActor::TryAttack()
{
    if (AbilitySystemComponent)
    {
        FGameplayTagContainer AbilityTags;
        AbilityTags.AddTag(DamageAbilityTag);
        AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags);
    }
}