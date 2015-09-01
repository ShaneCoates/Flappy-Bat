#include "HighScoreState.h"
#include "Game.h"
#include "AIE.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ScoreEntry.h"

using namespace std;

static int HighScoresSelectedCallback(void* userData, int numArgs, char **data, char **columnName);

	//constructor
HighScoreState::HighScoreState(Game *pGame)
{
	// Open database
	sqlite3_open("HighScores.db", &m_HSDatabase);

	m_pGame = pGame;

	CreateDatabase();

	m_tempScore = 0;
	m_placeY = 10;
	m_placeX = 0;
	m_cooldown = 0.5f;
	m_tempName = 'A';
	m_dt = 0;
	m_newScore = 0;
	m_isNew = false;


	for(int i = 0; i < MAX_SCORES; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m_name[j][i] = 'A';
		}
		m_score[i] = (MAX_SCORES-i)*5000;

		m_Scores.push_back(new ScoreEntry("AAA", (MAX_SCORES-i)*5000));
	}

}

//destructor
HighScoreState::~HighScoreState()
{
	sqlite3_close(m_HSDatabase);
}

void HighScoreState::Update(float dt)
{
	m_dt = dt;
	m_cooldown -= dt;

	if(m_pGame->GetGameState() != 1)
		m_pGame->ChangeState(1);

}

void HighScoreState::Draw()
{

	// temp buffer for screen drawing
	char buffer[32];

	// not new entry, display scores

	int scorePosOffset = 0;
	for(auto itr = m_Scores.begin(); itr != m_Scores.end(); ++itr)
	{
		char *name = (*itr)->m_Name;

		for(int j = 0; j < 3; j++)
		{
			sprintf(buffer, "%c", name[j]);						
			DrawString(buffer, 450 + (j*25), m_pGame->GetTextY() + 300 -(scorePosOffset*25));
		}

		sprintf(buffer, "%i", (*itr)->m_Score);
		DrawString(buffer, 550, m_pGame->GetTextY() + 300 -(scorePosOffset*25));
			
		scorePosOffset++;

		if(scorePosOffset == MAX_SCORES)
		{
			break;
		}
	}
}

void HighScoreState::Reset()
{
	m_tempScore = 0;
	m_placeY = 10;
	m_placeX = 0;
	m_cooldown = 0.5f;
	m_tempName = 'A';
	m_dt = 0;
	m_newScore = 0;
	m_isNew = false;
}

void HighScoreState::NewHighScore(int score)
{
	m_placeX = 0;
	m_placeY = 10;

	for(int i = 0; i < 3; i++)
	{
		m_newName[i] = 'A';
	}

	m_tempScore = score;

	if(m_tempScore > (*(m_Scores.end() -1))->m_Score)
	{
		m_isNew = true;
	}

	if(m_isNew)
		m_pGame->ChangeState(5);
}



void HighScoreState::AddScore(ScoreEntry *score)
{
	m_Scores.push_back(score);

	// dodgy n2 sort algorithm from the fiery pits of hell
	for(int j = 0; j < m_Scores.size(); j++) 
	{
		for(int i = 0; i < m_Scores.size(); i++)
		{
			if(i != m_Scores.size() - 1)
			{
				if(m_Scores[i]->m_Score < m_Scores[i + 1]->m_Score)
				{
					ScoreEntry *swappedScore = m_Scores[i];

					m_Scores[i] = m_Scores[i + 1];
					m_Scores[i + 1] = swappedScore;
				}
			}
		}
	}

	SaveScoreToDatabase(score);
}

void HighScoreState::SaveScoreToDatabase(ScoreEntry *score)
{
	string sqlStatement;

	sqlStatement =  "INSERT INTO HIGHSCORES(NAME, SCORE)" \
					"VALUES (?, ?);";
		
	sqlite3_stmt *insertStatement;
	sqlite3_prepare(m_HSDatabase, sqlStatement.c_str(), sqlStatement.length(), &insertStatement, NULL);

	sqlite3_bind_text(insertStatement, 1, score->m_Name, strlen(score->m_Name), SQLITE_TRANSIENT);
	sqlite3_bind_int(insertStatement, 2, score->m_Score);

	int result = sqlite3_step(insertStatement);

	sqlite3_finalize(insertStatement);

	if(result != SQLITE_DONE)
	{
		std::cout << "Holy shit it failed." << std::endl;
		std::cout << sqlite3_errstr(result) << std::endl;
	}	
}

void HighScoreState::CreateDatabase()
{
	char*errorMsg = NULL;
	string sqlStatement;

	sqlStatement = "CREATE TABLE HIGHSCORES (" \
		"NAME	varchar(3)," \
		"SCORE	int);";

	sqlite3_exec(m_HSDatabase, sqlStatement.c_str(), NULL, 0, &errorMsg);
}



void HighScoreState::ReadFromFile()
{
	char*errorMsg = NULL;
	string sqlStatement;

    errorMsg = NULL;
    sqlStatement =  "SELECT NAME, SCORE from HIGHSCORES order by SCORE desc LIMIT 10;";

	for(auto itr = m_Scores.begin(); itr != m_Scores.end(); ++itr)
	{
		delete (*itr);
	}

	m_Scores.clear();

    int result = sqlite3_exec(m_HSDatabase, sqlStatement.c_str(), HighScoresSelectedCallback, this, &errorMsg);

    if(errorMsg != NULL)
    {
        cout << "Error message: " << errorMsg << endl;
    }
}


static int HighScoresSelectedCallback(void* userData, int numArgs, char **data, char **columnName)
{
	HighScoreState *state = reinterpret_cast<HighScoreState *>(userData);

	state->m_Scores.push_back(new ScoreEntry(data[0], atoi(data[1])));

	return 0;
}

void HighScoreState::FillBlankScores()
{
	int ScoresToFill = MAX_SCORES - m_Scores.size();

	for(int i = 0; i < ScoresToFill; i++)
	{
		AddScore(new ScoreEntry("AAA", 5000 * (i+1)));
	}

}