#ifndef INC_CJOB_INFO
#define INC_CJOB_INFO
#include "CRandum.h"
#include <stdio.h>
#include <vector>
using namespace std;
#include <map>
#include <iostream>
class CJob_info
{
	int Producer_no;
	int Producer_rieki_zyouyo;
	int Fixed_salary;
	vector <int> voter_no;

public:
	CJob_info(){};
	void Vote(int Agent_no){voter_no.push_back(Agent_no);}
	void Set_producer_no(int no){Producer_no=no;};
	void Set_Producer_rieki_zyouyo(int amount){Producer_rieki_zyouyo=amount;};
	void Set_fixed_salary(int amount){Fixed_salary=amount;}
	int Get_fixed_salary(){return Fixed_salary;}
	int Get_producer_no(){return Producer_no;};
	int Get_vote_number(){return voter_no.size();};
	int Get_Producer_rieki_zyouyo(){return Producer_rieki_zyouyo;};
	int Choice();

	void Reset_job_info();

};

int CJob_info::Choice()
{
	printf("size=%d\n",voter_no.size());
	int no;	//Ì—pŽÒ
	CRandum *cr;
	no=cr->strand(0,voter_no.size()-1);
	return voter_no[no];
}

void CJob_info:: Reset_job_info()
{
	Fixed_salary=0;
	Producer_rieki_zyouyo=0;
	voter_no.clear();
}
#endif