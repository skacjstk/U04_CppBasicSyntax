#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class U04_CPPBASICSYNTAX_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void ChangeBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

private:
	//Axis Mapping
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);

	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

	//Action Mapping
	void OnRun();
	void OffRun();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private:
	class UMaterialInstanceDynamic* BodyMaterialDynamic;
	class UMaterialInstanceDynamic* LogoMaterialDynamic;
};
