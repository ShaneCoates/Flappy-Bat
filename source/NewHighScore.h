
/*-----------------------------------------------------------------------------
	Author: Shane Coates
	Description: New High Score State
	Will be drawn when the player makes a new high score
	Will allow the use to set their name
	
-----------------------------------------------------------------------------*/

#ifndef NEW_HIGH_SCORE_H
#define	NEW_HIGH_SCORE_H

class Game;
class ScoreEntry;
class HighScoreState;

class NewHighScore
{

public:

	NewHighScore(Game *pGame, HighScoreState *pHighScoreState);

	~NewHighScore();

	void Update(float dt);

	void Draw();

	void Reset();

	void CheckUserInput();

	void NewScore(int score);

protected:
private:

	Game *m_pGame;
	HighScoreState *m_pHighScoreState;

	float m_dt;

	unsigned int m_textAlpha[4];
	unsigned int m_place;

	char buffer[32];
	char m_name[3];
	int m_score;
	int m_tempScore;
};

#endif