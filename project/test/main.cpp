#include"head.h"
#include<iostream>
#include <fstream>
using namespace std;
Student stu[300];
Department depart[20];
int conflict[20][20] = { 0 };
int main()
{
	read();
	ofstream fout("output_data.txt", ios::trunc);      //Çå¿ÕÎÄ±¾
	time_conflict();
	match();
	output();
	//system("pause");
}