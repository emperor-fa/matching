#include"head.h"
#include<algorithm>
#include<iostream>
#include <fstream>
using namespace std;
void stuInitialization(vector<int> &stutimeno, vector<int>&tagno, vector<int> &departno) { //初始化
	for (int i = 0; i < 56; i++)       //时间初始化：星期*时间点（7*8）
		stutimeno.push_back(i);
	for (int i = 0; i < 10; i++)    //标签初始化：总数为10
		tagno.push_back(i);
	for (int i = 0; i < 20; i++)    //志愿初始化：总数为20
		departno.push_back(i);
}
void Student::create(string x) {
	vector<int> stutimeno;    //学生星期时间二维序号数组
	vector<int> tagno;      //学生标签序号数组
	vector<int> departno;  //学生志愿序号数组
	stuInitialization(stutimeno, tagno, departno);
	vector<int>freetemp;      //创建一个数组用于存储时间下标，以便排序
	int freeno = rand() % 12 + 7;
	for (int i = 0; i < freeno; i++) {
		int timeindex = rand() % stutimeno.size();       //生成1-56随机序号
		freetemp.push_back(stutimeno[timeindex]);
		stutimeno.erase(stutimeno.begin() + timeindex);         //删除
	}
	sort(freetemp.begin(), freetemp.end());   //排序
	for (int i = 0; i < freeno; i++) {
		int x = freetemp[i]/ 8, y = freetemp[i] % 8;     //将随机数对应到二维数组下标
		free_time.push_back(week[x] + to_string(stutime[x][y]) + ":00~" + to_string(stutime[x][y] + 2) + ":00");    //加入到学生空余时间		
	}

	student_no = x;      //学生学号
	int studepartno = rand() % 5 + 1;     //随机生成志愿部门的个数
	for (int i = 0; i < studepartno; i++) {
		int departindex = rand() % departno.size();      //随机生成下标
		application_department.push_back(department[departno[departindex]]);     //将随机下标对应的部门加入到志愿部门数组
		departno.erase(departno.begin() + departindex);      //删除该下标，防止重复
	}
	int stutagno = rand() % 3 + 2;     //同上进行标签的生成
	for (int i = 0; i < stutagno; i++) {
		int tagindex = rand() % tagno.size();
		tags.push_back(tag[tagno[tagindex]]);
		tagno.erase(tagno.begin() + tagindex);
	}
}
void Student::output() {     //输出
	ofstream fout("input.txt", ios::app);     //输出到文本
	int i = 0;
	fout << "        {" << endl << "            \"free_time\": [" << endl;
	for (i = 0; i < free_time.size()-1; i++) 
		fout << "                \"" << free_time[i] << "\"," << endl;
	fout << "                \"" << free_time[i] << "\"" << endl;
	fout << "            ]," << endl;

	fout << "            \"student_no\": \"" << student_no << "\"," << endl;

	fout << "            \"applications_department\": [" << endl;
	for (i = 0; i < application_department.size()-1; i++)
		fout << "                \"" << application_department[i] << "\"," << endl;
	fout << "                \"" << application_department[i] << "\"" << endl;
	fout << "            ]," << endl;

	fout << "            \"tags\": [" << endl;
	for (i = 0; i < tags.size()-1; i++)
		fout << "                \"" << tags[i] << "\"," << endl;
	fout << "                \"" << tags[i] << "\"" << endl;

	fout << "            ]" << endl;
}