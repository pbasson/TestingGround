//PROJECT: Testing Grounds
//AUTHOR: Preetpal Basson
//DESCRIPTION:

#include "Weapons/Gun.h"
#include "Animation/AnimInstance.h"
#include "Weapons/GunProjectile.h"
#include "Kismet/GameplayStatics.h"

AGun::AGun()
{
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
    RootComponent = FP_Gun;
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocationAndRotation(FVector(0.2f, 60.0f, 11.0f),FQuat(0.0f,0.0f,90.0f, 0.0f));

	AmmoCurrent = AmmoClip; 
    MaxAmmo = 30;
}

void AGun::BeginPlay()
{
    Super::BeginPlay();
}

void AGun::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGun::ReloadGun()
{
    if( AmmoCurrent < AmmoClip )
    {
        if ( ((AmmoCurrent + MaxAmmo) > AmmoClip) )
        { AmmoReloader(); }

        else if ( ((AmmoCurrent + MaxAmmo) <= AmmoClip) && MaxAmmo > AmmoZero )
        { AmmoSingleReloader(); }

        MaxAmmo = FMath::Clamp(MaxAmmo, AmmoZero, 180);
        AmmoCurrent = FMath::Clamp(AmmoCurrent, AmmoZero, AmmoClip);
    }
}

void AGun::AmmoReloader()
{
    UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
    AmmoReminder = AmmoClip - AmmoCurrent;
    AmmoCurrent = AmmoClip;
    MaxAmmo -= AmmoReminder;
}

void AGun::AmmoSingleReloader()
{
    UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
    AmmoReminder = MaxAmmo;
    AmmoCurrent += AmmoReminder;
    MaxAmmo -= AmmoReminder;
}

void AGun::AmmoIncrease()
{
    MaxAmmo += AmmoClip;
    MaxAmmo = FMath::Clamp(MaxAmmo, AmmoZero, 180);
}

void AGun::OnFire()
{
    if (AmmoCurrent > AmmoZero)
	{
		InitialFire();
		AmmoCurrent--;
	}
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

            FActorSpawnParameters ActorSpawnParams; //Set Spawn Collision Handling Override
            ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

            //Spawn the projectile at the muzzle
            World->SpawnActor<AGunProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
        }
    }
    // try and play the sound if specified
    if (FireSound != NULL)
    { UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation()); }

    // try and play a firing animation if specified
    if (FireAnimationTP != nullptr && AnimInstanceTP != nullptr)
    {
        if (AnimInstanceTP != NULL)
        { AnimInstanceTP->Montage_Play(FireAnimationTP, 1.f); }
    }
    if (FireAnimationFP != nullptr && AnimInstanceFP != nullptr)
    {
        if (AnimInstanceFP != NULL)
        { AnimInstanceFP->Montage_Play(FireAnimationFP, 1.f); }
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

bool AGun::OutOfAmmo() const
{
    if (AmmoCurrent == AmmoZero && MaxAmmo == AmmoZero)
    { return true; }

    return false;
}
