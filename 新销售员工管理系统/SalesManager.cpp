#include "SalesManager.h"

//SalesManager���캯�����ڳ�ʼ������
SalesManager::SalesManager()
{
	ifstream ifs;
	ifs.open("emp.dat", ios::in);
	//���һ���ļ�������
	if (!ifs.is_open())
	{
		cout << "��ǰ�ļ������ڣ�����" << endl;
		//��ʼ������
		fileISEmpty = true;
		staffMember = 0;
		ifs.close();
		return;
	}
	//��������ļ����ڵ�û������
	char a;
	ifs >> a;
	if (ifs.eof())
	{
		cout << "��ǰ�ļ�Ϊ�գ�����" << endl;
		//��ʼ������
		fileISEmpty = true;
		staffMember = 0;
		ifs.close();
		return;
	}
	//��������ļ����ڣ�����������
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
	cout << "ְ����ţ�" << m_id << endl
		<< "ְ��������" << m_name << endl
		<< "ְ�����䣺" << m_age << endl
		<< "ְ����λ��" << m_post << endl
		<< "�������۶" << m_sale << endl;
}

//�˵�
void SalesManager::menu()
{
	cout << "+------------------------+" << endl;
	cout << "| ��ӭʹ��ְ������ϵͳ   |" << endl;
	cout << "| 0.�˳��������         |" << endl;
	cout << "| 1.����ְ����Ϣ         |" << endl;
	cout << "| 2.��ʾְ����Ϣ         |" << endl;
	cout << "| 3.ɾ��ְ��             |" << endl;
	cout << "| 4.�޸�ְ����Ϣ         |" << endl;
	cout << "| 5.����ְ����Ϣ         |" << endl;
	cout << "| 6.�����ļ�             |" << endl;
	cout << "| 7.����ļ�             |" << endl;
	cout << "| 8.Ϊ���۾����������Ա |" << endl;
	cout << "| 9.ɾ��������ɵ�����Ա |" << endl;
	cout << "+------------------------+" << endl;
	cout << endl;
}

//���ְ��
void SalesManager::add()
{
	Staff* s = nullptr;
	string id;
	while (1)
	{
		cout << "������ְ����ţ�" << endl;
		cin >> id;
		if (existEmp(id) != -1)
		{
			cout << "id�Ѿ����ڣ�����������" << endl;
		}
		else
		{
			break;
		}
	}

	string name;
	cout << "������ְ��������" << endl;
	cin >> name;
	int age;
	cout << "������ְ�����䣺" << endl;
	cin >> age;
	int sale;
	cout << "������ְ�������۶" << endl;
	cin >> sale;
	int judge = false;
	while (!judge)
	{
		cout << "��ѡ��ְ����λ��" << endl;
		cout << "1.����Ա" << endl;
		cout << "2.����" << endl;
		cout << "3.���۾���" << endl;
		char choose;
		cin >> choose;
		switch (choose)
		{
		case '1':
			judge = true;
			s = new Salesman(id, name, age, "����Ա", sale);
			break;
		case '2':
			s = new Manager(id, name, age, "����", sale);
			judge = true;
			break;
		case '3':
			s = new SalesManager(id, name, age, "���۾���", sale);
			judge = true;
			break;
		default:
			cout << "����������������룡����" << endl;
			break;
		}
	}
	this->staffVector.push_back(s);
	cout << "Ա����ӳɹ�������" << endl;
	this->fileISEmpty = false;
	this->staffMember++;
	save();//�����ļ�
	system("pause");
	system("cls");
}

//��ʾȫ��ְ����Ϣ
void SalesManager::showAllEmp()
{
	if (fileISEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�����" << endl;
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
			cout << "�������۾��������Ա��Ϣ��" << endl;
			for (auto& i : newStaffVector)
			{
				i.show();
				cout << "�������۾���idΪ��" << endl;
				cout << i.getManager();
				cout << endl;
				cout << endl;
			}
		}

	}
	else
	{
		cout << "��ǰ�ļ�����գ�����" << endl;
	}
	system("pause");
	system("cls");
}

