#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "EnhancedInputComponent.h"
#include "SimpleFPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UChildActorComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSprint, bool, bIsSprinting);

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASimpleFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASimpleFPSCharacter();

private:
    /** Pawn mesh: 1st person view (arms; seen only by self) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* Mesh1P;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    UChildActorComponent* Gun;

    /** First person camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCameraComponent;

    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    /** Crouch Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* CrouchAction;

    /** Sprint Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* SprintAction;

    /** Shoot Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* ShootAction;

    UPROPERTY(EditAnywhere)
    float SprintSpeed = 900.0f;

    UPROPERTY(EditAnywhere)
    float WalkSpeed = 600.0f;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UCameraShakeBase> CameraShakeStep;

protected:
    virtual void BeginPlay();

public:
    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UAttributeComponent* AttributeComponent;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSprint OnSprint;

protected:
    void Move(const FInputActionValue& Value);
    void StopMove(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

    void StartCrouch(const FInputActionValue& Value);
    void StopCrouch(const FInputActionValue& Value);

    void StartSprint(const FInputActionValue& Value);

    void Shoot(const FInputActionValue& Value);

public:
    void StopSprint(const FInputActionValue& Value = FInputActionValue());

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
    /** Returns Mesh1P subobject **/
    USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
    /** Returns FirstPersonCameraComponent subobject **/
    UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
    UPROPERTY()
    UCameraShakeBase* CameraShakeStepInstance;
    
    bool bIsSprinting = false;

    UPROPERTY()
    class AGun* GunActor;
};

