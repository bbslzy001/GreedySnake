#ifndef __CONSTANT__
#define __CONSTANT__

/*������Ϸ���ڴ�С*/
//���ڿ��
const int kWindowWidth = 130;
//���ڸ߶�
const int kWindowHeight = 40;

/*������Ϸ��߽緽�������÷��š��������ռ2�߶�ռ1(�ڿ���̨�п�2��1Ϊ������)*/
//��߽�ˮƽ������
const int kBorderWidthNum = kWindowWidth / 2;
//��߽紹ֱ������
const int kBorderHeightNum = kWindowHeight;

/*���������Ϸ�������ֵ�������Σ�*/
//�����߶�ֵ
const int kSceneHeight = kBorderHeightNum - 2;
//�������ֵ
const int kSceneWidth = kSceneHeight * 2;

/*������Ϣ��߽�ˮƽ��ʼ���꣬�ñ߽�Ϊ�����Σ�����������38�����Ŀռ䣬��һ����λ��(38+1)*2-1+1������һ��λ��*/
//��Ϣ��߽�ˮƽ��ʼ����
const int kInfoboxBorderX = (kSceneHeight + 1) * 2;

/*������Ϣ�򷽿���*/
//��Ϣ��ֱ������
const int kInfoboxHeightNum = kBorderHeightNum - 2;
//��Ϣ��ˮƽ������
const int kInfoboxWidthNum = kInfoboxHeightNum;

#endif