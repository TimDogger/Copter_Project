// Fill out your copyright notice in the Description page of Project Settings.


#include "PID_Controller.h"

FPID::FPID()
{

}

FPID::FPID(float NewP, float NewI, float NewD)
{	
	P = NewP;
	I = NewI;
	D = NewD;
}


/*
// Sets default values for this component's properties
UPID_Controller::UPID_Controller()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	//UPID_Controller::bAutoActivate = true;


	// ...
}


// Called when the game starts
void UPID_Controller::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPID_Controller::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}*/

void UPID_Controller::Connect(float* Input, float* Output, float* Setpoint,
	FPID NewPid, int ControllerDirection, float* NewDeltaTime)
{
	DeltaTime = NewDeltaTime;
	MyOutput = Output;
	MyInput = Input;
	MySetpoint = Setpoint;
	bInAuto = false;
	SampleTime = 0.01;

	SetOutputLimits(-100, 100);			

	SetControllerDirection(ControllerDirection);
}

/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/

bool UPID_Controller::Compute()
{
	if (!bIsEnabled)
	{
		*MyOutput = 0;
		return false;
	}
	if (!bInAuto) return false;
		/*Compute all the working error variables*/
		float input = *MyInput;
		float delta = *MySetpoint - input;
		float error;

		/*if (FMath::Abs(delta) > 0.1f)
		{
			if (delta <= 180) error = delta;
			else if (delta > 180) error = delta - 360;
		}
		else error = 0;*/
			
		error = delta;

		ITerm += (Pid.I * error);
		if (ITerm > OutMax) ITerm = OutMax;
		else if (ITerm < OutMin) ITerm = OutMin;
		float dInput = (input - LastInput);

		/*Compute PID Output*/
		float output = Pid.P * error + ITerm - Pid.D * dInput;

		if (output > OutMax) output = OutMax;
		else if (output < OutMin) output = OutMin;
		*MyOutput = output;

		/*Remember some variables for next time*/
		LastInput = input;
		return true;
}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void UPID_Controller::SetTunings(FPID NewPid)
{
	if (NewPid.P < 0 || NewPid.I < 0 || NewPid.D < 0) return;

	DispPid.P = NewPid.P; DispPid.I = NewPid.I; DispPid.D = NewPid.D;

	float SampleTimeInSec = SampleTime;
	
	Pid.P = NewPid.P / 1000;
	Pid.I = NewPid.I * SampleTimeInSec / 1000;
	Pid.D = NewPid.D / SampleTimeInSec / 1000;

	if (controllerDirection == REVERSE)
	{
		Pid.P = (0 - Pid.P);
		Pid.I = (0 - Pid.I);
		Pid.D = (0 - Pid.D);
	}
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/


void UPID_Controller::SetSampleTime(float NewSampleTime)
{
	if (NewSampleTime > 0)
	{
		float ratio = NewSampleTime / SampleTime;
		Pid.I *= ratio;
		Pid.D /= ratio;
		SampleTime = NewSampleTime;
	}
}

void UPID_Controller::SetOutputLimits(float Min, float Max)
{
	if (Min >= Max) return;
	OutMin = Min;
	OutMax = Max;

	if (bInAuto)
	{
		if (*MyOutput > OutMax)* MyOutput = OutMax;
		else if (*MyOutput < OutMin)* MyOutput = OutMin;

		if (ITerm > OutMax) ITerm = OutMax;
		else if (ITerm < OutMin) ITerm = OutMin;
	}
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void UPID_Controller::SetMode(int Mode)
{
	bool newAuto = (Mode == AUTOMATIC);
	if (newAuto == !bInAuto)
	{  /*we just went from manual to auto*/
		UPID_Controller::Initialize();
	}
	bInAuto = newAuto;
}

/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void UPID_Controller::Initialize()
{
	ITerm = *MyOutput;
	LastInput = *MyInput;
	if (ITerm > OutMax) ITerm = OutMax;
	else if (ITerm < OutMin) ITerm = OutMin;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void UPID_Controller::SetControllerDirection(int Direction)
{
	if (bInAuto && Direction != controllerDirection)
	{
		Pid.P = (0 - Pid.P);
		Pid.I = (0 - Pid.I);
		Pid.D = (0 - Pid.D);
	}
	controllerDirection = Direction;
}

FPID UPID_Controller::GetPid() { return DispPid; }
int UPID_Controller::GetMode() { return  bInAuto ? AUTOMATIC : MANUAL; }
int UPID_Controller::GetDirection() { return controllerDirection; }

