// Fill out your copyright notice in the Description page of Project Settings.

#include "SpinHitter.h"


// Sets default values
ASpinHitter::ASpinHitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    this->GraphicalComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
}

// Called when the game starts or when spawned
void ASpinHitter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpinHitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpinHitter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Hit !");

    this->Linked->Spin();
}

