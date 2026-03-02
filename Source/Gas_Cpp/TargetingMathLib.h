#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TargetingMathLib.generated.h"

UENUM(BlueprintType)
enum class ESideRelativeToOwner : uint8
{
    Center UMETA(DisplayName = "Center/Colinear"),
    Left   UMETA(DisplayName = "Left"),
    Right  UMETA(DisplayName = "Right")
};

UCLASS()
class GAS_CPP_API UTargetingMathLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Targeting|Math")
    static bool ComputeTargetInfo(
        const AActor* Owner,
        const AActor* Target,
        FVector& OutDirectionToTarget,
        float& OutAngleDeg,
        ESideRelativeToOwner& OutSide,
        float ColinearTolerance = 1e-4f
    );
};