#pragma once

#include "CoreMinimal.h"
#include "WeaponClass.generated.h"

UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
    Unarmed UMETA(DisplayName = "Unarmed"),
    Primary UMETA(DisplayName = "Primary"),
    Secondary UMETA(DisplayName = "Secondary"),
};