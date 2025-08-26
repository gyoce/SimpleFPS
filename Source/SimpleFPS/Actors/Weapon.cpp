#include "Weapon.h"

#include "DrawDebugHelpers.h"

const FName AWeapon::BarrelSocketName = TEXT("barrel");
const FName AWeapon::LhikSocketName = TEXT("LHIK");

AWeapon::AWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeapon::Shoot()
{
    Mesh->PlayAnimation(GetFiringAnimation(), false);

    FTransform SocketTransform = Mesh->GetSocketTransform(AWeapon::BarrelSocketName);
    FVector Start = SocketTransform.GetLocation();
    FVector End = Start + SocketTransform.GetRotation().GetForwardVector() * GetRange();
    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.bTraceComplex = true;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);

    if (bHit)
        DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5.f), FColor::Red, false, 2.0f);
}

FTransform AWeapon::GetLhikTransform()
{
    return Mesh->GetSocketTransform(AWeapon::LhikSocketName);
}