#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EternalCombatComponent.generated.h"

class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALSTRIKER_API UEternalCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AttackBasic();

	void IncreaseCurrentComboCount();
	void ResetCurrentComboCount();
	
	void SetCanAttackState(const bool InCanAttackState) { bCanAttack = InCanAttackState; }

private:	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> CombatMontage;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	TMap<int32, FName> ComboMontageSectionNameContainer;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	int32 FullComboCount{};

	int32 CurrentComboCount{};

	bool bCanAttack{ true };
};
