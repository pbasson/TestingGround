// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	OutAmmo,
	Aiming,
	Reloading
};


UCLASS()
class TESTINGGROUND_API AGun : public AActor
{
	GENERATED_BODY()

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

public:	
	// Sets default values for this actor's properties
	AGun();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class AGunProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimationFP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimationTP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimInstance* AnimInstanceFP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimInstance* AnimInstanceTP;

	UFUNCTION(BlueprintCallable, Category = "Input")
    void OnFire();

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetAmmo() const;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int AmmoCurrent;
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetMaxAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ReloadGun();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void AmmoIncrease();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	const int AmmoClip = 18;

	int AmmoReminder;

	void InitialFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;



};
