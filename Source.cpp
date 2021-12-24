#include<iostream>
#include<ctime>
#include<sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
void menu(RenderWindow& game) // ������� ��� �������� ���� ����, ������� ��������� ��������� ����� ����
{
	// �������� � �������� ����� ��� �����
	SoundBuffer popBuffer;
	popBuffer.loadFromFile("resources/game_start.wav");
	Sound pop(popBuffer);
	pop.play();

	SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("resources/click.wav");
	Sound click(clickBuffer);
	
	Text title, menu1, menu2, menu3, theme, esc;

	// �������� ������� ��� ������
	Font font1;
	font1.loadFromFile("resources/Pixel-Regular.ttf");
	Font font2;
	font2.loadFromFile("resources/Pixeland.ttf");

	// ���������� ������ ���������� ��� ���������� � �������
	title.setFont(font1);
	title.setString("Minesweeper");
	title.setCharacterSize(45);

	theme.setFont(font2);
	theme.setString("CHANGE THEME");
	theme.setCharacterSize(40);

	esc.setFont(font2);
	esc.setString("Press ESC to return");
	esc.setCharacterSize(40);

	menu1.setFont(font2);
	menu1.setString("START GAME");
	menu1.setCharacterSize(40);

	menu2.setFont(font2);
	menu2.setString("EXIT");
	menu2.setCharacterSize(40);
	
	bool isMenu = true;
	int menuNum = 0;

	// ����������� ��������� ���������� �� �����������
	title.setPosition(0, 0);
	theme.setPosition(100, 100);
	esc.setPosition(0, 0);
	menu1.setPosition(150, 200);
	menu2.setPosition(150, 300);

	while (isMenu)// ���� ���� �������(true)
	{
		// ��������� ����� ����� ������
		menu1.setFillColor(Color::White);
		menu2.setFillColor(Color::White);
		title.setFillColor(Color::White);
		theme.setFillColor(Color::White);
		esc.setFillColor(Color::White);

		menuNum = 0;
		game.clear(Color::Black); // ������ ��� ����

		if (IntRect(150, 200, 130, 45).contains(Mouse::getPosition(game))) // ���� ������ �������� �� ������ �������, ��� ��������� �����
		{
			menu1.setFillColor(Color::Green); menuNum = 1; // ����� ����� ������ � ���������� ������ ������� ���� ������������ �������� (menuNum)
		}
		if (IntRect(150, 300, 130, 45).contains(Mouse::getPosition(game))) 
		{menu2.setFillColor(Color::Green); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left)) // ���� ������ ����� ������ ����
		{
			click.play(); // ��������� ����
			if (menuNum == 1) 
				isMenu = false; // ����� �� ���� � ��������� � ����
			if (menuNum == 2) { game.close(); isMenu = false; } // ����� �� ����
		}

		// ��������� ��������� ���������� � ���� ����
		game.draw(title);
		game.draw(menu1);
		game.draw(menu2);

		game.display();
	}
}
bool startGame() // ������� ����� ����
{
	srand(time(0));
	RenderWindow game(VideoMode(400, 600), "Minesweeper"); // �������� ���� ����
	menu(game); // ����� ����

	// �������� �������
	Clock clock;
	Time time;
	stringstream smth;
	int sec = 0;
	int min = 0;
	int hour = 0;

	Font font1;
	font1.loadFromFile("resources/Pixel-Regular.ttf");
	Font font2;
	font2.loadFromFile("resources/Pixeland.ttf");

	Text headline;
	headline.setFont(font1);
	headline.setString("Minesweeper");
	headline.setCharacterSize(30);

	Text LBM;
	LBM.setFont(font2);
	LBM.setString("LBM = Open cell");
	LBM.setCharacterSize(25);
	LBM.setPosition(30, 400);

	Text RBM;
	RBM.setFont(font2);
	RBM.setString("RBM = Set flag");
	RBM.setCharacterSize(25);
	RBM.setPosition(30, 420);

	Text Esc;
	Esc.setFont(font2);
	Esc.setString("Escape = Exit the game");
	Esc.setCharacterSize(25);
	Esc.setPosition(30, 440);

	Text Restart;
	Restart.setFont(font2);
	Restart.setString("F1 = Reset");
	Restart.setCharacterSize(25);
	Restart.setPosition(30, 460);

	Text Return;
	Return.setFont(font2);
	Return.setString("F2 = Return to menu");
	Return.setCharacterSize(25);
	Return.setPosition(30, 480);

	Text timer;
	timer.setFont(font2);
	timer.setPosition(200, 500);
	timer.setCharacterSize(50);

	// �������� �������� � ��������
	Texture texture;
	texture.loadFromFile("resources/tiles.jpg");
	// �������� ������� �� ���� ��������
	Sprite s(texture);


	SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("resources/click.wav");
	Sound click(clickBuffer);

	SoundBuffer flagBuffer;
	flagBuffer.loadFromFile("resources/flag.wav");
	Sound flag(flagBuffer);

	SoundBuffer gamestartBuffer;
	gamestartBuffer.loadFromFile("resources/game_start.wav");
	Sound gamestart(gamestartBuffer);
	gamestart.play();

	int width = 32; // ������ ������� (32 �������)
	int grid[12][12];  /*�����, ��� � ����� ����������� ���� �������, ��� ������� �� 12 ��������: 
	������ ������; ������ � ������������� ��� ������ ��� (�� 1 �� 8 ���); ����, �������� ������ � ������*/
	int sgrid[12][12]; // ����� ����� �����

	for (int i = 1; i <= 10; i++) // ������� ����� 10x10
		for (int j = 1; j <= 10; j++)
		{
			sgrid[i][j] = 10; // ��������� ����� ��������� ��������
			if (rand() % 5 == 0)
				grid[i][j] = 9; // ��������� ������� ��������� ������ ������ ������
			else
				grid[i][j] = 0; // ����� ������ �������
		}

	for (int i = 1; i <= 10; i++)// �������� �� �����
		for (int j = 1; j <= 10; j++) 
		{
			int a = 0; // ������ ����������, ������� � ���������� ������ ��������, ��������������� ���������� ��� ������ ��
			if (grid[i][j] == 9)
				continue;
			if (grid[i + 1][j] == 9) /*���� ������������ ���� ������ ������, �� � a ���������� �������, 
				�� ���� ���������� � ����� ������ �� ������ �������, � ������� � ������ 1 � ��� �����*/
				a++;
			if (grid[i][j + 1] == 9)
				a++;
			if (grid[i - 1][j] == 9)
				a++;
			if (grid[i][j - 1] == 9)
				a++;
			if (grid[i + 1][j + 1] == 9)
				a++;
			if (grid[i - 1][j - 1] == 9)
				a++;
			if (grid[i + 1][j - 1] == 9)
				a++;
			if (grid[i - 1][j + 1] == 9)
				a++;

			grid[i][j] = a; // ����������� ����� ������ �� ��������, ������� �������� ���������� a �� �����
		}

	while (game.isOpen()) // ���� ������� ���� ����
	{
		Vector2i pos = Mouse::getPosition(game); // ���������� ����� � ����
		// ������ ���������� �����
		int x = pos.x / width;
		int y = pos.y / width;

		Event event;
		while (game.pollEvent(event))
		{
			if (event.type == Event::Closed) // ����������� ������� ���� � ������� �������� � ���� ����
				game.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) // ���� ������ ����� ������ ����
				{
					sgrid[x][y] = grid[x][y]; // �������� ������ ����������� � ��� ���������� �� ������ �� ������� grid, ��� �� �� ����������� �������� �� �����
					// ������������ �����
					click.setVolume(30);
					click.play();
				}
				else
					if (event.key.code == Mouse::Right) // ���� ������ ������ ������ ����
					{
						sgrid[x][y] = 11; // ������ ������
						flag.setVolume(30);
						flag.play();
					}

			if (Keyboard::isKeyPressed(Keyboard::F1)) { return true; } // ���������� ����
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; } // ����� �� ����
			if (Keyboard::isKeyPressed(Keyboard::F2)) { menu(game); } // ����� � ����
		}

		game.clear(Color(0, 0, 0)); // ������ ��� ����
		// �������� �������
		smth.str("");

		time = clock.getElapsedTime();
		sec = time.asSeconds();
		min = sec / 3600;
		hour = (sec -(min * 3600)) / 60;
		sec = sec - (min * 3600 + hour * 60);

		if (min < 10)
		{
			smth << "0" << min;
		}
		else
		{
			smth << min;
		}

		if (hour < 10)
		{
			smth << ":" << "0" << hour;
		}
		else
		{
			smth << ":" << hour;
		}
		if (sec < 10)
		{
			smth << ":" << "0" << sec;
		}
		else
		{
			smth << ":" << sec;
		}

		timer.setString(smth.str());
		game.draw(timer);

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				if (sgrid[x][y] == 9) // ���� ����� ����� �� ������ � �����
				{
					sgrid[i][j] = grid[i][j]; // ����� ����������� � ������������ ��� ������
				}
				s.setTextureRect(IntRect(sgrid[i][j] * width, 0, width, width));
				s.setPosition(i * width, j * width); // ������������ ��������
				// ��������� �������
				game.draw(s);
			}
		
		// ��������� ������ � ����
		game.draw(headline);
		game.draw(LBM);
		game.draw(RBM);
		game.draw(Esc);
		game.draw(Restart);
		game.draw(Return);
		game.display();
		
	}
	system("pause");
	return 0;
}
void gameRunning() // �������, ������� ������������� ����
{
	if (startGame()) // ���� startGame() == true, �� �������� ������� gameRunning(), ������� ����� �������� startGame()
	{
		gameRunning();
	}
}
int main()
{
	gameRunning(); // ������ ����
	return 0;
}