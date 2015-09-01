/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Wall State
		Inherits from BackgroundObject.h
		Randomly spawns as player moves
		When player collides with wall they die
-------------------------------------------------------------------------------*/

#ifndef WALL_H
#define WALL_H

#include "BackgroundObject.h"

class Wall : public BackgroundObject
{
public:

	//Constructor
	Wall(Game *pGame);

	//Destructor
	virtual ~Wall();

	virtual void Update(float dt);

	virtual void Draw();

	unsigned int GetWhichWall()		{return m_whichWall;}
	unsigned int GetYPos2()			{return m_yPos2;}


protected:
private:

	unsigned int m_whichWall;
	unsigned int m_sprite2;
	unsigned int m_yPos2;

};
#endif