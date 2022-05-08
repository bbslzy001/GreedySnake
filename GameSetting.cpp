#include "Constant.h"
#include "GameSetting.h"

using namespace std;

//
static char choice = '0';
//
static int** judge;
//游戏结束判断
extern bool game_judge;

/*定义全局对象指针*/
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
	GetConsoleCursorInfo(handle, &CursorInfo);  //获取控制台光标信息
	CursorInfo.bVisible = false;  //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);  //设置控制台光标状态
}

void InitialGame(void)
{
	SetWindowSize();
	HideCursor();
}

void MainInterface(void)
{
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 7);
	cout << "请选择游戏难度：" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 5);
	cout << "1)娱乐" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 3);
	cout << "2)正常" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 1);
	cout << "3)地狱" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 + 1);
	cout << "请输入您的选择-> ";
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
	for (int i = 0; i < kBorderWidthNum; ++i) printf("\033[47;37m■\033[0m");  //该符号宽度占2高度占1
	cout << endl;
	for (int i = 1; i <= kSceneHeight; ++i)
	{
		printf("\033[47;37m■\033[0m");
		GotoXY(kInfoboxBorderX, i);
		printf("\033[40;37m■\033[0m");
		//窗口每行有0~129共130个位置，为将符号打印在每行末尾，需将光标移至128,将128和129放置一个■
		GotoXY(kWindowWidth - 2, i);
		printf("\033[47;37m■\033[0m\n");
	}
	for (int i = 0; i < kBorderWidthNum; ++i) printf("\033[47;37m■\033[0m");
	//将0~13共14的高度分成一格
	GotoXY(kInfoboxBorderX + 2, 13);
	for (int i = 0; i < kBorderWidthNum - kBorderHeightNum - 1; ++i) printf("\033[40;37m■\033[0m");
}

void InterfaceInformation(void)
{
	GotoXY(kInfoboxBorderX + 18, 3); cout << "当前分数：";
	GotoXY(kInfoboxBorderX + 18, 6); cout << "最高分数：";
	GotoXY(kInfoboxBorderX + 18, 9); cout << "当前用时：";
	GotoXY(kInfoboxBorderX + 8, 18); cout << "操作说明：";
	GotoXY(kInfoboxBorderX + 12, 21); cout << "向上：W      向下：S";
	GotoXY(kInfoboxBorderX + 12, 23); cout << "向左：A      向右：D";
	GotoXY(kInfoboxBorderX + 12, 25); cout << "加速：,      减速：.";
	GotoXY(kInfoboxBorderX + 8, 30); cout << "当前游戏难度：";
	if (choice == '1') cout << "娱乐";
	else if (choice == '2') cout << "正常";
	else if (choice == '3') cout << "地狱";
}

int InitialInterface(void)
{
	MainInterface();
	int speed = ChoiceDifficulty();
	system("cls");  //清屏
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
	//随机数格式：number = (rand()%(maxValue - minValue +1)) + minValue;
	int x, y;
	do
	{
		srand(time(NULL) ^ _getpid());  //创建随机种子，否则每次运行程序不是随机
		x = rand() % (kSceneWidth + 1 - 2 + 1) + 2;  //从2到77 (2, IB_width_value + 1)
		y = rand() % (kSceneHeight - 1 + 1) + 1;	 //从1到38 (1, IB_height_value)
	} while (judge[x][y] == 1);  //保证食物不会覆盖蛇
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
	printf("\a");  //游戏结束声音
	int grade = game_grade->GetGrade();
	int time = game_time->GetTime();
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 9);
	cout << "G A M E   O V E R" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 7);
	cout << "游戏得分：" << grade << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 5);
	cout << "游戏用时：" << time / 60 << ":";
	if (time % 60 < 10) cout << "0" << time % 60;
	else cout << time % 60;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 3);
	cout << "1)重新开始" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 1);
	cout << "2)结束游戏" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 + 1);
	cout << "请输入您的选择-> ";
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

//初始化时间
void Time::InitialTime(void)
{
	//获取初始时间
	begin_time_ = clock();
	//打印用时
	GotoXY(kInfoboxBorderX + 28, 9);
	cout << current_time_ / 60 << ":" << current_time_ % 60;
}

//刷新时间
void Time::UpdateTime(void)
{
	//获取当前时间
	end_time_ = clock();
	//计算用时
	current_time_ = (end_time_ - begin_time_) / 1000;
	//打印用时
	GotoXY(kInfoboxBorderX + 28, 9);
	cout << current_time_ / 60 << ":";
	if (current_time_ % 60 < 10) cout << "0" << current_time_ % 60;
	else cout << current_time_ % 60;
}

//获取本次时间
int Time::GetTime(void)
{
	return current_time_;
}

//初始化分数
void Grade::InitialGrade(void)
{
	GotoXY(kInfoboxBorderX + 28, 3);
	cout << current_score_;
	GotoXY(kInfoboxBorderX + 28, 6);
	cout << best_score_;
}

//更新分数
void Grade::UpdateGrade(void)
{
	thread th(GradeUpSound);
	/*
	因为在创建了线程后线程开始执行,但是主线程main()并没有停止脚步
	仍然继续执行然后退出,此时线程对象还是joinable的线程仍然存在但
	指向它的线程对象已经销毁，所以会抛出异常。
	*/
	th.detach();  //将子线程与主线程独立开，保证两者互不影响，否则抛出异常
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

//重置当前分数
void Grade::ResetGrade(void)
{
	current_score_ = 0;
}

//获取本次分数
int Grade::GetGrade(void)
{
	return current_score_;
}

//游戏结束
void Snake::GameOver(void)
{
	system("cls");
	game_judge = false;
}

//更新蛇状态
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

//判断是否为食物
bool Snake::JudgeFood(int x, int y)
{
	if (judge[x][y] == 2)
	{
		InitialFood();
		return true;
	}
	return false;
}

//判断是否为墙或身子
bool Snake::JudgeWallOrBody(int x, int y)
{
	if (x == 1 || y == 0 || x == kSceneWidth + 2 || y == kSceneHeight + 1) return true;
	if (judge[x][y] == 1) return true;
	return false;
}

//初始化蛇
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
	//printf("\033[字背景颜色;字体颜色m字符串\033[0m" );
	/*
	字背景颜色范围: 40--49           字颜色: 30--39
	40: 黑                           30: 黑
	41: 红                           31: 红
	42: 绿                           32: 绿
	43: 黄                           33: 黄
	44: 蓝                           34: 蓝
	45: 紫                           35: 紫
	46: 深绿                         36: 深绿
	47: 白色                         37: 白色
	*/
	GotoXY(10, 10); printf("\033[40;34m#\033[0m"); judge[10][10] = 1;
	GotoXY(11, 10); printf("\033[40;34m#\033[0m"); judge[11][10] = 1;
	GotoXY(12, 10); printf("\033[40;33m@\033[0m"); judge[12][10] = 1;
}

//判断蛇头下一个位置
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
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;34m#\033[0m");  //将原蛇头改为蛇身
		snake.push(make_pair(snake.back().first + x, snake.back().second + y));  //将新蛇头坐标入队
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

//更新蛇
void Snake::UpdateSnake(void)
{
	//判断并打印蛇头的下一个位置
	UpdateSnakeByStatus();
}