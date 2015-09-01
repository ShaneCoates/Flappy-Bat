#include "SplashState.h"
#include "AIE.h"
#include "Game.h"

//constructor
SplashState::SplashState( Game *pGame)
{
	m_pGame = pGame;

	m_time = 3.0f;

	m_splashImage = CreateSprite("./images/SplashScreen.png", m_pGame->GetWindowWidth()/2, m_pGame->GetWindowHeight()/2, true);

}

//destructor
SplashState::~SplashState()
{
	DestroySprite(m_splashImage);
}

void SplashState::Update(float dt)
{

	MoveSprite(m_splashImage, m_pGame->GetWindowWidth()/2, m_pGame->GetWindowHeight()/2);

	m_time -= dt;
	if(m_time < 0.0 || IsKeyDown(KEY_SPACE))
	{
		m_pGame->ChangeState(1);
	}

	m_pGame->SetText("PRESS SPACE TO SKIP");

}

void SplashState::Draw()
{
	DrawSprite(m_splashImage);
}