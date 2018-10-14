// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotReelManager.h"

#include "TimerManager.h"
#include "Engine.h"

// Sets default values
ASlotReelManager::ASlotReelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASlotReelManager::Spin()
{

}

// Called when the game starts or when spawned
void ASlotReelManager::BeginPlay()
{
	Super::BeginPlay();

    if (this->SlotObjectType != NULL)
    {
        for (int i = 0; i < ReelAmount; i++)
        {
            for (int k = 0; k < RowAmount; k++)
            {
                FTransform newCubeTranstorm = this->GetActorTransform();

                ASlotSymbol* res = this->SpawnCube(SlotObjectType.Get(), this->GetActorTransform());
                InstancedSlots.Add(res);

                if (res == NULL)
                    continue;

                res->AddActorLocalOffset(FVector(0, (i * 300) - 500, k * 300), false, nullptr, ETeleportType::TeleportPhysics);
            }
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Did not set SlotObjectType :(");
    }

    for (int i = 0; i < InstancedSlots.Num(); i++)
    {
        //InstancedSlots[i]->StartShuffle(20);
    }
}

void ASlotReelManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (int i = 0; i < InstancedSlots.Num(); i++)
    {
        GetWorld()->DestroyActor(InstancedSlots[i]);
    }

    InstancedSlots.Empty();
}

// Called every frame
void ASlotReelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ASlotSymbol* ASlotReelManager::SpawnCube(UClass* symbolClass, FTransform trans)
{
    auto res = GetWorld()->SpawnActor<ASlotSymbol>(symbolClass, trans);

    if (res == NULL)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Object is not a subclass of ASlotSymbolCube.");

        return NULL;
    }

    return res;
}