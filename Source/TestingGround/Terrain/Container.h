//PROJECT: Testing Grounds
//AUTHOR: Preetpal Basson
//DESCRIPTION:

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Container.generated.h"

class UGameplayStatics;
class UStaticMeshComponent;
class UDamageType;
class URadialForceComponent;
class UParticleSystemComponent;

UCLASS()
class TESTINGGROUND_API AContainer : public AActor
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

    AContainer();
	virtual void Tick(float DeltaTime) override;

    float TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser);
    float GetHealth() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class USoundBase* CollectSound;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* ImpactBlast;

    URadialForceComponent* ExplosionForce;

    void OnTimerExpire();

private:

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    UStaticMeshComponent* CanisterMesh;

    float HealthCurrent;
    float HealthMax = 60.0f;
    float HealthZero = 0.0f;
    float DestroyDelay = 0.25f;
    };
