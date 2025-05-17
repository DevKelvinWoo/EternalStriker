
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EternalStrikerMainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UEternalCombatComponent;

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEternalStrikerMainCharacter();

	UEternalCombatComponent* GetCombatComponent() { return CombatComponent; }

	UFUNCTION()
	void MoveCharacter(const FInputActionValue& InActionValue);
	UFUNCTION()
	void RunCharacter(const FInputActionValue& InActionValue);
	UFUNCTION()
	void JumpCharacter(const FInputActionValue& InActionValue);
	UFUNCTION()
	void LookCharacter(const FInputActionValue& InActionValue);
	UFUNCTION()
	void AttackBasic(const FInputActionValue& InActionValue);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCharacterMovementValues();

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEternalCombatComponent> CombatComponent;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsRunning{ false };

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanMove{ true };

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bRecoveringJump{ false };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxRunSpeed{ 950.f };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeed{ 550.f };
};
