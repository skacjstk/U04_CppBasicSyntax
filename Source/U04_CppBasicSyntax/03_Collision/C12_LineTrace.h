#pragma once

#include "CoreMinimal.h"
#include "03_Collision/C00_TextRenderBase.h"
#include "C12_LineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceEvent, class AActor*, InActor, FLinearColor, InColor);

				// DelegateName, Param1Type, Param1Name, Param2Type, Param2Name
UCLASS()
class U04_CPPBASICSYNTAX_API AC12_LineTrace : public AC00_TextRenderBase
{
	GENERATED_BODY()

public:
	AC12_LineTrace();
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void Ragdoll(class AActor* InActor, FLinearColor InColor);
public:
	UPROPERTY(BlueprintAssignable)
		FLineTraceEvent OnLineTraceEvent;
private:
	class AC11_LineTracePoint* Cylinders[2];
};
