#include "GA_HealAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"  // ← key include

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

    // If no montage assigned, apply heal immediately and exit
    if (!HealMontage)
    {
        ApplyHealToTargets(ActorInfo);
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    // Create the PlayMontageAndWait task
    UAbilityTask_PlayMontageAndWait* MontageTask =
        UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
            this,                  // owning ability
            FName("HealMontage"),  // task instance name
            HealMontage,           // montage asset
            MontagePlayRate,       // play rate
            MontageSectionName,    // section (NAME_None = start)
            false                  // stop when ability ends
        );

    // Bind all completion/interruption delegates
    MontageTask->OnCompleted.AddDynamic(this, &UGA_HealAbility::OnMontageCompleted);
    MontageTask->OnBlendOut.AddDynamic(this, &UGA_HealAbility::OnMontageCompleted);
    MontageTask->OnInterrupted.AddDynamic(this, &UGA_HealAbility::OnMontageInterrupted);
    MontageTask->OnCancelled.AddDynamic(this, &UGA_HealAbility::OnMontageCancelled);

    MontageTask->ReadyForActivation();

    // Apply heal immediately when montage starts playing
    ApplyHealToTargets(ActorInfo);
}

void UGA_HealAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateCancelAbility)
{
    // Stop the montage cleanly on cancel
    if (ActorInfo)
    {
        UAnimInstance* AnimInstance =
            ActorInfo->GetAnimInstance();

        if (AnimInstance && HealMontage)
            AnimInstance->Montage_Stop(0.25f, HealMontage); // 0.25s blend out
    }

    Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UGA_HealAbility::ApplyHealToTargets(const FGameplayAbilityActorInfo* ActorInfo)
{
    AActor* Owner = ActorInfo->OwnerActor.Get();
    if (!Owner || !HealEffectClass) return;

    TArray<AActor*> OverlappingActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    UKismetSystemLibrary::SphereOverlapActors(
        Owner->GetWorld(),
        Owner->GetActorLocation(),
        HealRange,
        ObjectTypes,
        nullptr,
        TArray<AActor*>{ Owner },
        OverlappingActors
    );

    for (AActor* TargetActor : OverlappingActors)
    {
        UAbilitySystemComponent* TargetASC =
            UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

        if (!TargetASC) continue;

        FGameplayEffectContextHandle Context =
            GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
        Context.AddSourceObject(Owner);

        FGameplayEffectSpecHandle SpecHandle =
            GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
                HealEffectClass, GetAbilityLevel(), Context);

        if (SpecHandle.IsValid())
        {
            UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
                SpecHandle,
                FGameplayTag::RequestGameplayTag(FName("Data.Heal")),
                HealAmount);

            GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
                *SpecHandle.Data.Get(), TargetASC);
        }
    }
}

// ── Montage callbacks ──────────────────────────────────────────────

void UGA_HealAbility::OnMontageCompleted()
{
    if (IsActive())
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_HealAbility::OnMontageInterrupted()
{
    if (IsActive())
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_HealAbility::OnMontageCancelled()
{
    if (IsActive())
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}