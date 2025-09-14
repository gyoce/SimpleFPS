#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "../Enums/WeaponClass.h"
#include "MainPlayerCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class AWeapon;
class AWeaponPickup;
class AMainPlayerController;
class UMainEnhancedInputUserSettings;
class UUserWidget;
class UInteractWidget;

UCLASS()
class SIMPLEFPS_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainPlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SpawnWeapon(TSubclassOf<AWeapon> WeaponToSpawn, FVector PickupLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void OnSwitchingWeapon(EWeaponClass WeaponClass);

	UFUNCTION(BlueprintImplementableEvent)
	void OnAiming(bool bAiming);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ThirdPersonCameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchCameraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipPrimaryWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipSecondaryWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipUnarmedWeaponAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponClass, AWeapon*> CurrentWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponClass CurrentWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> InteractWidgetClass;

	void ConfigMesh();
	void ConfigThirdPerson();
	void ConfigFirstPerson();

	void Move(const FInputActionValue& Value);
	void StopMove(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void StartAim(const FInputActionValue& Value);
	void StopAim(const FInputActionValue& Value);
	void SwitchCamera(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);
	void StartInteract(const FInputActionValue& Value);
	void StopInteract(const FInputActionValue& Value);
		
	void EquipPrimaryWeapon(const FInputActionValue& Value);
	void EquipSecondaryWeapon(const FInputActionValue& Value);
	void EquipUnarmedWeapon(const FInputActionValue& Value);

	void SpawnPickupWeapon(FVector& PickupLocation, AWeapon* Weapon);
	void HideAllWeaponsExceptCurrent();
	void SearchForItemToPickup();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	AWeapon* GetCurrentWeapon();

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void SetCurrentWeapon(EWeaponClass WeaponClass);

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	FTransform GetLhikTransform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsFirstPersonCamera = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanFire = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeedWhileSprinting = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customizable", meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeedWhileAiming = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* UserWidgetInteract = nullptr;

	// Cache variables
	AMainPlayerController* PlayerController = nullptr;
	UMainEnhancedInputUserSettings* UserSettings = nullptr;
	AWeaponPickup* OldWeaponPickup = nullptr;
	AWeaponPickup* WeaponToPickup = nullptr;
	UInteractWidget* InteractWidget = nullptr;
};
