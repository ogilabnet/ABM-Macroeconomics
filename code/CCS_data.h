#ifndef INC_CCS_DATA
#define INC_CCS_DATA
#include<stdio.h>
#include<vector>
class CCS_data
{
	int money;//aΰz
	int loan_s;
	int Agent_no;
	int Producer_no;
	int Consumer_no;
	int n;
	int loan_run;

public:
	void Set_Agent_no(int x){Agent_no=x;};
	void Set_Procucer_no(int x){Producer_no=x;};
	void Set_Consumer_no(int x){Consumer_no=x;};
	void Set_IC(int n1);
	int Get_Producer_no(){return Producer_no;};
	int Get_Agent_no(){return Agent_no;};
	int Get_Consumer_no(){return Consumer_no;};
	void Money_in(int x){money+=x;};
	int Money_rate_out(double x);
	void Set_loan(int lo,int in);


	void Repayment_r(){loan_run=0;};
	void Set_loan_run(int lo){loan_run=loan_run+lo;};
	int Get_loan_run(){return loan_run;};
	void repa_loan_run(int lo){loan_run=lo;};

//	int loanod[i]->Get_money_dat

};
int CCS_data::Money_rate_out(double x)
{
	int out;
	out=int(money*x);//aΰz*xπψ«Ύ·
	money=money-out;//aΰzπXV·ι
	return out;
}
void CCS_data::Set_IC(int n1)
{
	n=n1;//ΤΟϊΤi=120AbankΜϊπΕέθj
	money=0;//aΰz
	loan_s=0;//ΨόΰΤΟz
	loan_run=0;//Ψόΰcz
}

#endif