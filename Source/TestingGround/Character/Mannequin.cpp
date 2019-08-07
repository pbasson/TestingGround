//PROJECT: Testing Grounds
//AUTHOR: Preetpal Basson
//DESCRIPTION:

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Weapons/Gun.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "WidgetComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMannequin::AMannequin()
{
//	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

    PlayerLabel = "Player";
    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

	//Set up health values
    HealthCurrent = HealthMax;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	//RelativeLocation is used to position the camera
	FPCamera->RelativeLocation = FVector(-39.5f, 1.75f, 64.0f); 
	FPCamera->bUsePawnControlRotation = true; 

	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->SetupAttachment(FPCamera);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	FPMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FPMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	GunSetup();
	if (InputComponent != NULL) { 
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger); 
        InputComponent->BindAction("Reload", IE_Pressed, this, &AMannequin::ReloadDelayGun);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMannequin::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMannequin::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMannequin::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMannequin::LookUpAtRate);
}


void AMannequin::MoveForward(float Value)
{
	if (Value != MovementZero) { AddMovementInput(GetActorForwardVector(), Value); }
}

void AMannequin::MoveRight(float Value)
{
	if (Value != MovementZero) { AddMovementInput(GetActorRightVector(), Value); }
}

void AMannequin::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMannequin::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMannequin::GunSetup()
{
	if (GunBlueprint == NULL) { return; }

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	if (IsPlayerControlled()) { Gun->AttachToComponent(FPMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); }

	else { Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); }
	// AttachToComponent to Socket of the Skeleton
	Gun->AnimInstanceFP = FPMesh->GetAnimInstance();
	Gun->AnimInstanceTP = GetMesh()->GetAnimInstance();

}



void AMannequin::PullTrigger()
{
	if (Gun) 
	{ Gun->OnFire(); }
}

float AMannequin::TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    if (HealthCurrent > HealthZero)
	{ HealthCurrent = HealthCurrent - Damage; }

    if (HealthCurrent == HealthZero)
	{ UnPossessedDamage(); }

    return HealthCurrent;
}

void AMannequin::UnPossessedDamage()
{
    DetachFromControllerPendingDestroy();
    UnPossessed();

    AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, EnemyDeathSound, GetActorLocation());

    FTimerHandle Timer;
   //
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMannequin::EnemyDestroy, DestroyDelay, false);
    //GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMannequin::PlayerDead, DestroyDelay, false);

}

void AMannequin::UnPossessed()
{
    Super::UnPossessed();

    if (Gun != nullptr)
    { Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); }
}

void AMannequin::PlayerDead()
{
    if (GetName() == PlayerLabel)
    { UGameplayStatics::SetGamePaused(GetWorld(), IsPlayerDead()); }
}

void AMannequin::EnemyDestroy()
{
    AudioComponent->SetActive(false);
    if (GetName() !=  PlayerLabel) {
        Destroy();
        Gun->Destroy();
    }
}

float AMannequin::GetHealth() const
{
    return HealthCurrent / HealthMax;
}

float AMannequin::SetHealthpack(float Healthpack)
{
	if (HealthCurrent < HealthMax)
	{ HealthCurrent = HealthCurrent + Healthpack; }

    HealthCurrent = FMath::Clamp<int>(HealthCurrent, HealthZero, HealthMax);

	return HealthCurrent;
}

int AMannequin::GetGunAmmo() const
{
	return Gun->GetAmmo();
}

int AMannequin::GetGunMaxAmmo() const
{
	return Gun->GetMaxAmmo();
}

bool AMannequin::IsPlayerDead()
{
    if (HealthCurrent == HealthZero)
	{ return true; }

	return false;
}

void AMannequin::ReloadGun()
{
	if (Gun)
    { Gun->ReloadGun(); }

}

void AMannequin::ReloadDelayGun()
{
    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMannequin::ReloadGun, ReloadDelay, false);
}

void AMannequin::AmmoIncrease()
{
	if (Gun)
    { Gun->AmmoIncrease(); }
}

bool AMannequin::OutOfAmmo() const
{
    if (Gun)
    { return Gun->OutOfAmmo(); }

    return false;
}

void AMannequin::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Gun->Destroy();
}
