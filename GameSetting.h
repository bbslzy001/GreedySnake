#ifndef __GAMESETTING__
#define __GAMESETTING__



#include <windows.h>  //用于窗口设置和光标设置，设置振铃
#include <cstdlib>  //用于sprintf、使用system
#include <cstdio>  //用于system
#include <ctime>  //用于clock_t()
#include <queue>  //用于存储蛇
#include <map>  //用于存储蛇
#include <iostream>
#include <conio.h>  //用于_getch()
#include <thread>  //多线程



/*初始化游戏*/

//设置窗口大小，由 InitialGame() 函数调用
void SetWindowSize(void);

//隐藏光标，由 InitialGame() 函数调用
void HideCursor(void);

//对游戏进行初始化，调用 SetWindowSize()、HideCursor() 函数
void InitialGame(void);

//实例化游戏难度、时间、分数、蛇信息
void InstantiateData(void);



/*初始化一局游戏*/

//初始化游戏边界，调用 GotoXY() 函数，由 Initial() 函数调用
void BuildBoundary(void);

//初始化游戏右侧信息，调用 GotoXY()、GetDifficulty() 函数，由 Initial() 函数调用
void InterfaceInfo(void);

//初始化对蛇与食物坐标的判断信息，由 Initial() 函数调用
void InitialJudge(void);

//初始化食物，调用 GotoXY() 函数，由 Initial() 函数调用
void InitialFood(void);

//对每局游戏进行初始化，
//调用 ChoiceDifficultyInterface()、ChoiceDifficulty()、
//BuildBoundary()、InterfaceInfo()、
//InitialStatus()、InitialJudge()、InitialGrade()、InitialTime()、InitialSnake()、InitialFood() 函数
//由 main() 函数调用
void Initial(void);



/*游戏运行所需*/

//将光标移动到x,y位置
void GotoXY(int x, int y);

//得分声音反馈，由 UpdateGrade() 函数调用
void GradeUpSound(void);



/*游戏结束，重置游戏信息*/

//打印结束信息，调用 GetGrade()、GetTime()、GotoXY() 函数，由 main() 函数调用
void EndOfMsg(void);

//重置坐标信息，由 Reset() 函数调用
void ResetJudge(void);

//重置游戏后台信息，调用 ResetGrade()、ResetJudge()、ResetDifficulty() 函数
void Reset(void);



class Status
{
private:
	bool is_restart_ = false;
	bool is_run_ = false;
public:
	//初始化游戏状态，由 Initial() 函数调用
	void InitialStatus(void);

	//获取游戏运行状态，由 main() 函数调用
	bool GetIsRun(void);

	//获取重新开始状态，由 main() 函数调用
	bool GetIsRestart(void);

	//设置游戏运行状态，由 GameOver() 函数调用
	void SetIsRun(bool status);

	//判断是否重新开始，由 main() 函数调用
	void IfRestart(void);
};



class Difficulty
{
private:
	enum { kXEASY = 90, kXCOMMON = 60, kXDIFFICULT = 30 };
	enum { kYEASY = 180, kYCOMMON = 120, kYDIFFICULT = 60 };
	char difficulty_choice_ = '0';
public:
	//打印难度选择界面，调用 GotoXY() 函数，由 InitialInterface() 函数调用
	void ChoiceDifficultyInterface(void);

	//选择难度，由 InitialInterface() 函数调用
	void ChoiceDifficulty(void);

	//获取游戏速度，由 main() 函数调用
	int GetSpeed(void);

	//获取游戏难度，由 InterfaceInfo() 函数调用
	char GetDifficultyChoice(void);

	//重置游戏难度，由 Reset() 函数调用
	void ResetDifficulty(void);
};



class Time
{
private:
	clock_t begin_time_ = 0;
	clock_t end_time_ = 0;
	int current_time_ = 0;
public:
	//初始化时间，调用 GotoXY() 函数，由 Initial() 函数调用
	void InitialTime(void);

	//刷新时间，调用 GotoXY() 函数，由 main() 函数调用
	void UpdateTime(void);

	//获取本次时间，由 EndOfMsg() 函数调用
	int GetTime(void);
};



class Grade
{
private:
	int current_score_ = 0;
	int best_score_ = 0;
public:
	//初始化分数，调用 GotoXY() 函数，由 Initial() 函数调用
	void InitialGrade(void);

	//更新分数，调用 GotoXY() 函数，由 UpdateSnake() 函数调用
	void UpdateGrade(void);

	//重置当前分数，由 Reset() 函数调用
	void ResetGrade(void);

	//获取本次分数，由 EndOfMsg() 函数调用
	int GetGrade(void);
};



class Snake
{
private:
	std::queue<std::pair<int, int> > snake;
	enum { kUP = 1, kDOWN = 2, kLEFT = 3, kRIGHT = 4 };
	int snake_status_ = kRIGHT;
	char input_char_ = '0';
public:
	//判断是否为食物，调用 InitailFood() 函数，由 UpdateSnake() 函数调用
	bool JudgeFood(int x, int y);

	//判断是否为墙或身子，由 UpdateSnake() 函数调用
	bool JudgeWallOrBody(int x, int y);

	//初始化蛇头方向，由 InitialSnake() 函数调用
	void InitialSnakeDirection(void);

	//初始化蛇头位置，由 InitialSnake() 函数调用
	int* InitialSnakeXY(void);

	//初始化蛇，调用 GotoXY()、InitialSnakeDirection()、InitialSnakeXY() 函数，由 Initial() 函数调用
	void InitialSnake(void);

	//更新蛇头方向，由 main() 函数调用
	void UpdateSnakeDirection(void);

	//判断蛇头下一个位置并更新蛇，调用 JudgeFood()、JudgeWallOrBody() 函数，由 main() 函数调用
	void UpdateSnake(void);

	//判断蛇头方向是否为水平方向
	bool IsXDirection(void);

	//游戏结束，由 UpdateSnake() 函数调用
	void GameOver(void);
};



#endif