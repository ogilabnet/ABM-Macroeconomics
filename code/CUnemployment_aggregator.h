#ifndef INC_CUNEMPLOYMENT_AGGREGATOR
#define INC_CUNEMPLOYMENT_AGGREGATOR
#include <stdio.h>
#include <vector>

#include <vector>
#include <map>
#include <iostream>
#include "CParameter.h"

using namespace std;
class CUnemployment_aggregator
{
protected:
	vector<int > mem_unemployment;
	vector<int > mem_fixed_salary;
	int test;
	CParameter *cpara;

public:
	void Set_parameter_class(CParameter * cpar){cpara=cpar; };
	int Get_unemployment_no(int agent_no){return mem_unemployment[agent_no];};
	void Set_unemployment(int agent_no,int fixed_salary){mem_unemployment.push_back(agent_no);mem_fixed_salary.push_back(fixed_salary);}
	int Calc_fixed_salary();//何らかの給与の統計データを返却
	int Ave_fixed_salary();
	void Delete_unemployment(int consumer_no);
	int Get_unemployments_size(){printf("%d  cua4\n",mem_unemployment.size());return mem_unemployment.size();};
	void Print_unemploments(){
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n失業者数 %d\n失業者：",mem_unemployment.size());
		for(int i=0;i<int(mem_unemployment.size());i++)	fprintf(cpara->FI_Get_Labor_writer(),"%d , ",mem_unemployment[i]);}

};

int CUnemployment_aggregator::Calc_fixed_salary()
{
	int i,max=0;
	for(i=0;i<int(mem_fixed_salary.size());i++)
	{
		if(i==0) max=mem_fixed_salary[i];
		if(max<mem_fixed_salary[i]) max=mem_fixed_salary[i];
	}
	return max;
}
int CUnemployment_aggregator::Ave_fixed_salary()
{
	int i,sum=0,ave=0;
	for(i=0;i<int(mem_fixed_salary.size());i++)
	{
		sum+=mem_fixed_salary[i];
	}

	ave=int(sum/mem_fixed_salary.size());

	return ave;
}
void CUnemployment_aggregator::Delete_unemployment(int consumer_no)
{
	int i;
	vector <int >::iterator del_no;
	vector <int >::iterator del_sal;

	del_no=mem_unemployment.begin();
	del_sal=mem_fixed_salary.begin();
	for(i=0;i<int (mem_unemployment.size());i++)
	{
		if(mem_unemployment[i]==consumer_no)
		{
			break;
		}
		del_no++;
		del_sal++;
	}
	del_no=mem_unemployment.erase(del_no);
	del_sal=mem_fixed_salary.erase(del_sal);

}

#endif

