#include "library.h"

/*
	������������:
	- displayTime:			չʾһ��ʱ����Ϣ������style����չʾ��ʽ��Ĭ��ֵΪ1
							style == 1:ֱ�Ӱ���ctime���صĸ�ʽ��ӡ����Mon Apr 13 10:51:17 2020
							style == 2:ֻ��ӡ�����գ���:2018��12��26��
							style == 3:����ʱ���ʽ����2020/4/13 11:04
	- displayShoppingCart:  չʾ���ﳵ���飬���û��Ѿ����빺�ﳵ�з������Ŀ
	- displayBill:			չʾ�˵�����
*/

void Reception::displayTime(int style)
{
	// ��ͨ��ctime�ɶ��ĵ���ʱ����ַ���
	time_t t;					// time_t���󴢴��˵���ʱ��
	time(&t);					// time()��������time_t�����ָ�룬��ϵͳʱ�����time_t����
	string curTime(ctime(&t));  // ctime()�������ݽ��յ�ϵͳʱ������������ʱ�䣬����char*
	strip(curTime, '\n');		// ͨ��strip����ȥ��curTime��β��\n

	// ���ա� ��split�Ի�õ�string�����Ի�ø�������ʱ������ڵĲ���
	vector<string> date;
	split(curTime, date, ' ');
	string MONTH("JanFebMarAprMayJunJulAugSepOctNovDec");

	// ��������ĸ�ʽ���ʹ�ӡʱ��
	if (style == 1) {
		cout << "����:" << curTime << endl;
	}
	if (style == 2) {
		cout << "����:" << date[4] << "��";
		cout << (MONTH.find(date[1]) / 3 + 1) << "��";
		cout << date[2] << "��" << endl;
	}
	if (style == 3) {
		cout << "����:" << date[4] << "/";
		cout << (MONTH.find(date[1]) / 3 + 1) << "/";
		cout << date[2] << " " << date[3] << endl;
	}
}

int Reception::displayShoppingCart(list<Sale>& shoppingCart)
{
	// ���ݹ��ﳵ�е������ø����ַ�������������Ҫ�����������
	int maxISBNLength = 8, maxBookNameLength = 8;
	for (list<Sale>::iterator it = shoppingCart.begin(); it != shoppingCart.end(); ++it) {
		maxISBNLength = max(maxISBNLength, strlen((*it).getIsbn()));
		maxBookNameLength = max(maxBookNameLength, strlen((*it).getBookTitle()));
	}
	// ��ӡ�Ϸ��б���Ϣ
	centerPrint((char*)"����", 3); cout << " | ";
	centerPrint((char*)"ISBN��", maxISBNLength); cout << " | ";
	centerPrint((char*)"����", maxBookNameLength); cout << " | ";
	centerPrint((char*)"����", 10); cout << " | ";
	centerPrint((char*)"���", 10); cout << " | ";
	cout << endl;

	string num;
	int listLength;				// ��ӡ�ı��Ŀ�ȣ���Ϊ�����ķ���ֵ
	// ѭ����ӡ������Ϣ
	for (list<Sale>::iterator it = shoppingCart.begin(); it != shoppingCart.end(); ++it) {
		num = numToStr((*it).getNum());
		centerPrint(num, 3); cout << "  | ";
		centerPrint((*it).getIsbn(), maxISBNLength); cout << " | ";
		centerPrint((*it).getBookTitle(), maxBookNameLength); cout << " | ";

		cout << "RMB"; printf("%6.2lf", (*it).getRetail()); cout << "  | ";
		cout << "RMB"; printf("%6.2lf", (*it).calcuSaleMoney()); cout << "  | ";
		cout << endl;
	}
	listLength = 3 + 4 + maxISBNLength + 3 + maxBookNameLength + 3 + 6 + 4 + 6 + 4 + 6;
	return listLength;
}

void Reception::displayBill(list<Sale>& shoppingCart)
{
	double totalSale = 0;
	for (list<Sale>::iterator it = shoppingCart.begin(); it != shoppingCart.end(); ++it) {
		totalSale += (*it).calcuSaleMoney();
	}
	double totalTax = totalSale * Sale::taxRate;
	double totalMoney = totalSale + totalTax;
	cout << "�����ܶ RMB ";
	printf("%6.2lf\n", totalSale);
	cout << "����˰��   RMB ";
	printf("%6.2lf\n", totalTax);
	cout << "Ӧ���ܶ RMB ";
	printf("%6.2lf\n", totalMoney);
}