
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EternalStrikerMainCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

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

	UPROPERTY(EditAnywhere, Category = "IA")
	TObjectPtr<UInputAction> MoveIA;

	UPROPERTY(EditAnywhere, Category = "IMC")
	TObjectPtr<UInputMappingContext> MainCharacterIMC;
};
