// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/SlotSymbol.h"

#include "Components/MeshComponent.h"
#include "Classes/Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Classes/GameFramework/Actor.h"

// Sets default values
ASlotSymbol::ASlotSymbol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpinProps.Speed = -10;
    SpinProps.RotationAxis = FVector(0, 1, 0);
    isSpinning = false;
    
    CurrentSymbol = -1;
    TargetSpinSymbol = -1;
    spinAnimationAccumulator = 0;
}

void ASlotSymbol::AssignSymbolTexturesMap(TMap<int, UMaterial*> map)
{
    this->SymbolTextureMap = map;
}

void ASlotSymbol::SpinSymbol(int targetSymbol, float timeToSpin)
{
    this->isSpinning = true;
    this->TargetSpinSymbol = targetSymbol;

    this->GetWorldTimerManager().SetTimer(this->spinningTimer, this, &ASlotSymbol::OnSpinEnded, timeToSpin);
}

void ASlotSymbol::SetSymbol(int targetSymbol)
{
    if(CurrentSymbol == targetSymbol)
        return;

    UMaterial** result = this->SymbolTextureMap.Find(targetSymbol);

    if(result != NULL)
    {
        UMeshComponent* res = (UMeshComponent*)this->GetComponentByClass(UMeshComponent::StaticClass());

        if(res != NULL)
        {
            res->SetMaterial(0, *result);

            CurrentSymbol = targetSymbol;
        }
    }
}

void ASlotSymbol::OnSpinTick()
{
    this->AddActorLocalRotation(FQuat(this->SpinProps.RotationAxis, FMath::DegreesToRadians(this->SpinProps.Speed)));
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

    //this->SpinSymbol(0);
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

