#include "EternalStrikerEnemy.h"

float AEternalStrikerEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage{ Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser) };

	UE_LOG(LogTemp, Warning, TEXT("Actual Damage: %f"), ActualDamage);

	return ActualDamage;
}
