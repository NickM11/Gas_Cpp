// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"      // Add this
#include "GasTestAttributeSet.h"         // Add this
#include "MyTestDashAbility.h"
#include "GASActor.generated.h"

UCLASS()
class GAS_CPP_API AGASActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGASActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UAbilitySystemComponent* GASComponent;

	UPROPERTY()

	UGasTestAttributeSet* GasTestAttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UMyTestDashAbility> TestDashAbility;

public:	
	// Called every frame
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool ActivateDashAbility();

};
