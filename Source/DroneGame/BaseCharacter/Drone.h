// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "DroneGame/BaseCharacter/BaseBullet.h"
#include "Drone.generated.h"

UCLASS()
class DRONEGAME_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Gun;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwardBack(float Value);

	void MoveRightLeft(float Value);

	void MoveUpDown(float Value);

	void Shot();

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpeed = 5000.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseBullet> Bullet;

	UFUNCTION()
	void PickupItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Health = 100.0f;

	UPROPERTY()
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Charge = 5;

	UFUNCTION()
	void AddHealth(ABaseItem* Item);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);
};
