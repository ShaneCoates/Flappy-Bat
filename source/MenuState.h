/*-----------------------------------------------------------------------------
		Author: Shane Coates
		Description: Basic Menu State
		First screen shown after splash state

		will show
			- PLAY
			- OPTIONS
			- HIGH SCORES
			- QUIT

		when the user selects play, the game will start
		when the user selects options, the options state will be shown
		when the user hovers over high scores, the high scores state will be drawn
		when the user selects quit, the game will close

-------------------------------------------------------------------------------*/

#ifndef MENU_STATE_H
#define MENU_STATE_H

class Game;

class MenuState
{
public:

	//constructor
	MenuState(Game *pGame);

	//destructor
	~MenuState();

	void Update(float dt);
	void Draw();

	void CheckUserInput();

	bool IsSelectPressed();
	bool IsDownPressed();
	bool IsUpPressed();

	void Play();
	void Options();
	void HighScores();
	void Quit();

	void SetCooldown(float time);

	int GetSelected()										{return m_selected;}
	void SetSelected(unsigned int selected)					{m_selected = selected;}


protected:

	Game *m_pGame;


private:

	int m_selected;
	int m_selectedAlpha[4];

};

#endif