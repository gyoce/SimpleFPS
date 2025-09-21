#include "Weapon.h"

#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

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

AController* AWeapon::GetOwnerController()
{
    if (OwnerController != nullptr)
        return OwnerController;

    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr)
        return nullptr;
    OwnerController = OwnerPawn->GetController();
    return OwnerController;
}

void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeapon::Shoot(FVector StartLocation, FVector Direction)
{
    Mesh->PlayAnimation(GetFiringAnimation(), false);

    FVector End = StartLocation + Direction * Range;
    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.bTraceComplex = true;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, End, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
    DrawDebugLine(GetWorld(), StartLocation, End, FColor::Red, false, 2.0f);

    if (bHit)
    {
        DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5.f), FColor::Red, false, 2.0f);
        AActor* HitActor = HitResult.GetActor();
        if (HitActor != nullptr)
        {
            FPointDamageEvent DamageEvent(Damage, HitResult, End, nullptr);
            HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
        }
    }
}

FTransform AWeapon::GetLhikTransform()
{
    return Mesh->GetSocketTransform(AWeapon::LhikSocketName);
}