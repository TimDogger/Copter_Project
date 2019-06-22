// Fill out your copyright notice in the Description page of Project Settings.


#include "Copter.h"
#include "Components/InputComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Controller.h"


// Sets default values
ACopter::ACopter()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));	
	RollContoller = CreateDefaultSubobject<UPID_Controller>(TEXT("RollContoller"));
	PitchController = CreateDefaultSubobject<UPID_Controller>(TEXT("PitchController"));
	YawController = CreateDefaultSubobject<UPID_Controller>(TEXT("YawController"));
	AltitudeContoller = CreateDefaultSubobject<UPID_Controller>(TEXT("AltitudeContoller"));
	
	RootComponent = Mesh; 

	RollContoller->Connect(&RollIn, &RollOut, &RollSetpoint, RollPID, DIRECT, &Delta);
	PitchController->Connect(&PitchIn, &PitchOut, &PitchSetpoint, PitchPID, DIRECT, &Delta);
	YawController->Connect(&YawIn, &YawOut, &YawSetpoint, YawPID, DIRECT, &Delta);
	AltitudeContoller->Connect(&AltitudeIn, &AltitudeOut, &AltitudeSetpoint, AltitudePID, DIRECT, &Delta);

	InitializePid();
	StateUpdate();
			
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACopter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ACopter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Delta = DeltaTime;
	if (IsPowerOn)
	{
		FlyTimeMillis += FMath::RoundToInt(DeltaTime * 1000);
		StateUpdate();
	}	
}

// Called to bind functionality to input
void ACopter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
		
}

float ACopter::AddCopterThrottleInput_Implementation(float Value)
{
	if (IsPowerOn)
	{
		//Throttle = FMath::GetMappedRangeValueClamped(FVector2D(0, 100), FVector2D(ThrottleZero,100), ((Value * 50) + 50));
		Throttle = (Value * 50) + 50;
		if (FMath::Abs(Value) >= 0.1) AltitudeSetpoint = Altitude + (Value * AltitudeW);
	}	
	return Throttle;
}

float ACopter::AddCopterRollInput_Implementation(float Value)
{
	float angle;
	if (IsPowerOn)
	{
		if (Value >= 0) angle = Value * RollWMax;
		else angle = FMath::Abs(Value) * RollWMin;
		RollSetpoint = FMath::Clamp(angle, RollWMin, RollWMax);
	}
	return RollSetpoint;
}

float ACopter::AddCopterPitchInput_Implementation(float Value)
{
	float angle;
	if (IsPowerOn)
	{
		if (Value >= 0) angle = Value * PitchWMax;
		else angle = FMath::Abs(Value) * PitchWMin;
		PitchSetpoint = FMath::Clamp(angle, PitchWMin, PitchWMax);
	}
	return PitchSetpoint;
}

float ACopter::AddCopterYawInput_Implementation(float Value)
{
	if (FMath::Abs(Value) > 0.1f && IsPowerOn)
	{
		float yawDelta = Value * YawW;

		YawSetpoint = yawDelta + Bearing;
		if (bIsKeepBearing && YawSetpoint > 0 && YawSetpoint < 360)
		{
			YawSetpoint = yawDelta + Yaw;
			bIsKeepBearing = false;
		}
		else if (YawSetpoint <= 0 || YawSetpoint >= 360)
		{
			bIsKeepBearing = true;
			Bearing = Yaw;
		}			
	}
	return YawSetpoint;
}

bool ACopter::StartFly_Implementation()
{
	IsPowerOn = true;
	FlyTimeMillis = 0;

	InitializePid();

	StateUpdate();

	YawSetpoint = Bearing;
	bIsKeepBearing = true;
	AltitudeSetpoint = Altitude - 100;
	RollSetpoint = Roll;
	PitchSetpoint = Pitch;
	return true;
}

bool ACopter::StopFly_Implementation()
{
	IsPowerOn = false;
	return true;
}

void ACopter::InitializePid()
{
	RollContoller->SetOutputLimits(RollPidMin, RollPidMax);
	PitchController->SetOutputLimits(PitchPidMin, PitchPidMax);
	YawController->SetOutputLimits(YawPidMin, YawPidMax);
	AltitudeContoller->SetOutputLimits(AltitudePidMin, AltitudePidMax);

	RollContoller->SetMode(AUTOMATIC);
	PitchController->SetMode(AUTOMATIC);
	YawController->SetMode(AUTOMATIC);
	AltitudeContoller->SetMode(AUTOMATIC);

	RollContoller->SetSampleTime(Delta);
	PitchController->SetSampleTime(Delta);
	YawController->SetSampleTime(Delta);
	AltitudeContoller->SetSampleTime(Delta);
}

void ACopter::PidUpdate()
{
	RollIn = Roll;
	PitchIn = Pitch;
	YawIn = Bearing;
	AltitudeIn = Altitude;
}

void ACopter::PidCompute()
{
	RollContoller->Compute();
	PitchController->Compute();
	YawController->Compute();
	AltitudeContoller->Compute();
}

// Called every tick to update copter state parameters
void ACopter::StateUpdate()
{
	Roll = GetActorRotation().Roll;
	Pitch = GetActorRotation().Pitch;
	Yaw = FMath::GetMappedRangeValueClamped(FVector2D(-180, 180), FVector2D(0, 360), GetActorRotation().Yaw);
	Altitude = GetActorLocation().Z;
	Speed = GetVelocity().Size();

	float delta = Yaw - Bearing;

		if (delta < -180) Bearing = 360 + Yaw;
		else if (delta > 180) Bearing = Yaw - 360;
			else Bearing = Yaw;
}

void ACopter::ControlUpdate()
{	
	PidUpdate();
	PidCompute();

	UpdateMotorsCurrent();
}
