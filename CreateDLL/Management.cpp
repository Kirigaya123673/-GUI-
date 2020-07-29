#include "library.h"
#define _CRT_SECURE_NO_WARNINGS

/* ��������ĺ���:
		- strUpper:       ������ָ��ָ����ַ�����Сд��ĸת���ɴ�д��ĸ
		- lookUpBook:     Ҫ���û�����������Ȼ��������в��Ҹ��飬���û�ҵ�
						  ����Ļ����ʾһ��������Ϣ���Ա��������û�и��顣��
						  ���ҵ��˸��飬����BookInfo�еĺ�������ʾ�������Ϣ��
						  ֧��ģ�����ң���ƥ���г����������ߣ������纬�йؼ���
						  ������ƥ����
		- increaseBook:   ������Ŀ��Ҫ���û������������Ŀ�ĸ�����Ϣ���������Ϣ
						  ��������Ч�Լ��
		- editBook:       Ҫ���û��������޸ĵ���Ϣ��������ͬ��֧��ģ�����ң���û
						  ���ҵ�������������ʾ���ҵ��ˣ�����ֹһ������������û�
						  �����н��������ѡ���ҵ��������û�ѡ���������е�
						  һ����������޸ģ����һ�ѯ���û��Ƿ�ѡ���޸�ȫ����Ϣ��
						  ÿһ���ж϶���������Ч�Լ��
		- deleteBook:     Ҫ���û�������Ҫɾ��������������ú�������������в�
						  �ң����û���ҵ���Ӧ���飬��ô����һ����ʾ��Ϣ�����
						  �ҵ��˸��飬��ô�ʹ�BookData������������ȥ���飬����
						  ��ɾ����Ŀǰ���������ʾ��Ϣ��ʹ�û�ȷ��ɾ������
		- checkIsbn:      ��������isbn���Ƿ���ϸ�ʽҪ��
		- checkDateAdded: �����������ʱ���Ƿ���ϸ�ʽҪ��
		- isLY:           �ж��Ƿ�Ϊ����
		- checkDate:      �ж�������������������յ�������ɵ������Ƿ���Ϲ淶
*/
/*
		ϣ���Ľ��ĵط�:
		1.����չʾ��Ŀ��Ϣ�ĺ������պ�չʾ��������Ŀ���򲻴��������س�����ʾ���ࡱ����ʾ��Ϣ������75�д���
		2.editBook�����п��Բ���Ҫչʾ������������û��޸��Ѿ�չʾ�������Ϣ
*/

char* Management::strUpper(char* str)
{
	char* p;
	p = new char[strlen(str) + 1];
	strcpy(p, str);
	for (unsigned int i = 0; i < strlen(str); ++i)
		*(p + i) = toupper(*(p + i));
	return p;
}

void Management::lookUpBook(list<BookData>& books)
{
	string bookName;				// �û����������
	int bookNum = 0;				// �洢�ܹ����ҵ�����Ŀ������
	list<BookData> tempDict;		// ��ʱ�洢���ܷ���Ҫ���BookData����

	cout << "��Ҫ���ҵ�����: ";
	cin >> bookName; cin.ignore();

	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
		/*
			- validFind��ʾ������ָ��ָ��ĵ�ǰ�������ǲ��Ƿ��ϲ���Ҫ��
			- ���õ�ǰ����Եĳ�Ա�����ʼ��string���󣬷�������Ӵ�
			- ��Ϊ���ҷ�ʽΪģ�����ң�����ֻҪbookName����������string����
			  �е�һ��string���Ӵ����϶�Ϊ����Ҫ��
		*/
		string currBookName((*it).getBookTitle()),
			currAuthor((*it).getAuthor()),
			currPulisher((*it).getPublisher());
		bool validFind = (currBookName.find(bookName) + 1)
			|| (currAuthor.find(bookName) + 1)
			|| (currPulisher.find(bookName) + 1);
		if (validFind) {
			bookNum++;
			tempDict.push_back(BookData(*it));
		}
	}

	if (bookNum == 0) cout << "(�����ߡ���)/I��m sorry~ ��û���ҵ�����鼮......" << endl;
	else {
		cout << "��Ϊ���ҵ�" << bookNum << "�����йؼ���\"" << bookName << "\"�Ľ��(' �� �� ��')" << endl;
		int haveShow = 0;							// �Ѿ���ʾ�Ľ����Ŀ
		int x, y;									// ��ǰ�������Ļ�ϵ�����

		for (list<BookData>::iterator it = tempDict.begin(); it != tempDict.end(); ++it) {
			haveShow++;
			cout << endl << " book " << haveShow << " :\n" << endl;
			(*it).displayInfo();


			// ÿ��ʾ2�������ͣһ��
			if (haveShow % 2 == 0 && (it != tempDict.end())) {
				cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
				getchar();							// �����û�����Ļس���
				getXY(&x, &y);						// ��ȡ�������
				goToXY(x, y - 1);					// �˵���һ��
				cout << setw(50) << " ";			// �����ʾ��Ϣ
				goToXY(x, y - 2);					// ���˵���һ��
			}
		}
		cout << endl << "(�����ߡ���)/�Ѿ�������~~" << endl << endl;
	}
}

