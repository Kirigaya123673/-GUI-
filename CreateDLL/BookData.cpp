#include "library.h"

/*
	ʵ��BookData�еĺ���
	- displayInfo:		��ʽ��������������ǿ��Ƽ�ͷ�������Ⱥͺ����������ȣ�ȱʡֵ��5��7
*/
void BookData::displayInfo(int width1, int width2)
{
	cout << setw(width1) << " " << setw(width2) << "ISBN  ��" << ": " << isbn << endl;
	cout << setw(width1) << " " << setw(width2) << "��    ��" << ": " << bookTitle << endl;
	cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << author << endl;
	cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << publisher << endl;
	cout << setw(width1) << " " << setw(width2) << "��������" << ": " << dateAdded << endl;
	cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << qtyOnHand << endl;
	cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << wholesale << "Ԫ/��" << endl;
	cout << setw(width1) << " " << setw(width2) << "�� �� ��" << ": " << retail << "Ԫ/��" << endl;
}