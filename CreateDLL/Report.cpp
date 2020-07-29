#include "library.h"

/*����������
	- listAll:        �г����������ͼ���������Ϣ
	- listByWholesale:�г����������ͼ��������ۡ�������Լ��������ܶ�
	- listByRetail:   �г����������ͼ������ۼۡ�������Լ����ۼ��ܶ�
	- listByNum:	  �ȶ�ͼ�鰴������Ӵ�С����Ȼ���г�����ͼ��Ŀ����
	- listByValue:    �ȶ�ͼ�鰴ÿ���������ܶ�Ӵ�С��������Ȼ���г����
					  ������ͼ��������ۡ�������Լ��������ܶ�
	- listByDate:     �ȶ�ͼ�鰴�������������Ȼ���г����������ͼ������ڣ�
					  ͨ���������������Ծ����ǴӾ��鵽���������Ǵ����鵽��
					  ������Ĭ�ϴ����鵽����
	- cmp:			  ����������߼�
	- reverse:		  ����һ�������������������йصĺ�����������������������
					  ��Ĭ��ֵΪfalse���������������򣨴�С���󣩣�����Ϊtrue
					  ����Ϊ�������򣨴Ӵ�С��
*/


void Report::listAll(list<BookData>& books)
{
	cout << "����й���" << books.size() << "����:" << endl;
	int haveShow = 0;
	int x, y;
	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
		haveShow++;
		cout << endl << " book " << haveShow << " :\n" << endl;
		(*it).displayInfo();

		// ������Ļԭ��ÿ��ֻ����ʾ���������Ϣ
		if (haveShow % 2 == 0) {
			cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
			getchar();
			getXY(&x, &y);			// ��ȡ�������
			goToXY(x, y - 1);		// �˻ص���һ��
			cout << setw(50) << " ";// �����ʾ��Ϣ
			goToXY(x, y - 2);       // ���˵���һ��
		}
	}
	cout << endl << "(�����ߡ���)/�Ѿ�������~~" << endl << endl;
}

void Report::listByWholesale(list<BookData>& books)
{
	cout << "����й���" << books.size() << "����:" << endl;
	int haveShow = 0;
	int x, y;
	int width1 = 5, width2 = 7;

	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
		haveShow++;
		cout << " book " << haveShow << " :\n" << endl;
		cout << setw(width1) << " " << setw(width2) << "ISBN  ��" << ": " << (*it).getIsbn() << endl;
		cout << setw(width1) << " " << setw(width2) << "��    ��" << ": " << (*it).getBookTitle() << endl;
		cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << (*it).getWholesale() << "Ԫ/��" << endl;
		cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << (*it).getQtyOnHand() << endl;
		cout << setw(width1) << " " << setw(width2) << "�������ܶ�" << ": ";
		printf("%.2lfԪ\n\n", (double)(*it).getQtyOnHand() * (*it).getWholesale());


		// ������Ļԭ��ÿ��ֻ����ʾ���������Ϣ
		if (haveShow % 2 == 0) {
			cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
			getchar();
			getXY(&x, &y);			// ��ȡ�������
			goToXY(x, y - 1);		// �˻ص���һ��
			cout << setw(50) << " ";// �����ʾ��Ϣ
			goToXY(x, y - 2);       // ���˵���һ��
		}
	}
	cout << endl << "(�����ߡ���)/�Ѿ�������~~" << endl << endl;
}

