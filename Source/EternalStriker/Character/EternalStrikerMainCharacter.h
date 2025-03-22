
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EternalStrikerMainCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEternalStrikerMainCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void AddIMCAndBindActions(UInputComponent* InPlayerInputComponent);

	UFUNCTION()
	void MoveCharacter(const FInputActionValue& InActionValue);

	UFUNCTION()
	void RunCharacter(const FInputActionValue& InActionValue);

	void SetCharacterMovementValues();

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> MoveIA;

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> RunIA;

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> JumpIA;

	UPROPERTY(EditAnywhere, Category = "IMC")
	TObjectPtr<UInputMappingContext> MainCharacterIMC;

	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsRunning{ false };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxRunSpeed{ 950.f };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeed{ 550.f };

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanMove{ true };
};
