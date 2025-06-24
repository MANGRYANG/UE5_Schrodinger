// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollingGameInstance.h"
#include "Engine/DataTable.h"
#include "UPlayerSideviewCharacter.h"
#include <Kismet/GameplayStatics.h>

// ���� �ν��Ͻ� ������
USideScrollingGameInstance::USideScrollingGameInstance()
{
	// ��ȭ �����͸� �����ϴ� DataTable�� �ε�
    static ConstructorHelpers::FObjectFinder<UDataTable> DATA_TABLE(TEXT("/Game/DataTable/DialogCSV.DialogCSV"));

	// ������ ���̺��� ���������� �ε�Ǿ����� Ȯ��
    if (DATA_TABLE.Succeeded())
    {
		// �ε� ���� �� ��� ���� DialogDataTable�� �Ҵ�
        DialogDataTable = DATA_TABLE.Object;
    }
    else
    {
		// �ε� ���� �� �α׿� ���� �޽��� ���
        UE_LOG(LogTemp, Error, TEXT("Failed to load DialogDataTable"));
        DialogDataTable = nullptr;
    }
}

// ���� �ν��Ͻ� �ʱ�ȭ �Լ�
void USideScrollingGameInstance::Init()
{
    Super::Init();

	// ���� ID�� 1���� �ʱ�ȭ
    experimentId = 1;
	// �������� �̵��� ���� ID�� 1�� �ʱ�ȭ
    nextLevelId = 1;
	// ���� ��ȭ ID�� 0���� �ʱ�ȭ (��ȭ�� ���۵��� ���� ����)
    currentDialogId = 0;

	// ���� ��ġ�� 0���� �ʱ�ȭ
	radioactiveRate = 0.0f;
	// ĳ���� ���� ���¸� true�� �ʱ�ȭ (ĳ���Ͱ� ����ִ� ����)
	bIsCharacterAlive = true;
}

// Dialog ������ ���̺��� DialogID�� �ش��ϴ� ��ȭ �����͸� �����ϴ� �Լ�
FDialogData USideScrollingGameInstance::GetDialogData(int32 DialogID)
{
	// DialogDataTable�� ��ȿ���� Ȯ���� ��, �ش� ������ ���̺��� ��ȭ �����͸� Ž���� ����ü �������� ��ȯ
	return DialogDataTable ? *(DialogDataTable->FindRow<FDialogData>(*FString::FromInt(DialogID), TEXT(""))) : FDialogData();
}

// ���� ��ġ�� �����ϴ� �Լ�
void USideScrollingGameInstance::ModifyRadioactiveRate(float DeltaRate)
{
	// �Ű������� ���� DeltaRate�� ���� ���� ��ġ�� �ջ�
	radioactiveRate += DeltaRate;

	// ���� ��ġ�� 0% ���Ϸ� �������� ĳ���� ���� ���·� ��ȯ
	if (radioactiveRate <= 0.0f)
	{
		radioactiveRate = 0.0f; // ������ �������� �ʵ��� ����
		bIsCharacterAlive = true; // ���� ��ġ�� 0% ���Ϸ� �������� ĳ���� ���� ���� ����

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			AUPlayerSideviewCharacter* PlayerCharacter = Cast<AUPlayerSideviewCharacter>(PlayerController->GetPawn());
			if (PlayerCharacter)
			{
				// ĳ���͸� ���� ���·� ��ȯ�ϴ� �Լ� ȣ��
				PlayerCharacter->CharacterAlive();
			}
		}
	}
	// ���� ��ġ�� 100% �̻��� �Ǹ� �ִ� 100%�� �����ϰ� ĳ���� ��� ���·� ��ȯ
	else if (radioactiveRate >= 100.0f)
	{
		radioactiveRate = 100.0f; // �ִ� 100%�� ����
		bIsCharacterAlive = false; // ���� ��ġ�� 100%�� �ʰ��ϸ� ĳ���� ��� ���� ����

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            AUPlayerSideviewCharacter* PlayerCharacter = Cast<AUPlayerSideviewCharacter>(PlayerController->GetPawn());
            if (PlayerCharacter)
            {
				// ĳ���͸� ��� ���·� ��ȯ�ϴ� �Լ� ȣ��
				PlayerCharacter->CharacterDeath();
            }
        }
	}
}

// ���� ���� �� ���¸� �����ϴ� �Լ�
void USideScrollingGameInstance::ExperimentOver()
{
	// ���� ID�� 1 ����
	experimentId += 1;
	// ���� ���� ID�� 1�� �ʱ�ȭ
	nextLevelId = 1;
	// ���� ��ȭ ID�� 16���� �ʱ�ȭ
	currentDialogId = 16;

	// ���� ��ġ�� 0���� �ʱ�ȭ
	radioactiveRate = 0.0f;
	// ĳ���� ���� ���¸� true�� �ʱ�ȭ (ĳ���Ͱ� ����ִ� ����)
	bIsCharacterAlive = true;
}

// ���� ���� �� ���¸� �����ϴ� �Լ�
void USideScrollingGameInstance::GameOver()
{
	// ���� ID�� 1�� �ʱ�ȭ
	experimentId = 1;
	// ���� ���� ID�� 1�� �ʱ�ȭ
	nextLevelId = 1;
	// ���� ��ȭ ID�� 0���� �ʱ�ȭ
	currentDialogId = 0;

	// ���� ��ġ�� 0���� �ʱ�ȭ
	radioactiveRate = 0.0f;
	// ĳ���� ���� ���¸� true�� �ʱ�ȭ (ĳ���Ͱ� ����ִ� ����)
	bIsCharacterAlive = true;
}
