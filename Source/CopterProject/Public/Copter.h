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
	

private:


protected:
	
	UFUNCTION(BlueprintCallable)
	void StateUpdate();

	UFUNCTION (BlueprintCallable)
	void ControlUpdate();

	virtual void InitializePid();

	virtual void PidUpdate();

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



	int64* Millis;

	bool bIsKeepBearing;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control")
		float RollIn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		float RollOut;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control")
		float PitchIn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		float PitchOut;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Control")
		float YawIn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		float YawOut;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		float AltitudeIn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
		float RollPidMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
		float PitchPidMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
		float YawPidMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|PID")
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
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Configuration|Throttle")
		float ThrottleMin = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Throttle")
		float ThrottleMid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Configuration|Throttle")
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
