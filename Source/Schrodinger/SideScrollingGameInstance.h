// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Components/AudioComponent.h"
#include "SideScrollingGameInstance.generated.h"

// 대화 시스템과 관련된 데이터를 관리하는 구조체를 정의합니다.
USTRUCT(BlueprintType)
struct FDialogData : public FTableRowBase
{
	GENERATED_BODY()

	// 화자의 ID
	UPROPERTY(BlueprintReadWrite, Category = "Dialog")
	int32 SpeakerId;

	// 대화 내용
	UPROPERTY(BlueprintReadWrite, Category = "Dialog")
	FString DialogText;

	// 기본 생성자
	FDialogData() : SpeakerId(0), DialogText(TEXT("")) {}

	// 화자의 ID와 대화 내용을 매개변수로 받아 초기화하는 생성자
	FDialogData(int32 InSpeakerId, FString InDialogText)
		: SpeakerId(InSpeakerId), DialogText(InDialogText) {
	}
};

// 횡스크롤 게임 전용 게임 인스턴스 클래스
// 게임의 전반적인 상태 및 전역 변수를 관리하는 클래스입니다.
UCLASS()
class SCHRODINGER_API USideScrollingGameInstance : public UGameInstance
{
	GENERATED_BODY()

// 변수 관리

// 게임 진행 상태를 관리하기 위한 변수 정의
public:
	// 현재 진행 중인 실험의 ID (1 - 999)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="GameData")
	int32 experimentId;

	// 다음에 이동할 레벨의 ID (1 - 999)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="GameData")
	int32 nextLevelId;

	// 현재 진행 중인 대화 데이터의 ID (0부터 시작)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="GameData")
	int32 currentDialogId;

// 캐릭터 상태를 관리하기 위한 변수 정의
public:
	// 방사능 수치 (0% - 100% 내로 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	float radioactiveRate;

	// 캐릭터의 생존 및 사망 상태 (True: 생존, False: 사망)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	bool bIsCharacterAlive;

// 함수 관리

public:
	// 생성자
	USideScrollingGameInstance();

public:
	// 게임 시작 시 호출되는 Init 함수
	virtual void Init() override;

public:
	// 대화 데이터 테이블에서 DialogID에 해당하는 대화 데이터를 수집하는 함수
	UFUNCTION(BlueprintCallable, Category = "DialogManagement")
	FDialogData GetDialogData(int32 DialogID);

	// 방사능 수치를 재조정하는 함수
	UFUNCTION(BlueprintCallable, Category = "CharacterManagement")
	void ModifyRadioactiveRate(float DeltaRate);

	// 실험 종료 시 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "GameManagement")
	void ExperimentOver();

	// 게임 오버 시 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "GameManagement")
	void GameOver();

private:
	// 대화 데이터 테이블을 참조하는 변수
	UPROPERTY()
	class UDataTable* DialogDataTable;
};
