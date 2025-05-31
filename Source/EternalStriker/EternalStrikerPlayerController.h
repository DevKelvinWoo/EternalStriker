#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EternalStrikerPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

class AEternalStrikerMainCharacter;

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> MoveIA;

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> RunIA;

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> JumpIA;

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> LookIA;

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> AttackIA;

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> EquipIA;

	UPROPERTY(EditAnywhere, Category = "IMC")
	TObjectPtr<UInputMappingContext> MainCharacterIMC;

	UFUNCTION()
	void HandleOnMoveIATriggered(const FInputActionValue& InActionValue);
	UFUNCTION()
	void HandleOnRunIAStarted(const FInputActionValue& InActionValue);
	UFUNCTION()
	void HandleOnRunIACompleted(const FInputActionValue& InActionValue);
	UFUNCTION()
	void HandleOnJumpIAStarted(const FInputActionValue& InActionValue);
	UFUNCTION()
	void HandleOnLookIATriggered(const FInputActionValue& InActionValue);
	UFUNCTION()
	void HandleOnAttackIAStarted(const FInputActionValue& InActionValue);
	UFUNCTION()
	void HandleOnEquipIAStarted(const FInputActionValue& InActionValue);

	void AddIMCAndBindActions();

	UPROPERTY(Transient)
	TObjectPtr<AEternalStrikerMainCharacter> EternalStirkerMainCharacter;
};
