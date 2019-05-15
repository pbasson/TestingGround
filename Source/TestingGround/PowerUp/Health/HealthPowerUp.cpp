//AUTHOR: PREETPAL BASSON 

#include "HealthPowerUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AHealthPowerUp::AHealthPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(Radius);
	CollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = CollisionSphere;

	HealthMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthMesh"));
	HealthMesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthPowerUp::OnOverlapBegin);
}


void AHealthPowerUp::BeginPlay()
{
	Super::BeginPlay();
	


	
}



void AHealthPowerUp::OnOverlapBegin(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->GetName() == "Player"))
	{
		UE_LOG(LogTemp, Warning, TEXT("OverLap: %s"), *OtherActor->GetName());



		Destroy();
	}
	

}

void AHealthPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



