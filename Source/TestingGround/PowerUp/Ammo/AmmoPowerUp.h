// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoPowerUp.generated.h"

class UGameplayStatics;
class AMannequin;

UCLASS()
class TESTINGGROUND_API AAmmoPowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPowerUp();

	UPROPERTY(EditAnywhere, Category = "Collision")
	class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* AmmoMesh;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* AmmoSound;

	void AmmoIncrease(AActor * OtherActor);
	float Radius = 100.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
