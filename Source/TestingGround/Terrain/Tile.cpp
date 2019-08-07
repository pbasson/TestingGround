// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATile::ATile()
{
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector(4000.0f, 0.0f, 0.0f));
	
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
	if (Garbage.Num() != 0)
	{
		AActor * Prop;
		while (Garbage.Num() != 0)
		{
			Prop = Garbage.Pop();
			Prop->Destroy();
		}
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FTransform ATile::GetAttachment()
{
    return Arrow->GetComponentTransform();
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	RandomlySpawn(ToSpawn, MinSpawn, MaxSpawn);
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn)
{
	RandomlySpawn(ToSpawn, MinSpawn, MaxSpawn);
}

template<class T>
void ATile::RandomlySpawn(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
        bool found = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		if (found)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor(ToSpawn, SpawnPosition);
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

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
    FHitResult HitResult;
    FVector	GlobalLocation = ActorToWorld().TransformPosition(Location);
    bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));

    FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
    return HasHit;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (Spawned)
	{
		PlaceSpawn(Spawned, SpawnPosition);
		Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
	}
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	if (Spawned)
	{
		PlaceSpawn(Spawned, SpawnPosition);
		Spawned->SpawnDefaultController();
		Spawned->Tags.Add(FName("Enemy"));
	}
}

template<class T>
void ATile::PlaceSpawn(T Spawned, FSpawnPosition SpawnPosition)
{
    Garbage.Add(Spawned);
    Spawned->SetActorRelativeLocation(SpawnPosition.Location);
    Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
}

void ATile::SetPool(UActorPool* InPool)
{
	Pool = InPool;
	PositionNavMesh();
}

void ATile::PositionNavMesh()
{
	AActor* NavMeshBounds = Pool->Checkout();
    if (NavMeshBounds == nullptr) {
        return;	}

	NavMeshBounds->SetActorLocation(GetActorLocation() + NavigationRound);
	FNavigationSystem::Build(*GetWorld());
}
