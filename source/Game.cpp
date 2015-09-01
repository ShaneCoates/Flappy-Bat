#include <iostream>
#include "Game.h"
#include "AIE.h"
#include "MenuState.h"
#include "SplashState.h"
#include "OptionState.h"
#include "PlayState.h"
#include "HighScoreState.h"
#include "Background.h"
#include "sqlite3.h"
#include "Player.h"
#include "ScrollingText.h"
#include "NewHighScore.h"
#include "LightsOptions.h"
#include "SoundOptions.h"
#include "Apple.h"
#include "Wall.h"

//constructor
Game::Game(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle)
{
	Initialise(windowWidth, windowHeight, false, windowTitle);

	AddFont("./fonts/invaders.fnt");

	m_windowWidth		= windowWidth;
	m_windowHeight		= windowHeight;
	
	m_red				= rand() % 255;
	m_green				= rand() % 255;
	m_blue				= rand() % 255;

	m_difficulty		= 1.0f;
	m_inputCooldown		= 0.0f;
	m_gameOver			= false;
	m_disco				= false;

	m_masterVolume		= 0.5f;
	m_mute				= false;

	/*-------------------------------------------------------------------------
	Sets which gamestate will up drawn
	0 = SPLASH STATE
	1 = MENU STATE
	2 = OPTIONS STATE
	3 = GAME STATE
	4 = HIGH SCORE STATE
	5 = NEW HIGH SCORE STATE
	6 = LIGHT OPTIONS STATE
	7 = SOUND OPTIONS STATE
	-------------------------------------------------------------------------*/
	m_gameState = 0;
	
	m_splashState		= new SplashState(this);
	m_menuState			= new MenuState(this);
	m_optionState		= new OptionState(this);
	m_lightOptions		= new LightOptionState(this);
	m_soundOptions		= new SoundOptionState(this);
	m_highScoreState	= new HighScoreState(this);
	m_newHighScore		= new NewHighScore(this, m_highScoreState);	
	m_background		= new Background(this);
	m_playState			= new PlayState(this, m_highScoreState, m_background);
	m_player			= new Player(this);		
	
	m_player->SetMenu(true);
	m_player->SetWidth(32.0f);
	m_player->SetHeight(32.0f);

	m_highScoreState->ReadFromFile();
	m_highScoreState->FillBlankScores();

	m_audioEngine = irrklang::createIrrKlangDevice();

	m_audioEngine->play2D("./sounds/POL-raindrops-short.wav", true);
}

//destructor
Game::~Game()
{
	
	delete m_splashState;	
	delete m_menuState;		
	delete m_optionState;	
	delete m_playState;	
	delete m_newHighScore;
	delete m_highScoreState;	
	delete m_background;
	delete m_player;

	m_audioEngine->drop();


	Shutdown();
}

//returns when the main game loop has finished
void Game::RunGame()
{
	do
	{
		ClearScreen();
		Update();
		Draw();
	} while (FrameworkUpdate() == false && m_gameOver == false);
}

//called each frame from within RunGame()
void Game::Update()
{
	m_audioEngine->setSoundVolume(m_masterVolume);

	if(IsKeyDown('M') && GetCooldown() <= 0)
	{
		if(m_mute)
		{
			m_mute = false;
			SetCooldown(0.2f);
		}
		else
		{
			m_mute = true;
			SetCooldown(0.2f);
		}
	}

	if(m_mute)
	{
		m_audioEngine->setAllSoundsPaused(true); 
		m_masterVolume = 0;
	}
	else
		m_audioEngine->setAllSoundsPaused(false);


	SetFont("./fonts/invaders.fnt");

	float dt = GetDeltaTime();

	if(m_inputCooldown > 0)
		m_inputCooldown -= dt;
	if(m_gameState == 3 || m_gameState == 0 || m_gameState == 5)
		SetInGame(true);
	else
		SetInGame(false);


	if(!GetInGame())
	{
		m_player->SetX(200);
		m_player->SetY(516 - m_menuState->GetSelected() * 50.0f);
		m_player->Update(dt);
		m_player->Flap(2);
	}

	m_background->Update(dt);

	if(IsKeyDown('Q'))
		m_gameOver = true;


	if(m_gameState == 4)
		m_menuState->SetSelected(2);

	/*-------------------------------------------------------------------------
	Sets which gamestate will up drawn
	0 = SPLASH STATE
	1 = MENU STATE
	2 = OPTIONS STATE
	3 = GAME STATE
	4 = HIGH SCORE STATE
	5 = NEW HIGH SCORE STATE
	6 = LIGHT OPTIONS STATE
	7 = SOUND OPTIONS STATE
	-------------------------------------------------------------------------*/
	if(m_gameState == 0)
		m_splashState->Update(dt);
	else if(m_gameState == 1)
		m_menuState->Update(dt);
	else if(m_gameState == 2)
		m_optionState->Update(dt);
	else if(m_gameState == 3)
		m_playState->Update(dt);
	else if(m_gameState == 4)
		m_highScoreState->Update(dt);
	else if(m_gameState == 5)
		m_newHighScore->Update(dt);
	else if(m_gameState == 6)
		m_lightOptions->Update(dt);
	else if(m_gameState == 7)
		m_soundOptions->Update(dt);

	if(m_menuState->GetSelected() == 2)
	{
		m_highScoreState->Update(dt);
		m_highScoreState->Draw();
	}

}

