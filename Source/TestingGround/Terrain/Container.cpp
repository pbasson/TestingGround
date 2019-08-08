//PROJECT: Testing Grounds
//AUTHOR: Preetpal Basson
//DESCRIPTION:

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
    RootComponent = CanisterMesh;

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
    if(HealthCurrent > HealthZero)
    { HealthCurrent = HealthCurrent - Damage; }

    if (HealthCurrent == HealthZero)
    {
        ImpactBlast->Activate();
        SetRootComponent(ImpactBlast);
        UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());

        FTimerHandle Timer;
        GetWorld()->GetTimerManager().SetTimer(Timer, this, &AContainer::OnTimerExpire, DestroyDelay, false);
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

//TODO: Create Function so Manniquin () takes damage
