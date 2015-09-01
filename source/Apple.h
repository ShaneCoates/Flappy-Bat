/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Apple State
		Inherits from BackgroundObject.h
		Randomly spawns as player moves
		When player collides with apple their score goes up
		Score increases relative to current difficulty
-------------------------------------------------------------------------------*/

#ifndef APPLE_H
#define APPLE_H

#include "BackgroundObject.h"

class Apple : public BackgroundObject
{
public:

	//Constructor
	Apple(Game *pGame);

	//Destructor
	virtual ~Apple();

	virtual void Update(float dt);

	virtual void Draw();

protected:
private:

};
#endif