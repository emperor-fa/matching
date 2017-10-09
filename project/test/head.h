#ifndef HEAD_HPP
#define HEAD_HPP

#include<string>
#include<vector>
using namespace std;
void read();
void time_conflict();
void match();
void output();
class Student {
public:
	//Student();
	vector<string> free_time;    //����ʱ��
	string student_no;       //ѧ��
	vector<string> application_department;    //־Ը����
	vector<string> tags;    //ѧ����ǩ
	int join;       //���벿����
};
class Department {
public:
	vector<string> event_schedules;    //����
	int member_limit;       //��������
	string department_no;       //���ű��
	vector<string>tags;        //���ű�ǩ
	vector<int>member;
};
extern Student stu[300];
extern Department depart[20];
extern int conflict[20][20];
#endif