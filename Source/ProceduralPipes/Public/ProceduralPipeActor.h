// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PCGGraph.h"
#include "ProceduralPipeActor.generated.h"

//#define OVERRIDE_PCG_GRAPH_PROPERTY(Name, CategoryName, TooltipText) \
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CategoryName, \
//	meta = (InlineEditConditionToggle, Tooltip = TooltipText)) \
//bool bEnable##Name = false; \
//\
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CategoryName, \
//	meta = (EditCondition = "bEnable" #Name, EditConditionHides, Tooltip = TooltipText)) \
//TScriptInterface<UPCGGraphInterface> Name;
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

	



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|Joints")
	bool SpawnJoints = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|Joints", meta = (EditCondition = "SpawnJoints"))
	TSoftObjectPtr<UStaticMesh> JointMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|Joints", meta = (EditCondition = "SpawnJoints"))
	TSoftObjectPtr<UMaterialInterface> JointOverrideMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|Joints", meta = (EditCondition = "SpawnJoints"))
	bool SpawnMiddleJoints;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|ArrayMode")
	bool EnableArrayMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|ArrayMode", meta=(EditCondition="EnableArrayMode"))
	int Count = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|ArrayMode", meta=(EditCondition="EnableArrayMode"))
	float Spacing = 18.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|ArrayMode", meta=(EditCondition="EnableArrayMode"))
	FVector OffsetDirection = FVector(0.0, 0.0, 1.0);




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|OverrideGraphs", meta = (
		Tooltip="Use this to disable all override graphs for this asset.  Useful for debugging."))
	bool DisableAllOverrideGraphs;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|OverrideGraphs", meta = (InlineEditConditionToggle, EditCondition = "!DisableAllOverrideGraphs",
		Tooltip = "Final stage of processing which spawns Static Meshes. Override this to customize mesh spawning."))
	bool bEnableSpawnOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|OverrideGraphs", meta = (EditCondition = "bEnableSpawnOverride", 
		Tooltip = "Final stage of processing which spawns Static Meshes. Override this to customize mesh spawning."))
	TScriptInterface<UPCGGraphInterface> SpawnOverride;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pipes|OverrideGraphs",meta = (InlineEditConditionToggle, EditCondition = "!DisableAllOverrideGraphs",
		Tooltip = "Enables a Pre-Spawn Override Graph that processes ALL points before any meshes are spawned. This graph has global authority and can filter, merge, or modify points prior to the normal spawn behavior."))
	bool bEnablePreSpawnOverride;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|OverrideGraphs", meta = (EditCondition = "bEnablePreSpawnOverride", 
		Tooltip = "Graph executed before spawning begins. Receives the complete point set and must output the final points used for spawning. Use this to globally filter, merge, or preprocess points before any Spawn Override Graphs are evaluated."))
	TScriptInterface<UPCGGraphInterface> PreSpawnOverride;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|OverrideGraphs", meta = (InlineEditConditionToggle, EditCondition = "!DisableAllOverrideGraphs",
		Tooltip = "Enables a Post-Spawn Override Graph that runs after all meshes have been spawned. This graph is read-only and cannot modify spawn data, but can add secondary details or perform analysis based on the spawned results."))
	bool bEnablePostSpawnOverride;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipes|OverrideGraphs", meta = (EditCondition = "bEnablePostSpawnOverride",
		Tooltip = "Graph executed after all spawning is complete. Receives spawned meshes as input and may spawn additional effects, decorations, or data. This graph cannot alter the original spawn results."))
	TScriptInterface<UPCGGraphInterface> PostSpawnOverride;

	//OVERRIDE_PCG_GRAPH_PROPERTY(
	//	SpawnOverride,
	//	"Pipes|OverrideGraphs",
	//	"Final stage of processing which spawns Static Meshes. Override this to customize mesh spawning."
	//)
};
