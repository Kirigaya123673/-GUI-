
#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<iomanip>
#include<cctype>
#include<algorithm>
#include<string>
#include<vector>
#include<list>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<windows.h>
#include<sstream>
#include<fstream>
#include<ctime>
#include<conio.h>
using namespace std;

#define EXP extern "C" _declspec(dllexport)



/*
	- ������Ҫ����
	- TitleInfo:  ����ͼ��Ļ�����Ϣ�� ��Ҫ���������������硢ISBN��
				  �����ߵȣ��Լ�����Щ��Ա�Ĳ�������
	- BookData:   �����࣬�̳���TitleInfo�࣬�����˶�TitleInfo����
				  ���ݳ�Ա��������������Լ�����Щ��Ա�����Ĳ�������
	- Sale:       ��BookData�����࣬���ڴ������۹���
	- Report:     ��Ӧ<����ģ��>�Ĺ��ܺ������ɼ����������ɣ���û�ж�
				  �����ݳ�Ա�������޶�������Χ�����ã��ڲ����Ǿ�̬
				  ������Ա����Щ�������뱨�����й�
	- Management: ��Ӧ<����ģ��>�Ĺ��ܺ�������Report�������ƣ�ֻ�о�
				  ̬������Ա����Щ�����Ĺ��ܶ�����������й�
	- Reception:  ��Ӧ<����ģ��>�Ĺ��ܺ�������Report�������ƣ�ֻ�о�
				  ̬������Ա����Щ�����Ĺ��ܶ��������й�
*/

class TitleInfo
{
protected:
	char isbn[65];        // ���ISBN��
	char bookTitle[51];   // ����
	char author[31];      // ������
	char publisher[31];   // �����������
	char dateAdded[11];   // �������������ڣ�����2017-1-1
	int qtyOnHand;        // ��Ÿ���Ŀ����
	double wholesale;     // ��Ÿ���������۸�
	double retail;        // ��Ÿ�������ۼ�

public:
	// TitleInfo��Ĺ��캯��
	TitleInfo()
	{
		isbn[0] = '\0';
		bookTitle[0] = '\0';
		author[0] = '\0';
		publisher[0] = '\0';
		dateAdded[0] = '\0';
		this->qtyOnHand = 0;
		this->wholesale = 0;
		this->retail = 0;
	}
	TitleInfo(char* isbn, char* bookTitle, char* author,
		char* publisher, char* dateAdded, int qty,
		double whole, double retail)
	{
		strcpy(this->isbn, isbn);
		strcpy(this->bookTitle, bookTitle);
		strcpy(this->author, author);
		strcpy(this->publisher, publisher);
		strcpy(this->dateAdded, dateAdded);
		this->qtyOnHand = qty;
		this->wholesale = whole;
		this->retail = retail;
	}

	TitleInfo(const char* isbn, const char* bookTitle, const char* author,
		const char* publisher, const char* dateAdded, int qty,
		double whole, double retail)
	{
		strcpy(this->isbn, isbn);
		strcpy(this->bookTitle, bookTitle);
		strcpy(this->author, author);
		strcpy(this->publisher, publisher);
		strcpy(this->dateAdded, dateAdded);
		this->qtyOnHand = qty;
		this->wholesale = whole;
		this->retail = retail;
	}

	// �������ݳ�Ա�ĺ���
	void setIsbn(char* str) { strcpy_s(this->isbn, str); }
	void setBookTitle(char* str) { strcpy_s(this->bookTitle, str); }
	void setAuthor(char* str) { strcpy_s(this->author, str); }
	void setPublisher(char* str) { strcpy_s(this->publisher, str); }
	void setDateAdded(char* str) { strcpy_s(this->dateAdded, str); }
	void setQtyOnHand(int x) { this->qtyOnHand = x; }
	void setWholesale(double x) { this->wholesale = x; }
	void setRetail(double x) { this->retail = x; }

