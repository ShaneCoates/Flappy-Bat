/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Options State
		Shown if user navigates to it from the options state
		From here the user can adjust the lights:
			- red
			- green		and
			- blue
		values
		as well as setting disco mode to on/off

-------------------------------------------------------------------------------*/

#ifndef LIGHT_OPTION_STATE_H
#define LIGHT_OPTION_STATE_H


class Game;
class ScrollingText;

class LightOptionState
{
public:

	//constructor
	LightOptionState(Game *pGame);

	//destructor
	~LightOptionState();

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
	int m_selectedAlpha[5];
	char buffer[32];
};

#endif