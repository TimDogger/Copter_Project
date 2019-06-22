// Fill out your copyright notice in the Description page of Project Settings.


#include "CopterMotor.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACopterMotor::ACopterMotor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MotorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MotorMesh"));
	PropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropMesh"));
	RootComponent = MotorMesh;
	PropMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACopterMotor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACopterMotor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

