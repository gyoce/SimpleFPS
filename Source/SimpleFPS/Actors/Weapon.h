#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Enums/WeaponName.h"
#include "../Enums/WeaponType.h"
#include "../Enums/WeaponClass.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class AWeaponPickup;

UCLASS()
class SIMPLEFPS_API AWeapon : public AActor
{
    GENERATED_BODY()
    
public:	
    AWeapon();

    virtual void Tick(float DeltaTime) override;

    virtual void Shoot(FVector StartLocation, FVector Direction);

    TSubclassOf<AWeaponPickup> GetPickupClass() const { return PickupClass; }
    FName GetSocketName() const { return SocketName; }
    EWeaponName GetWeaponName() const { return WeaponName; }
    UAnimSequence* GetFiringAnimation() const { return FiringAnimation; }
    EWeaponClass GetWeaponClass() const { return WeaponClass; }

    FTransform GetLhikTransform();

    static const FName BarrelSocketName;
    static const FName LhikSocketName;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    float Range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    EWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    EWeaponName WeaponName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    EWeaponClass WeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AWeaponPickup> PickupClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    FName SocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    UAnimSequence* FiringAnimation;
};
