// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

	void RotateTurret(const FVector LookAtTarget);

	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
