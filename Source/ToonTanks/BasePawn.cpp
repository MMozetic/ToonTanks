// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(const FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	FRotator CurrentRotation = TurretMesh->GetComponentRotation();
	FRotator TargetRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	FRotator InterpolatedRotation = FMath::RInterpTo(
		CurrentRotation,
		TargetRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		10.f
	);

	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void ABasePawn::Fire()
{
	FVector ProjectileLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLocation, ProjectileRotation);
	Projectile->SetOwner(this);
}
