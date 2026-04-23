


#include "Items/RealItem.h"
#include "MyProject/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Interfaces/PickupInterface.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"




ARealItem::ARealItem()
{
 	
	PrimaryActorTick.bCanEverTick = true;

    ItemMesh =	CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	ItemEffect->SetupAttachment(GetRootComponent());

}


void ARealItem::BeginPlay()
{
	Super::BeginPlay();

	//SetActorLocation(FVector(0.f, 0.f, 100.f));
	//UWorld* World = GetWorld();
	//FVector Actor_Location = GetActorLocation();
	//FVector Location = GetActorLocation();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARealItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ARealItem::OnSphereEndOverlap);

	
}

float ARealItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float ARealItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void ARealItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(this);
	}
}

void ARealItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}

}

void ARealItem::SpawnPickupSystem()
{
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PickupEffect,
			GetActorLocation()
		);
	}
}

void ARealItem::SpawnPickupSound()
{
	if (PickupSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());

	}
}


void ARealItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FRotator NewRotation = GetActorRotation();
	//NewRotation.Yaw  += 90.f * DeltaTime;
	
	//SetActorRotation(NewRotation);

	RunningTime += DeltaTime;

	if (ItemState  == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}



	
}

