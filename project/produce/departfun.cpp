#include"head.h"
#include<algorithm>
#include<iostream>
#include <fstream>
using namespace std;
void departInitialization(vector<int> &eventno, vector<int>&tagno) {
	eventno.clear();
	tagno.clear();
	for (int i = 0; i < 10; i++)
		tagno.push_back(i);
	for (int i = 0; i < 49; i++)
		eventno.push_back(i);
}
void Department::create(string x) {    //ͬѧ���Զ�����
	vector<int>eventno;
	vector<int>tagno;
	departInitialization(eventno, tagno);

	vector<int>eventtemp;
	eventtemp.clear();
	int studepartno = rand() % 5 + 1;
	for (int i = 0; i < studepartno; i++) {
		int eventindex = rand() % eventno.size();
		eventtemp.push_back(eventindex);
		eventno.erase(eventno.begin() + eventindex);
	}
	sort(eventtemp.begin(), eventtemp.end());
	for (int i = 0; i < studepartno; i++) {
		int x = eventno[eventtemp[i]] / 7, y = eventno[eventtemp[i]] % 7;
		if (y != 6)
			event_schedules.push_back(week[x] + to_string(departtime[x][y]) + ":00~" + to_string(departtime[x][y] + 1) + ":00");
		else
			event_schedules.push_back(week[x] + to_string(departtime[x][y]) + ":00~" + to_string(departtime[x][y]) + ":30");
	}

	member_limit = rand() % 6 + 10;
	department_no = x;
	int departtagno = rand() % 7 + 2;     //ͬ�Ͻ��б�ǩ������
	for (int i = 0; i < departtagno; i++) {
		int tagindex = rand() % tagno.size();
		tags.push_back(tag[tagindex]);
		tagno.erase(tagno.begin() + tagindex);
	}
}
void Department::output() {
	ofstream fout("input.txt", ios::app);     //������ı�
	int i = 0;
	fout << "        {" << endl << "            \"event_schedules\": [" << endl;
	for (i = 0; i<event_schedules.size()-1; i++)
		fout << "                \"" << event_schedules[i] << "\"," << endl;
	fout << "                \"" << event_schedules[i] << "\"" << endl;

	fout << "            ]," << endl;
	fout << "            \"member_limit\": " << member_limit << "," << endl;

	fout << "            \"department_no\": \"" << department_no << "\"," << endl;

	fout << "            \"tags\": [" << endl;
	for (i = 0; i < tags.size()-1; i++)
		fout << "                \"" << tags[i] << "\"," << endl;
	fout << "                \"" << tags[i] << "\"" << endl;

	fout << "            ]" << endl;
}