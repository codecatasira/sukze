#include "MyPawn.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	CapsuleComponent->SetSimulatePhysics(false);

	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetSimulatePhysics(false);

	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength=300.0f;

	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}
void AMyPawn::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector=value.Get<FVector2D>();

	AddActorLocalRotation(FRotator(0.f,LookAxisVector.X * LookSpeed * GetWorld()->GetDeltaSeconds(),0.f));

	FRotator CurrentSpringArmRotation=SpringArm->GetRelativeRotation();
	
	float NewPitch=CurrentSpringArmRotation.Pitch-LookAxisVector.Y*LookSpeed*GetWorld()->GetDeltaSeconds();
	NewPitch=FMath::Clamp(NewPitch,-75.f,0.f);
	SpringArm->SetRelativeRotation(FRotator(NewPitch,0.f,0.f));
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController=Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem
			<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}
}
void AMyPawn::Move(const FInputActionValue& value)
{
	CurrentMoveInput = value.Get<FVector2D>();
}
void AMyPawn::StopMove(const FInputActionValue& value)
{
	CurrentMoveInput = FVector2D::ZeroVector;
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&AMyPawn::Move);
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Completed,
			this,
			&AMyPawn::StopMove);
		EnhancedInputComponent->BindAction(
			LookAction,
			ETriggerEvent::Triggered,
			this,
			&AMyPawn::Look);
		
	}
	
}



void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DeltaLocation(CurrentMoveInput.X,CurrentMoveInput.Y,0.0f);
	
	DeltaLocation.Normalize();

	AddActorLocalOffset(DeltaLocation*MoveSpeed*DeltaTime);

}