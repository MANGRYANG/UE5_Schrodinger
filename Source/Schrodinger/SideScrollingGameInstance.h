// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Components/AudioComponent.h"
#include "SideScrollingGameInstance.generated.h"

// ��ȭ �ý��۰� ���õ� �����͸� �����ϴ� ����ü�� �����մϴ�.
USTRUCT(BlueprintType)
struct FDialogData : public FTableRowBase
{
	GENERATED_BODY()

	// ȭ���� ID
	UPROPERTY(BlueprintReadWrite, Category = "Dialog")
	int32 SpeakerId;

	// ��ȭ ����
	UPROPERTY(BlueprintReadWrite, Category = "Dialog")
	FString DialogText;

	// �⺻ ������
	FDialogData() : SpeakerId(0), DialogText(TEXT("")) {}

	// ȭ���� ID�� ��ȭ ������ �Ű������� �޾� �ʱ�ȭ�ϴ� ������
	FDialogData(int32 InSpeakerId, FString InDialogText)
		: SpeakerId(InSpeakerId), DialogText(InDialogText) {
	}
};

// Ⱦ��ũ�� ���� ���� ���� �ν��Ͻ� Ŭ����
// ������ �������� ���� �� ���� ������ �����ϴ� Ŭ�����Դϴ�.
UCLASS()
class SCHRODINGER_API USideScrollingGameInstance : public UGameInstance
{
	GENERATED_BODY()

// ���� ����

// ���� ���� ���¸� �����ϱ� ���� ���� ����
public:
	// ���� ���� ���� ������ ID (1 - 999)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="GameData")
	int32 experimentId;

	// ������ �̵��� ������ ID (1 - 999)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="GameData")
	int32 nextLevelId;

	// ���� ���� ���� ��ȭ �������� ID (0���� ����)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="GameData")
	int32 currentDialogId;

// ĳ���� ���¸� �����ϱ� ���� ���� ����
public:
	// ���� ��ġ (0% - 100% ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	float radioactiveRate;

	// ĳ������ ���� �� ��� ���� (True: ����, False: ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	bool bIsCharacterAlive;

// �Լ� ����

public:
	// ������
	USideScrollingGameInstance();

public:
	// ���� ���� �� ȣ��Ǵ� Init �Լ�
	virtual void Init() override;

public:
	// ��ȭ ������ ���̺��� DialogID�� �ش��ϴ� ��ȭ �����͸� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "DialogManagement")
	FDialogData GetDialogData(int32 DialogID);

	// ���� ��ġ�� �������ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "CharacterManagement")
	void ModifyRadioactiveRate(float DeltaRate);

	// ���� ���� �� ȣ��Ǵ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "GameManagement")
	void ExperimentOver();

	// ���� ���� �� ȣ��Ǵ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "GameManagement")
	void GameOver();

private:
	// ��ȭ ������ ���̺��� �����ϴ� ����
	UPROPERTY()
	class UDataTable* DialogDataTable;
};
