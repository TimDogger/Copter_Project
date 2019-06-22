// Fill out your copyright notice in the Description page of Project Settings.


#include "PD_Controller.h"

// Sets default values for this component's properties
UPD_Controller::UPD_Controller()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPD_Controller::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPD_Controller::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

