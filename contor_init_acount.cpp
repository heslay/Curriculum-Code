#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#define max 15
#define Size 15
typedef struct message2
{
  char account[Size];
  char password[Size];
}message2;
typedef struct manger_mang
{
  message2 message[max];
  int manger_number;
}manger;
void save_manger_information(manger *mag)
{  
  getchar();
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
manger *create_new_account()
{ 
  manger *mag;
  mag=(manger *)malloc(sizeof(manger));
  mag->manger_number=0;
  char new_account[Size];
  char new_password[Size];
  char new_password1[Size];
  int a=1;
  while(a!=-1)
 {
  printf("please input your account information:\n");
  gets(new_account);
  getchar();
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
    printf("Information adopted!\n");
    printf("Is it use it?(0/1)\n");
    scanf("%d",&a);
    getchar();
    if(a==0)
    {
      printf("withdrawing!\n");
      continue ;
    }
    else if(a==-1)
    {
      break;
    }
    else
    { 
      mag->manger_number++;
      strcpy(mag->message[mag->manger_number].account,new_account);
      strcpy(mag->message[mag->manger_number].password,new_password1);
      printf("Creation successfully!\n");
     continue ;
    }
  }
  printf("ovew\n");
  getchar();
  return mag;
}
manger *look_manger_information()
{
  manger *mag;
  mag=(manger *)malloc(sizeof(manger));
  FILE *fp;
  fp=fopen("account.txt","r+");
  if(!fp)
  {
    printf("error");
    getchar();
  }
  fscanf(fp,"%d\n",&mag->manger_number);
   for(int i=1;i<=mag->manger_number;i++)
    {
      fscanf(fp,"%s\n",mag->message[i].account);
      fscanf(fp,"%s\n",mag->message[i].password);  
    }
    fclose(fp);
    return mag;
}
void display(manger *mag)
{
  for(int i=1;i<=mag->manger_number;i++)
  {
    puts(mag->message[i].account);
    puts(mag->message[i].password);
  }
}
int main()
{
  manger *mag,*mag1;
  mag=create_new_account();
  display(mag);
  getchar();
  save_manger_information(mag);
  mag1=look_manger_information();
  display(mag1);
}
/*     通用密码登录账户信息管理功能
//||||||||||||||*************************************||||||||||||||||||
//                        基本功能：账户信息管理                                 //
//||||||||||||||*************************************||||||||||||||||||
void display_manager(manger *mag)
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
void save_manger_information(manger *mag)
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
manger *look_manger_information()
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
int look_correct_account(manger *mag)
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
void delete_account(manger *mag)
{ 
    int a=look_correct_account(mag);
    int select;
    if(a==0)
    {
     printf("returning!\n");
     return ;
    }
    printf("your account information \n");
    printf("%s\n",mag->message[a].account);
    printf("%s\n",mag->message[a].account);
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
      save_manger_information(mag);
      printf("Delete successfully!\n");
      return ;
    }
}
//修改用户信息
void Modify_account(manger *mag)
{
    int b=look_correct_account(mag);
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
    printf("%s\n",mag->message[b].account);
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
      save_manger_information(mag);
      return ;
   }
} 
///登录身份核实
manger *identity_verification(int *k)
{
   manger *mag;
   mag=look_manger_information();
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
    printf("%d",m);
    getchar();
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
void Add_new_account(manger *mag)
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
      save_manger_information(mag);
      return ;
    }
}
//查看当前账户信息
manger *look_manger_all_information()
{ 
  manger *mag;
  mag=look_manger_information();
  display_manager(mag);
  return mag;
}
//密码信息
void account_manage(manger *mag)
{ 
  int a=1;
  while(a)
  {
    printf("one.   Look account All information\n");
    printf("two.   Add new account\n");
    printf("three. Modify account information\n");
    printf("four.  Delete account information\n");
    printf("five.  Break\n");
    printf("please choice for you!\n");
    scanf("%d",&a);
    getchar();
    switch(a)
    {
      case 1:mag=look_manger_all_information();
      break;
      case 2:Add_new_account(mag);
      break;
      case 3:Modify_account(mag);
      break;
      case 4:delete_account(mag);
      break;
      case 5:a=0;
      break;
    }
  }
}
////////////////////////////////////////////////////////
*/