void Report::listByRetail(list<BookData>& books)
{
	cout << "����й���" << books.size() << "����:" << endl;
	int haveShow = 0;
	int x, y;
	int width1 = 5, width2 = 7;

	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
		haveShow++;
		cout << " book " << haveShow << " :\n" << endl;
		cout << setw(width1) << " " << setw(width2) << "ISBN  ��" << ": " << (*it).getIsbn() << endl;
		cout << setw(width1) << " " << setw(width2) << "��    ��" << ": " << (*it).getBookTitle() << endl;
		cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << (*it).getRetail() << "Ԫ/��" << endl;
		cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << (*it).getQtyOnHand() << endl;
		cout << setw(width1) << " " << setw(width2) << "���ۼ��ܶ�" << ": ";
		printf("%.2lfԪ\n\n", (double)(*it).getQtyOnHand() * (*it).getRetail());


		// ������Ļԭ��ÿ��ֻ����ʾ���������Ϣ
		if (haveShow % 2 == 0) {
			cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
			getchar();
			getXY(&x, &y);			// ��ȡ�������
			goToXY(x, y - 1);		// �˻ص���һ��
			cout << setw(50) << " ";// �����ʾ��Ϣ
			goToXY(x, y - 2);       // ���˵���һ��
		}
	}
	cout << endl << "(�����ߡ���)/�Ѿ�������~~" << endl << endl;
}

void Report::listByNum(list<BookData>& books, bool reverse)
{
	// �Ȱ��տ��������Ȼ�󰴲��Ͱ�
	int haveShow = 0;						// ��¼�Ѿ�չʾ����ı���
	int width1 = 5, width2 = 7;				// ����������
	int x, y;								// ��ȡ�������ı���

	// ����reverse��ΪfalseΪĬ�ϵ�����
	if (reverse == false)
		books.sort(cmpByNum1);
	else
		books.sort(cmpByNum2);

	// �����������
	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
		haveShow++;
		cout << endl << " book " << haveShow << " :\n" << endl;
		cout << setw(width1) << " " << setw(width2) << "ISBN  ��" << ": " << (*it).getIsbn() << endl;
		cout << setw(width1) << " " << setw(width2) << "��    ��" << ": " << (*it).getBookTitle() << endl;
		cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << (*it).getQtyOnHand() << endl;

		// ������Ļԭ��ÿ��ֻ����ʾ���������Ϣ
		if (haveShow % 2 == 0) {
			cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
			getchar();
			getXY(&x, &y);			// ��ȡ�������
			goToXY(x, y - 1);		// �˻ص���һ��
			cout << setw(50) << " ";// �����ʾ��Ϣ
			goToXY(x, y - 2);       // ���˵���һ��
		}
	}
	cout << endl << "(�����ߡ���)/�Ѿ�������~~" << endl << endl;
}

void Report::listByValue(list<BookData>& books, bool reverse)
{
	// �Ȱ��տ��������Ȼ�󰴲��Ͱ�
	int haveShow = 0;						// ��¼�Ѿ�չʾ����ı���
	int width1 = 5, width2 = 7;				// ����������
	int x, y;								// ��ȡ�������ı���

	// ����reverse��ΪfalseΪĬ�ϵ�����
	if (reverse == false)
		books.sort(cmpByValue1);
	else
		books.sort(cmpByValue2);

	// �����������
	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
		haveShow++;
		cout << " book " << haveShow << " :\n" << endl;
		cout << setw(width1) << " " << setw(width2) << "ISBN  ��" << ": " << (*it).getIsbn() << endl;
		cout << setw(width1) << " " << setw(width2) << "��    ��" << ": " << (*it).getBookTitle() << endl;
		cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << (*it).getWholesale() << "Ԫ/��" << endl;
		cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << (*it).getQtyOnHand() << endl;
		cout << setw(width1) << " " << setw(width2) << "�������ܶ�" << ": ";
		printf("%.2lfԪ\n\n", (double)(*it).getQtyOnHand() * (*it).getWholesale());


		// ������Ļԭ��ÿ��ֻ����ʾ���������Ϣ
		if (haveShow % 2 == 0) {
			cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
			getchar();
			getXY(&x, &y);			// ��ȡ�������
			goToXY(x, y - 1);		// �˻ص���һ��
			cout << setw(50) << " ";// �����ʾ��Ϣ
			goToXY(x, y - 2);       // ���˵���һ��
		}
	}
	cout << endl << "(�����ߡ���)/�Ѿ�������~~" << endl << endl;
}

