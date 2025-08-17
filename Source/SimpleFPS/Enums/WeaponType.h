#pragma once

#include "CoreMinimal.h"
#include "WeaponType.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Unarmed UMETA(DisplayName = "Unarmed"),
    Pistol UMETA(DisplayName = "Pistol"),
    SMG UMETA(DisplayName = "SMG"),
    AssaultRifle UMETA(DisplayName = "Assault Rifle")
};