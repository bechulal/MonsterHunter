// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/RealItem.h"
#include "Soul.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASoul : public ARealItem
{
	GENERATED_BODY()
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:

	UPROPERTY(EditAnywhere , Category = "Soul Properties")
	int32 Soul;
	
public:
	FORCEINLINE int32 GetSouls() const { return Soul; }
	FORCEINLINE void SetSouls(int32 NumberOfSouls)  { Soul = NumberOfSouls; }

};
