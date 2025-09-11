#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractInterface.h"
#include "WeaponPickup.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AWeapon;

UCLASS()
class SIMPLEFPS_API AWeaponPickup : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	AWeaponPickup();

    virtual void Tick(float DeltaTime) override;

    virtual void Interact(class AMainPlayerCharacter* CharacterPickingUp) override;

    UFUNCTION(BlueprintImplementableEvent)
    void SetInteractable(bool bInteractable);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* PickupObjectMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = "true"))
    USphereComponent* PickupRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AWeapon> WeaponToSpawn;
};
