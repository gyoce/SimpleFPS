// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterDummy.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/DamageUserWidget.h"
#include "Engine/DamageEvents.h"
#include "Components/TextBlock.h"

// Sets default values
ACharacterDummy::ACharacterDummy()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterDummy::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACharacterDummy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterDummy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ACharacterDummy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
        
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    UUserWidget* UserDamageWidget = CreateWidget(PlayerController, DamageWidgetClass);
    DamageWidget = Cast<UDamageUserWidget>(UserDamageWidget);
    check(DamageWidget);

    FVector2D ScreenPosition;
    FVector RandomLocation = GetActorLocation() + FMath::VRand() * FMath::FRandRange(0, 50.0f);
    UGameplayStatics::ProjectWorldToScreen(PlayerController, RandomLocation, ScreenPosition);
    DamageWidget->DamagePosition = ScreenPosition;
    DamageWidget->Damage = Damage;
    DamageWidget->AddToViewport();

    return Damage;
}
