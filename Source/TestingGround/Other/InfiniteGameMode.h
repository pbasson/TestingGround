//PROJECT: Testing Grounds
//AUTHOR: Preetpal Basson
//DESCRIPTION:

#pragma once

#include "CoreMinimal.h"
#include "Other/TGGameMode.h"
#include "InfiniteGameMode.generated.h"

class ANavMeshBoundsVolume;
class ATile;

UCLASS()
class TESTINGGROUND_API AInfiniteGameMode : public ATGGameMode
{
	GENERATED_BODY()

public:
	AInfiniteGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Bounds")
	void PopulateBoundsVolumePool();

	UFUNCTION(BlueprintPure, Category = "Score")
	FString GetScoreValue();

	UFUNCTION(BlueprintCallable, Category = "Score")
	int SetScoreValue();

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<ATile> Tile_BP;

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void Restart();

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void NewGame();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	void CheckMenu();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
    class UActorPool* NavMeshPool;

	int ScoreValue;
	FTransform NextTilePos;
	

	bool GamePaused = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

};
