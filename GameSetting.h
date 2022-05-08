#ifndef __GAMESETTING__
#define __GAMESETTING__

#include <windows.h>  //���ڴ������ú͹�����ã���������
#include <cstdlib>  //����sprintf��ʹ��system
#include <cstdio>  //����system
#include <ctime>  //����clock_t()
#include <queue>  //���ڴ洢��
#include <map>  //���ڴ洢��
#include <iostream>
#include <conio.h>  //����_getch()
#include <thread>  //���߳�


/*��ʼ����Ϸ*/
//���ô��ڴ�С
void SetWindowSize(void);
//���ع��
void HideCursor(void);
//���� SetWindowSize��HideCursor ����������Ϸ���г�ʼ��
void InitialGame(void);


/*��ʼ��һ����Ϸ*/
//��ӡ��������Ϣ
void MainInterface(void);
//ѡ���Ѷ�
int ChoiceDifficulty(void);
//��ʼ����Ϸ�߽�
void BuildBoundary(void);
//��ʼ����Ϸ�Ҳ���Ϣ
void InterfaceInformation(void);
//���� MainInterface��ChoiceDifficulty��BuildBoundary��InterfaceInformation ��������ÿ����Ϸ���г�ʼ��
int InitialInterface(void);


/*��ʼ��һ����Ϸ�еĸ�����Ϣ*/
//ʵ�����ߡ�������ʱ����Ϣ
void InstantiateInfo(void);
//��ʼ���ߡ�������ʱ����Ϣ
void InitialInfo(void);
//��ʼ��������ʳ��������ж���Ϣ
void InitialJudge(void);
//��ʼ��ʳ��
void InitialFood(void);


/*��Ϸ��������*/
//������ƶ���x,yλ��
void GotoXY(int x, int y);
//�÷���������
void GradeUpSound(void);


/*��Ϸ������������Ϸ��Ϣ*/
//��Ϸ�˳�����ӡ������Ϣ
void EndOfMsg(void);
//�����ж���Ϣ
void ResetJudge(void);
//���÷�������Ϸ�����жϡ������ж�
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