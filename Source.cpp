#include<iostream>
#include<ctime>
#include<sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
void menu(RenderWindow& game) // функция для главного меню игры, которая принимает аргументы саомй игры
{
	// создание и загрузка файла для звука
	SoundBuffer popBuffer;
	popBuffer.loadFromFile("resources/game_start.wav");
	Sound pop(popBuffer);
	pop.play();

	SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("resources/click.wav");
	Sound click(clickBuffer);
	
	Text title, menu1, menu2, menu3, theme, esc;

	// создание шрифтов для текста
	Font font1;
	font1.loadFromFile("resources/Pixel-Regular.ttf");
	Font font2;
	font2.loadFromFile("resources/Pixeland.ttf");

	// назначение нужных параметров для переменных с текстом
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

	// расстановка текстовых переменных по координатам
	title.setPosition(0, 0);
	theme.setPosition(100, 100);
	esc.setPosition(0, 0);
	menu1.setPosition(150, 200);
	menu2.setPosition(150, 300);

	while (isMenu)// пока меню открыто(true)
	{
		// заполнить текст белым цветом
		menu1.setFillColor(Color::White);
		menu2.setFillColor(Color::White);
		title.setFillColor(Color::White);
		theme.setFillColor(Color::White);
		esc.setFillColor(Color::White);

		menuNum = 0;
		game.clear(Color::Black); // черный фон меню

		if (IntRect(150, 200, 130, 45).contains(Mouse::getPosition(game))) // если курсор попадает на нужную область, где находится текст
		{
			menu1.setFillColor(Color::Green); menuNum = 1; // смена цвета текста и присвоение первой строчки меню определенное значение (menuNum)
		}
		if (IntRect(150, 300, 130, 45).contains(Mouse::getPosition(game))) 
		{menu2.setFillColor(Color::Green); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left)) // если нажата левая кнопка мыши
		{
			click.play(); // проиграть звук
			if (menuNum == 1) 
				isMenu = false; // выход из меню и попадание в игру
			if (menuNum == 2) { game.close(); isMenu = false; } // выход из игры
		}

		// отрисовка текстовых переменных в окне игры
		game.draw(title);
		game.draw(menu1);
		game.draw(menu2);

		game.display();
	}
}
bool startGame() // функция самой игры
{
	srand(time(0));
	RenderWindow game(VideoMode(400, 600), "Minesweeper"); // создание окна игры
	menu(game); // вызов меню

	// создание таймера
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

	// загрузка текстуры с клетками
	Texture texture;
	texture.loadFromFile("resources/tiles.jpg");
	// создание спрайта из этой текстуры
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

	int width = 32; // размер спрайта (32 пикселя)
	int grid[12][12];  /*сетка, где и будет происходить весь процесс, она состоит из 12 спрайтов: 
	пустая клетка; клетка с расположением мин вокруг нее (от 1 до 8 мин); мина, закрытая клетка и флажок*/
	int sgrid[12][12]; // показ самой сетки

	for (int i = 1; i <= 10; i++) // создаем сетку 10x10
		for (int j = 1; j <= 10; j++)
		{
			sgrid[i][j] = 10; // заполняем сетку закрытыми клетками
			if (rand() % 5 == 0)
				grid[i][j] = 9; // случайным образом заполняем разные клетки минами
			else
				grid[i][j] = 0; // иначе пустой клеткой
		}

	for (int i = 1; i <= 10; i++)// пробегая по сетке
		for (int j = 1; j <= 10; j++) 
		{
			int a = 0; // вводим переменную, которая в дальнейшем примет значение, соответствующее количеству мин вокруг неё
			if (grid[i][j] == 9)
				continue;
			if (grid[i + 1][j] == 9) /*если присутствует мина вокруг клетки, то к a прибавляем единицу, 
				то есть переменная а стало теперь не пустой клеткой, а клеткой с цифрой 1 и так далее*/
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

			grid[i][j] = a; // присваиваем нашей клетке то значение, которая получила переменная a из цикла
		}

	while (game.isOpen()) // пока открыта окно игры
	{
		Vector2i pos = Mouse::getPosition(game); // добавление мышки в игру
		// задаем координаты мышке
		int x = pos.x / width;
		int y = pos.y / width;

		Event event;
		while (game.pollEvent(event))
		{
			if (event.type == Event::Closed) // возможность закрыть игру с помощью крестика в углу окна
				game.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) // если нажата левая кнопка мыши
				{
					sgrid[x][y] = grid[x][y]; // закрытая клетка открывается и она заменяется на клетку из массива grid, где мы ей присваивали значение из цикла
					// проигрывание звука
					click.setVolume(30);
					click.play();
				}
				else
					if (event.key.code == Mouse::Right) // если нажата правая кнопка мыши
					{
						sgrid[x][y] = 11; // ставим флажок
						flag.setVolume(30);
						flag.play();
					}

			if (Keyboard::isKeyPressed(Keyboard::F1)) { return true; } // перезапуск игры
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; } // выход из игры
			if (Keyboard::isKeyPressed(Keyboard::F2)) { menu(game); } // выход в меню
		}

		game.clear(Color(0, 0, 0)); // черный фон игры
		// создание таймера
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
				if (sgrid[x][y] == 9) // если игрок нажал на клетку с миной
				{
					sgrid[i][j] = grid[i][j]; // игрок проигрывает и раскрываются все клетки
				}
				s.setTextureRect(IntRect(sgrid[i][j] * width, 0, width, width));
				s.setPosition(i * width, j * width); // расположение спрайтов
				// отрисовка спрайта
				game.draw(s);
			}
		
		// отрисовка текста в игре
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
void gameRunning() // функция, которая перезагружает игру
{
	if (startGame()) // если startGame() == true, то вызываем функция gameRunning(), которая опять вызывает startGame()
	{
		gameRunning();
	}
}
int main()
{
	gameRunning(); // запуск игры
	return 0;
}