//called each frame from within RunGame()
void Game::Draw()
{

	m_background->Draw();
	if(!GetInGame())
	{
		m_player->Draw();
	}

	/*-------------------------------------------------------------------------
	Sets which gamestate will up drawn
	0 = SPLASH STATE
	1 = MENU STATE
	2 = OPTIONS STATE
	3 = GAME STATE
	4 = HIGH SCORE STATE
	5 = NEW HIGH SCORE STATE
	6 = LIGHT OPTIONS STATE
	7 = SOUND OPTIONS STATE
	-------------------------------------------------------------------------*/
	if(m_gameState == 0)
		m_splashState->Draw();
	else if(m_gameState == 1)
		m_menuState->Draw();
	else if(m_gameState == 2)
	{
		m_menuState->Draw();
		m_optionState->Draw();
	}
	else if(m_gameState == 3)
		m_playState->Draw();
	else if(m_gameState == 4)
	{
		m_highScoreState->Draw();
		m_menuState->Draw();
	}
	else if(m_gameState == 5)
		m_newHighScore->Draw();
	else if(m_gameState == 6)
	{
		m_lightOptions->Draw();
		m_menuState->Draw();
		m_optionState->Draw();
	}
	else if(m_gameState == 7)
	{
		m_soundOptions->Draw();
		m_menuState->Draw();
		m_optionState->Draw();
	}
}

void Game::Reset()
{
	m_playState->Reset();
	m_highScoreState->Reset();
	m_newHighScore->Reset();
}

void Game::QuitProgram()
{
	m_gameOver = true;
}

void Game::ChangeState( int stateID )
{

	if(GetCooldown() <= 0)
	{
		m_gameState = stateID;	
		SetCooldown(0.1f);	
		m_playState->Reset();
		
	}
}

void Game::SetText(std::string text)
{
	m_background->SetText(text);
}

void Game::AddApple()
{
	m_background->AddApples();
}

void Game::AddWall()
{
	m_background->AddWalls();
}

void Game::IncreaseScore(int score)
{
	m_playState->IncreaseScore(score);
}

bool Game::CheckAppleCollision(Apple *pApple)
{
	if(	pApple->GetX() < 232 &&
		pApple->GetX() > 168 &&
		pApple->GetY() < m_playState->GetPlayerY() + 30 &&
		pApple->GetY() > m_playState->GetPlayerY() - 30 )
		return true;
	else
		return false;
}

bool Game::CheckWallCollision(Wall *pWall)
{
	if		(pWall->GetWhichWall() == 1)
	{
		if(	pWall->GetX() < 222 &&
			pWall->GetX() > 178 &&
			m_playState->GetPlayerY() > pWall->GetY() - pWall->GetHeight()
			)
			return true;
		else
			return false;
	}
	else if (pWall->GetWhichWall() == 2)
	{
		if(	pWall->GetX() < 232 &&
			pWall->GetX() > 168 &&
			m_playState->GetPlayerY() < pWall->GetY()
			)
			return true;
		else 
			return false;
	}
	else if (pWall->GetWhichWall() == 3)
	{
		if(	(pWall->GetX() < 232 &&
			pWall->GetX() > 168 &&
			m_playState->GetPlayerY() > pWall->GetY() - pWall->GetHeight()) ||
			(
			pWall->GetX() < 232 &&
			pWall->GetX() > 168 &&
			m_playState->GetPlayerY() < pWall->GetYPos2()
			)
			)
			return true;
		else 
			return false;
	}
	else
		return false;

}

bool Game::GetNewLight()
{
	return m_background->GetNewLight();
}

void Game::SetDead(bool dead)
{
	m_playState->SetDead(true);
}

void Game::PlayFlapSound()
{
	m_audioEngine->play2D("./sounds/NFF-tiny-whip.wav", false);
}

void Game::PlayDeathSound()
{
	m_audioEngine->play2D("./sounds/NFF-bass-thud.wav", false);
}

void Game::PlayCoinSound()
{
	m_audioEngine->play2D("./sounds/NFF-coin-04.wav", false);
}

void Game::IncreaseDifficulty()
{
	if(m_difficulty < 5)
		m_difficulty++;
	m_playState->SetTempDifficulty(m_difficulty);
}

void Game::DecreaseDifficulty()
{
	if(m_difficulty > 1)	
		m_difficulty--;
	m_playState->SetTempDifficulty(m_difficulty);
}

void Game::SetLastWall(int last)
{
	m_background->SetLastWall(last);
}