// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ATank* Tank;

private:
	UPROPERTY(EditAnywhere, Category = "Attack")
	float FireRange = 750.f;

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();
};
