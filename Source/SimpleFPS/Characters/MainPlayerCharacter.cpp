#include "MainPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Actors/WeaponPickup.h"
#include "../Actors/Weapon.h"

AMainPlayerCharacter::AMainPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 96.0f);
	ConfigMesh();
	ConfigFirstPerson();
	ConfigThirdPerson();
}

void AMainPlayerCharacter::ConfigMesh()
{
	GetMesh()->bCastDynamicShadow = true;
	GetMesh()->CastShadow = true;
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.0f, 0.f));
}

void AMainPlayerCharacter::ConfigThirdPerson()
{
	ThirdPersonCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonCameraBoom"));
	ThirdPersonCameraBoom->SetupAttachment(RootComponent);
	ThirdPersonCameraBoom->TargetArmLength = 400.0f;
	ThirdPersonCameraBoom->bUsePawnControlRotation = true;

	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(ThirdPersonCameraBoom, USpringArmComponent::SocketName);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	ThirdPersonCameraComponent->bAutoActivate = false;
}

void AMainPlayerCharacter::ConfigFirstPerson()
{
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetMesh(), TEXT("head"));
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 10.f, 0.f));
	FirstPersonCameraComponent->SetRelativeRotation(FRotator(0.f, 90.f, -90.f));
    FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AMainPlayerCharacter::StopMove);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMainPlayerCharacter::StopMove);

        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::Look);

        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::Shoot);

        EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Started, this, &AMainPlayerCharacter::SwitchCamera);

        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::Interact);

        EnhancedInputComponent->BindAction(EquipPrimaryWeaponAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::EquipPrimaryWeapon);
        EnhancedInputComponent->BindAction(EquipSecondaryWeaponAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::EquipSecondaryWeapon);
        EnhancedInputComponent->BindAction(EquipUnarmedWeaponAction, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::EquipUnarmedWeapon);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
    }
}

void AMainPlayerCharacter::SpawnWeapon(TSubclassOf<AWeapon> WeaponToSpawn, FVector PickupLocation)
{
    CurrentWeaponClass = WeaponToSpawn->GetDefaultObject<AWeapon>()->GetWeaponClass();
    AWeapon* CurrentWeapon = GetCurrentWeapon();

    if (CurrentWeapon != nullptr)
        SpawnPickupWeapon(PickupLocation, CurrentWeapon);
 
    AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponToSpawn);
    NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, NewWeapon->GetSocketName());
    NewWeapon->SetOwner(this);
    CurrentWeapons.Add({ CurrentWeaponClass, NewWeapon });

    HideAllWeaponsExceptCurrent();
}

void AMainPlayerCharacter::SpawnPickupWeapon(FVector& PickupLocation, AWeapon* Weapon)
{
    PickupLocation.Z += 10.f;
    FVector SpawnLocation = GetActorLocation() + GetActorTransform().GetRotation().GetForwardVector() * 50.f;
    FTransform SpawnTransform(SpawnLocation);
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    GetWorld()->SpawnActor<AWeaponPickup>(Weapon->GetPickupClass(), SpawnTransform, SpawnParameters);
    Weapon->Destroy();
}

void AMainPlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void AMainPlayerCharacter::StopMove(const FInputActionValue&)
{
    
}

void AMainPlayerCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AMainPlayerCharacter::Shoot(const FInputActionValue& Value)
{
    AWeapon* CurrentWeapon = GetCurrentWeapon();

    if (CurrentWeapon == nullptr || !bCanFire)
        return;

    CurrentWeapon->Shoot(FirstPersonCameraComponent->GetComponentLocation(), FirstPersonCameraComponent->GetForwardVector());
}

void AMainPlayerCharacter::SwitchCamera(const FInputActionValue&)
{
    bIsFirstPersonCamera = !bIsFirstPersonCamera;

    FirstPersonCameraComponent->SetActive(bIsFirstPersonCamera);
    ThirdPersonCameraComponent->SetActive(!bIsFirstPersonCamera);        
}

void AMainPlayerCharacter::Interact(const FInputActionValue&)
{
    TArray<AActor*> Result;
    GetOverlappingActors(Result, AWeaponPickup::StaticClass());

    if (Result.IsEmpty())
        return;

    AWeaponPickup* FirstResult = Cast<AWeaponPickup>(Result[0]);
    FirstResult->Interact(this);
}

void AMainPlayerCharacter::EquipPrimaryWeapon(const FInputActionValue&)
{
    OnSwitchingWeapon(EWeaponClass::Primary);
}

void AMainPlayerCharacter::EquipSecondaryWeapon(const FInputActionValue&)
{
    OnSwitchingWeapon(EWeaponClass::Secondary);
}

void AMainPlayerCharacter::EquipUnarmedWeapon(const FInputActionValue&)
{
    OnSwitchingWeapon(EWeaponClass::Unarmed);
}

void AMainPlayerCharacter::HideAllWeaponsExceptCurrent()
{
    for (const auto& [_, Weapon] : CurrentWeapons)
        Weapon->SetHidden(Weapon->GetWeaponClass() != CurrentWeaponClass);
}

void AMainPlayerCharacter::SetCurrentWeapon(EWeaponClass WeaponClass)
{
    CurrentWeaponClass = WeaponClass;
    HideAllWeaponsExceptCurrent();
}

FTransform AMainPlayerCharacter::GetLhikTransform()
{
    AWeapon* CurrentWeapon = GetCurrentWeapon();
    if (CurrentWeapon == nullptr)
        return FTransform();

    FTransform LhikTransform = CurrentWeapon->GetLhikTransform();
    FVector OutVector;
    FRotator OutRotation;
    GetMesh()->TransformToBoneSpace(TEXT("hand_r"), LhikTransform.GetLocation(), LhikTransform.Rotator(), OutVector, OutRotation);
    return FTransform(OutRotation, OutVector, FVector::One());
}

AWeapon* AMainPlayerCharacter::GetCurrentWeapon()
{
    AWeapon** Weapon = CurrentWeapons.Find(CurrentWeaponClass);
    return Weapon == nullptr ? nullptr : *Weapon;
}
