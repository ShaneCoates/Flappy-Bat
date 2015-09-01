#include "AIE.h"
#include "SoundOptions.h"
#include "OptionState.h"
#include "ScrollingText.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


//constructor
SoundOptionState::SoundOptionState(Game *pGame)
{
	m_pGame = pGame;

	
	m_selected = 0;

	for(int i = 0; i < 3; i++)
	{
		m_selectedAlpha[i] = 100;
	}
}

//destructor
SoundOptionState::~SoundOptionState()
{

}

void SoundOptionState::Update(float dt)
{
	for(int i = 0; i < 3; i++)
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

void SoundOptionState::Draw()
{
	char buffer[32];

	DrawString("BACK"	, 600, m_pGame->GetTextY() + 200,	SColour(255, 255, 255, m_selectedAlpha[0]));
	
	sprintf(buffer, "VOLUME: %i"	, m_pGame->GetVolume());
	DrawString(buffer		, 600, m_pGame->GetTextY() + 150,	SColour(255, 255, 255, m_selectedAlpha[1]));
	 
	DrawString(m_pGame->GetMute() ? "MUTE: ON" : "MUTE: OFF"		, 600, m_pGame->GetTextY() + 100,	SColour(255, 255, 255, m_selectedAlpha[2]));
	

}

void SoundOptionState::CheckUserInput()
{
	if(IsSavePressed())
		SaveSettings();

	if(IsLoadPressed())
		LoadSettings();

	if(IsSelectPressed())
	{
		if (m_selected == 0)
			m_pGame->ChangeState(2);
	}
	if(IsDownPressed())
	{
		if(m_selected < 2)
			m_selected++;
	}
	if(IsUpPressed())
	{	
		if(m_selected > 0)
			m_selected--;
	}
	if(IsLeftPressed())
	{	
		if		(m_selected == 1)
			m_pGame->DecreaseVolume();
		else if (m_selected == 2)
			m_pGame->SetMute(!m_pGame->GetMute());
	}
	if(IsRightPressed())
	{	
		if		(m_selected == 1)
		{
			if(m_pGame->GetMute())
				m_pGame->SetMute(false);
			m_pGame->IncreaseVolume();
		}
		else if (m_selected == 2)
			m_pGame->SetMute(!m_pGame->GetMute());
	}
}

bool SoundOptionState::IsSelectPressed()
{	
	if(m_selected == 0)
	{
		if(IsKeyDown(KEY_LEFT) || IsKeyDown('A'))
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

bool SoundOptionState::IsDownPressed()
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

bool SoundOptionState::IsUpPressed()
	
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

bool SoundOptionState::IsLeftPressed()
	
{
	if(IsKeyDown(KEY_LEFT))
	{
		if(m_selected != 2)
			SetCooldown(0.01f);
		else
			SetCooldown(0.2f);
		return true;
	}
	else
	{
		return false;
	}
}

bool SoundOptionState::IsRightPressed()
{
	if(IsKeyDown(KEY_RIGHT))
	{
		if(m_selected != 2)
			SetCooldown(0.01f);
		else
			SetCooldown(0.2f);
		return true;
	}
	else
	{
		return false;
	}
}

bool SoundOptionState::IsSavePressed()

{
	if(IsKeyDown('S'))
		return true;
}

bool SoundOptionState::IsLoadPressed()	
{
	if(IsKeyDown('L'))
		return true;
}

void SoundOptionState::SetCooldown(float time)
{
	m_pGame->SetCooldown(time);
}

void SoundOptionState::SaveSettings()
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

void SoundOptionState::LoadSettings()
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
