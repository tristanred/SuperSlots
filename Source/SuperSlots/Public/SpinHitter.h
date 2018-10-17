// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlotReelManager.h"
#include "SpinHitter.generated.h"

UCLASS()
class SUPERSLOTS_API ASpinHitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinHitter();

    UPROPERTY(VisibleDefaultsOnly, Category = Slots)
    class UMeshComponent* GraphicalComponent;

    UPROPERTY(EditInstanceOnly, Category = Slots)
    ASlotReelManager* LinkedReelMan;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	
};
