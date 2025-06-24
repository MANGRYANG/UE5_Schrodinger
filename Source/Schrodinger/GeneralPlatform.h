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
	// ������ ���� �޽� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	UStaticMeshComponent* Platform;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	// ������ ���� �浹 ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* PlatformCollisionTop;

	// ������ �Ʒ��� �浹 ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* PlatformCollisionBottom;

	// �÷��̾� ĳ���Ͱ� ���� ���� �ö�� �ִ��� ���θ� ��Ÿ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerStatus")
	bool bIsPlayerOnPlatform;

	// �÷��̾� ĳ���͸� �����ϱ� ���� ����
	UPROPERTY()
	class AUPlayerSideviewCharacter* PlayerCharacter;

public:
	// �浹�� ���۵� �� ȣ��Ǵ� �Լ�
	UFUNCTION()
	void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// �浹�� ����� �� ȣ��Ǵ� �Լ�
	UFUNCTION()
	void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// ������ �浹�� Ȱ��ȭ�ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void EnableCollision();

	// ������ �浹�� ��Ȱ��ȭ�ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void DisableCollision();
};
