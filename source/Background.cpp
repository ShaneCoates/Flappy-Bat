#include "AIE.h"
#include "Background.h"
#include "Game.h"
#include "Player.h"
#include "Apple.h"
#include "Light.h"
#include "Lamp.h"
#include "Wall.h"
#include "ScrollingText.h"



//constructor
Background::Background(Game *pGame)
{
	m_pGame = pGame;

	//initialise all background variables
	m_backgroundImage	= CreateSprite("./images/background.png", m_pGame->GetWindowWidth() * 3, m_pGame->GetWindowHeight(), true);
	m_title				= CreateSprite("./images/TitleBar.png", 640, 120, true);

	m_titleXPos			= m_pGame->GetWindowWidth() * 0.5f;
	m_titleyPos			= m_pGame->GetWindowHeight() * 0.95f;

	m_bgXPos			= m_pGame->GetWindowWidth() * 1.5f;
	m_bgYPos			= m_pGame->GetWindowHeight() * 0.5f;
	
	m_lightCounter		= 0;
	m_textCounter		= 0;

	m_lightTimer		= 1.5;

	m_lastWall = 0;

	m_newLight = false;

	CreateLights();
	CreateText();
}

//destructor
Background::~Background()
{
	DestroySprite(m_backgroundImage);
	DestroySprite(m_title);
}

void Background::Update(float dt)
{	
	m_newLight = false;

	MoveSprite(m_backgroundImage, m_bgXPos, m_bgYPos);
	MoveSprite(m_title, m_titleXPos, m_titleyPos);

	UpdateBackground(dt);
	UpdateWalls(dt);
	UpdateLights(dt);
	UpdateApples(dt);
	UpdateText(dt);

}

void Background::Draw()
{
	DrawBackground();
	DrawLights();
	DrawWalls();
	DrawApples();
	DrawText();

	if(m_pGame->GetGameState() != 0)
		DrawSprite(m_title);
}

void Background::DrawTitle()
{
	DrawSprite(m_title);
}

void Background::AddWalls()
{
	m_wall.push_back(new Wall(m_pGame));
}

void Background::AddLights()
{
	m_lamp.push_back(new Lamp(m_pGame));
	m_light.push_back(new Light(m_pGame));
	m_newLight = true;
}

void Background::AddApples()
{
	m_apple.push_back(new Apple(m_pGame));
}

void Background::AddText()
{
	m_scrollingText.push_back(new ScrollingText(m_pGame, "PRESS SPACE TO SKIP"));
}

void Background::UpdateBackground(float dt)
{
	m_bgXPos -= dt * m_pGame->GetDifficulty() * 100;

	if (m_bgXPos <= m_pGame->GetWindowWidth() * -0.5f)
	{
		m_bgXPos = m_pGame->GetWindowWidth() * 1.5f;
	}
}

void Background::UpdateWalls(float dt)
{
	for(auto itr = m_wall.begin(); itr != m_wall.end();)
	{
		Wall *currWall = *itr;
		if(currWall->GetX() < -64.0f)
		{
			delete currWall;
			itr = m_wall.erase(itr);
			continue;
		} 
		else if (m_pGame->CheckWallCollision(currWall))
		{
			m_pGame->SetDead(true);
		}

		currWall->Update(dt);
		++itr;
	}
}

void Background::UpdateLights(float dt)
{
	m_lightTimer -= dt*m_pGame->GetDifficulty();
	if(m_lightTimer <= 0)
	{
		if(m_lastWall != 1 && m_lastWall != 3)
		{
			AddLights();
		}
		else
			m_lastWall = 0;
		m_lightTimer = 1;
	}

	for(auto itr = m_light.begin(); itr != m_light.end();)
	{
		Light *currLight = *itr;
		if(currLight->OffScreen())
		{
			delete currLight;
			itr = m_light.erase(itr);
			continue;
		} 
		else 
		{
			currLight->Update(dt);
		}
		++itr;
	}

	for(auto itr = m_lamp.begin(); itr != m_lamp.end();)
	{
		Lamp *currLamp = *itr;
		if(currLamp->OffScreen())
		{
			delete currLamp;
			itr = m_lamp.erase(itr);
			continue;
		} 
		else 
		{
			currLamp->Update(dt);
		}
		++itr;
	}


}

void Background::UpdateApples(float dt)
{
	for(auto itr = m_apple.begin(); itr != m_apple.end();)
	{
		Apple *currApple = *itr;
		if(currApple->GetX() < -32.0f)
		{
			delete currApple;
			itr = m_apple.erase(itr);
			continue;
		} 
		else if (m_pGame->CheckAppleCollision(currApple))
		{
			m_pGame->IncreaseScore(1000 * m_pGame->GetDifficulty());
			delete currApple;
			itr = m_apple.erase(itr);
			m_pGame->PlayCoinSound();
			continue;
		}
		else
		{
			currApple->Update(dt);
		}
		++itr;
	}
}

void Background::UpdateText(float dt)
{
	for(auto itr = m_scrollingText.begin(); itr != m_scrollingText.end();)
	{
		ScrollingText *currText = *itr;
		if(currText->OffScreen())
		{
			delete currText;
			itr = m_scrollingText.erase(itr);
			AddText();
			continue;
		} 
		else 
		{
			currText->Update(dt);
		}
		++itr;
	}
}

void Background::DrawBackground()
{
	DrawSprite(m_backgroundImage);
}

void Background::DrawWalls()
{
	for(auto itr = m_wall.begin(); itr != m_wall.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

void Background::DrawLights()
{
	for(auto itr = m_light.begin(); itr != m_light.end(); ++itr)
	{
		(*itr)->Draw();
	}
	for(auto itr = m_lamp.begin(); itr != m_lamp.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

void Background::DrawApples()
{
	for(auto itr = m_apple.begin(); itr != m_apple.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

void Background::DrawText()
{
	for(auto itr = m_scrollingText.begin(); itr != m_scrollingText.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

void Background::CreateLights()
{
	for(int i = 0; i < 16; i++)
	{
	AddLights();
	}

	for(auto itr = m_light.begin(); itr != m_light.end();)
	{
		Light *currLight = *itr;
		currLight->SetX(m_lightCounter * 96);
		++m_lightCounter;
		++itr;
	}
	
	m_lightCounter = 0;

	for(auto itr = m_lamp.begin(); itr != m_lamp.end();)
	{
		Lamp *currLamp = *itr;
		currLamp->SetX(m_lightCounter * 96);
		++m_lightCounter;
		++itr;
	}
}

void Background::CreateText()
{
	for(int i = 0; i < 3; i++)
	{
	AddText();
	}

	for(auto itr = m_scrollingText.begin(); itr != m_scrollingText.end();)
	{
		ScrollingText *currText = *itr;
		currText->SetX(m_textCounter * m_pGame->GetWindowWidth() / 2.0f );
		++m_textCounter;
		++itr;
	}
	
	m_textCounter = 0;
}

void Background::SetText(std::string newText)
{
	for(auto itr = m_scrollingText.begin(); itr != m_scrollingText.end();)
	{
		ScrollingText *currText = *itr;
		currText->SetText(newText);
		++itr;
	}
}

