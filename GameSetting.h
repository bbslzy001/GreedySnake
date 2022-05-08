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
//设置窗口大小
void SetWindowSize(void);
//隐藏光标
void HideCursor(void);
//调用 SetWindowSize、HideCursor 函数，对游戏进行初始化
void InitialGame(void);


/*初始化一局游戏*/
//打印主界面信息
void MainInterface(void);
//选择难度
int ChoiceDifficulty(void);
//初始化游戏边界
void BuildBoundary(void);
//初始化游戏右侧信息
void InterfaceInformation(void);
//调用 MainInterface、ChoiceDifficulty、BuildBoundary、InterfaceInformation 函数，对每局游戏进行初始化
int InitialInterface(void);


/*初始化一局游戏中的各类信息*/
//实例化蛇、分数、时间信息
void InstantiateInfo(void);
//初始化蛇、分数、时间信息
void InitialInfo(void);
//初始化对蛇与食物坐标的判断信息
void InitialJudge(void);
//初始化食物
void InitialFood(void);


/*游戏运行所需*/
//将光标移动到x,y位置
void GotoXY(int x, int y);
//得分声音反馈
void GradeUpSound(void);


/*游戏结束，重置游戏信息*/
//游戏退出，打印结束信息
void EndOfMsg(void);
//重置判断信息
void ResetJudge(void);
//重置分数、游戏结束判断、坐标判断
void Reset(void);


class Time
{
private:
	clock_t begin_time_ = 0;
	clock_t end_time_ = 0;
	int current_time_ = 0;
public:
	void InitialTime(void);
	void UpdateTime(void);
	int GetTime(void);
};

class Grade
{
private:
	int current_score_ = 0;
	int best_score_ = 0;
public:
	void InitialGrade(void);
	void UpdateGrade(void);
	void ResetGrade(void);
	int GetGrade(void);
};

class Snake
{
private:
	std::queue<std::pair<int, int> > snake;
	enum { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
	int snake_status_ = RIGHT;
	char input_char_ = '0';
public:
	bool JudgeFood(int x, int y);
	bool JudgeWallOrBody(int x, int y);
	void InitialSnake(void);
	void UpdateSnake(void);
	void UpdateSnakeByStatus(void);
	void GameOver(void);
	void SnakeStatus(void);
};

#endif