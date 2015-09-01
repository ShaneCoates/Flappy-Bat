#include "Wall.h"
#include "AIE.h"
#include "Game.h"
#include <iostream>


//Constructor
Wall::Wall(Game *pGame) : BackgroundObject(pGame)
{
	m_pGame = pGame;

	m_width = 64.0f;
	m_height = 175 + rand() % 80;
	m_whichWall = rand() % 3 + 1;
	
	m_pGame->SetLastWall(m_whichWall);
	//sets apples y position to somewhere within the playable area (170-550)
	
	if (m_whichWall == 3)
		m_height *= 0.7;

	m_yPos2 = 	m_yPos = m_pGame->GetTextY() + m_height;


	if		(m_whichWall == 1 || m_whichWall == 3)
		m_yPos = m_pGame->GetWindowHeight() -145;
	else if (m_whichWall == 2)
		m_yPos = m_pGame->GetTextY() + m_height + 10;

	//sets wall x position to the edge of the screen
	m_xPos = m_pGame->GetWindowWidth() + m_width * 3.0f;

	m_sprite2 = m_sprite = CreateSprite("./images/WallFromFloor.png", 64.0f, m_height, false);

	if		(m_whichWall == 1 || m_whichWall == 3)
		m_sprite = CreateSprite("./images/WallFromRoof.png", 64.0f, m_height, false);
	else if (m_whichWall == 2)
		m_sprite = CreateSprite("./images/WallFromFloor.png", 64.0f, m_height, false);

}

//Destructor
Wall::~Wall()
{
	DestroySprite(m_sprite);
	DestroySprite(m_sprite2);
}

void Wall::Update(float dt)
{
	BackgroundObject::Update(dt);		

}


void Wall::Draw()
{
	BackgroundObject::Draw();
		
	if (m_whichWall == 3)
	{
		SetSpriteScale( m_sprite2, m_width, m_height);
		MoveSprite( m_sprite2, m_xPos, m_yPos2 );
		DrawSprite( m_sprite2 );	
	}
}
