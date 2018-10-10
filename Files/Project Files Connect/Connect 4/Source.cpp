
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<iostream>
using namespace sf;
using namespace std;
CircleShape circles[6][7];
CircleShape player1;
CircleShape player2;
char place[6][7];
bool check(int a, int b);
int drop(int b, char player);

Font myfont;
Text mytext;
int main()
{
	RenderWindow window(VideoMode(1350, 900), "Connect Four=)", Style::Close | Style::Resize |Style::Fullscreen);
	Font font;
	font.loadFromFile("OpenSans-Bold.ttf");
	Text Instructions;
	Instructions.setFont(font);
	Instructions.setCharacterSize(20);
	Instructions.setFillColor(Color::White);
	Instructions.setPosition(0, 0);
	Instructions.setString("Press Esc to exit , press Enter to exit Fullscreen ");

	int counter = 0;
	//button start
	RectangleShape button(Vector2f(650.0f, 100.0f));
	button.setFillColor(Color::White);
	button.setPosition(380, 590);
	Text tstr;
	Font fontstr;
	fontstr.loadFromFile("OpenSans-Bold.ttf");
	tstr.setFont(fontstr);
	tstr.setCharacterSize(65);
	tstr.setFillColor(Color::Blue);
	tstr.setPosition(430, 600);
	tstr.setString("START THE GAME");
 
	//button game
	RectangleShape button2(Vector2f(500.0f, 45.0f));
	button2.setFillColor(Color::White);
	button2.setPosition(425, 710);
	Text tgame;
	Font fontgame;
	fontgame.loadFromFile("OpenSans-Bold.ttf");
	tgame.setFont(fontgame);
	tgame.setCharacterSize(40);
	tgame.setFillColor(Color::Blue);
	tgame.setPosition(500, 710);
	tgame.setString("Back to the games");
 
	//background
	Texture background;
	Sprite sp;
	background.loadFromFile("7.png");
	background.setSmooth(true);
	sp.setTexture(background);
	sp.setPosition(0, 0);
	bool Full = true;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Key::Escape)))
			{
				window.close();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Return))
			{
				if (Full)
				{

					window.create(VideoMode(1150, 700), "Connect Four=)", Style::Close | Style::Resize );

					Full = false;

				}
				else
				{
					window.create(VideoMode(1350, 900), "Connect Four=)", Style::Fullscreen);
					Full = true;
				}

			}
			if (Mouse::isButtonPressed(Mouse::Right))
			{
				  
				Vector2i mouseClick = Mouse::getPosition(window);
				
				pair<int, int> button1 = { mouseClick.x, mouseClick.y };

				if ( button1.first >= 379 && button1.second >= 590 && button1.first <= (1030) && button1.second <= (685))
				{
					counter=1;
					
				}
				else if (button1.first >= 430 && button1.second >= 709 && button1.first <= (920) && button1.second <= (750))
				{
					
					counter=2;
				}
			}
		}
		if (counter == 0)
		{
			window.clear();
			window.draw(sp);
			window.draw(button);
			window.draw(button2);
			window.draw(tstr);
			window.draw(tgame);
			window.draw(Instructions);
			window.display();
			
		}
		else if (counter == 1)
		{
			//Size&prop.of window
			 window.create(VideoMode(1350, 900), "Connect Four=)", Style::Close | Style::Resize | Style::Fullscreen);
			//Shape and dimension and the color and position
			RectangleShape MainBoard(Vector2f(840.0f, 715.0f));
				for (int a = 0; a <= 5; a++) {		//fill place with whitespace
					for (int b = 0; b <= 6; b++)
						place[a][b] = ' ';
				}
				MainBoard.setPosition(0, 100);
				MainBoard.setFillColor(Color::Blue);

				Font font1;
				font1.loadFromFile("Italic.ttf");
				Text t1, t2;
				t1.setFont(font1);
				t1.setCharacterSize(70);
				t1.setFillColor(Color::Green);
				t1.setPosition(950, 50);
				t1.setString("Player ONE");

				t2.setFont(font1);
				t2.setCharacterSize(70);
				t2.setFillColor(Color::Red);
				t2.setPosition(950, 120);
				t2.setString("Player TWO");


				Font font;
				font.loadFromFile("OpenSans-Bold.ttf");
				Text text;
				text.setFont(font);
				text.setCharacterSize(50);
				text.setFillColor(Color::Magenta);
				text.setPosition(20, 20);
				text.setString("  1       2       3       4       5       6       7");

				
				int col = 15;
				for (int c = 0; c < 7; c++)
				{
					int row = 700;
					for (int r = 0; r < 6; r++)
					{
						circles[r][c].setRadius(50);
						circles[r][c].setPosition(col, row);
						circles[r][c].setFillColor(Color::Black);
						row -= 115;
					}
					col += 115;
				}
				int hold = 0;//Will house user row choice
				int hold2 = -1;//will hold drop value
				int charsPlaced = 0;//Number of peices dropped so can end game if a draw
				bool gamewon = false;//Will be changed to true when game is won and will exit while loop
				char player = 15;//start as player 2 will change back 2 player 1
				bool isFullscreen = true;
				//Loop for displaying
				while (window.isOpen())
				{//will stop when game is won, ! means NOT makes the oppisite be checked

					Event event;

					while (!gamewon)
					{
						hold = 0;
						if (charsPlaced == 42) break;//if draw

													 //Loop for check every event if it'll close or not
						while (window.pollEvent(event))
						{
							if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								window.close();

							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{
								if (isFullscreen)
								{

									window.create(VideoMode(1350, 900), "Connect Four=)", Style::Close | Style::Resize | Style::Titlebar);
									isFullscreen = false;

								}
								else
								{
									window.create(VideoMode(1350, 900), "Connect Four=)", Style::Fullscreen);
									isFullscreen = true;
								}

							}
							

							if (Keyboard::isKeyPressed(Keyboard::Key::Num1) && hold != -1)
							{
								hold = 0;
								hold2 = drop(hold, player);//drop the player store the row in hold2
								if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
								else {
									gamewon = check(hold2, hold);//check if game is run
									charsPlaced++;//another character has been succesfully placed
								}

								if (hold2 != -1) {//check if there was a error in the last drop
									if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn
										cout << "player 1 : Choose a colomn to drop in: ";
										player = 254;//char of players piece
									}
									else {
										cout << "player 2 : Choose a colomn to drop in: ";
										player = 15;//char of player piece
									}
								}
								hold = -1;
							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Num2) && hold != -1)
							{
								hold = 1;
								hold2 = drop(hold, player);//drop the player store the row in hold2
								if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
								else {
									gamewon = check(hold2, hold);//check if game is run
									charsPlaced++;//another character has been succesfully placed
								}
								if (hold2 != -1) {//check if there was a error in the last drop
									if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn
										cout << "player 1 : Choose a colomn to drop in: ";
										player = 254;//char of players piece
									}
									else {
										cout << "player 2 : Choose a colomn to drop in: ";
										player = 15;//char of player piece
									}
								}
								hold = -1;
							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Num3) && hold != -1)
							{
								hold = 2;
								hold2 = drop(hold, player);//drop the player store the row in hold2
								if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
								else {
									gamewon = check(hold2, hold);//check if game is run
									charsPlaced++;//another character has been succesfully placed
								}
								if (hold2 != -1) {//check if there was a error in the last drop
									if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn
										cout << "player 1 : Choose a colomn to drop in: ";
										player = 254;//char of players piece
									}
									else {
										cout << "player 2 : Choose a colomn to drop in: ";
										player = 15;//char of player piece
									}
								}
								hold = -1;
							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Num4) && hold != -1)
							{
								hold = 3;
								hold2 = drop(hold, player);//drop the player store the row in hold2
								if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
								else {
									gamewon = check(hold2, hold);//check if game is run
									charsPlaced++;//another character has been succesfully placed
								}
								if (hold2 != -1) {//check if there was a error in the last drop
									if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn
										cout << "player 1 : Choose a colomn to drop in: ";
										player = 254;//char of players piece
									}
									else {
										cout << "player 2 : Choose a colomn to drop in: ";
										player = 15;//char of player piece
									}
								}
								hold = -1;
							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Num5) && hold != -1)
							{
								hold = 4;
								hold2 = drop(hold, player);//drop the player store the row in hold2
								if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
								else {
									gamewon = check(hold2, hold);//check if game is run
									charsPlaced++;//another character has been succesfully placed
								}
								if (hold2 != -1) {//check if there was a error in the last drop
									if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn
										cout << "player 1 : Choose a colomn to drop in: ";
										player = 254;//char of players piece
									}
									else {
										cout << "player 2 : Choose a colomn to drop in: ";
										player = 15;//char of player piece
									}
								}
								hold = -1;
							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Num6) && hold != -1)
							{
								hold = 5;
								hold2 = drop(hold, player);//drop the player store the row in hold2
								if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
								else {
									gamewon = check(hold2, hold);//check if game is run
									charsPlaced++;//another character has been succesfully placed
								}
								if (hold2 != -1) {//check if there was a error in the last drop
									if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn
										cout << "player 1 : Choose a colomn to drop in: ";
										player = 254;//char of players piece
									}
									else {
										cout << "player 2 : Choose a colomn to drop in: ";
										player = 15;//char of player piece
									}
								}
								hold = -1;
							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Num7) && hold != -1)
							{
								hold = 6;
								hold2 = drop(hold, player);//drop the player store the row in hold2
								if (hold2 == -1)	cout << "Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
								else {
									gamewon = check(hold2, hold);//check if game is run
									charsPlaced++;//another character has been succesfully placed
								}
								if (hold2 != -1) {//check if there was a error in the last drop
									if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn
										cout << "player 1 : Choose a colomn to drop in: ";
										player = 254;//char of players piece
									}
									else {
										cout << "player 2 : Choose a colomn to drop in: ";
										player = 15;//char of player piece
									}
								}
								hold = -1;
							}
							//}
						}

						window.display();
						window.draw(player2);
						window.draw(player1);
						window.draw(text);
						window.draw(MainBoard);
						window.draw(t1);
						window.draw(t2);
						window.draw(Instructions);
						int col = 15;
						for (int c = 0; c < 7; c++)
						{
							int row = 700;
							for (int r = 0; r < 6; r++)
							{

								window.draw(circles[r][c]);
								row -= 115;
							}
							col += 115;
						}

					}

					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape))
						{
							window.close();
						}

					}
					if (charsPlaced == 42 && !gamewon) {//if draw
						Texture textre;
						Sprite sp;
						textre.loadFromFile("drawn.png");
						sp.setTexture(textre);
						sp.setPosition(850, 450);
						window.display();
						window.draw(sp);
						window.draw(Instructions);

					}
					else
					{
						if (player == 15)//if won by player 2
						{
							Texture textre;
							Sprite sp;
							textre.loadFromFile("player2.jpg");
							sp.setTexture(textre);
							sp.setPosition(830, 350);
							window.display();
							window.draw(sp);
							window.draw(Instructions);

						}
						else
						{
							Texture textre;
							Sprite sp;
							textre.loadFromFile("player1.png");
							sp.setTexture(textre);
							sp.setPosition(830, 350);
							window.display();
							window.draw(sp);
							window.draw(Instructions);

						}
					}

				}
				return 0;			
			
		}
		else if (counter=2)
		{
			// the main window for all games 
		}
	}
 
	return 0;
}
int drop(int b, char player)
{
	if (place[0][b] == ' ') {
		int i;
		int j;
		for (i = 0; place[i][b] == ' '; i++)
			if (i == 5) {
				j = 0;
				place[i][b] = player;
				if (player == 15)
				{
					circles[j][b].setFillColor(Color::Green);
				}
				else
				{
					circles[j][b].setFillColor(Color::Red);
				}
				return i;
			}
		i--;
		place[i][b] = player;
		if (i == 4) {
			j = 1;
			place[i][b] = player;
			if (player == 15)
			{
				circles[j][b].setFillColor(Color::Green);
			}
			else
			{
				circles[j][b].setFillColor(Color::Red);
			}
			return i;
		}
		else if (i == 3) {
			j = 2;
			place[i][b] = player;
			if (player == 15)
			{
				circles[j][b].setFillColor(Color::Green);
			}
			else
			{
				circles[j][b].setFillColor(Color::Red);
			}
			return i;
		}
		else if (i == 2) {
			j = 3;
			place[i][b] = player;
			if (player == 15)
			{
				circles[j][b].setFillColor(Color::Green);
			}
			else
			{
				circles[j][b].setFillColor(Color::Red);
			}
			return i;
		}
		if (i == 1) {
			j = 4;
			place[i][b] = player;
			if (player == 15)
			{
				circles[j][b].setFillColor(Color::Green);
			}
			else
			{
				circles[j][b].setFillColor(Color::Red);
			}
			return i;
		}
		if (i == 0) {
			j = 5;
			place[i][b] = player;
			if (player == 15)
			{
				circles[j][b].setFillColor(Color::Green);
			}
			else
			{
				circles[j][b].setFillColor(Color::Red);
			}
			return i;
		}
		return i;
	}
	else {
		return -1;
	}

}
bool check(int a, int b) {
	int vertical = 1;//(|)
	int horizontal = 1;//(-)
	int diagonal1 = 1;//(\)
	int diagonal2 = 1;//(/)
	char player = place[a][b];
	int i;//vertical
	int ii;//horizontal
		   //check for vertical(|)
	for (i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);//Check down
	for (i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);//Check up
	if (vertical >= 4)return true;
	//check for horizontal(-)
	for (ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);//Check left
	for (ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);//Check right
	if (horizontal >= 4) return true;
	//check for diagonal 1 (\)
	for (i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);//up and left
	for (i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);//down and right
	if (diagonal1 >= 4) return true;
	//check for diagonal 2(/)
	for (i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);//up and right
	for (i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);//up and left
	if (diagonal2 >= 4) return true;
	return false;
}
