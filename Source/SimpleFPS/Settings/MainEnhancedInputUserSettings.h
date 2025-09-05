#pragma once

#include "CoreMinimal.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "MainEnhancedInputUserSettings.generated.h"

UCLASS()
class SIMPLEFPS_API UMainEnhancedInputUserSettings : public UEnhancedInputUserSettings
{
	GENERATED_BODY()
	
public:
	void SetAimSensitivity(float SensitivityX, float SensitivityY);
	FVector GetSensitivity();

	void SetUseAimingDownSightScale(bool bUsing);
	bool UseAimingDownSightScale() const { return bUseAimingDownSightScale; }

protected:
	UPROPERTY(EditAnywhere, Config)
	float AimSensitivityX = 0.75f;

	UPROPERTY(EditAnywhere, Config)
	float AimSensitivityY = 0.75f;

	bool bUseAimingDownSightScale = false;
};
