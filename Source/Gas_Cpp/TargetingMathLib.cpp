#include "TargetingMathLib.h"
#include "GameFramework/Actor.h"

bool UTargetingMathLib::ComputeTargetInfo(
    const AActor* Owner,
    const AActor* Target,
    FVector& OutDirectionToTarget,
    float& OutAngleDeg,
    ESideRelativeToOwner& OutSide,
    float ColinearTolerance
)
{
    OutDirectionToTarget = FVector::ZeroVector;
    OutAngleDeg = 0.f;
    OutSide = ESideRelativeToOwner::Center;

    if (!Owner || !Target) return false;

    const FVector OwnerLoc = Owner->GetActorLocation();
    const FVector TargetLoc = Target->GetActorLocation();

    const FVector ToTarget = TargetLoc - OwnerLoc;
    if (ToTarget.IsNearlyZero())
    {
        // Target on the same point
        return true;
    }

    OutDirectionToTarget = ToTarget.GetSafeNormal();

    const FVector Forward = Owner->GetActorForwardVector().GetSafeNormal();
    const FVector Up = Owner->GetActorUpVector().GetSafeNormal(); // ??? FVector::UpVector ??? world-up

    // Angle 0..180
    const float Dot = FMath::Clamp(FVector::DotProduct(Forward, OutDirectionToTarget), -1.f, 1.f);
    OutAngleDeg = FMath::RadiansToDegrees(FMath::Acos(Dot));

    // Left/Right sign
    const FVector Cross = FVector::CrossProduct(Forward, OutDirectionToTarget);
    const float Sign = FVector::DotProduct(Cross, Up);

    if (FMath::Abs(Sign) <= ColinearTolerance)
    {
        OutSide = ESideRelativeToOwner::Center; // almost straight or opposite
    }
    else if (Sign > 0.f)
    {
        OutSide = ESideRelativeToOwner::Left;
    }
    else
    {
        OutSide = ESideRelativeToOwner::Right;
    }

    return true;
}