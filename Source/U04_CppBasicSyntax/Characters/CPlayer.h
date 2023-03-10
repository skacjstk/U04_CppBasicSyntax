#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IRifle.h"
#include "CPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractEvent);

UCLASS()
class U04_CPPBASICSYNTAX_API ACPlayer : public ACharacter, public IIRifle
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Zoom")
		void ZoomIn();
	UFUNCTION(BlueprintImplementableEvent, Category = "Zoom")
		void ZoomOut();

public:
	// IRifle Implement
	FORCEINLINE class ACRifle* GetRifle() override { return Rifle; };
	void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) override;
	void OnTarget() override;
	void OffTarget() override;


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

	void OnInteract();
	void OnRifle();

	void OnAim();
	void OffAim();

	void OnFire();
	void OffFire();

	void OnAutoFire();

public:

	UPROPERTY()
		FInteractEvent OnInteractEvent;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UCUserWidget_Aim> AimWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
		TSubclassOf<class UCUserWidget_AutoFire> AutoFireWidgetClass;
private:
	class UMaterialInstanceDynamic* BodyMaterialDynamic;
	class UMaterialInstanceDynamic* LogoMaterialDynamic;

	class ACRifle* Rifle;
	class UCUserWidget_Aim* AimWidget;
	class UCUserWidget_AutoFire* AutoFireWidget;

};
