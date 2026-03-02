#include "GA_HealAbility.h"
#include "AbilitySystemComponent.h"
#include "Engine/OverlapResult.h"
#include "AbilitySystemBlueprintLibrary.h"

UGA_HealAbility::UGA_HealAbility()
{
    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Heal")));
}

void UGA_HealAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

    // Sphere trace to find nearby targets
    AActor* Owner = ActorInfo->OwnerActor.Get();
    if (!Owner || !HealEffectClass)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    Owner->GetWorld()->OverlapMultiByChannel(
        Overlaps,
        Owner->GetActorLocation(),
        FQuat::Identity,
        ECC_Pawn,
        FCollisionShape::MakeSphere(HealRange),
        Params
    );

    for (const FOverlapResult& Overlap : Overlaps)
    {
        UAbilitySystemComponent* TargetASC =
            UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Overlap.GetActor());

        if (TargetASC)
        {
            FGameplayEffectContextHandle Context = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
            Context.AddSourceObject(Owner);

            FGameplayEffectSpecHandle SpecHandle =
                GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
                    HealEffectClass, GetAbilityLevel(), Context);

            if (SpecHandle.IsValid())
            {
                // Pass heal amount as SetByCaller
                UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
                    SpecHandle,
                    FGameplayTag::RequestGameplayTag(FName("Data.Heal")),
                    HealAmount);

                GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
                    *SpecHandle.Data.Get(), TargetASC);
            }
        }
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}