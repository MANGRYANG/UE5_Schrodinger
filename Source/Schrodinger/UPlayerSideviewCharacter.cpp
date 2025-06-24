// Fill out your copyright notice in the Description page of Project Settings.


#include "UPlayerSideviewCharacter.h"

AUPlayerSideviewCharacter::AUPlayerSideviewCharacter()
{
}

void AUPlayerSideviewCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AUPlayerSideviewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUPlayerSideviewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 캐릭터를 생존 상태로 전환하는 함수
void AUPlayerSideviewCharacter::CharacterAlive()
{
	// 머터리얼을 생존 상태로 전환
	ChangeCharacterMaterial(true);
}

// 캐릭터를 사망 상태로 전환하는 함수
void AUPlayerSideviewCharacter::CharacterDeath()
{
	// 머터리얼을 사망 상태로 전환
	ChangeCharacterMaterial(false);
}

// 매개변수로 캐릭터의 생존 및 사망 상태를 받아 머터리얼을 변경하는 함수
void AUPlayerSideviewCharacter::ChangeCharacterMaterial(bool bIsAlive)
{
	// 생존 및 사망 상태에 대한 머터리얼을 로드
	UMaterialInterface* AliveMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Material/M_AliveMaterial.M_AliveMaterial'"));
	UMaterialInterface* DeadMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Material/M_DeadMaterial.M_DeadMaterial'"));

	// 두 머터리얼이 모두 유효한지 확인
	if (!AliveMaterial || !DeadMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load materials."));
		return;
	}

	// 캐릭터의 스켈레탈 메시 컴포넌트를 할당
	USkeletalMeshComponent* SkeletalMesh = GetMesh();

	// 스켈레탈 메시가 존재하는지 확인
	if (SkeletalMesh)
	{
		// 캐릭터의 생존 및 사망 상태 확인
		if (bIsAlive)
		{
			// 생존 상태일 때 머터리얼을 AliveMaterial로 설정
			SkeletalMesh->SetMaterial(0, AliveMaterial);
			SkeletalMesh->SetMaterial(1, AliveMaterial);
		}
		else
		{
			// 사망 상태일 때 머터리얼을 DeadMaterial로 설정
			SkeletalMesh->SetMaterial(0, DeadMaterial);
			SkeletalMesh->SetMaterial(1, DeadMaterial);
		}
	}

	else
	{
		// 스켈레탈 메시 컴포넌트가 존재하지 않을 경우 경고 메시지 출력
		UE_LOG(LogTemp, Warning, TEXT("Skeletal Mesh Component not found."));
	}
}

