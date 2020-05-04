// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDCPP.h"

void UHUDCPP::NativePreConstruct()
{
	UWidget* RootWidget = GetRootWidget();
	CanvasPanelCast = Cast<UCanvasPanel>(RootWidget);
}
