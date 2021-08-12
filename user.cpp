#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#define max 15
#define INTYTLY 32768
typedef struct tour_information
 {
	int id;//编号
	char name[20];//景点名称
	int price;//景点价格
    char introduce[50];//景点基本系介绍
 }tour_information;
typedef struct vex_date
{
	tour_information node[max];//顶点信息集
	int vex_relation[max][max];//边路线关系
	int node_number;//顶点数量
	int vex_number;//边数量
}vex_date;
typedef struct Prim_assist//Prim算法实现最小连通分量
{
  int assist_vex[max+1];
  int assist_node[max+1];
}assist;
typedef struct Dijistela_path//Dijikster算法实现最短路径
{
  int dict[max+1];
  int path_graphy[max+1][max+1];
}short_path;
//读取已有图的信息
vex_date* U_get_tour_information()
{
  vex_date *vex;
  char a[10];
  vex=(vex_date *)malloc(sizeof(vex_date));
  FILE *fp;
  fp=fopen("tour.txt","r+");
  fscanf(fp,"%d\n",&vex->node_number);
  for(int i=1;i<=vex->node_number;i++)
  {
   fscanf(fp,"%d\n",&vex->node[i].id);
   fscanf(fp,"%s\n",vex->node[i].name);  
   fscanf(fp,"%d\n",&vex->node[i].price);
   fscanf(fp,"%s\n",vex->node[i].introduce); 
  }
  fclose(fp);
  fp=fopen("vex.txt","r+");
  fscanf(fp,"%d\n",&vex->vex_number);
  for(int m=1;m<=vex->node_number;m++)
    {
    	for(int j=1;j<=vex->node_number;j++)
    	{
    		fscanf(fp,"%d\n",&vex->vex_relation[m][j]);
    	}
    }
    fclose(fp);
    return vex;
}
//显示信息
void U_display(vex_date *vex)
{ 
  printf("ID|:|Name|:|Price|:|Introduce\n");
  for(int i=1;i<=vex->node_number;i++)
  {
  printf("%d,%s,%d,%s\n",vex->node[i].id,vex->node[i].name,vex->node[i].price,vex->node[i].introduce);
  }
  printf("//////////////////////////////////////////////////////////\n");
  printf("The route is shown in the following figure\n");
  printf("%s::","view/run");
  for(int i=1;i<=vex->node_number;i++)
  	{
  	  printf("  %s ",vex->node[i].name);
  	}
  	printf("\n");
  for(int i=1;i<=vex->node_number;i++)
    {   
    	printf("%s::",vex->node[i].name);
    	for(int j=1;j<=vex->node_number;j++)
    	{ 
        if(vex->vex_relation[i][j]==INTYTLY)
        {
          printf("  %s  ","No!");
        }
        else
        {
    	   printf("   %d  ",vex->vex_relation[i][j]);
        }
    	}
    printf("\n");
    }
    printf("All the information has been shown!\n");
    printf("Press the key to return\n");
    getchar();
    return ;
}
///最短路径Dijkstra算法
void U_short_path_information(vex_date *vex)
{ 
  int start,end;
  int min,k,t;
  short_path *path;
  path=(short_path *)malloc(sizeof(path));
  int a=1;
  while(a)
  {
    printf("please enter where to start\n");
    scanf("%d",&start);
    getchar();
    printf("please enter where to end\n");
    scanf("%d",&end);
    getchar();
    printf("looking for.....\n");
   if(start>vex->node_number||end>vex->node_number||start<0||end<0)
    {
      printf("No relevent information!\n");
      printf("Plese enter the correct information Or break(0/1)?\n");
      scanf("%d",&a);
      getchar();
      continue;
    }
    else
    {
      sleep(1);
      printf("Successfully!\n");
      break;
    }
    break;
   }
   printf("suanfakasihi\n");
   //算法开始
   for(int i=1;i<=vex->node_number;i++)
   {
    path->dict[i]=vex->vex_relation[start][i];
    if(vex->vex_relation[start][i]!=INTYTLY)
    {
      path->path_graphy[i][1]=start;//标记每一个开始的位置
    }
   }
   path->path_graphy[start][0]=1;//加入确定的集合中 
   for(int i=2;i<=vex->node_number;i++)
   {
     min=INTYTLY;
     for(int j=1;j<=vex->node_number;j++)
     {
      if(path->path_graphy[j][0]!=1&&path->dict[j]<min)
      {
        min=path->dict[j];
        k=j;
      }
     }
      path->path_graphy[k][0]=1;
      for(int j=1;j<=vex->node_number;j++)
      {
        if(path->path_graphy[j][0]!=1&&vex->vex_relation[k][j]<INTYTLY&&path->dict[k]+vex->vex_relation[k][j]<path->dict[j])
        {
          path->dict[j]=path->dict[k]+vex->vex_relation[k][j];
          t=1;
          while(path->path_graphy[k][t]!=0)
          {
            path->path_graphy[j][t]=path->path_graphy[k][t];
            t++;
          }
          path->path_graphy[j][t]=k;
          path->path_graphy[j][k+1]=0;
        }
      }
   }
   for(int i=1;i<=vex->node_number;i++)
   {
    printf("%d ",path->path_graphy[end][i]);
   }
   printf("Display complete!\n");
   printf("Please press any key exit\n");
   free(path);
   getchar();
   return ;
}
//最小连通图prim算法
void U_assist_vex_information(vex_date *vex)
{
   assist *ass;
   int start;
   int k,min;
   ass=(assist *)malloc(sizeof(assist));
   printf("please enter the starting position!\n");
   scanf("%d",&start);
   getchar();    
   printf("looking for......\n");
   sleep(2);
   printf("Successfully!\n");
   ass->assist_vex[start]=0;
   for(int i=1;i<=vex->node_number;i++)
   { 
    if(i!=start)
    {
     ass->assist_vex[i]=vex->vex_relation[start][i];
     ass->assist_node[i]=vex->node[start].id;
    }
   }
   for(int i=2;i<=vex->node_number;i++)
   {
       min=INTYTLY;
       for(int j=1;j<=vex->node_number;j++)
       {
           if(ass->assist_vex[j]!=0&&ass->assist_vex[j]<min)
          {
            min=ass->assist_vex[j];
            k=j;
          }
       }
       printf("place: %s-->place: %s\n,distance= %d\n",vex->node[ass->assist_node[k]].name,vex->node[k].name,ass->assist_vex[k]);
       getchar();
       ass->assist_vex[k]=0;
       for(int m=1;m<vex->node_number;m++)
       {
        if(m!=k&&vex->vex_relation[k][m]<ass->assist_vex[m])
        {
          ass->assist_vex[m]=vex->vex_relation[k][m];
          ass->assist_node[m]=k;
        }
       }
    }
   printf("Display complete!\n");
   printf("Please press any key exit\n");
  // free(ass);
   getchar();
   return ;
}
//显示功能_1信息 
vex_date *U_display_information_1()
{
	vex_date *vex;
	vex=U_get_tour_information();
	U_display(vex);
  return vex;
}
//更新功能待开发
void U_refresh()
{
    printf("refrsh!!!\n");
    printf("......\n");
    sleep(2);
    printf("Successfully!!\n");
    sleep(1);
    return ;
} 
///用户界面
void U_menu()
{  
	int a=1;
  vex_date *vex;
	printf("You're enterd to Tour_intrdouce Apply\nstarting!!!\n");
	sleep(2);
  printf("It's ok!\n");
	while(a)
	{  
	 printf("*************Guide-Book***********\n");
	 printf("one.look all information\n");
	 printf("two.look stort ways to cities\n");
	 printf("three.look concent cities of stort ways\n");
	 printf("four.refresh system\n");
	 printf("five.break system\n");
	 printf("please choice to server for you!\n");
	 scanf("%d",&a);
   getchar();
	 switch(a)
	 {
	 	case 1:vex=U_display_information_1();
	 	break;
	 	case 2:U_short_path_information(vex);
	 	break;
	 	case 3:U_assist_vex_information(vex);
	 	break;
	 	case 4:U_refresh();
	 	break;
	 	case 5:a=0;
	 	break;
	 }
	}
	printf("Welcome next time!\n");
   sleep(2);
  printf("over quit!\n");
   sleep(1);
	return ;
}
int main()
{   
	U_menu();
}