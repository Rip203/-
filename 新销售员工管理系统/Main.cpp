#include<iostream>
#include"Staff.h"
#include"Salesman.h"
#include"Manager.h"
#include"SalesManager.h"
using namespace std;

void main()
{
	SalesManager sm;
	while (true)
	{
		sm.menu();
		char choose;
		cout << "��ѡ����Ҫʹ�õĹ��ܣ������빦��ǰ�����֣�" << endl;
		cin >> choose;
		switch (choose)
		{
		case '0':
			cout << "��ӭ�´�ʹ�ã�����" << endl;
			system("pause");
			system("cls");
			return;
		case '1':
			sm.add();
			break;
		case '2':
			sm.showAllEmp();
			break;
		case '3':
			sm.deleteEmp();
			break;
		case '4':
			sm.revise();
			break;
		case '5':
			sm.search();
			break;
		case '6':
			sm.recom();
			break;
		case '7':
			sm.deleteAllEmp();
			break;
		case '8':
			sm.allocationSalesManager();
			break;
		case '9':
			sm.deleteAlloSaleman();
			break;
		default:
			cout << "�����������������룡����" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
