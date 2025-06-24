#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UPlayerSideviewCharacter.generated.h"

// Ⱦ��ũ�� ���� ���� ���� ĳ���� Ŭ����
// ���� ĳ������ �ֿ� ����� �����մϴ�.
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
	// ĳ���� ���� ó�� �Լ�
	void CharacterAlive();

	// ĳ���� ��� ó�� �Լ�
	void CharacterDeath();

	// ĳ������ ��Ƽ������ �����ϴ� �Լ�
	void ChangeCharacterMaterial(bool isAlive);
};
