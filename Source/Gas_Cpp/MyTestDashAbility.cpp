// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestDashAbility.h"

UMyTestDashAbility::UMyTestDashAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	DashSpeed = 100;
}

bool UMyTestDashAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{

	AActor* Avatar = ActorInfo->AvatarActor.Get();
	if (!Avatar) {
		return false;
	}
	return Super::CanActivateAbility(Handle,ActorInfo,SourceTags,TargetTags,OptionalRelevantTags);
}

void UMyTestDashAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	AActor* Avatar = ActorInfo->AvatarActor.Get();

	FVector Direction = Avatar->GetActorForwardVector();

	Avatar->AddActorLocalOffset(Direction * DashSpeed);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
