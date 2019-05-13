// Fill out your copyright notice in the Description page of Project Settings.


#include "Container.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AContainer::AContainer()
{
    HealthCurrent = HealthMax;
    FMath::Clamp(HealthCurrent, HealthZero, HealthMax);

    CanisterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CanisterMesh"));

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;

    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
    ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float AContainer::TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{


    if(HealthCurrent > HealthZero) { HealthCurrent = HealthCurrent - Damage; }

    if (HealthCurrent == HealthZero)
    {
        ImpactBlast->Activate();
        SetRootComponent(ImpactBlast);

        FTimerHandle Timer;
        GetWorld()->GetTimerManager().SetTimer(Timer, this, &AContainer::OnTimerExpire, DestroyDelay, false);
     /*   UGameplayStatics::ApplyRadialDamage(
            GetWorld(),
            10.0f,
            GetActorLocation(),
            ExplosionForce->Radius,
            UDamageType::StaticClass(),
            TArray<AActor*>()
            );*/
    }
    return HealthCurrent;
}

float AContainer::GetHealth() const
{
    return HealthCurrent / HealthMax;
}

void AContainer::OnTimerExpire()
{
    Destroy();
}