void Management::increaseBook(list<BookData>& books)
{
	cout << "������������Ŀ�Ļ�����Ϣ:" << endl << endl;
	char isbn[14];
	char bookTitle[51];
	char author[31];
	char publisher[31];
	char dateAdded[11];
	int qtyOnHand;
	double wholesale;
	double retail;

	int width1 = 3, width2 = 10;

	do {
		cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "ISBN  ��" << ": ";
		cin.getline(isbn, 14);
		if (!checkIsbn(isbn)) cout << "�������isbn���벻���ϸ�ʽ,����������:(��ʽΪ������\'-\'�����,����\'-\'���ܳ����ڿ�ͷ���β����������\'-\'��������)" << endl;
	} while (!checkIsbn(isbn));

	cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "��    ��" << ": ";
	cin.getline(bookTitle, 51);

	cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": ";
	cin.getline(author, 31);

	cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": ";
	cin.getline(publisher, 31);

	do {
		cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "��������" << ": ";
		cin >> dateAdded; cin.ignore();
		if (!checkDateAdded(dateAdded)) cout << "�������ʱ���ʽ����,����������:(��ʽΪX-X-X,������-��-��,����2017-1-1)" << endl;
	} while (!checkDateAdded(dateAdded));

	do {
		cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": ";
		cin >> qtyOnHand; cin.ignore();
		if ((qtyOnHand < 0) || (fabs(qtyOnHand - (int)qtyOnHand) > 1e-6)) cout << "������Ŀ��������,����������:(��ȷ��������ǷǸ�����)" << endl;
	} while ((qtyOnHand < 0) || (fabs(qtyOnHand - (int)qtyOnHand) > 1e-6));

	do {
		cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��(Ԫ/��)" << ": ";
		cin >> wholesale; cin.ignore();
		if (wholesale <= 0) cout << "�����������������,����������:(��ȷ�����������ʵ��)" << endl;
	} while (wholesale <= 0);

	do {
		cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��(Ԫ/��)" << ": ";
		cin >> retail; cin.ignore();
		if (retail <= 0) cout << "�����������������,����������:(��ȷ�����������ʵ��)" << endl;
	} while (retail <= 0);

	books.push_back(BookData(isbn, bookTitle, author, publisher, dateAdded, qtyOnHand, wholesale, retail));

	cout << endl << "����ɹ�!(' �� �� ��')" << endl << endl;
}

