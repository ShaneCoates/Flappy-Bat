/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Gameplay State
		This is where the game is actually played
		Will draw player to the screen
		Allows user to control player
-------------------------------------------------------------------------------*/

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

class Game;
class Player;
class HighScoreState;
class Background;

class PlayState
{
public:

	//constructor
	PlayState(Game *pGame, HighScoreState *pHighScoreState, Background *pBackground);

	//destructor
	~PlayState();

	void Update(float dt);
	void Draw();
	void Reset();
	void CheckCollisions();

	void IncreaseScore(int score)							{m_score += score;}
	void SetTempDifficulty(int difficulty)					{m_tempDifficulty = difficulty;}
	void SetDead(bool dead);									
	void NewGame(float dt);


	unsigned int GetPlayerY();

protected:

	Game *m_pGame;
	Player *m_Player;
	HighScoreState *m_pHighScoreState;
	Background *m_pBackground;

private:

	unsigned int m_score;

	
	int m_appleTimer;

	int m_wallTimer;

	bool m_newGame;

	int m_tempDifficulty;

};

#endif