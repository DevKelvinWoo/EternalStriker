#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "EternalStrikerEnemy.generated.h"

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	//@TODO : EnemyStatComponent
	/*
	Sound, FX, Damage, Health, MP, etc..
	*/

	const FGameplayTag GetEnemyTypeTag() const { return EnemyTypeTag; }

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, Category = "Tag")
	FGameplayTag EnemyTypeTag{};
};
