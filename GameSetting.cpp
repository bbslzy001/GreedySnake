#include "Constant.h"
#include "GameSetting.h"

using namespace std;



//游戏蛇身、食物位置
static int** judge;

//游戏结束判断
extern bool game_judge;

/*定义全局对象指针*/
//状态类对象
extern Status* game_status;
//难度类对象
extern Difficulty* game_difficulty;
//时间类对象
extern Time* game_time;
//分数类对象
extern Grade* game_grade;
//蛇类对象
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

void InstantiateData(void)
{
	game_status = new Status;
	game_difficulty = new Difficulty;
	game_time = new Time;
	game_grade = new Grade;
	game_snake = new Snake;
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

void InterfaceInfo(void)
{
	GotoXY(kInfoboxBorderX + 18, 3); cout << "当前分数：";
	GotoXY(kInfoboxBorderX + 18, 6); cout << "最高分数：";
	GotoXY(kInfoboxBorderX + 18, 9); cout << "当前用时：";
	GotoXY(kInfoboxBorderX + 8, 18); cout << "操作说明：";
	GotoXY(kInfoboxBorderX + 12, 21); cout << "向上：W 或 ↑   向下：S 或 ↓";
	GotoXY(kInfoboxBorderX + 12, 23); cout << "向左：A 或 ←   向右：D 或 ↓";
	GotoXY(kInfoboxBorderX + 12, 25); cout << "加速：,        减速：.";
	GotoXY(kInfoboxBorderX + 8, 30); cout << "当前游戏难度：";
	if (game_difficulty->GetDifficultyChoice() == '1') cout << "简单";
	else if (game_difficulty->GetDifficultyChoice() == '2') cout << "正常";
	else cout << "困难";
}

void InitialJudge(void)
{
	judge = new int* [100]();
	for (int i = 0; i < 100; ++i)
	{
		judge[i] = new int[100]();
	}
	return;
}

void InitialFood(void)
{
	//随机数格式：number = ( rand() % (maxValue - minValue + 1)) + minValue;
	int x, y;
	do
	{
		srand(time(NULL) ^ _getpid());  //创建随机种子，否则每次运行程序不是随机
		x = rand() % ((kSceneWidth + 1) - 2 + 1) + 2;  //从2到77 (2, kSceneWidth + 1)
		y = rand() % (kSceneHeight - 1 + 1) + 1;	 //从1到38 (1, kSceneHeight)
	} while (judge[x][y] == 1);  //保证食物不会覆盖蛇
	GotoXY(x, y); printf("\033[40;31m$\033[0m"); judge[x][y] = 2;
}

void Initial(void)
{
	system("cls");
	/*游戏状态信息模块*/
	game_status->InitialStatus();
	/*每局游戏难度选择模块*/
	game_difficulty->ChoiceDifficultyInterface();
	game_difficulty->ChoiceDifficulty();
	system("cls");
	/*每局游戏界面模块*/
	BuildBoundary();
	InterfaceInfo();
	/*每局游戏后台信息模块*/
	InitialJudge();
	game_grade->InitialGrade();
	game_time->InitialTime();
	game_snake->InitialSnake();
	InitialFood();
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
	ResetJudge();
	game_difficulty->ResetDifficulty();
}



void Status::InitialStatus(void)
{
	is_restart_ = false;
	is_run_ = true;
}

bool Status::GetIsRun(void)
{
	return is_run_;
}

bool Status::GetIsRestart(void)
{
	return is_restart_;
}

void Status::SetIsRun(bool status)
{
	is_run_ = status;
}

void Status::IfRestart(void)
{
	char is_restart = '0';
	while (is_restart != '1' && is_restart != '2') is_restart = _getch();
	if (is_restart == '1') is_restart_ = true;
}



void Difficulty::ChoiceDifficultyInterface(void)
{
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 7);
	cout << "请选择游戏难度：" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 5);
	cout << "1)简单" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 3);
	cout << "2)正常" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 - 1);
	cout << "3)困难" << endl;
	GotoXY(kWindowWidth / 2 - 10, kWindowHeight / 2 + 1);
	cout << "请输入您的选择-> ";
}

void Difficulty::ChoiceDifficulty(void)
{
	while (1)
	{
		difficulty_choice_ = _getch();
		if (difficulty_choice_ >= '1' && difficulty_choice_ <= '3') return;
	}
}

int Difficulty::GetSpeed(void)
{
	switch (difficulty_choice_)
	{
	case '1': if (game_snake->IsXDirection()) return kXEASY; else return kYEASY;
	case '2': if (game_snake->IsXDirection()) return kXCOMMON; else return kYCOMMON;
	case '3': if (game_snake->IsXDirection()) return kXDIFFICULT; else return kYDIFFICULT;
	}
}

char Difficulty::GetDifficultyChoice(void)
{
	return difficulty_choice_;
}

void Difficulty::ResetDifficulty(void)
{
	difficulty_choice_ = '0';
}



void Time::InitialTime(void)
{
	//获取初始时间
	begin_time_ = clock();
	//打印用时
	GotoXY(kInfoboxBorderX + 28, 9);
	cout << current_time_ / 60 << ":" << current_time_ % 60;
}

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

int Time::GetTime(void)
{
	return current_time_;
}



