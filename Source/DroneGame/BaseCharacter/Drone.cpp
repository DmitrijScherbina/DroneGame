// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneGame/BaseCharacter/Drone.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "DroneGame/BaseCharacter/BaseItem.h"
//#include "GameFramework/PlayerController.h"


// Sets default values
ADrone::ADrone()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoxComponent);

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	Gun->SetupAttachment(Camera);

	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADrone::PickupItem);
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForwardBack", this, &ADrone::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveRightLeft", this, &ADrone::MoveRightLeft);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &ADrone::MoveUpDown);

	PlayerInputComponent->BindAxis("LookUpDown", this, &ADrone::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookLeftRight", this, &ADrone::AddControllerYawInput);

	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &ADrone::Shot);
}

void ADrone::MoveForwardBack(float Value)
{	
	if (Value > 0)
	{
		BoxComponent->AddForce(Camera->GetForwardVector()* MovementSpeed);
	}
	if (Value < 0)
	{
		BoxComponent->AddForce(Camera->GetForwardVector() * (MovementSpeed * -1));
	}

}

void ADrone::MoveRightLeft(float Value)
{
	if (Value > 0)
	{
		BoxComponent->AddForce(Camera->GetRightVector() * MovementSpeed);
	}
	if (Value < 0)
	{
		BoxComponent->AddForce(Camera->GetRightVector() * (MovementSpeed * -1));
	}	
}

void ADrone::MoveUpDown(float Value)
{
	if (Value > 0)
	{
		BoxComponent->AddForce(BoxComponent->GetUpVector() * MovementSpeed);
	}
	if (Value < 0)
	{
		BoxComponent->AddForce(BoxComponent->GetUpVector() * (MovementSpeed * -1));
	}
}

void ADrone::Shot()
{	
	if(Charge > 0 )
	{
		ABaseBullet* ShotBullet = GetWorld()->SpawnActor<ABaseBullet>(Bullet, Gun->GetComponentLocation(), Gun->GetComponentRotation());
		ShotBullet->Bullet->AddImpulse(Gun->GetUpVector() * BulletSpeed);

		Charge = Charge - 1;
	}

}

void ADrone::PickupItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseItem* Item = Cast<ABaseItem>(OtherActor);
	if (Item)
	{
		Charge = Charge + Item->Charge;
		AddHealth(Item);
		OtherActor->Destroy();	
	}	
}

void ADrone::AddHealth(ABaseItem* Item)
{
	if (Health < MaxHealth)
	{
		Health = Health + Item->Health;
		if (Health > MaxHealth)
		{
			Health = MaxHealth;
		}
	}
}

void ADrone::TakeDamage(float Damage)
{
	if(Health > Damage)
	{
		Health = Health - Damage;
	}
	else
	{		
		Health = 0;
		BoxComponent->AddImpulse(FVector(10000, 10000, 10000));
		BoxComponent->SetEnableGravity(true);
		DisableInput(GetLocalViewingPlayerController());		;
	}
}

