// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlotSymbol.h"
#include "SlotReelManager.generated.h"

class ReelManager;

UCLASS(Blueprintable)
class SUPERSLOTS_API ASlotReelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlotReelManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slots)
    int ReelAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slots)
    int RowAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slots)
    TSubclassOf<ASlotSymbol> SlotObjectType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slots)
    TMap<int, UMaterial*> SymbolMaterials;

    virtual void Spin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


    ASlotSymbol* GetSymbol(int reel, int row);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    // Spin Animation
    FTimerHandle spinningTimer;

    float spinTime;


    void OnSpinEnded();
    // Spin Animation

    ReelManager* RM;

    UFUNCTION()
    ASlotSymbol* SpawnCube(UClass* symbolClass, FTransform trans);

    UPROPERTY()
    TArray<ASlotSymbol*> InstancedSlots;
};