void Grade::InitialGrade(void)
{
	GotoXY(kInfoboxBorderX + 28, 3);
	cout << current_score_;
	GotoXY(kInfoboxBorderX + 28, 6);
	cout << best_score_;
}

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

void Grade::ResetGrade(void)
{
	current_score_ = 0;
}

int Grade::GetGrade(void)
{
	return current_score_;
}



void Snake::GameOver(void)
{
	system("cls");
	game_status->SetIsRun(false);
}

bool Snake::JudgeFood(int x, int y)
{
	if (judge[x][y] == 2)
	{
		InitialFood();
		return true;
	}
	return false;
}

bool Snake::JudgeWallOrBody(int x, int y)
{
	if (x == 1 || y == 0 || x == kSceneWidth + 2 || y == kSceneHeight + 1) return true;
	if (judge[x][y] == 1) return true;
	return false;
}

void Snake::InitialSnakeDirection(void)
{
	srand(time(NULL) ^ _getpid());  //创建随机种子，否则每次运行程序不是随机
	snake_status_ = rand() % (4 - 1 + 1) + 1;  //从1到4（1，4）
}

int* Snake::InitialSnakeXY(void)
{
	int* xy = new int[2]();
	srand(time(NULL) ^ _getpid());  //创建随机种子，否则每次运行程序不是随机
	xy[0] = rand() % ((kSceneWidth - 4) - 7 + 1) + 7;  //从7到72 (7, kSceneWidth - 4)
	xy[1] = rand() % ((kSceneHeight - 5) - 6 + 1) + 6;	 //从6到33 (1, kSceneHeight - 5)
	return xy;
}

void Snake::InitialSnake(void)
{
	while (!snake.empty())
	{
		snake.pop();
	}
	InitialSnakeDirection();
	int* xy = InitialSnakeXY();
	int x = 0, y = 0;
	switch (snake_status_)
	{
	case kUP: y = 1; break;
	case kDOWN: y = -1; break;
	case kLEFT: x = 1; break;
	case kRIGHT: x = -1; break;
	}
	snake.push(make_pair(xy[0] + x + x, xy[1] + y + y));  //队列先进先出，将蛇尾作为队头（方便出队，即删除蛇尾），蛇头作为队尾
	snake.push(make_pair(xy[0] + x, xy[1] + y));
	snake.push(make_pair(xy[0], xy[1]));
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
	GotoXY(xy[0] + x + x, xy[1] + y + y); printf("\033[40;34m#\033[0m"); judge[xy[0] + x + x][xy[1] + y + y] = 1;
	GotoXY(xy[0] + x, xy[1] + y); printf("\033[40;34m#\033[0m"); judge[xy[0] + x][xy[1] + y] = 1;
	GotoXY(xy[0], xy[1]); printf("\033[40;33m@\033[0m"); judge[xy[0]][xy[1]] = 1;
}

void Snake::UpdateSnakeDirection(void)
{
	input_char_ = _getch();
	switch (input_char_)
	{
	case 'w':
	case 'W':
	case 72:
		if (snake_status_ != kDOWN) snake_status_ = kUP; break;
	case 's':
	case 'S':
	case 80:
		if (snake_status_ != kUP) snake_status_ = kDOWN; break;
	case 'a':
	case 'A':
	case 75:
		if (snake_status_ != kRIGHT) snake_status_ = kLEFT; break;
	case 'd':
	case 'D':
	case 77:
		if (snake_status_ != kLEFT) snake_status_ = kRIGHT; break;
	}
}

bool Snake::IsXDirection(void)
{
	if (snake_status_ == kLEFT || snake_status_ == kRIGHT) return true;
	else return false;
}

void Snake::UpdateSnake(void)
{
	int x = 0, y = 0;
	switch (snake_status_)
	{
	case kUP: y = -1; break;
	case kDOWN: y = 1; break;
	case kLEFT: x = -1; break;
	case kRIGHT: x = 1; break;
	}
	if (JudgeWallOrBody(snake.back().first + x, snake.back().second + y))
	{
		GameOver();
		return;
	}
	if (JudgeFood(snake.back().first + x, snake.back().second + y))
	{
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;34m#\033[0m");  //队尾为蛇头，将原蛇头打印为蛇身
		snake.push(make_pair(snake.back().first + x, snake.back().second + y));  //将新蛇头坐标入队
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;33m@\033[0m");  //打印新蛇头
		judge[snake.back().first][snake.back().second] = 1;  //保存蛇头位置
		game_grade->UpdateGrade();  //更新分数
	}
	else
	{
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;34m#\033[0m");  //队尾为蛇头，将原蛇头打印为蛇身
		snake.push(make_pair(snake.back().first + x, snake.back().second + y));  //将新蛇头坐标入队
		GotoXY(snake.back().first, snake.back().second); printf("\033[40;33m@\033[0m");  //打印新蛇头
		judge[snake.back().first][snake.back().second] = 1;  //保存蛇头位置
		GotoXY(snake.front().first, snake.front().second); printf(" ");  //队首为蛇尾，将原蛇尾打印为空白
		judge[snake.front().first][snake.front().second] = 0;  //删除蛇尾位置
		snake.pop();  //队列先进先出，队头为蛇尾，将原蛇尾坐标出队
	}
}