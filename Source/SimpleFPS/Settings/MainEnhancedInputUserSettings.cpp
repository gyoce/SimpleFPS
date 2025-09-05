#include "MainEnhancedInputUserSettings.h"

void UMainEnhancedInputUserSettings::SetAimSensitivity(float SensitivityX, float SensitivityY)
{
    AimSensitivityX = SensitivityX;
    AimSensitivityY = SensitivityY;

    ApplySettings();
}

FVector UMainEnhancedInputUserSettings::GetSensitivity()
{
    return FVector(AimSensitivityX, AimSensitivityY, 1.f);
}

void UMainEnhancedInputUserSettings::SetUseAimingDownSightScale(bool bAiming)
{
    bUseAimingDownSightScale = bAiming;
}
