// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PID_Controller.h"
#include "Copter.generated.h"


UCLASS(Blueprintable)
class COPTERPROJECT_API ACopter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACopter();
	
protected:
	
	// Updates current copter's state parameters (roll, pitch, yaw, altitude, etc.)
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	virtual void StateUpdate();

	// Updates copter's control input
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	virtual void ControlUpdate();

	// Initializes PID controller with new parameters
	virtual void InitializePid();

	// Updates PID's current state values (roll, pitch, yaw, altitude)
	virtual void PidUpdate();

	// Calculates PID value
	virtual void PidCompute();

	UPROPERTY(Category = "PID_Controller", VisibleAnywhere, BlueprintReadOnly)
		class UPID_Controller* RollContoller;

	UPROPERTY(Category = "PID_Controller", VisibleAnywhere, BlueprintReadOnly)
		class UPID_Controller* PitchController;

	UPROPERTY(Category = "PID_Controller", VisibleAnywhere, BlueprintReadOnly)
		class UPID_Controller* YawController;

	UPROPERTY(Category = "PID_Controller", VisibleAnywhere, BlueprintReadOnly)
		class UPID_Controller* AltitudeContoller;

	UPROPERTY(Category = "Copter", VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* Mesh;
	   
	bool bIsKeepBearing;
		
	UPROPERTY(BlueprintReadOnly)
		float RollIn;

	UPROPERTY(BlueprintReadOnly)
		float RollOut;

	UPROPERTY(BlueprintReadOnly)
		float PitchIn;

	UPROPERTY(BlueprintReadOnly)
		float PitchOut;

	UPROPERTY(BlueprintReadOnly)
		float YawIn;

	UPROPERTY(BlueprintReadOnly)
		float YawOut;

	UPROPERTY(BlueprintReadOnly)
		float AltitudeIn;

	UPROPERTY(BlueprintReadOnly)
		float AltitudeOut;


public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool InitializeCopter();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
		float AddCopterThrottleInput(float Axis);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
		float AddCopterRollInput(float Axis);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
		float AddCopterPitchInput(float Axis);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
		float AddCopterYawInput(float Axis);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
		bool StartFly();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Control")
		bool StopFly();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Control")
		bool UpdateMotorsCurrent();


	// Current Roll
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Roll;

	// Current Pitch
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Yaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Bearing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Throttle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Altitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		bool IsPowerOn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		int64 FlyTimeMillis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float Delta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
		FPID RollPID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Roll")
		float RollPidMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Roll")
		float RollPidMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Roll")
		float RollWMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Roll")
		float RollWMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State|Setpoints")
		float RollSetpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Axis")
		float RollAxis;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
		FPID PitchPID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Pitch")
		float PitchPidMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Pitch")
		float PitchPidMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Pitch")
		float PitchWMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Pitch")
		float PitchWMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State|Setpoints")
		float PitchSetpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Axis")
		float PitchAxis;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
		FPID YawPID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Yaw")
		float YawPidMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Yaw")
		float YawPidMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Yaw")
		float YawW;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State|Setpoints")
		float YawSetpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Axis")
		float YawAxis;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
		FPID AltitudePID;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Altitude")
		float AltitudePidMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Altitude")
		float AltitudePidMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Altitude")
		float AltitudeW;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State|Setpoints")
		float AltitudeSetpoint;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Throttle")
		float ThrottleMin = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Throttle")
		float ThrottleMid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Throttle")
		float ThrottleMax = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Throttle")
		float ThrottleZero;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Axis")
		float ThrottleAxis;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Current")
		float EngineMinCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Current")
		float EngineMidCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Current")
		float EngineMaxCurrent;	 
};
