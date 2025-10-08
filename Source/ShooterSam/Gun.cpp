// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(Root);

	MuzzleFlash = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	MuzzleFlash->SetupAttachment(SkeletalMeshComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	MuzzleFlash->SetActive(false);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	MuzzleFlash->SetActive(true, true);
	if (AController* playerController = GetOwner()->GetInstigatorController())
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		playerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		FVector End = ViewPointLocation + (ViewPointRotation.Vector() * MaxRange);
		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, End, ECC_GameTraceChannel2, Params, FCollisionResponseParams::DefaultResponseParam);
		if (IsHit)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(), ImpactEffect.Get(), HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}
}

