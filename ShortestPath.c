    /***********************************************************************
	************************************************************************
     author:wangkang  qq:417301568 e-mail: wangkang806@163.com 
	 begin time:2010-5-30
	 end time:
	************************************************************************
	************************************************************************/

#include <stdio.h>

#define VEXNUM_MAX 20  //������󶥵�����
#define QUANZHI_NOT_REACHE 10000 //����Ȩֵ���ɴ�ʱ��ֵ��
#define CityNameLength 20

typedef int Quanzhi;
typedef struct{

	int value;
	char info[CityNameLength];//��������
}Vex,*Vex_point;

typedef struct{

	Vex v[VEXNUM_MAX]; //��������
	Quanzhi quan[VEXNUM_MAX][VEXNUM_MAX]; //Ȩֵ
	int vexnum;//������
	int quannum;//Ȩ������ ��������

} *Graph_point, Graph;

/***********************************************************************
************************************************************************
 �����ڽӾ���
************************************************************************
************************************************************************/
void createJuZhen(Graph_point m)
{
	int i,j,k,citynum,x,y;
	Quanzhi z;
	char c[CityNameLength];

	
	printf("�������붥����Ŀ: ");
	scanf("%d",&i);
    m->vexnum=i;

	//�������ֵ��
	for(i=0;i<m->vexnum;i++)
	{
		for(j=0;j<m->vexnum;j++)
		{
			if(i==j) m->quan[i][j]=0;
			else m->quan[i][j]=QUANZHI_NOT_REACHE;
		}
	}

	printf("��������Ȩ����Ŀ: ");
	scanf("%d",&j);
    m->quannum=j;
    
	for(citynum=0;citynum<m->vexnum;citynum++)
	{
		printf("�������%d�㶥�����ĳ���:",citynum);
		scanf("%s",c);
		for(k=0;k<CityNameLength;k++)
		{	
			m->v[citynum].info[k]=c[k];
		}
		m->v[citynum].value=citynum;
	}


	for(i=0;i<m->quannum;i++)
	{
		printf("�������������㣺(�м�Ӷ���)");
		scanf("%d,%d",&x,&y);
		printf("�������������Ȩֵ(����֮���������÷���)��");
		scanf("%d",&z);
		m->quan[x][y]=z;
		m->quan[y][x]=z;

	}
	//printf("%s\n",m->v[0].info);
	//printf("%d",j);
}


/***********************************************************************
************************************************************************
 ��ʾ�ڽӾ����
************************************************************************
************************************************************************/

void display(Graph_point m)
{
	int i,j,k;
	printf("\t");
	for(i=0;i<m->vexnum;i++)  //�������
	{
		//printf("%8d",m->v[i].value); //�������
		printf("%8s",m->v[i].info);   //�����������
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
 ���·��   �õ���Dijstra�㷨��
************************************************************************
************************************************************************/
typedef struct{
	Quanzhi value; //Ȩֵ
	int pre;//ǰһ������
}dijstra,*dijstra_point;


void shortertpath_Dijstra(Graph_point m,int vi,int vj)
{
	Quanzhi min;  //���·��
	dijstra dist[VEXNUM_MAX];
	int s[VEXNUM_MAX]; //ĳ�������Ƿ���ʹ������ʹ�Ϊ1��û���ʹ�Ϊ0
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
	//��ѭ��
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
		if(k==vj) break;//������㵽vj���㣬������ѭ����
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

	//��ӡ���
	printf("��С����Ϊ��%d\n",dist[vj]);
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

	printf("1. ��������2.�����·���� 3.�˳�����ѡ����Ҫ���еĲ���,����(1,2,3): ");
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
					printf("���󴴽��ɹ�\n");

					printf("������ʾ����--------\n");
					display(s);
					printf("\n\n\n");
					printf("1. ��������2.�����·���� 3.�˳��������ѡ����Ҫ���еĲ���,����(1,2,3): ");
					scanf("%d",&select);
					break;
				}
			case 2:
				{
					printf("��������ʼ���㣺");
					scanf("%d",&i);
					printf("������ĩ���㣺");
					scanf("%d",&j);
				
					fp=fopen("short.bin","rb");
					fread(s,sizeof(Graph),1,fp);
					fclose(fp);
					printf("������ʾ����--------\n");
					display(s);
					printf("\n\n\n");
					printf("���·������-------\n");
					shortertpath_Dijstra(s,i,j);
					printf("1. ��������2.�����·���� 3.�˳��������ѡ����Ҫ���еĲ���,����(1,2,3): ");
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
					printf("�����������������룺");
					scanf("%d",&select);

				}

		}
	}
	
}