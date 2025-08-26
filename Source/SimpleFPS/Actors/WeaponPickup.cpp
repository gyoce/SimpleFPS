#include "WeaponPickup.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "../Characters/MainPlayerCharacter.h"
#include "../Actors/Weapon.h"

AWeaponPickup::AWeaponPickup()
{
    PrimaryActorTick.bCanEverTick = false;

    PickupObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Object"));
    PickupObjectMesh->SetSimulatePhysics(true);
    PickupObjectMesh->SetMassOverrideInKg(NAME_None, 60.f, true);
    PickupObjectMesh->SetLinearDamping(0.25f);
    PickupObjectMesh->SetAngularDamping(0.25f);
    SetRootComponent(PickupObjectMesh);

    PickupRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Radius"));
    PickupRadius->SetSphereRadius(100.f);
    PickupRadius->SetupAttachment(PickupObjectMesh);
}

void AWeaponPickup::BeginPlay()
{
    Super::BeginPlay();
}

void AWeaponPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeaponPickup::Interact(AMainPlayerCharacter* CharacterPickingUp)
{
    CharacterPickingUp->SpawnWeapon(WeaponToSpawn, GetActorLocation());
    Destroy();
}
