#define _CRT_SECURE_NO_WARNINGS

#include "GameSetting.h"

using namespace std;

bool game_judge = true;

Grade* game_grade;
Time* game_time;
Snake* game_snake;

int main(void)
{
	InitialGame();
	InstantiateInfo();

	//用于判断是否重新开始
	char restart = '0';

	//重新开始
	do
	{
		//重新开始清屏
		if (restart == '1')
		{
			system("cls");
			restart = '0';
		}

		/*游戏各项初始化*/
		//定义本局游戏速度
		int speed = InitialInterface();
		InitialJudge();
		InitialInfo();
		InitialFood();

		//游戏运行
		while (game_judge)
		{
			game_time->UpdateTime();
			if (_kbhit()) game_snake->SnakeStatus();
			game_snake->UpdateSnake();
			Sleep(speed);
		}

		EndOfMsg();
		ResetJudge();
		Reset();

		while (restart != '1' && restart != '2') restart = _getch();
	} while (restart == '1');

	system("cls");

	return 0;
}