void Management::editBook(list<BookData>& books)
{
	string bookName;				// �û����������
	int bookNum = 0;				// �洢�ܹ����ҵ�����Ŀ������
	list<BookData> tempDict;		// ��ʱ�洢���ܷ���Ҫ���BookData����

	cout << "��������Ҫ�޸���Ϣ������:";
	cin >> bookName; cin.ignore();

	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {

		// �˴���lookUpBook�����е�ƥ���߼���ȫһ��
		string currBookName((*it).getBookTitle()),
			currAuthor((*it).getAuthor()),
			currPulisher((*it).getPublisher());
		bool validFind = (currBookName.find(bookName) + 1)
			|| (currAuthor.find(bookName) + 1)
			|| (currPulisher.find(bookName) + 1);
		if (validFind) {
			bookNum++;
			tempDict.push_back(BookData(*it));
		}
	}
	if (bookNum == 0) {
		cout << "(�����ߡ���)/I��m sorry~ ��û���ҵ�����鼮......" << endl;
		return;
	}

	else {
		cout << "��Ϊ���ҵ�" << bookNum << "�����йؼ���\"" << bookName << "\"�Ľ��(' �� �� ��')" << endl;
		int haveShow = 0;							// �Ѿ���ʾ�Ľ����Ŀ
		int x, y;									// ��ǰ�������Ļ�ϵ�����
		int id = 0;									// �û�ѡ���Ҫ�޸ĵ���ı��
		char decision[10], * p;

		for (list<BookData>::iterator it = tempDict.begin(); it != tempDict.end(); ++it) {
			haveShow++;
			cout << endl << " book " << haveShow << " :\n" << endl;
			(*it).displayInfo();


			// ÿ��ʾ2�������ͣһ��
			if (haveShow % 2 == 0 && (it != tempDict.end())) {
				cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
				getchar();							// �����û�����Ļس���
				getXY(&x, &y);						// ��ȡ�������
				goToXY(x, y - 1);					// �˵���һ��
				cout << setw(50) << " ";			// �����ʾ��Ϣ
				goToXY(x, y - 2);					// ���˵���һ��
			}
		}
		cout << endl << " " << endl;
		bool flag = true;							// �����ж��û��Ƿ��������쳣��Ϣ

		// Ҫ���û�������Ҫ�޸ĵ���ţ�����������Ч�Լ��
		do {
			cout << "����Ҫ�޸��ı������Ϣ�أ������롮book�����������ţ�:";
			cin >> id; cin.ignore();
			if (id >= 1 && id <= bookNum && (fabs(id - (int)id) <= 1e-6)) flag = true;
			else {
				cout << "����������Ч�����!" << endl;
				flag = false;
			}
		} while (!flag);

		/*
			- ����id��tempDict�������ҵ������isbn�ţ��ٸ���isbn����ԭ�����ܵ��������ҵ��Ǹ�������
			- �������editPointָ��ָ��ԭ��������Ҫ�޸ĵĽڵ�
		*/
		int i = 1;									// ����ƥ��id����ʱ�������ǵ�++
		char editIsbn[20];							// ����������Ҫ�޸ĵ�BookData�����isbn��
		list<BookData>::iterator editPoint;			// ����ָ����������Ҫ�޸ĵ�BookData����ĵ�����ָ��

		for (list<BookData>::iterator it = tempDict.begin(); it != tempDict.end(); ++it) {
			if (id == i) strcpy(editIsbn, (*it).getIsbn());
			i++;
		}
		for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
			if (strcmp(editIsbn, (*it).getIsbn()) == 0) editPoint = it;
		}

		// ѯ���û��Ƿ��޸�ȫ�������������Ч��
		do {

			cout << "���Ƿ�ѡ���޸ĸñ����ȫ�������������Yes��No�������ִ�Сд��:";
			cin >> decision; cin.ignore();
			system("cls");
			p = strUpper(decision);
			if (strcmp(p, "YES") == 0 || strcmp(p, "NO") == 0) flag = true;
			else {
				cout << "������Yes����No����ò������Ĳ���������֮����κ�һ��(' �� �� ��')" << endl;
				flag = false;
			}
		} while (!flag);

		// ������ʱ�����û���ĳһ��������ݵ��޸�ֵ
		char isbn[14];
		char bookTitle[51];
		char author[31];
		char publisher[31];
		char dateAdded[11];
		int qtyOnHand;
		double wholesale;
		double retail;
		char ch;

		int width1 = 3, width2 = 10;

		// �����û���ѡ����벻ͬ���޸ķ�ʽ
		// YES�����޸�ȫ��������˴����������⣬�˴�����������increaseBook�еļ���߼�һ��
		if (strcmp(p, "YES") == 0) {
			do {
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "ISBN  ��" << ": ";
				cin >> isbn; cin.ignore();
				if (!checkIsbn(isbn)) cout << "�������isbn���벻���ϸ�ʽ,����������:(��ʽΪ������\'-\'�����,����\'-\'���ܳ����ڿ�ͷ���β����������\'-\'��������)" << endl;
			} while (!checkIsbn(isbn));
			cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "��    ��" << ": ";
			cin >> bookTitle; cin.ignore();
			cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": ";
			cin >> author; cin.ignore();
			cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": ";
			cin >> publisher; cin.ignore();
			do {
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "��������" << ": ";
				cin >> dateAdded; cin.ignore();
				if (!checkDateAdded(dateAdded)) cout << "�������ʱ���ʽ����,����������:(��ʽΪX-X-X,������-��-��,����2017-1-1)" << endl;
			} while (!checkDateAdded(dateAdded));
			do {
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": "; cin >> qtyOnHand;
				cin.ignore();
				if ((qtyOnHand < 0) || (fabs(qtyOnHand - (int)qtyOnHand) > 1e-6)) cout << "������Ŀ��������,����������:(��ȷ��������ǷǸ�����)" << endl;
			} while ((qtyOnHand < 0) || (fabs(qtyOnHand - (int)qtyOnHand) > 1e-6));
			do {
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��(Ԫ/��)" << ": "; cin >> wholesale;
				cin.ignore();
				if (wholesale <= 0) cout << "�����������������,����������:(��ȷ�����������ʵ��)" << endl;
			} while (wholesale <= 0);
			do {
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��(Ԫ/��)" << ": "; cin >> retail;
				cin.ignore();
				if (retail <= 0) cout << "�����������������,����������:(��ȷ�����������ʵ��)" << endl;
			} while (retail <= 0);

			cout << "ȷ��Ҫ�޸��𣿣�y/n��";
			ch = getchar();
			if (ch == 'n') return;
			(*editPoint).setIsbn(isbn);
			(*editPoint).setAuthor(author);
			(*editPoint).setBookTitle(bookTitle);
			(*editPoint).setPublisher(publisher);
			(*editPoint).setDateAdded(dateAdded);
			(*editPoint).setQtyOnHand(qtyOnHand);
			(*editPoint).setWholesale(wholesale);
			(*editPoint).setRetail(retail);
			cout << endl << "�޸ĳɹ�!(' �� �� ��')" << endl << endl;
		}

		// NO�����޸Ĳ���������
		else if (strcmp(p, "NO") == 0) {
			bool flag = true;				//���������Ч�Ե�flag
			int editId;
			width1 = 5;
			width2 = 7;

			// ��ȡ��ţ�����ʾ����������
			do {
				cout << setw(width1) << " 1 : " << setw(width2) << "ISBN  ��" << endl;
				cout << setw(width1) << " 2 : " << setw(width2) << "��    ��" << endl;
				cout << setw(width1) << " 3 : " << setw(width2) << "�� �� ��" << endl;
				cout << setw(width1) << " 4 : " << setw(width2) << "�� �� ��" << endl;
				cout << setw(width1) << " 5 : " << setw(width2) << "��������" << endl;
				cout << setw(width1) << " 6 : " << setw(width2) << "�� �� ��" << endl;
				cout << setw(width1) << " 7 : " << setw(width2) << "�� �� ��" << endl;
				cout << setw(width1) << " 8 : " << setw(width2) << "�� �� ��" << endl;
				cout << "��������Ҫ�޸ĵ�������֮ǰ�ı�ţ�1-8����";
				cin >> editId; cin.ignore();
				if (editId >= 1 && editId <= 8 && (fabs(editId - (int)editId) <= 1e-8)) flag = true;
				else {
					cout << "��������Ч�ı�ţ�" << endl;
					flag = false;
				}
			} while (!flag);

			switch (editId)
			{
			case 1:
				do {
					cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "ISBN  ��" << ": ";
					cin >> isbn; cin.ignore();
					if (!checkIsbn(isbn)) cout << "�������isbn���벻���ϸ�ʽ,����������:(��ʽΪ������\'-\'�����,����\'-\'���ܳ����ڿ�ͷ���β����������\'-\'��������)" << endl;
				} while (!checkIsbn(isbn));
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setIsbn(isbn);
				break;

			case 2:
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "��    ��" << ": ";
				cin >> bookTitle; cin.ignore();
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setBookTitle(bookTitle);
				break;

			case 3:
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": ";
				cin >> author; cin.ignore();
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setAuthor(author);
				break;

			case 4:
				cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": ";
				cin >> publisher; cin.ignore();
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setPublisher(publisher);
				break;

			case 5:
				do {
					cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "��������" << ": ";
					cin >> dateAdded; cin.ignore();
					if (!checkDateAdded(dateAdded)) cout << "�������ʱ���ʽ����,����������:(��ʽΪX-X-X,������-��-��,����2017-1-1)" << endl;
				} while (!checkDateAdded(dateAdded));
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setDateAdded(dateAdded);
				break;

			case 6:
				do {
					cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��" << ": "; cin >> qtyOnHand;
					cin.ignore();
					if ((qtyOnHand < 0) || (fabs(qtyOnHand - (int)qtyOnHand) > 1e-6)) cout << "������Ŀ��������,����������:(��ȷ��������ǷǸ�����)" << endl;
				} while ((qtyOnHand < 0) || (fabs(qtyOnHand - (int)qtyOnHand) > 1e-6));
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setQtyOnHand(qtyOnHand);
				break;

			case 7:
				do {
					cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��(Ԫ/��)" << ": "; cin >> wholesale;
					cin.ignore();
					if (wholesale <= 0) cout << "�����������������,����������:(��ȷ�����������ʵ��)" << endl;
				} while (wholesale <= 0);
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setWholesale(wholesale);
				break;

			case 8:
				do {
					cout << setw(width1) << setiosflags(ios::left) << "->" << setw(width2) << setiosflags(ios::left) << "�� �� ��(Ԫ/��)" << ": "; cin >> retail;
					cin.ignore();
					if (retail <= 0) cout << "�����������������,����������:(��ȷ�����������ʵ��)" << endl;
				} while (retail <= 0);
				cout << "ȷ��Ҫ�޸��𣿣�y/n��";
				ch = getchar();
				if (ch == 'n') return;
				(*editPoint).setRetail(retail);
				break;
			}
			cout << endl << "�޸ĳɹ�!(' �� �� ��')" << endl << endl;
		}

	}

}

