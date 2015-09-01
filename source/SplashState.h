/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Splash State
		Splash state shown before the user enters the menu screen
		Will display the title of the game
		Will close after 3 seconds or on keypress
-------------------------------------------------------------------------------*/

#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

class Game;

class SplashState
{
public:

	//constructor
	SplashState( Game *pGame);
	
	//destructor
	~SplashState();

	void Update(float dt);
	void Draw();

protected:

	float m_time;

	Game *m_pGame;

private:

	unsigned int m_splashImage;

};


#endif