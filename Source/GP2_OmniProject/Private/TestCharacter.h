// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "TestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Functions
	UFUNCTION()
	FVector GetCameraForwardDir() const;
	UFUNCTION()
	FVector GetCameraRightDir() const;
	UFUNCTION() void MoveCharacter(const FInputActionValue& Value);
	UFUNCTION() void Look(const FInputActionValue& Value);
	
	//Input
	UPROPERTY(EditAnywhere, Category = "Input") UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* JumpAction;
	
	//Camera
	UPROPERTY(VisibleAnywhere, Category = "Camera") USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Camera") UCameraComponent* PlayerCamera;

	//Player Stats
	UPROPERTY(EditAnywhere, Category = "Player Settings") float SprintMultiplier{2.0f};
};
