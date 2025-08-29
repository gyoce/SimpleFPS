#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class SIMPLEFPS_API AMainPlayerController : public APlayerController
{
    GENERATED_BODY()
    
public:
    UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = nullptr;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* InputMappingContext;

    virtual void BeginPlay() override;
};
