// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterDummy.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/DamageUserWidget.h"
#include "Engine/DamageEvents.h"
#include "Components/TextBlock.h"
#include "../Components/CombatComponent.h"

ACharacterDummy::ACharacterDummy()
{
    PrimaryActorTick.bCanEverTick = false;

    CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

void ACharacterDummy::BeginPlay()
{
    Super::BeginPlay();
}

void ACharacterDummy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

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

    if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
    {
        const FPointDamageEvent* PointDamageEvent = static_cast<const FPointDamageEvent*>(&DamageEvent);
        check(PointDamageEvent);
        UE_LOG(LogTemp, Warning, TEXT("Bone name hit : %s"), *PointDamageEvent->HitInfo.BoneName.ToString());
        Damage *= GetDamageBoneModifier(PointDamageEvent->HitInfo.BoneName);
    }

    FVector2D ScreenPosition;
    FVector RandomLocation = GetActorLocation() + FMath::VRand() * FMath::FRandRange(0, 50.0f);
    UGameplayStatics::ProjectWorldToScreen(PlayerController, RandomLocation, ScreenPosition);
    DamageWidget->DamagePosition = ScreenPosition;
    DamageWidget->Damage = Damage;
    DamageWidget->AddToViewport();

    return Damage;
}

float ACharacterDummy::GetDamageBoneModifier(const FName& BoneName)
{
    float* Value = CombatComponent->BoneDamageModifiers.Find(BoneName);
    return Value == nullptr ? 1.0f : *Value;
}
