//CEquipment.h
#ifndef INC_EQUIPMENT
#define INC_EQUIPMENT
#include <stdio.h> 
#include <vector>
using namespace std;

class CEquipment :public CProducer
{

	int comp_q;//完成時のｑの値（設備投資後のその製品種別の最大生産量）
	int pro_price;//プロジェクト用の価格(投資に必要な金額）

public:
	void Estimate(int c_q,double capa_increase_rate,int invest_money);
	void Labor_Estimate(int invest_money);
	int Get_comp_q(){return comp_q;};
	int Get_project_price(){return pro_price;};
	void Set_shiwake_uriage(int i_period,int pro_price,int genka);
	void Set_shiwake_yokin_hikidashi(int i_period,int depo_m);
	void Set_shiwake_kyuyo(int i_period,int new_income);
	void Set_shiwake_loan(int i_period,int loan);
	void Set_shiwake_yokin_azuke(int i_period,int b_m);
	void Set_shiwake_seisan(int i_period,int genka);
	void Set_shiwake_loan_long(int i_period,int loan_l);
	void Set_shiwake_konyu(int i_period,int price_w);
	void Set_shiwake_shihon(int i_period,int genkin,int yokin);
	void Set_shiwake_kisyu(int i_period,int mibarai,int pay_b);
	void Set_shiwake_loan_s_hensai(int i_period,int loan,int loan_r);
	void Set_shiwake_kimatu(int i_period,int azuke_r);
	void Set_shiwake_Labor_uriage(int i_period,int pro_price);		//設備の生産と販売にかかる原価が期によって違うので
	void Set_shiwake_Labor_hanbai(int i_period,int genka);			//この二種類を分割する

};
void CEquipment::Set_shiwake_Labor_hanbai(int i_period,int genka)
{
	cac.Set_shiwake(i_period,genka,"売上原価","製品販売","設備",genka,1,0);
}

void CEquipment::Set_shiwake_Labor_uriage(int i_period,int genka)
{
	cac.Set_shiwake(i_period,pro_price,"現金","製品販売","売上額",pro_price,0,3);
}
void CEquipment::Set_shiwake_uriage(int i_period,int pro_price,int genka)
{
	cac.Set_shiwake(i_period,genka,"売上原価","製品販売","設備",genka,1,0);
	cac.Set_shiwake(i_period,pro_price,"現金","製品販売","売上額",pro_price,0,3);
}
void CEquipment::Set_shiwake_yokin_hikidashi(int i_period,int depo_m)
{
	cac.Set_shiwake(i_period,depo_m,"現金","預金引出","預金",depo_m,0,0);
}
void CEquipment::Set_shiwake_loan(int i_period,int loan)
{
	cac.Set_shiwake(i_period,loan,"預金","短期借入","短期借入金",loan,0,2);
}
void CEquipment::Set_shiwake_kyuyo(int i_period,int new_income)
{
	cac.Set_shiwake(i_period,new_income,"未払費用","給与支払","現金",new_income,2,0);
}
void CEquipment::Set_shiwake_yokin_azuke(int i_period,int b_m)
{
	cac.Set_shiwake(i_period,b_m,"預金","預け入れ","現金",b_m,0,0);
}
void CEquipment::Set_shiwake_loan_long(int i_period,int loan_l)
{
	cac.Set_shiwake(i_period,loan_l,"現金","長期借入","長期借入金",loan_l,0,2);
}
void CEquipment::Set_shiwake_seisan(int i_period,int genka)
{
	cac.Set_shiwake(i_period,genka,"売上原価","設備生産","労務費",genka,1,1);
	cac.Set_shiwake(i_period,genka,"設備","設備生産","売上原価",genka,0,1);
}
void CEquipment::Set_shiwake_shihon(int i_period,int genkin,int yokin)
{
	cac.Set_shiwake(i_period,genkin,"現金","初期保持金","株主資本",genkin,0,2);
	cac.Set_shiwake(i_period,yokin,"預金","初期保持金","株主資本",yokin,0,2);
}
void CEquipment::Set_shiwake_kisyu(int i_period,int mibarai,int pay_b)
{
	cac.Set_shiwake(i_period,mibarai,"賃金","期首処理","未払費用",mibarai,1,2);
	cac.Set_shiwake(i_period,mibarai,"労務費","期首処理","賃金",mibarai,1,1);
}
void CEquipment::Set_shiwake_loan_s_hensai(int i_period,int loan,int loan_r)
{
	cac.Set_shiwake(i_period,loan,"短期借入金","期末処理","預金",loan,2,0);
	cac.Set_shiwake(i_period,loan_r,"短期借入利息","期末処理","預金",loan_r,1,0);
}
void CEquipment::Set_shiwake_kimatu(int i_period,int azuke_r)
{
	cac.Set_shiwake(i_period,azuke_r,"預金","期末処理","受取利息",azuke_r,0,3);
}
void CEquipment::Estimate(int c_q,double capa_increase_rate,int invest_money)
{
	comp_q=int(c_q*capa_increase_rate);//printf("comp_q=%d\n",comp_q);
		//c_q:投資前のその製品種別の最大生産量
	pro_price=invest_money;
}
void CEquipment::Labor_Estimate(int invest_money)
{
	pro_price=invest_money;
}







#endif