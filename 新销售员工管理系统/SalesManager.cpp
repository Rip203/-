#include "SalesManager.h"

//SalesManager构造函数用于初始化对象
SalesManager::SalesManager()
{
	ifstream ifs;
	ifs.open("emp.dat", ios::in);
	//情况一：文件不存在
	if (!ifs.is_open())
	{
		cout << "当前文件不存在！！！" << endl;
		//初始化数组
		fileISEmpty = true;
		staffMember = 0;
		ifs.close();
		return;
	}
	//情况二：文件存在但没有内容
	char a;
	ifs >> a;
	if (ifs.eof())
	{
		cout << "当前文件为空！！！" << endl;
		//初始化数组
		fileISEmpty = true;
		staffMember = 0;
		ifs.close();
		return;
	}
	//情况三：文件存在，并且有数据
	int num = getFileMember();
	this->staffMember = num;
	getFileEmp();
	getAlloSaleman();
}


SalesManager::SalesManager(string id, string name, int age, string post, int sale)
{
	m_id = id;
	m_name = name;
	m_age = age;
	m_post = post;
	m_sale = sale;
}

void SalesManager::show()
{
	cout << "职工编号：" << m_id << endl
		<< "职工姓名：" << m_name << endl
		<< "职工年龄：" << m_age << endl
		<< "职工岗位：" << m_post << endl
		<< "本月销售额：" << m_sale << endl;
}

//菜单
void SalesManager::menu()
{
	cout << "+------------------------+" << endl;
	cout << "| 欢迎使用职工管理系统   |" << endl;
	cout << "| 0.退出管理程序         |" << endl;
	cout << "| 1.增加职工信息         |" << endl;
	cout << "| 2.显示职工信息         |" << endl;
	cout << "| 3.删除职工             |" << endl;
	cout << "| 4.修改职工信息         |" << endl;
	cout << "| 5.查找职工信息         |" << endl;
	cout << "| 6.重组文件             |" << endl;
	cout << "| 7.清空文件             |" << endl;
	cout << "| 8.为销售经理分配销售员 |" << endl;
	cout << "| 9.删除分配完成的销售员 |" << endl;
	cout << "+------------------------+" << endl;
	cout << endl;
}

//添加职工
void SalesManager::add()
{
	Staff* s = nullptr;
	string id;
	while (1)
	{
		cout << "请输入职工编号：" << endl;
		cin >> id;
		if (existEmp(id) != -1)
		{
			cout << "id已经存在，请重新输入" << endl;
		}
		else
		{
			break;
		}
	}

	string name;
	cout << "请输入职工姓名：" << endl;
	cin >> name;
	int age;
	cout << "请输入职工年龄：" << endl;
	cin >> age;
	int sale;
	cout << "请输入职本月销售额：" << endl;
	cin >> sale;
	int judge = false;
	while (!judge)
	{
		cout << "请选择职工岗位：" << endl;
		cout << "1.销售员" << endl;
		cout << "2.经理" << endl;
		cout << "3.销售经理" << endl;
		char choose;
		cin >> choose;
		switch (choose)
		{
		case '1':
			judge = true;
			s = new Salesman(id, name, age, "销售员", sale);
			break;
		case '2':
			s = new Manager(id, name, age, "经理", sale);
			judge = true;
			break;
		case '3':
			s = new SalesManager(id, name, age, "销售经理", sale);
			judge = true;
			break;
		default:
			cout << "输入错误，请重新输入！！！" << endl;
			break;
		}
	}
	this->staffVector.push_back(s);
	cout << "员工添加成功！！！" << endl;
	this->fileISEmpty = false;
	this->staffMember++;
	save();//保存文件
	system("pause");
	system("cls");
}

//显示全部职工信息
void SalesManager::showAllEmp()
{
	if (fileISEmpty)
	{
		cout << "文件不存在或者记录为空！！！" << endl;
	}
	else if (staffMember > 0)
	{
		for (auto& i : staffVector)
		{
			i->show();
			cout << endl;
		}
		if (newStaffVector.size() != 0)
		{
			cout << "分配销售经理的销售员信息：" << endl;
			for (auto& i : newStaffVector)
			{
				i.show();
				cout << "所属销售经理id为：" << endl;
				cout << i.getManager();
				cout << endl;
				cout << endl;
			}
		}

	}
	else
	{
		cout << "当前文件已清空！！！" << endl;
	}
	system("pause");
	system("cls");
}

