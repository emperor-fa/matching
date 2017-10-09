#include"head.h"
#include<iostream>
#include <fstream>
void time_conflict() {           //得到部门活动时间冲突表
	for (int i = 0; i < 19; i++) {       //部门i
		for (int j = i + 1; j < 20; j++) {      //部门j
			for (int x = 0; x < depart[i].event_schedules.size(); x++) {        //部门i的活动x
				for (int y = 0; y < depart[j].event_schedules.size(); y++) {       //部门j的活动y
					if (depart[i].event_schedules[x].substr(0, 5) == depart[j].event_schedules[y].substr(0, 5)) {     //星期一样					
						int i_start=0, i_end=0, j_start=0, j_end=0;       //两个部门的开始时间和结束时间
						bool dianflag=false, bolangflag=false;         //时间前的标识
						for (int k = 4; k < depart[i].event_schedules[x].length(); k++) {    //星期时间字符串逐字读取
							char temp = depart[i].event_schedules[x][k];
							if (temp == '.') {     //开始时间标识
								dianflag = true;
								continue;
							}
							if (temp == '~') {         //结束时间标识
								dianflag = false;
								bolangflag = true;
								continue;
							}
							if (dianflag&&isdigit(temp))i_start = i_start*10+ (temp-'0');     //计算开始时间
							if (bolangflag&&isdigit(temp))i_end = i_end * 10 + (temp - '0');   //计算结束时间
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
						if ((i_start <= j_start&&j_start < i_end) || (j_start <= i_start&&i_start < j_end)) {     //两部门活动冲突
							conflict[i][j] =conflict[j][i]= 1;			//记录在冲突表中
							x = 30;    //跳过下一个活动，直接与下一个部门比较
							y = 30;
						}
					}
				}				
			}
		}
	}
}
int tag_same(int i,int j) {   //学生与部门的标签相同个数
	int k=0;
	for (int x = 0; x < stu[i].tags.size(); x++) {     //学生标签
		for (int y = 0; y < depart[j].tags.size(); y++) {    //部门标签
			if (stu[i].tags[x].erase(stu[i].tags[x].find_last_not_of(",")+1) == depart[j].tags[y].erase(depart[j].tags[y].find_last_not_of(",")+1)) {    //由于读取时有些tag无',',所以删去','
				k++;
				break;    //一个标签比较完毕，比较下一个标签
			}
		}
	}
	return k;
}
int time_same(int i,int j) {      //学生空闲时间与部门活动时间匹配个数
	int k=0;
	for (int y = 0; y < depart[j].event_schedules.size(); y++) {       //部门的第y个活动
		for (int x = 0; x < stu[i].free_time.size(); x++) {         //学生的第x个空闲				
			if (stu[i].free_time[x].substr(0, 5) == depart[j].event_schedules[y].substr(0, 5)) {    //星期
				int stu_start=0, stu_end=0, depart_start=0, depart_end=0;      //学生空闲和部门活动的开始时间和结束时间
				bool dianflag = false, bolangflag = false;      //时间前的标识
				for (int m = 4; m < stu[i].free_time[x].length(); m++) {
					char temp = stu[i].free_time[x][m];
					if (temp == '.') {     //开始时间标识
						dianflag = true;
						continue;
					}
					if (temp == '~') {	    //结束时间标识
						dianflag = false;
						bolangflag = true;
						continue;
					}
					if (dianflag&&isdigit(temp))stu_start = stu_start * 10 + (temp - '0');   //计算开始时间
					if (bolangflag&&isdigit(temp))stu_end = stu_end * 10 + (temp - '0');     //计算结束时间
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
				if (stu_start <= depart_start&&depart_end <= stu_end) {     //学生空闲时间包含部门活动时间
					k++;  
					break;    //跳过与学生的下一个空闲比较，直接进行下一个部门活动的比较
				}
			}
		}
	}
	return k;
}
void swap(vector<int>&sametag, vector<int>&sametime,int x, int y,int j) {      //数组sametag,sametime,部门成员的两列交换
	int temp;
	temp = sametag[x]; sametag[x] = sametag[y]; sametag[y] = temp;
	temp = sametime[x]; sametime[x] = sametime[y]; sametime[y] = temp;
	temp = depart[j].member[x]; depart[j].member[x] = depart[j].member[y]; depart[j].member[y] = temp;
}
void sort(int j) {       //部门成员根据标签相同个数，活动时间匹配个数进行排序
	vector<int>sametag;
	vector<int>sametime;
	for (int i = 0; i < depart[j].member.size(); i++) {      //记录标签相同个数，活动时间匹配个数
		sametag.push_back(tag_same(depart[j].member[i], j));
		sametime.push_back(time_same(depart[j].member[i], j));
	}
	for (int x = 0; x < depart[j].member.size()-1; x++) {     //部门的成员排序
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
void match() {       //匹配
	int i,j,k;
	for (i = 0; i < 300; i++) {     //学生
		for (j = 0; j < stu[i].application_department.size(); j++) {      //学生部门志愿j
			if (j == 0) {
				depart[atoi(stu[i].application_department[j].substr(3, 2).c_str()) - 1].member.push_back(i);     //第一个志愿直接加入
				stu[i].join++;
				//cout << "ffgfbs";
			}
			else {
				for (k = 0; k < j; k++) {
					if (conflict[atoi(stu[i].application_department[k].substr(3, 2).c_str()) - 1][atoi(stu[i].application_department[j].substr(3, 2).c_str()) - 1] == 1)   //如果该志愿与更高级志愿冲突，则不加入
						break;
				}
				stu[i].join++;
			}
		}
	}
	for (j = 0; j < 20; j++) {     //部门将超过人数限制的人删除
		if (depart[j].member.size() > depart[j].member_limit) {     //招纳人数超过人数限制
			sort(j);       //按兴趣，活动时间优先排序
			int temp = depart[j].member.size();
			for (i = temp-1; i >= depart[j].member_limit; i--)      //删除多余的人
			{
				stu[depart[j].member[i]].join--;
				depart[j].member.pop_back();
			}				
		}
	}
}
void output() {       //输出
	vector<string>unlucky_department;	
	ofstream fout("output_data.txt");     //输出到文本
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
			fout.seekp(-1, ios_base::end);    //退格
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