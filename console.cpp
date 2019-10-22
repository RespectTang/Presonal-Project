#include<cstring>
#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<vector>
#include<fstream>
#include <iomanip>
#include <io.h>
using namespace std;
typedef long long ll;
bool is_have_v = false; //判断是否要动词形态归一化
/*************000****************/
bool judge_alphabet(char c) 
{
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z') 
	{
		return true;
	}
	return false;
}
vector<string> verb;
map<string, ll>verb_map;//存动词的变形的原形下标
map<string, ll>::iterator iter_verb;
ll sum_verb = 0;

string getFile(int &start, char *argv[],int size) //从start开始获得一个文件名,start指向文件名最后一个单词
{ 
	string file;
	string kong_ge = " ";
//	cout <<"file="<< file << endl;
	string end = ".txt";
	for (; start < size; start++) 
	{
		string te = argv[start];
		file += te;
		int t_size = te.size();
		int sum_deng = 0;
		if (t_size >= 4) 
		{
			for (int i = t_size - 4, j = 0; j < 4; i++, j++) 
			{
			//	cout << "te[i]=" << te[i] << " end[j]=" << end[j] << endl;
				if (te[i] != end[j]) 
				{
					break;
				}
				else
					sum_deng++;
			}
		}
		if (sum_deng==4)
			break;

		file += kong_ge;
	}
	return file;
}

/*************c***************/
struct solve_c_node {
	ll num;
	char c;
	double pinlv;
};

bool cmp_solve_c(solve_c_node x, solve_c_node y) 
{
	if (x.pinlv == y.pinlv)
		return x.c < y.c;
	else
		return x.pinlv > y.pinlv;
}

void solve_c(string file)
{
	ifstream book;
	const char *strr=file.c_str();
	book.open(strr);
	string str;
	ll sum_alphabet = 0;
	solve_c_node sum[52];
	
	for (int i = 0; i < 26; i++) 
	{
		sum[i].num = 0;
		sum[i].c = i + 'A';
		sum[i].pinlv = 0.0;
	}
	for (int i = 26; i < 52; i++) 
	{
		sum[i].num = 0;
		sum[i].c = i + 'a' - 26;
		sum[i].pinlv = 0.0;
	}

	while (!book.eof()) 
	{
		getline(book, str);
		for (int i = 0; str[i] != '\0'; i++) 
		{
			if (str[i] >= 'a' && str[i] <= 'z') 
			{
				sum_alphabet++;
				sum[str[i] - 'a' + 26].num++;
			}
			else if (str[i] >= 'A' && str[i] <= 'Z') 
			{
				sum_alphabet++;
				sum[str[i] - 'A'].num++;
			}
		}
	}
	book.close();

	for (int i = 0; i < 52; i++) 
	{
		sum[i].pinlv = sum[i].num*1.0 / sum_alphabet;
		int temp = sum[i].pinlv * 100;
		sum[i].pinlv = temp*1.0 / 100; //小数多位的时候排序时和需求不一样
	}
	sort(sum, sum + 52, cmp_solve_c);
	cout << "Resule in TheFirstStep.txt" << endl;

	freopen("TheZerotStep.txt", "w", stdout);
	cout << "字母频率:" << endl;

	for (int i = 0; i < 52; i++) 
	{
		cout << sum[i].c << "	";
		printf("%.2lf%\n", sum[i].pinlv*100);
	}
	fclose(stdout);
}

/*************c***************/
/************f****************/
struct solve_f_node {
	string word;
	ll sum;
}temp_word;

vector<solve_f_node> word;
map<string, ll>index_word;
map<string, ll>::iterator iterfind;
map<string, ll>stopWord;
map<string, ll>::iterator iter_stopWord;
ll sum_word = 0;
int max_size = 0;

bool cmp_solve_f(solve_f_node x, solve_f_node y) 
{
	if (x.sum == y.sum)
		return x.word < y.word;
	else
		return x.sum > y.sum;
}

