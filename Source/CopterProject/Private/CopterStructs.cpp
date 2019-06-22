// Fill out your copyright notice in the Description page of Project Settings.


#include "CopterStructs.h"
#include "Curves/CurveFloat.h"


FCopterMotorRatio::FCopterMotorRatio()
{
	Roll = 0.0f;
	Pitch = 0.0f;
	Yaw = 0.0f;
}

FCopterMotorRatio::FCopterMotorRatio(float NewRoll, float NewPitch, float NewYaw)
{
	Roll = NewRoll;
	Pitch = NewPitch;
	Yaw = NewYaw;
}

FEngineInfo::FEngineInfo()
{
	Bone = "";
	Socket = "";
	PropBone = "";
	Ratio = FCopterMotorRatio();
	Normal = FVector();
	Current = 0.0f;
}

FEngineInfo::FEngineInfo(FName NewBone, FName NewSocket, FName NewPropBone, 
	FCopterMotorRatio NewRatio, FVector NewNormal, float NewCurrent)
{
	Bone = NewBone;
	Socket = NewSocket;
	PropBone = NewPropBone;
	Ratio = NewRatio;
	Normal = NewNormal;
	Current = NewCurrent;	
}

FEngineModel::FEngineModel(){}

FEngineModel::FEngineModel(FName NewModelName, float NewVoltage, float NewKv, float NewMinCurrent, float NewMaxCurrent, 
	float NewResistance, float NewMass, UCurveFloat* NewThrustCurve, UStaticMeshComponent* NewMesh)
{
	ModelName = NewModelName;
	Voltage = NewVoltage;
	Kv = NewKv;
	MinCurrent = NewMinCurrent;
	MaxCurrent = NewMaxCurrent;
	Resistance = NewResistance;
	Mass = NewMass;
	ThrustCurve = NewThrustCurve;
	Mesh = NewMesh;
}
