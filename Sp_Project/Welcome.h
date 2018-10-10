#pragma once

using namespace std;
using namespace sf;

namespace WELCOME
{
	int welcomegamebox()
	{
		RenderWindow window(VideoMode(1360, 800), "Game Box", Style::Close);

		RectangleShape snack_rect(Vector2f(700.0f, 800.0f));
		RectangleShape minesweeper_rect(Vector2f(700.0f, 400.0f));
		RectangleShape connect4_rect(Vector2f(700.0f, 400.0f));

		Texture snack_recttexture, minesweeper_recttexture, connect4_recttexture;

		snack_rect.setPosition(0.0f, 0.0f);	
		snack_recttexture.loadFromFile("welcome/snakes.jpg");
		snack_recttexture.setSmooth(true);
		snack_rect.setTexture(&snack_recttexture);

		minesweeper_rect.setPosition(700.0f, 0.0f);
		minesweeper_recttexture.loadFromFile("welcome/mines.png");
		minesweeper_rect.setTexture(&minesweeper_recttexture);

		connect4_rect.setPosition(700.0f, 400.0f);
		connect4_recttexture.loadFromFile("welcome/connect.jpg");
		connect4_rect.setTexture(&connect4_recttexture);


		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == event.Closed)
				{
					window.close();
				}
				if (event.type == event.MouseButtonPressed)
					if (event.mouseButton.x >= snack_rect.getPosition().x && event.mouseButton.x <= snack_rect.getPosition().x + snack_rect.getSize().x && event.mouseButton.y >= snack_rect.getPosition().y && event.mouseButton.y <= snack_rect.getPosition().y + snack_rect.getSize().y)
					{
						cout << "snake and ladder" << endl;
						cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
						window.close();
						return 1;
					}
					else if (event.mouseButton.x >= minesweeper_rect.getPosition().x && event.mouseButton.x <= minesweeper_rect.getPosition().x + minesweeper_rect.getSize().x && event.mouseButton.y >= minesweeper_rect.getPosition().y && event.mouseButton.y <= minesweeper_rect.getPosition().y + minesweeper_rect.getSize().y)
					{
						cout << "mine sweeeper" << endl;
						cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
						window.close();
						return 2;
					}
					else if (event.mouseButton.x >= connect4_rect.getPosition().x && event.mouseButton.x <= connect4_rect.getPosition().x + connect4_rect.getSize().x && event.mouseButton.y >= connect4_rect.getPosition().y && event.mouseButton.y <= connect4_rect.getPosition().y + connect4_rect.getSize().y)
					{
						cout << "connect 4 " << endl;
						cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
						window.close();
						return 3;
					}
			}
			window.draw(snack_rect);
			window.draw(minesweeper_rect);
			window.draw(connect4_rect);

			window.display();
		}
	}

	int welcome()
	{
		return welcomegamebox();
	}
}