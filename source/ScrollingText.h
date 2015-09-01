/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Scrolling Text Class
		Inherits from the Background Object class
		Will be modified from different states to scroll along the bottom of the screen
-------------------------------------------------------------------------------*/

#ifndef SCROLLING_TEXT_H
#define SCROLLING_TEXT_H

#include <string>
#include "BackgroundObject.h"

class ScrollingText : public BackgroundObject
{
public:

	//Constructor
	ScrollingText(Game *pGame, std::string text);

	//Destructor
	virtual ~ScrollingText();

	virtual void Update(float dt);

	virtual void Draw();

	void SetText(std::string newText);

protected:
private:

	int m_stringLength;
	std::string m_text;

};
#endif