#include "CPlayer.h"
#include "Global.h"
#include "CAnimInstance.h"
#include "Weapons/CRifle.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/UserWidget.h"
#include "widgets/CUserWidget_Aim.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create Scene Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	//Set SkeletalMesh(Mannequin)
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (meshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(meshAsset.Object);

	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));

	ConstructorHelpers::FClassFinder<UCAnimInstance> animClass(TEXT("AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'"));
	if (animClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(animClass.Class);

	// Widget Asset Load
	ConstructorHelpers::FClassFinder<UCUserWidget_Aim> aimWidgetClass(TEXT("WidgetBlueprint'/Game/Widgets/WB_Aim.WB_Aim_C'"));
	if (aimWidgetClass.Succeeded())
		AimWidgetClass = aimWidgetClass.Class;

	//Component Settings
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(60, 0, 0);

	//Movement Settings
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	UObject* obj;

	//Body Material Asset
	obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'"));
	UMaterialInstanceConstant* bodyMaterialAsset = Cast<UMaterialInstanceConstant>(obj);
	if (bodyMaterialAsset == nullptr) return;

	//Logo Material Asset
	obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'"));
	UMaterialInstanceConstant* logoMaterialAsset = Cast<UMaterialInstanceConstant>(obj);
	if (logoMaterialAsset == nullptr) return;

	//Create Dynamic Material
	BodyMaterialDynamic = UMaterialInstanceDynamic::Create(bodyMaterialAsset, nullptr);
	LogoMaterialDynamic = UMaterialInstanceDynamic::Create(logoMaterialAsset, nullptr);

	//Set Material to SkeMeshComp
	GetMesh()->SetMaterial(0, BodyMaterialDynamic);
	GetMesh()->SetMaterial(1, LogoMaterialDynamic);

	Rifle = ACRifle::Spawn(GetWorld(), this);

	OnRifle();

	// Create Widget
	AimWidget = CreateWidget<UCUserWidget_Aim, APlayerController>(GetController<APlayerController>(), AimWidgetClass);
	AimWidget->AddToViewport();
	AimWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);

	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ACPlayer::OnInteract);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

}

void ACPlayer::ChangeBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterialDynamic->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterialDynamic->SetVectorParameterValue("BodyColor", InLogoColor);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	AddControllerYawInput(InAxis);
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	AddControllerPitchInput(InAxis);
}

void ACPlayer::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::OnInteract()
{
	if (OnInteractEvent.IsBound())
		OnInteractEvent.Broadcast();
}

void ACPlayer::OnRifle()
{
	if (Rifle->IsEquipped())
	{
		OffAim();
		Rifle->Unequip();
		return;
	}
	else {
		Rifle->Equip();
	}
}

void ACPlayer::OnAim()
{
	if(Rifle->IsEquipped() == false || Rifle->IsEquipping() == true) return;
	

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10);

	ZoomIn();
	Rifle->BeginAiming();

	AimWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACPlayer::OffAim()
{
	if (Rifle->IsEquipped() == false || Rifle->IsEquipping() == true) return;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SocketOffset = FVector(0,60,0);

	ZoomOut();
	Rifle->EndAiming();
	AimWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = Camera->GetForwardVector();
	FTransform cameraTransform = Camera->GetComponentToWorld();
	FVector cameraLocation = cameraTransform.GetLocation();	// 카메라의 월드상의 위치
	OutAimStart = cameraLocation + OutAimDirection * 100.f;

	FVector recoilCone = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutAimDirection, 0.2f);
	OutAimEnd = OutAimStart + recoilCone * 3000.f;	// 30미터 바깥의 랜덤 
}

void ACPlayer::OnTarget()
{
	AimWidget->OnTarget();
}

void ACPlayer::OffTarget()
{
	AimWidget->OffTarget();
}
