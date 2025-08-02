// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"

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
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

