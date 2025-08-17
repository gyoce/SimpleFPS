#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "../Enums/WeaponName.h"
#include "../Enums/WeaponType.h"
#include "../Enums/FireMode.h"
#include "WeaponMaster.generated.h"

class AWeaponPickup;

UCLASS()
class SIMPLEFPS_API UWeaponMaster : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    UWeaponMaster();

    TSubclassOf<AWeaponPickup> GetPickupClass() const { return PickupClass; }
    FName GetSocketName() const { return SocketName; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    float Range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    EWeaponName WeaponName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AWeaponPickup> PickupClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    FName SocketName;
};
