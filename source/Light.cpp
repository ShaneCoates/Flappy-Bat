#include "Light.h"
#include "AIE.h"
#include "Game.h"
#include <iostream>


//Constructor
Light::Light(Game *pGame) : BackgroundObject(pGame)
{
	m_pGame		= pGame;

	m_width		= 128.0f;
	m_height	= 422.0f;

	//sets apples y position to somewhere within the playable area (170-550)
	m_yPos		= m_pGame->GetWindowHeight() * 0.5f;
	//sets apples x position to the edge of the screen
	m_xPos		= m_pGame->GetWindowWidth() + m_width;

	m_alpha		= rand() % 100;
	m_tempAlpha = m_alpha;

	if(m_pGame->GetDisco())
	{
		RandomiseColours();	
	}
	else
	{
		m_red		= m_pGame->GetRed();
		m_green		= m_pGame->GetGreen();
		m_blue		= m_pGame->GetBlue();
	}
	m_sprite = CreateSprite("./images/light.png", m_width, m_height, true);

	m_flickerTimer = (rand() % 100) * 0.01f;
	m_flashTimer =  ((rand() % 80) + 20) * 0.01f;
	m_tempFlashTimer = m_flashTimer;

}

//Destructor
Light::~Light()
{
	DestroySprite(m_sprite);
}

void Light::Update(float dt)
{
	SetSpriteColour(m_sprite, SColour(m_red, m_green, m_blue, m_alpha));

	if(m_pGame->GetDisco())
		Flash(dt);

	if(m_tempAlpha < 20 && !m_pGame->GetDisco())
	{
		Flicker(dt);
	}

	BackgroundObject::Update(dt);
}

void Light::Draw()
{
	BackgroundObject::Draw();
}

void Light::RandomiseColours()
{
	m_red		= Randomise();
	m_green		= Randomise();
	m_blue		= Randomise();	
}

unsigned int Light::Randomise()
{
	return rand() % 255;
}

void Light::Flicker(float dt)
{
	m_alpha += dt * 10;
	if(m_alpha >= rand() % 255)
		m_alpha = 0;
}

void Light::Flash(float dt)
{
	m_flashTimer -= dt;
	if(m_flashTimer <= 0)
	{
		if(m_alpha <= 0 )
			m_alpha = m_tempAlpha;
		else
			m_alpha = 0;

		RandomiseColours();

		m_flashTimer = m_tempFlashTimer;

	}
}