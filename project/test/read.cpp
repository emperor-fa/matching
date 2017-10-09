#include"head.h"
#include<iostream>
#include <fstream>
using namespace std;
string trim(string s) {        //去除空格
	if (s.empty())
		return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
void read() {
	string str, str1;              //采用 string 类型 
	int i = 0, j = 0;
	ifstream infile;
	infile.open("input_data.txt", ios::in);     //打开文本
	bool stuflag = false, departflag = false;     
	bool stufreeflag = false, stuappflag = false, stutagflag = false;
	bool departeventflag = false, departtagflag = false;
	while (!infile.eof())            // 若未到文件结束一直循环 
	{
		getline(infile, str1, '\n');        //读取一行，并赋值到str1，以换行符结束     
		str = trim(str1);      //将str1去空格赋值到str
		if (str == "\"students\": [") {     //判断是否学生数据
			stuflag = true;
			departflag = false;
		}
		if (str == "\"departments\": [")     //判断是否部门数据
		{
			departflag = true;
			stuflag = false;
		}
		if (stuflag) {             //学生数据
			if (str == "]," || str == "]") {      //空闲时间，部门志愿，学生标签数据完结标志
				stufreeflag = false;
				stuappflag = false;
				stutagflag = false;
			}
			if (str == "\"free_time\": [") {       //空闲时间读取标志
				stufreeflag = true;
				continue;
			}
			if (str == "\"applications_department\": [") {     //部门志愿读取标志
				stuappflag = true;
				continue;
			}
			if (str == "\"tags\": [") {        //学生标签读取标志
				stutagflag = true;
				continue;
			}
			if (stufreeflag)stu[i].free_time.push_back(str);        //若空闲时间标识为真，则读取
			if (str.substr(0, 12) == "\"student_no\"")stu[i].student_no = str.substr(14);  //将学号提取读取
			if (stuappflag)stu[i].application_department.push_back(str);       //同空闲时间
			if (stutagflag)stu[i].tags.push_back(str);       //同上
			if (str == "},")i++;    //一个学生的数据读取完毕标志
		}
		if (departflag) {        //部门数据， 同上
			if (str == "]," || str == "]") { 
				departeventflag = false;
				departtagflag = false;
			}
			if (str == "\"event_schedules\": [") {
				departeventflag = true;
				continue;
			}
			if (str == "\"tags\": [") {
				departtagflag = true;
				continue;
			}
			if (departeventflag)depart[j].event_schedules.push_back(str);
			if (str.substr(0, 14) == "\"member_limit\"") depart[j].member_limit = 10 + atoi(str.substr(17,1).c_str()) ;   //提取转化为数字
			if (str.substr(0, 15) == "\"department_no\"")depart[j].department_no = str.substr(17);
			if (departtagflag)depart[j].tags.push_back(str);
			if (str == "},")j++;
		}	
	}
	infile.close();   //关闭文本
}