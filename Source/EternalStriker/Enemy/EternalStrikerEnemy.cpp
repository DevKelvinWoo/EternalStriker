#include "EternalStrikerEnemy.h"

float AEternalStrikerEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage{ Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser) };

	//@FIXME : Implement Enemy damage logic, this is only for test (Need Stat Component)
	EnemyHealth -= ActualDamage;
	if (EnemyHealth <= 0)
	{
		EnemyHealth = 0;
		UE_LOG(LogTemp, Warning, TEXT("Enemy is dead!"));
	}

	return ActualDamage;
}
