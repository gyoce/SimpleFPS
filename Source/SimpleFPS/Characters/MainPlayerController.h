#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class SIMPLEFPS_API AMainPlayerController : public APlayerController
{
    GENERATED_BODY()
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* InputMappingContext;

    virtual void BeginPlay() override;
};
