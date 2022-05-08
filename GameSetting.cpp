#include "Constant.h"
#include "GameSetting.h"

using namespace std;

//
static char choice = '0';
//
static int** judge;
//��Ϸ�����ж�
extern bool game_judge;

/*����ȫ�ֶ���ָ��*/
extern Grade* game_grade;
extern Time* game_time;
extern Snake* game_snake;

void SetWindowSize(void)
{
	char str[64];
	sprintf_s(str, "mode con cols=%d lines=%d", kWindowWidth, kWindowHeight);
	system(str);
}

void HideCursor(void)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);  //��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false;  //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);  //���ÿ���̨���״̬
}

void InitialGame(void)
{
	SetWindowSize();
	HideCursor();
}

void MainInterface(void)
{
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 7);
	cout << "��ѡ����Ϸ�Ѷȣ�" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 5);
	cout << "1)����" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 3);
	cout << "2)����" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 1);
	cout << "3)����" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 + 1);
	cout << "����������ѡ��-> ";
}


int ChoiceDifficulty(void)
{
	while (1)
	{
		choice = _getch();
		if (choice == '1') return 400;
		if (choice == '2') return 200;
		if (choice == '3') return 80;
	}
}

void BuildBoundary(void)
{
	for (int i = 0; i < kBorderWidthNum; ++i) printf("\033[47;37m��\033[0m");  //�÷��ſ��ռ2�߶�ռ1
	cout << endl;
	for (int i = 1; i <= kSceneHeight; ++i)
	{
		printf("\033[47;37m��\033[0m");
		GotoXY(kInfoboxBorderX, i);
		printf("\033[40;37m��\033[0m");
		//����ÿ����0~129��130��λ�ã�Ϊ�����Ŵ�ӡ��ÿ��ĩβ���轫�������128,��128��129����һ����
		GotoXY(kWindowWidth - 2, i);
		printf("\033[47;37m��\033[0m\n");
	}
	for (int i = 0; i < kBorderWidthNum; ++i) printf("\033[47;37m��\033[0m");
	//��0~13��14�ĸ߶ȷֳ�һ��
	GotoXY(kInfoboxBorderX + 2, 13);
	for (int i = 0; i < kBorderWidthNum - kBorderHeightNum - 1; ++i) printf("\033[40;37m��\033[0m");
}

void InterfaceInformation(void)
{
	GotoXY(kInfoboxBorderX + 18, 3); cout << "��ǰ������";
	GotoXY(kInfoboxBorderX + 18, 6); cout << "��߷�����";
	GotoXY(kInfoboxBorderX + 18, 9); cout << "��ǰ��ʱ��";
	GotoXY(kInfoboxBorderX + 8, 18); cout << "����˵����";
	GotoXY(kInfoboxBorderX + 12, 21); cout << "���ϣ�W      ���£�S";
	GotoXY(kInfoboxBorderX + 12, 23); cout << "����A      ���ң�D";
	GotoXY(kInfoboxBorderX + 12, 25); cout << "���٣�,      ���٣�.";
	GotoXY(kInfoboxBorderX + 8, 30); cout << "��ǰ��Ϸ�Ѷȣ�";
	if (choice == '1') cout << "����";
	else if (choice == '2') cout << "����";
	else if (choice == '3') cout << "����";
}

int InitialInterface(void)
{
	MainInterface();
	int speed = ChoiceDifficulty();
	system("cls");  //����
	BuildBoundary();
	InterfaceInformation();
	return speed;
}

void InstantiateInfo(void)
{
	game_grade = new Grade;
	game_time = new Time;
	game_snake = new Snake;
}

void InitialInfo(void)
{
	game_grade->InitialGrade();
	game_time->InitialTime();
	game_snake->InitialSnake();
}


void InitialJudge(void)
{
	judge = new int* [100]();
	for (int i = 0; i < 100; ++i)
	{
		judge[i] = new int[100]();
	}
}

void InitialFood(void)
{
	//�������ʽ��number = (rand()%(maxValue - minValue +1)) + minValue;
	int x, y;
	do
	{
		srand(time(NULL) ^ _getpid());  //����������ӣ�����ÿ�����г��������
		x = rand() % (kSceneWidth + 1 - 2 + 1) + 2;  //��2��77 (2, IB_width_value + 1)
		y = rand() % (kSceneHeight - 1 + 1) + 1;	 //��1��38 (1, IB_height_value)
	} while (judge[x][y] == 1);  //��֤ʳ�ﲻ�Ḳ����
	GotoXY(x, y); printf("\033[40;31m$\033[0m"); judge[x][y] = 2;
}

void GotoXY(int x, int y)
{
	COORD coordinate;
	coordinate.X = x; coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void GradeUpSound(void)
{
	Beep(500, 500);
}

void EndOfMsg(void)
{
	printf("\a");  //��Ϸ��������
	int grade = game_grade->GetGrade();
	int time = game_time->GetTime();
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 9);
	cout << "G A M E   O V E R" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 7);
	cout << "��Ϸ�÷֣�" << grade << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 5);
	cout << "��Ϸ��ʱ��" << time / 60 << ":";
	if (time % 60 < 10) cout << "0" << time % 60;
	else cout << time % 60;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 3);
	cout << "1)���¿�ʼ" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 1);
	cout << "2)������Ϸ" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 + 1);
	cout << "����������ѡ��-> ";
}

void ResetJudge(void)
{
	for (int i = 0; i < 100; ++i)
	{
		delete[]judge[i];
	}
	delete[]judge;
}

void Reset(void)
{
	game_grade->ResetGrade();
	game_judge = true;
}

