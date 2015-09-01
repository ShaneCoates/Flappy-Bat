/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Inherited class that will control all objects that scroll
-----------------------------------------------------------------------------*/

#ifndef BACKGROUND_OBJECT_H
#define BACKGROUND_OBJECT_H

#include "AIE.h"
#include "Game.h"

class BackgroundObject
{
public:

	//default constructor
	BackgroundObject(Game *pGame){}

	//destructor
	virtual ~BackgroundObject()
	{	
		m_xPos = 0;
		m_yPos = 0;
		m_height = 32;
		m_width = 32;
	
		m_sprite = -1;	
	}

	virtual void Update(float dt)
	{
		m_xPos -= dt * m_pGame->GetDifficulty() * 100;
	}

	virtual void Draw()
	{	
		SetSpriteScale( m_sprite, m_width, m_height);
		MoveSprite( m_sprite, m_xPos, m_yPos );
		DrawSprite( m_sprite );	
	}


	//Getters and Setters
	//Used when other objects/classes need to access the private variables that an entity holds
	float GetX()							{ return m_xPos; }
	void SetX(float x)						{m_xPos = x;}

	float GetY()							{ return m_yPos; }
	void SetY(float y)						{m_yPos = y;}

	virtual float GetHeight()				{ return m_height; }
	virtual void SetHeight(float height)	{m_height = height;}

	float GetWidth()						{ return m_width; }
	void SetWidth(float width)				{m_width = width;}

	int GetSprite()							{ return m_sprite; }
	void SetSprite(int spriteID)			{ m_sprite = spriteID; };

	bool OffScreen()
	{
		if(m_xPos <= m_width * -1.0f)
			return true;
		else
			return false;
	}


protected:

	float m_xPos;
	float m_yPos;
	float m_height;
	float m_width;

	unsigned int m_sprite;

	Game *m_pGame;

private:

};


#endif