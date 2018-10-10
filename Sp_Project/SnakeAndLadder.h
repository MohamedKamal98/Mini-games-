#pragma once

using namespace std;
using namespace sf;


namespace SNAKE_LADDER
{
	//the map connecting score to x , y indecies
	map <int, pair<int, int> > scoreAndIndicies;
	//map containing scores which have snakes and scores which have ladders and the score the player'll go to  
	map<int, int>snake, ladder;
	//map for checking if the score has a ladder or snake 
	map <int, bool> isTaken;

	//dice's random number
	int dicePicNumber = rand() % 6;
	//this variable is for animating the dice if the space key is pressed it wil be set to zero and the dice will change its texture till this variable is 100 and then it stops
	int numberOfRolling = 200;
	int lastRoll = 0;
	//size of the grid and maximum number of players
	const int SIZE = 10, np = 5;
	//width of each square of the grid
	float SQUAREX = 80.0f;
	//height of each square of the grid
	float SQUAREY = 80.0f;
	//width of the dice
	float DICEX = 100.0f;
	//height of the dice
	float DICEY = 100.0f;
	//variable for generating snakes and laddders
	int score1 = 0, score2 = 0;
	//maximum score of players
	int maxScore = 0;
	//this contains x and y indecies of the square the player should go to after rolling the dice
	float destination[5][2];
	//indexOfWinner
	int indexOfWinner = -1;
	//counter of forms
	int formCounter = 0;
	//speed of players
	float speed = 0.5;
	//variables for sprite animation
	int currentTimeX = 0;
	int lastTimeX = 0;
	int currentTimeY = 0;
	int lastTimeY = 0;
	int changingSpriteTextureDif = 30;
	//getting player' names variabes
	int number_of_players_y = 0;
	int i_y = 1;
	string playerInput_y;
	Font font_y;
	Text playerText_y[5], players_y[5], playerinfo_y;


	//window for getting the number of player
	RenderWindow snakeAndLadderWindow;
	//background texture
	Texture backgroundTexture;
	//background rectangle shape
	RectangleShape backgroundRec;
	//on game bacground
	Texture gameBacgroundTexture;
	//size of each square
	Vector2f sizeOfSquare = Vector2f(SQUAREX, SQUAREY);
	//the squares of the grid
	RectangleShape squares[SIZE][SIZE];
	//the dice
	RectangleShape dice(Vector2f(DICEX, DICEY));
	//texture which holds the picutre of numbers(score) of each square
	Texture cellTexture[100];
	//string variable for getting the texture from the path
	string numberOfCell;
	//texture for faces of the dice
	Texture diceTexture[6];
	//texture for the players
	Texture spriteTexture[5];
	//the players 
	Sprite sprites[np];
	//size of the texture of players
	Vector2f spriteTextureSize;
	//snake texture 
	Texture snakeTexture[16];
	//the sankes
	Sprite snakeSprite[16];
	//ladder texture
	Texture ladderTexture[8];
	//ladder sprite
	Sprite ladderSprite[16];
	//audio buffer for loading file for dice
	SoundBuffer diceSoundBuffer;
	//Sound object for dice
	Sound diceSound;
	//screaming sound for running into snake
	SoundBuffer findingSnakeBuffer;
	//screamning object
	Sound findingSnakeSound;
	//screaming sound for finding ladder
	SoundBuffer findingLadderBuffer;
	//founding ladder sound object
	Sound findingLadderSound;
	//Texts and Fonts
	Text text1, text[10];
	Text backToGames;
	Text newGame;
	Text BackToGamesFromInside;
	Text playerText[np];
	Text winningText;
	Text winnerName;
	Font font;
	Font font2;
	Text playerTurn;

	//data of players
	struct player {
		int score = 1;
		string name;
		Color color;
	}players[np];

	//setting font , text , background Image
	void setFontAndTextAndbackground();
	/*here each score is connect with another score and put into a snake or ladder*/
	void connectScores(map <int, int> &SnakeandLadder, char type);
	//creation of the grid
	void createGrid();
	//just displaying the grid
	void drawGrid();
	//getting dice textures(picture) from its path
	void createDice();
	//rolling dice if the counter is less than 100 or it will stay as it is
	void rollDice();
	//displaying current scores of players
	void playTurns(int);
	//updating player's score
	void gameplay(int, int, int);
	//checking if current score contains snake or ladder
	void checkPosition(int, int);
	//creating players
	void createSprite();
	//just displaying the players
	void drawSprite(int);
	//setting players' names
	void getPlayers(int);
	//creating snakes
	void createSnakes();
	//creating snakes
	void createLadder();
	//displaying ladders
	void drawLadders();
	//displaying snakes
	void drawSnakes();
	//launghing game
	void begin(int numberOfPlayers, int level);
	//getting playerNames
	int getplayer_name(int, Event, int&);

	//setting fonts and texts for getting names
	void text_style(Text playerTexts[], Text player[], Text& playerinfor);

