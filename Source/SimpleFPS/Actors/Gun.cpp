// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"

#include "../Characters/SimpleFPSCharacter.h"
#include "../Components/AttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

static const ECollisionChannel BulletChannel = ECollisionChannel::ECC_GameTraceChannel2;

AGun::AGun()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
    GunMesh->SetupAttachment(Root);
    GunMesh->SetCollisionProfileName(TEXT("OverlapAll"));
        
    GunMagazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMagazine"));
    GunMagazine->SetupAttachment(GunMesh);
    GunMagazine->SetCollisionProfileName(TEXT("OverlapAll"));
    
    CollisionQueryParams.AddIgnoredActor(this);
}

void AGun::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = MaxAmmo;

    PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
    check(PlayerCameraManager);

    AActor* ParentActor = GetParentActor();
    check(ParentActor);
    ParentFpsCharacter = Cast<ASimpleFPSCharacter>(ParentActor);
    check(ParentFpsCharacter);

    PlayersAttribute = ParentActor->GetComponentByClass<UAttributeComponent>();
    check(PlayersAttribute);
}

void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
    if (!CanFireGun())
        return;
    UE_LOG(LogTemp, Warning, TEXT("Gun class at runtime: %s"), *GetClass()->GetName());

    UE_LOG(LogTemp, Warning, TEXT("Fire!"));
    OnGunFired();

    FVector StartPoint = PlayerCameraManager->GetCameraLocation();
    FVector StartPointWithRange = PlayerCameraManager->GetActorForwardVector() * Range;
    FVector EndPoint = StartPoint + StartPointWithRange;

    FHitResult Hit;
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, BulletChannel, CollisionQueryParams);
    DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, true);
    if (bHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("HIT!"));
        float DamageToApply = ComputeDamage();
        DrawDebugLine(GetWorld(), StartPoint, Hit.Location, FColor::Red, true);
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            FVector HitDirection = (Hit.TraceEnd - Hit.TraceStart).GetSafeNormal();
            FPointDamageEvent DamageEvent(DamageToApply, Hit, HitDirection, nullptr);
            HitActor->TakeDamage(DamageToApply, DamageEvent, GetOwnerController(), this);
        }
    }
}

float AGun::ComputeDamage()
{
    float DamageToApply = Damage;
    DamageToApply *= (UKismetMathLibrary::NormalizeToRange(PlayersAttribute->Strength, 0.0f, 255.0f) + 1.0f);
    DamageToApply = UKismetMathLibrary::Lerp(Damage * 0.95f, Damage * 1.05f, FMath::FRand());
    return DamageToApply;
}

AController* AGun::GetOwnerController()
{
    if (OwnerController)
        return OwnerController;

    check(GetOwner());
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    check(OwnerPawn);
    OwnerController = OwnerPawn->GetController();
    check(OwnerController);

    CollisionQueryParams.AddIgnoredActor(GetOwner());

    return OwnerController;
}

bool AGun::CanFireGun() const
{
    return CurrentAmmo > 0;
}