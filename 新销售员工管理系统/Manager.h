#pragma once
#include"Staff.h"

class Manager : virtual public Staff
{
public:
	Manager() = default;
	Manager(string id, string name, int age, string post, int sale);
	void show();
};