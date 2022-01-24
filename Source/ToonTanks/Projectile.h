// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Attack")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;
};
