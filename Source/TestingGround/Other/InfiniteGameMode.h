// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Other/TGGameMode.h"
#include "InfiniteGameMode.generated.h"

class ANavMeshBoundsVolume;

UCLASS()
class TESTINGGROUND_API AInfiniteGameMode : public ATGGameMode
{
	GENERATED_BODY()

public:
	AInfiniteGameMode();
	UFUNCTION(BlueprintCallable, Category = "Bounds")
	void PopulateBoundsVolumePool();

	UFUNCTION(BlueprintPure, Category = "Score")
	int GetScore();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;

	int ScoreValue = 0;

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);



};
