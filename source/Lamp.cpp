#include "Lamp.h"
#include "AIE.h"
#include "Game.h"
#include <iostream>


//Constructor
Lamp::Lamp(Game *pGame) : BackgroundObject(pGame)
{
	m_pGame = pGame;

	m_width = 64.0f;
	m_height = 50.0f;

	//sets lamp y position to the height of the black bar along the top of the screen
	m_yPos = 570 + m_height * 0.5f;
	//sets lamp x position to the edge of the screen
	m_xPos = m_pGame->GetWindowWidth() + m_width * 2.0f;

	m_sprite = CreateSprite("./images/lamp.png", m_width, m_height, true);

}

//Destructor
Lamp::~Lamp()
{
	DestroySprite(m_sprite);
}

void Lamp::Update(float dt)
{
	BackgroundObject::Update(dt);
}

void Lamp::Draw()
{
	BackgroundObject::Draw();
}
