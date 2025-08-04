// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageUserWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SIMPLEFPS_API UDamageUserWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UDamageUserWidget(const FObjectInitializer& ObjectInitializer);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D DamagePosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage;
};