void Management::deleteBook(list<BookData>& books)
{
	string bookName;
	int bookNum = 0;
	list<BookData> tempDict;

	cout << "��������Ҫɾȥ���������:";
	cin >> bookName; cin.ignore();

	// ��ԭ�����п�ʼģ��ƥ�䣬ƥ���߼���lookUpBook��һ��
	for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {

		string currBookName((*it).getBookTitle()),
			currAuthor((*it).getAuthor()),
			currPulisher((*it).getPublisher());
		bool validFind = (currBookName.find(bookName) + 1)
			|| (currAuthor.find(bookName) + 1)
			|| (currPulisher.find(bookName) + 1);
		if (validFind) {
			bookNum++;
			tempDict.push_back(BookData(*it));
		}
	}
	if (bookNum == 0) {
		cout << "(�����ߡ���)/I��m sorry~ ��û���ҵ�����鼮......" << endl;
		return;
	}
	else {
		cout << "��Ϊ���ҵ�" << bookNum << "�����йؼ���\"" << bookName << "\"�Ľ��(' �� �� ��')" << endl;
		int haveShow = 0;							// �Ѿ���ʾ�Ľ����Ŀ
		int x, y;									// ��ǰ�������Ļ�ϵ�����
		int id = 0;									// �û�ѡ���Ҫ�޸ĵ���ı��

		for (list<BookData>::iterator it = tempDict.begin(); it != tempDict.end(); ++it) {
			haveShow++;
			cout << endl << " book " << haveShow << " :\n" << endl;
			(*it).displayInfo();


			// ÿ��ʾ2�������ͣһ��
			if (haveShow % 2 == 0 && (it != tempDict.end())) {
				cout << endl << "��Ϊ��չʾ" << haveShow << "����Ѱ���,���س�������ʾ������...";
				getchar();							// �����û�����Ļس���
				getXY(&x, &y);						// ��ȡ�������
				goToXY(x, y - 1);					// �˵���һ��
				cout << setw(50) << " ";			// �����ʾ��Ϣ
				goToXY(x, y - 2);					// ���˵���һ��
			}
		}
		cout << endl << " " << endl;
		bool flag = true;							// �����ж��û��Ƿ��������쳣��Ϣ

		// Ҫ���û�������Ҫ�޸ĵ���ţ�����������Ч�Լ��
		do {
			cout << "����Ҫɾȥ�ı����أ������롮book�����������ţ�:";
			cin >> id; cin.ignore();
			if (id >= 1 && id <= bookNum && (fabs(id - (int)id) <= 1e-6)) flag = true;
			else {
				cout << "����������Ч�����!" << endl;
				flag = false;
			}
		} while (!flag);

		// �˴���������ָ�븳ֵ���߼���editBook����ȫ��ͬ
		int i = 1;									// ����ƥ��id����ʱ�������ǵ�++
		char deleteIsbn[20];						// ����������Ҫɾȥ��BookData�����isbn��
		list<BookData>::iterator deletePoint;		// ����ָ����������Ҫɾȥ��BookData����ĵ�����ָ��

		for (list<BookData>::iterator it = tempDict.begin(); it != tempDict.end(); ++it) {
			if (id == i) strcpy(deleteIsbn, (*it).getIsbn());
			i++;
		}
		for (list<BookData>::iterator it = books.begin(); it != books.end(); ++it) {
			if (strcmp(deleteIsbn, (*it).getIsbn()) == 0) deletePoint = it;
		}
		cout << "��ȷ��Ҫɾȥ��һ�����𣿣�y/n��";
		char ch = getchar();
		if (ch == 'n') return;
		books.erase(deletePoint);
		cout << endl << "ɾ���ɹ�!(' �� �� ��')" << endl << endl;
	}
}

