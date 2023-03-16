#pragma once
#include"Staff.h"

class Salesman : virtual public Staff
{
	friend class SalesManager;
public:
	Salesman() = default;
	Salesman(string id, string name, int age, string post, int sale);
	void show();
	string getManager();
protected:
	string m_manager;
};