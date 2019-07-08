// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool; 
class UWorld;
class UArrowComponent;
class UCapsuleComponent;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

UCLASS()
class TESTINGGROUND_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	

	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawn(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Spawning")
	UArrowComponent* Arrow;

	FTransform GetAttachment();

protected:

	virtual void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EEndPlayReason);

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationRound;

private:

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	template<class T>
	void RandomlySpawn(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	template<class T>
	void PlaceSpawn(T ToSpawn, FSpawnPosition SpawnPosition);

	bool CanSpawnAtLocation(FVector Location, float Radius);
	UActorPool* Pool; 
	void PositionNavMesh();

	AActor* NavMeshVolume;
};


