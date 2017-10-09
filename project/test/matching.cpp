#include"head.h"
#include<iostream>
#include <fstream>
void time_conflict() {           //�õ����Żʱ���ͻ��
	for (int i = 0; i < 19; i++) {       //����i
		for (int j = i + 1; j < 20; j++) {      //����j
			for (int x = 0; x < depart[i].event_schedules.size(); x++) {        //����i�Ļx
				for (int y = 0; y < depart[j].event_schedules.size(); y++) {       //����j�Ļy
					if (depart[i].event_schedules[x].substr(0, 5) == depart[j].event_schedules[y].substr(0, 5)) {     //����һ��					
						int i_start=0, i_end=0, j_start=0, j_end=0;       //�������ŵĿ�ʼʱ��ͽ���ʱ��
						bool dianflag=false, bolangflag=false;         //ʱ��ǰ�ı�ʶ
						for (int k = 4; k < depart[i].event_schedules[x].length(); k++) {    //����ʱ���ַ������ֶ�ȡ
							char temp = depart[i].event_schedules[x][k];
							if (temp == '.') {     //��ʼʱ���ʶ
								dianflag = true;
								continue;
							}
							if (temp == '~') {         //����ʱ���ʶ
								dianflag = false;
								bolangflag = true;
								continue;
							}
							if (dianflag&&isdigit(temp))i_start = i_start*10+ (temp-'0');     //���㿪ʼʱ��
							if (bolangflag&&isdigit(temp))i_end = i_end * 10 + (temp - '0');   //�������ʱ��
						}
						dianflag = false, bolangflag = false;
						for (int k = 4; k < depart[j].event_schedules[y].length(); k++) {
							char temp = depart[j].event_schedules[y][k];
							if (temp == '.') {
								dianflag = true;
								continue;
							}
							if (temp == '~') {
								dianflag = false;
								bolangflag = true;
								continue;
							}
							if (dianflag&&isdigit(temp))j_start = j_start * 10 + (temp - '0');
							if (bolangflag&&isdigit(temp))j_end = j_end * 10 + (temp - '0');
						}
						if ((i_start <= j_start&&j_start < i_end) || (j_start <= i_start&&i_start < j_end)) {     //�����Ż��ͻ
							conflict[i][j] =conflict[j][i]= 1;			//��¼�ڳ�ͻ����
							x = 30;    //������һ�����ֱ������һ�����űȽ�
							y = 30;
						}
					}
				}				
			}
		}
	}
}
int tag_same(int i,int j) {   //ѧ���벿�ŵı�ǩ��ͬ����
	int k=0;
	for (int x = 0; x < stu[i].tags.size(); x++) {     //ѧ����ǩ
		for (int y = 0; y < depart[j].tags.size(); y++) {    //���ű�ǩ
			if (stu[i].tags[x].erase(stu[i].tags[x].find_last_not_of(",")+1) == depart[j].tags[y].erase(depart[j].tags[y].find_last_not_of(",")+1)) {    //���ڶ�ȡʱ��Щtag��',',����ɾȥ','
				k++;
				break;    //һ����ǩ�Ƚ���ϣ��Ƚ���һ����ǩ
			}
		}
	}
	return k;
}
int time_same(int i,int j) {      //ѧ������ʱ���벿�Żʱ��ƥ�����
	int k=0;
	for (int y = 0; y < depart[j].event_schedules.size(); y++) {       //���ŵĵ�y���
		for (int x = 0; x < stu[i].free_time.size(); x++) {         //ѧ���ĵ�x������				
			if (stu[i].free_time[x].substr(0, 5) == depart[j].event_schedules[y].substr(0, 5)) {    //����
				int stu_start=0, stu_end=0, depart_start=0, depart_end=0;      //ѧ�����кͲ��Ż�Ŀ�ʼʱ��ͽ���ʱ��
				bool dianflag = false, bolangflag = false;      //ʱ��ǰ�ı�ʶ
				for (int m = 4; m < stu[i].free_time[x].length(); m++) {
					char temp = stu[i].free_time[x][m];
					if (temp == '.') {     //��ʼʱ���ʶ
						dianflag = true;
						continue;
					}
					if (temp == '~') {	    //����ʱ���ʶ
						dianflag = false;
						bolangflag = true;
						continue;
					}
					if (dianflag&&isdigit(temp))stu_start = stu_start * 10 + (temp - '0');   //���㿪ʼʱ��
					if (bolangflag&&isdigit(temp))stu_end = stu_end * 10 + (temp - '0');     //�������ʱ��
				}
				dianflag = false, bolangflag = false;
				for (int m = 4; m < depart[j].event_schedules[y].length(); m++) {
					char temp = depart[j].event_schedules[y][m];
					if (temp == '.') {
						dianflag = true;
						continue;
					}
					if (temp == '~') {
						dianflag = false;
						bolangflag = true;
						continue;
					}
					if (dianflag&&isdigit(temp))depart_start = depart_start * 10 + (temp - '0');
					if (bolangflag&&isdigit(temp))depart_end = depart_end * 10 + (temp - '0');
				}
				if (stu_start <= depart_start&&depart_end <= stu_end) {     //ѧ������ʱ��������Żʱ��
					k++;  
					break;    //������ѧ������һ�����бȽϣ�ֱ�ӽ�����һ�����Ż�ıȽ�
				}
			}
		}
	}
	return k;
}
void swap(vector<int>&sametag, vector<int>&sametime,int x, int y,int j) {      //����sametag,sametime,���ų�Ա�����н���
	int temp;
	temp = sametag[x]; sametag[x] = sametag[y]; sametag[y] = temp;
	temp = sametime[x]; sametime[x] = sametime[y]; sametime[y] = temp;
	temp = depart[j].member[x]; depart[j].member[x] = depart[j].member[y]; depart[j].member[y] = temp;
}
void sort(int j) {       //���ų�Ա���ݱ�ǩ��ͬ�������ʱ��ƥ�������������
	vector<int>sametag;
	vector<int>sametime;
	for (int i = 0; i < depart[j].member.size(); i++) {      //��¼��ǩ��ͬ�������ʱ��ƥ�����
		sametag.push_back(tag_same(depart[j].member[i], j));
		sametime.push_back(time_same(depart[j].member[i], j));
	}
	for (int x = 0; x < depart[j].member.size()-1; x++) {     //���ŵĳ�Ա����
		for (int y = x+1; y < depart[j].member.size(); y++) {
			if (sametag[x] < sametag[y])
				swap(sametag, sametime, x, y, j);
			else if (sametag[x] == sametag[y]) {
				if (sametime[x] < sametime[y])
					swap(sametag, sametime, x, y, j);
			}
		}
	}
}
void match() {       //ƥ��
	int i,j,k;
	for (i = 0; i < 300; i++) {     //ѧ��
		for (j = 0; j < stu[i].application_department.size(); j++) {      //ѧ������־Ըj
			if (j == 0) {
				depart[atoi(stu[i].application_department[j].substr(3, 2).c_str()) - 1].member.push_back(i);     //��һ��־Ըֱ�Ӽ���
				stu[i].join++;
				//cout << "ffgfbs";
			}
			else {
				for (k = 0; k < j; k++) {
					if (conflict[atoi(stu[i].application_department[k].substr(3, 2).c_str()) - 1][atoi(stu[i].application_department[j].substr(3, 2).c_str()) - 1] == 1)   //�����־Ը����߼�־Ը��ͻ���򲻼���
						break;
				}
				stu[i].join++;
			}
		}
	}
	for (j = 0; j < 20; j++) {     //���Ž������������Ƶ���ɾ��
		if (depart[j].member.size() > depart[j].member_limit) {     //��������������������
			sort(j);       //����Ȥ���ʱ����������
			int temp = depart[j].member.size();
			for (i = temp-1; i >= depart[j].member_limit; i--)      //ɾ���������
			{
				stu[depart[j].member[i]].join--;
				depart[j].member.pop_back();
			}				
		}
	}
}
void output() {       //���
	vector<string>unlucky_department;	
	ofstream fout("output_data.txt");     //������ı�
	fout << "{" << endl;
	fout << "    \"unlucky_student\": [ ";
	for (int i = 0; i < 300; i++) {
		if (stu[i].join == 0)
			fout << endl << "        " << stu[i].student_no;
			//cout << endl << "        " << stu[i].student_no ;
	}
	fout.seekp(-1, ios_base::end);
	fout << " " << endl << "    ]," << endl;
	fout << "    \"addmitted\": [" << endl;
	for (int i = 0; i < 20; i++) {
		if (depart[i].member.size()> 0) {
			fout << "        {" << endl;
			fout << "            \"member\": [";
			for (int j = 0; j < depart[i].member.size(); j++) {
				fout << endl << "                " << stu[depart[i].member[j]].student_no;
			}
			fout.seekp(-1, ios_base::end);    //�˸�
			fout << " " << endl << "            ]," << endl;
			fout << "            \"department_no\": " << depart[i].department_no << endl;
			if(i<19)
				fout << "        }," << endl;
			else 
				fout << "        }" << endl;
		}
		else unlucky_department.push_back(depart[i].department_no);
	}
	fout << "    \"unlucky_department\": [ ";
	for (int i = 0; i < unlucky_department.size(); i++)
		fout << endl << "        " << unlucky_department[i];
	fout.seekp(-1, ios_base::end);
	fout << " " << endl << "    ]" << endl;
	fout << "}" << endl;
}