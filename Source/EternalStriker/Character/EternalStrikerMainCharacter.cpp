
#include "EternalStrikerMainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEternalStrikerMainCharacter::AEternalStrikerMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SetCharacterMovementValues();

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
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

	check(MainCharacterIMC);
	
	EnhancedInputLocalPlayerSubSystem->AddMappingContext(MainCharacterIMC, 0);

	check(MoveIA && RunIA && JumpIA && LookIA);

	EnhancedPlayerInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ThisClass::MoveCharacter);
	EnhancedPlayerInputComponent->BindAction(RunIA, ETriggerEvent::Started, this, &ThisClass::RunCharacter);
	EnhancedPlayerInputComponent->BindAction(RunIA, ETriggerEvent::Completed, this, &ThisClass::RunCharacter);
	EnhancedPlayerInputComponent->BindAction(JumpIA, ETriggerEvent::Started, this, &ThisClass::JumpCharacter);
	EnhancedPlayerInputComponent->BindAction(LookIA, ETriggerEvent::Triggered, this, &ThisClass::LookCharacter);
}

void AEternalStrikerMainCharacter::MoveCharacter(const FInputActionValue& InActionValue)
{
	check(Controller);

	if (!bCanMove)
	{
		return;
	}

	const FVector2D& MovementVector = InActionValue.Get<FVector2D>();

	const FRotator& Rotation = Controller->GetControlRotation();
	const FRotator& YawRotation = FRotator(0, Rotation.Yaw, 0);

	const FVector& ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector& RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AEternalStrikerMainCharacter::RunCharacter(const FInputActionValue& InActionValue)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	check(MovementComponent);

	const bool bInputDashKey = InActionValue.IsNonZero();
	if (bInputDashKey)
	{
		bIsRunning = true;
		MovementComponent->MaxWalkSpeed = MaxRunSpeed;
	}
	else
	{
		bIsRunning = false;
		MovementComponent->MaxWalkSpeed = MaxWalkSpeed;
	}
}

void AEternalStrikerMainCharacter::JumpCharacter(const FInputActionValue& InActionValue)
{
	if (bIsRunning || bRecoveringJump)
	{
		return;
	}

	const bool bInputJumpKey = InActionValue.IsNonZero();
	if (bInputJumpKey)
	{
		Jump();
	}
}

void AEternalStrikerMainCharacter::LookCharacter(const FInputActionValue& InActionValue)
{
	check(Controller);

	const bool bInputLookAtKey = InActionValue.IsNonZero();

	if (!bInputLookAtKey)
	{
		return;
	}

	const FVector2D& LookAxisVector = InActionValue.Get<FVector2D>();
	
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AEternalStrikerMainCharacter::SetCharacterMovementValues()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	check(MovementComponent);

	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
	MovementComponent->AirControl = 0.35f;
	MovementComponent->MaxWalkSpeed = MaxWalkSpeed;
	MovementComponent->MinAnalogWalkSpeed = 20.f;
	MovementComponent->bUseSeparateBrakingFriction = true;
	MovementComponent->MaxAcceleration = 1000.f;
	MovementComponent->BrakingDecelerationWalking = 1100.f;
	MovementComponent->BrakingDecelerationFalling = 1500.0f;
	MovementComponent->JumpZVelocity = 450.f;
	MovementComponent->GravityScale = 1.5f;
}
