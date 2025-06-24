// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollingGameInstance.h"
#include "Engine/DataTable.h"
#include "UPlayerSideviewCharacter.h"
#include <Kismet/GameplayStatics.h>

// 게임 인스턴스 생성자
USideScrollingGameInstance::USideScrollingGameInstance()
{
	// 대화 데이터를 저장하는 DataTable을 로드
    static ConstructorHelpers::FObjectFinder<UDataTable> DATA_TABLE(TEXT("/Game/DataTable/DialogCSV.DialogCSV"));

	// 데이터 테이블이 성공적으로 로드되었는지 확인
    if (DATA_TABLE.Succeeded())
    {
		// 로드 성공 시 멤버 변수 DialogDataTable에 할당
        DialogDataTable = DATA_TABLE.Object;
    }
    else
    {
		// 로드 실패 시 로그에 오류 메시지 출력
        UE_LOG(LogTemp, Error, TEXT("Failed to load DialogDataTable"));
        DialogDataTable = nullptr;
    }
}

// 게임 인스턴스 초기화 함수
void USideScrollingGameInstance::Init()
{
    Super::Init();

	// 실험 ID를 1으로 초기화
    experimentId = 1;
	// 다음으로 이동할 레벨 ID를 1로 초기화
    nextLevelId = 1;
	// 현재 대화 ID를 0으로 초기화 (대화가 시작되지 않은 상태)
    currentDialogId = 0;

	// 방사능 수치를 0으로 초기화
	radioactiveRate = 0.0f;
	// 캐릭터 생존 상태를 true로 초기화 (캐릭터가 살아있는 상태)
	bIsCharacterAlive = true;
}

// Dialog 데이터 테이블에서 DialogID에 해당하는 대화 데이터를 수집하는 함수
FDialogData USideScrollingGameInstance::GetDialogData(int32 DialogID)
{
	// DialogDataTable이 유효한지 확인한 뒤, 해당 데이터 테이블에서 대화 데이터를 탐색해 구조체 형식으로 반환
	return DialogDataTable ? *(DialogDataTable->FindRow<FDialogData>(*FString::FromInt(DialogID), TEXT(""))) : FDialogData();
}

// 방사능 수치를 수정하는 함수
void USideScrollingGameInstance::ModifyRadioactiveRate(float DeltaRate)
{
	// 매개변수로 받은 DeltaRate를 현재 방사능 수치에 합산
	radioactiveRate += DeltaRate;

	// 방사능 수치가 0% 이하로 내려가면 캐릭터 생존 상태로 전환
	if (radioactiveRate <= 0.0f)
	{
		radioactiveRate = 0.0f; // 음수로 내려가지 않도록 제한
		bIsCharacterAlive = true; // 방사능 수치가 0% 이하로 내려가면 캐릭터 생존 상태 진입

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			AUPlayerSideviewCharacter* PlayerCharacter = Cast<AUPlayerSideviewCharacter>(PlayerController->GetPawn());
			if (PlayerCharacter)
			{
				// 캐릭터를 생존 상태로 전환하는 함수 호출
				PlayerCharacter->CharacterAlive();
			}
		}
	}
	// 방사능 수치가 100% 이상이 되면 최대 100%로 제한하고 캐릭터 사망 상태로 전환
	else if (radioactiveRate >= 100.0f)
	{
		radioactiveRate = 100.0f; // 최대 100%로 제한
		bIsCharacterAlive = false; // 방사능 수치가 100%를 초과하면 캐릭터 사망 상태 진입

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            AUPlayerSideviewCharacter* PlayerCharacter = Cast<AUPlayerSideviewCharacter>(PlayerController->GetPawn());
            if (PlayerCharacter)
            {
				// 캐릭터를 사망 상태로 전환하는 함수 호출
				PlayerCharacter->CharacterDeath();
            }
        }
	}
}

// 실험 종료 시 상태를 리셋하는 함수
void USideScrollingGameInstance::ExperimentOver()
{
	// 실험 ID를 1 증가
	experimentId += 1;
	// 다음 레벨 ID를 1로 초기화
	nextLevelId = 1;
	// 현재 대화 ID를 16으로 초기화
	currentDialogId = 16;

	// 방사능 수치를 0으로 초기화
	radioactiveRate = 0.0f;
	// 캐릭터 생존 상태를 true로 초기화 (캐릭터가 살아있는 상태)
	bIsCharacterAlive = true;
}

// 게임 오버 시 상태를 리셋하는 함수
void USideScrollingGameInstance::GameOver()
{
	// 실험 ID를 1로 초기화
	experimentId = 1;
	// 다음 레벨 ID를 1로 초기화
	nextLevelId = 1;
	// 현재 대화 ID를 0으로 초기화
	currentDialogId = 0;

	// 방사능 수치를 0으로 초기화
	radioactiveRate = 0.0f;
	// 캐릭터 생존 상태를 true로 초기화 (캐릭터가 살아있는 상태)
	bIsCharacterAlive = true;
}
