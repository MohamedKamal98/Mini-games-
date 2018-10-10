#pragma once

using namespace std;
using namespace sf;

namespace MINE_SWEEPER
{
#define SIZE 10

	//main window initialisation 
	RenderWindow Minesweeper;
	int difficulty = -1;

	//holds player name
	string name;

	//map for cell range mouse clicks
	map < pair<int, int>, pair< pair<int, int>, pair<int, int> > > cellRange;

	//for visual mine cells on the grid
	RectangleShape mine[SIZE][SIZE];
	//sets cell size
	Vector2f cellSize = Vector2f(45.0f, 45.0f);
	//texture for unopened cell
	Texture closedCell;

	//headboard texture
	RectangleShape headboard;
	Texture headboardTexture;

	//new game smile face texture
	RectangleShape newGame;
	Texture newGameTexture;

	//texture for lost face
	Texture lostFaceTexture;

	//headboard for bomb counter
	RectangleShape headboardBombCount[3];
	Texture headboardBombCountTexture[3];

	//headboard for timer
	RectangleShape timer[3];
	Texture timerTexture[3];

	//Texture for empty cells
	Texture emptyCellTexture;

	//Texture for empty cells
	Texture flaggedCellTexture;
	//Texture for killing mine
	Texture killingMine;

	//question mark texture
	Texture questionMarkTexture;

	//texture for flagged non-mine cells
	Texture notMineTexture;

	//texture for winning
	Texture wonTexture;

	//you won message
	RectangleShape youWon;
	Texture youWonTexture;

	//Texture for bombs
	Texture bombTexture;
	//Texture for numbers of bombs around the cell
	Texture numberOfbombsAroundCell[8];


	//grid for getting bombs and numbers
	int grid[SIZE][SIZE];

	//flagged
	bool flaggedCell[SIZE][SIZE];

	//flag counter
	int flagCounter = 0;

	//number of bombs in the level 
	int numberOfBombs;

	//Counter for Welcome window
	int counter = 0;

	//the eight directions for searching the cells (dfs)
	int dx[] = { 0, 0, 1, -1 , 1 , -1 , 1 , -1 };
	int dy[] = { 1, -1, 0, 0 , 1 , -1 , -1 , 1 };

	//array for checking if the cell is already visited
	bool visited[SIZE][SIZE];


	void mineSweeper();
	void welcomeminesweeper();

	vector<pair<int, string> > getLeaderBoard(string, int, int);
	void leaderboards(string, int, int);

	bool valid(int, int);
	void generateBombs(int);
	void countBombs(int cell[][SIZE]);
	void checkNeighboringCell(int, int);
	bool checkCell(int, int);
	pair<int, int> cellPosition(int, int);
	bool won(bool board[][SIZE]);

	void setNumberOfBombsTexture();
	void setMineSize();
	void setHeadboard();
	void setNewGame();
	void setBombCount();
	void setTimer(int);
	void viewBombs();
	void drawMines();
	void drawBombCount();
	void drawTimer();

	void game(int);

	void mineSweeper()
	{
		counter = 0;
		welcomeminesweeper();
		return;
	}


	//getting leaderboard
	vector<pair<int, string> > getLeaderBoard(string currentPlayerName, int currentPlayerScore, int level)
	{
		vector<pair<int, string > > leaderBoard;
		leaderBoard.push_back({ currentPlayerScore , currentPlayerName });
		fstream leaderBoardFile("leaderBoardFile_Level" + to_string(level) + ".txt", ios::in);

		string temp_name;
		int temp_score;
		while (leaderBoardFile >> temp_score >> temp_name)
		{
			leaderBoard.push_back({ temp_score , temp_name });
		}

		sort(leaderBoard.begin(), leaderBoard.end());
		leaderBoardFile.close();

		leaderBoardFile.open("leaderBoardFile_Level" + to_string(level) + ".txt", ios::out);

		for (int i = 0; i < min((int)leaderBoard.size(), 10); i++)
		{
			leaderBoardFile << leaderBoard[i].first << " " << leaderBoard[i].second << endl;
		}

		return leaderBoard;
	}

