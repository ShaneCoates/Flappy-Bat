
#include "AIE.h"
#include "MenuState.h"
#include "Game.h"
#include <string>
#include "Player.h"


//constructor
MenuState::MenuState(Game *pGame)
{
	m_pGame			= pGame;
	
	m_selected = 0;
	for(int i = 0; i < 4; i++)
	{
		m_selectedAlpha[i] = 100;
	}
}

//destructor
MenuState::~MenuState()
{

}

void MenuState::Update(float dt)
{
	if(m_pGame->GetCooldown() <=0)
	{
		CheckUserInput();
	}
	m_pGame->SetText("ARROW KEYS TO NAVIGATE");
}

void MenuState::Draw()
{
	for(int i = 0; i < 4; i++)
	{
		m_selectedAlpha[i] = 100;
	}
	m_selectedAlpha[m_selected] = 255;

	DrawString("PLAY"		, 250, m_pGame->GetTextY() + 400, SColour(255, 255, 255, m_selectedAlpha[0]));
	DrawString("OPTIONS"	, 250, m_pGame->GetTextY() + 350, SColour(255, 255, 255, m_selectedAlpha[1]));
	DrawString("HIGH SCORES", 250, m_pGame->GetTextY() + 300, SColour(255, 255, 255, m_selectedAlpha[2]));
	DrawString("QUIT"		, 250, m_pGame->GetTextY() + 250, SColour(255, 255, 255, m_selectedAlpha[3]));
}

void MenuState::Play()
{
	m_pGame->ChangeState(3);
}

void MenuState::Options()
{
	m_pGame->ChangeState(2);
}

void MenuState::HighScores()
{
	m_pGame->ChangeState(4);
}

void MenuState::Quit()
{
	m_pGame->QuitProgram();
}

void MenuState::CheckUserInput()
{
	if(IsSelectPressed())
	{
		if		(m_selected == 0)
			Play();
		else if (m_selected == 1)
			Options();
		else if (m_selected == 3)
			Quit();
	}
	if(IsDownPressed())
	{
		if(m_selected < 3)
			m_selected++;
	}
	if(IsUpPressed())
	{	
		if(m_selected > 0)
			m_selected--;
	}

}

bool MenuState::IsSelectPressed()
{
	if(m_selected == 1)
	{
		if(IsKeyDown(KEY_RIGHT) || IsKeyDown('D'))
		{
			return true;
		}
	}

	if(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_ENTER))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MenuState::IsDownPressed()
{
	if(IsKeyDown(KEY_DOWN) || IsKeyDown('S'))
	{
		SetCooldown(0.1f);
		return true;
	}
	else
	{
		return false;
	}
}

bool MenuState::IsUpPressed()
	
{
	if(IsKeyDown(KEY_UP) || IsKeyDown('W'))
	{
		SetCooldown(0.1f);
		return true;
	}
	else
	{
		return false;
	}
}

void MenuState::SetCooldown(float time)
{
	m_pGame->SetCooldown(time);
}