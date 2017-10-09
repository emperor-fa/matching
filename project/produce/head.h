#ifndef HEAD_HPP
#define HEAD_HPP

#include<vector>
#include <string>
using namespace std;
extern string department[20];  //部门编号
extern string stuno[300];     //学生学号
extern string week[7];   //星期
extern int stutime[7][8];   //空闲时间
extern int departtime[7][7];
extern string tag[10];   //标签
class Student {
public:
	//Student();
	void create(string x);    //生成
	void output();    //输出
private:
	vector<string> free_time;    //空闲时间
	string student_no;       //学号
	vector<string> application_department;    //志愿部门
	vector<string> tags;    //学生标签
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