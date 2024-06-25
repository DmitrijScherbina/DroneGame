// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneGame/BaseCharacter/BaseTurret.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABaseTurret::ABaseTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));		

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(BoxComponent);

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	Gun->SetupAttachment(BoxComponent);

	DetectionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionZone"));
	DetectionZone->SetupAttachment(BoxComponent);

	DetectionZone->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseTurret::DetectEnemy);
	DetectionZone->OnComponentEndOverlap.AddUniqueDynamic(this, &ABaseTurret::LoseEnemy);
}

// Called when the game starts or when spawned
void ABaseTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Drone)
	{
		if(Drone->Health > 0)
		{
			FRotator LookAtEnemy = UKismetMathLibrary::FindLookAtRotation(Gun->GetComponentLocation(), Drone->GetActorLocation());
			LookAtEnemy.Pitch = LookAtEnemy.Pitch - 90.0f;
			Gun->SetWorldRotation(LookAtEnemy);
			if (TimeUntilShot == 0)
			{
				TimeUntilShot = DeltaTime;
				ABaseBullet* ShotBullet = GetWorld()->SpawnActor<ABaseBullet>(Bullet, Gun->GetComponentLocation(), Gun->GetComponentRotation());
				if (ShotBullet)
				{
					ShotBullet->Bullet->AddImpulse(Gun->GetUpVector() * BulletSpeed);
				}
			}
			else
			{
				TimeUntilShot = TimeUntilShot + DeltaTime;
				if (TimeUntilShot > TimeBetweenShots)
				{
					TimeUntilShot = 0;
				}
			}
		}
	}
}

// Called to bind functionality to input
void ABaseTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseTurret::DetectEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Drone = Cast<ADrone>(OtherActor);
}

void ABaseTurret::LoseEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Drone == Cast<ADrone>(OtherActor))
	{
		Drone = nullptr;
		TimeUntilShot = 0;
	}
}

void ABaseTurret::TakeDamage(float Damage)
{
	if (Health > Damage)
	{
		Health = Health - Damage;
	}
	else
	{
		Health = 0;
		Destroy();
	}
}

