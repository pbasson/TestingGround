// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPowerUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Mannequin.h"

// Sets default values
AAmmoPowerUp::AAmmoPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(Radius);
	CollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = CollisionSphere;

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	AmmoMesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	AmmoMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPowerUp::OnOverlapBegin);

}

void AAmmoPowerUp::OnOverlapBegin(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->GetName() == "Player"))
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAPPED"))
		AmmoIncrease(OtherActor);	}
}

void AAmmoPowerUp::AmmoIncrease(AActor * OtherActor)
{
	class AMannequin* OtherCharacter = Cast<AMannequin>(OtherActor);

	if (OtherCharacter != nullptr && AmmoSound != nullptr)
	{
		OtherCharacter->AmmoIncrease();
		UGameplayStatics::PlaySoundAtLocation(this, AmmoSound, GetActorLocation());

		Destroy();
	}
}

// Called when the game starts or when spawned
void AAmmoPowerUp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAmmoPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

