// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"

#include "../Characters/SimpleFPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

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
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
    Super::BeginPlay();
    CurrentAmmo = MaxAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
    if (CanFireGun())
    {
        APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
        if (PlayerCameraManager == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("PlayerCameraManager is null in AGun::PullTrigger"));
            return;
        }

        UE_LOG(LogTemp, Warning, TEXT("Fire!"));

        FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
        FVector CameraForwardWithRange = PlayerCameraManager->GetActorForwardVector() * Range;
        FVector EndPoint = CameraLocation + CameraForwardWithRange;

        FHitResult Hit;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);
        CollisionParams.AddIgnoredActor(GetOwner());
        bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel2, CollisionParams);
        DrawDebugLine(GetWorld(), CameraLocation, EndPoint, FColor::Green, true);
        if (bHit)
        {
            UE_LOG(LogTemp, Warning, TEXT("HIT HIT HIT HIT %s -> %s"), *CameraLocation.ToString(), *Hit.Location.ToString());
            DrawDebugLine(GetWorld(), CameraLocation, Hit.Location, FColor::Red, true);
        }
    }
}

bool AGun::CanFireGun() const
{
    return CurrentAmmo > 0;
}

