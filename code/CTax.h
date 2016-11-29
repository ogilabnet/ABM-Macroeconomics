//CTax.h
#ifndef INC_CTAX
#define INC_CTAX
#include<stdio.h>
#include<vector>
#include"CParameter.h"
using namespace std;

class CTax
{
	struct tax_tag
	{
		char str[20];
		int tax_type;	//010:法人税
						//020:所得税
						//030:消費税
						//910:受取法人税
						//920:受取所得税
						//930:受け取り消費税
		int i_period;
		int amount;
		int agent_no;
	}*tt;

	int profit_under_line;
	int profit_under_line_producer;
	int calculated_houzin_tax;
	int calculated_syotoku_tax;
	double corp_tax_ratio;
	double income_tax_ratio;
	double sales_tax_ratio;

	vector <struct tax_tag *> mem_tax; 

	CParameter *cpara;

	FILE *show_tax_file;

public:

	void Set_parameter_class(CParameter * cpar){cpara=cpar;};
	long long Calc_houzin_tax(long long rieki);
	long long Calc_syotoku_tax(long long inco);
	long long Calc_shouhi_tax(long long uriage);

	//セッター
	void Set_tax(int i_period, int tax_type, int amount,int agent_no);	
	void Set_IC(int profit_under_line1,int profit_under_line_producer1,double income_tax_ratio1,double corp_tax_ratio1);
	void Set_min_price(int min_price1);

	//ゲッター
	int Get_calculated_houzin_tax(){return calculated_houzin_tax;};
	int Get_calculated_syotoku_tax(){return calculated_syotoku_tax;};

	//ファイルプリント
	void Set_F_show_tax(FILE *fi){show_tax_file=fi;};
	void Show_tax(FILE *fi);
};

void CTax::Set_IC(int profit_under_line1,int profit_under_line_producer1,double income_tax_ratio1,double corp_tax_ratio1)
{
	profit_under_line=profit_under_line1;
	profit_under_line_producer=profit_under_line_producer1;
	income_tax_ratio=income_tax_ratio1;
	corp_tax_ratio=corp_tax_ratio1;
	sales_tax_ratio=cpara->GET_PARA_sales_tax_rate();
	
}


void CTax::Show_tax(FILE *fi)
{
	int size,i;
	int syotoku=0,houzin=0,shouhi=0;
	size=mem_tax.size();
	
	for(i=0;i<int(mem_tax.size());i++)
	{
		if(mem_tax[i]->tax_type==910)	houzin+=mem_tax[i]->amount;
		if(mem_tax[i]->tax_type==920)	syotoku+=mem_tax[i]->amount;
		if(mem_tax[i]->tax_type==930)	shouhi+=mem_tax[i]->amount;
	}
	fprintf(fi,"%d , %d , %d , %d\n",houzin,syotoku,shouhi,houzin+syotoku+shouhi);
	mem_tax.clear();
}
long long CTax::Calc_shouhi_tax(long long uriage)
{
	int tax;
	tax=int(uriage*cpara->GET_PARA_sales_tax_rate());
	return tax;
}
long long CTax::Calc_houzin_tax(long long rieki)
{
	int limit=1000;

	if(rieki>limit)	calculated_houzin_tax=int(rieki*cpara->GET_PARA_corp_tax_rate());
	else calculated_houzin_tax=0;

	fprintf(cpara->FI_Get_free_text2(),"法人税率　%lf\n",cpara->GET_PARA_corp_tax_rate());

	return calculated_houzin_tax;
}

long long CTax::Calc_syotoku_tax(long long inco)
{
	int limit=profit_under_line;
	switch(cpara->GET_PARA_syotokuzei_switch())
	{
		//累進課税
		case 1:
			if(limit>=inco)
				calculated_syotoku_tax=int(inco*cpara->GET_PARA_income_tax_rate()/5);	
			else if(limit<inco && inco<=limit*2)
				calculated_syotoku_tax=int(inco*cpara->GET_PARA_income_tax_rate()/4);	
			else if(limit*2<inco && inco<=limit*3)
				calculated_syotoku_tax=int(inco*cpara->GET_PARA_income_tax_rate()/3);	
			else if(limit*3<inco && inco<=limit*4)
				calculated_syotoku_tax=int(inco*cpara->GET_PARA_income_tax_rate()/2);	
			else
				calculated_syotoku_tax=int(inco*cpara->GET_PARA_income_tax_rate()/1);	
			break;

		//固定税率
		case 2:
			if(inco>=limit)	calculated_syotoku_tax=int(inco*cpara->GET_PARA_income_tax_rate());
			else calculated_syotoku_tax=0;
			break;
 
	}
	

	return calculated_syotoku_tax;
}


void CTax::Set_tax(int i_period,int tax_type,int amount,int agent_no)
{
	int size;
	size=mem_tax.size();

	tt = new struct tax_tag;
	mem_tax.push_back(tt);
	mem_tax[size]->tax_type=tax_type;
	mem_tax[size]->i_period=i_period;
	mem_tax[size]->amount=amount;
	mem_tax[size]->agent_no=agent_no;

	
}


#endif