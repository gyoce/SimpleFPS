#include "InputModifierAimSensitivity.h"

#include "EnhancedPlayerInput.h"
#include "EnhancedInputSubsystems.h"
#include "../Settings/MainEnhancedInputUserSettings.h"

FInputActionValue UInputModifierAimSensitivity::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
    EnsureSettingsIsSet(PlayerInput);

    if (Settings->UseAimingDownSightScale())
        return (CurrentValue.Get<FVector>() * Settings->GetSensitivity()) * FVector(0.3f, 0.3f, 1.f);
    return CurrentValue.Get<FVector>() * Settings->GetSensitivity();
}

void UInputModifierAimSensitivity::EnsureSettingsIsSet(const UEnhancedPlayerInput* PlayerInput)
{
    if (Settings == nullptr)
        Settings = PlayerInput->GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->GetUserSettings<UMainEnhancedInputUserSettings>();
}
