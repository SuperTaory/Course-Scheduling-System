/*每年两学期。每学期的教学周数和学分均有上限，在教学计划一定的情况下，
开设的课程必须满足次序关系，
设计要求：
采用邻接表，栈等数据结构
可以随机，文件及人工输入数据；
计算课程的最优划分，尽量使学期最短
可以统计数据并满足必要的约束条件
可以查询更新数据
其他完善或拓展功能
*/


#include <iostream>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<windows.h>
#include "Graph.h"
#include "TopologicalSort.h"
using namespace std;

void Menu()
{
	int n;
	ALGraph G;
	while(n)
	{
		system("cls");
	int i;
	printf("\t\t\t\t欢迎使用课程设计系统\n");
	printf("\n\t\t\t\t1-新建课程表\n");
	printf("\n\t\t\t\t2-查询已排课程\n");
	printf("\n\t\t\t\t3-更新课程表\n");
	printf("\n\t\t\t\t4-统计信息\n\n\t\t\t\t输入：");

	scanf("%d",&i);

	switch(i)
	{
	case 1:
		system("cls");
		func1(G);
		break;
	case 2:
		system("cls");
		SearchCourse();
		system("cls");
		break;
	case 3:
		system("cls");
		Update();
		system("cls");
		break;
	case 4:
		system("cls");
		Tongji();
		break;
	default:
		printf("输入错误!");
		exit(0);system("cls");
	}
	printf("\n\n\t\t\t是否返回主菜单？(1-返回主菜单，0-退出系统)\n\n\t\t\t输入：");
	scanf("%d",&n);
	}
	system("cls");
	printf("\n\n\t\t\t\t谢谢使用课程设计系统!\n\n");
}
int main()
{
	Menu();
	return 0;
}
