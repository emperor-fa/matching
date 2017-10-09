#include"head.h"
#include<iostream>
#include <fstream>
using namespace std;
string trim(string s) {        //ȥ���ո�
	if (s.empty())
		return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
void read() {
	string str, str1;              //���� string ���� 
	int i = 0, j = 0;
	ifstream infile;
	infile.open("input_data.txt", ios::in);     //���ı�
	bool stuflag = false, departflag = false;     
	bool stufreeflag = false, stuappflag = false, stutagflag = false;
	bool departeventflag = false, departtagflag = false;
	while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
	{
		getline(infile, str1, '\n');        //��ȡһ�У�����ֵ��str1���Ի��з�����     
		str = trim(str1);      //��str1ȥ�ո�ֵ��str
		if (str == "\"students\": [") {     //�ж��Ƿ�ѧ������
			stuflag = true;
			departflag = false;
		}
		if (str == "\"departments\": [")     //�ж��Ƿ�������
		{
			departflag = true;
			stuflag = false;
		}
		if (stuflag) {             //ѧ������
			if (str == "]," || str == "]") {      //����ʱ�䣬����־Ը��ѧ����ǩ��������־
				stufreeflag = false;
				stuappflag = false;
				stutagflag = false;
			}
			if (str == "\"free_time\": [") {       //����ʱ���ȡ��־
				stufreeflag = true;
				continue;
			}
			if (str == "\"applications_department\": [") {     //����־Ը��ȡ��־
				stuappflag = true;
				continue;
			}
			if (str == "\"tags\": [") {        //ѧ����ǩ��ȡ��־
				stutagflag = true;
				continue;
			}
			if (stufreeflag)stu[i].free_time.push_back(str);        //������ʱ���ʶΪ�棬���ȡ
			if (str.substr(0, 12) == "\"student_no\"")stu[i].student_no = str.substr(14);  //��ѧ����ȡ��ȡ
			if (stuappflag)stu[i].application_department.push_back(str);       //ͬ����ʱ��
			if (stutagflag)stu[i].tags.push_back(str);       //ͬ��
			if (str == "},")i++;    //һ��ѧ�������ݶ�ȡ��ϱ�־
		}
		if (departflag) {        //�������ݣ� ͬ��
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
			if (str.substr(0, 14) == "\"member_limit\"") depart[j].member_limit = 10 + atoi(str.substr(17,1).c_str()) ;   //��ȡת��Ϊ����
			if (str.substr(0, 15) == "\"department_no\"")depart[j].department_no = str.substr(17);
			if (departtagflag)depart[j].tags.push_back(str);
			if (str == "},")j++;
		}	
	}
	infile.close();   //�ر��ı�
}