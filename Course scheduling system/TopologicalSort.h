#ifndef TOPOLOGICALSORT_H_INCLUDED
#define TOPOLOGICALSORT_H_INCLUDED
#include<string>
#include"Graph.h"

struct Queue
{
	int Top,Tail;
	VNode *a[20];
	VNode *Front();
	void Clear();
	void Pop();
	void Push(VNode *e);
	bool Empty();
};


void Queue::Push(VNode *e)
{
	a[Tail++]=e;
	return ;
}


void Queue::Clear()
{
	Top=Tail=0;
	return ;
}

void Queue::Pop()
{
	Top++;
	return ;

}

VNode *Queue::Front()
{
	return a[Top];
}

bool Queue::Empty()
{
	return Top==Tail;
}

bool Find(ALGraph G)
{
	int j=0;
	for(int i=0;i<G.vexnum;i++)
	{
		if(G.AdjList[i].data.marks==0)
			{j=1;
		    break;}
	}
	return j;
}

void CourseSort(ALGraph G)
{
	int i,m,n,k=0,s=0,a=0;
	int Term=1;
	FILE *fp1;
	float t=0;//学期剩余学分
	VNode *v;
	VNode Sort[50];
	ArcNode *p;
	int Maxweeks;
	float Maxpoints;
	printf("\t\t\t请输入每学期的周数和学分上限\n");
	printf("\n\t\t\t周数上限:");
	scanf("%d",&Maxweeks);
	printf("\n\t\t\t学分上限:");
	scanf("%f",&Maxpoints);
	s=Maxweeks;
	t=Maxpoints;
	system("cls");
	Queue Q;
	Q.Clear();
	while(Find(G))
	{   a=0;
		m=0,n=0;
		for(i=0;i<G.vexnum;i++)
	    {
		  if(G.AdjList[i].data.Indegree==0&&G.AdjList[i].data.marks!=1)
		  {
		 	  Q.Push(&G.AdjList[i]);
		 	  a++;
		 	  m++;
		 	  G.AdjList[i].data.marks=1;
		  }
	    }//入度为0的点入队列
	    if(a==0)
		{
			printf("\n\n\\t\t\t\t......检测到图中存在环!试重新创建课程图!\n\n");
			exit(0);
		}
		else
		{
	    while(!Q.Empty())
	    {
		   v=Q.Front();//取队首元素
		   n++;
		   Q.Pop(); //出队列
		   p=v->firstarc;
		   while(p)
		   {
				G.AdjList[p->adjvex].data.Indegree--;//入度减一
				p=p->nextarc;
		   }

		   if(v->data.Point<=t&&v->data.Weeks<=s)
		   {
				v->data.term=Term;
				Sort[k++]=*v;
		   }
		   else
		    {
				Term++;//学期数加一
				t=Maxpoints;
				v->data.term=Term;
				Sort[k++]=*v;
			}
			  if(n==m)
		   {
		   	for(int j=0;j<k;j++)
			{
				if(Sort[j].data.term==Term)
				{
					if(s>=(Maxweeks-Sort[j].data.Weeks))
					{
						s=Maxweeks-Sort[j].data.Weeks;
					}
				}
			}
			t=t-v->data.Point;
		   }
		   else
		   {
		   	s=Maxweeks;
		   	t=t-v->data.Point;
		   }
	    }
		}
	}

	printf("经最优划分使学期最短的情况下安排这些课程的最少学期数是: %d\n\t\t\t\t课程表如下\n",Term);
	for(int j=1;j<=Term;j++)
	{
		printf("\n\t\t\t\t第%d学期的课程如下\n\n",j);
		printf("\t\t\t课程编号  课程名称     学分   周数   学期数\n");
		for(int m=0;m<k;m++)
		{
			if(Sort[m].data.term==j)
				printf("\n\t\t\t%d\t%10s\t%.2f\t%d\t%d\t\n",Sort[m].data.Num,Sort[m].data.Name,Sort[m].data.Point,Sort[m].data.Weeks,Sort[m].data.term);
		}
	}
	fp1=fopen("beifen","w+");
	if((fp1=fopen("beifen.txt","w+"))==NULL)
	{
		printf("打开文件失败!");
		exit(0);
	}
	else
	    for(int d=0;d<k;d++)
		{
			fprintf(fp1,"%d\t%10s\t%.2f\t%d\t%d\t\n",Sort[d].data.Num,Sort[d].data.Name,Sort[d].data.Point,Sort[d].data.Weeks,Sort[d].data.term);
		}
		fclose(fp1);
}

