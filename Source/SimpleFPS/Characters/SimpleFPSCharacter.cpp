// Copyright Epic Games, Inc. All Rights Reserved.
#include "SimpleFPSCharacter.h"
#include "../Actors/SimpleFPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "../Components/AttributeComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Actors/Gun.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASimpleFPSCharacter::ASimpleFPSCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(40.f, 96.0f);
        
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->SetRelativeLocation(FVector(-30.f, 0.f, 60.f)); // Position the camera
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
    Mesh1P->SetOnlyOwnerSee(true);
    Mesh1P->SetupAttachment(FirstPersonCameraComponent);
    Mesh1P->bCastDynamicShadow = false;
    Mesh1P->CastShadow = false;
    Mesh1P->SetRelativeLocation(FVector(-10.f, 0.f, -150.f));

    Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("Gun"));
    Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));

    AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
}

void ASimpleFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

    CameraShakeStepInstance = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(CameraShakeStep, 1.0f);
    if (CameraShakeStepInstance)
        CameraShakeStepInstance->ShakeScale = 0.0f;
    else
        UE_LOG(LogTemp, Error, TEXT("Failed to start camera shake instance."));

    GunActor = Cast<AGun>(Gun->GetChildActor());
    if (GunActor != nullptr)
        GunActor->SetOwner(this);
    else
        UE_LOG(LogTemp, Error, TEXT("Failed to cast Gun child actor to AGun"));
}

void ASimpleFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASimpleFPSCharacter::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ASimpleFPSCharacter::StopMove);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASimpleFPSCharacter::StopMove);

        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASimpleFPSCharacter::Look);

        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ASimpleFPSCharacter::StartCrouch);
        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ASimpleFPSCharacter::StopCrouch);
        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Canceled, this, &ASimpleFPSCharacter::StopCrouch);
    
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASimpleFPSCharacter::StartSprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASimpleFPSCharacter::StopSprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ASimpleFPSCharacter::StopSprint);

        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ASimpleFPSCharacter::Shoot);
    }
    else
    {
        UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
    }
}

void ASimpleFPSCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);

        if (CameraShakeStepInstance)
            CameraShakeStepInstance->ShakeScale = GetCharacterMovement()->IsFalling() ? 0.0f : 1.0f;
    }
}

void ASimpleFPSCharacter::StopMove(const FInputActionValue& Value)
{
    if (CameraShakeStepInstance)
        CameraShakeStepInstance->ShakeScale = 0.0f;
}

void ASimpleFPSCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ASimpleFPSCharacter::StartCrouch(const FInputActionValue&)
{
    Crouch();
    FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 40.f));
}

void ASimpleFPSCharacter::StopCrouch(const FInputActionValue&)
{
    UnCrouch();
    FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
}

void ASimpleFPSCharacter::StartSprint(const FInputActionValue&)
{
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    bIsSprinting = true;
    OnSprint.Broadcast(bIsSprinting);
}

void ASimpleFPSCharacter::StopSprint(const FInputActionValue&)
{
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    bIsSprinting = false;
    OnSprint.Broadcast(bIsSprinting);
}

void ASimpleFPSCharacter::Shoot(const FInputActionValue&)
{
    if (GunActor)
        GunActor->PullTrigger();
}
