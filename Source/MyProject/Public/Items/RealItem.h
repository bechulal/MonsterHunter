

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealItem.generated.h"

class USphereComponent;

UCLASS()
class MYPROJECT_API ARealItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ARealItem();
	virtual void Tick(float DeltaTime) override;
protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;


	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

	enum class EItemState : uint8
	{
		EIS_Hovering,
		EIS_Equipped
	};
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Sine Parameters")
	float Amplitude = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();
	
	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* ItemEffect;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess =" true"))
	float RunningTime;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* PickupEffect;
};
