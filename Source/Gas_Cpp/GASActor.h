// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"      // Add this
#include "GasTestAttributeSet.h"         // Add this
#include "GASActor.generated.h"

UCLASS()
class GAS_CPP_API AGASActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGASActor();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UAbilitySystemComponent* GASComponent;

	UPROPERTY()

	UGasTestAttributeSet* GasTestAttributeSet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
