// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/Gun.h"
#include "Animation/AnimInstance.h"
#include "Weapons/GunProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocationAndRotation(FVector(0.2f, 60.0f, 11.0f),FQuat(0.0f,0.0f,90.0f, 0.0f));

	AmmoCurrent = AmmoClip; 
	MaxAmmo = 180;
}

void AGun::ReloadGun()
{
	FMath::Clamp(MaxAmmo, 0, 180);
	FMath::Clamp(AmmoCurrent, 0, 18);

	if (AmmoCurrent == 0)
	{
//		if (AmmoCurrent = AmmoClip)
		UE_LOG(LogTemp, Warning,TEXT("Ammo Zero"))
		if (MaxAmmo > AmmoClip)
		{
			FiringStatus = EFiringStatus::Reloading;
			MaxAmmo = MaxAmmo - AmmoClip;
			AmmoCurrent = AmmoClip;
		}
		else if (MaxAmmo <= AmmoClip)
		{
			UE_LOG(LogTemp, Warning, TEXT(" OutAmmo"))
			FiringStatus = EFiringStatus::OutAmmo;
			AmmoCurrent = MaxAmmo;
			MaxAmmo = 0;
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

}

void AGun::OnFire()
{
	if (AmmoCurrent > 0)
	{
		InitialFire();
		AmmoCurrent--;
	}
}

EFiringStatus AGun::GetFiringStatus() const
{
	return FiringStatus;
}

int AGun::GetAmmo() const
{
	return AmmoCurrent;
}

int AGun::GetMaxAmmo() const
{
	return MaxAmmo;
}

void AGun::InitialFire()
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
		if (AnimInstanceTP != NULL) { AnimInstanceTP->Montage_Play(FireAnimationTP, 1.f); }
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

