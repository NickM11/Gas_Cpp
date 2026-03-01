// Fill out your copyright notice in the Description page of Project Settings.


#include "GASActor.h"

// Sets default values
AGASActor::AGASActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GASComponent = CreateDefaultSubobject<UAbilitySystemComponent>("GASComponent");

	GasTestAttributeSet = CreateDefaultSubobject<UGasTestAttributeSet>("GasTestAttributeSet");

}

UAbilitySystemComponent* AGASActor::GetAbilitySystemComponent() const
{
	return GASComponent;
}

// Called when the game starts or when spawned
void AGASActor::BeginPlay()
{
	GASComponent->InitAbilityActorInfo(this,this);
	Super::BeginPlay();
	
}

// Called every frame
void AGASActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGASActor::ActivateDashAbility()
{
	if (!TestDashAbility) return false;

	FGameplayAbilitySpecHandle Handle = GASComponent->GiveAbility(
		FGameplayAbilitySpec(TestDashAbility, 1, 0));

	return GASComponent->TryActivateAbility(Handle);
}

