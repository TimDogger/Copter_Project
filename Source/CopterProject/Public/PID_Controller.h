// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PID_Controller.generated.h"


USTRUCT(BlueprintType)
struct FPID
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float P;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float I;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float D;

	FPID();
	
	FPID(float, float, float);

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class COPTERPROJECT_API UPID_Controller : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPID_Controller();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetTunings(FPID Pid);
	

#define AUTOMATIC	1
#define MANUAL	0
#define DIRECT  0
#define REVERSE  1

	void Connect(float* Input, float* Output, float* Setpoint,
		FPID NewPid, int ControllerDirection, float* NewDeltaTime);
	
	UFUNCTION(BlueprintCallable)
	void SetMode(int Mode);

	UFUNCTION(BlueprintCallable)
	bool Compute();

	UFUNCTION(BlueprintCallable)
	void SetOutputLimits(float Min, float Max);
 
	UFUNCTION(BlueprintCallable)
	void SetControllerDirection(int Direction);

	UFUNCTION(BlueprintCallable)											
	void SetSampleTime(float NewSampleTime);

	FPID GetPid();

	UFUNCTION(BlueprintCallable)
	int GetMode();						  //  inside the PID.

	UFUNCTION(BlueprintCallable)
	int GetDirection();		

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsEnabled = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int controllerDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FPID Pid;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int64 SampleTime;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float SampleTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float OutMin;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float OutMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bInAuto;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int64 LastTime;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float ITerm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float LastInput;

private:
	void Initialize();

	float GetError(float, float);

	FPID DispPid;		
	
	float* DeltaTime;
		
	int64* Millis;

	float* MyInput;

	float* MyOutput;

	float* MySetpoint;

	
	
};
