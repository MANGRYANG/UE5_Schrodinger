// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneralPlatform.generated.h"


UCLASS()
class SCHRODINGER_API AGeneralPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 발판의 정적 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	UStaticMeshComponent* Platform;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	// 발판의 위쪽 충돌 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* PlatformCollisionTop;

	// 발판의 아래쪽 충돌 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* PlatformCollisionBottom;

	// 플레이어 캐릭터가 발판 위에 올라와 있는지 여부를 나타내는 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerStatus")
	bool bIsPlayerOnPlatform;

	// 플레이어 캐릭터를 참조하기 위한 변수
	UPROPERTY()
	class AUPlayerSideviewCharacter* PlayerCharacter;

public:
	// 충돌이 시작될 때 호출되는 함수
	UFUNCTION()
	void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 충돌이 종료될 때 호출되는 함수
	UFUNCTION()
	void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 발판의 충돌을 활성화하는 함수
	UFUNCTION(BlueprintCallable)
	void EnableCollision();

	// 발판의 충돌을 비활성화하는 함수
	UFUNCTION(BlueprintCallable)
	void DisableCollision();
};
