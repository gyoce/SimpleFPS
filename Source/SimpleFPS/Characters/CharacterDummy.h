// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../CombatInterface.h"
#include "CharacterDummy.generated.h"

UCLASS()
class SIMPLEFPS_API ACharacterDummy : public ACharacter, public ICombatInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ACharacterDummy();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
    virtual float GetDamageBoneModifier(const FName& BoneName) override;

private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<class UUserWidget> DamageWidgetClass;

    UPROPERTY()
    class UDamageUserWidget* DamageWidget;

    UPROPERTY(EditAnywhere)
    TMap<FName, float> BoneDamageModifiers;
};