void SearchCourse()
{
	VNode S[50];
	char s[20];
	int d=0,j=0,m=1,n,Term=0;
	FILE *fp2;
	fp2=fopen("beifen.txt","a+");
	if((fp2=fopen("beifen.txt","a+"))==NULL)
	{
		printf("打开文件失败!");
		exit(0);
	}
	else
		while(!feof(fp2))
	{
		fscanf(fp2,"%d%s%f%d%d",&S[d].data.Num,&S[d].data.Name,&S[d].data.Point,&S[d].data.Weeks,&S[d].data.term);
		d++;
	}
	fclose(fp2);
	for(int s=0;s<d-1;s++)
	{
		if(S[s].data.term>=Term)
		{
			Term=S[s].data.term;
		}
	}

	while(m)
	{
		system("cls");
		printf("\n\t\t\t\t1-依课程名字查询\n\n\t\t\t\t2-依学期序号查询\n\n\t\t\t\t3-查询全部课程\n\n\t\t\t\t输入:");
	    scanf("%d",&n);
		switch(n)
		{
		case 1:
			system("cls");
			j=0;
	        printf("\n请输入你要查询的课程名字：");
	        scanf("%s",s);
	        system("cls");
	        for(int i=0;i<d;i++)
            {
	      	if(strcmp(S[i].data.Name,s)==0)
		    {
			 printf("\n\t\t\t\t您所查的课程信息为：\n");
			 printf("\n\t\t\t课程编号  课程名称     学分   周数   学期数\n");
			 printf("\n\t\t\t%d\t%10s\t%.2f\t%d\t%d\t\n",S[i].data.Num,S[i].data.Name,S[i].data.Point,S[i].data.Weeks,S[i].data.term);
			  j=1;
			 break;
		    }
			}
         	if(j==0)
	        {
		        printf("\n\t\t\t.......未查找到你所要查找的课程信息!\n");
	        }
	        break;
		case 2:
			system("cls");
			int t;
			printf("\n请输入您要查询的学期号：");
			scanf("%d",&t);
			system("cls");
			if(t<=Term)
			{
			printf("\n\t\t\t\t第%d学期的课程如下\n\n",t);
			printf("\t\t\t课程编号  课程名称     学分   周数   学期数\n\n");
			for(int i=0;i<d;i++)
			{
				if(S[i].data.term==t)
				{
				   printf("\n\t\t\t%d\t%10s\t%.2f\t%d\t%d\t\n",S[i].data.Num,S[i].data.Name,S[i].data.Point,S[i].data.Weeks,S[i].data.term);
				}
			 }
			}
			else
				printf("\n\t\t\t......输入学期序号过大，该学期不存在!\n");
			break;
		case 3:
			system("cls");
			for(int i=1;i<=Term;i++)
	       {
	        	printf("\n\t\t\t\t  第%d学期的课程如下\n\n",i);
	        	printf("\t\t\t课程编号  课程名称     学分   周数   学期数\n");
		        for(int k=0;k<d;k++)
		        {
		        	if(S[k].data.term==i)
			        	printf("\n\t\t\t%d\t%10s\t%.2f\t%d\t%d\t\n",S[k].data.Num,S[k].data.Name,S[k].data.Point,S[k].data.Weeks,S[k].data.term);
		        }
		   }
		   break;
		default:
			printf("\n\t\t\t\t......输入错误!\n");
		}

	printf("\n\n\t\t\t是否继续查询？\t(是-输入1，否-输入0)\n\n\t\t\t输入：");
	scanf("%d",&m);
	}
}