//ɾ��Ա��
void SalesManager::deleteEmp()
{
	if (fileISEmpty)
	{
		cout << "��ǰ�ļ�Ϊ�գ�����" << endl;
	}
	else
	{
		cout << "����������Ҫɾ����ְ����ţ�" << endl;
		string id;
		cin >> id;
		int index = existEmp(id);//��������Ѱ��id
		if (index != -1)
		{
			staffVector.erase(staffVector.begin() + index);
			//���������е�������
			staffMember--;
			//�����ݱ������ĵ���
			save();
			cout << "ɾ���ɹ�������" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�޸�Ա��
void SalesManager::revise()
{
	if (fileISEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ�գ�����" << endl;
	}
	else
	{
		string id;
		cout << "������Ҫ�޸ĵ�ְ��id��" << endl;
		cin >> id;
		if (existEmp(id) != -1)
		{
			int index = existEmp(id);
			Staff* s = nullptr;
			string id;
			while (1)
			{
				cout << "������ְ����ţ�" << endl;
				cin >> id;
				if (existEmp(id) != -1)
				{
					cout << "id�Ѿ����ڣ�����������" << endl;
				}
				else
				{
					break;
				}
			}
			string name;
			cout << "������ְ��������" << endl;
			cin >> name;
			int age;
			cout << "������ְ�����䣺" << endl;
			cin >> age;
			int sale;
			cout << "������ְ�����µ����۶" << endl;
			cin >> sale;
			int judge = false;
			while (!judge)
			{
				cout << "��ѡ��ְ����λ��" << endl;
				cout << "1.����Ա" << endl;
				cout << "2.����" << endl;
				cout << "3.���۾���" << endl;
				char choose;
				cin >> choose;
				switch (choose)
				{
				case '1':
					judge = true;
					s = new Salesman(id, name, age, "����Ա", sale);
					break;
				case '2':
					s = new Manager(id, name, age, "����", sale);
					judge = true;
					break;
				case '3':
					s = new SalesManager(id, name, age, "���۾���", sale);
					judge = true;
					break;
				default:
					cout << "����������������룡����" << endl;
					break;
				}
			}
			this->staffVector[index] = s;
			cout << "Ա���޸ĳɹ�������" << endl;
			save();//�����ļ�
		}
		else if (existEmp(id) == -1)
		{
			cout << "ְ��id������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����Ա��
void SalesManager::search()
{
	if (fileISEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ�գ�����" << endl;
	}
	else
	{
		char choose;
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1.Ա��id����" << endl;
		cout << "2.Ա����������" << endl;
		cin >> choose;

		if (choose == '1')
		{
			string id;
			cout << "��������Ҫ���ҵ�id��" << endl;
			cin >> id;
			if (existEmp(id) == -1)
			{
				cout << "����ʧ�ܣ���id��Ա�������ڣ�����" << endl;
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
			int n = 0;//������
			string name;
			cout << "��������Ҫ���ҵ�Ա��������" << endl;
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
				cout << "����ʧ�ܣ���������Ա�������ڣ�����" << endl;
			}
			else
			{
				cout << "������ͬ��Ա������" << n << "��" << endl;
			}
		}
		else
		{
			cout << "����������������룡" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�ع��ļ�
void SalesManager::recom()
{
	if (fileISEmpty)
	{
		cout << "��ǰ�ļ������ڻ��ļ�Ϊ��!" << endl;
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

	cout << "�ع��ɹ�������" << endl;
	save();
	system("pause");
	system("cls");
}

//ɾ������Ա��
void SalesManager::deleteAllEmp()
{
	if (fileISEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������!" << endl;
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
			cout << "��ȷ���Ƿ�����ĵ���" << endl;
			cout << "���룺Y(��ղ��˳�����)" << endl;
			cout << "���룺N(�����û��˵�)" << endl;
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
				cout << "����ɹ�������" << endl;
				staffMember = 0;
				save();
				newSave();
				system("pause");
				system("cls");
				cout << "��ӭ�´�ʹ�ã�����" << endl;
				exit(0);
			case 'N':
				system("cls");
				return;
			default:
				cout << "����������������룡" << endl;
			}
		}
	}
}

//�����۾����������Ա
void SalesManager::allocationSalesManager()
{
	while (1)
	{
		string id;
		cout << "������Ҫ�������Ա�����۾����id��" << endl;
		cin >> id;
		int y = judgeSaleManager(id);
		if (y != -1)
		{
			cout << "�����۾�����ϢΪ��" << endl;
			staffVector[y]->show();
			cout << endl;
			while (1)
			{
				string newId;
				cout << "����������Աid��" << endl;
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
					cout << "����Ա����ɹ���" << endl;
					system("pause");
					system("cls");
					return;
				}
				else if (existEmp(newId) == -1)
				{
					cout << "��Ա�������ڣ�����¼�룡" << endl;
					system("pause");
					system("cls");
					return;
				}
				else
				{
					if (existEmp(newId) == -1)
					{
						cout << "��Ա�������ڣ�����¼�룡" << endl;
						system("pause");
						system("cls");
						return;
					}
					else
					{
						cout << "��Ա����������Ա������������" << endl;
					}
				}
			}
		}
		else
		{
			cout << "��Ա���������۾�������������" << endl;
		}
	}
}

//ɾ���Ѿ����������Ա
void SalesManager::deleteAlloSaleman()
{
	if (newStaffVector.size() == 0)
	{
		cout << "��ǰ��δ���κ�������Ա��ĳλ���۾�������" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "����������Ҫɾ����ְ����ţ�" << endl;
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
				cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
				system("pause");
				system("cls");
			}
		}
		if (index != -1)
		{
			newStaffVector.erase(newStaffVector.begin() + index);
			newSave();
			cout << "ɾ���ɹ�������" << endl;
			system("pause");
			system("cls");
		}
	}
}

//���ְ���Ƿ����
int SalesManager::existEmp(string id)
{
	int index = -1;//Ĭ�ϳ�ʼֵΪ-1

	//������������Ѱ��id�Ƿ����
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

	return index;//���ظ�ְ�����ڵ���������
}

//���ļ��ڴ�������ʱ����ȡ����
int SalesManager::getFileMember()
{
	ifstream ifs;
	ifs.open("emp.dat", ios::in);

	string id;
	string name;
	int age;
	string post;
	int sale;

	int num = 0;//������

	while (ifs >> id && ifs >> name && ifs >> age && ifs >> post && ifs >> sale)
	{
		num++;
	}

	return num;
}

//�����ļ�emp.dat
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

//����ļ��е�����
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
		if (post.compare("����Ա") == 0)//Salesman 
		{
			worker = new Salesman(id, name, age, post, sale);
		}
		else if (post.compare("����") == 0)//Manager 
		{
			worker = new Manager(id, name, age, post, sale);
		}
		else if (post.compare("���۾���") == 0)//SaleManager
		{
			worker = new SalesManager(id, name, age, post, sale);
		}
		staffVector.push_back(worker);;
	}
	ifs.close();
}

//��AllocationSaleman�ļ��л�ȡ��Ϣ
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

//�����Ѿ����������Ա
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

//�ж�Ա���Ƿ�Ϊ���۾���
int SalesManager::judgeSaleManager(string id)
{
	for (int i = 0; i < staffVector.size(); i++)
	{
		if (staffVector[i]->m_post.compare("���۾���") == 0 && staffVector[i]->m_id.compare(id) == 0)
		{
			return i;
		}
	}
	return -1;
}

//�ж�Ա���Ƿ�Ϊ����Ա
int SalesManager::judgeSaleman(string id)
{
	for (int i = 0; i < staffVector.size(); i++)
	{
		if (staffVector[i]->m_post.compare("����Ա") == 0 && staffVector[i]->m_id.compare(id) == 0)
		{
			return i;
		}
	}
	return -1;
}
