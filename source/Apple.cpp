#include "Apple.h"
#include "AIE.h"
#include "Game.h"
#include <iostream>


//Constructor
Apple::Apple(Game *pGame) : BackgroundObject(pGame)
{
	m_pGame = pGame;

	//initialise all variables
	m_width = 32.0f;
	m_height = 32.0f;

	//sets apples y position to somewhere within the playable area (170-550)
	m_yPos = 170 + rand() % 380;
	//sets apples x position to the edge of the screen
	m_xPos = m_pGame->GetWindowWidth() + m_width;

	m_sprite = CreateSprite("./images/apple.png", m_width, m_height, true);
}

//Destructor
Apple::~Apple()
{
	DestroySprite(m_sprite);
}

void Apple::Update(float dt)
{
	//calls the BackgroundObject update function
	BackgroundObject::Update(dt);
}

void Apple::Draw()
{
	//calls the BackgroundObject draw function
	BackgroundObject::Draw();
}
