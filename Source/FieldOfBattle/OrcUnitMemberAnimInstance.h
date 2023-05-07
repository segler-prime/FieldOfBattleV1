// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OrcUnitMemberAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API UOrcUnitMemberAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:

	UPROPERTY(BlueprintReadWrite)
	class AOrcUnitMember* OrcUnitMember;

	UPROPERTY(BlueprintReadWrite)
	float speed;

};
