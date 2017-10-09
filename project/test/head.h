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
	vector<string> free_time;    //空闲时间
	string student_no;       //学号
	vector<string> application_department;    //志愿部门
	vector<string> tags;    //学生标签
	int join;       //加入部门数
};
class Department {
public:
	vector<string> event_schedules;    //常规活动
	int member_limit;       //限制人数
	string department_no;       //部门编号
	vector<string>tags;        //部门标签
	vector<int>member;
};
extern Student stu[300];
extern Department depart[20];
extern int conflict[20][20];
#endif