void first_step(string file, bool _x = false)
{
	temp_word.sum = 1;
	ifstream book;
	const char *strr=file.c_str();
	book.open(strr);
	string str;
	while (!book.eof()) 
	{
		getline(book, str);
		int size = str.size();
		string test_word;
		for (int i = 0; i < size; i++) 
		{
			if (str[i] >= 'A'&&str[i] <= 'Z') //大写字母转小写
				str[i] = str[i] + 'a' - 'A';

			if (str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9') //当前位是字母或数字加到单词字符串后面
				test_word += str[i];

			else if (!test_word.empty() || (i == size - 1 && str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9')) //_x代表去掉停词表中的单词 如果test_word是里面的，clear然后continue
			{
				if (_x) 
				{ 
					iter_stopWord = stopWord.find(test_word);
					if (iter_stopWord == stopWord.end()) //带表停词表没这这个单词
					{ 

					}
					else 
					{
						test_word.clear();
						continue;
					}
				}
				iterfind = index_word.find(test_word);
				if (iterfind == index_word.end()) 
				{ //还没出现过这个单词，插入到vector中
					temp_word.word = test_word;
					word.push_back(temp_word);

					index_word[test_word] = sum_word;//单词插入到map中
					sum_word++;

					max_size = max(max_size, int(test_word.size()));
				}
				else 
				{ //有这个单词，数量+1
					word[iterfind->second].sum++;
				}
				test_word.clear();
			}
		}
	}
	book.close();

}

/*************f***************/
// solve_f
void printf_solve_f()
{
	freopen("TheFirstStep.txt", "w", stdout);
	cout << "单词数量: " << endl;
	for (int i = 0; i < sum_word; i++) 
	{
		//printf("%s\t%d\n",word[i].word,word[i].sum);
		cout << word[i].word << ": " << word[i].sum << endl;
	}
	fclose(stdout);

}

void solve_f(string file)
{
	first_step(file);
	sort(word.begin(), word.end(), cmp_solve_f);
	cout << "The Result in TheFirstStep.txt" << endl;
	printf_solve_f();
}

/*************f***************/

/*************d***************/

void getAllFiles(string path, vector<string>& files)
{
	long hFile = 0;// 文件句柄
	struct _finddata_t fileinfo;	// 文件信息
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) // 保存文件的全路径
	{
		do 
		{
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个
		_findclose(hFile);
	}
}

void getAllFiles_zi_folder(string path, vector<string>& files) {
	
	long hFile = 0;//文件句柄
	struct _finddata_t fileinfo;//文件信息
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) 
	{
		do 
		{
			if ((fileinfo.attrib & _A_SUBDIR))  //比较文件类型是否是文件夹
			{ 
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) 
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);//递归搜索
				}
			}
			else 
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}

void printf_solve_d(int n)
{
	freopen("TheFirstStep-last.txt", "w", stdout);
	cout  << "单词" << "数量" << endl;

	int size_n = sum_word;
	if (n != -1)
		size_n = min((ll)n, sum_word);
	for (int i = 0; i < size_n; i++) 
	{
		cout << word[i].word << ": " << word[i].sum << endl;
		//cout << setw(max_size + 10 - word[i].word.size()) << setiosflags(ios::left) << word[i].word << word[i].sum << endl;
	}
	fclose(stdout);
}
void solve_d(string directory, bool _s, int _n) 
{
	vector<string>file;
	if (_s) 
	{ //遍历所有子目录
	
		getAllFiles_zi_folder(directory, file);
		int size = file.size();

		for (int i = 0; i < size; i++) 
		{
			if (file[i].substr(file[i].size() - 4) == ".txt") 
			{
				first_step(file[i]);
			}

		}
	}
	else 
	{
		
		getAllFiles(directory, file);
		int size = file.size();
		for (int i = 0; i < size; i++) 
		{
			if (file[i].substr(file[i].size() - 4) == ".txt") 
			{
				first_step(file[i]);
			}
		}
		
	}
	cout << "Result in FirstStep_last.txt" << endl;
	sort(word.begin(), word.end(), cmp_solve_f);
	printf_solve_d(_n);
}

int main(int argc, char* argv[])
{

	string file_book;
	bool _c = false; //母频率    wf.exe -c <file name> 
	bool _f = false;//出文件中所有不重复的单词    wf.exe -f <file>  
	bool _d = false;//一个目录所有文件执行功能1 wf.exe -d <directory>
	string file_directory;
	bool _s = false;  //历目录下所有子目录  wf.exe -d -s  <directory> 
	bool _n = false;   //输出出现次数最多的前 n 个单词  wf.exe -d -s  <directory> -n <number> (_n可能在前面)
	int number_n=-1;
	bool _x = false; //支持停词表  wf.exe -x <stopwordfile>  -f <file> 
	string file_stopword;
	bool _p = false; //输出<number>个词的短语    wf.exe -p <number>  <file> 
	int number_p;
	bool _v = false; //以上功能扩展 支持动词形态的归一化  wf.exe -v <verb file> .... 
	string file_verb;
	
	for (int start = 0; start < argc; start++) 
	{
		if (strcmp(argv[start], "-c") == 0) 
		{
			_c = true;
			start++;
			file_book = getFile(start, argv, argc);
		}
		else if (strcmp(argv[start], "-f") == 0) 
		{
			_f = true;
			start++;
			file_book = getFile(start, argv, argc);
		}
		else if (strcmp(argv[start], "-d") == 0) 
		{
			_d = true;
			start++;
			if (strcmp(argv[start], "-s") == 0) 
			{
				_s = true;
				start++;
				file_directory = argv[start];
			}
			else
				file_directory = argv[start];
		}
		else if (strcmp(argv[start], "-n") == 0) 
		{
			_n = true;
			number_n = 0;
			start++;
			string number = argv[start];
			int size = number.size();
			number_n = 0;
			for (int j = 0; j < size; j++)
				number_n = number_n * 10 + number[j] - '0';
		}
		else if (strcmp(argv[start], "-x") == 0) 
		{
			_x = true;
			start++;
			file_stopword = getFile(start, argv, argc);
		}
		else if (strcmp(argv[start], "-p") == 0) 
		{
			_p = true;
			start++;
			string number = argv[start];
			int size = number.size();
			number_p = 0;
			for (int j = 0; j < size; j++)
				number_p = number_p * 10 + number[j] - '0';
			start++;
			file_book = getFile(start, argv, argc);

		}
		else if (strcmp(argv[start], "-v") == 0) 
		{
			_v = true;
			start++;
			file_verb = getFile(start, argv, argc);
		}
	}


	//类型判断完后
//	if (_v == true) { //含有-v参数 支持动词形态的归一化
//		is_have_v = true;
//		solve_v(file_verb);
//	}

	if (_c == true) 
	{ // 输出字母频率
		solve_c(file_book);
	}
	else if (_f == true && _x == false) 
	{ //输出文件中所有不重复的单词
		solve_f(file_book);
	}
	else if (_d == true) 
	{//对每一个目录使用-f 
		solve_d(file_directory, _s, number_n);
	}
//	else if (_x == true) {
//		solve_x(file_stopword, file_book);
//	}
//	else if (_p == true) {
//		solve_p(file_book, number_p);
//	}

	return 0;
}