void Report::listByDate(list<BookData>& books, bool reverse)
{
	// �Ȱ��տ��������Ȼ�󰴲��Ͱ�
	int haveShow = 0;						// ��¼�Ѿ�չʾ����ı���
	int width1 = 5, width2 = 7;				// ����������
	int x, y;								// ��ȡ�������ı���

	// ����
	if (reverse == false)
		books.sort(cmpByDate1);
	else
		books.sort(cmpByDate2);

	// �����������
	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
		haveShow++;
		cout << " book " << haveShow << " :\n" << endl;
		cout << setw(width1) << " " << setw(width2) << "ISBN  ��" << ": " << (*it).getIsbn() << endl;
		cout << setw(width1) << " " << setw(width2) << "��    ��" << ": " << (*it).getBookTitle() << endl;
		cout << setw(width1) << " " << setw(width2) << "��������" << ": " << (*it).getDateAdded() << endl << endl;

		// ������Ļԭ��ÿ��ֻ����ʾ���������Ϣ
		if (haveShow % 2 == 0) {
			cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
			getchar();
			getXY(&x, &y);			// ��ȡ�������
			goToXY(x, y - 1);		// �˻ص���һ��
			cout << setw(50) << " ";// �����ʾ��Ϣ
			goToXY(x, y - 2);       // ���˵���һ��
		}
	}
	cout << endl << "(�����ߡ���)/�Ѿ�������~~" << endl << endl;
}

// ����
bool Report::cmpByNum1(BookData& book1, BookData& book2)
{
	return (book1.getQtyOnHand() < book2.getQtyOnHand());

	return (book1.getQtyOnHand() > book2.getQtyOnHand());
}

// ����
bool Report::cmpByNum2(BookData& book1, BookData& book2)
{
	return (book1.getQtyOnHand() > book2.getQtyOnHand());
}

// ����
bool Report::cmpByValue1(BookData& book1, BookData& book2)
{
	return (((int)book1.getQtyOnHand() * book1.getWholesale()) < ((int)book2.getQtyOnHand() * book2.getWholesale()));
}

// ����
bool Report::cmpByValue2(BookData& book1, BookData& book2)
{
	return (((int)book1.getQtyOnHand() * book1.getWholesale()) > ((int)book2.getQtyOnHand() * book2.getWholesale()));
}

// ����(�Ӿ��鵽����)
bool Report::cmpByDate1(BookData& book1, BookData& book2)
{
	// �Ȱ���-���ָ�������
	vector<string> date1, date2;
	split(book1.getDateAdded(), date1, '-');
	split(book2.getDateAdded(), date2, '-');

	// �༶�Ƚϣ����ȼ�Ϊ: �� > �� > ��
	if (strToNum(date1[0]) != strToNum(date2[0]))
		return (strToNum(date1[0]) < strToNum(date2[0]));
	if (strToNum(date1[1]) != strToNum(date2[1]))
		return (strToNum(date1[1]) < strToNum(date2[1]));
	return (strToNum(date1[2]) < strToNum(date2[2]));
}

// ����(�����鵽����)
bool Report::cmpByDate2(BookData& book1, BookData& book2)
{
	// �Ȱ���-���ָ�������
	vector<string> date1, date2;
	split(book1.getDateAdded(), date1, '-');
	split(book2.getDateAdded(), date2, '-');

	// �༶�Ƚϣ����ȼ�Ϊ: �� > �� > ��
	if (strToNum(date1[0]) != strToNum(date2[0]))
		return (strToNum(date1[0]) > strToNum(date2[0]));
	if (strToNum(date1[1]) != strToNum(date2[1]))
		return (strToNum(date1[1]) > strToNum(date2[1]));
	return (strToNum(date1[2]) > strToNum(date2[2]));
}
