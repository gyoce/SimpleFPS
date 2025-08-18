#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "../Enums/WeaponName.h"
#include "MainPlayerCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SIMPLEFPS_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainPlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SpawnWeapon(TSubclassOf<class UWeaponMaster> WeaponToSpawn, FVector PickupLocation);

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
	UInputAction* SwitchCameraAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWeaponMaster* CurrentWeapon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponName CurrentWeaponName;

	void ConfigMesh();
	void ConfigThirdPerson();
	void ConfigFirstPerson();

	void Move(const FInputActionValue& Value);
	void StopMove(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void SwitchCamera(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

	bool bIsFirstPersonCamera = true;
};
