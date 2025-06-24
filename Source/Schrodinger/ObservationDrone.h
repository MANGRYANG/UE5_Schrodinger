// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObservationDrone.generated.h"

UCLASS()
class SCHRODINGER_API AObservationDrone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObservationDrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// ���� Ʈ���̽��� �� �ٷ� ���� �� �����ϴ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObservationDrone")
	int32 NumberOfLines = 5;

	// ����� ������ ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObservationDrone")
	float ObservationAngle = 20.0f;

	// ����� ������ ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObservationDrone")
	float ObservationRange = 2500.0f;

public:
	UFUNCTION(BlueprintCallable, Category = "ObservationDrone")
	bool StartObservation();
};
