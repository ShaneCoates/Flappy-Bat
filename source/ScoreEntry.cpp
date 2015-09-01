#include "ScoreEntry.h"
#include <cstring>

ScoreEntry::ScoreEntry()
{
	strcpy(m_Name, "AAA");
	m_Score = 0;
}

ScoreEntry::ScoreEntry(const char *name, int score)
{
	strcpy(m_Name, name);
	m_Score = score;
}

ScoreEntry::~ScoreEntry()
{

}