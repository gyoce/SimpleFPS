#pragma once

#include "CoreMinimal.h"
#include "WeaponName.generated.h"

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
    Unarmed UMETA(DisplayName = "Unarmed"),
    Pistol UMETA(DisplayName = "Pistol"),
    AK47 UMETA(DisplayName = "AK-47")
};