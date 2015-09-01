#include "Game.h"
#include "HighScoreState.h"
#include "ScoreEntry.h"
#include "NewHighScore.h"
#include "AIE.h"


NewHighScore::NewHighScore(Game *pGame, HighScoreState *pHighScoreState)
{
	m_pGame = pGame;
	m_pHighScoreState = pHighScoreState;


	m_score = 0;
	m_tempScore = 0;
	m_place = 0;

	for(int i = 0; i < 3; i++)
	{
		m_textAlpha[i] = 100;
		m_name[i] = 'A';
	}
}

NewHighScore::~NewHighScore()
{
}

void NewHighScore::Update(float dt)
{
	m_pGame->SetText("NEW HIGH SCORE!");
	
	CheckUserInput();
	if(!m_pHighScoreState->GetIsNew())
	{
		m_pGame->Reset();		
		m_pGame->ChangeState(4);
	}
	else
		{
		m_tempScore = m_pHighScoreState->GetScore();

		for(int i = 0; i < 3; i++)
		{
			m_textAlpha[i] = 100;
		}
		m_textAlpha[m_place] = 255;

		float m_dt = dt;

		if(m_score < m_tempScore)
			m_score += m_tempScore*m_dt;
		else
			m_score = m_tempScore;


		for(int i = 0; i < 3; i++)
		{
			sprintf(buffer, "%c", m_name[i]);
			DrawString(buffer, (m_pGame->GetWindowWidth() *0.5f) - 100.0f + (100.0f*i) ,m_pGame->GetWindowHeight() * 0.5f, SColour(255, 255, 255, m_textAlpha[i]));
		}

		sprintf(buffer, "%i", m_score);
		DrawString(buffer, (m_pGame->GetWindowWidth() *0.5f) - strlen(buffer)*6 ,m_pGame->GetWindowHeight() * 0.5f -50);
	}
}

void NewHighScore::Draw()
{

}

void NewHighScore::Reset()
{
	m_score = 0;
	m_tempScore = 0;
	m_place = 0;

	for(int i = 0; i < 3; i++)
	{
		m_textAlpha[i] = 100;
		m_name[i] = 'A';
	}
}

void NewHighScore::CheckUserInput()
{
	
	if((IsKeyDown(KEY_BACKSPACE) || IsKeyDown(KEY_LEFT)) && m_pGame->GetCooldown() < 0.0f && m_place > 0)
		{
			m_place--;
			m_pGame->SetCooldown(0.2f);
		}
	if(IsKeyDown(KEY_UP) && m_pGame->GetCooldown() < 0.0f && m_place < 4 && m_name[m_place] > 65)
		{
			m_name[m_place]--;
			m_pGame->SetCooldown(0.1f);	
		}
	if(IsKeyDown(KEY_DOWN)&& m_pGame->GetCooldown() < 0.0f && m_place < 4 && m_name[m_place] < 90)
		{
			m_name[m_place]++;
			m_pGame->SetCooldown(0.1f);	
		}
	if((IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_RIGHT)) && m_pGame->GetCooldown() < 0.0f)
		{
			m_place++;	
			if(m_place < 2)
			{
				m_pGame->SetCooldown(0.2f);	
			}
		}
	if(m_place == 3)
		{		
			char nameBuffer[4];
			sprintf(nameBuffer, "%c%c%c", m_name[0], m_name[1], m_name[2]);
			m_pHighScoreState->AddScore(new ScoreEntry(nameBuffer, m_tempScore));
			m_pHighScoreState->SetIsNew(false);
		}
	
	for(int i = 65; i < 91; i++)
		{
		if(IsKeyDown(i) && m_pGame->GetCooldown() < 0.0f)
			{
				m_name[m_place] = i;
				if(m_place < 2)
				{
					m_place++;
				}
				m_pGame->SetCooldown(0.2f);
			}
		}

	if(IsKeyDown(KEY_ESCAPE))
		m_pGame->ChangeState(4);
}