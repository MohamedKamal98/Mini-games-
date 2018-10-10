#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <time.h>
#include <vector>
#include <algorithm>
#include "SnakeAndLadder.h"
#include "Welcome.h"
#include "ConnectFour.h"
#include "MineSweeper.h"

int main()
{
	SNAKE_LADDER::setFontAndTextAndbackground();
	SNAKE_LADDER::text_style(SNAKE_LADDER::playerText_y, SNAKE_LADDER::players_y, SNAKE_LADDER::playerinfo_y);

	int gameNumber;

	while (gameNumber = WELCOME::welcome())
	{
		switch (gameNumber)
		{
		case 1:
			SNAKE_LADDER::snakeAndLadder();
			break;
		case 2:
			MINE_SWEEPER::mineSweeper();
			break;
		case 3:
			CONNECT_FOUR::connectFour();
			break;
		}
	}

	return 0;
}