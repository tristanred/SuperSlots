// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Materials/Material.h"

#include "SlotSymbol.generated.h"

USTRUCT(BlueprintType)
struct FSlotSpinParameters
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    int Speed; // In degrees per second

    UPROPERTY(EditAnywhere)
    FVector RotationAxis;
};

UCLASS(Blueprintable)
class SUPERSLOTS_API ASlotSymbol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlotSymbol();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slots)
    TArray<UMaterial*> SymbolTextures;

    // ===== Spinning =====
    FQuat OriginalRotation;
    FTimerHandle spinningTimer;
    bool isSpinning;
    int TargetSpinSymbol;
    float spinAnimationAccumulator;

    UPROPERTY(EditAnywhere, Category = Slots)
    FSlotSpinParameters SpinProps;


    UFUNCTION(BlueprintCallable)
    void SpinSymbol(int targetSymbol);

    UFUNCTION(BlueprintCallable)
    void SetSymbol(int targetSymbol);

    void OnSpinTick();
    void OnSpinEnded();
    // ===== Spinning =====

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
