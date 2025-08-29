#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "InputModifierAimSensitivity.generated.h"

class UMainEnhancedInputUserSettings;

UCLASS()
class SIMPLEFPS_API UInputModifierAimSensitivity : public UInputModifier
{
	GENERATED_BODY()
	
protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;

	void EnsureSettingsIsSet(const UEnhancedPlayerInput* PlayerInput);

	UPROPERTY(Transient)
	UMainEnhancedInputUserSettings* Settings;
};
