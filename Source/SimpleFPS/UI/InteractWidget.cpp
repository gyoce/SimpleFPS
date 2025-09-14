#include "InteractWidget.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UInteractWidget::UInteractWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}

void UInteractWidget::SetInteract(bool bInteract)
{
    bInteractable = bInteract;
    InteractText->SetRenderOpacity(bInteractable ? 1.0f : 0.0f);
}

void UInteractWidget::StartInteract()
{
    InteractProgress->SetRenderOpacity(1.0f);
    bInteracting = true;
}

void UInteractWidget::StopInteract()
{
    bInteracting = false;
    InteractProgress->SetRenderOpacity(0.0f);      
    InteractText->SetRenderOpacity(0.0f);
    InteractProgress->SetPercent(0.0f);
    InteractElapsed = 0.0f;
}

void UInteractWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bInteractable && bInteracting)
    {
        InteractElapsed += InDeltaTime;
        float Percent = FMath::Clamp(InteractElapsed / InteractDuration, 0.0f, 1.0f);
        InteractProgress->SetPercent(Percent);
    }
}
