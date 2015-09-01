
/*-----------------------------------------------------------------------------
	Author: Shane Coates
	Description: 
	This is the game class, it will encapsulate window management and the main
	game loop...
-----------------------------------------------------------------------------*/



#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>

#include "irrklang.h"

// pre-definition of classes
class SplashState;
class MenuState;
class OptionState;
class LightOptionState;
class SoundOptionState;
class PlayState;
class HighScoreState;
class NewHighScore;
class Background;
class Apple;
class Wall;

class ScrollingText;
class Player;


class Game
{
public:

	//constructor
	Game(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle);

	//destructor
	~Game();

	//returns when the main game loop has finished
	void RunGame();

	void Reset();

	void QuitProgram();

	void ChangeState( int stateID );

	void SetText(std::string text);

	void AddApple();

	void AddWall();

	bool CheckAppleCollision(Apple *pApple);

	bool CheckWallCollision(Wall *pWall);

	void SetDead(bool dead);									



	//GETTERS AND SETTER
	unsigned int GetWindowWidth()							{return m_windowWidth;}

	unsigned int GetWindowHeight()							{return m_windowHeight;}

	unsigned int GetGameState()								{return m_gameState;}
	
	unsigned int GetTextY()									{return 130;}
	
	void SetDifficulty(float difficulty)					{m_difficulty = difficulty;}
	float GetDifficulty()									{return m_difficulty;}
	void IncreaseDifficulty();						

	void IncreaseDifficulty(float increase)					{m_difficulty += increase;}
	void DecreaseDifficulty();									
	
	void SetRed(int red)									{m_red = red;}
	unsigned int GetRed()									{return m_red;}
	void IncreaseRed()										{if(m_red < 255)		m_red++;}
	void DecreaseRed()										{if(m_red > 0)			m_red--;}		

	void SetGreen(int green)								{m_green = green;}
	unsigned int GetGreen()									{return m_green;}
	void IncreaseGreen()									{if(m_green < 255)		m_green++;}
	void DecreaseGreen()									{if(m_green > 0)		m_green--;}		

	void SetBlue(int blue)									{m_blue = blue;}
	unsigned int GetBlue()									{return m_blue;}
	void IncreaseBlue()										{if(m_blue < 255)		m_blue++;}
	void DecreaseBlue()										{if(m_blue > 0)			m_blue--;}		

	void SetVolume(float volume)							{m_masterVolume = volume;}
	unsigned int GetVolume()								{return m_masterVolume * 100;}
	void IncreaseVolume()									{if(m_masterVolume < 1.0f)		m_masterVolume+= 0.01f;}
	void DecreaseVolume()									{if(m_masterVolume > 0)			m_masterVolume-= 0.01f;}		

	void SetCooldown(float time)							{m_inputCooldown = time;}
	float GetCooldown()										{return m_inputCooldown;}

	void SetInGame(bool inGame)								{m_inGame = inGame;}
	bool GetInGame()										{return m_inGame;}

	void SetDisco(bool disco)								{m_disco = disco; SetCooldown(0.1f);}
	bool GetDisco()											{return m_disco;}

	void SetMute(bool mute)									{m_mute = mute; SetCooldown(0.1f);}
	bool GetMute()											{return m_mute;}

	void SetLastWall(int last);

	void PlayFlapSound();

	void PlayDeathSound();

	void PlayCoinSound();

	bool GetNewLight();		

	void IncreaseScore(int score);


private:

	//called each frame from within RunGame()
	void Update();

	//called each frame from within RunGame()
	void Draw();

private:

		unsigned int			m_windowWidth;
		unsigned int			m_windowHeight;

		bool					m_inGame;

		unsigned int			m_gameState;
		unsigned int			m_red;
		unsigned int			m_green;
		unsigned int			m_blue;

		float					m_inputCooldown;
		float					m_difficulty;
		bool					m_gameOver;
		bool					m_disco;

		float					m_masterVolume;
		bool					m_mute;

		SplashState				*m_splashState;
		MenuState				*m_menuState;
		OptionState				*m_optionState;
		LightOptionState		*m_lightOptions;
		SoundOptionState		*m_soundOptions;
		PlayState				*m_playState;
		HighScoreState			*m_highScoreState;
		NewHighScore			*m_newHighScore;
		Background				*m_background;

		ScrollingText			*m_scrollingText;
		Player					*m_player;

		irrklang::ISoundEngine	*m_audioEngine;

	//TODO: place game related variables here
	//TODO: place game related functions here

};


#endif