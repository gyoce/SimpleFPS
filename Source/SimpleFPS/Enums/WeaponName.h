#pragma once

#include "CoreMinimal.h"
#include "WeaponName.generated.h"

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
    Unarmed UMETA(DisplayName = "Unarmed"),
    Pistol_A UMETA(DisplayName = "Pistol_A"),
    Assault_Rifle_A UMETA(DisplayName = "Assault_Rifle_A"),
};