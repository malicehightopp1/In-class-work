// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//spring arm setup
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	//Camera setup
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom);

	PlayerCamera->bUsePawnControlRotation = false; //dont use dont use pawns rotation
	CameraBoom->bUsePawnControlRotation = true; //rotating the spring arm around the player
	CameraBoom->TargetArmLength = 500.0f; //length of spring arm
	bUseControllerRotationYaw = false; //do not use player controller yaw rotation
	GetCharacterMovement()->bOrientRotationToMovement = true; //rotates by movement rotation
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerCameraManager* cameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)))
	{
		cameraManager->StartCameraFade(1.25f, 0.0f, 3.0f, FLinearColor::Black, false, false);
	}
}
void ATestCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	 if (const APlayerController* playerController = Cast<APlayerController>(GetController()))
	 {
		 if (UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		 {
			 subSystem->AddMappingContext(MappingContext, 0);
		 }
	 }
}
// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		inputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestCharacter::MoveCharacter);
		inputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestCharacter::Look);
		inputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATestCharacter::Jump);
		inputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATestCharacter::StopJumping);
	}
}
FVector ATestCharacter::GetCameraForwardDir() const
{
	FVector cameraFWD = PlayerCamera->GetForwardVector(); //grabbing forward vector
	cameraFWD.Z = 0.0f;
	return cameraFWD;
}
FVector ATestCharacter::GetCameraRightDir() const
{
	return PlayerCamera->GetRightVector();
}
void ATestCharacter::MoveCharacter(const FInputActionValue& Value)
{
	FVector2D input = Value.Get<FVector2D>();
	input.Normalize();

	AddMovementInput(input.Y * GetCameraForwardDir() + input.X * GetCameraRightDir());
}
void ATestCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D lookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(lookAxisVector.Y);
	AddControllerYawInput(lookAxisVector.X);
}