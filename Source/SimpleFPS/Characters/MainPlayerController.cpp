#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(LocalPlayerSubsystem);
    LocalPlayerSubsystem->AddMappingContext(InputMappingContext, 0);
}