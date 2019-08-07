//PROJECT: Testing Grounds
//AUTHOR: Preetpal Basson
//DESCRIPTION:

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MannequinHUD.generated.h"

UCLASS()
class AMannequinHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMannequinHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

