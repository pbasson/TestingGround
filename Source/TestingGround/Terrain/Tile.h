// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool; 

UCLASS()
class TESTINGGROUND_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EEndPlayReason);


private:

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Spawnpoint, float Rotation, float Scale);
	bool CanSpawnAtLocation(FVector Location, float Radius);
	UActorPool* Pool; 
	void PositionNavMesh();

	AActor* NavMeshVolume;
};
