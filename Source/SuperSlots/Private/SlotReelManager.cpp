// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/SlotReelManager.h"

#include "TimerManager.h"
#include "Engine.h"

#include "ReelManager.h"
#include "SymbolSet.h"
#include "LineSet.h"

// Sets default values
ASlotReelManager::ASlotReelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    spinTime = 3.0f;
}

void ASlotReelManager::Spin()
{
    this->RM->Spin();
    this->RM->CalculateWins();

    int index = 0;
    for (int i = 0; i < this->RM->Reels; i++)
    {
        for (int k = 0; k < this->RM->Rows; k++)
        {
            InstancedSlots[index]->SpinSymbol(this->RM->ReelSymbols[i][k]->id, spinTime);
            index++;
        }
    }

    this->GetWorldTimerManager().SetTimer(this->spinningTimer, this, &ASlotReelManager::OnSpinEnded, spinTime);
}

// Called when the game starts or when spawned
void ASlotReelManager::BeginPlay()
{
	Super::BeginPlay();

    this->RM = new ReelManager(5, 3);
    this->RM->CreateDefaultObjects();

    if (this->SlotObjectType != NULL)
    {
        for (int i = 0; i < ReelAmount; i++)
        {
            for (int k = 0; k < RowAmount; k++)
            {
                FTransform newCubeTranstorm = this->GetActorTransform();

                ASlotSymbol* res = this->SpawnCube(SlotObjectType.Get(), this->GetActorTransform());

                if (res == NULL)
                    continue;

                InstancedSlots.Add(res);

                res->AddActorLocalOffset(FVector(0, (i * 300) - 500, k * 300), false, nullptr, ETeleportType::TeleportPhysics);
            }
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Did not set SlotObjectType :(");
    }

    this->RM->Spin();
}

void ASlotReelManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (int i = 0; i < InstancedSlots.Num(); i++)
    {
        GetWorld()->DestroyActor(InstancedSlots[i]);
    }

    InstancedSlots.Empty();

    if (this->RM != NULL)
    {
        //delete(this->RM);
    }
}

ASlotSymbol* ASlotReelManager::GetSymbol(int reel, int row)
{
    int seachIndex = 0;

    // New idea, the bullshit search algorithm. Optimized for speed !
    // Not speed of execution but speed of development.
    // TODO : Fixme.
    for (int i = 0; i < this->RM->Reels; i++)
    {
        for (int k = 0; k < this->RM->Rows; k++)
        {
            if (reel == i && row == k)
            {
                return this->InstancedSlots[seachIndex];
            }

            seachIndex++;
        }
    }

    return NULL;
}

// Called every frame
void ASlotReelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlotReelManager::OnSpinEnded()
{
    LineWin** winningLine = this->RM->GetLineWins();
    if (winningLine != NULL)
    {
        for (int i = 0; i < this->RM->Lines->PatternsCount; i++)
        {
            // Check if this line wins
            if (winningLine[i] != NULL)
            {
                int winLineIndex = winningLine[i]->winLineIndex;

                int* offsets = this->RM->Lines->LinePatterns[winLineIndex];

                for (int k = 0; k < this->RM->Reels; k++)
                {
                    ASlotSymbol* winSymbol = this->GetSymbol(k, offsets[k]);

                    FString msg = FString::Printf(TEXT("Winning Sym on %d, %d"), k, offsets[k]);
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg);
                }
            }
        }
    }
}

ASlotSymbol* ASlotReelManager::SpawnCube(UClass* symbolClass, FTransform trans)
{
    auto res = GetWorld()->SpawnActorDeferred<ASlotSymbol>(symbolClass, trans);

    if (res == NULL)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Object is not a subclass of ASlotSymbolCube.");

        return NULL;
    }

    res->AssignSymbolTexturesMap(this->SymbolMaterials);

    UGameplayStatics::FinishSpawningActor(res, trans);

    return res;
}