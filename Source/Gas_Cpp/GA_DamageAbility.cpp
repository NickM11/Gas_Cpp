#include "GA_DamageAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UGA_DamageAbility::UGA_DamageAbility()
{
    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Damage")));
}

void UGA_DamageAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    AActor* Owner = ActorInfo->OwnerActor.Get();
    if (!Owner || !DamageEffectClass)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    // Line trace from actor forward
    FVector Start = Owner->GetActorLocation();
    FVector End = Start + Owner->GetActorForwardVector() * AttackRange;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    if (Owner->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params))
    {
        UAbilitySystemComponent* TargetASC =
            UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Hit.GetActor());

        if (TargetASC)
        {
            FGameplayEffectContextHandle Context =
                GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
            Context.AddSourceObject(Owner);

            FGameplayEffectSpecHandle SpecHandle =
                GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
                    DamageEffectClass, GetAbilityLevel(), Context);

            if (SpecHandle.IsValid())
            {
                UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
                    SpecHandle,
                    FGameplayTag::RequestGameplayTag(FName("Data.Damage")),
                    DamageAmount);

                GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
                    *SpecHandle.Data.Get(), TargetASC);
            }
        }
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}