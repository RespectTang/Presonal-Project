#include <bits/stdc++.h>
using namespace std;
struct Word      		//单词结构体
{
int  time;				//单词出现次数 
char ch[20];			//存储单词 
} word[100000];
 
int select=1;			//select用于判断系统是否继续运行（默认为1,至少运行一次） 
bool cmp(Word a,Word b)
{
	return a.time>b.time;
}

void  readfile(char txt[],int num,char ch)		//获取英文文本信息及总单词数量 
{												
   FILE *fp;
   int i=1;
   fp=fopen("data.txt","r");
   if(!fp)
   {
	   cout<<"打开文件data.txt失败!"<<endl;
	   exit(0);
   }	
   ch=fgetc(fp);									//ch为文章第一个字符，判断文章文件是否为空。
   if(ch!=EOF)
   {
     txt[0]=ch;
     for(i;!feof(fp);i++) 							//如果未遇到读入文本结束符
	 {
          txt[i]=fgetc(fp);							//获取文本，将文本中的各个字符放到txt数组中
	 }
     txt[i]='\0';									//添加字符串的结束标识 
     num=i;											//记录单词的总数
   }
     if(0==i)
	   cout<<"文件为空，请选择英文文本输入！"<<endl;
   fclose(fp);
}

void  writefile(char txt[] ,int num, char ch)		//向文件写入英文文本信息
{
    char txt_str[100000];
    FILE *fp;
    char str=' ';
    getchar();
    int i=0;
    fp=fopen("data.txt","w");
    if(!fp)
    {
	   cout<<"打开文件data.txt失败!"<<endl;;
    }
    cout<<"请输入:"<<endl;
    gets(txt_str);
    if(ch!=EOF)
    fputc(str,fp);
    fputs(txt_str,fp);								//将新增的文章写入文件
    strcat(txt,txt_str);
    readfile(txt,num,ch);
    fclose(fp);
}

void show(char txt[],int num,char ch)				//输出单词 
{
   if(ch==EOF)
          cout<<"文件为空，请选择英文文本输入！"<<endl;
   else
          cout<<txt<<endl;
}

void sort(int k)			//按字典顺序进行单词排序
{
	int time;
	int i,j,t;
	char temp[20];  //中间变量 
	for(i=0;i<k-1;i++)
	{
		for(j=k-1;j>i;j--)
			if((strcmp(word[j].ch,word[j+1].ch)==1)) //比较两个单词，若后一个单词大于前一个，进行调换
			{
             strcpy(temp,word[j].ch);//交换单词
             strcpy(word[j].ch,word[j+1].ch);
             strcpy(word[j+1].ch,temp);
             t=word[j].time;//交换单词频数
             word[j].time=word[j+1].time;
             word[j+1].time=t;
			}
	}
} 

void count(char *txt,char *b)				//统计单词频数
{
	int j,i=0;//i记录有多少不同的单词，n记录相同单词出现的次数
	char *t;
	bool judge=false;
	int sum=0;
	FILE *fp;
	for(t=strtok(txt,b);t!=NULL;t=strtok(NULL,b))
	{ 
		sum++;//单词总数
		strcpy(word[i].ch,t);
		(word[i].time)=1;
		for(j=0;j<i;j++)
			if(strcmp(word[i].ch,word[j].ch)==0)
			{
				(word[j].time)++;
				judge=true;
			}
		if(judge)
			i--;
   		i++;
   		judge=false;
	}
   	i=i-1;
   	
   	fp=fopen("顺序排序.txt","w");
    if(!fp)
    {
   		cout<<"打开文件顺序排序.txt失败!"<<endl;
		exit(0);
	}	 
   	fprintf(fp,"单词总数为：%d\n",sum);////将单词总数读到文件中
    for(j=0;j<i;j++)
   	{
		fprintf(fp,"%-16s\t%d\t%.4lf%\n",word[j].ch,word[j].time,word[j].time*100.0/sum);//将单词、单词频数读到文件中
	}
	cout<<"顺序排序已写入顺序排序.txt"<<endl;
	
	
   	sort(i);
   	fp=fopen("字典排序.txt","w");
    if(!fp)
    {
   		cout<<"打开文件字典排序.txt失败!"<<endl;
		exit(0);
	}
    for(j=0;j<i;j++)
   	{
		fprintf(fp,"%-16s\t%d\t%.4lf%\n",word[j].ch,word[j].time,word[j].time*100.0/sum);
	}
    cout<<"字典排序已写入字典排序.txt"<<endl; 
    
    fp=fopen("单词频数排序.txt","w");
    if(!fp)
    {
   		cout<<"打开单词频数排序.txt失败!"<<endl;
		exit(0);
	}
	sort(word,word+i,cmp); 
    for(j=0;j<i;j++)
   	{
		fprintf(fp,"%-16s\t%d\t%.4lf%\n",word[j].ch,word[j].time,word[j].time*100.0/sum);
	}
    cout<<"单词频数排序已写入单词频数排序.txt"<<endl; 
    
    fclose(fp); 
}
 
void menu()
{
    int choise,times=0;//times记录文章中的总字符数
    char b[20]={',','.','?',':',' '};
	char txt[200000],ch;
	cout<<"1.显示英文文本"<<endl;
	cout<<"2.显示单词总数、全部单词及频数"<<endl;
	cout<<"3.输入英文文本(会覆盖原文本)"<<endl;
	cout<<"4.退出系统"<<endl;
    cout<<"请选择您需要的操作序号(1-4)按回车确认:"<<endl;
    readfile(txt,times,ch);
    cin>>choise;
    switch(choise)
  {
   	  case 1:show(txt,times,ch);break;
      case 2:count(txt,b);break;
      case 3:writefile(txt,times,ch);break;
      case 4:select=0;break;
      default:cout<<"请在1-4之间选择\n"<<endl;break;
   }
}
 
int main(int args,char* argv[])
{ 
  	while(select)
	{
		menu();
	}
	return 0;
} 

