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

// ĳ���͸� ���� ���·� ��ȯ�ϴ� �Լ�
void AUPlayerSideviewCharacter::CharacterAlive()
{
	// ���͸����� ���� ���·� ��ȯ
	ChangeCharacterMaterial(true);
}

// ĳ���͸� ��� ���·� ��ȯ�ϴ� �Լ�
void AUPlayerSideviewCharacter::CharacterDeath()
{
	// ���͸����� ��� ���·� ��ȯ
	ChangeCharacterMaterial(false);
}

// �Ű������� ĳ������ ���� �� ��� ���¸� �޾� ���͸����� �����ϴ� �Լ�
void AUPlayerSideviewCharacter::ChangeCharacterMaterial(bool bIsAlive)
{
	// ���� �� ��� ���¿� ���� ���͸����� �ε�
	UMaterialInterface* AliveMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Material/M_AliveMaterial.M_AliveMaterial'"));
	UMaterialInterface* DeadMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Material/M_DeadMaterial.M_DeadMaterial'"));

	// �� ���͸����� ��� ��ȿ���� Ȯ��
	if (!AliveMaterial || !DeadMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load materials."));
		return;
	}

	// ĳ������ ���̷�Ż �޽� ������Ʈ�� �Ҵ�
	USkeletalMeshComponent* SkeletalMesh = GetMesh();

	// ���̷�Ż �޽ð� �����ϴ��� Ȯ��
	if (SkeletalMesh)
	{
		// ĳ������ ���� �� ��� ���� Ȯ��
		if (bIsAlive)
		{
			// ���� ������ �� ���͸����� AliveMaterial�� ����
			SkeletalMesh->SetMaterial(0, AliveMaterial);
			SkeletalMesh->SetMaterial(1, AliveMaterial);
		}
		else
		{
			// ��� ������ �� ���͸����� DeadMaterial�� ����
			SkeletalMesh->SetMaterial(0, DeadMaterial);
			SkeletalMesh->SetMaterial(1, DeadMaterial);
		}
	}

	else
	{
		// ���̷�Ż �޽� ������Ʈ�� �������� ���� ��� ��� �޽��� ���
		UE_LOG(LogTemp, Warning, TEXT("Skeletal Mesh Component not found."));
	}
}

