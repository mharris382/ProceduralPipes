// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCGGraph.h"
#include "ProceduralPipeActor.generated.h"


#define OVERRIDE_PCG_GRAPH_PROPERTY(DisplayName, CategoryName, TooltipText) \
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CategoryName, meta = (InlineEditConditionToggle, DisplayName = DisplayName)) \
bool bEnable##DisplayName = false; \
\
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CategoryName, meta = (EditCondition = "DisableAllOverrideGraphs || bEnable" #DisplayName, Tooltip=TooltipText)) \
TScriptInterface<UPCGGraphInterface> DisplayName;

//USTRUCT(BlueprintType)
//struct PROCEDURALPIPES_API FPipePartConfig
//{
//	GENERATED_BODY();
//
//	FPipePartConfig() = default;
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PipePart")
//	//TSoftObjectPtr<UStaticMesh> Mesh;
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PipePart")
//	TSoftObjectPtr<UMaterialInterface> PartOverrideMaterial;
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PipePart", meta = (ClampMin = "0.01"))
//	float PartScale = 1.0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PipePart")
//	FRotator PartRotation;
//
//
//
//};


USTRUCT(BlueprintType)
struct PROCEDURALPIPES_API FOverrideablePCGGraph
{
	GENERATED_BODY();

	FOverrideablePCGGraph() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides")
	bool EnableOverrideGraph;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overrides", meta = (EditCondition = "EnableOverrideGraph"))
	TScriptInterface<UPCGGraphInterface> OverrideGraph;
};


UCLASS(Abstract, BlueprintType)
class PROCEDURALPIPES_API AProceduralPipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralPipeActor();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes", meta = (ClampMin = "0.01"))
	float PipeScale = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes")
	TSoftObjectPtr<UMaterialInterface> OverrideMaterial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes")
	TSoftObjectPtr<UStaticMesh> StraightMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes")
	TSoftObjectPtr<UStaticMesh> CornerMesh;

	



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joints")
	bool SpawnJoints = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joints", meta = (EditCondition = "SpawnJoints"))
	TSoftObjectPtr<UStaticMesh> JointMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joints", meta = (EditCondition = "SpawnJoints"))
	TSoftObjectPtr<UMaterialInterface> JointOverrideMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joints", meta = (EditCondition = "SpawnJoints"))
	bool SpawnMiddleJoints;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArrayMode")
	bool EnableArrayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArrayMode", meta=(EditCondition="EnableArrayMode"))
	int Count = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArrayMode", meta=(EditCondition="EnableArrayMode"))
	float Spacing = 18.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArrayMode", meta=(EditCondition="EnableArrayMode"))
	FVector OffsetDirection = FVector(0.0, 0.0, 1.0);




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverrideGraphs", meta = (Tooltip="Use this to disable all override graphs for this asset.  Useful for debugging."))
	bool DisableAllOverrideGraphs;

	OVERRIDE_PCG_GRAPH_PROPERTY(SpawnOverrideGraph, "OverrideGraphs", "Final Stage of processing which spawns Static Meshes.  Override this to process and/or change how the static meshes are spawned")
};
