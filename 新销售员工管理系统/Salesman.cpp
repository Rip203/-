#include "Salesman.h"

Salesman::Salesman(string id, string name, int age, string post, int sale)
{
	m_id = id;
	m_name = name;
	m_age = age;
	m_post = post;
	m_sale = sale;
}

void Salesman::show()
{
	cout << "职工编号：" << m_id << endl
		<< "职工姓名：" << m_name << endl
		<< "职工年龄：" << m_age << endl
		<< "职工岗位：" << m_post << endl
		<< "本月销售额：" << m_sale << endl;
}

string Salesman::getManager()
{
	return this->m_manager;
}
