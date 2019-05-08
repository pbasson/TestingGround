// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/Gun.h"
#include "Animation/AnimInstance.h"
#include "Weapons/GunProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
//	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 60.0f, 11.0f));
	FP_MuzzleLocation->SetRelativeLocationAndRotation(FVector(0.2f, 60.0f, 11.0f),FQuat(0.0f,0.0f,90.0f, 0.0f));
//	FP_MuzzleLocation->SetRelativeRotation(FQuat(0.0f, 0.0f, -40.0f, 0.0f));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

//	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void AGun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation(); // Set Rotation
			const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();  // Set Location

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
            World->SpawnActor<AGunProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimationTP != nullptr && AnimInstanceTP != nullptr)
	{
		if (AnimInstanceTP != NULL)	{ AnimInstanceTP->Montage_Play(FireAnimationTP, 1.f); }
	}
	if (FireAnimationFP != nullptr && AnimInstanceFP != nullptr)
	{
		if (AnimInstanceFP != NULL) { AnimInstanceFP->Montage_Play(FireAnimationFP, 1.f); }
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

