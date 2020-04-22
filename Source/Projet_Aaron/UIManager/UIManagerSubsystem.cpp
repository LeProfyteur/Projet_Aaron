#include "UIManagerSubsystem.h"

void UIManagerSubsystem::Reset()
{
	MenuStack.Reset();
}

void UIManagerSubsystem::PushMenu(UUserWidget* Menu)
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
	Menu->AddToViewport();
	Menu->SetFocus();
	MenuStack.Push(Menu);
}

void UIManagerSubsystem::PopMenu()
{
	//Collapse & remove Current Menu from the Viewport (if exists)
	if (UUserWidget* CurrentMenu = GetCurrentMenu())
	{
		CurrentMenu->SetVisibility(ESlateVisibility::Collapsed);
		CurrentMenu->RemoveFromViewport();

		MenuStack.Pop(true);
	}

	//If there is still a Current Menu, Display this one
	if (UUserWidget* CurrentMenu = GetCurrentMenu())
	{
		CurrentMenu->SetVisibility(ESlateVisibility::Visible);
		CurrentMenu->SetFocus();
	}
}

UUserWidget* UIManagerSubsystem::GetCurrentMenu() const
{
	if (IsShowingAMenu())
	{
		return MenuStack.Last();
	}
	return nullptr;
}

bool UIManagerSubsystem::IsShowingAMenu() const
{
	return MenuStack.Num() > 0;
}
