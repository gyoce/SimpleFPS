// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, Stamina);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEFPS_API UAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    // Sets default values for this component's properties
    UAttributeComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStaminaChanged OnStaminaChanged;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
    float Stamina;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
    float MaxStamina = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
    float StaminaRegenRate = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
    float StaminaConsumeRate = 20.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
    float StaminaClearExhaustionTime = 3.0f;

private:
    UFUNCTION()
    void HandleOnSprint(bool IsSprinting);
    
    void ClearExhaustion();

    bool bIsSprinting = false;
    bool bIsExhausted = false;
    
    class ASimpleFPSCharacter* Character;
    FTimerHandle ClearExhaustionTimerHandle;
};
