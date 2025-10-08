// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Gun.generated.h"



UCLASS()
class SHOOTERSAM_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, Category="Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, Category="Shoot")
	float MaxRange = 10000.0f;

	UPROPERTY(visibleAnywhere, Category="Shoot")
	TObjectPtr<UNiagaraComponent> MuzzleFlash;

	UPROPERTY(EditAnywhere, Category="Shoot")
	TObjectPtr<UNiagaraSystem> ImpactEffect;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Shoot")
	void PullTrigger();
};
