// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

class AGun;
class UInputComponent;

UCLASS()
class TESTINGGROUND_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AGun> GunBlueprint;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual float TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
    float HealthCurrent;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullTrigger();

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	float SetHealthpack(float Healthpack);

	UFUNCTION(BlueprintCallable, Category = "Fire")
	int GetGunAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	int GetGunMaxAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsPlayerDead();

	void ReloadGun();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void ReloadDelayGun();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void AmmoIncrease();

    UFUNCTION(BlueprintCallable, Category = "Firing")
    bool OutOfAmmo() const;

	virtual void UnPossessed() override;
	void EnemyDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

private:

	void GunSetup();
	void PlayerDead();
	void UnPossessedDamage();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun* Gun = nullptr;

    float MovementZero = 0;
    float DestroyDelay = 2.0f;
    float ReloadDelay = 0.5f;


	const float HealthZero = 0.0f;
	const float HealthMax = 100.0f;
};
