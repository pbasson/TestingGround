//AUTHOR:PREETPAL_BASSON
//PURPOSE :

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:
		UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray<AActor*> PatrolPoints;

};
