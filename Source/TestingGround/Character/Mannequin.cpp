// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"


void AMannequin::OnFire()
{
	if (Gun) { Gun->OnFire(); }
}

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

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
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	GunSetup();
}

void AMannequin::GunSetup()
{

	UE_LOG(LogTemp, Warning, TEXT("GUNSETUP"));
	if (GunBlueprint == NULL) { return; }

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	// AttachToComponent to Socket of the Skeleton
	Gun->AttachToComponent(FPMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	Gun->AnimInstance = FPMesh->GetAnimInstance();
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

