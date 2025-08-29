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

protected:
	UPROPERTY(EditAnywhere, Config)
	float AimSensitivityX = 1.f;

	UPROPERTY(EditAnywhere, Config)
	float AimSensitivityY = 1.f;
};
