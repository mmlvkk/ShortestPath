    /***********************************************************************
	************************************************************************
     author:wangkang  qq:417301568 e-mail: wangkang806@163.com 
	 begin time:2010-5-30
	 end time:
	************************************************************************
	************************************************************************/

#include <stdio.h>

#define VEXNUM_MAX 20  //定义最大顶点数。
#define QUANZHI_NOT_REACHE 10000 //定义权值不可达时的值。
#define CityNameLength 20

typedef int Quanzhi;
typedef struct{

	int value;
	char info[CityNameLength];//城市名字
}Vex,*Vex_point;

typedef struct{

	Vex v[VEXNUM_MAX]; //顶点数组
	Quanzhi quan[VEXNUM_MAX][VEXNUM_MAX]; //权值
	int vexnum;//顶点数
	int quannum;//权的数量 ，即弧数

} *Graph_point, Graph;

/***********************************************************************
************************************************************************
 创建邻接矩阵
************************************************************************
************************************************************************/
void createJuZhen(Graph_point m)
{
	int i,j,k,citynum,x,y;
	Quanzhi z;
	char c[CityNameLength];

	
	printf("请你输入顶点数目: ");
	scanf("%d",&i);
    m->vexnum=i;

	//给矩阵初值。
	for(i=0;i<m->vexnum;i++)
	{
		for(j=0;j<m->vexnum;j++)
		{
			if(i==j) m->quan[i][j]=0;
			else m->quan[i][j]=QUANZHI_NOT_REACHE;
		}
	}

	printf("请你输入权的数目: ");
	scanf("%d",&j);
    m->quannum=j;
    
	for(citynum=0;citynum<m->vexnum;citynum++)
	{
		printf("请输入第%d点顶点代表的城市:",citynum);
		scanf("%s",c);
		for(k=0;k<CityNameLength;k++)
		{	
			m->v[citynum].info[k]=c[k];
		}
		m->v[citynum].value=citynum;
	}


	for(i=0;i<m->quannum;i++)
	{
		printf("请输入两个顶点：(中间加逗号)");
		scanf("%d,%d",&x,&y);
		printf("输入两个顶点的权值(城市之间坐车所用费用)：");
		scanf("%d",&z);
		m->quan[x][y]=z;
		m->quan[y][x]=z;

	}
	//printf("%s\n",m->v[0].info);
	//printf("%d",j);
}


/***********************************************************************
************************************************************************
 显示邻接矩阵的
************************************************************************
************************************************************************/

void display(Graph_point m)
{
	int i,j,k;
	printf("\t");
	for(i=0;i<m->vexnum;i++)  //输出顶点
	{
		//printf("%8d",m->v[i].value); //输出顶点
		printf("%8s",m->v[i].info);   //输出城市名字
	}
    printf("\n");
	
	for(i=0;i<m->vexnum;i++)
	{
		//printf("%8d",m->v[i].value);
		printf("%8s",m->v[i].info);
		for(j=0;j<m->vexnum;j++)
		{
			printf("%8d",m->quan[i][j]);

		}
		printf("\n");

	}

}

/***********************************************************************
************************************************************************
 最短路径   用到了Dijstra算法。
************************************************************************
************************************************************************/
typedef struct{
	Quanzhi value; //权值
	int pre;//前一个顶点
}dijstra,*dijstra_point;


void shortertpath_Dijstra(Graph_point m,int vi,int vj)
{
	Quanzhi min;  //最短路径
	dijstra dist[VEXNUM_MAX];
	int s[VEXNUM_MAX]; //某个顶点是否访问过，访问过为1，没访问过为0
	int i,j,k,n;
	for(i=0;i<m->vexnum;i++)
	{
		//
		s[i]=0;
		if(i!=vi)
		{
			
			dist[i].value=m->quan[vi][i];
			if(m->quan[vi][i]==QUANZHI_NOT_REACHE) 	dist[i].pre=-1;
			else dist[i].pre=vi;
		
		}

	}

	s[vi]=1;
	//主循环
	for(i=0;i<m->vexnum;i++)
	{
		min=QUANZHI_NOT_REACHE;
		for(n=0;n<m->vexnum;n++)
		{
			if(s[n]==0&& dist[n].value<min)
			{
				min=dist[n].value;
				k=n;
			}

		}	
		if(k==vj) break;//如果计算到vj顶点，就跳出循环。
		//
		s[k]=1;
		for(j=0;j<m->vexnum;j++)
		{
			if(s[j]==0 && m->quan[k][j]<QUANZHI_NOT_REACHE && (dist[k].value+m->quan[k][j])<dist[j].value ) 
			{
				dist[j].value=dist[k].value+m->quan[k][j];
				dist[j].pre=k;

			}
		}

	}

	//打印输出
	printf("最小花费为：%d\n",dist[vj]);
	printf("%d%s<---",vj,m->v[vj].info);
	j=vj;
	while(j!=vi &&j!=-1)
	{
		j=dist[j].pre;
		printf("%d%s<---",j,m->v[j].info);								
	}
	printf("\b\b\b\b");	
	printf("    \n");
	
}



void main()
{
	int i,j,select,k=0;
	FILE *fp;
	Graph g;
	Graph_point s;
	s=&g;

	printf("1. 创建矩阵。2.求最短路径。 3.退出。请选择你要进行的操作,输入(1,2,3): ");
	scanf("%d",&select);
	while(k==0)
	{
		switch(select)
		{
			case 1:
				{
					createJuZhen(s);
					fp=fopen("short.bin","wb");
					fwrite(s,sizeof(Graph),1,fp);
					fclose(fp);
					printf("矩阵创建成功\n");

					printf("矩阵显示如下--------\n");
					display(s);
					printf("\n\n\n");
					printf("1. 创建矩阵。2.求最短路径。 3.退出。请继续选择你要进行的操作,输入(1,2,3): ");
					scanf("%d",&select);
					break;
				}
			case 2:
				{
					printf("请输入起始顶点：");
					scanf("%d",&i);
					printf("请输入末顶点：");
					scanf("%d",&j);
				
					fp=fopen("short.bin","rb");
					fread(s,sizeof(Graph),1,fp);
					fclose(fp);
					printf("矩阵显示如下--------\n");
					display(s);
					printf("\n\n\n");
					printf("最短路径如下-------\n");
					shortertpath_Dijstra(s,i,j);
					printf("1. 创建矩阵。2.求最短路径。 3.退出。请继续选择你要进行的操作,输入(1,2,3): ");
					scanf("%d",&select);
					break;

				}
			case 3:
				{
					k=1;
					break;

				}
			default:
				{
					printf("输入有误，请重新输入：");
					scanf("%d",&select);

				}

		}
	}
	
}