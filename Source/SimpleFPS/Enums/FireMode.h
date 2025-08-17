#pragma once

#include "CoreMinimal.h"
#include "FireMode.generated.h"

UENUM(BlueprintType)
enum class EFireMode : uint8
{
    SemiAuto UMETA(DisplayName = "Semi Auto"),
    FullAuto UMETA(DisplayName = "Full Auto")
};