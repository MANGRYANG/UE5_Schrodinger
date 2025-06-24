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

	// 발판 정적 메시 컴포넌트 생성
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(Platform);  // PlatformMesh를 RootComponent로 설정

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	if (CubeMesh.Succeeded())
	{
		// 큐브 메시 할당
		Platform->SetStaticMesh(CubeMesh.Object);
	}

	// 발판의 위쪽 충돌 컴포넌트 생성
	PlatformCollisionTop = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformCollisionTop"));
	PlatformCollisionTop->SetupAttachment(RootComponent);  // Cube의 하위 컴포넌트로 설정

	// 발판의 아래쪽 충돌 컴포넌트 생성
	PlatformCollisionBottom = CreateDefaultSubobject<UBoxComponent>(TEXT("PlatformCollisionBottom"));
	PlatformCollisionBottom->SetupAttachment(RootComponent);  // Cube의 하위 컴포넌트로 설정

	// 기본 값 설정
	bIsPlayerOnPlatform = false;
}

// Called when the game starts or when spawned
void AGeneralPlatform::BeginPlay()
{
	Super::BeginPlay();

	// 충돌 이벤트 처리
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

// TriggerEnter를 처리하는 함수
void AGeneralPlatform::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 오버랩되는 액터가 플레이어 캐릭터인지 확인
	if (Cast<AUPlayerSideviewCharacter>(OtherActor))
	{
		// 위쪽 충돌 컴포넌트와 오버랩된 경우
		if (Cast<UBoxComponent>(HitComp) == PlatformCollisionTop)
		{
			// 플레이어가 발판 위에 올라왔음을 인지
			bIsPlayerOnPlatform = true;
		}
		// 아래쪽 충돌 컴포넌트와 오버랩된 경우
		else if (Cast<UBoxComponent>(HitComp) == PlatformCollisionBottom)
		{
			// 발판의 충돌을 비활성화
			DisableCollision();
		}
	}
}

// TriggerExit를 처리하는 함수
void AGeneralPlatform::TriggerExit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 오버랩이 종료된 액터가 플레이어 캐릭터인지 확인
	if (Cast<AUPlayerSideviewCharacter>(OtherActor))
	{
		// 위쪽 충돌 컴포넌트와의 오버랩이 종료된 경우
		if (HitComp == PlatformCollisionTop)
		{
			// 플레이어가 발판 위에 있지 않음을 인지
			bIsPlayerOnPlatform = false;
		}
		// 아래쪽 충돌 컴포넌트와의 오버랩이 종료된 경우
		else if (HitComp == PlatformCollisionBottom)
		{
			// 발판의 충돌을 활성화
			EnableCollision();
		}
	}
}

// 발판의 충돌을 활성화하는 함수
void AGeneralPlatform::EnableCollision()
{
	// Pawn 채널에 대한 충돌을 Block으로 설정하여 캐릭터에 대한 발판의 충돌을 활성화
	Platform->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

// 발판의 충돌을 비활성화하는 함수
void AGeneralPlatform::DisableCollision()
{
	// Pawn 채널에 대한 충돌을 Ignore으로 설정하여 캐릭터에 대한 발판의 충돌을 비활성화
	Platform->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}