//��ʼ��ʱ��
void Time::InitialTime(void)
{
	//��ȡ��ʼʱ��
	begin_time_ = clock();
	//��ӡ��ʱ
	GotoXY(kInfoboxBorderX + 28, 9);
	cout << current_time_ / 60 << ":" << current_time_ % 60;
}

//ˢ��ʱ��
void Time::UpdateTime(void)
{
	//��ȡ��ǰʱ��
	end_time_ = clock();
	//������ʱ
	current_time_ = (end_time_ - begin_time_) / 1000;
	//��ӡ��ʱ
	GotoXY(kInfoboxBorderX + 28, 9);
	cout << current_time_ / 60 << ":";
	if (current_time_ % 60 < 10) cout << "0" << current_time_ % 60;
	else cout << current_time_ % 60;
}

//��ȡ����ʱ��
int Time::GetTime(void)
{
	return current_time_;
}

//��ʼ������
void Grade::InitialGrade(void)
{
	GotoXY(kInfoboxBorderX + 28, 3);
	cout << current_score_;
	GotoXY(kInfoboxBorderX + 28, 6);
	cout << best_score_;
}

//���·���
void Grade::UpdateGrade(void)
{
	thread th(GradeUpSound);
	/*
	��Ϊ�ڴ������̺߳��߳̿�ʼִ��,�������߳�main()��û��ֹͣ�Ų�
	��Ȼ����ִ��Ȼ���˳�,��ʱ�̶߳�����joinable���߳���Ȼ���ڵ�
	ָ�������̶߳����Ѿ����٣����Ի��׳��쳣��
	*/
	th.detach();  //�����߳������̶߳���������֤���߻���Ӱ�죬�����׳��쳣
	++current_score_;
	GotoXY(kInfoboxBorderX + 28, 3);
	cout << current_score_;
	if (best_score_ < current_score_)
	{
		best_score_ = current_score_;
		GotoXY(kInfoboxBorderX + 28, 6);
		cout << best_score_;
	}
}

//���õ�ǰ����
void Grade::ResetGrade(void)
{
	current_score_ = 0;
}

//��ȡ���η���
int Grade::GetGrade(void)
{
	return current_score_;
}

//��Ϸ����
void Snake::GameOver(void)
{
	system("cls");
	game_judge = false;
}

//������״̬
void Snake::SnakeStatus(void)
{
	input_char_ = _getch();
	switch (input_char_)
	{
	case 'w':
	case 'W':
		if (snake_status_ != DOWN) snake_status_ = UP; break;
	case 's':
	case 'S':
		if (snake_status_ != UP) snake_status_ = DOWN; break;
	case 'a':
	case 'A':
		if (snake_status_ != RIGHT) snake_status_ = LEFT; break;
	case 'd':
	case 'D':
		if (snake_status_ != LEFT) snake_status_ = RIGHT; break;
	}
}

//�ж��Ƿ�Ϊʳ��
bool Snake::JudgeFood(int x, int y)
{
	if (judge[x][y] == 2)
	{
		InitialFood();
		return true;
	}
	return false;
}

//�ж��Ƿ�Ϊǽ������
bool Snake::JudgeWallOrBody(int x, int y)
{
	if (x == 1 || y == 0 || x == kSceneWidth + 2 || y == kSceneHeight + 1) return true;
	if (judge[x][y] == 1) return true;
	return false;
}

//��ʼ����
void Snake::InitialSnake(void)
{
	while (!snake.empty())
	{
		snake.pop();
	}
	snake_status_ = RIGHT;
	snake.push(make_pair(10, 10));
	snake.push(make_pair(11, 10));
	snake.push(make_pair(12, 10));
	//printf("\033[�ֱ�����ɫ;������ɫm�ַ���\033[0m" );
	/*
	�ֱ�����ɫ��Χ: 40--49           ����ɫ: 30--39
	40: ��                           30: ��
	41: ��                           31: ��
	42: ��                           32: ��
	43: ��                           33: ��
	44: ��                           34: ��
	45: ��                           35: ��
	46: ����                         36: ����
	47: ��ɫ                         37: ��ɫ
	*/
	GotoXY(10, 10); printf("\033[40;34m#\033[0m"); judge[10][10] = 1;
	GotoXY(11, 10); printf("\033[40;34m#\033[0m"); judge[11][10] = 1;
	GotoXY(12, 10); printf("\033[40;33m@\033[0m"); judge[12][10] = 1;
}

//�ж���ͷ��һ��λ��
void Snake::UpdateSnakeByStatus(void)
{
	int x = 0, y = 0;
	switch (snake_status_)
	{
	case UP: y = -1; break;
	case DOWN: y = 1; break;
	case LEFT: x = -1; break;
	case RIGHT: x = 1; break;
	}
	if (JudgeWallOrBody(snake.back().first + x, snake.back().second + y))
	{
		GameOver();
		return;
	}
	if (JudgeFood(snake.back().first + x, snake.back().second + y))
	{
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;34m#\033[0m");  //��ԭ��ͷ��Ϊ����
		snake.push(make_pair(snake.back().first + x, snake.back().second + y));  //������ͷ�������
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;33m@\033[0m"); judge[snake.back().first][snake.back().second] = 1;
		game_grade->UpdateGrade();
	}
	else
	{
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;34m#\033[0m");
		snake.push(make_pair(snake.back().first + x, snake.back().second + y));
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;33m@\033[0m"); judge[snake.back().first][snake.back().second] = 1;
		GotoXY(snake.front().first, snake.front().second); printf(" "); judge[snake.front().first][snake.front().second] = 0;
		snake.pop();
	}
}

//������
void Snake::UpdateSnake(void)
{
	//�жϲ���ӡ��ͷ����һ��λ��
	UpdateSnakeByStatus();
}