	//drawing getting name texts
	void draw_names(Text playertexts[], Text playerss[], Text playerinfor , int);

	void snakeAndLadder()
	{
		//creating window
		snakeAndLadderWindow.create(VideoMode(1800, 910), "Snake And Ladder", Style::Close);
		srand(time(NULL));
		int playerCounter = 0;
		//used for animating dice and players
		bool diceIsRolled = 0;
		//counter for changing texture pictures
		int numberOfPlayers = 1;
		int spriteTextureCounter = 0;
		int level = 1;
		snakeAndLadderWindow.setKeyRepeatEnabled(false);
		bool start = 1;
		formCounter = 0;
		backgroundRec.setTexture(&backgroundTexture);
		number_of_players_y = 0;
		i_y = 1;
		playerInput_y = "";
		playerinfo_y.setString("");
		for (int i = 0; i < np; i++)
			playerText_y[i].setString("");



		while (snakeAndLadderWindow.isOpen())
		{
			//checking for events
			Event event;
			while (snakeAndLadderWindow.pollEvent(event))
			{
				switch (event.type)
				{
					//if close button was clicked
				case Event::Closed:
					snakeAndLadderWindow.close();
				case Event::KeyPressed:
					if (formCounter == 0)
					{
						if (Keyboard::isKeyPressed(Keyboard::S))
							formCounter++;
						if (Keyboard::isKeyPressed(Keyboard::B))
						{
							number_of_players_y = 0;
							i_y = 1;
							playerInput_y = "";
							playerinfo_y.setString("");
							for (int i = 0; i < np; i++)
								playerText_y[i].setString("");
							snakeAndLadderWindow.close();
							return;
						}
					}
					else if (formCounter == 1)
					{
						if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1))
						{
							numberOfPlayers = 1;
							formCounter++;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2))
						{
							numberOfPlayers = 2;
							formCounter++;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3))
						{
							numberOfPlayers = 3;
							formCounter++;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4))
						{
							numberOfPlayers = 4;
							formCounter++;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5))
						{
							numberOfPlayers = 5;
							formCounter++;
						}
						else
						{
							cout << "Wrong Number\n";
						}
					}
					/*else if (formCounter == 2)
					{
						if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1))
						{
							level = 1;
							begin(numberOfPlayers, level);
							playerCounter = 0;
							formCounter++;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2))
						{
							level = 2;
							begin(numberOfPlayers, level);
							playerCounter = 0;
							formCounter++;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3))
						{
							level = 3;
							begin(numberOfPlayers, level);
							playerCounter = 0;
							formCounter++;
						}
						else
						{
							cout << "Wrong Number\n";
						}

					}*/
					else if (formCounter == 3)
					{
						if (Keyboard::isKeyPressed(Keyboard::N))
						{
							formCounter = 1;
							snake.clear();
							ladder.clear();
							for (int i = 0; i < np; i++)
							{
								players[i].score = 1;
							}
							maxScore = 0;
							numberOfPlayers = 0;
							playerCounter = 0;
							numberOfRolling = 200;
							start = 1;
							backgroundRec.setTexture(&backgroundTexture);
							number_of_players_y = 0;
							i_y = 1;
							playerInput_y = "";
							playerinfo_y.setString("");
							for (int i = 0; i < np; i++)
								playerText_y[i].setString("");
						}
						else if (Keyboard::isKeyPressed(Keyboard::B))
						{
							snakeAndLadderWindow.close();
							return ;
						}
						else if (Keyboard::isKeyPressed(Keyboard::Space))
						{
							start = 0;
							if (!diceIsRolled)
							{
								diceSound.play();
								lastRoll = 0;
								numberOfRolling = 0;
								currentTimeX = lastTimeX = currentTimeY = lastTimeY = 0;
							}
						}
					}
					else if (formCounter == 4)
					{
						if (Keyboard::isKeyPressed(Keyboard::N))
						{
							formCounter = 1;
							snake.clear();
							ladder.clear();
							for (int i = 0; i < np; i++)
							{
								players[i].score = 1;
							}
							maxScore = 0;
							numberOfPlayers = 0;
							playerCounter = 0;
							numberOfRolling = 200;
							start = 1;
							number_of_players_y = 0;
							i_y = 1;
							playerInput_y = "";
							playerinfo_y.setString("");
							for (int i = 0; i < np; i++)
								playerText_y[i].setString("");
						}
						else if (Keyboard::isKeyPressed(Keyboard::B))
						{
							snakeAndLadderWindow.close();
							number_of_players_y = 0;
							i_y = 1;
							playerInput_y = "";
							playerinfo_y.setString("");
							for (int i = 0; i < np; i++)
								playerText_y[i].setString("");
							return;
						}
					}
					break;
				}
				if (formCounter == 2)
				{
					if (number_of_players_y == numberOfPlayers)
					{
						begin(numberOfPlayers, level);
						playerCounter = 0;
						formCounter++;
					}
					else
					{
						number_of_players_y = getplayer_name(number_of_players_y, event, i_y);
					}
				}
			}

			snakeAndLadderWindow.clear();
			snakeAndLadderWindow.draw(backgroundRec);

			if (formCounter == 0)
			{
				snakeAndLadderWindow.draw(text1);
				snakeAndLadderWindow.draw(backToGames);
			}
			else if (formCounter == 1)
			{
				snakeAndLadderWindow.draw(text[0]);
				snakeAndLadderWindow.draw(text[1]);
				snakeAndLadderWindow.draw(text[2]);
				snakeAndLadderWindow.draw(text[3]);
				snakeAndLadderWindow.draw(text[4]);
				snakeAndLadderWindow.draw(text[5]);
			}
			else if (formCounter == 2)
			{
				/*snakeAndLadderWindow.draw(text[6]);
				snakeAndLadderWindow.draw(text[7]);
				snakeAndLadderWindow.draw(text[8]);
				snakeAndLadderWindow.draw(text[9]);*/
				draw_names(playerText_y, players_y, playerinfo_y , numberOfPlayers);
				snakeAndLadderWindow.draw(playerinfo_y);
			}
			else if (formCounter == 3)
			{
				if (start)
				{
					playerCounter = 0;
				}
				if (numberOfRolling == 100)
				{
					//getting new score for current player
					gameplay(playerCounter, dicePicNumber + 1, numberOfPlayers);
					//making the dice rolled
					diceIsRolled = 1;
					//updating this
					numberOfRolling = 200;
				}

				//checking if the current positiong of player equals its destination
				if (sprites[playerCounter].getPosition().x == destination[playerCounter][0] && sprites[playerCounter].getPosition().y == destination[playerCounter][1] && diceIsRolled)
				{
					//checking if there is ladder or snake at current position and updating destination
					checkPosition(playerCounter, numberOfPlayers);
					//checking if the current positiong of player equals its destination
					if (sprites[playerCounter].getPosition().x == destination[playerCounter][0] && sprites[playerCounter].getPosition().y == destination[playerCounter][1])
					{
						//moving to next player
						playerCounter++;
						//checking if current number exceeded the number of players and restting it
						if (playerCounter == numberOfPlayers)
						{
							playerCounter = 0;
						}
						//makeing dice unrolled
						diceIsRolled = 0;
						spriteTextureCounter = 0;
						speed = 0.5;
					}
				}
				else
				{
					//moving player to the right
					if (sprites[playerCounter].getPosition().x < destination[playerCounter][0])
					{
						//moving at speed .5 to right
						sprites[playerCounter].move(speed, 0);
						//updating texture for animation
						if (currentTimeX - lastTimeX >= changingSpriteTextureDif || spriteTextureCounter == 0)
						{
							sprites[playerCounter].setTextureRect(IntRect(spriteTextureCounter * spriteTextureSize.x / 9, 3 * spriteTextureSize.y / 4, spriteTextureSize.x / 9, spriteTextureSize.y / 4));
							lastTimeX = currentTimeX;
							spriteTextureCounter++;
							if (spriteTextureCounter == 8)
							{
								spriteTextureCounter = 0;
							}
						}
					}
					//moving player to the left
					else if (sprites[playerCounter].getPosition().x > destination[playerCounter][0])
					{
						//moving at speed .5 to left
						sprites[playerCounter].move(-speed, 0);
						//updating texture for animation
						if (currentTimeX - lastTimeX >= changingSpriteTextureDif || spriteTextureCounter == 0)
						{
							sprites[playerCounter].setTextureRect(IntRect(spriteTextureCounter * spriteTextureSize.x / 9, spriteTextureSize.y / 4, spriteTextureSize.x / 9, spriteTextureSize.y / 4));
							lastTimeX = currentTimeX;
							spriteTextureCounter++;
							if (spriteTextureCounter == 8)
							{
								spriteTextureCounter = 0;
							}
						}
					}
					//moving player up
					if (sprites[playerCounter].getPosition().y < destination[playerCounter][1])
					{
						//moving at speed .5 up 
						sprites[playerCounter].move(0, speed);
						//updating texture for animation
						if (currentTimeY - lastTimeY >= changingSpriteTextureDif || spriteTextureCounter == 0)
						{
							sprites[playerCounter].setTextureRect(IntRect(spriteTextureCounter * spriteTextureSize.x / 9, 2 * spriteTextureSize.y / 4, spriteTextureSize.x / 9, spriteTextureSize.y / 4));
							lastTimeY = currentTimeY;
							spriteTextureCounter++;
							if (spriteTextureCounter == 8)
							{
								spriteTextureCounter = 0;
							}
						}
					}
					//moving player down
					else if (sprites[playerCounter].getPosition().y > destination[playerCounter][1])
					{
						//moving at speed .5 down
						sprites[playerCounter].move(0, -speed);
						//updating texture for animation
						if (currentTimeY - lastTimeY >= changingSpriteTextureDif || spriteTextureCounter == 0)
						{
							sprites[playerCounter].setTextureRect(IntRect(spriteTextureCounter * spriteTextureSize.x / 9, 0, spriteTextureSize.x / 9, spriteTextureSize.y / 4));
							lastTimeY = currentTimeY;
							spriteTextureCounter++;
							if (spriteTextureCounter == 8)
							{
								spriteTextureCounter = 0;
							}
						}
					}
					currentTimeX++;
					currentTimeY++;
				}

				if (maxScore == 100)
				{
					//checking if the winner went to 100
					winnerName.setString(players[indexOfWinner].name);
					if (sprites[indexOfWinner].getPosition().x == destination[indexOfWinner][0] && sprites[indexOfWinner].getPosition().y == destination[indexOfWinner][1])
					{
						formCounter++;
						maxScore = 1000;
					}
				}
				rollDice();
				for (int i = 0; i < numberOfPlayers; i++)
				{
					snakeAndLadderWindow.draw(playerText[i]);
				}
				playerTurn.setString(players[playerCounter].name + "'s Turn \t\t press space to play");
				playerTurn.setFillColor(players[playerCounter].color);
				drawGrid();
				drawSnakes();
				drawLadders();
				drawSprite(numberOfPlayers);
				snakeAndLadderWindow.draw(newGame);
				snakeAndLadderWindow.draw(BackToGamesFromInside);
				snakeAndLadderWindow.draw(playerTurn);
			}
			else if (formCounter == 4)
			{
				drawGrid();
				for (int i = 0; i < numberOfPlayers; i++)
					snakeAndLadderWindow.draw(playerText[i]);
				drawSnakes();
				rollDice();
				drawLadders();
				snakeAndLadderWindow.draw(winningText);
				snakeAndLadderWindow.draw(winnerName);
				drawSprite(numberOfPlayers);
				snakeAndLadderWindow.draw(newGame);
				snakeAndLadderWindow.draw(BackToGamesFromInside);
			}
			snakeAndLadderWindow.display();
		}

		return ;
	}

	//setting font , text , background Image
	void setFontAndTextAndbackground()
	{
		//setting background image
		backgroundTexture.loadFromFile("Pics/background.png");
		backgroundTexture.setSmooth(true);
		backgroundRec.setTexture(&backgroundTexture);
		backgroundRec.setSize(Vector2f(1910, 920));
		gameBacgroundTexture.loadFromFile("Pics/gameBackground.png");
		//loading font
		font.loadFromFile("Fonts/Sansation.ttf");
		font2.loadFromFile("Fonts/mn2t.otf");

		playerTurn.setFont(font);
		playerTurn.setStyle(Text::Bold);
		playerTurn.setFillColor(Color::Black);
		text1.setFont(font); // font is a sf::Font
		text1.setFillColor(sf::Color::Black);
		backToGames.setFont(font);
		backToGames.setStyle(Text::Bold);
		backToGames.setFillColor(Color::Black);
		BackToGamesFromInside.setFont(font);
		BackToGamesFromInside.setFillColor(Color::Black);
		BackToGamesFromInside.setStyle(Text::Bold);
		newGame.setFont(font);
		newGame.setFillColor(Color::Black);
		newGame.setStyle(Text::Bold);
		winningText.setFont(font);
		winningText.setStyle(Text::Bold);
		winnerName.setStyle(Text::Bold);
		winnerName.setFont(font);
		winnerName.setFillColor(Color::Black);
		winningText.setFillColor(Color::Black);
		text1.setStyle(sf::Text::Bold);
		for (int i = 0; i < 10; i++)
		{
			text[i].setFont(font2);
			text[i].setFillColor(sf::Color::Black);
			text[i].setStyle(sf::Text::Bold);
		}

		text1.setPosition(650, 550);
		backToGames.setPosition(645, 700);

		int pos = 400;
		for (int i = 0; i < np; i++)
		{
			playerText[i].setFont(font);
			playerText[i].setPosition(1190, pos);
			playerText[i].setStyle(Text::Bold);
			playerText[i].setCharacterSize(50);
			pos += 80;
		}
		playerText[0].setFillColor(Color::Blue);
		playerText[1].setFillColor(Color::White);
		playerText[2].setFillColor(Color::Black);
		playerText[3].setFillColor(Color::Green);
		playerText[4].setFillColor(Color::Red);

		//set the character size
		text1.setCharacterSize(100); // in pixels, not points!
		text[0].setCharacterSize(40);
		text[1].setCharacterSize(30);
		text[2].setCharacterSize(30);
		text[3].setCharacterSize(30);
		text[4].setCharacterSize(30);
		text[5].setCharacterSize(30);
		text[6].setCharacterSize(40);
		text[7].setCharacterSize(30);
		text[8].setCharacterSize(30);
		text[9].setCharacterSize(30);
		winningText.setCharacterSize(250);
		winnerName.setCharacterSize(150);
		backToGames.setCharacterSize(100);
		newGame.setCharacterSize(40);
		BackToGamesFromInside.setCharacterSize(40);
		playerTurn.setCharacterSize(40);

		//show text
		// set the string to display
		text1.setString(" Start --> [S] ");
		text[0].setString(" CHOOSE NUMBER OF PLAYERS ");
		text[1].setString(" One player    --> [1] ");
		text[2].setString(" Two players   --> [2]");
		text[3].setString(" Three players --> [3] ");
		text[4].setString(" Four players  --> [4]");
		text[5].setString(" Five players  --> [5]");
		text[6].setString(" CHOOSE LEVEL ");
		text[7].setString(" LEVEL 1 --> [1]");
		text[8].setString(" LEVEL 2 --> [2]");
		text[9].setString(" LEVEL 3 --> [3]");
		winningText.setString(" Winner ");
		backToGames.setString(" Back --> [B] ");
		BackToGamesFromInside.setString(" Back --> [B] ");
		newGame.setString(" New game --> [N] ");

		//	set position of text
		text[0].setPosition(sf::Vector2f(120.0f, 200.0f));
		text[1].setPosition(sf::Vector2f(140.0f, 350.0f));
		text[2].setPosition(sf::Vector2f(140.0f, 450.0f));
		text[3].setPosition(sf::Vector2f(140.0f, 550.0f));
		text[4].setPosition(sf::Vector2f(140.0f, 650.0f));
		text[5].setPosition(sf::Vector2f(140.0f, 750.0f));
		text[6].setPosition(sf::Vector2f(280.0f, 200.0f));
		text[7].setPosition(sf::Vector2f(300.0f, 350.0f));
		text[8].setPosition(sf::Vector2f(300.0f, 450.0f));
		text[9].setPosition(sf::Vector2f(300.0f, 550.0f));
		winningText.setPosition(Vector2f(10, 100));
		winnerName.setPosition(Vector2f(200, 400));
		newGame.setPosition(920, 285);
		BackToGamesFromInside.setPosition(1470, 285);
		playerTurn.setPosition(980, 800);
	}

	/*here each score is connect with another score and put into a snake or ladder*/
	void connectScores(map <int, int> &SnakeandLadder, char type)
	{
		srand(time(NULL));
		isTaken[0] = 1;
		isTaken[1] = 1;
		isTaken[100] = 1;

		for (int i = 0; i < ((0.15 * 100) + 1) / 2; i++)
		{
			while (isTaken[score1]) {
				score1 = 2 + rand() % 98;
			}

			isTaken[score1] = true;

			while (isTaken[score2])
			{
				score2 = 2 + rand() % 98;
			}

			isTaken[score2] = true;

			if (type == 'S')
			{
				if (score1 > score2)
				{
					SnakeandLadder[score1] = score2;

				}
				else
					SnakeandLadder[score2] = score1;
			}
			else if (type == 'L')
				if (score1 < score2)
				{
					SnakeandLadder[score1] = score2;
				}
				else
					SnakeandLadder[score2] = score1;
		}

	}

	//creation of the grid
	void createGrid()
	{
		backgroundRec.setTexture(&gameBacgroundTexture);
		float height = 10.0f, width = 10.0f;
		int cellCounter = 100;
		/*two for loops for making the grid generates the numbers as it is*/
		for (int i = 0; i < SIZE; i++)
		{
			if (i % 2 != 0)
			{
				cellCounter -= 9;
				for (int j = 0; j < SIZE; j++)
				{
					//getting the number of current square number and putting it in a string to get it from the path
					numberOfCell = "cellNumber/" + to_string(cellCounter) + ".png";
					//loading the texture (score picture)
					cellTexture[cellCounter - 1].loadFromFile(numberOfCell);
					cellTexture[cellCounter - 1].setSmooth(true);
					//connecting the score with its x and y indecies
					scoreAndIndicies[cellCounter] = { i , j };
					//putting the texture on its square
					squares[i][j].setTexture(&cellTexture[cellCounter - 1]);
					//resizing the square
					squares[i][j].setSize(sizeOfSquare);
					//getting square position
					squares[i][j].setPosition(height, width);
					//some calculations to be well positioned
					height += 90.0f;
					cellCounter++;
				}
				width += 90.0f;
				height = 10.0f;
				cellCounter -= 11;
			}
			else
			{
				/*read the comments in the above for loop its the same*/
				for (int j = 0; j < SIZE; j++)
				{
					numberOfCell = "cellNumber/" + to_string(cellCounter) + ".png";
					cellTexture[cellCounter - 1].loadFromFile(numberOfCell);
					cellTexture[cellCounter - 1].setSmooth(true);
					scoreAndIndicies[cellCounter] = { i , j };
					squares[i][j].setTexture(&cellTexture[cellCounter - 1]);
					squares[i][j].setSize(sizeOfSquare);
					squares[i][j].setPosition(height, width);

					height += 90.0f;
					cellCounter--;
				}
				width += 90.0f;
				height = 10.0f;
			}
		}

		//generating snakes and ladders
		connectScores(snake, 'S');
		connectScores(ladder, 'L');

		//shows beginnings and ends of snakes
		cout << "SNAKES:\n";
		for (map<int, int> ::iterator iter = snake.begin(); iter != snake.end(); iter++)
		{
			cout << " IF YOUR SCORE  =   " << iter->first << "  " << "THERE is snake  so  " << "  Your score will be =  " << iter->second << "\n";
		}
		cout << endl;

		//shows beginnings and ends of ladders
		cout << "LADDERS:\n";
		for (map<int, int> ::iterator iter = ladder.begin(); iter != ladder.end(); iter++)
		{
			cout << " IF YOUR SCORE  =  " << iter->first << "  " << "  THERE is Ladder so  " << "   Your score will be  = " << iter->second << "\n";
		}
		cout << endl;

		return;
	}

	//just displaying the grid
	void drawGrid()
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				snakeAndLadderWindow.draw(squares[i][j]);
			}
		}
	}

	//getting dice textures(picture) from its path
	void createDice()
	{
		dice.setPosition(1300.0f, 265.0f);
		diceTexture[0].loadFromFile("dice/1.png");
		diceTexture[1].loadFromFile("dice/2.png");
		diceTexture[2].loadFromFile("dice/3.png");
		diceTexture[3].loadFromFile("dice/4.png");
		diceTexture[4].loadFromFile("dice/5.png");
		diceTexture[5].loadFromFile("dice/6.png");
		for (int i = 0; i < 6; i++)
			diceTexture[i].setSmooth(true);
		diceSoundBuffer.loadFromFile("Sounds/dieThrow1.ogg");
		diceSound.setBuffer(diceSoundBuffer);
	}

	//rolling dice if the counter is less than 100 or it will stay as it is
	void rollDice()
	{
		if (numberOfRolling <= 100 && numberOfRolling - lastRoll == 15)
		{
			dicePicNumber = rand() % 6;
			dice.setTexture(&diceTexture[dicePicNumber]);
			lastRoll = numberOfRolling;
		}

		snakeAndLadderWindow.draw(dice);
		if (numberOfRolling <= 100) numberOfRolling++;
	}

	//displaying current scores of players
	void playTurns(int numberOfplayers)
	{
		//prints updated scoreboard
		cout << "Scoreboard:\n\n";
		cout << "Name\t\tScore\n";

		player tempSort[np];

		for (int i = 0; i < np; i++)
		{
			tempSort[i] = players[i];
		}

		//sorting scores 
		bool swapped;
		do {
			swapped = false;
			for (int i = 0; i < np - 1; i++) {
				if (tempSort[i].score < tempSort[i + 1].score) {
					swap(tempSort[i], tempSort[i + 1]);
					swapped = true;
				}
			}
		} while (swapped);

		for (int i = 0; i < numberOfplayers; i++)
		{
			cout << tempSort[i].name << "\t\t" << tempSort[i].score << endl;
			playerText[i].setFillColor(tempSort[i].color);
			playerText[i].setString(tempSort[i].name + "\t\t" + to_string(tempSort[i].score));
			snakeAndLadderWindow.draw(playerText[i]);
		}
	}

	//updating player's score
	void gameplay(int numberOfPlayer, int move, int numberOfPlayers)
	{
		cout << "It's " << players[numberOfPlayer].name << "'s turn, press any key to play...\n";

		//dice roll
		cout << "You got " << move << endl;

		//updates player current score
		players[numberOfPlayer].score += move;

		//checking if some one exceeded the maximum score of baord
		if (players[numberOfPlayer].score >= 100)
		{
			players[numberOfPlayer].score = 100;
			indexOfWinner = numberOfPlayer;
		}

		//getting x and y indecies of new score
		int destinationX = scoreAndIndicies[players[numberOfPlayer].score].first;
		int destinationY = scoreAndIndicies[players[numberOfPlayer].score].second;

		//setting player's destination
		destination[numberOfPlayer][0] = squares[destinationX][destinationY].getPosition().x;
		destination[numberOfPlayer][1] = squares[destinationX][destinationY].getPosition().y;

		//views updated grid
		playTurns(numberOfPlayers);

		//check if anyone has won the game yet
		if (players[numberOfPlayer].score > maxScore) maxScore = players[numberOfPlayer].score;
	}

	//checking if current score contains snake or ladder
	void checkPosition(int numberOfPlayer, int numberOfPlayers)
	{

		//checks updated score for snakes or ladders
		auto isSnake = snake.find(players[numberOfPlayer].score);
		auto isLadder = ladder.find(players[numberOfPlayer].score);

		if (isSnake != snake.end())
		{
			findingSnakeSound.play();
			cout << "OH NO! YOU FELL INTO A SNAKE!\n";
			speed = 1;
			players[numberOfPlayer].score = snake[players[numberOfPlayer].score];
		}
		else if (isLadder != ladder.end())
		{
			findingLadderSound.play();
			speed = 1;
			cout << "WOOHOO! YOU FOUND A LADDER!\n";
			players[numberOfPlayer].score = ladder[players[numberOfPlayer].score];
		}

		//getting x and y indecies of new score
		int destinationX = scoreAndIndicies[players[numberOfPlayer].score].first;
		int destinationY = scoreAndIndicies[players[numberOfPlayer].score].second;

		//setting player's destination
		destination[numberOfPlayer][0] = squares[destinationX][destinationY].getPosition().x;
		destination[numberOfPlayer][1] = squares[destinationX][destinationY].getPosition().y;

		//displaying new score
		playTurns(numberOfPlayers);

		//check if anyone has won the game yet
		if (players[numberOfPlayer].score > maxScore) maxScore = players[numberOfPlayer].score;
	}

	//creating players
	void createSprite()
	{
		//loading players' texture from path
		for (int i = 0; i < 5; i++)
		{
			string textureOfSprite = "player/" + to_string(i + 1) + ".png";
			spriteTexture[i].loadFromFile(textureOfSprite);
			spriteTexture[i].setSmooth(true);
		}
		//setting width and heigth of the texture
		spriteTextureSize.x = spriteTexture[0].getSize().x;
		spriteTextureSize.y = spriteTexture[0].getSize().y;

		for (int i = 0; i < np; i++)
		{
			//setting texture
			sprites[i].setTexture(spriteTexture[i]);
			//cropping the texture to get specific part of it
			sprites[i].setTextureRect(IntRect(2 * spriteTextureSize.x / 9, 2 * spriteTextureSize.y / 4, spriteTextureSize.x / 9, spriteTextureSize.y / 4));
			//setting position to be at score 1
			sprites[i].setPosition(squares[9][0].getPosition().x, squares[9][0].getPosition().y);
			//setting destination of players to be at the same point
			destination[i][0] = squares[9][0].getPosition().x;
			destination[i][1] = squares[9][0].getPosition().y;
		}
	}

	//just displaying the players
	void drawSprite(int numberOfPlayers)
	{
		for (int i = 0; i < numberOfPlayers; i++)
		{
			sprites[i].setScale(1.2f, 1.2f);
			snakeAndLadderWindow.draw(sprites[i]);
		}
	}

	//setting players' names
	void getPlayers(int numberOfPlayers)
	{
		for (int i = 0; i < numberOfPlayers; i++)
		{
			players[i].name = (string)playerText_y[i].getString();
			switch (i)
			{
			case 0:
				players[i].color = Color::Blue;
				break;
			case 1:
				players[i].color = Color::White;
				break;
			case 2:
				players[i].color = Color::Black;
				break;
			case 3:
				players[i].color = Color::Green;
				break;
			case 4:
				players[i].color = Color::Red;
				break;
			}
			playerText[i].setString(players[i].name + "\t\t" + to_string(players[i].score));
		}
	}

	//creating snakes
	void createSnakes()
	{
		//running into snake sound
		findingSnakeBuffer.loadFromFile("Sounds/Scream.ogg");
		findingSnakeSound.setBuffer(findingSnakeBuffer);
		//loading snake texture
		auto it = snake.begin();
		for (int i = 0; i < 8 && it != snake.end(); i++, it++)
		{
			//loading snake texture
			string snakeName = "Snake/" + to_string(i + 1) + ".png";
			snakeTexture[i].loadFromFile(snakeName);
			snakeTexture[i].setSmooth(true);
			snakeName = "Snake/t" + to_string(i + 1) + ".png";
			snakeTexture[i + 8].loadFromFile(snakeName);
			//setting each snake on each score
			snakeSprite[i].setTexture(snakeTexture[i]);
			snakeSprite[i + 8].setTexture(snakeTexture[i + 8]);
			//start of snake
			int xIndex = scoreAndIndicies[it->first].first;
			int yIndex = scoreAndIndicies[it->first].second;
			float xPos = squares[xIndex][yIndex].getPosition().x;
			float yPos = squares[xIndex][yIndex].getPosition().y;
			snakeSprite[i].setPosition(xPos, yPos);
			snakeSprite[i].setTextureRect(IntRect(0, 2 * snakeTexture[i].getSize().y / 4, snakeTexture[i].getSize().x / 3, snakeTexture[i].getSize().y / 4));
			//end of snake
			xIndex = scoreAndIndicies[it->second].first;
			yIndex = scoreAndIndicies[it->second].second;
			xPos = squares[xIndex][yIndex].getPosition().x;
			yPos = squares[xIndex][yIndex].getPosition().y;
			snakeSprite[i + 8].setPosition(xPos - 45, yPos - 25);
		}
	}

	//creating snakes
	void createLadder()
	{
		//finding ladder sound
		findingLadderBuffer.loadFromFile("Sounds/Happy.ogg");
		findingLadderSound.setBuffer(findingLadderBuffer);
		//loading snake texture
		auto it = ladder.begin();
		for (int i = 0; i < 8 && it != ladder.end(); i++, it++)
		{
			//loading ladder texture
			string ladderName = "Ladder/" + to_string(i + 1) + ".png";
			ladderTexture[i].loadFromFile(ladderName);
			ladderTexture[i].setSmooth(true);
			//setting each ladder on each score
			ladderSprite[i].setTexture(ladderTexture[i]);
			ladderSprite[i + 8].setTexture(ladderTexture[i]);
			//start of ladder
			int xIndex = scoreAndIndicies[it->first].first;
			int yIndex = scoreAndIndicies[it->first].second;
			float xPos = squares[xIndex][yIndex].getPosition().x;
			float yPos = squares[xIndex][yIndex].getPosition().y;
			ladderSprite[i].setPosition(xPos, yPos);
			//end of ladder
			xIndex = scoreAndIndicies[it->second].first;
			yIndex = scoreAndIndicies[it->second].second;
			xPos = squares[xIndex][yIndex].getPosition().x;
			yPos = squares[xIndex][yIndex].getPosition().y;
			ladderSprite[i + 8].setPosition(xPos, yPos);
		}
	}

	//displaying ladders
	void drawLadders()
	{
		for (int i = 0; i < 16; i++)
		{
			ladderSprite[i].setScale(.13, .13);
			snakeAndLadderWindow.draw(ladderSprite[i]);
		}
	}

	//displaying snakes
	void drawSnakes()
	{
		for (int i = 0; i < 16; i++)
		{
			(i < 8) ? snakeSprite[i].setScale(.8, .8) : snakeSprite[i].setScale(.25, .25);
			snakeAndLadderWindow.draw(snakeSprite[i]);
		}
	}

	//Launching game 
	void begin(int numberOfPlayers, int level)
	{
		snake.clear();
		ladder.clear();
		isTaken.clear();
		for (int i = 0; i < np; i++)
		{
			players[i].score = 1;
		}
		maxScore = 0;
		createDice();
		createGrid();
		createSprite();
		getPlayers(numberOfPlayers);
		createSnakes();
		createLadder();
		//setting initial dice texture to be one
		dice.setTexture(&diceTexture[0]);
	}

	//getting player's names
	int getplayer_name(int number_of_players, Event event, int& x)
	{
		playerinfo_y.setString("Enter name of player #" + to_string(x));

		if (event.type == Event::TextEntered)
		{
			if (event.text.unicode == 8)
			{
				if (playerInput_y.size() > 0) playerInput_y.erase(playerInput_y.size() - 1, 1);
			}
			else if ((event.text.unicode >= 65 && event.text.unicode <= 122))

				playerInput_y += (char)event.text.unicode;

			playerText_y[number_of_players].setString(playerInput_y);
			if (Keyboard::isKeyPressed(Keyboard::Return) && playerInput_y.size() > 0)
			{

				number_of_players++;
				x++;
				playerInput_y.clear();
			}
		}

		return number_of_players;
	}

	//setting font and text for getting names
	void text_style(Text playerTexts[], Text player[], Text& playerinfor)
	{
		font_y.loadFromFile("Fonts/mn2t.otf");
		playerinfor.setFont(font_y);
		playerinfor.setCharacterSize(40);
		playerinfor.setFillColor(Color::Black);
		playerinfor.setStyle(Text::Bold);
		playerinfor.setPosition(100, 200);

		for (int i = 0; i < 5; i++)

		{
			player[i].setFont(font_y);
			player[i].setCharacterSize(30);
			player[i].setPosition(180.0f, 300.0f + (i*100.0f));
			player[i].setFillColor(Color::Black);
			player[i].setStyle(Text::Bold);
		}
		for (int i = 0; i < 5; i++)
		{
			playerTexts[i].setFont(font_y);
			playerTexts[i].setCharacterSize(30);
			playerTexts[i].setPosition(600.0f, 300.0f + (i * 100.0f));
			playerTexts[i].setFillColor(Color::Black);
			playerTexts[i].setStyle(Text::Bold);
		}

		players_y[0].setString("Player # 1 Name :");
		players_y[1].setString("Player # 2 Name :");
		players_y[2].setString("Player # 3 Name :");
		players_y[3].setString("Player # 4 Name :");
		players_y[4].setString("Player # 5 Name :");


		playerinfo_y.setString("Enter name of player #" + to_string(1));
	}

	//drawing text for getting names
	void draw_names(Text playertexts[], Text playerss[], Text playerinfor , int to)
	{
		for (int i = 0; i < to; i++)
		{
			snakeAndLadderWindow.draw(playertexts[i]);
			snakeAndLadderWindow.draw(playerss[i]);
		}

		snakeAndLadderWindow.draw(playerinfor);
	}
}