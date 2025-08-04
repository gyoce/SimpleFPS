// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"

#include "../Characters/SimpleFPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = MaxAmmo;

    PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
    if (PlayerCameraManager == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCameraManager is null in AGun::BeginPlay"));
        return;
    }
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
    if (!CanFireGun())
        return;

    UE_LOG(LogTemp, Warning, TEXT("Fire!"));

    FVector StartPoint = PlayerCameraManager->GetCameraLocation();
    FVector StartPointWithRange = PlayerCameraManager->GetActorForwardVector() * Range;
    FVector EndPoint = StartPoint + StartPointWithRange;

    FHitResult Hit;
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_GameTraceChannel2, CollisionQueryParams);
    DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, true);
    if (bHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("HIT!"));
        DrawDebugLine(GetWorld(), StartPoint, Hit.Location, FColor::Red, true);
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            FVector HitDirection = (Hit.TraceEnd - Hit.TraceStart).GetSafeNormal();
            FPointDamageEvent DamageEvent(Damage, Hit, HitDirection, nullptr);
            HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
        }
    }
}

AController* AGun::GetOwnerController()
{
    if (OwnerController)
        return OwnerController;

    if (GetOwner() == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("GetOwner is null in AGun::GetOwnerController"));
        return nullptr;
    }
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("OwnerPawn is null in AGun::GetOwnerController"));
        return nullptr;
    }
    OwnerController = OwnerPawn->GetController();
    if (OwnerController == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("OwnerController is null in AGun::GetOwnerController"));
        return nullptr;
    }

    CollisionQueryParams.AddIgnoredActor(GetOwner());

    return OwnerController;
}

bool AGun::CanFireGun() const
{
    return CurrentAmmo > 0;
}

