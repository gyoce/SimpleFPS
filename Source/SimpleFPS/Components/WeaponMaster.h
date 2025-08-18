#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Enums/WeaponName.h"
#include "../Enums/WeaponType.h"
#include "../Enums/FireMode.h"
#include "WeaponMaster.generated.h"

class AWeaponPickup;

UCLASS()
class SIMPLEFPS_API UWeaponMaster : public USkeletalMeshComponent
{
    GENERATED_BODY()

public:
    UWeaponMaster();

    TSubclassOf<AWeaponPickup> GetPickupClass() const { return PickupClass; }
    FName GetSocketName() const { return SocketName; }
    EWeaponName GetWeaponName() const { return WeaponName; }
    UAnimSequence* GetFiringAnimation() const { return FiringAnimation; }
    float GetRange() const { return Range; }

    static const FName BarrelSocketName;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    UAnimSequence* FiringAnimation;
};
