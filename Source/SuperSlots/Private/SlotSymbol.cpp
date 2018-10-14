// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotSymbol.h"

// Sets default values
ASlotSymbol::ASlotSymbol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASlotSymbol::SpinSymbol(int targetSymbol)
{
    this->isSpinning = true;
    this->TargetSpinSymbol = targetSymbol;

    this->GetWorldTimerManager().SetTimer(this->spinningTimer, this, &ASlotSymbol::OnSpinEnded, 1.0f);
}

void ASlotSymbol::SetSymbol(int targetSymbol)
{

}

void ASlotSymbol::OnSpinTick()
{
    this->AddActorLocalRotation(FQuat(FVector(0, 1, 0), FMath::DegreesToRadians(-10)));

}

void ASlotSymbol::OnSpinEnded()
{
    this->SetSymbol(TargetSpinSymbol);

    this->isSpinning = false;

    this->SetActorRotation(OriginalRotation);
}

// Called when the game starts or when spawned
void ASlotSymbol::BeginPlay()
{
	Super::BeginPlay();

    OriginalRotation = this->GetActorQuat();

    this->SpinSymbol(0);
}

// Called every frame
void ASlotSymbol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (isSpinning)
    {
        this->OnSpinTick();
    }
}

