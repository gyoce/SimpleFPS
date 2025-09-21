#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnnemyCharacter.generated.h"

UCLASS()
class SIMPLEFPS_API AEnnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnnemyCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Health = 100.0f;
};
