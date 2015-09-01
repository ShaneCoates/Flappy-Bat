#include "AIE.h"
#include "PlayState.h"
#include "HighScoreState.h"
#include "Game.h"
#include "Player.h"
#include <string>
#include "Background.h"


//constructor
PlayState::PlayState(Game *pGame, HighScoreState *pHighScoreState, Background *pBackground)
{
	m_pGame = pGame;
	m_pHighScoreState = pHighScoreState;
	m_pBackground = pBackground;
	m_Player = new Player(m_pGame);

	m_Player->SetMenu(false);
	m_Player->SetWidth(32.0f);
	m_Player->SetHeight(32.0f);
	m_Player->SetX(200);
	m_Player->SetY(516);

	m_tempDifficulty = 1;

	m_score = 0;

	m_newGame = false;

	m_appleTimer = rand() % 5 + 5;
	m_wallTimer  = 2;
}

//destructor
PlayState::~PlayState()
{
	delete m_Player;
}

void PlayState::Update(float dt)
{

	if(m_newGame)
		NewGame(dt);

	if(!m_Player->GetDead())
	{
		m_score += dt * 1000;
		m_pGame->IncreaseDifficulty(dt * 0.1f);
	}
	
	if(m_pGame->GetNewLight())
	{
		m_wallTimer  -= 1; 
		m_appleTimer -= 1;
	}

	CheckCollisions();
	
	if (IsKeyDown(KEY_ESCAPE))
	{
		m_pGame->ChangeState(1);
	}

	if(m_appleTimer <= 0)
	{
		m_pGame->AddApple();
		m_appleTimer = rand() % 5 + 5;
	}

	if(m_wallTimer <= 0)
	{
		m_pGame->AddWall();
		m_wallTimer = 4;
	}

	if(!m_newGame)
		m_Player->Update(dt);

	m_pGame->SetText("PRESS SPACE TO FLY");
}

void PlayState::Draw()
{
	char buffer[32];
	sprintf(buffer, "SCORE: %i", m_score);
	DrawString(buffer, 100, m_pGame->GetWindowHeight() - m_pGame->GetTextY() / 2);

	m_Player->Draw();
}

void PlayState::Reset()
{	
	m_Player->ResetRotation();
	m_Player->SetMenu(false);
	m_Player->SetDead(false);
	m_Player->SetWidth(32.0f);
	m_Player->SetHeight(32.0f);
	m_Player->SetX(200);
	m_Player->SetY(516);
	m_Player->ResetSprite();
	m_score = 0;
	m_newGame = true;
	m_pGame->SetDifficulty(m_tempDifficulty);

}

void PlayState::CheckCollisions()
{
	if(m_Player->GetY() < 160)
	{
		m_pHighScoreState->NewHighScore(m_score);
		m_pGame->ChangeState(4);
	}

	if(IsKeyDown('D'))
		m_Player->SetDead(true);

	if(m_Player->GetY() > 550)
		m_Player->SetDead(true);

	if(m_Player->GetY() < 160)		
		m_Player->SetDead(true);

}

unsigned int PlayState::GetPlayerY()
{
	return m_Player->GetY();
}

void PlayState::SetDead(bool dead)
{
	if(!m_newGame)
	{
		m_Player->SetDead(true);
	}
}

void PlayState::NewGame(float dt)
{
	if(m_Player->GetHeight() < 64.0f)
	{
		m_Player->SetHeight(m_Player->GetHeight() + 32*dt);
		m_Player->SetWidth(m_Player->GetWidth() + 32*dt);
		m_Player->SetY(m_Player->GetY() - 100*dt);
	}
	else
	{
		m_Player->SetHeight(64.0f);
		m_Player->SetWidth(64.0f);
		m_newGame = false;
	}
	m_tempDifficulty = (int)m_pGame->GetDifficulty();
}