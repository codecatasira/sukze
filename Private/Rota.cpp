#include "Rota.h"

ARota::ARota()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);


	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;



}
void ARota::BeginPlay()
{
	Super::BeginPlay();
	StratLocation = GetActorLocation();
	RunningTime = 0.f;
}


void ARota::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f , RotationSpeed * DeltaTime,0.0f ));
	}
	RunningTime += DeltaTime;
	float DeltaHeight = Amplitude * FMath::Sin(Frequency * RunningTime * 2 * PI);

	FVector NewLocation = StratLocation;
	NewLocation.Z += DeltaHeight;

	SetActorLocation(NewLocation);

}


