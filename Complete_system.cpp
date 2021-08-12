/*
    ------------****************-----------
  作者  ：   郝韶阳                
  创作时间：  2019年12月20日
  创作地点：  西安邮电大学 
  项目名称：  旅游攻略小型系统
  项目简介：  城市交通的基本情况，可查询路线，修改路线景点信息
            最短连通路，最短路线,管理与用户分别使用
 *****************************************
*/
//C_为controller.cpp文件函数
//U_为user.cpp文件函数
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#define Size 15
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
	int vex_relation[max][max];//边关系
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
typedef struct message2//账户信息
{
  char account[Size];
  char password[Size];
}message2;
typedef struct manger_mang//账户信息
{
  message2 message[max];
  int manger_number;
}manger;
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//////////////////////////分界标记///////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
///----------------------Controller.cpp-------------------------//////
////////////////////////////////////////////////////////////////////
///
//||||||||||||||*************************************||||||||||||||||||
//                    附属功能：信息存储文件
//||||||||||||||*************************************||||||||||||||||||
//信息存储在文件中
void C_save_text(vex_date *vex,char *text,int k)
{
	  FILE *fp;
    fp=fopen(text,"w+");
    getchar();
    if(k==1)
   {
   	fprintf(fp,"%d\n",vex->node_number);
    for(int i=1;i<=vex->node_number;i++)
    {
    	fprintf(fp,"%d\n",vex->node[i].id);
      fprintf(fp,"%s\n",vex->node[i].name);  
      fprintf(fp,"%d\n",vex->node[i].price);
      fprintf(fp,"%s\n",vex->node[i].introduce);
    }
    fclose(fp);
    return ;
   }
  else if(k==2)
  { 
  	fprintf(fp,"%d\n",vex->vex_number);
    for(int i=1;i<=vex->node_number;i++)
    {
    	for(int j=1;j<=vex->node_number;j++)
    	{
    		fprintf(fp,"%d\n",vex->vex_relation[i][j]);
    	}
    }
    fclose(fp);
  }
  else
  {
    fclose(fp);
  	printf("errr\n");
  	return ;
  }
}
//||||||||||||||*************************************||||||||||||||||||
//                    功能五：建立新的图信息
//||||||||||||||*************************************||||||||||||||||||
///建立图的所有信息
vex_date* C_create_all_tour_information()
{
  vex_date *vex;
  vex=(vex_date *)malloc(sizeof(vex_date));
  printf("请输入景点个数和无向边的信息个数\n");
  scanf("%d,%d",&vex->node_number,&vex->vex_number);
  getchar();
  printf("请输入景点信息\n");
  for(int i=1;i<=vex->node_number;i++)
  { 
  	//vex->node[i]=(tour_information *)malloc(sizeof(tour_information));
  	vex->node[i].id=i;
  	printf("请输入第%d个景点信息\n",i);
    printf("请输入景点名称\n");
    gets(vex->node[i].name);
    getchar();
    printf("请输入景点价格\n");
    scanf("%d",&vex->node[i].price);
    getchar();
    printf("请输入景点基本信息\n");
    gets(vex->node[i].introduce);
    getchar();
  }
  C_save_text(vex,"tour.txt",1);
  printf("请输入%d个边的信息:\n",vex->vex_number);
  int vex_a,vex_b;
  for(int i=1;i<=vex->vex_number;i++)
  {
  	for(int j=1;j<=vex->vex_number;j++)
  	{
       vex->vex_relation[i][j]=INTYTLY;
  	}
  }
  for(int i=1;i<=vex->vex_number;i++)
  {
  	printf("请输入第%d条边的信息\n",i);
  	scanf("%d,%d",&vex_a,&vex_b);
  	getchar();
  	printf("请输入路程(公里)\n");
  	scanf("%d",&vex->vex_relation[vex_a][vex_b]);
  	getchar();
  	vex->vex_relation[vex_b][vex_a]=vex->vex_relation[vex_a][vex_b];
  }
  vex->vex_number=vex->vex_number*2;
  C_save_text(vex,"vex.txt",2);
  return vex;
}
//||||||||||||||*************************************||||||||||||||||||
//                    附属功能：显示图中信息
//||||||||||||||*************************************||||||||||||||||||//显示信息
void C_display(vex_date *vex)
{ 
  if(vex->node_number==0||vex->vex_number==0)
  {
    printf("the tour is full!\n");
    return ;
  }
  printf("%d views in there\n",vex->node_number);
  printf("ID|:|Name|:|Price|:|Introduce\n");
  for(int i=1;i<=vex->node_number;i++)
  {
  printf("%d,%s,%d,%s\n",vex->node[i].id,vex->node[i].name,vex->node[i].price,vex->node[i].introduce);
  }
  printf("//////////////////////////////////////////////////////////\n");
  printf("The route is shown in the following figure\n");
  printf("%d route in there\n",vex->vex_number);
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
//||||||||||||||*************************************||||||||||||||||||
//                    附属功能：获取已有图的信息
//||||||||||||||*************************************||||||||||||||||||
//获取已经存好的图信息
vex_date* C_get_tour_information()
{
  vex_date *vex;
  char a[10];
  vex=(vex_date *)malloc(sizeof(vex_date));
  FILE *fp;
  fp=fopen("tour.txt","r+");
  if(fp==NULL)
  {
    printf("no tour information!");
    return NULL;
  }
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
//||||||||||||||*************************************||||||||||||||||||
//                    功能一：显示所有信息功能
//||||||||||||||*************************************||||||||||||||||||
vex_date *C_dis_all_tour_information()
{
    vex_date *vex;
    vex=C_get_tour_information();
    if(vex)
    {
     C_display(vex);
    }
    return vex;
}
//||||||||||||||*************************************||||||||||||||||||
//                    功能二：修改边的信息
//||||||||||||||*************************************||||||||||||||||||
void C_add_new_init_route(vex_date *vex,int new_id)
{ 
  for(int i=1;i<=vex->node_number;i++)
  {
   vex->vex_relation[new_id][i]=INTYTLY;
   vex->vex_relation[i][new_id]=INTYTLY;
  }
  C_save_text(vex,"vex.txt",2);
}
//添加边-新的信息
void C_add_new_route(vex_date *vex)
{  
   int a=1;
   while(a)
   {
    int vex_a,vex_b,vex_weight;
    printf("please input new vex information(a,b)\n");
    scanf("%d,%d",&vex_a,&vex_b);
    getchar();
    printf("please input nex distance\n");
    scanf("%d",&vex_weight);
    getchar();
    if(vex->vex_relation[vex_a][vex_b]!=INTYTLY)
    {
      printf("the route had existent!\n");
      printf("try again!\n");
      continue;
    }
    while(a)
  {
    printf("Is it save it or not?(0/1)\n");
    {
      scanf("%d",&a);
      getchar();
    }
    if(a==1)
    {
      vex->vex_relation[vex_b][vex_a]=vex_weight;
      vex->vex_relation[vex_a][vex_b]=vex_weight;
      vex->vex_number++;
      vex->vex_number++;
      C_save_text(vex,"vex.txt",2);
      printf("Save successfully!\n");
      sleep(1);
      return ;
   }
   else if(a==0)
   {
    printf("withdrawing!:\n");
    sleep(1);
    return ;
   }
   else
   {
    continue;
   }
  }
 }
  return ;
}
///删除原来的边信息
void C_delete_route(vex_date *vex)
{  
   int a=1;
   while(a)
   {
    int vex_a,vex_b;
    printf("please input vex will been deleted information(a,b)\n");
    scanf("%d,%d",&vex_a,&vex_b);
    getchar();
     if(vex->vex_relation[vex_a][vex_b]==INTYTLY||vex_a<0||vex_b<0||vex_a>vex->node_number||vex_b>vex->node_number)
    {
      printf("the route had no existent!\n");
      printf("try again!\n");
      continue;
    }
    while(a)
  {
    printf("Is it save it or not?(0/1)\n");
    {
      scanf("%d",&a);
      getchar();
    }
    if(a==1)
    {
      vex->vex_relation[vex_b][vex_a]=INTYTLY;
      vex->vex_relation[vex_a][vex_b]=INTYTLY;
      vex->vex_number--;
      vex->vex_number--;
      C_save_text(vex,"vex.txt",2);
      printf("Delete successfully!\n");
      sleep(1);
      return ;
   }
   else if(a==0)
   {
    printf("withdrawing!:\n");
    sleep(1);
    return ;
   }
   else
   {
    continue;
   }
  }
 }
  return ;
}
//修改边路线信息
void C_revise_tour_information(vex_date *vex)
{ 
  int a=1;
  sleep(1);
  while(a)
  { 
    printf("one.add new route to tour:\n");//添加新的路线信息
    printf("two.delete route to tour:\n");//删除路线信息
    printf("three.break!\n");
    printf("please choice to server for you\n");
    scanf("%d",&a);
    getchar();
    switch(a)
    {
      case 1:C_add_new_route(vex);
      break;
      case 2:C_delete_route(vex);
      break;
      case 3:a=0;
      break;
    }
  }
  printf("Returning.....\n");
  return ;
}
//||||||||||||||*************************************||||||||||||||||||
//                   功能三：修改景点的信息
//||||||||||||||*************************************||||||||||||||||||
//添加新的景点信息
void C_add_new_view(vex_date *vex)
{   
    int a=1; 
    int k;
    k=vex->node_number+1;
    // printf("%d,%d\n",k,vex->vex_number);
    //getchar();
    printf("please input new information of view\n");
    printf("please input name\n");
    gets(vex->node[k].name);
    getchar();
    printf("plese input price\n");
    scanf("%d",&vex->node[k].price);
    getchar();
    printf("please input Introduction\n");
    gets(vex->node[k].introduce);
    getchar();
    while(a)
  {
    printf("Is it add it or not?(0/1)\n");
    scanf("%d",&a);
    getchar();
    if(a==1)
    {
      vex->node_number++;
      vex->node[vex->node_number].id=vex->node_number;
      C_save_text(vex,"tour.txt",1);
      C_add_new_init_route(vex,k);
      printf("add successfully!\n");
      sleep(1);
      return ;
    }
   else if(a==0)
   {
    printf("withdrawing!:\n");
    sleep(1);
    return ;
   }
   else
   {
    continue;
   }
  }
}
//修改新的景点信息
void C_update_new_view(vex_date *vex,int id,int k)
{ 
   char vex_name[20];
   int vex_price;
   char vex_introudce[50];
   int a=1;
   if(k==1)
   {
     printf("please input new name:\n");
     gets(vex_name);
     getchar();
     while(a)
     {
      printf("Whether to save it or not？(0/1)\n");
      scanf("%d",&a);
      getchar();
      if(a==1)
      {
        strcpy(vex->node[id].name,vex_name);
        C_save_text(vex,"tour.txt",1);
        printf("Save successfully\n");
        return ;
      }
      else if(a==0)
      {
        printf("withdrawing!\n");
        return ;
      }
      else
      {
        continue;
      }
     }
   }
   else if(k==2)
   {
     printf("plese input new price\n");
     scanf("%d",&vex_price);
     getchar();
     while(a)
     {
      printf("Whether to save it or not？(0/1)\n");
      scanf("%d",&a);
      getchar();
      if(a==1)
      {
        vex->node[id].price=vex_price;
        C_save_text(vex,"tour.txt",1);
        printf("Save successfully:\n");
        return ;
      }
      else if(a==0)
      {
        printf("withdrawing!\n");
        return ;
      }
      else
      {
        continue;
      }
     }
   }
   if(k==3)
   {
     printf("plese input new Introduction:\n");
     gets(vex_introudce);
     getchar();
     while(a)
     {
      printf("Whether to save it or not？(0/1)\n");
      scanf("%d",&a);
      getchar();
      if(a==1)
      {
        strcpy(vex->node[id].introduce,vex_introudce);
        C_save_text(vex,"tour.txt",1);
        printf("Save successfully!\n");
        return ;
      }
      else if(a==0)
      {
        printf("withdrawing!\n");
        return ;
      }
      else
      {
        continue;
      }
     }
   }
   return ;
}
//删除结点信息
void C_delete_view(vex_date *vex)
{  
   int det=1;
   int select;
   int k=vex->node_number;
   while(det)
   {
    printf("please enter what veiw do you want to delete:\n");
   scanf("%d",&det);
   getchar();
    if(det>vex->node_number||vex->node_number<0)
    {
      printf("the view is error!\n");
      printf("please try again or break(0/1)\n");
      scanf("%d",&select);
      getchar();
      if(select==0)
      {
        printf("returning!\n");
        return ;
      }
      else if(select==1)
      {
       continue;
      }
    }
    else
    {
      printf("look successfully!\n");
      break;
    }
   }
   printf("Do you sure delete it?\n(0/1)");
   scanf("%d",&select);
   getchar();
   if(select==1)
   {
      //vex->node[det].id=vex->node[k].id;
      vex->node[det].price=vex->node[k].price;
      strcpy(vex->node[det].name,vex->node[k].name);
      strcpy(vex->node[det].introduce,vex->node[k].introduce);
      for(int x=1;x<=vex->node_number;x++)
      {
        if(vex->vex_relation[det][x]!=INTYTLY)
        {
          vex->vex_number=vex->vex_number-2;
        }

      }
      for(int i=1;i<=vex->node_number;i++)
      { 
         if(i==det)
         {
          for(int j=1;j<=vex->node_number;j++)
               {
                if(j==i)
                {
                vex->vex_relation[j][j]= vex->vex_relation[k][k];
                continue;
                }
                vex->vex_relation[det][j]= vex->vex_relation[k][j];
               }
          continue;
         }
         vex->vex_relation[i][det]=vex->vex_relation[i][k];
      }
      vex->node_number--;
      C_save_text(vex,"tour.txt",1);
      C_save_text(vex,"vex.txt",2);
      printf("Save successfully!\n");
      return ;
   }
   else if(select==0)
   {
    printf("withdrawing!\n");
    return ;
   }
   else
   {
    printf("input error!\n");
    printf("returning!\n");
    return ;
   }
   return;

}
//更新新的景点信息
void C_update_view(vex_date *vex)
{ 
  int a;
  int id;
  while(1)
  {
    printf("please input id that you want to update:\n");
    scanf("%d",&id);
    getchar();
    if(id>vex->node_number||id<0)
    {
     printf("the view is not existent\n");
     printf("plese try again!\n");
     continue;
    }
    else
    {
      break;
    }
  }
  while(id)
  {
   printf("please choice to that you need to update:\n");
   printf("one   :  name\n");
   printf("two   :  price\n");
   printf("three :  introduce\n");
   printf("four  :   break!\n");
   scanf("%d",&a);
   getchar();
   switch(a)
   {
    case 1:C_update_new_view(vex,id,a);
    break;
    case 2:C_update_new_view(vex,id,a);
    break;
    case 3:C_update_new_view(vex,id,a);
    break;
    case 4:
    printf("returning!\n");
    sleep(1);
    return ; 
   }
 }
  return ;
}
//修改景点信息
void C_revise_view_information(vex_date *vex)
{ 
  int a=1;
  sleep(1);
  while(a)
  { 
    printf("one.   add new view spot to tour:\n");//添加新的景点信息
    printf("two.   update view sopt tour:\n");//修改景点信息
    printf("three. delete view sopt tour:\n");//删除景点信息
    printf("four.  break!\n");
    printf("please choice to server for you\n");
    scanf("%d",&a);
    getchar();
    switch(a)
    {
      case 1:C_add_new_view(vex);
      break;
      case 2:C_update_view(vex);
      break;
      case 3:C_delete_view(vex);
      break;
      case 4:a=0;
    }
  }
  printf("Returning.....\n");
  return ;
}
//||||||||||||||*************************************||||||||||||||||||
//                    功能四：更新页面功能-》待复杂开发
//||||||||||||||*************************************||||||||||||||||||
//更新信息功能
void C_update_information()
{
  printf("Updating.....\n");
  sleep(1);
  printf("Updating successfully!\n");
  return ;
}

//||||||||||||||*************************************||||||||||||||||||
//                        基本功能：账户信息管理                                 //
//||||||||||||||*************************************||||||||||||||||||
//显示信息
void C_display_manager(manger *mag)
{
  for(int i=1;i<=mag->manger_number;i++)
  {
    printf("the account information:\n");
    puts(mag->message[i].account);
    puts(mag->message[i].password);
    printf("\n");
  }
}
//信息存储文件中
void C_save_manger_information(manger *mag)
{  
   FILE *fp;
   fp=fopen("account.txt","w+");
   fprintf(fp,"%d\n",mag->manger_number);
   for(int i=1;i<=mag->manger_number;i++)
    {
      fprintf(fp,"%s\n",mag->message[i].account);
      fprintf(fp,"%s\n",mag->message[i].password);  
    }
    fclose(fp);
    return ;
}
//密码文件读取辨别身份
manger *C_look_manger_information()
{
  manger *mag;
  mag=(manger *)malloc(sizeof(manger));
  FILE *fp;
  fp=fopen("account.txt","r+");
  fscanf(fp,"%d\n",&mag->manger_number);
   for(int i=1;i<=mag->manger_number;i++)
    {
      fscanf(fp,"%s\n",mag->message[i].account);
      fscanf(fp,"%s\n",mag->message[i].password);  
    }
    fclose(fp);
    return mag;
}
//查找判断账户信息是否存在
int C_look_correct_account(manger *mag)
{
   int a=1;
   char new_account[Size];
   while(a)
   {
    printf("please input your account name!\n");
    gets(new_account);
    getchar();
    for(int i=1;i<=mag->manger_number;i++)
    {
     if(strcmp(mag->message[i].account,new_account)==0)
     {
      printf("Information adopted!\n");
      return i;
     }
   }
   printf("no information what you input!\n");
   printf("pleas try again(0/1)\n");
   scanf("%d",&a);
   getchar();
   if(a==0)
   {
    return 0;
   }
   else
   {
    continue;
   }
  }
 return 0;
}
//删除用户信息
void C_delete_account(manger *mag)
{ 
    int a=C_look_correct_account(mag);
    int select;
    if(a==0)
    {
     printf("returning!\n");
     return ;
    }
    printf("your account information \n");
    printf("%s\n",mag->message[a].account);
    printf("%s\n",mag->message[a].password);
    printf("Is it delete it?(0/1)\n");
    scanf("%d",&select);
    getchar();
    if(a==0)
    {
      printf("withdrawing!\n");
      return ;
    }
    else if(select==1)
    {
      strcpy(mag->message[a].account,mag->message[mag->manger_number].account);
      strcpy(mag->message[a].password,mag->message[mag->manger_number].password);
      mag->manger_number--;
      C_save_manger_information(mag);
      printf("Delete successfully!\n");
      return ;
    }
}
//修改用户信息
void C_Modify_account(manger *mag)
{   
    
    int b=C_look_correct_account(mag);
    int select=1;
    char new_password[Size];
    char new_password1[Size];
    if(b==0)
    {
     printf("returning!\n");
     return ;
    }
    printf("your account information \n");
    printf("%s\n",mag->message[b].account);
    printf("%s\n",mag->message[b].password);
    while(select)
   {
    printf("please input your new password:\n");
    gets(new_password);
    getchar();
    printf("please input your new password again!:\n");
    gets(new_password1);
    getchar();
    if(strcmp(new_password,new_password1)!=0)
    {
      printf("your two messsage are inconsistent!\n");
      printf("please try again!\n");
      continue;
    }
    else
    {
      printf("Information adopted!\n");
      break;
    }
  }
    printf("Is it save it?(0/1)\n");
    scanf("%d",&select);
    getchar();
    if(select==0)
    {
      printf("withdrawing!\n");
      return ;
    }
    else
    { 
      strcpy(mag->message[b].password,new_password1);
      printf("Creation successfully!\n");
      C_save_manger_information(mag);
      return ;
   }
} 
///登录身份核实
manger *C_identity_verification(int *k)
{
   manger *mag;
   mag=C_look_manger_information();
   char acc[Size];
   char pass[Size];
   printf("you have three opportunities to entry!\n");
   int opportunity=3;
   int m;
   while(opportunity--)
   { 
     m=1;
     printf("please input your account information:\n");
     gets(acc);
     getchar();
     printf("please input your password:\n");
     gets(pass);
     getchar();
     for(int i=1;i<=mag->manger_number;i++,m++)
     {
       if(strcmp(mag->message[i].account,acc)==0)
      {
          if(strcmp(mag->message[i].password,pass)==0)
         {
          printf("Information adopted!\n");
          *k=1;
          return mag;
         }
          else
         {
         printf("the password is wrong!\n");
         printf("please input correct information for the password!\n");
         break;
         }
      }
      else
      { 
        continue;
      }
    }
      if(m>mag->manger_number)
       {
        printf("the account is wrong!\n");
        printf("please input correct information for the account!\n");
        continue;
       }
    }
    printf("Login information has been frozen!\n");
    *k=0;
    return NULL;
}
//添加新管理用户信息
void C_Add_new_account(manger *mag)
{ 
  char new_account[Size];
  char new_password[Size];
  char new_password1[Size];
  int a=1;
  printf("please input your account information:\n");
  gets(new_account);
  getchar();
  while(a)
  {
    printf("please input your password:\n");
    gets(new_password);
    getchar();
    printf("please input your password again!:\n");
    gets(new_password1);
    getchar();
    if(strcmp(new_password,new_password1)!=0)
    {
      printf("your two messsage are inconsistent!\n");
      printf("please try again!\n");
      continue;
    }
    else
    {
      printf("Information adopted!\n");
      break;
    }
  }
    printf("Is it use it?(0/1)\n");
    scanf("%d",&a);
    getchar();
    if(a==0)
    {
      printf("withdrawing!\n");
      return ;
    }
    else
    { 
      mag->manger_number++;
      strcpy(mag->message[mag->manger_number].account,new_account);
      strcpy(mag->message[mag->manger_number].password,new_password1);
      printf("Creation successfully!\n");
      C_save_manger_information(mag);
      return ;
    }
}
//查看当前账户信息
manger *C_look_manger_all_information()
{ 
  manger *mag;
  mag=C_look_manger_information();
  C_display_manager(mag);
  return mag;
}
//密码信息
void C_account_manage(manger *mag)
{ 
  int a=1;
  while(a)
  { 
    printf("**********@@@@@@@@@@@@**********\n");
    printf(" |one.   Look account All information\n");
    printf(" |two.   Add new account\n");
    printf(" |three. Modify account information\n");
    printf(" |four.  Delete account information\n");
    printf(" |five.  Break\n");
    printf("please choice for you!\n");
    scanf("%d",&a);
    getchar();
    switch(a)
    {
      case 1:mag=C_look_manger_all_information();
      break;
      case 2:C_Add_new_account(mag);
      break;
      case 3:C_Modify_account(mag);
      break;
      case 4:C_delete_account(mag);
      break;
      case 5:a=0;
      break;
    }
  }
}
//||||||||||||||*************************************||||||||||||||||||
//                        内核：菜单                                 //
//||||||||||||||*************************************||||||||||||||||||
void C_meun()
{ 
  int a=1;
  int k;
  manger *mag;//
  mag=C_identity_verification(&k);//
  if(k==0)
  {
    printf("please look into your account information!\n");
    return ;
  }
  printf("Success to enter!\n");
  sleep(1);
  printf("Tourism management system!\n");
  sleep(1);
  while(a)
  {  
   vex_date *vex;
   sleep(1);
   printf(">>>>>>>>>>>>>>Guide-Book<<<<<<<<<<<<<<\n");
   printf("===========================================\n");
   printf("  |one.look all information\n");//查询所有信息
   printf("  |two.Modify route information for tour\n");//修改路线信息
   printf("  |three.Modify scenic spot information for tour\n");//修改景点信息
   printf("  |four.create new tour information\n");////创建新的旅游信息
   printf("  |five. Account manage\n");///账户信息管理
   printf("  |six.refresh system\n");//刷新系统
   printf("  |seven.break system\n");//退出
   printf("===========================================\n");
   printf("\n");
   printf("    ~~~~please choice to server for you!\n");
   scanf("%d",&a);
   getchar();
   switch(a)
   {
    case 1:vex=C_dis_all_tour_information();
    break;
    case 2:C_revise_tour_information(vex);
    break;
    case 3:C_revise_view_information(vex);
    break;
    case 4:vex=C_create_all_tour_information();
    break;
    case 5:C_account_manage(mag);
    break;
    case 6:C_update_information();
    break;
    case 7:a=0;
    break;
   }
  }
  printf("Welcome next time!\n");
  printf("over quit!\n");
  sleep(1);
  return ;
}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//////////////////////////分界标记///////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
///----------------------User.cpp-------------------------//////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
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
   //printf("suanfakasihi\n");
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
   printf("start: ");
   for(int i=1;i<=vex->node_number;i++)
   {
    if(path->path_graphy[end][i])
    {
      printf("%s-->",vex->node[path->path_graphy[end][i]].name);
    }
   }
   printf("end: %s\n",vex->node[end].name);
   printf("\n");
   printf("Display complete!\n");
   printf("Please press any key exit\n");
   //free(path);
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
      // printf("%d",k);
      // getchar();
       printf("place: %s-->place: %s\n,distance= %d\n",vex->node[ass->assist_node[k]].name,vex->node[k].name,ass->assist_vex[k]);
       sleep(1);
       ass->assist_vex[k]=0;
       for(int m=1;m<=vex->node_number;m++)
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
   //ass=NULL;
   //free(ass);
   getchar();
   return ;
}
//显示功能_1信息 
vex_date *U_display_information_1()
{
  vex_date *vex;
  vex=U_get_tour_information();//获取已有图
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
void U_meun()
{  
  int a=1;
  vex_date *vex;
  printf("You're enterd to Tour_intrdouce Apply\nstarting!!!\n");
  sleep(2);
  printf("It's ok!\n");
  vex=U_display_information_1();
  while(a)
  {  
   printf("*************Guide-Book***********\n");
   printf("=======================================\n");
   printf("  |one.look all information\n");
   printf("  |two.look stort ways to cities\n");
   printf("  |three.look concent cities of stort ways\n");
   printf("  |four.refresh system\n");
   printf("  |five.break system\n");
   printf("=======================================\n");
   printf("\n");
   printf("  please choice to server for you!\n");
   scanf("%d",&a);
   getchar();
   switch(a)
   {
    case 1:U_display(vex);
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
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//////////////////////////分界标记///////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////**********主函数*********//////
int main()
{  
  int a=1;
  sleep(1);
  printf("Welcome to use system!\n");
  sleep(1);
  printf("Loading.....\n");
  sleep(1);
  printf("Success!\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("-----------------**********Projext********------------------------\n");
  printf("@Author       :  shaoyang Hao\n");                
  printf("Creation time :  20th,December,2019\n");
  printf("Creation Place:  Xi'an University of Posts\n"); 
  printf("Project Name  :  Tourism strategy small systrm\n");
  printf("Introduction  :  Basic information of urban traffic\n");
  printf("                ,modification of informa_tion about\n");
  printf("                 city,and the choice ofUrban path...etc.\n");  
  printf("==================================================================\n");   
  printf("******************************************************************\n");
  getchar();
  while(a)
 {
   printf("*************System_tour***********\n");
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("  ||| one.controller go!\n");
   printf("  ||| two.user go!\n");
   printf("  ||| three.break\n");
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("\n");
   printf("please choice to server for you!\n");
   scanf("%d",&a);
   getchar();
   switch(a)
   {
     case 1:C_meun();
     break;
     case 2:U_meun();
     break;
     case 3:
     sleep(2);a=0;
     break;
   }
  }
  sleep(1);
  printf("see you again!\n");
}