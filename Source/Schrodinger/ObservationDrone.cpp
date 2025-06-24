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
	// ���� �ν��Ͻ��� �����Ͽ� ĳ������ ���� ���� �ľ�
	USideScrollingGameInstance* GameInstance = Cast<USideScrollingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		// ĳ���Ͱ� ���� ������ ��쿡�� ���� Ʈ���̽��� ����
		if (GameInstance->bIsCharacterAlive)
		{
			for (int i = 0; i < NumberOfLines; ++i) {
				// ����� ������ ���� Ʈ���̽��� ����
				FVector TempVector = GetActorRightVector(); // ����� ��� �ٶ󺸴� ���� -> ������ ����
				FRotator TempRotation = TempVector.Rotation();

				// ���������� �̿��Ͽ� ������ ����
				TempRotation.Pitch = (TempRotation.Pitch - (ObservationAngle / 2.0f)) + i * (ObservationAngle / (NumberOfLines - 1));

				// ���� ��ġ�� �� ��ġ ���
				FVector Start = GetActorLocation() + (GetActorRightVector() * 70) + (GetActorUpVector() * 25); // ���� ��ġ
				FVector End = Start + (TempRotation.Vector() * ObservationRange);

				// ���� Ʈ���̽� ����
				FHitResult HitResult;
				FCollisionQueryParams CollisionParams;
				CollisionParams.AddIgnoredActor(this); // �ڱ� �ڽ��� ����

				//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);

				// Hit�� �߻��Ͽ����� Ȯ��
				if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
				{
					// Hit�� ���Ͱ� �÷��̾� ĳ�������� Ȯ��
					AUPlayerSideviewCharacter* PlayerCharacter = Cast<AUPlayerSideviewCharacter>(HitResult.GetActor());
					if (PlayerCharacter)
					{
						GameInstance->ExperimentOver(); // ���� ���� �Լ� ȣ��
						return true;
					}
				}
			}
		}
	}
	return false;
}