	// �������ݳ�Ա�ĺ���
	char* getIsbn() { return this->isbn; }
	char* getBookTitle() { return this->bookTitle; }
	char* getAuthor() { return this->author; }
	char* getPublisher() { return this->publisher; }
	char* getDateAdded() { return this->dateAdded; }
	int getQtyOnHand() { return this->qtyOnHand; }
	double getWholesale() { return this->wholesale; }
	double getRetail() { return this->retail; }

};

class BookData : public TitleInfo
{
public:
	// BookData�Ĺ��캯��
	BookData() {}
	BookData(char* isbn, char* bookTitle, char* author,
		char* publisher, char* dateAdded, int qty,
		double whole, double retail)
		: TitleInfo(isbn, bookTitle, author, publisher, dateAdded, qty, whole, retail)
	{}

	// ���忽�����캯��
	BookData(const BookData& obj)
	{
		strcpy(this->isbn, obj.isbn);
		strcpy(this->bookTitle, obj.bookTitle);
		strcpy(this->author, obj.author);
		strcpy(this->publisher, obj.publisher);
		strcpy(this->dateAdded, obj.dateAdded);
		this->qtyOnHand = obj.qtyOnHand;
		this->wholesale = obj.wholesale;
		this->retail = obj.retail;
	}

	// ���ظ�ֵ�����
	BookData& operator=(const BookData right)
	{
		if (this == &right) return *this;
		strcpy(this->isbn, right.isbn);
		strcpy(this->bookTitle, right.bookTitle);
		strcpy(this->author, right.author);
		strcpy(this->publisher, right.publisher);
		strcpy(this->dateAdded, right.dateAdded);
		this->qtyOnHand = right.qtyOnHand;
		this->wholesale = right.wholesale;
		this->retail = right.retail;
	}

	// չʾ���ȫ����Ϣ
	void displayInfo(int width1 = 5, int width2 = 7);

};

class Sale :public BookData
{
private:
	int num;					// �����鹺�������

public:
	static double taxRate;		// ˰�ʣ������κ�һ���飬˰����ͬ������Ϊ��̬����

	// �������캯�������в�����һ��BookData������Ϊ�������ǻ���BookData�����ʼ��Sale
	Sale(const BookData& book) :BookData(book)
	{
		num = 0;
	}

	Sale(const BookData& book, int num) :BookData(book)
	{
		this->num = num;
	}

	void setNum(int x) { num = x; }
	int getNum() { return num; }
	double calcuSaleMoney();			// ����ñ����ܵ����۶�
	double calcuTax();					// ����ñ���Ӧ����˰
	double calcuTotalMoney();			// ����ñ����ܵ�Ӧ����Ǯ

};

class Report
{
public:
	/*����������
		- listAll:        �г����������ͼ���������Ϣ
		- listByWholesale:�г����������ͼ��������ۡ�������Լ��������ܶ�
		- listByRetail:   �г����������ͼ������ۼۡ�������Լ����ۼ��ܶ�
		- listByNum:	  �ȶ�ͼ�鰴������Ӵ�С����Ȼ���г�����ͼ��Ŀ����
		- listByValue:    �ȶ�ͼ�鰴ÿ���������ܶ�Ӵ�С��������Ȼ���г����
						  ������ͼ��������ۡ�������Լ��������ܶ�
		- listByDate:     �ȶ�ͼ�鰴�������������Ȼ���г����������ͼ�������
	*/
	static void listAll(list<BookData>&);
	static void listByWholesale(list<BookData>&);
	static void listByRetail(list<BookData>&);
	static void listByNum(list<BookData>&, bool reverse = false);
	static void listByValue(list<BookData>&, bool reverse = false);
	static void listByDate(list<BookData>&, bool reverse = false);
	static bool cmpByNum1(BookData&, BookData&);
	static bool cmpByNum2(BookData&, BookData&);
	static bool cmpByValue1(BookData&, BookData&);
	static bool cmpByValue2(BookData&, BookData&);
	static bool cmpByDate1(BookData&, BookData&);
	static bool cmpByDate2(BookData&, BookData&);
};

class Management
{
public:

