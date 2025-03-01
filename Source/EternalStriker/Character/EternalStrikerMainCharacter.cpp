
#include "EternalStrikerMainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AEternalStrikerMainCharacter::AEternalStrikerMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEternalStrikerMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEternalStrikerMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEternalStrikerMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AddIMCAndBindActions(PlayerInputComponent);
}

void AEternalStrikerMainCharacter::AddIMCAndBindActions(UInputComponent* InPlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(InPlayerInputComponent);
	check(EnhancedPlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController);

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	check(EnhancedInputLocalPlayerSubSystem);

	if (ensureAlways(IsValid(MainCharacterIMC)))
	{
		EnhancedInputLocalPlayerSubSystem->AddMappingContext(MainCharacterIMC, 0);
	}

	if (ensureAlways(IsValid(MoveIA)))
	{

		EnhancedPlayerInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ThisClass::MoveCharacter);
	}
}

void AEternalStrikerMainCharacter::MoveCharacter(const FInputActionValue& InActionValue)
{
	const FVector2D& MovementVector = InActionValue.Get<FVector2D>();

	check(Controller);

	const FRotator& Rotation = Controller->GetControlRotation();
	const FRotator& YawRotation = FRotator(0, Rotation.Yaw, 0);

	const FVector& ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector& RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}
