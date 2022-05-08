#ifndef __CONSTANT__
#define __CONSTANT__

/*定义游戏窗口大小*/
//窗口宽度
const int kWindowWidth = 130;
//窗口高度
const int kWindowHeight = 40;

/*定义游戏外边界方块数，该符号“■”宽度占2高度占1(在控制台中宽2高1为正方形)*/
//外边界水平方块数
const int kBorderWidthNum = kWindowWidth / 2;
//外边界垂直方块数
const int kBorderHeightNum = kWindowHeight;

/*定义左侧游戏场景宽高值（正方形）*/
//场景高度值
const int kSceneHeight = kBorderHeightNum - 2;
//场景宽度值
const int kSceneWidth = kSceneHeight * 2;

/*定义信息框边界水平起始坐标，让边界为正方形，故两侧间存在38个■的空间，下一个■位于(38+1)*2-1+1和其下一个位置*/
//信息框边界水平起始坐标
const int kInfoboxBorderX = (kSceneHeight + 1) * 2;

/*定义信息框方块数*/
//信息框垂直方块数
const int kInfoboxHeightNum = kBorderHeightNum - 2;
//信息框水平方块数
const int kInfoboxWidthNum = kInfoboxHeightNum;

#endif