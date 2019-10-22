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
bool is_have_v = false; //�ж��Ƿ�Ҫ������̬��һ��
/*****************************/
//solve_v
bool judge_alphabet(char c) {
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z') {
		return true;
	}
	return false;
}
vector<string> verb;
map<string, ll>verb_map;//�涯�ʵı��ε�ԭ���±�
map<string, ll>::iterator iter_verb;
ll sum_verb = 0;
/*************c***************/
struct solve_c_node {
	ll num;
	char c;
	double pinlv;
};

bool cmp_solve_c(solve_c_node x, solve_c_node y) {
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
	for (int i = 0; i < 26; i++) {
		sum[i].num = 0;
		sum[i].c = i + 'A';
		sum[i].pinlv = 0.0;
	}
	for (int i = 26; i < 52; i++) {
		sum[i].num = 0;
		sum[i].c = i + 'a' - 26;
		sum[i].pinlv = 0.0;
	}

	while (!book.eof()) {
		getline(book, str);
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] >= 'a' && str[i] <= 'z') {
				sum_alphabet++;
				sum[str[i] - 'a' + 26].num++;
			}
			else if (str[i] >= 'A' && str[i] <= 'Z') {
				sum_alphabet++;
				sum[str[i] - 'A'].num++;
			}
		}
	}
	book.close();

	for (int i = 0; i < 52; i++) {
		sum[i].pinlv = sum[i].num*1.0 / sum_alphabet;
		int temp = sum[i].pinlv * 100;
		sum[i].pinlv = temp*1.0 / 100; //С����λ��ʱ������ʱ������һ��
	}
	sort(sum, sum + 52, cmp_solve_c);
	cout << "Resule in TheFirstStep.txt" << endl;

	freopen("TheZerotStep.txt", "w", stdout);
	cout << "��ĸƵ��:" << endl;

	for (int i = 0; i < 52; i++) {
		cout << sum[i].c << "	";
		printf("%.2lf%\n", sum[i].pinlv*100);
	}
	fclose(stdout);
}