void Tongji()
{
    VNode S[50];
	int d=0,Term=0,p1=0;
    float p2=0;
	FILE *fp2;
	fp2=fopen("beifen.txt","a+");
	if((fp2=fopen("beifen.txt","a+"))==NULL)
	{
		printf("打开文件失败!");
		exit(0);
	}
	else
		while(!feof(fp2))
	{
		fscanf(fp2,"%d%s%f%d%d",&S[d].data.Num,&S[d].data.Name,&S[d].data.Point,&S[d].data.Weeks,&S[d].data.term);
		d++;
	}
	fclose(fp2);

	for(int i=0;i<d-1;i++)
	{
		if(S[i].data.term>=Term)
		{
			Term=S[i].data.term;
		}
	}
	for(int j=1;j<=Term;j++)
	{
		p1=0;
		p2=0;
		for(int k=0;k<d;k++)
		{
			if(S[k].data.term==j)
			{
				p1++;
				p2=p2+S[k].data.Point;
			}
		}
		printf("\n\t\t\t第%d学期共需学习%d门课程，修得%.2f学分!\n",j,p1,p2);
	}

}

void func1(ALGraph G)
{
	int i;
	printf("\n\t\t\t\t请选择创建课程图的方式：\n");
	printf("\n\t\t\t\t1-人工输入\n");
	printf("\n\t\t\t\t2-文件输入\n\n\t\t\t\t输入：");
	scanf("%d",&i);
	switch(i)
	{
	case 1:
		system("cls");
		CreateALGraph(G);
		break;
	case 2:
		system("cls");
		FileCreate(G);
		break;
	default:
		printf("输入错误!");
		exit(0);
	}
	system("cls");
	GhArc(G);
	GhPrint(G);
	CourseSort(G);
	printf("\n\n\t\t\t教务课程计划安排成功!\n");
}

void Update()
{
    char n[20];
    VNode S[50];
    int i,s,d=0,j=0;
    FILE *fp3,*fp4;
	fp3=fopen("beifen.txt","a+");
	if((fp3=fopen("beifen.txt","a+"))==NULL)
	{
		printf("打开文件失败!");
		exit(0);
	}
	else
		while(!feof(fp3))
	{
		fscanf(fp3,"%d%s%f%d%d",&S[d].data.Num,&S[d].data.Name,&S[d].data.Point,&S[d].data.Weeks,&S[d].data.term);
		d++;
	}
	fclose(fp3);
	while(s)
	{
		system("cls");
	j=0;
    printf("输入你要更新的课程的名字：");
    scanf("%s",n);
    for(i=0;i<d-1;i++)
	{
		if(strcmp(S[i].data.Name,n)==0)
		{
			printf("\n您所要更新的课程信息为：\n");
			 printf("\n课程编号  课程名称     学分   周数   学期数\n");
			 printf("\n%d\t%10s\t%.2f\t%d\t%d\t\n",S[i].data.Num,S[i].data.Name,S[i].data.Point,S[i].data.Weeks,S[i].data.term);
			 j++;
			 break;
		}
	}
	if(j==0)
		printf("\n未查找您要更新的课程!\n");
	else
		{
	     printf("\n%s  更新为： ",S[i].data.Name);
	     scanf("%s",S[i].data.Name);
	     system("cls");
		 printf("\n更新后的信息为：\n");
		 printf("\n课程编号  课程名称     学分   周数   学期数\n");
	     printf("\n%d\t%10s\t%.2f\t%d\t%d\t\n",S[i].data.Num,S[i].data.Name,S[i].data.Point,S[i].data.Weeks,S[i].data.term);
         fp4=fopen("beifen.txt","w+");
	     if((fp4=fopen("beifen.txt","w+"))==NULL)
	     {
	    	printf("打开文件失败!");
	    	exit(0);
	     }
	     else
	          for(int k=0;k<d-1;k++)
		      {
		      	fprintf(fp4,"%d\t%10s\t%.2f\t%d\t%d\t\n",S[k].data.Num,S[k].data.Name,S[k].data.Point,S[k].data.Weeks,S[k].data.term);
		      }
		 fclose(fp4);
		 printf("\n更新成功!\n");
		}
		printf("\n是否继续更新？\t(是-输入1，否-输入0)\n\n输入：");
	    scanf("%d",&s);
	}
}

#endif // TOPOLOGICALSORT_H_INCLUDED
