// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CopterMotorInterface.h"
#include "CopterMotor.generated.h"

UCLASS()
class COPTERPROJECT_API ACopterMotor : public AActor, public ICopterMotorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACopterMotor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MotorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PropMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




};
