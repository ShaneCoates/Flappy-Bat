#include "Player.h"
#include "AIE.h"
#include <iostream>
#include "Game.h"


//constructor
Player::Player(Game *pGame)
{

	m_pGame = pGame;

	m_width = 64;
	m_height = 64;


	m_playerGlide		= CreateSprite("./Images/PlayerGlide.png", (int)m_width, (int)m_height, true);
	m_playerFlap1[0]	= CreateSprite("./Images/PlayerFlap.png", (int)m_width, (int)m_height, true);
	m_playerFlap1[1]	= CreateSprite("./Images/ReverseFlap.png", (int)m_width, (int)m_height, true);
	m_playerFlap2[0]	= CreateSprite("./Images/PlayerFlap1.png", (int)m_width, (int)m_height, true);
	m_playerFlap2[1]	= CreateSprite("./Images/ReverseFlap1.png", (int)m_width, (int)m_height, true);

	m_playerDead		= CreateSprite("./Images/PlayerGlide.png", (int)m_width, (int)m_height, true);

	m_sprite = m_playerGlide;

	m_counter = 0;

	m_fallSpeed = 0;

	m_xPos = 150;
	m_yPos = 248;

	m_deathRotation = 0;
	m_totalRotation = 0;
	m_flipped = 0;
	m_inMenu = false;
	m_delay = 0.0f;
	m_dead = false;
}
	
//destructor
Player::~Player()
{
	DestroySprite(m_playerGlide);
	DestroySprite(m_playerFlap1[0]);
	DestroySprite(m_playerFlap1[1]);
	DestroySprite(m_playerFlap2[0]);
	DestroySprite(m_playerFlap2[1]);	
	DestroySprite(m_playerDead);		
}

void Player::Update(float dt)
{
	m_dt = dt;
	if(m_dead)
	{
		RotateSprite(m_playerDead, -m_totalRotation);
		RotateSprite(m_playerDead, m_deathRotation);
		m_totalRotation = m_deathRotation;
	}
	if(!m_inMenu)
	{
		if(m_dead)
		{
			m_sprite = m_playerDead;
			m_deathRotation -= 1.5f;
			m_fallSpeed += 800 * dt;
			m_yPos -= dt * (100 + m_fallSpeed);
		}
		else
		{
			if(IsKeyDown(KEY_SPACE))
			{
				Fly(dt);
			}
			else
			{
				Glide(dt);
			}
		}
	}
}

void Player::Draw()
{
	SetSpriteScale(m_sprite, m_width, m_height);
	MoveSprite(m_sprite, m_xPos, m_yPos);
	DrawSprite(m_sprite);
}

void Player::Flap(float delay)
{
	
	m_delay = delay;

	if(m_counter > m_delay * 2.0f)
	{
		m_counter = 0;
	}		
	if(m_counter == 0)
		m_pGame->PlayFlapSound();

	m_counter += m_dt * 10;

	if(m_counter < m_delay )
	{
		m_sprite = m_playerFlap1[m_flipped];
	}
	else if(m_counter < m_delay * 1.5f)
	{
		m_sprite = m_playerFlap2[m_flipped];
	}



}

void Player::Fly(float dt)
{
	m_fallSpeed = 0;
	Flap(2);
	if		(m_pGame->GetDifficulty() > 4)
		m_yPos+= dt * 180;
	else if (m_pGame->GetDifficulty() > 3)
		m_yPos+= dt * 170;	
	else if (m_pGame->GetDifficulty() > 2)
		m_yPos+= dt * 160;	
	else if (m_pGame->GetDifficulty() >= 1)
		m_yPos+= dt * 150;

	//m_yPos+= dt * (150 + m_pGame->GetDifficulty() * 10);

}

void Player::Glide(float dt)
{
	m_fallSpeed += 400 * dt;
	//m_yPos -= dt * (100 + m_fallSpeed);	

	if		(m_pGame->GetDifficulty() > 4)
		m_yPos -= dt * (130 + m_fallSpeed);
	else if (m_pGame->GetDifficulty() > 3)
		m_yPos -= dt * (120 + m_fallSpeed);
	else if (m_pGame->GetDifficulty() > 2)
		m_yPos -= dt * (110 + m_fallSpeed);
	else if (m_pGame->GetDifficulty() >= 1)
		m_yPos -= dt * (100 + m_fallSpeed);

	m_sprite = m_playerGlide;
	m_counter = 0;
}

void Player::Flip()
{
	m_flipped = 1;
}

void Player::SetMenu(bool inMenu)
{
	m_inMenu = inMenu;
}

void Player::ResetRotation()
{
	m_deathRotation -= m_totalRotation;
	m_fallSpeed = 0;
}
void Player::SetDead(bool dead)
{
	if(!m_dead && dead)
		m_pGame->PlayDeathSound();
	
	m_dead = dead; 
}