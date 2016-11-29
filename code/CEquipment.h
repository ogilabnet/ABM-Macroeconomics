//CEquipment.h
#ifndef INC_EQUIPMENT
#define INC_EQUIPMENT
#include <stdio.h> 
#include <vector>
using namespace std;

class CEquipment :public CProducer
{

	int comp_q;//Š®¬‚Ì‚‘‚Ì’liİ”õ“Š‘Œã‚Ì‚»‚Ì»•ií•Ê‚ÌÅ‘å¶Y—Êj
	int pro_price;//ƒvƒƒWƒFƒNƒg—p‚Ì‰¿Ši(“Š‘‚É•K—v‚È‹àŠzj

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
	void Set_shiwake_Labor_uriage(int i_period,int pro_price);		//İ”õ‚Ì¶Y‚Æ”Ì”„‚É‚©‚©‚éŒ´‰¿‚ªŠú‚É‚æ‚Á‚Äˆá‚¤‚Ì‚Å
	void Set_shiwake_Labor_hanbai(int i_period,int genka);			//‚±‚Ì“ñí—Ş‚ğ•ªŠ„‚·‚é

};
void CEquipment::Set_shiwake_Labor_hanbai(int i_period,int genka)
{
	cac.Set_shiwake(i_period,genka,"”„ãŒ´‰¿","»•i”Ì”„","İ”õ",genka,1,0);
}

void CEquipment::Set_shiwake_Labor_uriage(int i_period,int genka)
{
	cac.Set_shiwake(i_period,pro_price,"Œ»‹à","»•i”Ì”„","”„ãŠz",pro_price,0,3);
}
void CEquipment::Set_shiwake_uriage(int i_period,int pro_price,int genka)
{
	cac.Set_shiwake(i_period,genka,"”„ãŒ´‰¿","»•i”Ì”„","İ”õ",genka,1,0);
	cac.Set_shiwake(i_period,pro_price,"Œ»‹à","»•i”Ì”„","”„ãŠz",pro_price,0,3);
}
void CEquipment::Set_shiwake_yokin_hikidashi(int i_period,int depo_m)
{
	cac.Set_shiwake(i_period,depo_m,"Œ»‹à","—a‹àˆøo","—a‹à",depo_m,0,0);
}
void CEquipment::Set_shiwake_loan(int i_period,int loan)
{
	cac.Set_shiwake(i_period,loan,"—a‹à","’ZŠúØ“ü","’ZŠúØ“ü‹à",loan,0,2);
}
void CEquipment::Set_shiwake_kyuyo(int i_period,int new_income)
{
	cac.Set_shiwake(i_period,new_income,"–¢•¥”ï—p","‹‹—^x•¥","Œ»‹à",new_income,2,0);
}
void CEquipment::Set_shiwake_yokin_azuke(int i_period,int b_m)
{
	cac.Set_shiwake(i_period,b_m,"—a‹à","—a‚¯“ü‚ê","Œ»‹à",b_m,0,0);
}
void CEquipment::Set_shiwake_loan_long(int i_period,int loan_l)
{
	cac.Set_shiwake(i_period,loan_l,"Œ»‹à","’·ŠúØ“ü","’·ŠúØ“ü‹à",loan_l,0,2);
}
void CEquipment::Set_shiwake_seisan(int i_period,int genka)
{
	cac.Set_shiwake(i_period,genka,"”„ãŒ´‰¿","İ”õ¶Y","˜J–±”ï",genka,1,1);
	cac.Set_shiwake(i_period,genka,"İ”õ","İ”õ¶Y","”„ãŒ´‰¿",genka,0,1);
}
void CEquipment::Set_shiwake_shihon(int i_period,int genkin,int yokin)
{
	cac.Set_shiwake(i_period,genkin,"Œ»‹à","‰Šú•Û‹à","Š”å‘–{",genkin,0,2);
	cac.Set_shiwake(i_period,yokin,"—a‹à","‰Šú•Û‹à","Š”å‘–{",yokin,0,2);
}
void CEquipment::Set_shiwake_kisyu(int i_period,int mibarai,int pay_b)
{
	cac.Set_shiwake(i_period,mibarai,"’À‹à","Šúñˆ—","–¢•¥”ï—p",mibarai,1,2);
	cac.Set_shiwake(i_period,mibarai,"˜J–±”ï","Šúñˆ—","’À‹à",mibarai,1,1);
}
void CEquipment::Set_shiwake_loan_s_hensai(int i_period,int loan,int loan_r)
{
	cac.Set_shiwake(i_period,loan,"’ZŠúØ“ü‹à","Šú––ˆ—","—a‹à",loan,2,0);
	cac.Set_shiwake(i_period,loan_r,"’ZŠúØ“ü—˜‘§","Šú––ˆ—","—a‹à",loan_r,1,0);
}
void CEquipment::Set_shiwake_kimatu(int i_period,int azuke_r)
{
	cac.Set_shiwake(i_period,azuke_r,"—a‹à","Šú––ˆ—","óæ—˜‘§",azuke_r,0,3);
}
void CEquipment::Estimate(int c_q,double capa_increase_rate,int invest_money)
{
	comp_q=int(c_q*capa_increase_rate);//printf("comp_q=%d\n",comp_q);
		//c_q:“Š‘‘O‚Ì‚»‚Ì»•ií•Ê‚ÌÅ‘å¶Y—Ê
	pro_price=invest_money;
}
void CEquipment::Labor_Estimate(int invest_money)
{
	pro_price=invest_money;
}







#endif