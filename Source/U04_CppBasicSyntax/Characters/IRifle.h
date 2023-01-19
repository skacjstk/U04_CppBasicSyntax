#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IRifle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIRifle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class U04_CPPBASICSYNTAX_API IIRifle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class ACRifle* GetRifle() = 0;
	virtual void GetAimInfo(FVector& OutAimStart, FVector & OutAimEnd, FVector& OutAimDirection) = 0;

	virtual void OnTarget() {};
	virtual void OffTarget() {};
};
