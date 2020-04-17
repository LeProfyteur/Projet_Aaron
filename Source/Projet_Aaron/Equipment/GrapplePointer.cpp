// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplePointer.h"

// Sets default values
AGrapplePointer::AGrapplePointer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereBox = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Box"));
	RootComponent = SphereBox;
}


