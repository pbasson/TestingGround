// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "Engine/World.h"
#include "NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationRound = FVector(2000, 0, 0);

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	

}

void ATile::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Pool->ReturnActor(NavMeshVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector	GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	return HasHit;
}


void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector Spawnpoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptyLocation(Spawnpoint, Radius);
		if (found)
		{
			float Rotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor(ToSpawn, Spawnpoint, Rotation, RandomScale);
		}
	}
}


bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{

	FBox Bounds(MinExtent, MaxExtent);
	const int MAX_ATTEMPT = 100;
	for (size_t i = 0; i < MAX_ATTEMPT; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;
			return true; 
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Spawnpoint, float Rotation, float Scale)
{
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(Spawnpoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorRotation(FRotator(0, Rotation, 0));
		Spawned->SetActorScale3D(FVector(Scale));
}

void ATile::SetPool(UActorPool* InPool)
{
	Pool = InPool;
	PositionNavMesh();
}

void ATile::PositionNavMesh()
{
	AActor* NavMeshBounds = Pool->Checkout();
	if (NavMeshBounds == nullptr)
	{
		return; 
	}
		NavMeshBounds->SetActorLocation(GetActorLocation() + NavigationRound);
		FNavigationSystem::Build(*GetWorld());
}