void Management::changeTaxRate()
{
	double rate;
	bool flag = true;
	do {
		cout << "�������µ�˰��ֵ��0-1��:";
		cin >> rate; cin.ignore();
		if (rate > 0 && rate < 1) flag = true;
		else {
			cout << "��������Ч��˰�ʣ�" << endl;
			flag = false;
		}
	} while (!flag);
	Sale::taxRate = rate;
	cout << endl << "˰���޸ĳɹ�!(' �� �� ��')" << endl << endl;
}

bool Management::checkIsbn(char* isbn)
{
	bool flag = true;
	for (unsigned int i = 0; i < strlen(isbn); i++) {
		// isbn����ֻ�����ֺ�-,���в������ֻ�-�ģ�flag��Ϊfalse
		if (!((*(isbn + i) >= '0' && *(isbn + i) <= '9') || (*(isbn + i) == '-'))) {
			flag = false;
			//cout << "�������isbn���г��������ֺ�\'-\'֮��ķ���" << endl;
		}
		// isbn����������-��������һ��
		if (i != strlen(isbn) - 1) {
			if (*(isbn + i) == '-' && *(isbn + i + 1) == '-') {
				flag = false;
				//cout << "�������isbn���г���������һ���\'-\'" << endl;
			}

		}
	}
	// -���ܳ����ڿ�ͷ���β
	if (*isbn == '-') flag = false;
	if (*(isbn + strlen(isbn) - 1) == '-') flag = false;
	return flag;
}

bool Management::checkDateAdded(char* dateAdded)
{
	bool flag = true;
	int _num = 0;		//����-�ĸ���
	for (unsigned int i = 0; i < strlen(dateAdded); ++i) {
		if (*(dateAdded + i) == '-') _num++;
	}
	// -���������������ָܷ��������
	if (_num != 2) return false;

	// �ָ�������
	vector<string> date;
	split(string(dateAdded), date, '-');

	// �����Ч��
	flag = checkDate(strToNum(date[0]), strToNum(date[1]), strToNum(date[2]));

	return flag;
}

bool Management::isLY(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return true;
	else return false;
}

bool Management::checkDate(int year = 2020, int month = 1, int day = 1)
{
	bool flag = true;
	int calender[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	// ���ڲ���С��0
	if (year <= 0 || month <= 0 || day <= 0) flag = false;
	// ������Ķ��·ݵ����ó�������
	if (isLY(year) && month == 2)
		flag = (day <= 29) ? true : false;
	else
		flag = (day <= calender[month - 1]) ? true : false;
	return flag;
}

