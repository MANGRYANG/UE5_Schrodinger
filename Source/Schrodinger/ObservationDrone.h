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
	// 라인 트레이스를 몇 줄로 나눌 지 결정하는 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObservationDrone")
	int32 NumberOfLines = 5;

	// 드론이 관측할 범위 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObservationDrone")
	float ObservationAngle = 20.0f;

	// 드론이 관측할 범위의 길이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObservationDrone")
	float ObservationRange = 2500.0f;

public:
	UFUNCTION(BlueprintCallable, Category = "ObservationDrone")
	bool StartObservation();
};
