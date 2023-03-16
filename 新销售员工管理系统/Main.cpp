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
		cout << "请选择您要使用的功能：（输入功能前的数字）" << endl;
		cin >> choose;
		switch (choose)
		{
		case '0':
			cout << "欢迎下次使用！！！" << endl;
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
			cout << "输入有误，请重新输入！！！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
