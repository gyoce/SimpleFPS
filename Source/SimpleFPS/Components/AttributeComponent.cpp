// Fill out your copyright notice in the Description page of Project Settings.
#include "AttributeComponent.h"

#include "../Characters/SimpleFPSCharacter.h"

UAttributeComponent::UAttributeComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    Stamina = MaxStamina;

    SetComponentTickInterval(1.0f);
}

void UAttributeComponent::BeginPlay()
{
    Super::BeginPlay();

    Character = Cast<ASimpleFPSCharacter>(GetOwner());
    if (Character != nullptr)
        Character->OnSprint.AddDynamic(this, &UAttributeComponent::HandleOnSprint);
    else
        UE_LOG(LogTemp, Error, TEXT("AttributeComponent: Failed to find Character!"));
}

void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UE_LOG(LogTemp, Log, TEXT("Stamina: %.2f"), Stamina);

    if (bIsExhausted)
        return;

    float LastStamina = Stamina;

    if (bIsSprinting)
        Stamina = FMath::Clamp(Stamina - StaminaConsumeRate, 0.0f, MaxStamina);
    else
        Stamina = FMath::Clamp(Stamina + StaminaRegenRate, 0.0f, MaxStamina);

    if (!FMath::IsNearlyEqual(LastStamina, Stamina))
        OnStaminaChanged.Broadcast(Stamina);

    if (Stamina <= 0.0f)
    {
        bIsExhausted = true;
        Character->StopSprint();
        GetWorld()->GetTimerManager().SetTimer(ClearExhaustionTimerHandle, this, &UAttributeComponent::ClearExhaustion, StaminaClearExhaustionTime, false);
    }
}

void UAttributeComponent::HandleOnSprint(bool IsSprinting)
{
    bIsSprinting = IsSprinting;
}

void UAttributeComponent::ClearExhaustion()
{
    bIsExhausted = false;
}
