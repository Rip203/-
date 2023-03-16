#pragma once
#include"Staff.h"
#include"Salesman.h"
#include"Manager.h"

class SalesManager : public Salesman, public Manager
{
public:
	SalesManager();
	SalesManager(string id, string name, int age, string post, int sale);
	void allocationSalesManager();//分配销售员
	void show();//显示销售经理信息
	void menu();//菜单
	void add();//添加职工
	void save();//保存文件
	void showAllEmp();//显示全部职工
	void recom();//重构文件（按员工id从小到大排序）
	void deleteEmp();//删除职工
	void revise();//修改员工
	void search();//查找职工
	int existEmp(string id);//检测职工是否存在
	int getFileMember();//从文件中获取员工人数
	void getFileEmp();//从文件中写入数据
	void deleteAllEmp();//清除所有员工
	int judgeSaleManager(string id);//判断员工是否为销售经理
	int judgeSaleman(string id);//判断员工是否为销售员
	void newSave();//保存已经分配好的经理
	void getAlloSaleman();//从AllocationSaleman文件中获取信息
	void deleteAlloSaleman();//删除已经分配的销售员
private:
	vector<Staff*> staffVector;//职工容器
	vector<Salesman> newStaffVector;//已经分配销售员的销售经理职工容器
	int staffMember;//职工人数
	bool fileISEmpty;//判断文件是否为空
};
