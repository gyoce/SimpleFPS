#include "MainGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMainGameMode::AMainGameMode() : Super()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BP_MainPlayerCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;
}
