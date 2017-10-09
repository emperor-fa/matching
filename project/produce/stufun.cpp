#include"head.h"
#include<algorithm>
#include<iostream>
#include <fstream>
using namespace std;
void stuInitialization(vector<int> &stutimeno, vector<int>&tagno, vector<int> &departno) { //��ʼ��
	for (int i = 0; i < 56; i++)       //ʱ���ʼ��������*ʱ��㣨7*8��
		stutimeno.push_back(i);
	for (int i = 0; i < 10; i++)    //��ǩ��ʼ��������Ϊ10
		tagno.push_back(i);
	for (int i = 0; i < 20; i++)    //־Ը��ʼ��������Ϊ20
		departno.push_back(i);
}
void Student::create(string x) {
	vector<int> stutimeno;    //ѧ������ʱ���ά�������
	vector<int> tagno;      //ѧ����ǩ�������
	vector<int> departno;  //ѧ��־Ը�������
	stuInitialization(stutimeno, tagno, departno);
	vector<int>freetemp;      //����һ���������ڴ洢ʱ���±꣬�Ա�����
	int freeno = rand() % 12 + 7;
	for (int i = 0; i < freeno; i++) {
		int timeindex = rand() % stutimeno.size();       //����1-56������
		freetemp.push_back(stutimeno[timeindex]);
		stutimeno.erase(stutimeno.begin() + timeindex);         //ɾ��
	}
	sort(freetemp.begin(), freetemp.end());   //����
	for (int i = 0; i < freeno; i++) {
		int x = freetemp[i]/ 8, y = freetemp[i] % 8;     //���������Ӧ����ά�����±�
		free_time.push_back(week[x] + to_string(stutime[x][y]) + ":00~" + to_string(stutime[x][y] + 2) + ":00");    //���뵽ѧ������ʱ��		
	}

	student_no = x;      //ѧ��ѧ��
	int studepartno = rand() % 5 + 1;     //�������־Ը���ŵĸ���
	for (int i = 0; i < studepartno; i++) {
		int departindex = rand() % departno.size();      //��������±�
		application_department.push_back(department[departno[departindex]]);     //������±��Ӧ�Ĳ��ż��뵽־Ը��������
		departno.erase(departno.begin() + departindex);      //ɾ�����±꣬��ֹ�ظ�
	}
	int stutagno = rand() % 3 + 2;     //ͬ�Ͻ��б�ǩ������
	for (int i = 0; i < stutagno; i++) {
		int tagindex = rand() % tagno.size();
		tags.push_back(tag[tagno[tagindex]]);
		tagno.erase(tagno.begin() + tagindex);
	}
}
void Student::output() {     //���
	ofstream fout("input.txt", ios::app);     //������ı�
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