#include"head.h"
#include <ctime>
#include<iostream>
#include <fstream>
using namespace std;
string department[20];
string stuno[300];
string week[7] = { "Mon.","Tues.","Wed.","Thur.","Fri.","Sat.","Sun." };
int stutime[7][8];
int departtime[7][7];
string tag[10] = { "basketball","dance","chess","English","film","football","music","programming","reading","study" };
void Initialization() {
	for (int i = 0; i < 9; i++)        //部门编号初始化
		department[i] = "D00" + to_string(i + 1);
	for (int i = 9; i < 20; i++)
		department[i] = "D0" + to_string(i + 1);
	for (int i = 0; i < 9; i++)           //学生学号初始化
		stuno[i] = "03150200" + to_string(i + 1);
	for (int i = 9; i < 99; i++)
		stuno[i] = "0315020" + to_string(i + 1);
	for (int i = 99; i < 300; i++)
		stuno[i] = "031502" + to_string(i + 1);
	for (int j = 0; j < 8; j++)         //学生空闲时间初始化，参照老师的input.text起始时间为8，10，12，14，16，18，20，22，时长为2小时
		for (int i = 0; i < 7; i++)
			stutime[i][j] = 8 + j * 2;
	for (int j = 0; j < 4; j++)    //部门活动时间初始化，起始时间为8，9，10，11，14，17，时长1小时；加上18：00-18：30；
		for (int i = 0; i < 7; i++)
			departtime[i][j] = 8 + j;
	for (int i = 0; i < 7; i++)
		departtime[i][4] = 14;
	for (int j = 5; j < 7; j++)
		for (int i = 0; i < 7; i++)
			departtime[i][j] = 12 + j;
}
int main()
{
	srand((unsigned)time(NULL));
	Initialization();
	Student stu[300];
	Department depart[20];
	ofstream fpout("input.txt", ios::trunc);      //清空文本
	ofstream fout("input.txt", ios::app);     //输出到文本
	fout << "{" << endl << "    \"students\": [" << endl;
	for (int i = 0; i < 300; i++) {
		stu[i].create(stuno[i]);
		stu[i].output();
		if(i!=299)
			fout << "        }," << endl;
		else
			fout << "        }" << endl;
	}
	fout << "    ]," << endl;

	fout << "    \"departments\": [" << endl;
	for (int i = 0; i < 20; i++) {
		depart[i].create(department[i]);
		depart[i].output();
		if (i != 19)
			fout << "        }," << endl;
		else
			fout << "        }" << endl;
	}
	fout << "    ]" << endl << "}" << endl;
}