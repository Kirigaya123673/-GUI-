#include "library.h"
/*
	���涨�弸��ȫ�ֺ���:
	- strToNum(char*):     ���������ֵ�char*�ַ���ת��Ϊ10��������
	- strToNum(string):    ���������ֵ�string�ַ���ת��Ϊ10��������

	- split(const string &, vector<string> &, const char flag = ' '):

						   ��python�е�split����һ�£�����һ������string
						   ����flag�����ݽ����и��������ڵڶ�����������
						   ��string������
	- strip(string&, const char):

						   ��python�е�strip��������һ�£���������ַ�������
						   βȥ���������ַ������������ַ�������β�ַ�������
						   ɾ�����ַ�������ͬ�������Ķ�
	- centerPrint(string &, int, char flag = ' '):
						   ���������һ���������ڶ���������ʾ���������ಿ
						   �ֻᱻflag����,flagĬ��Ϊ�ո�������С��string��
						   ���ȣ���᲻�����ε����string
	- getXY(int*, int*):   ����ָ���int��ַ����ȡ�������Ļ�ϵ�����(x,y)
	- goToXY(int, int):    ʹ����ƶ���ָ��������ȥ


*/

int strToNum(char* str)
{
	int num = 0;
	for (unsigned int i = 0; i < strlen(str); i++)
		num += (*(str + i) - '0') * pow(10, strlen(str) - i - 1);
	return num;
}

int strToNum(string str)
{
	int num = 0;
	for (unsigned int i = 0; i < str.length(); i++)
		num += (str[i] - '0') * pow(10, str.length() - i - 1);
	return num;
}

string numToStr(int x)
{
	string result;
	stringstream ss;		// ����������ss
	ss << x;				// ��int xת��Ϊ��ss
	ss >> result;			// ����ssת�����ַ���
	return result;
}

string numToStr(double x)
{
	string result;
	stringstream ss;		// ����������ss
	ss << x;				// ��int xת��Ϊ��ss
	ss >> result;			// ����ssת�����ַ���
	return result;
}


/*split����Ч��չʾ��

	string a = "apple-banana-pear";
	����'-'�ָ�õ���
	"apple" "banana" "pear"
	�ָ���������string�������У����ڶ����������õ�vector
*/
void split(const string& s, vector<string>& result, const char flag)
{
	result.clear();						// result������յ��и���������һ��ʼ�������һ��
	istringstream stimulateCin(s); 		// ģ�������һ������������ģ����������ݾ������ǵ�Ҫ�и�Ķ���
	string splitPiece;					// ��ʱ���ÿһ���и��С��

	while (getline(stimulateCin, splitPiece, flag)) {	// ʹ��getline������Ƭ�ζ�ȡ���ﵽ�и��Ч��
		result.push_back(splitPiece);
	}
}


/*strip����Ч��չʾ��
	string a = "\napple\n";
	��'\n'strip�õ���
	"apple"
	ԭstring�����"apple"

	��string a = "apple";
	��'\n'strip�����κα仯
*/
void strip(string& s, const char flag)
{
	string temp;
	for (unsigned i = 0; i < s.length(); i++) {
		// �����˵�����������������==flag
		if ((i == 0 || i == (s.length() - 1)) && s[i] == flag)
			continue;
		else
			temp += s[i];
	}
	s.swap(temp);
}

void centerPrint(string& s, int width, char flag)
{
	if (s.length() >= width)
		cout << s;
	else {
		int leftWid = (width - s.length()) / 2;
		int rightWid = width - leftWid - s.length();
		string leftStr(leftWid, flag), rightStr(rightWid, flag);
		cout << (leftStr + s + rightStr);
	}
}

void centerPrint(char* p, int width, char flag)
{
	if (strlen(p) >= width)
		cout << p;
	else {
		int leftWid = (width - strlen(p)) / 2;
		int rightWid = width - leftWid - strlen(p);
		string leftStr(leftWid, flag), rightStr(rightWid, flag), str(p);
		cout << (leftStr + str + rightStr);
	}
}

void getXY(int* x, int* y)
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &c);
	*x = c.dwCursorPosition.X;
	*y = c.dwCursorPosition.Y;
}

void goToXY(int x, int y)
{
	COORD p = { x,y };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, p);
}
