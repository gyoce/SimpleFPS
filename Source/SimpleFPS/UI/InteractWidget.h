#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class SIMPLEFPS_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInteractWidget(const FObjectInitializer& ObjectInitializer);

	void SetInteract(bool bInteract);
	void StartInteract();
	void StopInteract();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UProgressBar* InteractProgress;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* InteractText;

	bool bInteractable = false;
	bool bInteracting = false;
	float InteractElapsed = 0.0f;
	float InteractDuration = 1.0f;
};
