#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rota.generated.h"

UCLASS()
class DS1_API ARota : public AActor
{
	GENERATED_BODY()
	
public:	
	ARota();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rota|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rota|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rota|Properties")
	float RotationSpeed;
	FVector StratLocation;
	float RunningTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rota|Properties")
	float Amplitude=50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rota|Properties")
	float Frequency=1.f;


	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
};
