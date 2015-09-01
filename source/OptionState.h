/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Options State
		Shown if user navigates to it from the menu state
		From here the user can adjust the games:
			- difficulty
		or navigate to the
			- lights options state	or
			- sound options state

-------------------------------------------------------------------------------*/

#ifndef OPTION_STATE_H
#define OPTION_STATE_H


class Game;
class ScrollingText;

class OptionState
{
public:

	//constructor
	OptionState(Game *pGame);

	//destructor
	~OptionState();

	void Update(float dt);
	void Draw();

	void CheckUserInput();

	bool IsSelectPressed();
	bool IsDownPressed();
	bool IsUpPressed();
	bool IsLeftPressed();
	bool IsRightPressed();

	bool IsSavePressed();
	bool IsLoadPressed();

	void SaveSettings();
	void LoadSettings();
	
	void SetCooldown(float time);

	int GetSelected()		{return m_selected;}



protected:

	Game *m_pGame;

private:
	
	int m_selected;
	int m_selectedAlpha[4];
	char buffer[32];
};

#endif