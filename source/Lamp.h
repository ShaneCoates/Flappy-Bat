/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Very Basic Lamp Class
		Moves alongside all LIGHT class objects
-------------------------------------------------------------------------------*/

#ifndef LAMP_H
#define LAMP_H

#include "BackgroundObject.h"

class Lamp : public BackgroundObject
{
public:

	//Constructor
	Lamp(Game *pGame);

	//Destructor
	virtual ~Lamp();

	virtual void Update(float dt);

	virtual void Draw();



protected:
private:

};
#endif