// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLEFPS_API AGun : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AGun();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void PullTrigger();

private:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* GunMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* GunMagazine;

    UPROPERTY(EditAnywhere)
    int CurrentAmmo;

    UPROPERTY(EditAnywhere)
    int MaxAmmo = 30;

    UPROPERTY(EditAnywhere)
    float Damage = 20;

    UPROPERTY(EditAnywhere)
    float Range = 10000.0f;

    // Cache variables
    class APlayerCameraManager* PlayerCameraManager;
    struct FCollisionQueryParams CollisionQueryParams;
    AController* OwnerController = nullptr;

    AController* GetOwnerController();

    bool CanFireGun() const;
};
