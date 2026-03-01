#include "GASBaseActor.h"
#include "AbilitySystemComponent.h"
#include "GASAttributeSet.h"
#include "GASGameplayAbility.h"

AGASBaseActor::AGASBaseActor()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AGASBaseActor::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AGASBaseActor::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        GrantDefaultAbilities();
        ApplyDefaultEffects();
    }
}

void AGASBaseActor::GrantDefaultAbilities()
{
    for (TSubclassOf<UGASGameplayAbility>& AbilityClass : DefaultAbilities)
    {
        if (AbilityClass)
        {
            FGameplayAbilitySpec Spec(AbilityClass, 1, INDEX_NONE, this);
            AbilitySystemComponent->GiveAbility(Spec);
        }
    }
}

void AGASBaseActor::ApplyDefaultEffects()
{
    FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
    Context.AddSourceObject(this);

    for (TSubclassOf<UGameplayEffect>& EffectClass : DefaultEffects)
    {
        if (EffectClass)
        {
            FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, Context);
            if (Spec.IsValid())
                AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
        }
    }
}

float AGASBaseActor::GetHealth() const
{
    return AttributeSet ? AttributeSet->GetHealth() : 0.f;
}

float AGASBaseActor::GetMaxHealth() const
{
    return AttributeSet ? AttributeSet->GetMaxHealth() : 0.f;
}