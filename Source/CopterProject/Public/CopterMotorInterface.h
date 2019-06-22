// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CopterMotorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UCopterMotorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COPTERPROJECT_API ICopterMotorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MotorControl")
	float SetCurrent(float NewCurrent);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable,  Category = "MotorControl")
	float SetMidThrottle(float MidThrust);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MotorControl")
	float SetThrottle(float NewThrottle);

};