	//showing leaderboard
	void leaderboards(string s, int score, int level)
	{
		RenderWindow leaderboardWindow(VideoMode(650, 800), "Leaderboards", Style::Close);
		Font topScoresFont;
		topScoresFont.loadFromFile("Splash/Homestead-Display.ttf");
		Text topTenPlayers[10], topTenRecords[10];

		vector < pair<int, string> > topTen = getLeaderBoard(name, score, level);

		RectangleShape background;
		Texture backgroundTexture;

		backgroundTexture.loadFromFile("Graphics/bg.png");
		background.setTexture(&backgroundTexture);
		background.setPosition(0, 0);
		background.setSize(Vector2f(650.0f, 800.0f));

		//set text font
		for (int i = 0; i < min(10, (int)topTen.size()); i++)
		{

			topTenRecords[i].setFont(topScoresFont);
			topTenPlayers[i].setFont(topScoresFont);

			topTenRecords[i].setFillColor(Color::Black);
			topTenPlayers[i].setFillColor(Color::Black);

			topTenRecords[i].setCharacterSize(35);
			topTenPlayers[i].setCharacterSize(35);

			topTenPlayers[i].setString(topTen[i].second);
			topTenRecords[i].setString(to_string(topTen[i].first));

			topTenPlayers[i].setPosition(165.0f, 125.0f + (67 * i));
			topTenRecords[i].setPosition(430.0f, 125.0f + (67 * i));
		}

		while (leaderboardWindow.isOpen())
		{
			Event event;
			while (leaderboardWindow.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					leaderboardWindow.close();
					break;
				}
			}

			leaderboardWindow.clear();

			leaderboardWindow.draw(background);

			for (int i = 0; i < 10; i++)
			{
				leaderboardWindow.draw(topTenPlayers[i]);
				leaderboardWindow.draw(topTenRecords[i]);
			}


			Sprite LevelDifficulty;
			Texture star;

			switch (level)
			{
			case 1:
				star.loadFromFile("Graphics/Star(1).png");
				break;

			case 2:
				star.loadFromFile("Graphics/Star(2).png");
				break;
			case 3:
				star.loadFromFile("Graphics/Star(3).png");
				break;
			}

			LevelDifficulty.setTexture(star);
			//LevelDifficulty.setScale(140, 140);
			LevelDifficulty.setPosition(540, 60);

			leaderboardWindow.draw(LevelDifficulty);

			leaderboardWindow.display();

		}
	}

	//checks for valid indices
	bool valid(int x, int y)
	{
		return (x < 10 && x >= 0 && y < 10 && y >= 0);
	}

	//function for welcome window
	void welcomeminesweeper();

	//generates bombs in the grid
	void generateBombs(int level)
	{
		//setting number of bombs according to chosen level
		switch (level)
		{
		case 1:
			numberOfBombs = 10;
			break;
		case 2:
			numberOfBombs = 15;
			break;
		case 3:
			numberOfBombs = 20;
		}

		//getting bombs indicies
		map<pair<int, int>, bool>isTaken;
		int x, y;
		for (int i = 0; i < numberOfBombs; i++)
		{
			x = rand() % SIZE;
			y = rand() % SIZE;

			if (isTaken[{x, y}] == 0)
			{
				isTaken[{x, y}] = 1;
				grid[x][y] = -1;
			}
			else
			{
				i--;
				continue;
			}
		}
	}

	//counts bombs around each cell
	void countBombs(int cell[][SIZE])
	{
		int bombcounter;
		//check on every cell in the 2D cell[sze][sze]
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				bombcounter = 0;

				if (cell[i][j] == -1) {
					continue;
				}


				//check on the 8 cells around the requird cell
				for (int k = i - 1; k < i + 2; k++)
				{
					for (int g = j - 1; g < j + 2; g++)
					{
						//cell[i][j] (required cell)continue on the following cell
						if (cell[k][g] == cell[i][j] || !valid(k, g))
							continue;
						//check on the bomb
						else if (cell[k][g] == -1)
							bombcounter++;
					}
				}

				//the last cell in the counter around the required  cell will carry the number of bombs
				cell[i][j] = bombcounter;

			}
		}
	}

	//cheking neighbouring cell of the empty cell
	void checkNeighboringCell(int x, int y)
	{
		if (valid(x, y) && !visited[x][y])
		{
			visited[x][y] = 1;
			if (grid[x][y] == -1)
			{
				return;
			}
			else if (grid[x][y])
			{
				//setting number of bombs around the cell texture and returning 1
				if (!flaggedCell[x][y])
					mine[x][y].setTexture(&numberOfbombsAroundCell[grid[x][y] - 1]);
				return;
			}
			else
			{
				//the cell is empty and empty texture will be put and other surrounding cells will be checked
				if (!flaggedCell[x][y])
					mine[x][y].setTexture(&emptyCellTexture);
				//openning neighbouring cells of the empty cell
				for (int i = 0; i < 8; i++)
				{
					checkNeighboringCell(x + dx[i], y + dy[i]);
				}
				return;
			}
		}
	}
	
	//checking what the cell contains and return 0 if there is a bomb otherwise it will return 1
	bool checkCell(int x, int y)
	{

		visited[x][y] = 1;
		//checking for if there is a bomb in the cell(-1), empty cell(0) or contains a number
		if (grid[x][y] == -1)
		{
			//setting bombs texture in the square and returning zero 
			mine[x][y].setTexture(&bombTexture);
			return 1;
		}
		else if (grid[x][y])
		{
			//setting number of bombs around the cell texture and returning 1
			if (!flaggedCell[x][y])
				mine[x][y].setTexture(&numberOfbombsAroundCell[grid[x][y] - 1]);
			return 0;
		}
		else
		{
			//the cell is empty and empty texture will be put and other surrounding cells will be checked
			if (!flaggedCell[x][y])
				mine[x][y].setTexture(&emptyCellTexture);
			//openning neighbouring cells of the empty cell
			for (int i = 0; i < 8; i++)
			{
				checkNeighboringCell(x + dx[i], y + dy[i]);
			}
			return 0;
		}
	}

	//takes mouse input and returns position of the clicked cell
	pair<int, int> cellPosition(int x, int y)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				//takes the x-coordinate
				pair <int, int > px = cellRange[{i, j}].first;
				//takes the y-coordinate
				pair <int, int > py = cellRange[{i, j}].second;
				//checks if the click is in the current cell range
				if (x >= px.first && x <= px.second && y >= py.first && y <= py.second)
					return{ i,j };
			}
		}
		return{ x, y };
	}

	//loads number of bombs images from file
	void setNumberOfBombsTexture()
	{
		for (int i = 0; i < 8; i++)
		{
			numberOfbombsAroundCell[i].loadFromFile("Graphics/Number of Bombs/" + to_string(i + 1) + ".png");
		}
	}

	//setting size, texture, position for each cell
	void setMineSize()
	{
		//setting grid initial position of the first cell
		float height = 160, width = 20;

		//loads images of unopened cell, opened cell, flagged cell and bomb cell
		closedCell.loadFromFile("Graphics/closed cell.png");
		emptyCellTexture.loadFromFile("Graphics/opened cell.png");
		flaggedCellTexture.loadFromFile("Graphics/flagged.png");
		bombTexture.loadFromFile("Graphics/opened mine.png");
		questionMarkTexture.loadFromFile("Graphics/question.png");

		//sets images for each cell as unopened cell
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				//sets cell size
				mine[i][j].setSize(cellSize);
				//set cell texture
				mine[i][j].setTexture(&closedCell);
				//set cell position on the grid
				mine[i][j].setPosition(width, height);

				//setting cell range
				cellRange[{i, j}] = { { width, width + 45 },{ height, height + 45 } };


				width += 45.0f;
			}
			width = 20.0f;
			height += 45.0f;
		}
	}

	//drawing mines
	void drawMines()
	{

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				Minesweeper.draw(mine[i][j]);
			}
		}
	}

	/*setting headboard with new game icon, timer and bomb count*/

	//sets headboard size, texture, position
	void setHeadboard()
	{
		//loading headboard image from file
		headboardTexture.loadFromFile("Graphics/border.png");
		//getting image dimensions
		float headboardX = headboardTexture.getSize().x, headboardY = headboardTexture.getSize().y;
		//setting headboard object according to its size
		Vector2f headboardSize = Vector2f(headboardX, headboardY);
		headboard.setSize(headboardSize);
		headboard.setTexture(&headboardTexture);
		headboard.setPosition(0, 0);

	}
	//sets new game icon size, texture, position
	void setNewGame()
	{
		//loading new game image from file
		newGameTexture.loadFromFile("Graphics/new game.png");
		//getting image dimensions
		float newGameX = newGameTexture.getSize().x, newGameY = newGameTexture.getSize().y;
		//setting new game object
		Vector2f newGameSize = Vector2f(90, 90);
		//setting size
		newGame.setSize(newGameSize);
		//setting texture
		newGame.setTexture(&newGameTexture);
		//setting position
		newGame.setPosition(196, 35);
	}

	//sets bomb count size, texture, position
	void drawHeadboardBombCount()
	{
		for (int i = 0; i < 3; i++)
			Minesweeper.draw(headboardBombCount[i]);
	}

	//sets bomb counter on headboard
	void setBombCount()
	{
		int leftBombs = numberOfBombs - flagCounter;
		headboardBombCountTexture[2].loadFromFile("Graphics/Count/d" + to_string(leftBombs % 10) + ".png");
		headboardBombCountTexture[1].loadFromFile("Graphics/Count/d" + to_string((leftBombs / 10) % 10) + ".png");
		headboardBombCountTexture[0].loadFromFile("Graphics/Count/d" + to_string((leftBombs / 100) % 10) + ".png");

		for (int i = 0; i < 3; i++)
		{
			headboardBombCount[i].setTexture(&headboardBombCountTexture[i]);
			headboardBombCount[i].setPosition(49 + (45 * i), 42);
			headboardBombCount[i].setSize(Vector2f(44, 80));
		}
	}

	//draws bomb counter
	void drawBombCount()
	{
		for (int i = 0; i < 3; i++)
		{
			Minesweeper.draw(headboardBombCount[i]);
		}
	}

	void setTimer(int time)
	{
		timerTexture[2].loadFromFile("Graphics/Count/d" + to_string(time % 10) + ".png");
		timerTexture[1].loadFromFile("Graphics/Count/d" + to_string((time / 10) % 10) + ".png");
		timerTexture[0].loadFromFile("Graphics/Count/d" + to_string((time / 100) % 10) + ".png");

		for (int i = 0; i < 3; i++)
		{
			timer[i].setTexture(&timerTexture[i]);
			timer[i].setPosition(310 + (45 * i), 42);
			timer[i].setSize(Vector2f(44, 80));
		}
	}

	//draws timer
	void drawTimer()
	{
		for (int i = 0; i < 3; i++)
		{
			Minesweeper.draw(timer[i]);
		}
	}

	//checks if player has won or not
	bool won(bool board[][SIZE])
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (!board[i][j]) return 0;
			}
		}

		return (flagCounter == numberOfBombs) ? 1 : 0;
	}
	//views rest of bombs
	void viewBombs()
	{
		notMineTexture.loadFromFile("Graphics/not mine.png");
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (grid[i][j] == -1)
				{
					if (!flaggedCell[i][j])
						mine[i][j].setTexture(&bombTexture);
				}
				else if (flaggedCell[i][j])
				{
					mine[i][j].setTexture(&notMineTexture);
				}
			}
		}
	}

	//runs game window
	void game(int level)
	{
		Minesweeper.create(VideoMode(495, 628), "Minesweeper", Style::Close);

		generateBombs(level);
		countBombs(grid);
		memset(visited, 0, sizeof(visited));

		setMineSize();
		setBombCount();
		setHeadboard();
		setNewGame();
		setNumberOfBombsTexture();
		bool shown = 0;
		//clock for the timer on the headboard
		Clock clock;

		bool lost = 0;
		int startTimer = 0;

		//shows total gameplay time after winning or losing
		int gameTime = 0;

		while (Minesweeper.isOpen())
		{

			Time elapsed = clock.getElapsedTime();
			int elapsedTime = elapsed.asSeconds();

			Event event;
			while (Minesweeper.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					memset(grid, 0, sizeof(grid));
					memset(visited, 0, sizeof(visited));
					memset(flaggedCell, 0, sizeof(flaggedCell));
					counter = 1;
					lost = 0;
					difficulty = -1;
					flagCounter = 0;
					Minesweeper.close();
					return;
				}
				switch (event.type)
				{
				case Event::MouseButtonPressed:
				{

					// open neighboring cells if flags equal to number of bombs around cell


					//if (Mouse::isButtonPressed(Mouse::Left) && Mouse::isButtonPressed(Mouse::Right))
					//{
					//	//cout << "both" << endl;
					//	Vector2i mouseClick = Mouse::getPosition(Minesweeper);
					//	pair <int, int> pos = cellPosition( mouseClick.x, mouseClick.y );
					//	if (valid(pos.first, pos.second))
					//	{
					//		if (visited[pos.first][pos.second])
					//		{
					//			int surroundingFlags = 0;
					//			for (int i = 0; i < 8; i++)
					//			{
					//				if (valid(pos.first + dx[i], pos.second + dy[i]))
					//				{
					//					if (flaggedCell[pos.first + dx[i]][pos.second + dy[i]]) surroundingFlags++;
					//				}
					//			}

					//			if (surroundingFlags >= grid[pos.first][pos.second] && !flaggedCell[pos.first][pos.second])
					//			{
					//				for (int i = 0; i < 8; i++)
					//				{
					//					if (valid(pos.first + dx[i], pos.second + dy[i]))
					//					{
					//						if (!flaggedCell[pos.first + dx[i] ][pos.second +dy[i]] && !visited[pos.first + dx[i]][pos.second + dy[i]])
					//						{
					//							lost = checkCell(pos.first + dx[i], pos.second + dy[i]);

					//							if (lost)
					//							{
					//								startTimer = 0;

					//								if (gameTime == 0)
					//									gameTime = elapsedTime;

					//								viewBombs();
					//								newGameTexture.loadFromFile("Graphics/killed.png");
					//								killingMine.loadFromFile("Graphics/killing mine.png");
					//								mine[pos.first + dx[i]][pos.second + dy[i]].setTexture(&killingMine);
					//								newGame.setTexture(&newGameTexture);
					//							}

					//						}
					//					}
					//				}
					//			}
					//		}
					//	}
					//}


					if (Mouse::isButtonPressed(Mouse::Left))
					{
						Vector2i mouseClick = Mouse::getPosition(Minesweeper);

						pair <int, int> pos = { mouseClick.x, mouseClick.y };

						if (pos.first >= 196 && pos.second >= 40 && pos.first <= 286 && pos.second <= 130)
						{
							memset(grid, 0, sizeof(grid));
							memset(visited, 0, sizeof(visited));
							memset(flaggedCell, 0, sizeof(flaggedCell));
							counter = 1;
							lost = 0;
							difficulty = -1;
							flagCounter = 0;
							welcomeminesweeper();
						}
					}

					if (!lost)
					{
						//checks for mouse input to open cells
						if (Mouse::isButtonPressed(Mouse::Left))
						{
							Vector2i mouseClick = Mouse::getPosition(Minesweeper);
							
							pair <int, int> pos = cellPosition(mouseClick.x, mouseClick.y);

							if (valid(pos.first, pos.second))
							{
								startTimer++;

								if (flaggedCell[pos.first][pos.second]) continue;
								lost = checkCell(pos.first, pos.second);
								if (lost)
								{
									startTimer = 0;

									if (gameTime == 0)
										gameTime = elapsedTime;

									viewBombs();
									newGameTexture.loadFromFile("Graphics/killed.png");
									killingMine.loadFromFile("Graphics/killing mine.png");
									mine[pos.first][pos.second].setTexture(&killingMine);
									newGame.setTexture(&newGameTexture);
								}
							}

						}


						//checks mouse input to add flags
						if (Mouse::isButtonPressed(Mouse::Right))
						{
							Vector2i mouseClick = Mouse::getPosition(Minesweeper);
							pair <int, int> pos = cellPosition(mouseClick.x, mouseClick.y);
							if (valid(pos.first, pos.second))
							{
								startTimer++;

								if (visited[pos.first][pos.second] && !flaggedCell[pos.first][pos.second]) continue;
								if (!flaggedCell[pos.first][pos.second])
								{
									mine[pos.first][pos.second].setTexture(&flaggedCellTexture);
									flaggedCell[pos.first][pos.second] = true;
									visited[pos.first][pos.second] = true;
									flagCounter++;
								}
								else
								{
									mine[pos.first][pos.second].setTexture(&questionMarkTexture);
									flaggedCell[pos.first][pos.second] = false;
									visited[pos.first][pos.second] = false;
									flagCounter--;
								}
							}
						}
					}

				}
				break;
				}
			}

			setBombCount();
			Minesweeper.clear();

			drawMines();
			Minesweeper.draw(headboard);
			drawBombCount();
			drawHeadboardBombCount();

			if (startTimer == 0)
			{
				clock.restart();
				if (!lost)
				{
					setTimer(elapsedTime);
				}
				else
				{
					setTimer(gameTime);
				}
			}
			else
			{
				setTimer(elapsedTime);
			}

			drawTimer();

			if (won(visited))
			{
				//cout << "name: " << name << " score: " << gameTime << "level: " << level << endl;
				wonTexture.loadFromFile("Graphics/won.png");
				newGame.setTexture(&wonTexture);
				youWonTexture.loadFromFile("Graphics/you won box.png");
				youWon.setPosition(150, 300);
				youWon.setSize(Vector2f(youWonTexture.getSize().x / 2, youWonTexture.getSize().y / 2));
				youWon.setTexture(&youWonTexture);
				Minesweeper.draw(youWon);

				startTimer = 0;

				if (gameTime == 0)
					gameTime = elapsedTime;

				lost = 1;
				if (!shown)
				{
					Minesweeper.draw(newGame);
					Minesweeper.display();
					leaderboards(name, gameTime, level), shown = 1;
				}
			}
			Minesweeper.draw(newGame);

			Minesweeper.display();
		}

	}

	void welcomeminesweeper()
	{
		Minesweeper.create(VideoMode(512, 512), "Minesweeper", Style::Close);
		RectangleShape open(Vector2f(512.0f, 512.0f));
		RectangleShape textrect(Vector2f(10.0f, 10.0f));
		RectangleShape backgroundtexture_rect(Vector2f(512.0f, 512.0f));
		Texture opentexture;
		Texture backgroundtexture;
		//open.setPosition(10.0f, 10.0f);
		opentexture.loadFromFile("Splash/open.png");
		open.setTexture(&opentexture);
		backgroundtexture.loadFromFile("Splash/1bg.jpg");
		backgroundtexture_rect.setTexture(&backgroundtexture);
		Text text, text1[4];
		Font font;
		font.loadFromFile("Splash/octin college rg.otf");
		text.setFont(font);
		text.setString("Press Space");
		text.setPosition(Vector2f(165.0f, 400.0f));

		// set the character size
		text.setCharacterSize(35); // in pixels, not points!

								   // set the color
		text.setFillColor(Color::White);

		// set the text style
		text.setStyle(sf::Text::Italic);
		for (int i = 0; i < 4; i++)
		{
			text1[i].setFont(font);
			text1[i].setFillColor(Color::Black);
			text1[i].setStyle(Text::Bold);
		}

		//set the character size
		text1[0].setCharacterSize(60);
		text1[1].setCharacterSize(25);
		text1[2].setCharacterSize(25);
		text1[3].setCharacterSize(25);

		//show the text
		text1[0].setString(" Choose  Level  ");
		text1[1].setString("Level One     -->  [1]");
		text1[2].setString("Level Two    -->  [2]");
		text1[3].setString("Level Three  -->  [3]");

		//set positon of text
		text1[0].setPosition(Vector2f(45.0f, 80.0f));
		text1[1].setPosition(Vector2f(140.0f, 180.0f));
		text1[2].setPosition(Vector2f(140.0f, 230.0f));
		text1[3].setPosition(Vector2f(140.0f, 280.0f));


		//username

		Text inputPrompt, playerName;
		name = "";
		inputPrompt.setString("Enter your name: ");

		inputPrompt.setFont(font);
		playerName.setFont(font);

		inputPrompt.setFillColor(Color::Black);
		playerName.setFillColor(Color::Black);
		inputPrompt.setStyle(Text::Bold);
		playerName.setStyle(Text::Bold);


		inputPrompt.setCharacterSize(50);

		inputPrompt.setPosition(Vector2f(45.0f, 80.0f));
		playerName.setPosition(Vector2f(140.0f, 180.0f));








		while (Minesweeper.isOpen())
		{
			Event event;
			while (Minesweeper.pollEvent(event))
			{
				if (event.type == event.Closed)
				{
					Minesweeper.close();
				}

				if (counter == 3)
					game(difficulty);

				if (Keyboard::isKeyPressed(Keyboard::Key::Space) && counter == 0)
				{
					counter++;
				}


				switch (event.type)
				{
				case Event::TextEntered:
				{
					if (counter == 2)
					{
						if (event.text.unicode == 8)
						{
							if (!name.empty())
								name.erase(name.size() - 1, 1);
						}
						else if ((event.text.unicode >= 65 && event.text.unicode <= 122))
						{
							name += (char)event.text.unicode;
						}

						playerName.setString(name);

						if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 0)
						{
							counter++;
						}
					}
				}
				}



			}


			Minesweeper.clear();


			if (counter == 0)
			{
				Minesweeper.draw(open);
				Minesweeper.draw(text);
			}
			else if (counter == 1)
			{

				Minesweeper.draw(backgroundtexture_rect);
				for (int i = 0; i < 4; i++)
				{
					Minesweeper.draw(text1[i]);
				}



				if (Keyboard::isKeyPressed(Keyboard::Key::Num1) || Keyboard::isKeyPressed(Keyboard::Key::Numpad1))
				{
					difficulty = 1;
					counter++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Key::Num2) || Keyboard::isKeyPressed(Keyboard::Key::Numpad2))
				{
					difficulty = 2;
					counter++;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Key::Num3) || Keyboard::isKeyPressed(Keyboard::Key::Numpad3))
				{
					difficulty = 3;
					counter++;
				}
			}
			else if (counter == 2)
			{
				Minesweeper.draw(backgroundtexture_rect);
				Minesweeper.draw(inputPrompt);
				Minesweeper.draw(playerName);
			}

			Minesweeper.display();
		}
	}
}