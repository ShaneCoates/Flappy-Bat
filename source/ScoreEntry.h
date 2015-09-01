


class ScoreEntry
{
public:
	char m_Name[3];
	int m_Score;

	ScoreEntry();
	ScoreEntry(const char* name, int score);

	~ScoreEntry();
};