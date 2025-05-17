
#include "EternalStriker/EternalStrikerPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Character/EternalStrikerMainCharacter.h"

void AEternalStrikerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EternalStirkerMainCharacter = Cast<AEternalStrikerMainCharacter>(GetPawn());
}

void AEternalStrikerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	AddIMCAndBindActions();
}

void AEternalStrikerPlayerController::AddIMCAndBindActions()
{
	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedPlayerInputComponent);

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(EnhancedInputLocalPlayerSubSystem);

	ensureAlways(MainCharacterIMC);

	EnhancedInputLocalPlayerSubSystem->AddMappingContext(MainCharacterIMC, 0);

	ensureAlways(MoveIA && RunIA && JumpIA && LookIA && AttackIA);

	EnhancedPlayerInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ThisClass::HandleOnMoveIATriggered);
	EnhancedPlayerInputComponent->BindAction(RunIA, ETriggerEvent::Started, this, &ThisClass::HandleOnRunIAStarted);
	EnhancedPlayerInputComponent->BindAction(RunIA, ETriggerEvent::Completed, this, &ThisClass::HandleOnRunIACompleted);
	EnhancedPlayerInputComponent->BindAction(JumpIA, ETriggerEvent::Started, this, &ThisClass::HandleOnJumpIAStarted);
	EnhancedPlayerInputComponent->BindAction(LookIA, ETriggerEvent::Triggered, this, &ThisClass::HandleOnLookIATriggered);
	EnhancedPlayerInputComponent->BindAction(AttackIA, ETriggerEvent::Started, this, &ThisClass::HandleOnAttackIAStarted);
}

void AEternalStrikerPlayerController::HandleOnMoveIATriggered(const FInputActionValue& InActionValue)
{
	if (!ensureAlways(IsValid(EternalStirkerMainCharacter)))
	{
		return;
	}

	EternalStirkerMainCharacter->MoveCharacter(InActionValue);
}

void AEternalStrikerPlayerController::HandleOnRunIAStarted(const FInputActionValue& InActionValue)
{
	if (!ensureAlways(IsValid(EternalStirkerMainCharacter)))
	{
		return;
	}

	EternalStirkerMainCharacter->RunCharacter(InActionValue);
}

void AEternalStrikerPlayerController::HandleOnRunIACompleted(const FInputActionValue& InActionValue)
{
	if (!ensureAlways(IsValid(EternalStirkerMainCharacter)))
	{
		return;
	}

	EternalStirkerMainCharacter->RunCharacter(InActionValue);
}

void AEternalStrikerPlayerController::HandleOnJumpIAStarted(const FInputActionValue& InActionValue)
{
	if (!ensureAlways(IsValid(EternalStirkerMainCharacter)))
	{
		return;
	}

	EternalStirkerMainCharacter->JumpCharacter(InActionValue);
}

void AEternalStrikerPlayerController::HandleOnLookIATriggered(const FInputActionValue& InActionValue)
{
	if (!ensureAlways(IsValid(EternalStirkerMainCharacter)))
	{
		return;
	}

	EternalStirkerMainCharacter->LookCharacter(InActionValue);
}

void AEternalStrikerPlayerController::HandleOnAttackIAStarted(const FInputActionValue& InActionValue)
{
	if (!ensureAlways(IsValid(EternalStirkerMainCharacter)))
	{
		return;
	}

	EternalStirkerMainCharacter->AttackBasic(InActionValue);
}
