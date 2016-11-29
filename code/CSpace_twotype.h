//CSpace_two_type　CSpaceの継承
#ifndef INC_CSPACE_TWOTYPE
#define INC_CSPACE_TWOTYPE
#include <stdio.h> 
#include <vector>
using namespace std;

class CSpace_twotype : public CSpace
{

public:
	void Set_Parameter_class(CParameter * cpar,CFunction *c){cpara=cpar;	cf=c;};
	void Set_CShow(CShow * cla_x){cs=cla_x;};

	//命名規則、（大枠時間）__（時間名）__（関数名）

	template<class T,class U> void KM__BK__Suply_inte(T &member,U &bank,int i_period); //期末_決算前_銀行側利子支払い
	template<class T,class U> void KM__BK__Repay_loan_l(T &member,U &bank,int i_period);//期末_決算前_長期借入返済
	template<class T,class U> void Inv_KM__BK__Repay_loan_l(T &member,U &bank,int i_period);//期末_決算前_長期借入返済

};
template<class T,class U> void CSpace_twotype::KM__BK__Suply_inte(T &member, U &bank,int i_period)
{
	//期末_決算前_銀行側利子支払い

	for(int i=0;i<int(member.size());i++)
	{
		int inte=0;
		inte=bank[member[i]->Get_bank_no()]->suply_inte(member,member[i]->Get_Agent_no());
		member[i]->Set_shiwake_uke_risoku(i_period,inte);
		bank[member[i]->Get_bank_no()]->Set_shiwake_risoku(i_period,inte);
	}
}

template<class T,class U> void CSpace_twotype::KM__BK__Repay_loan_l(T &member, U &bank, int i_period)
{
	int i,sum;
	int loan_l,sum_loan_l;
	int repay_lack;
	int setubi,shoukyaku,loan_r2;
	int taihi;//預金行為等での残高一時退避用変数

	for(i=0;i<int(member.size());i++)
	{
		loan_l=0;
		loan_r2=0;
		sum_loan_l=0;
		if(member[i]->Get_loan_l_zandaka()<=0)
		{
			loan_l=0;loan_r2=0;sum_loan_l=0;
		}
		else
		{
			loan_l=member[i]->Get_loan_amount();
			loan_r2=member[i]->Get_inte();
			sum_loan_l=loan_l+loan_r2;
			taihi=member[i]->Get_genkin_suitoutyou_zandaka();
			member[i]->Set_shiwake_yokin_azuke(i_period,taihi);
			bank[member[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);


			if(member[i]->Get_yokin_suitoutyou_zandaka()<sum_loan_l)
			{
				repay_lack=sum_loan_l-member[i]->Get_yokin_suitoutyou_zandaka();
				member[i]->Set_shiwake_loan(i_period,repay_lack);
				bank[member[i]->Get_bank_no()]->Set_shiwake_loan(i_period,repay_lack);
				member[i]->Set_loan_s(repay_lack);
				bank[member[i]->Get_bank_no()]->Set_loan_s(repay_lack);
			}
			bank[member[i]->Get_bank_no()]->Repayment(member,member[i]->Get_Producer_no());
		}
		if(i_period == 0){
			if(member[i]->Get_loan_l_zandaka()==0) shoukyaku=0;
			else shoukyaku=0;
		}
		else{
			if(member[i]->Get_loan_l_zandaka()==0) shoukyaku=0;
			else{
				setubi=member[i]->Get_setubi_ac();
				shoukyaku=loan_l;
			}
		}
		sum=loan_l+loan_r2;
		member[i]->Set_shiwake_kimatu(i_period,shoukyaku,loan_l,loan_r2);
		bank[member[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,loan_l,loan_r2);
		member[i]->Set_loan_l(-loan_l);
		bank[member[i]->Get_bank_no()]->Set_loan_l(-loan_l);
		bank[member[i]->Get_bank_no()]->Set_hensai(loan_l);
	}
	
}


template<class T,class U> void CSpace_twotype::Inv_KM__BK__Repay_loan_l(T &member, U &bank, int i_period)
{
	int i,sum;
	int loan_l,sum_loan_l;
	int repay_lack;
	int shoukyaku,loan_r2;
	int taihi;//預金行為等での残高一時退避用変数

	for(i=0;i<int(member.size());i++)
	{
		loan_l=0;
		loan_r2=0;
		sum_loan_l=0;
		if(member[i]->Inv_get_loan_l_number()<=0)
		{
			loan_l=0;loan_r2=0;sum_loan_l=0;
		}
		else
		{
			loan_l=member[i]->Inv_get_loan_l_amount();
			loan_r2=member[i]->Inv_get_loan_l_inte();
			sum_loan_l=loan_l+loan_r2;
			taihi=member[i]->Get_genkin_suitoutyou_zandaka();
			member[i]->Set_shiwake_yokin_azuke(i_period,taihi);
			bank[member[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);



			if(member[i]->Get_yokin_suitoutyou_zandaka()<sum_loan_l)
			{
				repay_lack=sum_loan_l-member[i]->Get_yokin_suitoutyou_zandaka();
				member[i]->Set_shiwake_loan(i_period,repay_lack);
				bank[member[i]->Get_bank_no()]->Set_shiwake_loan(i_period,repay_lack);
				member[i]->Set_loan_s(repay_lack);
				bank[member[i]->Get_bank_no()]->Set_loan_s(repay_lack);
			}

			bank[member[i]->Get_bank_no()]->Inv_repayment(loan_l,loan_r2);
			member[i]->Inv_repayment();

		}


		shoukyaku=member[i]->Inv_get_depreciation();
		member[i]->Inv_depreciation();


		sum=loan_l+loan_r2;
		member[i]->Set_shiwake_kimatu(i_period,shoukyaku,loan_l,loan_r2);
		bank[member[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,loan_l,loan_r2);
		member[i]->Set_loan_l(-loan_l);
		bank[member[i]->Get_bank_no()]->Set_loan_l(-loan_l);
		bank[member[i]->Get_bank_no()]->Set_hensai(loan_l);
		
	}
	
}
#endif

