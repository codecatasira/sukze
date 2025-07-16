#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Roca.generated.h"

UCLASS()
class DS1_API ARoca : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoca();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roca|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roca|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roca|Properties")
	float RotationSpeed;
	

	virtual void Tick(float DeltaTime)override;


};