	/* ��������ĺ���:
			- strUpper:       ������ָ��ָ����ַ�����Сд��ĸת���ɴ�д��ĸ
			- lookUpBook:     Ҫ���û�����������Ȼ��������в��Ҹ��飬���û�ҵ�
							  ����Ļ����ʾһ��������Ϣ���Ա��������û�и��顣��
							  ���ҵ��˸��飬����BookInfo�еĺ�������ʾ�������Ϣ��
							  ֧��ģ�����ң���ƥ���г����������ߣ������纬�йؼ���
							  ������ƥ����
			- increaseBook:   ������Ŀ��Ҫ���û������������Ŀ�ĸ�����Ϣ
			- editBook:       Ҫ���û��������޸ĵ���Ϣ��������ͬ��֧��ģ�����ң���û
							  ���ҵ�������������ʾ���ҵ��ˣ�����ֹһ������������û�
							  �����н��������ѡ��
			- deleteBook:     Ҫ���û�������Ҫɾ��������������ú�������������в�
							  �ң����û���ҵ���Ӧ���飬��ô����һ����ʾ��Ϣ�����
							  �ҵ��˸��飬��ô�ʹ�BookData������������ȥ���飬����
							  ��ɾ����Ŀǰ���������ʾ��Ϣ��ʹ�û�ȷ��ɾ������
			- changeRate:	  �޸�˰��
			- checkIsbn:      ��������isbn���Ƿ���ϸ�ʽҪ��
			- checkDateAdded: �����������ʱ���Ƿ���ϸ�ʽҪ��
			- isLY:           �ж��Ƿ�Ϊ����
			- checkDate:      �ж�������������������յ�������ɵ������Ƿ���Ϲ淶
		*/
	static char* strUpper(char*);
	static void lookUpBook(list<BookData>&);
	static void increaseBook(list<BookData>&);
	static void editBook(list<BookData>&);
	static void deleteBook(list<BookData>&);
	static void changeTaxRate();
	static bool checkIsbn(char*);
	static bool checkDateAdded(char*);
	static bool isLY(int);
	static bool checkDate(int, int, int);
};

class Reception
{
	/*
		������������:
		- displayTime:			չʾһ��ʱ����Ϣ����������չʾ��ʽ
		- displayShoppingCart:  չʾ�˵����飬���û��Ѿ����빺�ﳵ�з��룬�����б�Ŀ��
		- displayBill:			չʾ�˵�����
	*/
public:
	static void displayTime(int style = 1);
	static int displayShoppingCart(list<Sale>&);
	static void displayBill(list<Sale>&);
};





/*(��Global Function�ж��������º���)
	������������ȫ�ֺ���:
	- strToNum(char*):     ���������ֵ�char*�ַ���ת��Ϊ10��������
	- strToNum(string):    ���������ֵ�string�ַ���ת��Ϊ10��������
	- numToStr(int):	   ��int������ת����string�ַ���
	- numToStr(double):	   ��double������ת����string�ַ���

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

int strToNum(char*);
int strToNum(string);
string numToStr(int);
string numToStr(double);
void split(const string&, vector<string>&, const char);
void strip(string&, const char);
void centerPrint(string&, int, char flag = ' ');
void centerPrint(char*, int, char flag = ' ');
void getXY(int*, int*);
void goToXY(int, int);

/*(��Module�ж��������µ�ģ�麯��)
	ģ�飺���շ�����������ģ�飬�������˵�������ģ�顢����ģ��ͱ���ģ��
		  ������Ϊ��Ҫ��������ʵĴ�����������BookData���ͶԵ�list
	��ʱ�䣬��Ҫ��������ģ�飬�Է��������������������������
*/

int mainMenuModule(list<BookData>&);					// ���˵�ģ�飬�����û�ѡ�
void receptionModule(list<BookData>&);					// ����ģ��
void managementModule(list<BookData>&);				// ������ģ��
void reportModule(list<BookData>&);					// ����ģ��
void resetModule(list<BookData>&, list<BookData>&);		// ����ģ��

#endif // !TEST_H


