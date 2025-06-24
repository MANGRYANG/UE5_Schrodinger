// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservationDrone.h"
#include "Blueprint/UserWidget.h"
#include "SideScrollingGameInstance.h"
#include "UPlayerSideviewCharacter.h"

// Sets default values
AObservationDrone::AObservationDrone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AObservationDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObservationDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AObservationDrone::StartObservation()
{
	// 게임 인스턴스에 접근하여 캐릭터의 생존 여부 파악
	USideScrollingGameInstance* GameInstance = Cast<USideScrollingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		// 캐릭터가 생존 상태인 경우에만 라인 트레이스를 수행
		if (GameInstance->bIsCharacterAlive)
		{
			for (int i = 0; i < NumberOfLines; ++i) {
				// 드론이 수행할 라인 트레이스의 로직
				FVector TempVector = GetActorRightVector(); // 드론의 렌즈가 바라보는 방향 -> 오른쪽 벡터
				FRotator TempRotation = TempVector.Rotation();

				// 등차수열을 이용하여 각도를 조정
				TempRotation.Pitch = (TempRotation.Pitch - (ObservationAngle / 2.0f)) + i * (ObservationAngle / (NumberOfLines - 1));

				// 시작 위치와 끝 위치 계산
				FVector Start = GetActorLocation() + (GetActorRightVector() * 70) + (GetActorUpVector() * 25); // 시작 위치
				FVector End = Start + (TempRotation.Vector() * ObservationRange);

				// 라인 트레이스 실행
				FHitResult HitResult;
				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(this); // 자기 자신은 무시

				//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);

				// Hit이 발생하였는지 확인
				if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
				{
					// Hit된 액터가 플레이어 캐릭터인지 확인
					AUPlayerSideviewCharacter* PlayerCharacter = Cast<AUPlayerSideviewCharacter>(HitResult.GetActor());
					if (PlayerCharacter)
					{
						GameInstance->ExperimentOver(); // 실험 종료 함수 호출
						return true;
					}
				}
			}
		}
	}
	return false;
}

