// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UPlayerSideviewCharacter.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AGeneralPlatform::AGeneralPlatform()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// ���� ���� �޽� ������Ʈ ����
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(Platform);  // PlatformMesh�� RootComponent�� ����

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	if (CubeMesh.Succeeded())
	{
		// ť�� �޽� �Ҵ�
		Platform->SetStaticMesh(CubeMesh.Object);
	}

	// ������ ���� �浹 ������Ʈ ����
	PlatformCollisionTop = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformCollisionTop"));
	PlatformCollisionTop->SetupAttachment(RootComponent);  // Cube�� ���� ������Ʈ�� ����

	// ������ �Ʒ��� �浹 ������Ʈ ����
	PlatformCollisionBottom = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformCollisionBottom"));
	PlatformCollisionBottom->SetupAttachment(RootComponent);  // Cube�� ���� ������Ʈ�� ����

	// �⺻ �� ����
	bIsPlayerOnPlatform = false;
}

// Called when the game starts or when spawned
void AGeneralPlatform::BeginPlay()
{
	Super::BeginPlay();

	// �浹 �̺�Ʈ ó��
	PlatformCollisionTop->SetGenerateOverlapEvents(true);
	PlatformCollisionBottom->SetGenerateOverlapEvents(true);

	PlatformCollisionTop->OnComponentBeginOverlap.AddDynamic(this, &AGeneralPlatform::TriggerEnter);
	PlatformCollisionTop->OnComponentEndOverlap.AddDynamic(this, &AGeneralPlatform::TriggerExit);

	PlatformCollisionBottom->OnComponentBeginOverlap.AddDynamic(this, &AGeneralPlatform::TriggerEnter);
	PlatformCollisionBottom->OnComponentEndOverlap.AddDynamic(this, &AGeneralPlatform::TriggerExit);

}

// Called every frame
void AGeneralPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// TriggerEnter�� ó���ϴ� �Լ�
void AGeneralPlatform::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �������Ǵ� ���Ͱ� �÷��̾� ĳ�������� Ȯ��
	if (Cast<AUPlayerSideviewCharacter>(OtherActor))
	{
		// ���� �浹 ������Ʈ�� �������� ���
		if (Cast<UBoxComponent>(HitComp) == PlatformCollisionTop)
		{
			// �÷��̾ ���� ���� �ö������ ����
			bIsPlayerOnPlatform = true;
		}
		// �Ʒ��� �浹 ������Ʈ�� �������� ���
		else if (Cast<UBoxComponent>(HitComp) == PlatformCollisionBottom)
		{
			// ������ �浹�� ��Ȱ��ȭ
			DisableCollision();
		}
	}
}

// TriggerExit�� ó���ϴ� �Լ�
void AGeneralPlatform::TriggerExit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// �������� ����� ���Ͱ� �÷��̾� ĳ�������� Ȯ��
	if (Cast<AUPlayerSideviewCharacter>(OtherActor))
	{
		// ���� �浹 ������Ʈ���� �������� ����� ���
		if (HitComp == PlatformCollisionTop)
		{
			// �÷��̾ ���� ���� ���� ������ ����
			bIsPlayerOnPlatform = false;
		}
		// �Ʒ��� �浹 ������Ʈ���� �������� ����� ���
		else if (HitComp == PlatformCollisionBottom)
		{
			// ������ �浹�� Ȱ��ȭ
			EnableCollision();
		}
	}
}

// ������ �浹�� Ȱ��ȭ�ϴ� �Լ�
void AGeneralPlatform::EnableCollision()
{
	// Pawn ä�ο� ���� �浹�� Block���� �����Ͽ� ĳ���Ϳ� ���� ������ �浹�� Ȱ��ȭ
	Platform->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

// ������ �浹�� ��Ȱ��ȭ�ϴ� �Լ�
void AGeneralPlatform::DisableCollision()
{
	// Pawn ä�ο� ���� �浹�� Ignore���� �����Ͽ� ĳ���Ϳ� ���� ������ �浹�� ��Ȱ��ȭ
	Platform->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}