// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "DroneGame/BaseCharacter/Drone.h"
#include "DroneGame/BaseCharacter/BaseBullet.h"
#include "BaseTurret.generated.h"

UCLASS()
class DRONEGAME_API ABaseTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> DetectionZone;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void DetectEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LoseEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	ADrone* Drone = nullptr;

	UPROPERTY()
	float TimeUntilShot = 0;

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenShots = 1.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseBullet> Bullet;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpeed = 3000.0f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Health = 100.0f;

	UPROPERTY()
	float MaxHealth = 100.0f;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

};
