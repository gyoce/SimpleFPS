#include "EnnemyCharacter.h"

#include "Components/CapsuleComponent.h"

AEnnemyCharacter::AEnnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AEnnemyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	if (Health <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DEAD"));
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetSimulatePhysics(true);
	}

	return DamageToApply;
}
