// Copyright (c) 2025 Max Harris
// Published by Procedural Architect


#include "ProceduralPipeActor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AProceduralPipeActor::AProceduralPipeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;
	//
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//BoundingBox->SetupAttachment(RootComponent);
	//BoundingBox->SetCollisionProfileName(TEXT("NoCollision"));
	//
	//UpdateBounds();
	//
	//Tags.AddUnique(FName("Pipe"));
	//if (IsBatched)
	//{
	//	Tags.AddUnique(FName("Batched"));
	//}
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoundingBox->SetupAttachment(RootComponent);
	BoundingBox->SetCollisionProfileName(TEXT("NoCollision"));

	// IMPORTANT: Do NOT call UpdateBounds() here.
	// Constructors run during CDO creation / async load where BP dispatch is unsafe.

	Tags.AddUnique(FName("Pipe"));
	// Also avoid tagging based on IsBatched here (see note below).
}

void AProceduralPipeActor::ComputeBoundingBox_Implementation(FVector& BoundsMin, FVector& BoundsMax)
{
	if (BoundingBox)
	{
		BoundsMin = FVector(-100, -100, -100);
		BoundsMax = -BoundsMin;
	}
}

void AProceduralPipeActor::UpdateBounds()
{
	FVector Min;
	FVector Max;
	ComputeBoundingBox(Min, Max);
	FVector Extents = ((Max - Min) * 0.5f) + BoundsPadding;
	FVector BoxOffset = (Extents + Min);
	BoundingBox->SetBoxExtent(Extents);
	BoundingBox->SetRelativeLocation(BoxOffset);
}

void AProceduralPipeActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Keep tags consistent with actual current property values
	Tags.AddUnique(FName("Pipe"));
	if (IsBatched)
	{
		Tags.AddUnique(FName("Batched"));
	}
	else
	{
		Tags.Remove(FName("Batched"));
	}

	UpdateBounds();
}

void AProceduralPipeActor::PostLoad()
{
	Super::PostLoad();

	// Avoid touching bounds on the CDO
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		UpdateBounds();
	}
}