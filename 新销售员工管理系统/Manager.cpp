#include "Manager.h"

Manager::Manager(string id, string name, int age, string post, int sale)
{
	m_id = id;
	m_name = name;
	m_age = age;
	m_post = post;
	m_sale = sale;
}

void Manager::show()
{
	cout << "ְ����ţ�" << m_id << endl
		<< "ְ��������" << m_name << endl
		<< "ְ�����䣺" << m_age << endl
		<< "ְ����λ��" << m_post << endl
		<< "�������۶" << m_sale << endl;
}
