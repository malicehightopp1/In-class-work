// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Systems/Managers/SpawnerManager/MySpawner.h"
// Sets default values
AMySpawner::AMySpawner()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnTestingActor();
}

// Called every frame
void AMySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMySpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMySpawner::SpawnTestingActor()
{
	FActorSpawnParameters SpawnParameters; //YOU NEED THIS FOR SPAWNING OBJECTS
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(MySpawnerComponent,SpawnLocation,FRotator::ZeroRotator, SpawnParameters);
}

