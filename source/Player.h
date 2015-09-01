/*-----------------------------------------------------------------------------

		Author: Shane Coates
		Description: Player class
		Creates a player object
		controls position of player and whether it is alive, dead or in a menu

-----------------------------------------------------------------------------*/

#ifndef PLAYER_H
#define PLAYER_H

class Game;

class Player
{
public:

	//constructor
	Player(Game *pGame);
	
	//destructor
	~Player();

	void Update(float dt);

	void Draw();

	void Flap(float delay);
	void Glide(float dt);
	void Fly(float dt);

	void Flip();

	void SetMenu(bool inMenu);

	float GetX()							{ return m_xPos; }
	void SetX(float x)						{m_xPos = x;}

	float GetY()							{ return m_yPos; }
	void SetY(float y)						{m_yPos = y;}

	float GetHeight()						{ return m_height; }
	void SetHeight(float height)			{m_height = height;}

	float GetWidth()						{ return m_width; }
	void SetWidth(float width)				{m_width = width;}

	bool GetDead()							{ return m_dead; }
	void SetDead(bool dead);				
	

	void ResetSprite()						{m_sprite = m_playerGlide;}

	void ResetRotation();

public:

	unsigned int m_playerGlide;
	unsigned int m_playerFlap1[2];
	unsigned int m_playerFlap2[2];
	unsigned int m_playerDead;
	float m_dt;
	float m_counter;

	float m_fallSpeed;	
	float m_deathRotation;
	float m_totalRotation;
	
private:

	Game *m_pGame;


	int m_flipped;
	bool m_inMenu;
	float m_delay;
	float m_xPos;
	float m_yPos;
	unsigned int m_sprite;
	float m_width;
	float m_height;
	bool m_dead;



};


#endif