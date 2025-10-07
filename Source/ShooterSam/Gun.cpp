// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"


// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTriger()
{
	UE_LOG(LogTemp, Log, TEXT("Bang!") );
	if (AController* playerController = GetOwner()->GetInstigatorController())
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		playerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
		DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.0f, 2.0f, FColor::Red, false, 2.0f);
	}
}

