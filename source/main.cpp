
#include "AIE.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>

const int iScreenWidth = 1280;
const int iScreenHeight = 720;

int main( int argc, char* argv[] )
{	

	srand((unsigned int)time(NULL));

	Game *pGame = new Game(iScreenWidth, iScreenHeight, "Flappy Bat");

	pGame->RunGame();

	delete pGame;

	return 0;
}

