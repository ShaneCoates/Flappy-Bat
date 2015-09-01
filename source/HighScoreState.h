/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic High Score State
		Shown after the player dies	or
		if user chooses to navigate here from menu state
		Shows top 10 high scores
		lists them by score
		shows name and score

-------------------------------------------------------------------------------*/




#ifndef HIGH_SCORE_STATE_H
#define HIGH_SCORE_STATE_H

#include <vector>
#include "sqlite3.h"

class Game;
class ScoreEntry;
class HighScoreState
{
public:

	//constructor
	HighScoreState(Game *pGame);

	//destructor
	~HighScoreState();

	void Update(float dt);
	void Draw();
	void Reset();
	void NewHighScore(int score);

	void CreateDatabase();
	void FillBlankScores();
	void ReadFromFile();

	unsigned int GetScore()					{return m_tempScore;}

	int m_score[10];
	char m_name[3][10];
	std::vector<ScoreEntry *> m_Scores;

	void SetScoreName(int scoreIndex, char first, char second, char third);
	void SetScore(int scoreIndex, int score);
	void SetIsNew(bool isNew)				{m_isNew = isNew;}
	bool GetIsNew()							{return m_isNew;}

	void AddScore(ScoreEntry *score);
	void SaveScoreToDatabase(ScoreEntry *score);

	int m_newScore;


protected:

	Game *m_pGame;



private:

	int m_tempScore;
	char m_tempName;
	int m_placeY;
	int m_placeX;
	float m_cooldown;
	char m_newName[3];
	int m_textAlpha[3];
	float m_dt;
	bool m_isNew;

	static const int MAX_SCORES = 10;

	sqlite3 *m_HSDatabase;

};

#endif