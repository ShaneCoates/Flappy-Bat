/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Sound Options State
		Shown if user navigates to it from the options state
		From here the user can adjust the master volume
		or set mute on/off
		they can also navigate back to the main menu
-------------------------------------------------------------------------------*/

#ifndef SOUND_OPTION_STATE_H
#define SOUND_OPTION_STATE_H


class Game;
class ScrollingText;

class SoundOptionState
{
public:

	//constructor
	SoundOptionState(Game *pGame);

	//destructor
	~SoundOptionState();

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
	int m_selectedAlpha[3];
	char buffer[32];
};

#endif