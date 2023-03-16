#pragma once
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class Staff
{
	friend class SalesManager;
public:
	virtual void show() = 0;
protected:
	int m_sale = 0;
	string m_id;
	string m_name;
	int m_age = 0;
	string m_post;
};