/************0****************/
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
bool cmp_solve_f(solve_f_node x, solve_f_node y) {
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
	while (!book.eof()) {
		getline(book, str);
		int size = str.size();
		string test_word;
		for (int i = 0; i < size; i++) {
			if (str[i] >= 'A'&&str[i] <= 'Z') //��д��ĸתСд
				str[i] = str[i] + 'a' - 'A';

			if (str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9') //��ǰλ����ĸ�����ּӵ������ַ�������
				test_word += str[i];

			else if (!test_word.empty() || (i == size - 1 && str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9')) {
				if (_x) { //_x����ȥ��ͣ�ʱ��еĵ��� ���test_word������ģ�clearȻ��continue
					iter_stopWord = stopWord.find(test_word);
					if (iter_stopWord == stopWord.end()) { //����ͣ�ʱ�û���������

					}
					else {
						test_word.clear();
						continue;
					}
				}
				iterfind = index_word.find(test_word);
				if (iterfind == index_word.end()) { //��û���ֹ�������ʣ����뵽vector��
					temp_word.word = test_word;
					word.push_back(temp_word);

					index_word[test_word] = sum_word;//���ʲ��뵽map��
					sum_word++;

					max_size = max(max_size, int(test_word.size()));
				}
				else { //��������ʣ�����+1
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
	cout << setw(max_size + 10) << setiosflags(ios::left) << "��������: " << endl;
	for (int i = 0; i < sum_word; i++) {
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


string getFile(int &start, char *argv[],int size) { //��start��ʼ���һ���ļ���,startָ���ļ������һ������
	string file;
	string kong_ge = " ";
//	cout <<"file="<< file << endl;
	string end = ".txt";
	for (; start < size; start++) {
		string te = argv[start];
		file += te;
		int t_size = te.size();
		int sum_deng = 0;
		if (t_size >= 4) {
			for (int i = t_size - 4, j = 0; j < 4; i++, j++) {
			//	cout << "te[i]=" << te[i] << " end[j]=" << end[j] << endl;
				if (te[i] != end[j]) {
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


int main(int argc, char* argv[])
{

	string file_book;
	bool _c = false; //����0 ��ĸƵ��    wf.exe -c <file name> 
	bool _f = false;// ����1 ����ļ������в��ظ��ĵ���    wf.exe -f <file>  
	bool _d = false;//����2 ��һ��Ŀ¼�����ļ�ִ�й���1 wf.exe -d <directory>
	string file_directory;
	bool _s = false;  //����2��չ������Ŀ¼��������Ŀ¼  wf.exe -d -s  <directory> 
	bool _n = false;   //����2��չ��������ִ�������ǰ n ������  wf.exe -d -s  <directory> -n <number> (_n������ǰ��)
	int number_n=-1;
	bool _x = false; //����1��չ ֧��ͣ�ʱ�  wf.exe -x <stopwordfile>  -f <file> 
	string file_stopword;
	bool _p = false; //����5  ���<number>���ʵĶ���    wf.exe -p <number>  <file> 
	int number_p;
	bool _v = false; //���Ϲ�����չ ֧�ֶ�����̬�Ĺ�һ��  wf.exe -v <verb file> .... 
	string file_verb;
	
	for (int start = 0; start < argc; start++) {
		if (strcmp(argv[start], "-c") == 0) {
			_c = true;
			start++;
			file_book = getFile(start, argv, argc);
		}
		else if (strcmp(argv[start], "-f") == 0) {
			_f = true;
			start++;
			file_book = getFile(start, argv, argc);
		}
		else if (strcmp(argv[start], "-d") == 0) {
			_d = true;
			start++;
			if (strcmp(argv[start], "-s") == 0) {
				_s = true;
				start++;
				file_directory = argv[start];
			}
			else
				file_directory = argv[start];
		}
		else if (strcmp(argv[start], "-n") == 0) {
			_n = true;
			number_n = 0;
			start++;
			string number = argv[start];
			int size = number.size();
			number_n = 0;
			for (int j = 0; j < size; j++)
				number_n = number_n * 10 + number[j] - '0';
		}
		else if (strcmp(argv[start], "-x") == 0) {
			_x = true;
			start++;
			file_stopword = getFile(start, argv, argc);
		}
		else if (strcmp(argv[start], "-p") == 0) {
			_p = true;
			start++;
	//		cout << "argv[start]=" << argv[start] << endl;
			string number = argv[start];
			int size = number.size();
			number_p = 0;
			for (int j = 0; j < size; j++)
				number_p = number_p * 10 + number[j] - '0';
			start++;
			file_book = getFile(start, argv, argc);

		}
		else if (strcmp(argv[start], "-v") == 0) {
			_v = true;
			start++;
			file_verb = getFile(start, argv, argc);
		}
	}


	//�����ж����
//	if (_v == true) { //����-v���� ֧�ֶ�����̬�Ĺ�һ��
//		is_have_v = true;
//		solve_v(file_verb);
//	}

	if (_c == true) { // �����ĸƵ��
//		cout << "_c=true file=" << file_book << endl;
		solve_c(file_book);
	}
	else if (_f == true && _x == false) { //����ļ������в��ظ��ĵ���
//		cout << "_f=true file=" << file_book << endl;
		solve_f(file_book);
	}
//	else if (_d == true) {
//	//	cout << "_d=true file_directory=" << file_directory<< endl;
//		solve_d(file_directory, _s, number_n);
//	}
//	else if (_x == true) {
////		cout << "_x=true file_stopword=" << file_stopword<<" file=" << file_book << endl;
//		solve_x(file_stopword, file_book);
//	}
//	else if (_p == true) {
//		solve_p(file_book, number_p);
//	}

	return 0;
}
