#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EternalStrikerEnemy.generated.h"

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	//@FIXME : Fix Enemy properties and methods, this is only for test
	int32 EnemyHealth{ 100 };

	//@TODO : Implements Hit Interface to play sound by weapon

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:

};
