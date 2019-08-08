

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TGPlayerController.generated.h"


UCLASS()
class TESTINGGROUND_API ATGPlayerController : public APlayerController
{
	GENERATED_BODY()

 public:
     virtual void BeginPlay() override;
	
	
};
