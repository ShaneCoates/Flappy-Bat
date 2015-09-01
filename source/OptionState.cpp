#include "AIE.h"
#include "OptionState.h"
#include "ScrollingText.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


//constructor
OptionState::OptionState(Game *pGame)
{
	m_pGame = pGame;

	
	m_selected = 0;

	for(int i = 0; i < 4; i++)
	{
		m_selectedAlpha[i] = 100;
	}
}

//destructor
OptionState::~OptionState()
{

}

void OptionState::Update(float dt)
{
	for(int i = 0; i < 4; i++)
	{
		m_selectedAlpha[i] = 100;
	}
	m_selectedAlpha[m_selected] = 255;

	if(m_pGame->GetCooldown() <=0)
	{
		CheckUserInput();
	}

	if (IsKeyDown(KEY_ESCAPE))
	{
		m_selected = 0;
		m_pGame->ChangeState(1);
	}

	m_pGame->SetText("'S' TO SAVE     'L' TO LOAD     'R' TO RANDOMISE");

}

void OptionState::Draw()
{
	char buffer[32];

	DrawString("BACK"		, 450, m_pGame->GetTextY() + 350,	SColour(255, 255, 255, m_selectedAlpha[0]));
	
	sprintf(buffer, "DIFFICULTY: %i", (int)m_pGame->GetDifficulty());
	DrawString(buffer		, 450, m_pGame->GetTextY() + 300,	SColour(255, 255, 255, m_selectedAlpha[1]));

	DrawString("LIGHTS"		, 450, m_pGame->GetTextY() + 250,	SColour(255, 255, 255, m_selectedAlpha[2]));
	
	DrawString("SOUND"		, 450, m_pGame->GetTextY() + 200,	SColour(255, 255, 255, m_selectedAlpha[3]));
	
}

void OptionState::CheckUserInput()
{
	if(IsSavePressed())
		SaveSettings();

	if(IsLoadPressed())
		LoadSettings();

	if(IsSelectPressed())
	{
		if (m_selected == 0)
			m_pGame->ChangeState(1);
		else if(m_selected == 2)
			m_pGame->ChangeState(6);
		else if(m_selected == 3)
			m_pGame->ChangeState(7);
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
	if(IsRightPressed())
	{
		if(m_selected == 1)
			m_pGame->IncreaseDifficulty();
	}
	if(IsLeftPressed())
	{
		if(m_selected == 1)
			m_pGame->DecreaseDifficulty();
	}

	if(IsKeyDown('R'))
	{
		m_pGame->SetRed(rand() % 255);
		m_pGame->SetGreen(rand() % 255);
		m_pGame->SetBlue(rand() % 255);
	}
}

bool OptionState::IsSelectPressed()
{	
	if(m_selected == 0)
	{
		if(IsKeyDown(KEY_LEFT) || IsKeyDown('A'))
		{
			return true;
		}
	}

	if(m_selected == 2 || m_selected == 3)
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

bool OptionState::IsDownPressed()
{
	if(IsKeyDown(KEY_DOWN))
	{
		SetCooldown(0.1f);
		return true;
	}
	else
	{
		return false;
	}
}

bool OptionState::IsUpPressed()
	
{
	if(IsKeyDown(KEY_UP))
	{
		SetCooldown(0.1f);
		return true;
	}
	else
	{
		return false;
	}
}
bool OptionState::IsLeftPressed()
	
{
	if(IsKeyDown(KEY_LEFT))
	{
		SetCooldown(0.2f);
		return true;
	}
	else
	{
		return false;
	}
}

bool OptionState::IsRightPressed()
	
{
	if(IsKeyDown(KEY_RIGHT))
	{
		SetCooldown(0.2f);
		return true;
	}
	else
	{
		return false;
	}
}

bool OptionState::IsSavePressed()

{
	if(IsKeyDown('S'))
		return true;
}

bool OptionState::IsLoadPressed()	
{
	if(IsKeyDown('L'))
		return true;
}

void OptionState::SetCooldown(float time)
{
	m_pGame->SetCooldown(time);
}

void OptionState::SaveSettings()
{
	fstream file("Settings.txt", ios_base::out | ios::binary);

	if(file.is_open())
	{
		file << m_pGame->GetDifficulty() << std::endl;
		file << m_pGame->GetRed() << std::endl;
		file << m_pGame->GetBlue() << std::endl;
		file << m_pGame->GetGreen() << std::endl;
		file << m_pGame->GetMute() << std::endl;
		file << m_pGame->GetVolume() << std::endl;
	}

	file.close();
}

void OptionState::LoadSettings()
{
	fstream file("Settings.txt", ios_base::in | ios::binary);
	unsigned int loadedSetting = 0;
	if(file.is_open())
	{
		file >> loadedSetting;
		m_pGame->SetDifficulty(loadedSetting);
		
		file >> loadedSetting;
		m_pGame->SetRed(loadedSetting);
		
		file >> loadedSetting;
		m_pGame->SetBlue(loadedSetting);
		
		file >> loadedSetting;
		m_pGame->SetGreen(loadedSetting);
		
		file >> loadedSetting;
		m_pGame->SetMute(loadedSetting);

		file >> loadedSetting;
		m_pGame->SetVolume((float) 0.01f * loadedSetting);


	}
	file.close();
	
}
