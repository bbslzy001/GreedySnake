#define _CRT_SECURE_NO_WARNINGS

#include "GameSetting.h"

using namespace std;

Status* game_status;
Difficulty* game_difficulty;
Time* game_time;
Judge* game_judge;
Snake* game_snake;

int main(void)
{
	InitialGame();
	InstantiateData();

	do
	{
		Initial();

		while (game_status->GetIsRun())
		{
			game_time->UpdateTime();
			if (_kbhit()) game_snake->UpdateSnakeDirection();
			game_snake->UpdateSnake();
			Sleep(game_difficulty->GetSpeed());
		}

		EndOfMsg();
		game_judge->ResetJudge();
		game_status->IfRestart();
	} while (game_status->GetIsRestart());

	system("cls");

	return 0;
}