//删除员工
void SalesManager::deleteEmp()
{
	if (fileISEmpty)
	{
		cout << "当前文件为空！！！" << endl;
	}
	else
	{
		cout << "请输入您想要删除的职工编号：" << endl;
		string id;
		cin >> id;
		int index = existEmp(id);//在数组中寻找id
		if (index != -1)
		{
			staffVector.erase(staffVector.begin() + index);
			//更新数组中的总人数
			staffMember--;
			//将数据保存在文档中
			save();
			cout << "删除成功！！！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改员工
void SalesManager::revise()
{
	if (fileISEmpty)
	{
		cout << "文件不存在或文件为空！！！" << endl;
	}
	else
	{
		string id;
		cout << "请输入要修改的职工id：" << endl;
		cin >> id;
		if (existEmp(id) != -1)
		{
			int index = existEmp(id);
			Staff* s = nullptr;
			string id;
			while (1)
			{
				cout << "请输入职工编号：" << endl;
				cin >> id;
				if (existEmp(id) != -1)
				{
					cout << "id已经存在，请重新输入" << endl;
				}
				else
				{
					break;
				}
			}
			string name;
			cout << "请输入职工姓名：" << endl;
			cin >> name;
			int age;
			cout << "请输入职工年龄：" << endl;
			cin >> age;
			int sale;
			cout << "请输入职工本月的销售额：" << endl;
			cin >> sale;
			int judge = false;
			while (!judge)
			{
				cout << "请选择职工岗位：" << endl;
				cout << "1.销售员" << endl;
				cout << "2.经理" << endl;
				cout << "3.销售经理" << endl;
				char choose;
				cin >> choose;
				switch (choose)
				{
				case '1':
					judge = true;
					s = new Salesman(id, name, age, "销售员", sale);
					break;
				case '2':
					s = new Manager(id, name, age, "经理", sale);
					judge = true;
					break;
				case '3':
					s = new SalesManager(id, name, age, "销售经理", sale);
					judge = true;
					break;
				default:
					cout << "输入错误，请重新输入！！！" << endl;
					break;
				}
			}
			this->staffVector[index] = s;
			cout << "员工修改成功！！！" << endl;
			save();//保存文件
		}
		else if (existEmp(id) == -1)
		{
			cout << "职工id不存在" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找员工
void SalesManager::search()
{
	if (fileISEmpty)
	{
		cout << "文件不存在或文件为空！！！" << endl;
	}
	else
	{
		char choose;
		cout << "请选择查找方式：" << endl;
		cout << "1.员工id查找" << endl;
		cout << "2.员工姓名查找" << endl;
		cin >> choose;

		if (choose == '1')
		{
			string id;
			cout << "请输入您要查找的id：" << endl;
			cin >> id;
			if (existEmp(id) == -1)
			{
				cout << "查找失败，该id号员工不存在！！！" << endl;
				return;
			}
			else
			{
				for (int i = 0; i < staffVector.size(); i++)
				{
					if (staffVector[i]->m_id.compare(id) == 0)
					{
						staffVector[i]->show();
						break;
					}
				}
			}
		}
		else if (choose == '2')
		{
			int n = 0;//计数器
			string name;
			cout << "请输入您要查找的员工姓名：" << endl;
			cin >> name;
			for (int i = 0; i < staffVector.size(); i++)
			{
				if (staffVector[i]->m_name.compare(name) == 0)
				{
					staffVector[i]->show();
					cout << endl;
					n++;
				}
			}
			if (n == 0)
			{
				cout << "查找失败，该姓名的员工不存在！！！" << endl;
			}
			else
			{
				cout << "姓名相同的员工共：" << n << "人" << endl;
			}
		}
		else
		{
			cout << "输入错误，请重新输入！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//重构文件
void SalesManager::recom()
{
	if (fileISEmpty)
	{
		cout << "当前文件不存在或文件为空!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < staffVector.size() - 1; i++)
	{
		for (int j = 0; j < staffVector.size() - i - 1; j++)
		{
			if (staffVector[j]->m_id.compare(staffVector[j + 1]->m_id) > 0)
			{
				Staff* temp = staffVector[j];
				staffVector[j] = staffVector[j + 1];
				staffVector[j + 1] = temp;
			}
		}
	}

	cout << "重构成功！！！" << endl;
	save();
	system("pause");
	system("cls");
}

//删除所有员工
void SalesManager::deleteAllEmp()
{
	if (fileISEmpty)
	{
		cout << "文件为空或文件不存在!" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		bool judge = false;
		while (!judge)
		{
			char choose;
			cout << "请确认是否清空文档：" << endl;
			cout << "输入：Y(清空并退出程序)" << endl;
			cout << "输入：N(返回用户菜单)" << endl;
			cin >> choose;
			switch (choose)
			{
			case 'Y':
				for (int i = 0; i < staffVector.size(); i++)
				{
					staffVector.pop_back();
				}
				for (int i = 0; i < newStaffVector.size(); i++)
				{
					newStaffVector.pop_back();
				}
				cout << "清除成功！！！" << endl;
				staffMember = 0;
				save();
				newSave();
				system("pause");
				system("cls");
				cout << "欢迎下次使用！！！" << endl;
				exit(0);
			case 'N':
				system("cls");
				return;
			default:
				cout << "输入错误请重新输入！" << endl;
			}
		}
	}
}

//给销售经理分配销售员
void SalesManager::allocationSalesManager()
{
	while (1)
	{
		string id;
		cout << "请输入要添加销售员的销售经理的id：" << endl;
		cin >> id;
		int y = judgeSaleManager(id);
		if (y != -1)
		{
			cout << "该销售经理信息为：" << endl;
			staffVector[y]->show();
			cout << endl;
			while (1)
			{
				string newId;
				cout << "请输入销售员id：" << endl;
				cin >> newId;
				int x = judgeSaleman(newId);
				if (x != -1)
				{
					SalesManager s;
					s.m_id = staffVector[x]->m_id;
					s.m_name = staffVector[x]->m_name;
					s.m_age = staffVector[x]->m_age;
					s.m_post = staffVector[x]->m_post;
					s.m_sale = staffVector[x]->m_sale;
					s.m_manager = staffVector[y]->m_id;
					staffVector.erase(staffVector.begin() + x);
					this->staffMember--;
					save();
					newStaffVector.push_back(s);
					newSave();
					cout << "销售员分配成功！" << endl;
					system("pause");
					system("cls");
					return;
				}
				else if (existEmp(newId) == -1)
				{
					cout << "该员工不存在，请先录入！" << endl;
					system("pause");
					system("cls");
					return;
				}
				else
				{
					if (existEmp(newId) == -1)
					{
						cout << "该员工不存在，请先录入！" << endl;
						system("pause");
						system("cls");
						return;
					}
					else
					{
						cout << "该员工不是销售员，请重新输入" << endl;
					}
				}
			}
		}
		else
		{
			cout << "该员工不是销售经理，请重新输入" << endl;
		}
	}
}

//删除已经分配的销售员
void SalesManager::deleteAlloSaleman()
{
	if (newStaffVector.size() == 0)
	{
		cout << "当前还未分任何配销售员给某位销售经理！！！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入您想要删除的职工编号：" << endl;
		string id;
		cin >> id;
		int index = -1;
		for (int i = 0; i < newStaffVector.size(); i++)
		{
			if (newStaffVector[i].m_id.compare(id) == 0)
			{
				index = i;
				break;
			}
			else
			{
				cout << "删除失败，未找到该职工" << endl;
				system("pause");
				system("cls");
			}
		}
		if (index != -1)
		{
			newStaffVector.erase(newStaffVector.begin() + index);
			newSave();
			cout << "删除成功！！！" << endl;
			system("pause");
			system("cls");
		}
	}
}

//检测职工是否存在
int SalesManager::existEmp(string id)
{
	int index = -1;//默认初始值为-1

	//遍历整个数组寻找id是否存在
	for (int i = 0; i < staffVector.size(); i++)
	{
		if (staffVector[i]->m_id.compare(id) == 0)
		{
			index = i;
			break;
		}
	}
	for (int i = 0; i < newStaffVector.size(); i++)
	{
		if (newStaffVector[i].m_id.compare(id) == 0)
		{
			index = i;
			break;
		}
	}

	return index;//返回该职工所在的数组索引
}

//当文件内存在数据时，获取人数
int SalesManager::getFileMember()
{
	ifstream ifs;
	ifs.open("emp.dat", ios::in);

	string id;
	string name;
	int age;
	string post;
	int sale;

	int num = 0;//计数器

	while (ifs >> id && ifs >> name && ifs >> age && ifs >> post && ifs >> sale)
	{
		num++;
	}

	return num;
}

//保存文件emp.dat
void SalesManager::save()
{
	ofstream ofs;
	ofs.open("emp.dat", ios::out);
	for (int i = 0; i < this->staffMember; i++)
	{
		ofs << this->staffVector[i]->m_id << " "
			<< this->staffVector[i]->m_name << " "
			<< this->staffVector[i]->m_age << " "
			<< this->staffVector[i]->m_post << " "
			<< this->staffVector[i]->m_sale << endl;
	}
	ofs.close();
}

//获得文件中的数据
void SalesManager::getFileEmp()
{
	ifstream ifs;
	ifs.open("emp.dat", ios::in);

	string id;
	string name;
	int age;
	string post;
	int sale;

	while (ifs >> id && ifs >> name && ifs >> age && ifs >> post && ifs >> sale)
	{
		Staff* worker = nullptr;
		if (post.compare("销售员") == 0)//Salesman 
		{
			worker = new Salesman(id, name, age, post, sale);
		}
		else if (post.compare("经理") == 0)//Manager 
		{
			worker = new Manager(id, name, age, post, sale);
		}
		else if (post.compare("销售经理") == 0)//SaleManager
		{
			worker = new SalesManager(id, name, age, post, sale);
		}
		staffVector.push_back(worker);;
	}
	ifs.close();
}

//从AllocationSaleman文件中获取信息
void SalesManager::getAlloSaleman()
{
	ifstream ifs;
	ifs.open("AllocationSaleman.dat", ios::in);

	string id;
	string name;
	int age;
	string post;
	int sale;
	string manager;

	while (ifs >> id && ifs >> name && ifs >> age && ifs >> post && ifs >> sale && ifs >> manager)
	{
		Salesman s;
		s.m_id = id;
		s.m_name = name;
		s.m_age = age;
		s.m_post = post;
		s.m_sale = sale;
		s.m_manager = manager;
		newStaffVector.push_back(s);
	}
	ifs.close();
}

//保存已经分配的销售员
void SalesManager::newSave()
{
	ofstream ofs;
	ofs.open("AllocationSaleman.dat", ios::out);
	for (int i = 0; i < this->newStaffVector.size(); i++)
	{
		ofs << this->newStaffVector[i].m_id << " "
			<< this->newStaffVector[i].m_name << " "
			<< this->newStaffVector[i].m_age << " "
			<< this->newStaffVector[i].m_post << " "
			<< this->newStaffVector[i].m_sale << " "
			<< this->newStaffVector[i].m_manager << endl;
	}
	ofs.close();
}

//判断员工是否为销售经理
int SalesManager::judgeSaleManager(string id)
{
	for (int i = 0; i < staffVector.size(); i++)
	{
		if (staffVector[i]->m_post.compare("销售经理") == 0 && staffVector[i]->m_id.compare(id) == 0)
		{
			return i;
		}
	}
	return -1;
}

//判断员工是否为销售员
int SalesManager::judgeSaleman(string id)
{
	for (int i = 0; i < staffVector.size(); i++)
	{
		if (staffVector[i]->m_post.compare("销售员") == 0 && staffVector[i]->m_id.compare(id) == 0)
		{
			return i;
		}
	}
	return -1;
}
