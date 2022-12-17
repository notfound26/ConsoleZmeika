
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


/// <summary>Ширина</summary>
const int play_field_width = 20;
/// <summary>Высота</summary>
const int play_field_height = 20;
/// <summary>Размер поля</summary>
const int size_of_field = play_field_width * play_field_height;

/// <summary>Поле</summary>
int play_field[size_of_field];

/// <summary>Координата змейки по x</summary>

int head_x_position;
/// <summary>Координата змейки по y</summary>
int head_y_position;
/// <summary>Направление движения змейки / 1-Вверх;2-Вправо;3-Вниз;4-Влево</summary>
int direction = 1;
/// <summary>Длина змейки</summary>
int snake_length = 3;
/// <summary>Счет</summary>
int score = 0;

/// <summary>Игра запущена</summary>
bool game_running;

/// <summary>Уровень сложности</summary>
int difficulty;

void run();
void print_play_field();
void initialize_play_field();
void move_snake(int x, int y);
void update_field();
void generate_food();
char get_play_field_value(int value);

/// <summary>Точка входа в приложение</summary>
int main()
{
	cout << "Choose difficulty: " << endl << endl;
	cout << "1 - Easy" << endl;
	cout << "2 - Medium" << endl;
	cout << "3 - Hard" << endl;
	cout << "Enter option ( 1 - 3 ): "; cin >> difficulty; cout << endl;
	cout << "Loading..." << endl;

	run();
	return 0;
}

/// <summary>Запуск игры</summary>
void run()
{
	// создание поля
	initialize_play_field();
	game_running = true;
	while (game_running)
	{

		if (_kbhit())
		{
			char key = _getch();
			switch (key) {
			case 'w':
				if (direction != 3) direction = 1;
				break;
			case 'd':
				if (direction != 4) direction = 2;
				break;
			case 's':
				if (direction != 1) direction = 3;
				break;
			case 'a':
				if (direction != 2) direction = 4;
				break;
			}


		}
		// обновить поле
		update_field();
		system("cls");
		// вывод поля
		print_play_field();
		switch (difficulty)
		{
		case 1: Sleep(500);
			break;
		case 2: Sleep(400);
			break;
		case 3: Sleep(200);
			break;
		}
	}

	// конец игры
	cout << "!Game over!" << endl << "Your score is: " << score;

	cin.ignore();
}

/// <summary>Движение змейки</summary>
/// <param name="x">Горизонтальное смещение</param>
/// <param name="y">Вертикальное смещение</param>
void move_snake(int x, int y) {
	//новые координаты головы
	int newx = head_x_position + x;
	int newy = head_y_position + y;

	// проверка на еду
	if (play_field[newx + newy * play_field_width] == -2)
	{
		// удлинение 
		snake_length++;
		score++;
		// создание новой еды
		generate_food();
	}

	// проверка на стену и собственный хвост
	else if (play_field[newx + newy * play_field_width] != 0)
	{
		game_running = false;
	}

	// +1 для назначенного размера змеи
	head_x_position = newx;
	head_y_position = newy;
	play_field[head_x_position + head_y_position * play_field_width] = snake_length + 1;

}


/// <summary>Генерация еды</summary>
void generate_food() {
	int x = 0;
	int y = 0;
	do
	{

		srand(time(NULL));
		x = rand() % (play_field_width - 2) + 1;
		y = rand() % (play_field_height - 2) + 1;

		// проверка на свободность поля
	} while (play_field[x + y * play_field_width] != 0);

	// положить еду
	play_field[x + y * play_field_width] = -2;
}

/// <summary>Обновление игрового поля</summary>
void update_field()
{
	// движение
	switch (direction) {
	case 1: move_snake(-1, 0);     //1:вверх
		break;
	case 2: move_snake(0, 1);	//2:вправо		
		break;
	case 3: move_snake(1, 0);	//3:вниз
		break;
	case 4: move_snake(0, -1);		//4:влево
		break;
	}

	for (int i = 0; i < size_of_field; i++)
	{
		if (play_field[i] > 0) play_field[i]--;
	}

}

/// <summary>Создание карты</summary>
void initialize_play_field()
{
	// начало змеи в середине поля (play_field[210])
	head_x_position = play_field_width / 2;
	head_y_position = play_field_height / 2;
	play_field[head_x_position + head_y_position * play_field_height] = 1;

	// верхняя и нижняя стена
	for (int x = 0; x < play_field_width; x++)
	{    //берет play_field[0] и play_field [380] и одновременно заполняет 'X' и тд, до play_field[19] и play_field [399], т.е верхняя и нижняя строка
		play_field[x] = -1;
		play_field[x + (play_field_height - 1) * play_field_width] = -1;
	}

	// левая и правая стенка
	for (int y = 0; y < play_field_height; y++)
	{    //тоже самое но берет play_field[0] и play_field[19], затем play_field[20] и play_field[39] т.е. пропуская 18 "игровых полей" с каждой итерацией
		play_field[0 + y * play_field_height] = -1;
		play_field[(play_field_width - 1) + y * play_field_width] = -1;
	}

	// создание изначальной еды
	generate_food();
}

/// <summary>Вывод поля</summary>
void print_play_field()
{
	for (int x = 0; x < play_field_width; x++)
	{
		for (int y = 0; y < play_field_height; y++)
		{
			// значение в проверяемых x,y координатах
			std::cout << get_play_field_value(play_field[x + y * play_field_width]);
		}
		// вывод в виде поля
		cout << endl;

	}
}
/// <summary>Функция вывода игрового поля</summary>
/// <param name="value">Значение</param>
char get_play_field_value(int value)
{
	// змейка
	if (value > 0) return 'o';

	switch (value) {
		// стена
	case -1: return 'O';
		// еда
	case -2: return '@';
	}
}