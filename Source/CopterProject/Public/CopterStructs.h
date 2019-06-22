// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CopterStructs.generated.h"

USTRUCT(BlueprintType)
struct FCopterMotorRatio
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Roll;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Pitch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Yaw;

	FCopterMotorRatio();

	FCopterMotorRatio(float, float, float);

};

USTRUCT(BlueprintType)
struct FEngineInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Bone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Socket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName PropBone;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCopterMotorRatio Ratio;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Normal;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Current;

	FEngineInfo();

	FEngineInfo(FName NewBone, FName NewSocket, FName NewPropBone,
		FCopterMotorRatio NewRatio, FVector NewNormal, float NewCurrent);
};

USTRUCT(BlueprintType)
struct FEngineModel
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ModelName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Voltage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Kv;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MinCurrent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxCurrent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Resistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Mass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* ThrustCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	FEngineModel();

	FEngineModel(FName, float, float, float, float,
		float, float, UCurveFloat*, UStaticMeshComponent*);

};

