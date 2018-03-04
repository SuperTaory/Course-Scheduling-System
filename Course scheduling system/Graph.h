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
#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#define MAX_VERTEX_NUM 50


//表节点
struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
};

//顶点信息
struct VertexType
{
	int Num;
	char Name[20];
	float Point;
	int Weeks;
	bool marks;
	int term;
	int Indegree;
	int Outdegree;
};

//头结点
typedef struct VNode
{
	VertexType data;
	ArcNode *firstarc;
}VNode;

typedef struct ALGraph
{
    VNode AdjList[MAX_VERTEX_NUM];
	int vexnum;
	int arcnum;
}ALGraph;

int GLocateVex(ALGraph G,int x)
{
	int i,j=-1;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.AdjList[i].data.Num==x)
        {
            j=i;
            break;
        }
	}
	return j;
}


void GhArc(ALGraph G)
{
	int i;
	ArcNode *q;
	printf("\t\t\t所创建课程图的课程关系如下(编号代替课程表示)\n");
	for(i=0;i<G.vexnum;i++)
	{
		q=G.AdjList[i].firstarc;
		while(q)
		{
			printf("\t\t\t\t\t%d->%d\n",G.AdjList[i].data.Num,G.AdjList[q->adjvex].data.Num);
		    q=q->nextarc;
		}
	}
}

void GhPrint(ALGraph G)
{
	int i;
	printf("\t\t\t\t   课程信息如下:\n\n\t\t\t课程编号 课程名称    学分   周数\n");
	for(i=0;i<G.vexnum;i++)
	{
		printf("\n\t\t\t%d\t%10s\t%.1f\t%d\n\n",G.AdjList[i].data.Num,G.AdjList[i].data.Name,G.AdjList[i].data.Point,G.AdjList[i].data.Weeks);
	}
}


void FileCreate(ALGraph &G)
{
	FILE *fp;
	int i=0;
	int m,n,k,s1,s2;
	ArcNode *s;
	fp=fopen("entering.txt","a+");
	if((fp=fopen("entering.txt","a+"))==NULL)
	{
		printf(".......打开文件失败!");
		exit(0);
	}
	else
	{
	while(!feof(fp))
	{
		fscanf(fp,"%d%s%f%d",&G.AdjList[i].data.Num,&G.AdjList[i].data.Name,&G.AdjList[i].data.Point,&G.AdjList[i].data.Weeks);
		G.AdjList[i].firstarc=NULL;
		G.AdjList[i].data.marks=0;
		G.AdjList[i].data.term=0;
		G.AdjList[i].data.Outdegree=0;
		G.AdjList[i].data.Indegree=0;
		i++;
	}
	fclose(fp);
	G.vexnum=i;
	printf("\t\t\t\t读取课程信息成功！\n\n");
	GhPrint(G);
	printf("\t\t\t请输入课程图的边数：");
	scanf("%d",&G.arcnum);
	printf("\n\t\t\t请输入顶点关系:(课程编号(弧尾) 课程编号(弧头))\n");
	for(int j=1;j<=G.arcnum;j++)
	{
		printf("\t\t\t");
		scanf("%d",&s1);
		scanf("%d",&s2);
		if(s1==s2)
		{
			printf("\t\t\t.....输入不合理! 请重新输入：\n");
			j--;
			continue;
		}
		else
		{
	    m=GLocateVex(G,s1);
	    n=GLocateVex(G,s2);
	    if(m==-1||n==-1)
		{
			printf("\t\t\t在图中没有找到该编号，请重新输入:\n");
			j--;
			continue;
		}
		else
		{
		   s = (ArcNode*)malloc(sizeof(ArcNode));
	       if(!s)
		   {
		   	  printf("储存分配失败!");
			  exit(0);
		   }
		    s->adjvex=n;
	        s->nextarc=G.AdjList[m].firstarc;
	        G.AdjList[m].firstarc=s;
			G.AdjList[m].data.Outdegree++;
	        G.AdjList[n].data.Indegree++;
        }
	   }
	}
	}
}

void CreateALGraph(ALGraph &G)
{
	int i,j,m,n,k,s1,s2;
    ArcNode *s;
	printf("请输入所创建课程图的顶点个数和边数：");
	scanf("%d %d",&i,&j);
	G.vexnum=i;
	G.arcnum=j;
	printf("\n请输入顶点的信息顺序如下:\n");
	printf("\n课程编号 课程名称 学分 周数\n");
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%d%s%f%d",&G.AdjList[i].data.Num,&G.AdjList[i].data.Name,&G.AdjList[i].data.Point,&G.AdjList[i].data.Weeks);
		G.AdjList[i].firstarc=NULL;
		G.AdjList[i].data.marks=0;
		G.AdjList[i].data.term=0;
		G.AdjList[i].data.Outdegree=0;
		G.AdjList[i].data.Indegree=0;
	}
	printf("\n请输入顶点关系:(课程编号(弧尾) 课程编号(弧头))\n");
	for(j=1;j<=G.arcnum;j++)
	{
		scanf("%d",&s1);
		scanf("%d",&s2);
		if(s1==s2)
		{
			printf("输入不合理！请重新输入：\n");
			j--;
			continue;
		}
		else
		{
	    m=GLocateVex(G,s1);
	    n=GLocateVex(G,s2);
	    if(m==-1||n==-1)
		{
			printf("在图中没有找到该编号，请重新输入:\n");
			j--;
			continue;
		}
		else
		{
		   s = (ArcNode*)malloc(sizeof(ArcNode));
	       if(!s)
		   {
		   	  printf("储存分配失败!");
			  exit(0);
		   }
		    s->adjvex=n;
	        s->nextarc=G.AdjList[m].firstarc;
	        G.AdjList[m].firstarc=s;
			G.AdjList[m].data.Outdegree++;
	        G.AdjList[n].data.Indegree++;
        }
		}
	}
//	printf("创建成功!\n");
}

#endif // HEAD_H_INCLUDED
