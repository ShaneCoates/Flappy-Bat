#include "ScrollingText.h"
#include "AIE.h"
#include "Game.h"
#include <iostream>



//Constructor
ScrollingText::ScrollingText(Game *pGame, std::string text) : BackgroundObject(pGame)
{	
	m_pGame			= pGame;
	
	m_text			= text;
	m_stringLength	= m_text.length();
	m_width			= m_pGame->GetWindowWidth() / 3.5;
	m_height		= 0.0f;	
	m_yPos			= m_pGame->GetTextY();
	m_xPos			= m_pGame->GetWindowWidth() + m_width;
}

//Destructor
ScrollingText::~ScrollingText()
{

}

void ScrollingText::Update(float dt)
{
	BackgroundObject::Update(dt);

}

void ScrollingText::Draw()
{
	DrawString(m_text.c_str(), m_xPos, m_yPos);
}

void ScrollingText::SetText(std::string newText)
{
	m_text			= newText;
}
