#include <bits/stdc++.h>
using namespace std;
struct Word      		//���ʽṹ��
{
int  time;				//���ʳ��ִ��� 
char ch[20];			//�洢���� 
} word[100000];
 
int select=1;			//select�����ж�ϵͳ�Ƿ�������У�Ĭ��Ϊ1,��������һ�Σ� 
bool cmp(Word a,Word b)
{
	return a.time>b.time;
}

void  readfile(char txt[],int num,char ch)		//��ȡӢ���ı���Ϣ���ܵ������� 
{												
   FILE *fp;
   int i=1;
   fp=fopen("data.txt","r");
   if(!fp)
   {
	   cout<<"���ļ�data.txtʧ��!"<<endl;
	   exit(0);
   }	
   ch=fgetc(fp);									//chΪ���µ�һ���ַ����ж������ļ��Ƿ�Ϊ�ա�
   if(ch!=EOF)
   {
     txt[0]=ch;
     for(i;!feof(fp);i++) 							//���δ���������ı�������
	 {
          txt[i]=fgetc(fp);							//��ȡ�ı������ı��еĸ����ַ��ŵ�txt������
	 }
     txt[i]='\0';									//����ַ����Ľ�����ʶ 
     num=i;											//��¼���ʵ�����
   }
     if(0==i)
	   cout<<"�ļ�Ϊ�գ���ѡ��Ӣ���ı����룡"<<endl;
   fclose(fp);
}

void  writefile(char txt[] ,int num, char ch)		//���ļ�д��Ӣ���ı���Ϣ
{
    char txt_str[100000];
    FILE *fp;
    char str=' ';
    getchar();
    int i=0;
    fp=fopen("data.txt","w");
    if(!fp)
    {
	   cout<<"���ļ�data.txtʧ��!"<<endl;;
    }
    cout<<"������:"<<endl;
    gets(txt_str);
    if(ch!=EOF)
    fputc(str,fp);
    fputs(txt_str,fp);								//������������д���ļ�
    strcat(txt,txt_str);
    readfile(txt,num,ch);
    fclose(fp);
}

void show(char txt[],int num,char ch)				//������� 
{
   if(ch==EOF)
          cout<<"�ļ�Ϊ�գ���ѡ��Ӣ���ı����룡"<<endl;
   else
          cout<<txt<<endl;
}

void sort(int k)			//���ֵ�˳����е�������
{
	int time;
	int i,j,t;
	char temp[20];  //�м���� 
	for(i=0;i<k-1;i++)
	{
		for(j=k-1;j>i;j--)
			if((strcmp(word[j].ch,word[j+1].ch)==1)) //�Ƚ��������ʣ�����һ�����ʴ���ǰһ�������е���
			{
             strcpy(temp,word[j].ch);//��������
             strcpy(word[j].ch,word[j+1].ch);
             strcpy(word[j+1].ch,temp);
             t=word[j].time;//��������Ƶ��
             word[j].time=word[j+1].time;
             word[j+1].time=t;
			}
	}
} 

void count(char *txt,char *b)				//ͳ�Ƶ���Ƶ��
{
	int j,i=0;//i��¼�ж��ٲ�ͬ�ĵ��ʣ�n��¼��ͬ���ʳ��ֵĴ���
	char *t;
	bool judge=false;
	int sum=0;
	FILE *fp;
	for(t=strtok(txt,b);t!=NULL;t=strtok(NULL,b))
	{ 
		sum++;//��������
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
   	
   	fp=fopen("˳������.txt","w");
    if(!fp)
    {
   		cout<<"���ļ�˳������.txtʧ��!"<<endl;
		exit(0);
	}	 
   	fprintf(fp,"��������Ϊ��%d\n",sum);////���������������ļ���
    for(j=0;j<i;j++)
   	{
		fprintf(fp,"%-16s\t%d\t%.4lf%\n",word[j].ch,word[j].time,word[j].time*100.0/sum);//�����ʡ�����Ƶ�������ļ���
	}
	cout<<"˳��������д��˳������.txt"<<endl;
	
	
   	sort(i);
   	fp=fopen("�ֵ�����.txt","w");
    if(!fp)
    {
   		cout<<"���ļ��ֵ�����.txtʧ��!"<<endl;
		exit(0);
	}
    for(j=0;j<i;j++)
   	{
		fprintf(fp,"%-16s\t%d\t%.4lf%\n",word[j].ch,word[j].time,word[j].time*100.0/sum);
	}
    cout<<"�ֵ�������д���ֵ�����.txt"<<endl; 
    
    fp=fopen("����Ƶ������.txt","w");
    if(!fp)
    {
   		cout<<"�򿪵���Ƶ������.txtʧ��!"<<endl;
		exit(0);
	}
	sort(word,word+i,cmp); 
    for(j=0;j<i;j++)
   	{
		fprintf(fp,"%-16s\t%d\t%.4lf%\n",word[j].ch,word[j].time,word[j].time*100.0/sum);
	}
    cout<<"����Ƶ��������д�뵥��Ƶ������.txt"<<endl; 
    
    fclose(fp); 
}
 
void menu()
{
    int choise,times=0;//times��¼�����е����ַ���
    char b[20]={',','.','?',':',' '};
	char txt[200000],ch;
	cout<<"1.��ʾӢ���ı�"<<endl;
	cout<<"2.��ʾ����������ȫ�����ʼ�Ƶ��"<<endl;
	cout<<"3.����Ӣ���ı�(�Ḳ��ԭ�ı�)"<<endl;
	cout<<"4.�˳�ϵͳ"<<endl;
    cout<<"��ѡ������Ҫ�Ĳ������(1-4)���س�ȷ��:"<<endl;
    readfile(txt,times,ch);
    cin>>choise;
    switch(choise)
  {
   	  case 1:show(txt,times,ch);break;
      case 2:count(txt,b);break;
      case 3:writefile(txt,times,ch);break;
      case 4:select=0;break;
      default:cout<<"����1-4֮��ѡ��\n"<<endl;break;
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

