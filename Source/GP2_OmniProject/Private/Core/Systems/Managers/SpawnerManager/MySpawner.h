// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MySpawner.generated.h"

UCLASS()
class AMySpawner : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable) void SpawnTestingActor();
	
	UPROPERTY(EditAnywhere, Category = "Spawn Component") TSubclassOf<AActor> MySpawnerComponent;
	UPROPERTY(EditAnywhere, Category = "Spawn Component") FVector SpawnLocation;
};
