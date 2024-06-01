// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneGame/BaseCharacter/BaseBullet.h"
#include "DroneGame/BaseCharacter/Drone.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));


}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();

	Bullet->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseBullet::BulletHit);
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}