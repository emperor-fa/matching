#ifndef HEAD_HPP
#define HEAD_HPP

#include<vector>
#include <string>
using namespace std;
extern string department[20];  //���ű��
extern string stuno[300];     //ѧ��ѧ��
extern string week[7];   //����
extern int stutime[7][8];   //����ʱ��
extern int departtime[7][7];
extern string tag[10];   //��ǩ
class Student {
public:
	//Student();
	void create(string x);    //����
	void output();    //���
private:
	vector<string> free_time;    //����ʱ��
	string student_no;       //ѧ��
	vector<string> application_department;    //־Ը����
	vector<string> tags;    //ѧ����ǩ
};
class Department {
public:
	void create(string x);
	void output();
private:
	vector<string> event_schedules;
	int member_limit;
	string department_no;
	vector<string>tags;
};

#endif