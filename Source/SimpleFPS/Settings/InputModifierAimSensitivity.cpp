#include "InputModifierAimSensitivity.h"

#include "EnhancedPlayerInput.h"
#include "EnhancedInputSubsystems.h"
#include "../Settings/MainEnhancedInputUserSettings.h"

FInputActionValue UInputModifierAimSensitivity::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
    EnsureSettingsIsSet(PlayerInput);

    return CurrentValue.Get<FVector>() * Settings->GetSensitivity();
}

void UInputModifierAimSensitivity::EnsureSettingsIsSet(const UEnhancedPlayerInput* PlayerInput)
{
    if (Settings == nullptr)
        Settings = PlayerInput->GetOwningLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->GetUserSettings<UMainEnhancedInputUserSettings>();
}
