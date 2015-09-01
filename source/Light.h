/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Light Class
		Inherits from BackgroundObject.h
		Draws lights to the screen
		at all times there should be 10 lights on the screen
		when one leaves the screen on the left, a new one will be created on the right
		every light has a randomised alpha value
		certain lights will flicker		
-------------------------------------------------------------------------------*/

#ifndef LIGHT_H
#define LIGHT_H

#include "BackgroundObject.h"

class Light : public BackgroundObject
{
public:

	//Constructor
	Light(Game *pGame);

	//Destructor
	virtual ~Light();

	virtual void Update(float dt);

	virtual void Draw();

	unsigned int Randomise();

	void RandomiseColours();

	void Flicker(float dt);

	void Flash(float dt);

protected:
private:


	unsigned int m_red;
	unsigned int m_green;
	unsigned int m_blue;	
	float m_alpha;
	float m_tempAlpha;
	float m_flickerTimer;
	float m_flashTimer;
	float m_tempFlashTimer;

	

};
#endif