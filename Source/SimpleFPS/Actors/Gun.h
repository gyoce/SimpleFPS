#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLEFPS_API AGun : public AActor
{
    GENERATED_BODY()
    
public:	
    AGun();

protected:
    virtual void BeginPlay() override;

public:	
    virtual void Tick(float DeltaTime) override;

    void PullTrigger();

    UFUNCTION(BlueprintImplementableEvent, Category = Gun)
    void OnGunFired();

private:
    float ComputeDamage();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* GunMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* GunMagazine;

    UPROPERTY(EditAnywhere, Category = Gun)
    int CurrentAmmo;

    UPROPERTY(EditAnywhere, Category = Gun)
    int MaxAmmo = 30;

    UPROPERTY(EditAnywhere, Category = Gun)
    float Damage = 20;

    UPROPERTY(EditAnywhere, Category = Gun)
    float Range = 10000.0f;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class ASimpleFPSCharacter* ParentFpsCharacter = nullptr;

    class APlayerCameraManager* PlayerCameraManager = nullptr;
    struct FCollisionQueryParams CollisionQueryParams;
    AController* OwnerController = nullptr;

    class UAttributeComponent* PlayersAttribute = nullptr;

    AController* GetOwnerController();
    bool CanFireGun() const;
};
