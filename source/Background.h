/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Background State
		holds all background objects
		controls all background objects
			background objects:
				- lights
				- lamps
				- apples
				- walls
				- background image

		moves all objects depending on current difficulty
		checks for player collision with apples and walls
-------------------------------------------------------------------------------*/

#include <list>

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Game;
class Apple;
class Lamp;
class Light;
class Wall;
class Player;
class ScrollingText;


class Background
{
public:

	//constructor
	Background(Game *pGame);

	//destructor
	~Background();

	void Update(float dt);
	void Draw();
	void DrawTitle();
	void AddWalls();
	void AddLights();
	void AddApples();
	void AddText();
	void UpdateBackground(float dt);
	void UpdateWalls(float dt);
	void UpdateLights(float dt);
	void UpdateApples(float dt);
	void UpdateText(float dt);
	void DrawBackground();
	void DrawWalls();
	void DrawLights();
	void DrawApples();
	void DrawText();
	void CreateLights();
	void CreateText();
	void SetText(std::string newText);

	bool GetNewLight()				{return m_newLight;}
	void SetLastWall(int last)		{m_lastWall = last;}

protected:

	Game *m_pGame;
	std::list<Apple *>			m_apple;
	std::list<Lamp *>			m_lamp;
	std::list<Light *>			m_light;
	std::list<Wall *>			m_wall;
	std::list<ScrollingText *>	m_scrollingText;

private:

	unsigned int m_backgroundImage;
	unsigned int m_title;

	float m_titleXPos;
	float m_titleyPos;

	float m_bgXPos;
	float m_bgYPos;

	float m_lightCounter;
	float m_textCounter;

	bool m_newLight;

	int m_lastWall;

	float m_lightTimer;

};

#endif