#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Unequip.generated.h"

/**
 * 
 */
UCLASS()
class U04_CPPBASICSYNTAX_API UCAnimNotifyState_Unequip : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	// name 가져오는건 
	FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
//	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) const;
};
