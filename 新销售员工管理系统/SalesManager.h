#pragma once
#include"Staff.h"
#include"Salesman.h"
#include"Manager.h"

class SalesManager : public Salesman, public Manager
{
public:
	SalesManager();
	SalesManager(string id, string name, int age, string post, int sale);
	void allocationSalesManager();//��������Ա
	void show();//��ʾ���۾�����Ϣ
	void menu();//�˵�
	void add();//���ְ��
	void save();//�����ļ�
	void showAllEmp();//��ʾȫ��ְ��
	void recom();//�ع��ļ�����Ա��id��С��������
	void deleteEmp();//ɾ��ְ��
	void revise();//�޸�Ա��
	void search();//����ְ��
	int existEmp(string id);//���ְ���Ƿ����
	int getFileMember();//���ļ��л�ȡԱ������
	void getFileEmp();//���ļ���д������
	void deleteAllEmp();//�������Ա��
	int judgeSaleManager(string id);//�ж�Ա���Ƿ�Ϊ���۾���
	int judgeSaleman(string id);//�ж�Ա���Ƿ�Ϊ����Ա
	void newSave();//�����Ѿ�����õľ���
	void getAlloSaleman();//��AllocationSaleman�ļ��л�ȡ��Ϣ
	void deleteAlloSaleman();//ɾ���Ѿ����������Ա
private:
	vector<Staff*> staffVector;//ְ������
	vector<Salesman> newStaffVector;//�Ѿ���������Ա�����۾���ְ������
	int staffMember;//ְ������
	bool fileISEmpty;//�ж��ļ��Ƿ�Ϊ��
};
