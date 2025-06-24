#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UPlayerSideviewCharacter.generated.h"

// 횡스크롤 게임 전용 게임 캐릭터 클래스
// 게임 캐릭터의 주요 기능을 정의합니다.
UCLASS()
class SCHRODINGER_API AUPlayerSideviewCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUPlayerSideviewCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 캐릭터 생존 처리 함수
	void CharacterAlive();

	// 캐릭터 사망 처리 함수
	void CharacterDeath();

	// 캐릭터의 머티리얼을 변경하는 함수
	void ChangeCharacterMaterial(bool isAlive);
};
