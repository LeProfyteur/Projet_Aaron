#include "UIManagerSubsystem.h"

void UUIManagerSubsystem::InitializeSubsystem()
{
	MenuStack.Empty();
}

void UUIManagerSubsystem::PopAllMenus()
{
	while (MenuStack.Num() > 0)
	{
		PopMenu();
	}
}

void UUIManagerSubsystem::Reset()
{
	MenuStack.Reset();
}

void UUIManagerSubsystem::PushMenu(UUserWidget* Menu)
{
	//Collapse current Menu
	if (UUserWidget* CurrentMenu = GetCurrentMenu())
	{
		CurrentMenu->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		//First Menu to open, Show Cursor
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
	}

	//Push Menu to the Stack & Viewport
	//UE_LOG(LogLevel, Display, TEXT("Pushing Menu %s, %d Menus in Stack"), *Menu->GetDisplayLabel(), MenuStack.Num());
	Menu->AddToViewport();
	Menu->SetFocus();
	MenuStack.Push(Menu);
}

void UUIManagerSubsystem::PopMenu()
{
	//Collapse & remove Current Menu from the Viewport (if exists)
	if (UUserWidget* CurrentMenu = GetCurrentMenu())
	{
		//UE_LOG(LogLevel, Display, TEXT("Poping Menu %s, %d Menus in Stack"), *CurrentMenu->GetDisplayLabel(), MenuStack.Num());
		CurrentMenu->SetVisibility(ESlateVisibility::Collapsed);
		CurrentMenu->RemoveFromViewport();

		MenuStack.Pop(true);

		//If there is still a Current Menu, Display this one
		if (UUserWidget* NextCurrentMenu = GetCurrentMenu())
		{
			NextCurrentMenu->SetVisibility(ESlateVisibility::Visible);
			NextCurrentMenu->SetFocus();
		}
		else
		{	
			//Last Menu to Pop, Hide Cursor & Focus on Game
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
			GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		}
	}
}

UUserWidget* UUIManagerSubsystem::GetCurrentMenu() const
{
	if (IsShowingAMenu())
	{
		return MenuStack.Last();
	}
	return nullptr;
}

bool UUIManagerSubsystem::IsShowingAMenu() const
{
	return MenuStack.Num() > 0;
}
