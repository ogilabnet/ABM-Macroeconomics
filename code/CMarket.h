//CMarket
#ifndef INC_CMARKET
#define INC_CMARKET
#include <stdio.h>
#include "CRandum.h"
#include "CAgent.h"
#include "CProducer.h"
#include "CConsumer.h"
#include "CBank.h"
#include "CEquipment.h"
#include "CGovernment.h"
#include "CShow.h"
#include "CFunction.h"
#include "CSpace.h"
#include "CSpace_twotype.h"
#include "CSpace_threetype.h"
#include "CSellowner.h"
#include "CPrice_tag.h"
#include "CJob_info.h"
#include "CUnemployment_aggregator.h"
//#include "CParameter.h"
#include <vector>
#include <iostream>

int strcmp(char *s1,char *s2);
using namespace std;

//～～～メモリリーク検出用・ヘッダ版～～～
#include <cstdlib>
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new  ::new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif
//～～～～～～～～～～～～～～～～～～～～

class CMarket
{
	int Agent_type;
           //Agent_type=10; 一般消費者
		   //Agent_type=20; 一般消費者向け生産者
	       //Agent_tuype=30;生産者向け生産者（原料を生産する)
	int Agent_no;

	int invest_max;
	int n_class;//市場にある製品種別の最大数
	int nmax_c;//各消費者が購入する製品種別の最大数
	int nmax_p;//各生産者が生産する製品種別の最大数
	double income_tax_rate;
	int nmax_p_min;
	double bonus_rate_min;//ボーナスを給与に還元する場合のmin比率（例：0.2なら利益の0.2倍をmin還元量とする）
	double bonus_rate_max;
	double bonus_rate_min_e;//equip
	double bonus_rate_max_e;
	int nbonus;
	int nbank_con;
	double Adjustment_Sensitivity;
	double capa_increase_rate;
	int first_price;
	int invest_money;
	double min_price_p;	
	double max_price_p;	
	double min_price_m;	
	double max_price_m;
	double max_q_re;	
	double min_q_re;
	int min_q_limit;
	double min_q_init;
	double min_with_drawal_rate;	
	double max_with_drawal_rate;//
	double price_increase_rate;	
	double price_k;
	double q_limit_k;
	int repay_time_ave,repay_time_bun;
	int i_period;//期数
	int ri_count;
	int s_stock_r;	
	int s_stock_w;
	
	
	int min_price_w;	
	int max_price_w;
	int nkessan;


	int pay_ave;		//
	int pay_ave0;		//
	int ave9;			//
	int ave7;			//平均給与

	double gov_invest_ratio;	//政府投資率

	/////////FILEの生成/////////
	//他のエージェント内に内蔵
	FILE *out3;   
	FILE *employ_FILE;	
	FILE *seisan;
	FILE *out;	
	FILE *test;	
	FILE *gyousei_syouhisya;

	
	///////VECTORの生成/////////
	vector <CProduct *> mem_product;//市場にあるリテイラー商品の集合
	vector <CProduct *> mem_product_whole;//市場にあるホールセラー商品集合
	vector <CProduct *> mem_buy;//その期に購入されたリテイラー商品の集合
	vector <CProduct *> mem_buy_w;//その期に購入されたホールセラー商品集合
	vector <CProduct *>::iterator del_p;
	vector <int> mem_ncr_w;//市場にある卸用製品種別の種別番号の集合
	vector <int> mem_ncr_r;//市場にある小売用製品種別番号の集合
	vector <int> mem_ncr_r_m;//市場にある小売り用製品種番号の原料集合
	vector <int> init_r;//初期生産リテイラーエージェントno
	vector <CProduct_class *> mem_class_statics;//市場の消費者の購入製品別統計データの集合
	vector <CProduct_class *> mem_class_statics_w;//ホールセラーの購入製品別統計データ集合
	vector <CProduct_class *>::iterator del_pc;
	vector <CProduct_class *> mem_class_stock_statics;//市場のリテイラー在庫製品別統計データの集合
	vector <CProduct_class *> mem_class_stock_statics_w;//市場のホールセラー在庫製品別統計データ集合


	vector <int > statistics_kyuyo;	//もらった給与をその場で記憶してプリントアウト（いらなければ捨てる）
	vector <int > kyuyo_no;			//statistics_kyuyoのエージェント番号保存
	vector <int > sort_static_kyuyo;//給与のソートしたエージェントナンバー
	vector <int > statistics_income;	//給与の総計
	vector <int > new_inmoney;
	vector <int > mem_unemployment;	//失業者の集合


	//////////クラスの生成/////
	CRandum *cr;
	CParameter *cpara;
	CProduct *cp;
	CAgent *ag;
	CConsumer *co;
	vector <CConsumer *> mem_con;
	CWholesaler *wh;
	vector <CWholesaler *> mem_whole;
	CRetailer *re;
	vector <CRetailer *> mem_retailer;
	CEquipment *ce;
	vector <CEquipment *> mem_equip;
	CBank *cb;
	vector <CBank *> mem_bank;
	CProducer *cpr;
	CProduct_class *cps;
	CPrice_tag *ptag;
	vector <CPrice_tag *> mem_RP_tag;
	vector <CPrice_tag *> mem_WP_tag;

	CShow *cs;
	CGovernment *cg;
	CFunction *cf;
	CSpace_twotype *cs_2;
	CSpace_threetype *cs_3;
	CSellowner *cso;


	//～～～～～Labor～～～～～～～
	CJob_info *cji;
	CUnemployment_aggregator *cua;
	vector <CJob_info *> mem_cji;
	

	//～～～～～～～～関数郡～～～～～～～～//
public:
	CMarket();//コンストラクタ
	CMarket(CShow * cla_x);//コンストラクタCShow導入（こちらが2010/11/20以降メイン）

	void Set_Parameter_class(CParameter * cpar){cpara=cpar;	};
	void Set_FILE_output();
	void Create_CSpace();
	void Set_seed(){srand(cpara->Get_PARA_seed());};


	//////初期値受け渡し////////
	void Set_parameter();


	void Set_i_period(int i_p1){i_period=i_p1;};
	void Set_randum(CRandum *cr1){cr=cr1;};
	void Set_qmax_whole(int qmaxmax_w,int qmaxmin_w);
	void Set_qmax_retailer(int qmaxmax,int qmaxmin);

	void Set_Investment(double capa_increase_rate1,int invest_money1,int min_q_limit1){capa_increase_rate=capa_increase_rate1;invest_money=invest_money1;min_q_limit=min_q_limit1;};

	///////エージェントの生成////////////
	void CReate_Consumer(int nconsumer);
	void CReate_Wholesaler(int nwholesaler);
	void CReate_Retailer(int nretailer);
	void Create_Equipment(int nequipment);
	void CReate_Bank(int nbank);
	void CReate_Government();


	////////DEFINE//////////
	void Define_seizou();
	void Define_mem_ncr_w();
	void Define_mem_ncr_r();
	void Def_statics_mem_buy();
	void Def_statics_mem_product();

	///////ファイル書き込み系関数郡///////////
	void Show_employ();
	void Show_statics_retailer();
	void Show_static_mem_buy_w();
//	void Show_statics_mem_buy();
	void Show_statics_mem_product();
	void Show_tax();
	void Show_price();

	
	///////市場行動///////

	int Get_Product_retailer(int i,int j);
	int Get_Product_wholesaler(int i,int j);
	int Get_product_size_wholesaler();
	int Get_product_size_retailer();
	int Get_Product_whole(int i,int j);
	int Get_Product_retailer_re(int i,int j);
	int Get_yokin_count(int x);

	void Set_reserve();

	void Clear_p_class_buy();
	void Clear_p_class_buy_w();
	void Erase_mem_buy();
	void Erase_mem_statics();
	void Erase_mem_stock_statics();
	void Erase_mem_statics_w();
	void Employ(int no_c);//従業員の雇用
	
	void Def_nstock_retailer();	
	void Production_retail_revised();
	void Production_whole();
	void Production_retail();
	void Production_whole_revised();
	void Production_retailer_not_whole();
	void Set_buy_number();

	void Buy_consumer();
	void Buy_producer();

		
	void Agent_hensai();
	void Investment();
	void Bankruptcy_recreate();

	void Bankruptcy(int max_ban);

	//給与支払　新版(補助金を受け取った際に合計額で預金額を定めるため、その場で預金しない)
	void Suply_pay_wage();
	void Suply_pay_wage_r();
	void Suply_pay_wage_w();
	void Suply_pay_wage_e();
	void Suply_pay_wage_b();
	void Suply_pay_wage_g();
	template<class T> void Suply_pay_producer(const T& member);


	void Calc_bonus();
	void Set_init_equipment_revel();
	void Cobb_Duclas_production_func();

	void Deposit_consumer();
	void Sort_income();
	
	void Kessan_Agent();
	void Kisyu();
//	void Kisyu_set_re();	20110222　現在使用されていない
	void Kimatu();
	void Dismiss();
	void Del_banker_product(int banker_no);	//倒産者の製品を市場から排除

	void Create_price_tag();

	
	///////税金/////////////
	void Pay_tax();

	

	///////行政処理////////
	void Collection_statistics_income();
	void Buy_government();
	void Gov_investment();
	void Situgyou_hosyou();
	void Hozyokin_kouhu();
	void Yugu_shouhisya_kouhukin();
	void Hosyou_shouhisya_kouhukin();
	void Gav_yosan();

	vector<CConsumer *> PrintDataGet_consumer_add(){return mem_con;};
	vector<CRetailer *> PrintDataGet_Retailer_add(){return mem_retailer;};
	vector<CWholesaler *> PrintDataGet_Wholesaler_add(){return mem_whole;};
	vector<CBank *> PrintDataGet_Bank_add(){return mem_bank;};
	vector<CEquipment *> PrintDataGet_Equipment_add(){return mem_equip;};
	CGovernment * PrintDataGet_Governament(){return cg;};

	vector<CProduct_class *> PrintDataGet_mem_class_statics(){return mem_class_statics;};
	vector<CProduct_class *> PrintDataGet_mem_class_statics_w(){return mem_class_statics_w;};
	vector<CProduct_class *> PrintDataGet_mem_class_stock_statics(){return mem_class_stock_statics;};
	vector<CProduct_class *> PrintDataGet_mem_class_stock_statics_w(){return mem_class_stock_statics_w;};

	vector<CProduct *> PrintDataGet_mem_buy(){return mem_buy;};
	vector<CProduct *> PrintDataGet_mem_buy_w(){return mem_buy_w;};
	vector<CProduct *> PrintDataGet_mem_product(){return mem_product;};
	vector<CProduct *> PrintDataGet_mem_product_whole(){return mem_product_whole;};
	vector<int> PrintDataGet_mem_ncr_w(){return mem_ncr_w;};
	vector<int> PrintdataGet_mem_ncr_r(){return mem_ncr_r;};


	void buy_test(vector<typename *> buyer,vector<typename *> saler);
	template<class T,class U> void Buy_retailer_product_fixamount(const T& buyer, const U& saler);
	template<class T,class U> void Buy_retailer_product_fixamount_fixclass(const T& buyer, const U& saler);
	template<class T,class U> void Buy_retailer_product_propsellamount(const T& buyer, const U& saler);
	template<class T,class U> void Buy_retailer_product_propsellamount_fixclass(const T& buyer, const U& saler);
	template<class T,class U> void Buy_retailer_product_propemployno(const T& buyer, const U& saler);
	template<class T,class U> void Buy_retailer_product_propemployno_fixclass(const T& buyer, const U& saler);
	template<class T,class U,class V> void Buy_money_func(const T& buyer, const U& saler,const V& product,int buyer_no,int saler_no,int product_no);
	template<class T,class U> void Buy_retailer_product_depend_profit_fixclass(const T &buyer, const U &saler);

	

	template <class T,class U> void Set_create_price_tag(T &member, U &tag);
	
	void test_tag();




	void CR_Define_mem_ncr_r();
	void CR_Define_mem_ncr_w();
	void CR_suply_wage();
	void CR_Set_qmax_retailer();
	void CR_production_retail();
	void CR_production_retail_revised();
	void CR_buy_consumer(){cs_3->CR_B__BC__Buy_consumer(mem_con,mem_retailer,mem_bank,mem_RP_tag,mem_product,del_p,mem_buy,i_period);};
	void CR_Set_koatari_genka();
	void CR_print_koatari_genka();
	void CR_Kessan_Agent();
	void CR_CReate_Consumer(int nconsumer);
	int CR_Get_CR_kurikosi_switch(){return cpara->GET_PARA_CR_kurikosi_switch();};
	void CR_Show_q_limit();
	void CR_Show_q_kinds();
	void CR_CReate_Retailer(int nretailer);

	void Labor_Dismiss();
	void Labor_decide_emp_inv();
	void Labor_Recruitment_activity();
	void Labor_employ();
	void Labor_Investment();

	void Labor_test_dismiss_point(){for(int i=0;i<int(mem_retailer.size());i++) mem_retailer[i]->Labor_test_dismiss_point();}
	void Labor_test_up_point(){for(int i=0;i<int(mem_retailer.size());i++) mem_retailer[i]->Labor_test_up_point();}
	template<class T,class U>void Labor_investment_action(int producer_type,T &invester,U &equip,int &inv_no);

	void Labor_print_production_power();
	void Labor_print_eqw(){for(int i=0;i<int(mem_retailer.size());i++)mem_retailer[i]->Labor_print_eqw();};
	void Labor_Reset_limit_up_data();
	void Labor_Print_unemployment(){cua->Print_unemploments();}
	void Labor_Bankruptcy(int max_ban);
	void Labor_government_yosan();
	void Labor_situgyouhosyou();
	void Labor_decide_emp_inv_not_emp();
	void Labor_Hozyokin_kouhu();
	void Labor_Hozyokin_kouhu_zyoui();
	void Labor_Hozyokin_kouhu_assignment();

	void Labor_Print_fixed_wage(){
		int sum=0;
		for(int i=0;i<int(mem_con.size());i++)	sum+=mem_con[i]->Get_constant_wage();
		fprintf(cpara->FI_Get_Labor_parameter_fixed_wage(),"%d , %d\n",i_period,sum/mem_con.size());
	}

	void PrintProducer_yokin_suitoutyou(){for(int i=0;i<int(mem_retailer.size());i++) fprintf(cpara->FI_Get_Producer_Genkin_suitoutyou(),"%d , ",mem_retailer[i]->Get_yokin_suitoutyou_zandaka()); fprintf(cpara->FI_Get_Producer_Genkin_suitoutyou(),"\n");};

	void Labor_housyu();
	void Print_allmoney();
	void Calc_R_koubai_yosan();

	void buy_checker();
	void Labor_recognition_riekiritu();

	void Labor_choice_producer();
	void Labor_test();

	////ここから設備複数化用関数群
	void Inv_set_init_equipment_level();			//設備の初期設定、Producerno呼び出し関数が変わる
	template<class T,class U>void Inv_investment_action(T &invester,U &equip,int &inv_no);		//設備投資行動、呼び出し関数が変わる

	void Inv_labor_decide_emp_inv();
	void Inv_labor_decide_inv_not_emp();


	void print_sihon(){
		for(int i=0;i<int(mem_retailer.size());i++)
		{
			if(mem_retailer[i]->Get_Agent_no()==23) mem_retailer[i]->Print_sihon();
		}
	}
	
};
void CMarket::Inv_labor_decide_inv_not_emp()
{
	int i,hensai_t,invest_price;
	hensai_t=int(cr->seiki(cpara->GET_PARA_repay_time_ave(),cpara->GET_PARA_repay_time_bun()));
	invest_price=cpara->GET_PARA_invest_money();
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n設備及び雇用の生産能力拡大方法決定の意思決定行動\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		mem_retailer[i]->Labor_limit_up_conf();
//		mem_retailer[i]->Labor_inside_data();
		mem_retailer[i]->Inv_Labor_inside_data();
		mem_retailer[i]->Labor_outside_data(hensai_t,invest_price,0.03/12);
		mem_retailer[i]->Labor_set_unemployment_data(cua->Calc_fixed_salary());
		mem_retailer[i]->Inv_Labor_calc_deicision();
		mem_retailer[i]->Labor_decision_limit_up_way_not_emp();

		if(i==0) mem_retailer[i]->Labor_out_put_data();
		fprintf(cpara->FI_Get_Labor_writer(),"\n");
	}

}
void CMarket::Inv_labor_decide_emp_inv()
{
	int i,hensai_t,invest_price;
	hensai_t=int(cr->seiki(cpara->GET_PARA_repay_time_ave(),cpara->GET_PARA_repay_time_bun()));
	invest_price=cpara->GET_PARA_invest_money();
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n設備及び雇用の生産能力拡大方法決定の意思決定行動\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		mem_retailer[i]->Labor_limit_up_conf();
		mem_retailer[i]->Inv_Labor_inside_data();

		mem_retailer[i]->Labor_outside_data(hensai_t,invest_price,0.03/12);
		mem_retailer[i]->Labor_set_unemployment_data(cua->Calc_fixed_salary());
		mem_retailer[i]->Inv_Labor_calc_deicision();

		mem_retailer[i]->Labor_decision_limit_up_way();

		if(i==0) mem_retailer[i]->Labor_out_put_data();
		fprintf(cpara->FI_Get_Labor_writer(),"\n");
	}
}
template<class T,class U> void CMarket::Inv_investment_action(T &invester,U &equip,int &inv_no)
{
	invester->Inv_investment(mem_bank[invester->Get_bank_no()],equip,inv_no);
}
void CMarket::Inv_set_init_equipment_level()
{
	int i,j;
	for(i=0;i<int(mem_retailer.size());i++)
	{
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			mem_retailer[i]->Inv_set_init_equipment_level(j);
		}
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		for(j=0;j<mem_whole[i]->Get_n_class();j++)
		{
			mem_whole[i]->Inv_set_init_equipment_level(j);
		}
	}

	fprintf(cpara->FI_Get_phenom_writer(),"\n初期設備のレベルの記述\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"retailer_no=%d: , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d ,  %d ,",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_equipment_revel(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"whole_no=%d: , ",mem_whole[i]->Get_Agent_no());
		for(j=0;j<mem_whole[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d ,  %d ,",mem_whole[i]->Get_class_no(j),mem_whole[i]->Get_equipment_revel(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
}
void CMarket::Labor_test()
{
	vector <int> test_vec;
	test_vec=cg->Get_assignment_producer();
	for(int i=0;i<int(test_vec.size());i++)
	{
		printf("g_p_no:%d\n",test_vec[i]);
	}
}
void CMarket::Labor_Hozyokin_kouhu_assignment()
{
	int i,j;
	int size;
	int g_money;
	int kouhukin=0;
	int sum_uriage=0;
	int zisseki=0;
	vector<int> assigment_pro;

	assigment_pro=cg->Get_assignment_producer();
//	int kouhu=0;
	size=mem_retailer.size()+mem_whole.size()+mem_equip.size();
	g_money=cg->Get_hozyokin_yosan();
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"yosan , %d , ",g_money);

	kouhukin=g_money/cpara->Get_PARA_Labor_assignment_size();
	

	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"kouhukin , ");
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"retailer , ");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		for(j=0;j<int(assigment_pro.size());j++)
		{
			if(assigment_pro[j]==mem_retailer[i]->Get_Agent_no())
			{
				fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",kouhukin);
				mem_retailer[i]->Set_shiwake_hozyokin(i_period,kouhukin);
				mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
				cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
				zisseki+=kouhukin;
			}
		}
	//		mem_retailer[i]->Set_yokin(kouhukin);
	}

	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"\n");
	fprintf(gyousei_syouhisya,"%d , %d\n",zisseki , cg->Get_genkin_suitoutyou_zandaka());
}
void CMarket::Labor_choice_producer()
{
	int i,j,x;
	vector <int> producer_no;
	vector <int> government_producer_no;
	vector <int> ::iterator ite;
	for(i=0;i<int(mem_retailer.size());i++)	producer_no.push_back(mem_retailer[i]->Get_Agent_no());

//	printf("assmient_size%d , switch:%d\n",cpara->Get_PARA_Labor_assignment_size(),cpara->Get_PARA_Labor_assignment_switch());
	for(i=0;i<cpara->Get_PARA_Labor_assignment_size();i++)
	{
		x=cr->strand(0,producer_no.size()-1);
		government_producer_no.push_back(producer_no[x]);
		ite=producer_no.begin();
		for(j=0;j<int(producer_no.size());j++)
		{
			if(j==x)
			{
				ite=producer_no.erase(ite);
				break;
			}
			ite++;
		}
	}
	cg->Set_assignment_producer(government_producer_no);
	for(i=0;i<int(government_producer_no.size());i++)	printf("g_p_no:%d\n",government_producer_no[i]);

}
void CMarket::Labor_recognition_riekiritu()
{
	int i;
	if(i_period==0)	
	{
		for(i=0;i<int(mem_retailer.size());i++) 
		{
			fprintf(cpara->FI_Get_Labor_keihi_soukei(),"リテイラー%d , ",mem_retailer[i]->Get_Agent_no());
			fprintf(cpara->FI_Get_Labor_keihi_toukisonekiritu(),"リテイラー%d , ",mem_retailer[i]->Get_Agent_no());
		}
		for(i=0;i<int(mem_whole.size());i++)
		{
			fprintf(cpara->FI_Get_Labor_keihi_soukei(),"ホールセラー%d , ",mem_whole[i]->Get_Agent_no());
			fprintf(cpara->FI_Get_Labor_keihi_toukisonekiritu(),"ホールセラー%d , ",mem_whole[i]->Get_Agent_no());
		}
		fprintf(cpara->FI_Get_Labor_keihi_soukei(),"\n");
	}

	
	fprintf(cpara->FI_Get_Labor_keihi_soukei(),"%d , ",i_period);
	fprintf(cpara->FI_Get_Labor_keihi_toukisonekiritu(),"%d , ",i_period);

	for(i=0;i<int(mem_retailer.size());i++)	mem_retailer[i]->Labor_recognition_riekiritu();
	for(i=0;i<int(mem_whole.size());i++)	mem_whole[i]->Labor_recognition_riekiritu();

	fprintf(cpara->FI_Get_Labor_keihi_soukei(),"\n");
	fprintf(cpara->FI_Get_Labor_keihi_toukisonekiritu(),"\n");
}
void CMarket::Calc_R_koubai_yosan()
{
	int i;
	for(i=0;i<int(mem_retailer.size());i++)	mem_retailer[i]->Calc_R_koubai_yosan();
	for(i=0;i<int(mem_whole.size());i++) mem_whole[i]->Calc_R_koubai_yosan();
}
void CMarket::buy_checker()
{
	int i,j,no,k,size=0;
	for(i=0;i<int(mem_con.size());i++)
	{
		if(mem_con[i]->Get_Agent_no()==27)
		{
			fprintf(cpara->FI_Get_free_text3(),"消費者購買力確認\n残余資金,%d\n",mem_con[i]->Get_genkin_suitoutyou_zandaka());

			for(j=0;j<mem_con[i]->Get_ncr_c();j++)
			{
				size=0;
				no=mem_con[i]->Get_buy_class_no(j);
				for(k=0;k<int(mem_product.size());k++)
				{
					if(mem_product[k]->Get_class_no()==no) size++;
				}
				fprintf(cpara->FI_Get_free_text3(),"購買可能製品種 , %d , 数量 , %d\n",no,size);

			}
		}
	}
}
void CMarket::Labor_housyu()
{
	int i;
	fprintf(cpara->FI_Get_free_text2(),"役員報酬 ,  ");
	for(i=0;i<int(mem_retailer.size());i++)	mem_retailer[i]->Labor_housyu(mem_bank);
	for(i=0;i<int(mem_whole.size());i++) mem_whole[i]->Labor_housyu(mem_bank);
	for(i=0;i<int(mem_equip.size());i++) mem_equip[i]->Labor_housyu(mem_bank);
	fprintf(cpara->FI_Get_free_text2(),"\n");
}
void CMarket::Print_allmoney()
{
	int i,sum=0,sum_genkin=0,not_bank_sum=0;
	int c_genkin=0,c_yokin=0;
	int r_genkin=0,r_yokin=0;
	int w_genkin=0,w_yokin=0;
	int e_genkin=0,e_yokin=0;
	int b_genkin=0,b_yokin=0;
	int g_genkin=0;



	for(i=0;i<int(mem_con.size());i++)	
	{
		c_genkin+=mem_con[i]->Get_genkin_suitoutyou_zandaka();
		c_yokin+=mem_con[i]->Get_yokin_suitoutyou_zandaka();
	}
	for(i=0;i<int(mem_retailer.size());i++)
	{
		r_genkin+=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();
		r_yokin+=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
	}
	for(i=0;i<int(mem_whole.size());i++)	
	{
		w_genkin+=mem_whole[i]->Get_genkin_suitoutyou_zandaka();
		w_yokin+=mem_whole[i]->Get_yokin_suitoutyou_zandaka();
	}
	for(i=0;i<int(mem_equip.size());i++)	
	{
		e_genkin+=mem_equip[i]->Get_genkin_suitoutyou_zandaka();
		e_yokin+=mem_equip[i]->Get_yokin_suitoutyou_zandaka();
	}
	for(i=0;i<int(mem_bank.size());i++)	
	{
		b_genkin+=mem_bank[i]->Get_genkin_suitoutyou_zandaka();
		b_yokin+=mem_bank[i]->Get_yokin_suitoutyou_zandaka();
	}

	g_genkin+=cg->Get_genkin_suitoutyou_zandaka();
	
	sum=c_genkin+c_yokin+r_genkin+r_yokin+w_genkin+w_yokin+e_genkin+e_yokin+b_genkin+b_yokin+g_genkin;
	sum_genkin=c_genkin+r_genkin+w_genkin+e_genkin+b_genkin+g_genkin;
	not_bank_sum=c_genkin+c_yokin+r_genkin+r_yokin+w_genkin+w_yokin+e_genkin+e_yokin+g_genkin;

	fprintf(cpara->FI_Get_all_money(),"%d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d\n",i_period,sum,c_genkin,c_yokin,r_genkin,r_yokin,w_genkin,w_yokin,e_genkin,e_yokin,b_genkin,b_yokin,g_genkin,sum_genkin,not_bank_sum);

}
void CMarket::Labor_situgyouhosyou()
{
		int s_size=0;
	int i;
	int sum_hosyou=0;
	int hosyou=0;
	int depo=0;
	int new_income;
	//失業者人数検索
	for(i=0;i<int(mem_con.size());i++)
	{
		if(mem_con[i]->Get_office_type()==-99999)	s_size++;
	}
	//失業人数検索終了
	
	sum_hosyou=cg->Get_hosyou_yosan();
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n失業補償支払い\n失業者数：%d , 全体予算：%d\n",s_size,sum_hosyou);
	if(sum_hosyou>0)
	{
		hosyou=sum_hosyou/s_size;
		
		for(i=0;i<int(mem_con.size());i++)
		{

			if(mem_con[i]->Get_office_type()==-99999)
			{
				new_income=hosyou;
				mem_con[i]->Set_depo_rate_new3(new_income);

//				fprintf(depo_ch1," , %d , %d\n",int(mem_con[i]->Get_depo_rate()*new_income),new_income);
				mem_con[i]->Renew_income(new_income);
//				printf("\n\nhosyou=  %d , new_income= %d , depo=%d\n\n",hosyou,new_income,depo);
				mem_con[i]->Set_shiwake_hosyoukin(i_period,new_income);
				cg->Set_shiwake_situgyouhosyou(i_period,new_income);

				fprintf(cpara->FI_Get_Labor_writer(),"consumer_no:%d , 失業補償:%d\n",mem_con[i]->Get_Agent_no(),new_income);
//支払時側の会計処理					mem_bank[mem_con[k]->Get_bank_no()]->Set_shiwake_kyuyo(i_period,new_income);
			}
		}

	}
	fprintf(gyousei_syouhisya," %d , ",hosyou);

}


void CMarket::Labor_government_yosan()
{
	int g_money=0,hosyou=0,toushi=0,hozyokin=0,kyuyo=0,yugu=0,koubai=0;
	int s_size=0;
	int kyuyo_yosan=0,kari_kyuyo=0;
	g_money=cg->Get_genkin_suitoutyou_zandaka();
	printf("g_money=%d\n",g_money);
	for(int i=0;i<int(mem_con.size());i++)
	{
		if(mem_con[i]->Get_office_type()==0)	s_size++;
	}

	if(cg->Get_no_employ()>0)		//公務員がいる場合に給与計算
	{
		kyuyo_yosan=int(cg->Get_genkin_suitoutyou_zandaka()*cpara->GET_PARA_wage_yosan_rate());		//給与に使える限度額を計算
		kari_kyuyo=kyuyo_yosan/cg->Get_no_employ();			//仮の一人当たり給与額算定

		if(kari_kyuyo>cg->Get_ave_inc()*cpara->GET_PARA_gav_wage_rate())					//仮の一人当たり給与予算が民間平均より大きい場合
		{
			kyuyo=int(cg->Get_ave_inc()*cg->Get_no_employ()*cpara->GET_PARA_gav_wage_rate());	//民間と同じ額
		}
		else												//仮の一人当たり給与予算が民間平均より小さい場合は予算内で行う
		{
			kyuyo=kyuyo_yosan;
		}
	}
	g_money=g_money-kyuyo;

	if(cua->Get_unemployments_size()>0)
	{
		hosyou=int(cua->Ave_fixed_salary()*cua->Get_unemployments_size()*cpara->Get_PARA_Labor_situgyouhosyou_rate());
		fprintf(cpara->FI_Get_free_text2(),"yosan : %d , size : %d\n",hosyou,cua->Get_unemployments_size());
		if(g_money>=hosyou) {}
		else if(g_money<hosyou)
		{
			hosyou=g_money;
		}

		g_money=g_money-hosyou;

	}

	toushi=int(g_money*cpara->GET_PARA_gov_invest_ratio());	//外部入力の割合で投資金決定
	yugu=int(g_money*cpara->GET_PARA_yugu_ratio());			//外部入力の割合で金持ち優遇金決定
	hozyokin=int(g_money*cpara->GET_PARA_kigyou_hozyokin_ratio());	//保障、投資が割合で差し引かれたあとの金が補助金
	koubai=int(g_money*cpara->GET_PARA_g_koubai_ratio());

	fprintf(gyousei_syouhisya,"%d , %d , %d , %d , %d , %d , %d , ",kyuyo,g_money+hosyou,hosyou,toushi,yugu,hozyokin,koubai);
	cg->Set_hosyou_yosan(hosyou);
	cg->Set_kyuyo_yosan(kyuyo);
	cg->Set_toushi_yosan(toushi);
	cg->Set_yugu_yosan(yugu);
	cg->Set_hozyokin_yosan(hozyokin);
	cg->Set_koubai_yosan(koubai);
	

	fprintf(cpara->FI_Get_phenom_writer(),"\n%d期 政府予算 , 給与予算 , 政策予算 , 失業補償予算 , 政府投資予算 , 優遇予算 , 企業補助金予算 , 購買予算\n",i_period);
	fprintf(cpara->FI_Get_phenom_writer()," , %d , %d , %d , %d , %d , %d , %d , ",kyuyo,g_money+hosyou,hosyou,toushi,yugu,hozyokin,koubai);
}

void CMarket::Labor_Bankruptcy(int max_ban)
{
	printf("banker_check\n");
	int i,j;
	int size,size_c,size_con,size_b;
	int bankr;//,i_first;
	int mo=0;	int nc;
	int loan_s,loan_l,genkin,yokin;
	int loan_s_shi;
	int bankruptcy_count=0;
	int newave_price=0;
	int genshi;
	if(i_period!=0)
	{
		newave_price=first_price;
	}
	vector <int> risyoku;
	vector<int> ::iterator del_c;
	vector <CRetailer *>::iterator del_pr;
	size=mem_retailer.size();
	size_con=mem_con.size();
	size_b=mem_bank.size();
restart:
	size=mem_retailer.size();
	del_pr=mem_retailer.begin();
	for(i=0;i<size;i++)
	{
		bankr=mem_retailer[i]->Get_bankr_p();//借入時の倒産し数（現在未使用）

		mem_retailer[i]->bankr(max_ban);//廃業処理、売れていない製品を検索して売れていなければ倒産
		nc=mem_retailer[i]->Get_ncr_p();//現在の生産クラスの確認、これが0ならば倒産処理開始		
//		printf("r=%d agent_no=%d size_r=%d bp=%d los=%d lol=%d\n",i,mem_retailer[i]->Get_Agent_no(),size,bankr,mem_retailer[i]->Get_loan_s_zandaka(),mem_retailer[i]->Get_loan_l_zandaka());
		if(nc==0)
		{
			fprintf(cpara->FI_Get_Labor_writer(),"producer_no=%d , ",mem_retailer[i]->Get_Producer_no());
				size_c=mem_retailer[i]->Get_no_employ();		//雇用しているエージェント数の取得
				loan_s=mem_retailer[i]->Get_loan_s_zandaka();	//短期借入残高取得
				loan_l=mem_retailer[i]->Get_loan_l_zandaka();	//長期借入残高取得
				printf("=========Bankr=========== r=%d agent=%d yo=%d los=%d lol=%d\n",i,mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_yokin_suitoutyou_zandaka(),loan_s,loan_l);
//				scanf("%d",&dummy);
				genkin=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();//現金残高の取得
				mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,genkin);//現金を預金に編入（銀行側処理）
				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,genkin);//現金処理の仕分け（銀行側）
				yokin=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();//預金を全額引き出し


				if(loan_s<=yokin)	//短期借入が預金より大きければ短期借入を返済する
				{
					mem_retailer[i]->Set_loan_s(-loan_s);//返済処理
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s);	//短期借入残高減算
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,loan_s,0);	//短期借入の返済仕訳処理
					mem_retailer[i]->Set_shiwake_s_hensai(i_period,loan_s);			//短期借入の返済処理
//					printf("bankr : loan_s<=yokin : loan_s=%d yokin=%d\n",loan_s,mem_retailer[i]->Get_yokin_suitoutyou_zandaka());
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(loan_s);	//～おそらく返済残高
					loan_s_shi=0;													//～～不明
					genshi=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();		//～おそらく返済原資、残額を編入
				}
				else		//短期借り入れだけでは返済できない場合
				{//loan_s>yokin
					genshi=0;													//～おそらく返済原資
					mem_retailer[i]->Set_shiwake_s_hensai(i_period,yokin);			//預金残額分だけ返済仕訳（企業側）
					mem_retailer[i]->Set_loan_s(-yokin);							//短期借入残高処理（企業側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-yokin);	//預金分だけ短期借入返済借入残高処理（銀行側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,yokin,0);//預金分だけ短期借入返済仕訳処理（銀行側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(yokin);
					loan_s_shi=loan_s-yokin;										//短期借入の残額
				}

				if(genshi>0)	//短期借入返済後に残預金があるのであれば長期返済
				{
					if(loan_l-genshi>0)//長期借入が多い場合は残額全額返却
					{
						mem_retailer[i]->Set_loan_l(-genshi);		//長期借入の返済
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-genshi);	//長期借入返済処理
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,genshi,0);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(genshi);	//長期借入返済処理
						mem_retailer[i]->Set_shiwake_l_hensai(i_period,genshi);		//長期借入返済処理（仕分け）
						loan_l=loan_l-genshi;
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
					}
					else//長期借入が残預金より少ない場合は返済後に残金ばらまき（暫定で企業に配布）
					{
						mem_retailer[i]->Set_loan_l(-genshi);		//長期借入の返済
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-genshi);	//長期借入返済処理
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,genshi,0);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(genshi);	//長期借入返済処理
						mem_retailer[i]->Set_shiwake_l_hensai(i_period,genshi);		//長期借入返済処理（仕分け）
						loan_l=0;
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
						genshi=genshi-loan_l;
						int test_pay=genshi/mem_retailer.size();			

						for(int fx=0;fx<int(mem_retailer.size());fx++)
						{
							mem_retailer[fx]->Set_shiwake_hozyokin(i_period,test_pay);
						}
					}
				}
				else//残金一切なしの場合の処理
				{
	/*				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
					*/
				}
				
			int dismiss_no,no;
			//不良債権分を保管するかどうか
			for(j=0;j<size_c;j++)
			{
				dismiss_no=mem_retailer[i]->Get_employer(j);
				if(cf->Comp_AGEvec_VAR(mem_con,dismiss_no)==1)
				{
					no=cf->Comp_AGEvec_VAR_return_no(mem_con,dismiss_no);
					cua->Set_unemployment(mem_con[no]->Get_Agent_no(),mem_con[no]->Get_constant_wage());
					mem_con[no]->Set_office(-99999);
					mem_con[no]->Set_office_type(-99999);
					fprintf(cpara->FI_Get_Labor_writer(),"dismiss_no=%d\n",mem_con[no]->Get_Agent_no());
				}
			}
			fprintf(cpara->FI_Get_Labor_writer(),"unemp_size=%d\n",cua->Get_unemployments_size());
			fprintf(test,"pn=%d\n",mem_retailer[i]->Get_Producer_no());
				
//銀行に売れ残り製品の販売権を与える（バグの元になっているので使用中止）			mem_bank[mem_retailer[i]->Get_bank_no()]->renew_stock_price_banker(mem_product,mem_retailer[i]->Get_Producer_no());
			
			Del_banker_product(mem_retailer[i]->Get_Producer_no());

			mem_retailer.erase(del_pr);
			goto restart;
		}
		del_pr++;
	}


	//状況記述
	fprintf(cpara->FI_Get_Labor_writer(),"解雇後、消費者エージェントのオフィス番号とタイプ\n");
	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_Labor_writer(),"消費者エージェント番号%d , オフィス番号：%d , オフィスタイプ：%d\n",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_office_no(),mem_con[i]->Get_office_type());
	}

	fprintf(test,"re=%d , who=%d\n",mem_retailer.size(),mem_whole.size());
}
void CMarket::Labor_Reset_limit_up_data()
{
	for(int i=0;i<int(mem_retailer.size());i++)
	{
		mem_retailer[i]->Labor_Reset_limit_up_data();
	}
}
template<class T,class U>void CMarket::Labor_investment_action(int producer_type,T &invester,U &equip,int &inv_no)
{
	int c_n,c_q,pro_price=0,loan=0,loan_w=0,hensai_t=0;
	int zikoshikin=0;
	switch(cpara->Get_PARA_Labor_invest_capital_switch())
	{
	case 0:
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用しない\n");
		//選ばれたエージェントがホールセラーの場合
		c_n=invester->Labor_get_limit_up_data_productclass();//投資対象の製品種別番号を返す
		c_q=invester->Get_class_q_limit(c_n);
		equip->Labor_Estimate(cpara->GET_PARA_invest_money());//投資後の最大生産量comp_qと投資金額pro_priceを定義する
		pro_price=equip->Get_project_price();//投資に必要なお金の額
		loan_w=pro_price;//借入金の額
		if(invester->Get_loan_l_zandaka()==0)
		{
			hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
			pro_price=int(pro_price);	loan_w=pro_price;//借入金額
			if(producer_type==0)	loan=mem_bank[invester->Get_bank_no()]->Loan_l_w(mem_whole,invester->Get_Producer_no(),loan_w,hensai_t);					//0:ホールセラーの銀行処理
			else if(producer_type==1)loan=mem_bank[invester->Get_bank_no()]->Loan_l_r(mem_retailer,invester->Get_Producer_no(),loan_w,hensai_t);	//1:リテイラーの銀行処理
			//（vector<int>loanとvector<int>inteを作成)
		}
		else
		{
			loan=0;
		}
	
	//	invest_money_w+=loan_w;
		if(loan>0)
		{
			invester->Set_loan_l(loan);
			mem_bank[invester->Get_bank_no()]->Set_loan_l(loan);
			equip->Set_rieki(loan);
			invester->Up_equipment_revel(c_n);		//プロデューサ→プロダクトクラス　ただequipmentlevelを＋＋するだけ
	//		printf("loan=%d pro_price=%d\n",loan,pro_price);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
			invester->Set_shiwake_setubi(i_period,pro_price,loan);
			equip->Set_shiwake_Labor_uriage(i_period,pro_price);
			equip->Set_shiwake_yokin_azuke(i_period,pro_price);
			mem_bank[equip->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
			invester->Labor_Reset_eqw(c_n);
			inv_no++;
		}							
		break;

	case 1:
		
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用\n");
		//選ばれたエージェントがホールセラーの場合
		c_n=invester->Labor_get_limit_up_data_productclass();//投資対象の製品種別番号を返す
		c_q=invester->Get_class_q_limit(c_n);
		equip->Labor_Estimate(cpara->GET_PARA_invest_money());//投資後の最大生産量comp_qと投資金額pro_priceを定義する
		pro_price=equip->Get_project_price();//投資に必要なお金の額

		if(invester->Get_rieki_zyouyo()>0)	zikoshikin=int(double(invester->Get_yokin_suitoutyou_zandaka()*cpara->Get_PARA_Labor_invest_capital_rate()));
		
		if(zikoshikin>pro_price)
		{
				loan_w=0;//借入金の額
				zikoshikin=pro_price;
		}
		else loan_w=pro_price-zikoshikin;//借入金の額
		
		if(loan_w>0 && invester->Get_loan_l_zandaka()==0)
		{
			hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
			pro_price=int(pro_price);	//loan_w=pro_price;//借入金額
			if(producer_type==0)	loan=mem_bank[invester->Get_bank_no()]->Loan_l_w(mem_whole,invester->Get_Producer_no(),loan_w,hensai_t);					//0:ホールセラーの銀行処理
			else if(producer_type==1)loan=mem_bank[invester->Get_bank_no()]->Loan_l_r(mem_retailer,invester->Get_Producer_no(),loan_w,hensai_t);	//1:リテイラーの銀行処理
			//（vector<int>loanとvector<int>inteを作成)
		}
		else
		{
			loan=0;
		}
	
	//	invest_money_w+=loan_w;
		if(loan>0)
		{
			invester->Set_loan_l(loan);
			mem_bank[invester->Get_bank_no()]->Set_loan_l(loan);
			equip->Set_rieki(loan);
			invester->Up_equipment_revel(c_n);		//プロデューサ→プロダクトクラス　ただequipmentlevelを＋＋するだけ
	//		printf("loan=%d pro_price=%d\n",loan,pro_price);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
			invester->Set_shiwake_setubi(i_period,pro_price,loan);
			equip->Set_shiwake_Labor_uriage(i_period,pro_price);
			equip->Set_shiwake_yokin_azuke(i_period,pro_price);
			mem_bank[equip->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
			invester->Labor_Reset_eqw(c_n);
			inv_no++;
			fprintf(cpara->FI_Get_Labor_writer(),"自己資本投入型エージェントナンバー：%d , 自己資本：%d , 借入額：%d\n",invester->Get_Agent_no(),zikoshikin,loan);
		}
		else if(zikoshikin==pro_price)
		{
//			invester->Set_loan_l(loan);
	//		mem_bank[invester->Get_bank_no()]->Set_loan_l(loan);
			equip->Set_rieki(loan);
			invester->Up_equipment_revel(c_n);		//プロデューサ→プロダクトクラス　ただequipmentlevelを＋＋するだけ
	//		printf("loan=%d pro_price=%d\n",loan,pro_price);
	//		mem_bank[invester->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,pro_price);
			invester->Set_shiwake_setubi(i_period,pro_price,loan);
			equip->Set_shiwake_Labor_uriage(i_period,pro_price);
			equip->Set_shiwake_yokin_azuke(i_period,pro_price);
			mem_bank[equip->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
			invester->Labor_Reset_eqw(c_n);
			inv_no++;
			fprintf(cpara->FI_Get_Labor_writer(),"自己資本投入型エージェントナンバー：%d , 自己資本：%d , 借入額：%d\n",invester->Get_Agent_no(),zikoshikin,loan);
		}
		break;

/*	case 2:
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用\n");
		//選ばれたエージェントがホールセラーの場合
		c_n=invester->Labor_get_limit_up_data_productclass();//投資対象の製品種別番号を返す
		c_q=invester->Get_class_q_limit(c_n);
		equip->Labor_Estimate(cpara->GET_PARA_invest_money());//投資後の最大生産量comp_qと投資金額pro_priceを定義する
		pro_price=equip->Get_project_price();//投資に必要なお金の額

		if(invester->Get_rieki_zyouyo()>0)	zikoshikin=int(double(invester->Get_yokin_suitoutyou_zandaka()*cpara->Get_PARA_Labor_invest_capital_rate()));
		
		if(zikoshikin>pro_price)
		{
				loan_w=0;//借入金の額
				zikoshikin=pro_price;
		}
		else loan_w=pro_price-zikoshikin;//借入金の額
		
		if(loan_w>0 && invester->Get_loan_l_zandaka()==0)
		{
			hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
			pro_price=int(pro_price);	//loan_w=pro_price;//借入金額
			if(producer_type==0)	loan=mem_bank[invester->Get_bank_no()]->Loan_l_w(mem_whole,invester->Get_Producer_no(),loan_w,hensai_t);					//0:ホールセラーの銀行処理
			else if(producer_type==1)loan=mem_bank[invester->Get_bank_no()]->Loan_l_r(mem_retailer,invester->Get_Producer_no(),loan_w,hensai_t);	//1:リテイラーの銀行処理
			//（vector<int>loanとvector<int>inteを作成)
		}
		else
		{
			loan=0;
		}
	
	//	invest_money_w+=loan_w;
		if(loan>0)
		{
			invester->Set_loan_l(loan);
			mem_bank[invester->Get_bank_no()]->Set_loan_l(loan);
			equip->Set_rieki(loan);
			invester->Up_equipment_revel(c_n);		//プロデューサ→プロダクトクラス　ただequipmentlevelを＋＋するだけ
	//		printf("loan=%d pro_price=%d\n",loan,pro_price);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
			invester->Set_shiwake_setubi(i_period,pro_price,loan);
			equip->Set_shiwake_Labor_uriage(i_period,pro_price);
			equip->Set_shiwake_yokin_azuke(i_period,pro_price);
			mem_bank[equip->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
			invester->Labor_Reset_eqw(c_n);
			inv_no++;
			fprintf(cpara->FI_Get_Labor_writer(),"自己資本投入型エージェントナンバー：%d , 自己資本：%d , 借入額：%d\n",invester->Get_Agent_no(),zikoshikin,loan);
		}
		else if(zikoshikin==pro_price)
		{
//			invester->Set_loan_l(loan);
	//		mem_bank[invester->Get_bank_no()]->Set_loan_l(loan);
			equip->Set_rieki(loan);
			invester->Up_equipment_revel(c_n);		//プロデューサ→プロダクトクラス　ただequipmentlevelを＋＋するだけ
	//		printf("loan=%d pro_price=%d\n",loan,pro_price);
	//		mem_bank[invester->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,pro_price);
			invester->Set_shiwake_setubi(i_period,pro_price,loan);
			equip->Set_shiwake_Labor_uriage(i_period,pro_price);
			equip->Set_shiwake_yokin_azuke(i_period,pro_price);
			mem_bank[equip->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
			invester->Labor_Reset_eqw(c_n);
			inv_no++;
			fprintf(cpara->FI_Get_Labor_writer(),"自己資本投入型エージェントナンバー：%d , 自己資本：%d , 借入額：%d\n",invester->Get_Agent_no(),zikoshikin,loan);
		}
		break;*/

	case 2:
		int zikoshikin=0;
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用\n");
		//選ばれたエージェントがホールセラーの場合
		c_n=invester->Labor_get_limit_up_data_productclass();//投資対象の製品種別番号を返す
		c_q=invester->Get_class_q_limit(c_n);
		equip->Labor_Estimate(cpara->GET_PARA_invest_money());//投資後の最大生産量comp_qと投資金額pro_priceを定義する
		pro_price=equip->Get_project_price();//投資に必要なお金の額

//		zikoshikin=int(double(invester->Get_yokin_suitoutyou_zandaka()*cpara->Get_PARA_Labor_invest_capital_rate()));
		zikoshikin=int(double(pro_price)*double(cpara->Get_PARA_owncash_rate_inv()));
		//zikoshikin=int(double(pro_price)*double(0.5));

		printf("kingaku test \n 0.5:%d , para:%d\n",int(double(pro_price)*double(0.5)),int(double(pro_price)*double(cpara->Get_PARA_owncash_rate_inv())));
		scanf("%d",&zikosihon);
		printf("teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n");

		loan_w=pro_price-zikoshikin;//借入金の額
		
		if(loan_w>0 && invester->Get_loan_l_zandaka()==0 && invester->Get_yokin_suitoutyou_zandaka()-zikoshikin>0)
		{
			hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
			pro_price=int(pro_price);	//loan_w=pro_price;//借入金額
			if(producer_type==0)	loan=mem_bank[invester->Get_bank_no()]->Loan_l_w(mem_whole,invester->Get_Producer_no(),loan_w,hensai_t);					//0:ホールセラーの銀行処理
			else if(producer_type==1)loan=mem_bank[invester->Get_bank_no()]->Loan_l_r(mem_retailer,invester->Get_Producer_no(),loan_w,hensai_t);	//1:リテイラーの銀行処理
			//（vector<int>loanとvector<int>inteを作成)
		}

		if(loan>0)
		{
			invester->Set_loan_l(loan);
			mem_bank[invester->Get_bank_no()]->Set_loan_l(loan);

			invester->Set_shiwake_yokin_hikidashi(i_period,zikoshikin);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,zikoshikin);
				

			equip->Set_rieki(loan+zikoshikin);
			invester->Up_equipment_revel(c_n);		//プロデューサ→プロダクトクラス　ただequipmentlevelを＋＋するだけ
	//		printf("loan=%d pro_price=%d\n",loan,pro_price);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
			mem_bank[invester->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
			invester->Set_shiwake_setubi(i_period,pro_price,loan);
			equip->Set_shiwake_Labor_uriage(i_period,pro_price);
			equip->Set_shiwake_yokin_azuke(i_period,pro_price);
			mem_bank[equip->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
			invester->Labor_Reset_eqw(c_n);
			inv_no++;
			fprintf(cpara->FI_Get_Labor_writer(),"自己資本投入型エージェントナンバー：%d , 自己資本：%d , 借入額：%d\n",invester->Get_Agent_no(),zikoshikin,loan);
		}
		break;
	}
	
}


void CMarket::Labor_print_production_power()
{
	int i,j;
	fprintf(cpara->FI_Get_Labor_writer(),"\n%d生産能力限界\n",i_period);
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_Labor_writer(),"retailer_no=%d: , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_Labor_writer(),"class=%d ,  %d ,",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_class_q_limit(j));
		}
		fprintf(cpara->FI_Get_Labor_writer(),"\n");
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		fprintf(cpara->FI_Get_Labor_writer(),"whole_no=%d: , ",mem_whole[i]->Get_Agent_no());
		for(j=0;j<mem_whole[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_Labor_writer(),"class=%d ,  %d ,",mem_whole[i]->Get_class_no(j),mem_whole[i]->Get_class_q_limit(j));
		}
		fprintf(cpara->FI_Get_Labor_writer(),"\n");
	}

}
void CMarket::Labor_Investment()
{
	int i,j,k,l,m,b=0;
//	int size_r,size_w,size_e,size_inw;
	int size_e,size_inw;
	int ni,nicon;
//	int c_n,c_q;
//	int loan,pro_price;
//	int loan_w;
	int cap_b=0,res=0;
//	int hensai_t;//返済期間
//	double kk;
	int invest_counter=0;
//	size_r=mem_retailer.size();
//	size_w=mem_whole.size();
	size_e=mem_equip.size();
	vector <int> inw;
	vector <int>::iterator p;
	vector <int> inw_r;
	vector <int> inw_w;
	vector <int> e_uriage;
	for(i=0;i<size_e;i++) e_uriage.push_back(0);
	//------------------------------------
	int no_r=0;//投資retailerの数
	int invest_money_r=0;//retailerの投資金総額
	int no_w=0;//投資wholesalerの数
	int invest_money_w=0;//wholesalerの投資金総額
	//-------------------------------------
	//要求を持つエージェントを集める

	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_eqw(),"producer_no, %d: , ",mem_retailer[i]->Get_Agent_no());
		mem_retailer[i]->Get_eqw();
		if(mem_retailer[i]->Labor_get_limit_up_data_way()==2)	inw.push_back(mem_retailer[i]->Get_Producer_no());
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		if(mem_whole[i]->Labor_get_limit_up_data_way()==2)	inw.push_back(mem_whole[i]->Get_Producer_no());
	}

	
	if(inw.size()>0)
	{
		//投資要求のあるエージェントをランダムに選ぶ
		for(j=0;j<invest_max;j++)//一期での選定数
		{
			size_inw=inw.size();
			if(size_inw>0)
			{	
				ni=cr->strand(0,size_inw-1);
				i=inw[ni];//投資機会のあるエージェント番号
				p=inw.begin();
				nicon=0;
				for(k=0;k<size_inw;k++)
				{
					if(nicon==ni) 
					{
						p=inw.erase(p);
						break;
					}
					p++;nicon++;
				}
				//選ばれたエージェントがホールセラーの場合
				if(i<=mem_whole[int(mem_whole.size())-1]->Get_Producer_no())
				{
					inw_w.push_back(i);
					for(l=0;l<int(mem_whole.size());l++)
					{
						if(mem_whole[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							//Labor_investment_action(0,mem_whole[l],mem_equip[m],no_w);
							Inv_investment_action(mem_whole[l],mem_equip[m],no_w);
						}
					}
				}
				else
				{
					inw_r.push_back(i);//選ばれたエージェントがリテイラ
					for(l=0;l<int(mem_retailer.size());l++)
					{
	//					printf("r_p=%d,i=%d r_n=%d\n",mem_retailer[l]->Get_Producer_no(),i,l);
						if(mem_retailer[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
//							Labor_investment_action(1,mem_retailer[l],mem_equip[m],no_r);
							Inv_investment_action(mem_retailer[l],mem_equip[m],no_r);
						}
					}
				}
			}
		}
	}
	
	
	for(i=0;i<size_e;i++)
	{
		mem_equip[i]->Set_shiwake_seisan(i_period,mem_equip[i]->Get_koteihi());
		mem_equip[i]->Set_shiwake_Labor_hanbai(i_period,mem_equip[i]->Get_koteihi());
		//mem_equip[i]->Set_shiwake_uriage(i_period,e_uriage[i],mem_equip[i]->Get_koteihi());
		printf("eq:%d\n",mem_equip[i]->Get_koteihi());
//		printf("cons:%d , bonus:%d\n",mem_equip[i]->Get_total_price_genka(),mem_equip[i]->Get_bonus());
	}

	cs->CM_Show_Investment_top(no_r,no_w,invest_money_r,invest_money_w);//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//	fprintf(invest," , %d, %d , %d, %d,",no_r,no_w,invest_money_r,invest_money_w);上の行と一緒でなければ削除しないこと

	for(i=0;i<int(inw_r.size());i++) cs->CM_Show_Investment_middle(inw_r[i]);//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//		fprintf(invest," %d ,",inw_r[i]);上の行と一緒でなければ削除しないこと

	for(i=0;i<int(inw_w.size());i++) cs->CM_Show_Investment_middle(inw_w[i]);//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//		fprintf(invest," %d ,",inw_w[i]);上の行と一緒でなければ削除しないこと

	cs->CM_Show_Investment_row();//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//	fprintf(invest,"\n");上の行と一緒でなければ削除しないこと
}

void CMarket::Labor_decide_emp_inv_not_emp()
{
	int i,hensai_t,invest_price;
	hensai_t=int(cr->seiki(cpara->GET_PARA_repay_time_ave(),cpara->GET_PARA_repay_time_bun()));
	invest_price=cpara->GET_PARA_invest_money();
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n設備及び雇用の生産能力拡大方法決定の意思決定行動\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		mem_retailer[i]->Labor_limit_up_conf();
		mem_retailer[i]->Labor_inside_data();
		mem_retailer[i]->Labor_outside_data(hensai_t,invest_price,0.03/12);
		mem_retailer[i]->Labor_set_unemployment_data(cua->Calc_fixed_salary());
		mem_retailer[i]->Labor_calc_deicision();
		mem_retailer[i]->Labor_decision_limit_up_way_not_emp();

		if(i==0) mem_retailer[i]->Labor_out_put_data();
		fprintf(cpara->FI_Get_Labor_writer(),"\n");
	}

}
void CMarket::Labor_decide_emp_inv()
{
	int i,hensai_t,invest_price;
	hensai_t=int(cr->seiki(cpara->GET_PARA_repay_time_ave(),cpara->GET_PARA_repay_time_bun()));
	invest_price=cpara->GET_PARA_invest_money();
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n設備及び雇用の生産能力拡大方法決定の意思決定行動\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		mem_retailer[i]->Labor_limit_up_conf();
		mem_retailer[i]->Labor_inside_data();
		mem_retailer[i]->Labor_outside_data(hensai_t,invest_price,0.03/12);
		mem_retailer[i]->Labor_set_unemployment_data(cua->Calc_fixed_salary());
		mem_retailer[i]->Labor_calc_deicision();
		mem_retailer[i]->Labor_decision_limit_up_way();

		if(i==0) mem_retailer[i]->Labor_out_put_data();
		fprintf(cpara->FI_Get_Labor_writer(),"\n");
	}

}
void CMarket::Labor_Recruitment_activity()
{
	int i,j,emp_num=0;
	vector<CJob_info *> ::iterator del_info;
	Labor_Print_unemployment();
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～求人票の出力～～～\n\n");
	for(i=0;i<int(mem_retailer.size());i++)	//求人票出力
	{
//		mem_retailer[i]->Labor_set_mem_cji(mem_cji);
		mem_retailer[i]->Labor_Create_Jobs_info(mem_cji);
		fprintf(cpara->FI_Get_Labor_writer(),"size=%d\n",mem_cji.size());
	}
	for(i=0;i<int (mem_cji.size());i++ ) fprintf(cpara->FI_Get_Labor_writer(),"Producer_no:%d , salary:%d,rieki_zyouyo=%d\n",mem_cji[i]->Get_producer_no(),mem_cji[i]->Get_fixed_salary(),mem_cji[i]->Get_Producer_rieki_zyouyo());

	fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～消費者の応募～～～\n\n");
	for(i=0;i<int(mem_con.size());i++)		//応募
	{
		if(mem_con[i]->Get_office_no()<0) mem_con[i]->Laboer_Choice_Producer(mem_cji);
	}
	
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～求人票の回収と雇用～～～\n\n");
	for(i=0;i<int(mem_retailer.size());i++)	//求人票の回収と雇用
	{
		mem_retailer[i]->Labor_reemploy(mem_cji,mem_con,cua,del_info,emp_num);
	}
	
	fprintf(cpara->FI_Get_Labor_employ_time(),"%d , %d\n",i_period,emp_num);

	fprintf(cpara->FI_Get_employ_file(),"\n\n i_period:%d\n",i_period);
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_employ_file(),"agent_no:%d , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_no_employ();j++)	fprintf(cpara->FI_Get_employ_file(),"%d , ",mem_retailer[i]->Get_employer(j));
		fprintf(cpara->FI_Get_employ_file(),"\n");
	}
	Labor_Print_unemployment();
}


void CMarket::Labor_Dismiss()
{
	int i,dismiss_no=0,no;

	for(i=0;i<int(mem_retailer.size());i++)			//リテイラーのループ　解雇者がいるかを判定,同時に利益順位のための配列収集
	{
fprintf(cpara->FI_Get_Labor_writer(),"producer_no=%d , ",mem_retailer[i]->Get_Producer_no());
		mem_retailer[i]->Decide_dismisses();	//解雇行動判定
		if(mem_retailer[i]->Get_dismiss_flag()==1)	//解雇であれば解雇者ベクタにエージェントを入れる
		{
fprintf(cpara->FI_Get_Labor_writer(),"dismiss_flag=OK\n");
			//mem_unemployment.push_back(mem_retailer[i]->Get_dismiss_no());
			dismiss_no=mem_retailer[i]->Get_dismiss_no();
			if(cf->Comp_AGEvec_VAR(mem_con,dismiss_no)==1)
			{
				no=cf->Comp_AGEvec_VAR_return_no(mem_con,dismiss_no);
				cua->Set_unemployment(mem_con[no]->Get_Agent_no(),mem_con[no]->Get_constant_wage());
				mem_con[no]->Set_office(-99999);
				mem_con[no]->Set_office_type(-99999);
				fprintf(cpara->FI_Get_Labor_writer(),"dismiss_no=%d\n",mem_con[no]->Get_Agent_no());
			}
		}
		else fprintf(cpara->FI_Get_Labor_writer(),"dismiss_flag=NO\n");

	}											//解雇者の取り出し終了
fprintf(cpara->FI_Get_Labor_writer(),"unemp_size=%d\n",cua->Get_unemployments_size());
	fprintf(cpara->FI_Get_se_con(),"\n\n");


	//状況記述
	fprintf(cpara->FI_Get_Labor_writer(),"解雇後、消費者エージェントのオフィス番号とタイプ\n");
	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_Labor_writer(),"消費者エージェント番号%d , オフィス番号：%d , オフィスタイプ：%d\n",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_office_no(),mem_con[i]->Get_office_type());
	}



}




void CMarket::CR_CReate_Retailer(int nretailer)
{
	int i,j,depo;	int i_period=0;	int shihon;
	int size_b;
	size_b=mem_bank.size();
	for(i=0;i<nretailer;i++)
	{
		Agent_no++;
		re=new CRetailer;

		re->Set_parameter_class(cpara);	//パラメータクラスのセット
		re->Set_tax_class(cg->Get_CTax_class());
		re->Set_randum(cr);				//ランダムクラスのセット
		
		//共通化可能部分
		re->Set_n_class(cpara->GET_PARA_n_class());
		//
		re->Set_IC();
		re->Set_Agent_no(Agent_no);
		re->Set_Agent_type(20);
		re->Set_Producer_no(Agent_no);
		re->Set_Producer_type(20);
		
		
		re->Def_koteihi(cpara->GET_PARA_min_koteihi(),cpara->GET_PARA_max_koteihi());
		re->Set_bank_no(cr->strand(0,size_b-1));

		re->Set_ncr_p(cpara->GET_PARA_nmax_p());
		re->Set_ncr_c(cr->strand(1,cpara->GET_PARA_nmax_c()));
		re->Create_Product_class_p(cpara->GET_PARA_max_memo_time(),cpara->GET_PARA_max_reac_flag());
		//ncr_p個のProduct_classのインスタンスを生成し、mem_class_pに格納する
		re->Create_mem_buy_retailer_product_data();			//企業の購買情報プロダクトクラスデータの生成
//		if(re->Get_Agent_no()==7 || re->Get_Agent_no()==8)
		if(re->Get_Agent_no()==30)
		{
			re->Set_nkessan(2);
			re->Set_ncase(2);
		}
		else{
			re->Set_nkessan(cpara->GET_PARA_nkessan());
			re->Set_ncase(cpara->GET_PARA_ncase());
		}

		depo=cr->strand(cpara->GET_PARA_min_init_depo_r(),cpara->GET_PARA_max_init_depo_r());
		shihon=depo+(depo/10);

		re->Set_kisyu_shihon(shihon);
		re->Set_kisyu_zandaka();

		re->Set_bonus(0);
		re->Set_bankr_p(0);
		re->Set_buy_p(0);
		re->Reset_loan_time();
		re->Set_loan_time_limit(cpara->GET_PARA_loan_time_limit());
		if(cpara->GET_PARA_CR_maxqre_decision_switch()!=0||cpara->GET_PARA_pricing_switch()==5||cpara->GET_PARA_pricing_switch()==6)
		{
			re->CR_set_price_q_rate();
		}
		mem_retailer.push_back(re);
		mem_retailer[i]->Set_shiwake_shihon(i_period,depo/10,depo);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);
		init_r.push_back(mem_retailer[i]->Get_Producer_no());
	}

	
	fprintf(cpara->FI_Get_phenom_writer(),"\nリテイラーの生成\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"create whole: , agent_no=%d , agent_type=%d , genkin=%d , yokin=%d\n",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_Agent_type(),mem_retailer[i]->Get_genkin_suitoutyou_zandaka(),mem_retailer[i]->Get_yokin_suitoutyou_zandaka());
		fprintf(cpara->FI_Get_phenom_writer(),"class size=%d , ",mem_retailer[i]->Get_mem_class_p_size());
		for(j=0;j<mem_retailer[i]->Get_mem_class_p_size();j++)	fprintf(cpara->FI_Get_phenom_writer(),"class_no=%d , ",mem_retailer[i]->Get_class_no(j));
		fprintf(cpara->FI_Get_phenom_writer(),"\n\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\n");

}
void CMarket::CR_Show_q_kinds()
{
	int i,j,k,count=0;
	if(i_period==0)
	{
		fprintf(cpara->FI_Get_CR_syubetu_koubaimae_seihinsu(),"期数 , ");
		fprintf(cpara->FI_get_CR_syubetu_seisansu(),"期数 , ");
		for(i=0;i<int(mem_ncr_r.size());i++)
		{
			fprintf(cpara->FI_Get_CR_syubetu_koubaimae_seihinsu(),"%d番 , ",mem_ncr_r[i]);
			fprintf(cpara->FI_get_CR_syubetu_seisansu(),"%d番 , ",mem_ncr_r[i]);
		}
		fprintf(cpara->FI_Get_CR_syubetu_koubaimae_seihinsu(),"購買前製品数 \n");
		fprintf(cpara->FI_get_CR_syubetu_seisansu(),"生産数\n");
	}
	
	fprintf(cpara->FI_Get_CR_syubetu_koubaimae_seihinsu(),"%d , ",i_period);
	fprintf(cpara->FI_get_CR_syubetu_seisansu(),"%d , ",i_period);



	for(i=0;i<int(mem_ncr_r.size());i++)
	{
		count=0;
		for(j=0;j<int(mem_product.size());j++)
		{
			if(mem_ncr_r[i]==mem_product[j]->Get_class_no())	count++;
		}
		fprintf(cpara->FI_Get_CR_syubetu_koubaimae_seihinsu(),"%d , ",count);
	}

	for(i=0;i<int(mem_ncr_r.size());i++)
	{
		count=0;
		for(j=0;j<int(mem_retailer.size());j++)
		{
			for(k=0;k<mem_retailer[j]->Get_n_class();k++)
			{
				if(mem_ncr_r[i]==mem_retailer[j]->Get_class_no(k)) count+=mem_retailer[j]->Get_q(k);
			}
		}
		fprintf(cpara->FI_get_CR_syubetu_seisansu(),"%d , ",count);
	}

	fprintf(cpara->FI_Get_CR_syubetu_koubaimae_seihinsu(),"\n");
	fprintf(cpara->FI_get_CR_syubetu_seisansu(),"\n");



}
void CMarket::CR_Show_q_limit()
{
	int q_size=0,q_seisan=0;
	for(int i=0;i<int(mem_retailer.size());i++)	
	{
		for(int j=0;j<mem_retailer[i]->Get_n_class();j++) 
		{		
			q_size+=mem_retailer[i]->Get_q_limit(j);
			q_seisan+=mem_retailer[i]->Get_q(j);
		}
	}

//	fprintf(cpara->FI_Get_free_text(),"retailer_q_sum=%d , seisan_q=%d\n",q_size,q_seisan);
}
void CMarket:: CR_CReate_Consumer(int nconsumer)
{
	int i,depo;	int i_period=0;	int shihon;
	int size_b;
	int k_switch=cpara->GET_PARA_CR_kurikosi_switch();	//繰越をするかしないかの判定スイッチ
	size_b=mem_bank.size();
	for(i=0;i<nconsumer;i++)
	{
		Agent_no++;
		co=new CConsumer;
		co->Set_randum(cr);
		co->Set_parameter_class(cpara);
		co->Set_tax_class(cg->Get_CTax_class());

		co->Set_Agent_no(Agent_no);
		co->Set_Agent_type(10);
		co->Set_Consumer_no(Agent_no);
		co->Set_Consumer_type(10);
		co->Set_n_class(cpara->GET_PARA_n_class());
		co->Set_ncr_c(cr->strand(4,cpara->GET_PARA_nmax_c()));
		co->Create_Product_class_c(cpara->GET_PARA_max_memo_time(),cpara->GET_PARA_max_reac_flag());//ncr_c個のProduct_classのインスタンスを生成する
		co->Set_constant_wage(co->Def_income(cpara->GET_PARA_min_constant_wage(),cpara->GET_PARA_max_constant_wage()));
		co->Set_weight_buy();
		co->Set_bank_no(cr->strand(0,size_b-1));
		co->Set_deporate_decision_Coefficient(cpara->GET_PARA_threshold_deposit(),cpara->GET_PARA_deporate_coefficient());
		depo=cr->strand(cpara->GET_PARA_min_init_depo_c(),cpara->GET_PARA_max_init_depo_c());
		shihon=depo+(depo/10);
		co->Set_kisyu_shihon(shihon);
		co->Set_kisyu_zandaka();
		if(co->Get_Agent_no()==90){
			co->Set_nkessan(2);
			co->Set_ncase(2);
		}
		else{
			co->Set_nkessan(cpara->GET_PARA_nkessan());
			co->Set_ncase(cpara->GET_PARA_ncase());
		}
		mem_con.push_back(co);
		
		if(k_switch==0 || k_switch==1 ||k_switch==2)
			mem_con[i]->Set_shiwake_shihon(i_period,depo/10,depo);
		else
			mem_con[i]->Set_shiwake_shihon(i_period,depo/10,0);

		mem_bank[mem_con[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);
	}


	fprintf(cpara->FI_Get_phenom_writer(),"\n消費者の生成\n");
	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"create consumer: , agent_no=%d , agent_type=%d , genkin=%d , yokin=%d , ",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_Agent_type(),mem_con[i]->Get_genkin_suitoutyou_zandaka(),mem_con[i]->Get_yokin_suitoutyou_zandaka());
		fprintf(cpara->FI_Get_phenom_writer(),"class size=%d , ",mem_con[i]->Get_ncr_c());
		fprintf(cpara->FI_Get_phenom_writer(),"\n\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
}
void CMarket::CR_Kessan_Agent()
{
	int nk;//nkessan && i
	int i,x;	int rieki;
	int size_c,size_r,size_sum;
	int loan_l=0,loan_r2=0;
	int zankin=0;
	int zankin_mainus=0;
	int shihon=0;
	int bonus_limit_wage_rate=1;
	int zankin_sum=0,zankin_minus_sum=0;
	int kisyu_yokin=0;
	int no_employ=0;
	
	size_c=mem_con.size();
	
	size_r=mem_retailer.size();
	
	size_sum=size_r;//retailer+wholesaler+equipment+bank
	x=size_c/size_sum;//従業員配分のmin数


	for(i=0;i<size_c;i++)
	{
		if(i<1)
		{
			if(nkessan==0 || nkessan==1)	nk=0;
			else nk=1;
		}
		else nk=1;
		if(nk==0) fprintf(out3,"%d期 Consumer = %d Agent_no=%d\n",i_period,i,mem_con[i]->Get_Agent_no());
		mem_con[i]->Kessan(0,&rieki,i_period);
	}

	for(i=0;i<size_r;i++)
	{
		loan_l=0;
		loan_r2=0;

		if(i<2)
		{
			if(nkessan==0 || nkessan==1)	nk=0;
			else nk=1;
		}
		else nk=1;
		if(0==0) fprintf(out3,"%d期 Retailer = %d Agent_no=%d\n",i_period,i,mem_retailer[i]->Get_Agent_no());
		mem_retailer[i]->Kessan(0,&rieki,i_period);

//20111120		loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
//20111120		loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
		mem_retailer[i]->Set_bonus_account_clac();
//		no_employ=mem_retailer[i]->Get_no_employ();
//		mem_retailer[i]->Calc_bonus(loan_l,loan_r2,no_employ);


//		fprintf(cpara->FI_Get_free_text2(),"ag_no:%d , zankin:%d , zankin_mainus:%d\n",mem_retailer[i]->Get_Agent_no(),zankin,zankin_mainus);
//		printf("pay_bonus %d\n",pay_bonus);
		//ボーナス計算終了
	}

//	fprintf(cpara->FI_Get_free_text2(),"zankin , %d , zankin_minus , %d\n",zankin_sum,zankin_minus_sum);
}
void CMarket::CR_print_koatari_genka()
{
	fprintf(cpara->FI_Get_phenom_writer(),"個当たり原価の表示\n");
	for(int i=0;i<int(mem_retailer.size());i++)	
	{
		fprintf(cpara->FI_Get_phenom_writer(),"producer_no=%d , ",mem_retailer[i]->Get_Producer_no());
		for(int j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"clas_no=%d  koatari_genryouhi=%d , ",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->CR_Get_koatari_genryouhi(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}

	fprintf(cpara->FI_Get_phenom_writer(),"個当たり原価の表示～～終了～～～\n\n\n\n");
}
void CMarket::CR_Set_koatari_genka()
{
	for(int i=0;i<int(mem_retailer.size());i++)	
	{
		mem_retailer[i]->CR_set_koatari_genka();
		mem_retailer[i]->CR_set_koatari_genryouhi();
	}
}
void CMarket::CR_Define_mem_ncr_r()
{
	//retailerの製品種別番号の集合=consusmerが購入する製品種別番号の集合、を定義する
	int i,j;
	int size_ncr_w;
	int ncon;
	for(i=0;i<int(mem_ncr_w.size());i++) printf("w_size=%d, i=%d\n",mem_ncr_w.size(),mem_ncr_w[i]);
	size_ncr_w=mem_ncr_w.size();
	for(i=0;i<n_class;i++)
	{
		ncon=0;
		for(j=0;j<size_ncr_w;j++)
		{
			if(mem_ncr_w[j]!=i) ncon++;
		//	if(mem_ncr_w[j]==i) ncon=1;
		}
		//iがncr_size_wに含まれていない新しい番号であればmem_ncr_rに入れる.
		if(ncon==size_ncr_w) mem_ncr_r.push_back(i);	
	}

	printf("ncr_r.size=%d ncr_w.size=%d\n",mem_ncr_r.size(),mem_ncr_w.size());
	for(i=0;i<int(mem_ncr_r.size());i++)
	{
		printf("%d\n",mem_ncr_w[i]);
		mem_ncr_r_m.push_back(mem_ncr_w[i]);
	}

	fprintf(cpara->FI_Get_phenom_writer(),"define mem_ncr_r\n リテイラーの製品種集合の表示\n mem_ncr_r size=%d , ",mem_ncr_r.size());
	for(i=0;i<int(mem_ncr_r.size());i++) fprintf(cpara->FI_Get_phenom_writer(),"mem_ncr_r no%d: , %d , ",i,mem_ncr_r[i]);
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
	fprintf(cpara->FI_Get_phenom_writer(),"define mem_ncr_r_m\n リテイラーの製品種の減量表示\n mem_ncr_r_m size=%d , ",mem_ncr_r_m.size());
	for(i=0;i<int(mem_ncr_r.size());i++) fprintf(cpara->FI_Get_phenom_writer(),"mem_ncr_r_m no%d: , %d , ",i,mem_ncr_r_m[i]);
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
}
void CMarket::CR_Define_mem_ncr_w()
{
	//wholesalerの製品種別番号の集合を定義する
	int i;
	int ncon=0;
	int ncon_whole=0;
//	int size;
//	int size_ncr_w;
//	int class_no;	

	for(i=0;i<cpara->GET_PARA_n_class()/2;i++)
	{
		printf("%d\n",cpara->GET_PARA_n_class()/2);
		mem_ncr_w.push_back(i);
	}
}
void CMarket::CR_production_retail()
{
		//初期生産
	int size,size_b;
	int i,j;int b=0;
	int ncr_p;//int p_gen,p_gen2,price_w;
//	int size_wp;
//	int material_need,depo_m;
//	int z;
//	int capital;
//	int loan,lack_money;
	int hyouka_genka=0;
//	int ncon=0,min_pro=0,min_id;
		//min_pro:minimum price of product in the market
		//min_id:no of minimum price product in mem_product_whole

	size=mem_retailer.size();
	size_b=mem_bank.size();

//	fprintf(cpara->FI_Get_market_product()," , ");
	cs->CM_Show_Production_retail_top(mem_product_whole.size());//CShow機能移転、依存度が高い場合は削除、下の行が機能内容
//	fprintf(market_product," %d ,",mem_product_whole.size());//上の行と一緒でなければ削除しないこと
	
	for(i=0;i<size;i++)
	{
		mem_retailer[i]->First_set_q();
		hyouka_genka=0;
		fprintf(seisan,"R , %d , %d , %d , ",i,mem_retailer[i]->Get_Producer_no(),mem_retailer[i]->Get_Agent_no());
//		mem_retailer[i]->Set_material_need();
				//各製品種別毎に生産量qを決定する
				//material_need=生産量とする
				//価格の改定は未

//		depo_m=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
//		capital=mem_retailer[i]->Get_genkin_suitoutyou_zandaka()+depo_m;//売上集計後の所有金額+depo_mを所有金額とする
//		mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,depo_m);//預金を全額引き出す
//		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_m);

		mem_retailer[i]->Set_total_price_genka(mem_retailer[i]->Get_buy_p());
		mem_retailer[i]->CR_seisan_plan();
		
		int taihi;
		taihi=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();
		mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,mem_retailer[i]->Get_genkin_suitoutyou_zandaka());
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);



		mem_retailer[i]->CR_seisan();//		mem_retailer[i]->Seisan_revised();//各製品種別について製品をq個作る

		

		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();//生産する製品種別の数
//		p_gen2=mem_retailer[i]->Get_total_price_genka()-mem_retailer[i]->Get_buy_p()-mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ();
//		price_w=mem_retailer[i]->Get_buy_p();
//		mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);
//		mem_retailer[i]->Set_shiwake_seisan(i_period,p_gen2+price_w);

		for(j=0;j<ncr_p;j++)
		{
			hyouka_genka+=Get_Product_retailer(i,j);//i番目リテーラーからj番目種目の製品の納入をq個うけ,mem_productに格納する
			//mem_productには同一のリテーラー,製品種別の製品が連番で格納される
		}
//		hyouka_genka-=(p_gen2+price_w);
		mem_retailer[i]->Set_shiwake_seisan(i_period,hyouka_genka);	//評価原価の誤差分
		mem_retailer[i]->Erase_retail_buy();
		fprintf(seisan,"\n-----------------------------------------------------------------------------\n");
		
	}

	cs->CM_Show_Production_retail_row(mem_product_whole.size());//CShowに機能移転、依存度が高ければ削除、機能は下の行の通り
	fprintf(cpara->FI_Get_market_product(),",");
	cs->CM_Show_Production_retail_row(mem_product.size());
}
void CMarket::CR_production_retail_revised()
{
	int size,size_w;
	int i,j;int b=0;
	int ncr_p;
	int p_gen2;
	int price_w;
	int capital;
	int hyouka_genka=0;
	int product_before=mem_product.size();
	int test_i;
	vector <int> retailer_no;
	vector <int> ::iterator del_no;
	vector <CProduct *>::iterator del_pw;
	del_pw=mem_product_whole.begin();
	size=mem_retailer.size();
	size_w=mem_whole.size();

	cso->Set_price_tag(mem_product_whole,mem_WP_tag);

	cs->CM_Show_Production_retail_top(mem_product_whole.size());	//CShowに機能移譲、依存度高めなら削除、機能は下の行

	for(i=0;i<int(mem_retailer.size());i++)	retailer_no.push_back(i);
	
	
	while(retailer_no.size()>0)
	{
		test_i=0;
		i=cf->Random_choice_int(retailer_no,del_no);

		hyouka_genka=0;

		mem_retailer[i]->CR_New_set_price();		//価格の決定
		mem_retailer[i]->CR_Seisan_plan_revised(mem_product_whole,max_q_re,min_q_re,Adjustment_Sensitivity);
		
				//各製品種別毎に生産量qを決定する
		        //在庫がある場合には予定生産量-在庫を新規の生産量とする。
				//material_need=生産量とする
				//価格の改定は未

//		cs_3->PR__PR__Buy_material_retailer(mem_retailer,mem_whole,mem_bank,mem_WP_tag,mem_product_whole,del_pw,mem_buy_w,i,i_period);


		//原料購買行動終わり
		capital=0;
	//	mem_retailer[i]->Set_capital(capital);
		mem_retailer[i]->Calc_cost(q_limit_k,price_increase_rate,min_price_p,max_price_p,min_price_m,max_price_m);//各製品種別毎に改定価格を定義してpriceを更新する
		mem_retailer[i]->CR_set_koatari_genryouhi();
		mem_retailer[i]->Renew_stock_price(mem_product);//売れ残り商品の価格を改定する
		mem_retailer[i]->CR_seisan();

		if(mem_retailer[i]->Get_buy_p()==0)	 p_gen2=mem_retailer[i]->Get_total_price_genka();
		else	p_gen2=mem_retailer[i]->Get_total_price_genka();

		price_w=mem_retailer[i]->Get_buy_p();
		mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);
		mem_retailer[i]->Set_shiwake_seisan(i_period,p_gen2+mem_retailer[i]->Get_buy_p());

		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++)	hyouka_genka+=Get_Product_retailer_re(i,j);
		hyouka_genka-=(p_gen2+mem_retailer[i]->Get_buy_p());
		mem_retailer[i]->Set_shiwake_seisan(i_period,hyouka_genka);
		mem_retailer[i]->Reset_buy_p();
	}

	
	cso->Set_price_tag(mem_product,mem_RP_tag);	//リテイラーのプライスタグ作成
	cs->Show_Product_tag(mem_RP_tag);			//作成したプライスタグのプリント


	cs->CM_Show_Production_retail_top(mem_product_whole.size());//CShowに機能移譲、依存度高めなら削除、機能は下の行
	cs->CM_Show_Production_retail_row(mem_product.size()-product_before);//CShowに機能移譲、依存度高めなら削除、機能は下の行
}
void CMarket::CR_Set_qmax_retailer()
{
	int i,j,q_limit;
	fprintf(cpara->FI_Get_phenom_writer(),"\n\n\nリテイラー生産力の状況\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"producer_no=%d , ",mem_retailer[i]->Get_Producer_no());
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			q_limit=cr->strand(cpara->GET_PARA_CR_fixed_q_limit_down(),cpara->GET_PARA_CR_fixed_q_limit_up());
			mem_retailer[i]->Set_q_limit(q_limit,j,min_q_limit);
			mem_retailer[i]->Adjust_q_init(j);
			mem_retailer[i]->Adjust_q_init(j);
			fprintf(cpara->FI_Get_phenom_writer(),"class %d q=%d , ",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_q_limit(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n\n");
	}

	fprintf(cpara->FI_Get_phenom_writer(),"リテイラー生産力状況終了\n\n");
}
void CMarket::CR_suply_wage()
{
	int i;
	int fixed_income=cpara->GET_PARA_CR_fixed_income();
	int pay_ave=0;
	int clear_money=0;
	int kurikoshi_switch=cpara->GET_PARA_CR_kurikosi_switch();
	for(i=0;i<int(mem_con.size());i++)
	{
		if(kurikoshi_switch==2 || kurikoshi_switch==5)
		{//非繰越作業		繰越をしない2と5の時だけ起動
			clear_money=mem_con[i]->Get_genkin_suitoutyou_zandaka();
			mem_con[i]->Set_shiwake_syotoku_tax(i_period,clear_money);
		}

		mem_con[i]->Set_depo_rate_new3(fixed_income);
		mem_con[i]->Renew_income(fixed_income);
		mem_con[i]->Set_shiwake_kyuyo(i_period,fixed_income);

		pay_ave+=fixed_income;

		statistics_income.push_back(fixed_income);
		sort_static_kyuyo.push_back(mem_con[i]->Get_Agent_no());
		statistics_kyuyo.push_back(fixed_income);
		kyuyo_no.push_back(mem_con[i]->Get_Agent_no());
	}
}

CMarket::CMarket()
{
	cp=new CProduct;
	cr=new CRandum;
	

	

	srand(150);
	Agent_no=0;
}

CMarket::CMarket(CShow * cla_x)
{

	cp=new CProduct;
	cr=new CRandum;
	cf=new CFunction(cr);
	cso=new CSellowner;
	cs=cla_x;
//	cs_2=new CSpace_twotype(cr);


//	srand(150);
//	
	Agent_no=0;
}
void CMarket::Create_CSpace()
{
	cs_2=new CSpace_twotype;
	cs_3=new CSpace_threetype;
	cua=new CUnemployment_aggregator;
	cua->Set_parameter_class(cpara);
	
	cs_2->Set_Parameter_class(cpara,cf);
	cs_3->Set_Parameter_class(cpara,cf);
	cs_2->Set_CShow(cs);
	cs_3->Set_CShow(cs);
}
void CMarket::test_tag()
{
//	vector<CPrice_tag *>::iterator tag_ite;
//	cso->Create_price_tag(mem_retailer,mem_RP_tag);

}
void CMarket::Create_price_tag()
{
	Set_create_price_tag(mem_retailer,mem_RP_tag);
	cso->Set_price_tag(mem_product,mem_RP_tag);

	Set_create_price_tag(mem_whole,mem_WP_tag);
	cso->Set_price_tag(mem_product_whole,mem_WP_tag);
	cs->Show_Product_tag(mem_RP_tag);
	cs->Show_Product_tag(mem_WP_tag);
}
template <class T,class U> void CMarket::Set_create_price_tag(T &member, U &tag)
{
	int checker;
	for(int i=0;i<int(member.size());i++)
	{
		for(int j=0;j<int(member[i]->Get_n_class());j++)
		{
			checker=0;
			for(int k=0;k<int(tag.size());k++)
			{
				if(tag[k]->Get_Producer_no()==member[i]->Get_Producer_no() &&tag[k]->Get_class_no()==member[i]->Get_class_no(j))
				{
					checker=1;
				}
			}

			if(checker==0)
			{
				ptag=new CPrice_tag;
				ptag->Set_Agent_no(member[i]->Get_Producer_no());
				ptag->Set_Producer_no(member[i]->Get_Producer_no());
				ptag->Set_class_no(member[i]->Get_class_no(j));
				tag.push_back(ptag);
			}
		}
	}
}

template<class T,class U,class V> void CMarket::Buy_money_func(const T& buyer, const U& saler,const V& product,int buyer_no,int saler_no,int product_no)
{
	int buy_money=0;
	int p_gen=0;
	saler[saler_no]->Set_rieki(product[product_no]->Get_price(),product[product_no]->Get_class_no());
	buy_money=product[product_no]->Get_price();
	p_gen=product[product_no]->Get_price_genka();
	saler[saler_no]->Set_shiwake_uriage(i_period,buy_money,p_gen);
	saler[saler_no]->Set_shiwake_yokin_azuke(i_period,buy_money);
	mem_bank[saler[saler_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_money);

	buyer[buyer_no]->Set_shiwake_buy_retailer_product(i_period,buy_money);
	saler[saler_no]->Erase_material();
	mem_buy.push_back(mem_product[product_no]);
}
template<class T,class U> void CMarket::Buy_retailer_product_fixamount(const T& buyer, const U& saler)
{
	double beta=0.1;

	int i,j;
	int taihi;		//銀行に現金を預ける際の数値一時保管変数
	int re_no;		//購買者のナンバー
	int ni;
	int buy_amount;	//購買必要量
	int min_price=0,min_no;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	bool first_product=false;
	bool no_product=true;
	vector <int >buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_phenom_writer(),"buy_producer_switch : 固定製品数購買ルール使用\n");
	for(i=0;i<int(buyer.size());i++)	buy_agent_no.push_back(i);
	for(i=0;i<int(buyer.size());i++)
	{
		//ランダムに購入者を選択　選択された購入者の添え字は以降re_noとなる
		ni=cr->strand(0,buy_agent_no.size()-1);
		re_no=buy_agent_no[ni];
		dl_re=buy_agent_no.begin();
		for(j=0;j<int(buy_agent_no.size());j++)
		{
			if(j==ni)
			{
				dl_re=buy_agent_no.erase(dl_re);
				break;
			}
			dl_re++;
		}

		//ランダム選択終了
		//製品の最高値を記憶（購買時に金がない場合を考慮して）
		for(j=0;j<int(mem_product.size());j++)
		{
			if(j==0)	safty_price=mem_product[j]->Get_price();
			else	
			{
				if(safty_price<mem_product[j]->Get_price())	safty_price=mem_product[j]->Get_price();
			}
		}
		//製品最高値記憶終了
		buy_amount=cpara->GET_PARA_buy_producer_amount();
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());
		buyer[re_no]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());		
		no_product=true;	

		//購買開始
		while(buy_amount>0 && buyer[re_no]->Get_genkin_suitoutyou_zandaka()>safty_price && mem_product.size()>0&&no_product==true)
		{//printf("size %d , no %d\n",mem_product.size(),mem_retailer[re_no]->Get_Agent_no());
			first_product=false;
			for(j=0;j<int(mem_product.size());j++)
			{
				if(first_product==false&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no())
				{
					min_price=mem_product[j]->Get_price();
					min_no=j;
					first_product=true;		//最初にmin_priceを入れるための確認（自分の製品を買わないためj==0は不可）
				}
				else
				{
					if(min_price>mem_product[j]->Get_price()&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no())
					{
						min_price=mem_product[j]->Get_price();
						min_no=j;
					}
				}
			}
			if(first_product==true)	no_product=true;
			else no_product=false;
//			printf("amount:%d , genkin :%d , size:%d\n",buy_amount,mem_retailer[re_no]->Get_genkin_suitoutyou_zandaka(),mem_product.size());
			if(first_product==true)
			{
				del_p=mem_product.begin();
				for(j=0;j<min_no;j++)	del_p++;	

				for(j=0;j<int(saler.size());j++)
				{
					if(mem_product[min_no]->Get_Producer_no()==saler[j]->Get_Producer_no())
					{
						Buy_money_func(buyer,saler,mem_product,re_no,j,min_no);
						mem_product.erase(del_p);
						buy_amount=buy_amount-1;
						break;	
					}
				}
			}
		}//while
		//購買終了
		taihi=buyer[re_no]->Get_genkin_suitoutyou_zandaka();
		buyer[re_no]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	}
	//リテイラ－の購買終了
}
template<class T,class U> void CMarket::Buy_retailer_product_fixamount_fixclass(const T &buyer, const U &saler)
{
	int i,j;
	int taihi;		//銀行に現金を預ける際の数値一時保管変数
	int re_no;		//購買者のナンバー
	int ni;
	int buy_amount;	//購買必要量
	int min_price=0,min_no;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	bool first_product=false;
	bool no_product=true;
	vector <int > buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_phenom_writer(),"buy_producer_switch : 固定製品数購買ルール使用\n");
	for(i=0;i<int(buyer.size());i++)	buy_agent_no.push_back(i);
	for(i=0;i<int(buyer.size());i++)
	{
		//ランダムに購入者を選択　選択された購入者の添え字は以降re_noとなる
		ni=cr->strand(0,buy_agent_no.size()-1);
		re_no=buy_agent_no[ni];
		dl_re=buy_agent_no.begin();
		for(j=0;j<int(buy_agent_no.size());j++)
		{
			if(j==ni)
			{
				dl_re=buy_agent_no.erase(dl_re);
				break;
			}
			dl_re++;
		}
		
		//ランダム選択終了
		//製品の最高値を記憶（購買時に金がない場合を考慮して）
		for(j=0;j<int(mem_product.size());j++)
		{
			if(j==0)	safty_price=mem_product[j]->Get_price();
			else	
			{
				if(safty_price<mem_product[j]->Get_price())	safty_price=mem_product[j]->Get_price();
			}
		}
		//製品最高値記憶終了
		buy_amount=cpara->GET_PARA_buy_producer_amount();
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());
		buyer[re_no]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());		
		no_product=true;	
//		printf("agent_no=%d\n",buyer[re_no]->Get_Agent_no());
		//購買開始
		while(buy_amount>0 && buyer[re_no]->Get_genkin_suitoutyou_zandaka()>safty_price && mem_product.size()>0&&no_product==true)
		{//printf("size %d , no %d\n",mem_product.size(),mem_retailer[re_no]->Get_Agent_no());
			first_product=false;
			for(int k=0;k<buyer[re_no]->Get_class_buy_retailer_data_size();k++)
			{
				for(j=0;j<int(mem_product.size());j++)
				{
					if(first_product==false&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
					{
						min_price=mem_product[j]->Get_price();
						min_no=j;
						first_product=true;		//最初にmin_priceを入れるための確認（自分の製品を買わないためj==0は不可）
					}
					else
					{
						if(min_price>mem_product[j]->Get_price()&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
						{
							min_price=mem_product[j]->Get_price();
							min_no=j;
						}
					}
				}
			}

			if(first_product==true)	
			{no_product=true;}
			else {no_product=false;}

//			printf("agent_no=%d , class=%d\n",mem_product[min_no]->Get_Agent_no(),mem_product[min_no]->Get_class_no());
//			printf("amount:%d , genkin :%d , size:%d\n",buy_amount,mem_retailer[re_no]->Get_genkin_suitoutyou_zandaka(),mem_product.size());
			if(first_product==true)
			{
				del_p=mem_product.begin();
				for(j=0;j<min_no;j++)	del_p++;	

				for(j=0;j<int(saler.size());j++)
				{
//					printf("agent_no=%d\n",saler[j]->Get_Agent_no());
					if(mem_product[min_no]->Get_Producer_no()==saler[j]->Get_Producer_no())
					{
						Buy_money_func(buyer,saler,mem_product,re_no,j,min_no);
						
						mem_product.erase(del_p);
						buy_amount=buy_amount-1;
						break;	
					}
				}
			}
		}//while
		//購買終了
		taihi=buyer[re_no]->Get_genkin_suitoutyou_zandaka();
		buyer[re_no]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	}
		//リテイラ－の購買終了

}

template<class T,class U>void CMarket::Buy_retailer_product_depend_profit_fixclass(const T &buyer, const U &saler)
{
		int i,j;
	int taihi;		//銀行に現金を預ける際の数値一時保管変数
	int re_no;		//購買者のナンバー
	int ni;
//	int buy_amount;	//購買必要量
	int min_price=0,min_no;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	bool first_product=false;
	bool no_product=true;
	int R_koubai_yosan=0;
	vector <int > buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_phenom_writer(),"buy_producer_switch : 固定製品数購買ルール使用\n");
	for(i=0;i<int(buyer.size());i++)	buy_agent_no.push_back(i);
	for(i=0;i<int(buyer.size());i++)
	{
		//ランダムに購入者を選択　選択された購入者の添え字は以降re_noとなる
		ni=cr->strand(0,buy_agent_no.size()-1);
		re_no=buy_agent_no[ni];
		dl_re=buy_agent_no.begin();
		for(j=0;j<int(buy_agent_no.size());j++)
		{
			if(j==ni)
			{
				dl_re=buy_agent_no.erase(dl_re);
				break;
			}
			dl_re++;
		}
		
		//ランダム選択終了
		//製品の最高値を記憶（購買時に金がない場合を考慮して）
		for(j=0;j<int(mem_product.size());j++)
		{
			if(j==0)	safty_price=mem_product[j]->Get_price();
			else	
			{
				if(safty_price<mem_product[j]->Get_price())	safty_price=mem_product[j]->Get_price();
			}
		}
		//製品最高値記憶終了

		//購買基準判定位置
		R_koubai_yosan=buyer[re_no]->Get_R_koubai_yosan();


		//預金引出し処理
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());
		buyer[re_no]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());		

		no_product=true;	
//		printf("agent_no=%d\n",buyer[re_no]->Get_Agent_no());
		//購買開始
		while(R_koubai_yosan>safty_price && buyer[re_no]->Get_genkin_suitoutyou_zandaka()>safty_price && mem_product.size()>0&&no_product==true)
		{//printf("size %d , no %d\n",mem_product.size(),mem_retailer[re_no]->Get_Agent_no());
			first_product=false;
			for(int k=0;k<buyer[re_no]->Get_class_buy_retailer_data_size();k++)
			{
				for(j=0;j<int(mem_product.size());j++)
				{
					if(first_product==false&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
					{
						min_price=mem_product[j]->Get_price();
						min_no=j;
						first_product=true;		//最初にmin_priceを入れるための確認（自分の製品を買わないためj==0は不可）
					}
					else
					{
						if(min_price>mem_product[j]->Get_price()&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
						{
							min_price=mem_product[j]->Get_price();
							min_no=j;
						}
					}
				}
			}

			if(first_product==true)	
			{no_product=true;}
			else {no_product=false;}

//			printf("agent_no=%d , class=%d\n",mem_product[min_no]->Get_Agent_no(),mem_product[min_no]->Get_class_no());
//			printf("amount:%d , genkin :%d , size:%d\n",buy_amount,mem_retailer[re_no]->Get_genkin_suitoutyou_zandaka(),mem_product.size());
			if(first_product==true)
			{
				del_p=mem_product.begin();
				for(j=0;j<min_no;j++)	del_p++;	

				for(j=0;j<int(saler.size());j++)
				{
//					printf("agent_no=%d\n",saler[j]->Get_Agent_no());
					if(mem_product[min_no]->Get_Producer_no()==saler[j]->Get_Producer_no())
					{
						Buy_money_func(buyer,saler,mem_product,re_no,j,min_no);
						
						R_koubai_yosan=R_koubai_yosan-mem_product[min_no]->Get_price();
						mem_product.erase(del_p);
						
						break;	
					}
				}
			}
		}//while
		//購買終了

		taihi=buyer[re_no]->Get_genkin_suitoutyou_zandaka();
		buyer[re_no]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	}
		//リテイラ－の購買終了

}

template<class T,class U> void CMarket::Buy_retailer_product_propemployno(const T &buyer, const U &saler)
{
	double beta=0.1;
	int i,j;
	int taihi;		//銀行に現金を預ける際の数値一時保管変数
	int re_no;		//購買者のナンバー
	int ni;
	int buy_amount;	//購買必要量
	int min_price=0,min_no;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	bool first_product=false;
	bool no_product=true;
	vector <int >buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_phenom_writer(),"buy_producer_switch : 固定製品数購買ルール使用\n");
	for(i=0;i<int(buyer.size());i++)	buy_agent_no.push_back(i);
	for(i=0;i<int(buyer.size());i++)
	{
		//ランダムに購入者を選択　選択された購入者の添え字は以降re_noとなる
		ni=cr->strand(0,buy_agent_no.size()-1);
		re_no=buy_agent_no[ni];
		dl_re=buy_agent_no.begin();
		for(j=0;j<int(buy_agent_no.size());j++)
		{
			if(j==ni)
			{
				dl_re=buy_agent_no.erase(dl_re);
				break;
			}
			dl_re++;
		}

		//ランダム選択終了
		//製品の最高値を記憶（購買時に金がない場合を考慮して）
		for(j=0;j<int(mem_product.size());j++)
		{
			if(j==0)	safty_price=mem_product[j]->Get_price();
			else	
			{
				if(safty_price<mem_product[j]->Get_price())	safty_price=mem_product[j]->Get_price();
			}
		}
		//製品最高値記憶終了
		buy_amount=cpara->GET_PARA_buy_producer_amount()*buyer[i]->Get_no_employ();
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());
		buyer[re_no]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());		
		no_product=true;	

		//購買開始
		while(buy_amount>0 && buyer[re_no]->Get_genkin_suitoutyou_zandaka()>safty_price && mem_product.size()>0&&no_product==true)
		{//printf("size %d , no %d\n",mem_product.size(),mem_retailer[re_no]->Get_Agent_no());
			first_product=false;
			for(j=0;j<int(mem_product.size());j++)
			{
				if(first_product==false&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no())
				{
					min_price=mem_product[j]->Get_price();
					min_no=j;
					first_product=true;		//最初にmin_priceを入れるための確認（自分の製品を買わないためj==0は不可）
				}
				else
				{
					if(min_price>mem_product[j]->Get_price()&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no())
					{
						min_price=mem_product[j]->Get_price();
						min_no=j;
					}
				}
			}

			if(first_product==true)	no_product=true;
			else no_product=false;
//			printf("amount:%d , genkin :%d , size:%d\n",buy_amount,mem_retailer[re_no]->Get_genkin_suitoutyou_zandaka(),mem_product.size());
			if(first_product==true)
			{
				del_p=mem_product.begin();
				for(j=0;j<min_no;j++)	del_p++;
				for(j=0;j<int(saler.size());j++)
				{
					if(mem_product[min_no]->Get_Producer_no()==saler[j]->Get_Producer_no())
					{
						Buy_money_func(buyer,saler,mem_product,re_no,j,min_no);
						mem_product.erase(del_p);
						buy_amount=buy_amount-1;
						break;	
					}
				}
			}
		}//while
		//購買終了
		taihi=buyer[re_no]->Get_genkin_suitoutyou_zandaka();
		buyer[re_no]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	}
	//リテイラ－の購買終了
}

template<class T,class U> void CMarket::Buy_retailer_product_propemployno_fixclass(const T &buyer, const U &saler)
{
	int i,j;
	int taihi;		//銀行に現金を預ける際の数値一時保管変数
	int re_no;		//購買者のナンバー
	int ni;
	int buy_amount;	//購買必要量
	int min_price=0,min_no;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	bool first_product=false;
	bool no_product=true;
	vector <int > buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_phenom_writer(),"buy_producer_switch : 固定製品数購買ルール使用\n");
	for(i=0;i<int(buyer.size());i++)	buy_agent_no.push_back(i);
	for(i=0;i<int(buyer.size());i++)
	{
		//ランダムに購入者を選択　選択された購入者の添え字は以降re_noとなる
		ni=cr->strand(0,buy_agent_no.size()-1);
		re_no=buy_agent_no[ni];
		dl_re=buy_agent_no.begin();
		for(j=0;j<int(buy_agent_no.size());j++)
		{
			if(j==ni)
			{
				dl_re=buy_agent_no.erase(dl_re);
				break;
			}
			dl_re++;
		}
		
		//ランダム選択終了
		//製品の最高値を記憶（購買時に金がない場合を考慮して）
		for(j=0;j<int(mem_product.size());j++)
		{
			if(j==0)	safty_price=mem_product[j]->Get_price();
			else	
			{
				if(safty_price<mem_product[j]->Get_price())	safty_price=mem_product[j]->Get_price();
			}
		}
		//製品最高値記憶終了
		buy_amount=cpara->GET_PARA_buy_producer_amount()*buyer[i]->Get_no_employ();
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());
		buyer[re_no]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());		
		no_product=true;	
		
		//購買開始
		while(buy_amount>0 && buyer[re_no]->Get_genkin_suitoutyou_zandaka()>safty_price && mem_product.size()>0&&no_product==true)
		{//printf("size %d , no %d\n",mem_product.size(),mem_retailer[re_no]->Get_Agent_no());
			first_product=false;
			for(int k=0;k<buyer[re_no]->Get_class_buy_retailer_data_size();k++)
			{
				for(j=0;j<int(mem_product.size());j++)
				{
					if(first_product==false&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
					{
						min_price=mem_product[j]->Get_price();
						min_no=j;
						first_product=true;		//最初にmin_priceを入れるための確認（自分の製品を買わないためj==0は不可）
					}
					else
					{
						if(min_price>mem_product[j]->Get_price()&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
						{
							min_price=mem_product[j]->Get_price();
							min_no=j;
						}
					}
				}
			}

			if(first_product==true)	no_product=true;
			else no_product=false;
//			printf("amount:%d , genkin :%d , size:%d\n",buy_amount,mem_retailer[re_no]->Get_genkin_suitoutyou_zandaka(),mem_product.size());
			if(first_product==true)
			{
				del_p=mem_product.begin();
				for(j=0;j<min_no;j++)	del_p++;	

				for(j=0;j<int(saler.size());j++)
				{
					if(mem_product[min_no]->Get_Producer_no()==saler[j]->Get_Producer_no())
					{
						Buy_money_func(buyer,saler,mem_product,re_no,j,min_no);
						
						mem_product.erase(del_p);
						buy_amount=buy_amount-1;
						break;	
					}
				}
			}
		}//while
		//購買終了
		taihi=buyer[re_no]->Get_genkin_suitoutyou_zandaka();
		buyer[re_no]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	}
		//リテイラ－の購買終了
}

template<class T,class U> void CMarket::Buy_retailer_product_propsellamount(const T &buyer, const U &saler)
{
	double beta=0.1;

	int i,j;
	int taihi;		//銀行に現金を預ける際の数値一時保管変数
	int re_no;		//購買者のナンバー
	int ni;
	int buy_amount;	//購買必要量
	int money;
	int buy_money;
	int min_price=0,min_no;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	bool first_product=false;
	bool no_product=true;
	vector <int >buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_phenom_writer(),"buy_producer_switch : 固定製品数購買ルール使用\n");
	for(i=0;i<buyer.size();i++)	buy_agent_no.push_back(i);
	for(i=0;i<buyer.size();i++)
	{
		//ランダムに購入者を選択　選択された購入者の添え字は以降re_noとなる
		ni=cr->strand(0,buy_agent_no.size()-1);
		re_no=buy_agent_no[ni];
		dl_re=buy_agent_no.begin();
		for(j=0;j<buy_agent_no.size();j++)
		{
			if(j==ni)
			{
				dl_re=buy_agent_no.erase(dl_re);
				break;
			}
			dl_re++;
		}

		//ランダム選択終了
		//製品の最高値を記憶（購買時に金がない場合を考慮して）
		for(j=0;j<mem_product.size();j++)
		{
			if(j==0)	safty_price=mem_product[j]->Get_price();
			else	
			{
				if(safty_price<mem_product[j]->Get_price())	safty_price=mem_product[j]->Get_price();
			}
		}
		//製品最高値記憶終了
		buy_amount=cpara->GET_PARA_buy_producer_amount();
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());
		buyer[re_no]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());		
		no_product=true;	

		//購買開始
		while(buy_amount>0 && buyer[re_no]->Get_genkin_suitoutyou_zandaka()>safty_price && mem_product.size()>0&&no_product==true)
		{//printf("size %d , no %d\n",mem_product.size(),mem_retailer[re_no]->Get_Agent_no());
			first_product=false;
			for(j=0;j<mem_product.size();j++)
			{
				if(first_product==false&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no())
				{
					min_price=mem_product[j]->Get_price();
					min_no=j;
					first_product=true;		//最初にmin_priceを入れるための確認（自分の製品を買わないためj==0は不可）
				}
				else
				{
					if(min_price>mem_product[j]->Get_price()&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no())
					{
						min_price=mem_product[j]->Get_price();
						min_no=j;
					}
				}
			}

			if(first_product==true)	no_product=true;
			else no_product=false;
//			printf("amount:%d , genkin :%d , size:%d\n",buy_amount,mem_retailer[re_no]->Get_genkin_suitoutyou_zandaka(),mem_product.size());
			if(first_product==true)
			{
				del_p=mem_product.begin();
				for(j=0;j<min_no;j++)	del_p++;	

				for(j=0;j<saler.size();j++)
				{
					if(mem_product[min_no]->Get_Producer_no()==saler[j]->Get_Producer_no())
					{
						Buy_money_func(buyer,saler,mem_product,re_no,j,min_no);
						mem_product.erase(del_p);
						buy_amount=buy_amount-1;
						break;	

					}
				}
			}
		}//while
		//購買終了
		taihi=buyer[re_no]->Get_genkin_suitoutyou_zandaka();
		buyer[re_no]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	}
	//リテイラ－の購買終了
}

template<class T,class U> void CMarket::Buy_retailer_product_propsellamount_fixclass(const T &buyer, const U &saler)
{
	int i,j;
	int taihi;		//銀行に現金を預ける際の数値一時保管変数
	int re_no;		//購買者のナンバー
	int ni;
	int buy_amount;	//購買必要量
	int min_price=0,min_no;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	int amount_product=0;
	bool first_product=false;
	bool no_product=true;
	vector <int > buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_phenom_writer(),"buy_producer_switch : 固定製品数購買ルール使用\n");
	for(i=0;i<int(buyer.size());i++)	buy_agent_no.push_back(i);
	for(i=0;i<int(buyer.size());i++)
	{
		//ランダムに購入者を選択　選択された購入者の添え字は以降re_noとなる
		ni=cr->strand(0,buy_agent_no.size()-1);
		re_no=buy_agent_no[ni];
		dl_re=buy_agent_no.begin();
		for(j=0;j<int(buy_agent_no.size());j++)
		{
			if(j==ni)
			{
				dl_re=buy_agent_no.erase(dl_re);
				break;
			}
			dl_re++;
		}
		
		//ランダム選択終了
		//製品の最高値を記憶（購買時に金がない場合を考慮して）
		for(j=0;j<int(mem_product.size());j++)
		{
			if(j==0)	safty_price=mem_product[j]->Get_price();
			else	
			{
				if(safty_price<mem_product[j]->Get_price())	safty_price=mem_product[j]->Get_price();
			}
		}
		//製品最高値記憶終了

		if(buyer[re_no]->Get_Agent_type()==20)	buy_amount=buyer[re_no]->Get_nop_sum()/cpara->GET_PARA_buy_producer_amount();
		if(buyer[re_no]->Get_Agent_type()==30)	buy_amount=buyer[re_no]->Get_nop_sum()/cpara->GET_PARA_buy_producer_amount()/2;
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());
		buyer[re_no]->Set_shiwake_yokin_hikidashi(i_period,buyer[re_no]->Get_yokin_suitoutyou_zandaka());		
		no_product=true;	
		
		//購買開始
		while(buy_amount>0 && buyer[re_no]->Get_genkin_suitoutyou_zandaka()>safty_price && mem_product.size()>0&&no_product==true)
		{//printf("size %d , no %d\n",mem_product.size(),mem_retailer[re_no]->Get_Agent_no());
			first_product=false;
			for(int k=0;k<buyer[re_no]->Get_class_buy_retailer_data_size();k++)
			{
				for(j=0;j<int(mem_product.size());j++)
				{
					if(first_product==false&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
					{
						min_price=mem_product[j]->Get_price();
						min_no=j;
						first_product=true;		//最初にmin_priceを入れるための確認（自分の製品を買わないためj==0は不可）
					}
					else
					{
						if(min_price>mem_product[j]->Get_price()&&mem_product[j]->Get_Producer_no()!=buyer[re_no]->Get_Producer_no()&&buyer[re_no]->Get_buy_retailer_data_class_no(k)==mem_product[j]->Get_class_no())
						{
							min_price=mem_product[j]->Get_price();
							min_no=j;
						}
					}
				}
			}

			if(first_product==true)	no_product=true;
			else no_product=false;
//			printf("amount:%d , genkin :%d , size:%d\n",buy_amount,mem_retailer[re_no]->Get_genkin_suitoutyou_zandaka(),mem_product.size());
			if(first_product==true)
			{
				del_p=mem_product.begin();
				for(j=0;j<min_no;j++)	del_p++;	

				for(j=0;j<int(saler.size());j++)
				{
					if(mem_product[min_no]->Get_Producer_no()==saler[j]->Get_Producer_no())
					{
						Buy_money_func(buyer,saler,mem_product,re_no,j,min_no);
						
						mem_product.erase(del_p);
						buy_amount=buy_amount-1;
						break;	
					}
				}
			}
		}//while
		//購買終了
		taihi=buyer[re_no]->Get_genkin_suitoutyou_zandaka();
		buyer[re_no]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[buyer[re_no]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	}
		//リテイラ－の購買終了
}




void CMarket::Set_FILE_output()
{
	//CMarket内で使用するファイル
	seisan=cpara->FI_Get_seisan();
	out3=cpara->FI_Get_out3();
	employ_FILE=cpara->FI_Get_employ_file();
	test=cpara->FI_Get_test();
	out=cpara->FI_Get_out();
	gyousei_syouhisya=cpara->FI_Get_gyousei_syouhisya();
}

void CMarket::Del_banker_product(int banker_no)
{
	int i,product_checker=0;
	bool checker=false;

	while(checker==false)
	{
		del_p=mem_product.begin();
		for(i=0;i<int(mem_product.size());i++)
		{
			if(mem_product[i]->Get_Agent_no()==banker_no)
			{
				del_p=mem_product.erase(del_p);
				break;
			}
			else	del_p++;
		}
		product_checker=0;
		for(i=0;i<int(mem_product.size());i++)
		{
			if(mem_product[i]->Get_Agent_no()==banker_no)	product_checker++;
		}
		if(product_checker==0)	checker=true;
	}
}

void CMarket::Buy_producer()
{

	double beta=0.1;

	int min_price=0;		//製品購買時の最小価格とベクターでの番号
	int p_gen=0;
	int safty_price=0;	
	bool first_product=false;
	bool no_product=true;
	vector <int >buy_agent_no;
	vector <int >::iterator dl_re;

	fprintf(cpara->FI_Get_market_product()," %d , ",mem_product.size());

	switch(cpara->GET_PARA_buy_producer_switch())
	{
	case 0:
		break;

	case 1:
		Buy_retailer_product_fixamount(mem_retailer,mem_retailer);
		Buy_retailer_product_fixamount(mem_whole,mem_retailer);

		break;

	case 11:
		Buy_retailer_product_fixamount_fixclass(mem_retailer,mem_retailer);
		Buy_retailer_product_fixamount_fixclass(mem_whole,mem_retailer);
		break;

	case 2:
		Buy_retailer_product_propemployno(mem_retailer,mem_retailer);
		Buy_retailer_product_propemployno(mem_whole,mem_retailer);
		break;

	case 12:
		Buy_retailer_product_propemployno_fixclass(mem_retailer,mem_retailer);
		Buy_retailer_product_propemployno_fixclass(mem_whole,mem_retailer);
		break;

	case 3:

		break;

	case 13:
		Buy_retailer_product_propsellamount_fixclass(mem_retailer,mem_retailer);
		Buy_retailer_product_propsellamount_fixclass(mem_whole,mem_retailer);
		break;


	case 4:	//自社の利益に前期利益に依存して製品を購買する

		break;

	case 14:
		Buy_retailer_product_depend_profit_fixclass(mem_retailer,mem_retailer);
		Buy_retailer_product_depend_profit_fixclass(mem_whole,mem_retailer);
		break;


	}

	fprintf(cpara->FI_Get_market_product()," %d\n",mem_product.size());
	
}

void CMarket::Dismiss()
{
	int i;
	vector <int> retailer_no;			//リテイラー番号保管配列
	vector <int> retailer_rieki;		//リテイラー利益保管配列
	vector <int> dummy1;				//ダミーベクター１
	vector <int> dummy2;				//ダミーベクター２
	vector <int> consumer_no;			//失業消費者番号保管配列
	for(i=0;i<int(mem_retailer.size());i++) mem_retailer[i]->Reset_new_worker();	//リテイラーの新規雇用エージェントの記憶及びフラグを初期化

	for(i=0;i<int(mem_retailer.size());i++)			//リテイラーのループ　解雇者がいるかを判定,同時に利益順位のための配列収集
	{
		mem_retailer[i]->Decide_dismisses();	//解雇行動判定
		if(mem_retailer[i]->Get_dismiss_flag()==1)	//解雇であれば解雇者ベクタにエージェントを入れる
		{
			consumer_no.push_back(mem_retailer[i]->Get_dismiss_no());
		}

		retailer_rieki.push_back(mem_retailer[i]->Get_kimatu_riekizyouyo());		//retailerの期末利益剰余取り出し
		retailer_no.push_back(mem_retailer[i]->Get_Agent_no());						//retailerの番号取り出し
	}											//解雇者の取り出し終了
	fprintf(cpara->FI_Get_se_con(),"\n\n");
//	for(i=0;i<retailer_rieki.size();i++)	printf("before no:%d , rieki:%d\n",retailer_no[i],retailer_rieki[i]);

	//期末の利益剰余を昇順にソート
    int  j;
	retailer_no=cf->Sort_NUMvec(retailer_rieki,retailer_no,dummy1,dummy2,0);

	//期末の利益剰余を昇順ソート終了

	int k;
	int l;
	int checker=0;
	for(i=0;i<int(consumer_no.size());i++)
	{
		printf("size no %d , con %d\n",consumer_no.size(),mem_con.size());
		k=cf->Comp_AGEvec_VAR_return_no(mem_con,consumer_no[i]);
		if(cf->Comp_AGEvec_VAR(mem_con,consumer_no[i])==1) fprintf(cpara->FI_Get_employ_file(),"memcon %d , con_no %d , k==%d\n",mem_con[k]->Get_Agent_no(),consumer_no[i],k);
		fprintf(cpara->FI_Get_employ_file(),"re_size %d , co_size %d\n",retailer_no.size(),consumer_no.size());
		checker=0;
		l=0;
	

		for(j=0;j<int(mem_retailer.size());j++)
		{
			fprintf(cpara->FI_Get_employ_file(),"agent_no %d , before %d ,",mem_retailer[j]->Get_Agent_no(),retailer_no[retailer_no.size()-1-i]);
			if(mem_retailer[j]->Get_Agent_no()==retailer_no[retailer_no.size()-1-i])
			{
				fprintf(cpara->FI_Get_employ_file(),"agent_no %d , before %d ,k=%d, ",mem_con[k]->Get_Agent_no(),mem_con[k]->Get_office_no(),k);
				mem_retailer[j]->Set_employ(mem_con[k]->Get_Agent_no());
				mem_retailer[j]->Set_employ_const_wage(mem_con[k]->Get_constant_wage());
				mem_con[k]->Set_office(mem_retailer[j]->Get_Producer_no());
				mem_con[k]->Set_office_type(mem_retailer[j]->Get_Agent_type());
				fprintf(cpara->FI_Get_employ_file()," after %d",mem_con[k]->Get_office_no());
			}
			fprintf(cpara->FI_Get_employ_file(),"\n");
		}

	}
	for(j=0;j<int(mem_retailer.size());j++)	mem_retailer[j]->Calc_sum_const_wage();

	Cobb_Duclas_production_func();

	fprintf(cpara->FI_Get_employ_file(),"\n\n i_period:%d\n",i_period);
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_employ_file(),"agent_no:%d , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_no_employ();j++)	fprintf(cpara->FI_Get_employ_file(),"%d , ",mem_retailer[i]->Get_employer(j));
		fprintf(cpara->FI_Get_employ_file(),"\n");
	}
	consumer_no.clear();
	retailer_no.clear();
	retailer_rieki.clear();
//	for(i=0;i<retailer_rieki.size();i++)	fprintf(cpara->FI_Get_Equipment(),"after no:%d , rieki:%d\n",retailer_rieki[i],retailer_no[i]);
//	fprintf(cpara->FI_Get_Equipment(),"\n");

}

void CMarket::Set_parameter()
{
	
	invest_max=cpara->GET_PARA_invest_max();
	n_class	=	cpara->GET_PARA_n_class();
	nmax_c	=	cpara->GET_PARA_nmax_c();
	nmax_p	=	cpara->GET_PARA_nmax_p();
	income_tax_rate	=	cpara->GET_PARA_income_tax_rate();
	nmax_p_min	=	cpara->GET_PARA_nmax_p_min();
	bonus_rate_min	=	cpara->GET_PARA_bonus_rate_min();
	bonus_rate_max	=	cpara->GET_PARA_bonus_rate_max();
	bonus_rate_min_e=	cpara->GET_PARA_bonus_rate_min_e();
	bonus_rate_max_e=	cpara->GET_PARA_bonus_rate_max_e();
	nbonus	=	cpara->GET_PARA_nbonus();
	nbank_con=cpara->GET_PARA_nbank_con();
	Adjustment_Sensitivity	=	cpara->GET_PARA_Adjustment_Sensitivity();	
	capa_increase_rate	=	cpara->GET_PARA_capa_increase_rate();
	first_price	=	cpara->GET_PARA_first_price();
	invest_money	=	cpara->GET_PARA_invest_money();
	max_price_m	=	cpara->GET_PARA_max_price_m();
	max_price_p	=	cpara->GET_PARA_max_price_p();
	max_q_re	=	cpara->GET_PARA_max_q_re();
	max_with_drawal_rate	=	cpara->GET_PARA_max_with_drawal_rate();
	min_price_m	=	cpara->GET_PARA_min_price_m();
	min_price_p	=	cpara->GET_PARA_min_price_p();
	min_q_init	=	cpara->GET_PARA_min_q_init();
	min_q_limit	=	cpara->GET_PARA_min_q_limit();
	min_q_re	=	cpara->GET_PARA_min_q_re();
	min_with_drawal_rate	=	cpara->GET_PARA_min_with_drawal_rate();
	price_increase_rate	=	cpara->GET_PARA_price_increase_rate();
	price_k	=	cpara->GET_PARA_price_k();
	q_limit_k	=	cpara->GET_PARA_q_limit_k();
	repay_time_ave	=	cpara->GET_PARA_repay_time_ave();
	repay_time_bun	=	cpara->GET_PARA_repay_time_bun();
	nkessan=cpara->GET_PARA_nkessan();
	
//	gov_invest_ratio=cpara->GET_PARA_gov_invest_ratio();
//	hosyou_ratio=cpara->GET_PARA_hosyou_ratio();
//	yugu_ratio=cpara->GET_PARA_yugu_ratio();
//	kigyou_hozyokin_ratio=cpara->GET_PARA_kigyou_hozyokin_ratio();
//	g_koubai_ratio=cpara->GET_PARA_g_koubai_ratio();
	
}
void CMarket::Bankruptcy_recreate()
{
	printf("banker_check\n");
	int i,j;
	int size,size_c,size_con,size_b;
	int bankr;//,i_first;
	int mo=0;	int nc;
	int loan_s,loan_l,genkin,yokin;
	int loan_s_shi;
	int bankruptcy_count=0;
	int newave_price=0;
	int genshi;
	if(i_period!=0)
	{
//		for(i=0;i<mem_class_statics.size();i++)	newave_price+=mem_class_statics[i]->Get_ave_price();
//		newave_price=newave_price/mem_class_statics.size();
		newave_price=first_price;
	}
	vector <int> risyoku;
	vector<int> ::iterator del_c;
	vector <CRetailer *>::iterator del_pr;
	size=mem_retailer.size();
	size_con=mem_con.size();
	size_b=mem_bank.size();
//restart:
	size=mem_retailer.size();
	del_pr=mem_retailer.begin();
	for(i=0;i<size;i++)
	{
		bankr=mem_retailer[i]->Get_bankr_p();//借入時の倒産し数（現在未使用）

		mem_retailer[i]->bankr(cpara->GET_PARA_max_ban());//廃業処理、売れていない製品を検索して売れていなければ倒産
		nc=mem_retailer[i]->Get_ncr_p();//現在の生産クラスの確認、これが0ならば倒産処理開始		
//		printf("r=%d agent_no=%d size_r=%d bp=%d los=%d lol=%d\n",i,mem_retailer[i]->Get_Agent_no(),size,bankr,mem_retailer[i]->Get_loan_s_zandaka(),mem_retailer[i]->Get_loan_l_zandaka());
		if(nc==0)
		{
				size_c=mem_retailer[i]->Get_no_employ();		//雇用しているエージェント数の取得
				loan_s=mem_retailer[i]->Get_loan_s_zandaka();	//短期借入残高取得
				loan_l=mem_retailer[i]->Get_loan_l_zandaka();	//長期借入残高取得
				printf("=========Bankr=========== r=%d agent=%d yo=%d los=%d lol=%d\n",i,mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_yokin_suitoutyou_zandaka(),loan_s,loan_l);
				genkin=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();//現金残高の取得
				mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,genkin);//現金を預金に編入（銀行側処理）
				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,genkin);//現金処理の仕分け（銀行側）
				yokin=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();//預金を全額引き出し


				if(loan_s<=yokin)	//短期借入が預金より大きければ短期借入を返済する
				{
					mem_retailer[i]->Set_loan_s(-loan_s);//返済処理
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s);	//短期借入残高減算
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,loan_s,0);	//短期借入の返済仕訳処理
					mem_retailer[i]->Set_shiwake_s_hensai(i_period,loan_s);			//短期借入の返済処理
//					printf("bankr : loan_s<=yokin : loan_s=%d yokin=%d\n",loan_s,mem_retailer[i]->Get_yokin_suitoutyou_zandaka());
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(loan_s);	//～おそらく返済残高
					loan_s_shi=0;													//～～不明
					genshi=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();		//～おそらく返済原資、残額を編入
				}
				else		//短期借り入れだけでは返済できない場合
				{//loan_s>yokin
					genshi=0;													//～おそらく返済原資
					mem_retailer[i]->Set_shiwake_s_hensai(i_period,yokin);			//預金残額分だけ返済仕訳（企業側）
					mem_retailer[i]->Set_loan_s(-yokin);							//短期借入残高処理（企業側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-yokin);	//預金分だけ短期借入返済借入残高処理（銀行側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,yokin,0);//預金分だけ短期借入返済仕訳処理（銀行側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(yokin);
					loan_s_shi=loan_s-yokin;										//短期借入の残額
				}

				if(genshi>0)	//短期借入返済後に残預金があるのであれば長期返済
				{
					if(loan_l-genshi>0)//長期借入が多い場合は残額全額返却
					{
						mem_retailer[i]->Set_loan_l(-genshi);		//長期借入の返済
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-genshi);	//長期借入返済処理
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,genshi,0);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(genshi);	//長期借入返済処理
						mem_retailer[i]->Set_shiwake_l_hensai(i_period,genshi);		//長期借入返済処理（仕分け）
						loan_l=loan_l-genshi;
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
					}
					else//長期借入が残預金より少ない場合は返済後に残金ばらまき（暫定で企業に配布）
					{
						mem_retailer[i]->Set_loan_l(-genshi);		//長期借入の返済
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-genshi);	//長期借入返済処理
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,genshi,0);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(genshi);	//長期借入返済処理
						mem_retailer[i]->Set_shiwake_l_hensai(i_period,genshi);		//長期借入返済処理（仕分け）
						loan_l=0;
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
						genshi=genshi-loan_l;
						int test_pay=genshi/mem_retailer.size();			

						for(int fx=0;fx<int(mem_retailer.size());fx++)
						{
							mem_retailer[fx]->Set_shiwake_hozyokin(i_period,test_pay);
						}
					}
				}
				else//残金一切なしの場合の処理
				{
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
				}

				//不良債権分を保管するかどうか
	//			cb->banker_l(mem_retailer,mem_retailer[i]->Get_Producer_no());
				for(j=0;j<size_c;j++)
				{
					risyoku.push_back(mem_retailer[i]->Get_employer(j));
				}
				fprintf(test,"pn=%d\n",mem_retailer[i]->Get_Producer_no());
				
				mem_bank[mem_retailer[i]->Get_bank_no()]->renew_stock_price_banker(mem_product,mem_retailer[i]->Get_Producer_no());
				mem_retailer.erase(del_pr);

/*
				////////////倒産企業の代わりに補充

					int i,depo;	int shihon;
					int size_b; int re_size;
					re_size=mem_retailer.size();
					size_b=mem_bank.size();
					Agent_no++;
					re=new CRetailer(profit_under_line,syotokuzei_ratio,houzinzei_ratio);
					re->Set_IC(max_e_flag,max_equip_end);
					re->set_balance_IC();
					re->Set_file(retai);
					re->Set_Agent_no(Agent_no);
					re->Set_Agent_type(20);
					re->Set_Producer_no(Agent_no);
					re->Set_Producer_type(20);
					re->Set_randum(cr);
					re->Set_out(out);
					re->Set_out3(shiwake,out3,out3_csv,loan);//file
					re->Set_test(test);
					re->Set_seihin_price(seihin_price);
					re->Set_employ_file(employ_FILE);
					re->Set_n_class(n_class);
//					re->Def_hendouhi(min_hendouhi,max_hendouhi);
					re->Def_koteihi(min_koteihi,max_koteihi);
					re->Set_depo_rate(depo_rate_p);
					re->Set_bank_no(cr->strand(0,size_b-1));
					re->Set_ncr_p(cr->strand(nmax_p_min,nmax_p));
					re->Set_ncr_p(2);
					re->Create_Product_class_p(max_memo_time,max_reac_flag);
				/*	if(re->Get_Agent_no()==24 || re->Get_Agent_no()==8)
					{
						re->Set_nkessan(nkessan);
						re->Set_ncase(ncase);
					}
					else{
						re->Set_nkessan(2);
						re->Set_ncase(2);
					}*/
/*					re->Set_nkessan(0);
					re->Set_ncase(0);

					re->Set_seisan_FILE(seisan,eqw);
					depo=cr->strand(min_init_depo_r,max_init_depo_r);
					shihon=depo+(depo/10);
					re->Set_kisyu_shihon(shihon);
					re->Set_kisyu_mibarai(0);
					re->Set_kisyu_seihin(0);
					re->Set_kisyu_genkin(depo/10);
					re->Set_kisyu_yokin(depo);
					re->Set_kisyu_zandaka();
					re->Set_bonus(0);
					re->Set_bankr_p(0);
					re->Set_buy_p(0);
					re->Set_F_show_tax(show_tax_file);
					mem_retailer.push_back(re);
					mem_retailer[re_size]->Set_genkin(depo/10);
					mem_retailer[re_size]->Set_yokin(depo);
					mem_bank[mem_retailer[re_size]->Get_bank_no()]->Set_yokin(depo);
					mem_retailer[re_size]->Set_shiwake_shihon(i_period,depo/10,depo);
					mem_bank[mem_retailer[re_size]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);

					//生産数、製品種等、割り付け
					mem_retailer[re_size]->Set_qmaxmax(static_qmax(),static_qmax()/2,static_qmax());//qmaxmax,qmaxmin,min_q_init);//生産限界の決定
					mem_retailer[re_size]->Set_class_no_p(mem_ncr_r);//ncr_p個の製品種別インスタンスに製品種別番号を割りつける
					mem_retailer[re_size]->Set_material_no(mem_ncr_w);//製品種別毎にmem_ncr_wの中から原料を１つ指定する。
					printf("banker_check1\n");
					mem_retailer[re_size]->Set_market_buy_renew(static_qmax()/2);
					//mem_retailer[re_size]->Set_total_constant_wage(0);

					printf("banker_check2\n");
					init_r.push_back(mem_retailer[re_size]->Get_Producer_no());

					///////////////補充した企業へ消費者再就職

					size_c=risyoku.size();
					size_rwe=mem_whole.size()+mem_retailer.size()+mem_equip.size();
					size_we=mem_whole.size()+mem_equip.size();
					ri_count=0;
					for(int ii=0;ii<risyoku.size();ii++)
					{
						del_c=risyoku.begin();

						for(int jj=0;jj<size_con;jj++)
						{
							if(risyoku[ii]==mem_con[jj]->Get_Consumer_no())
							{
								ri_count=ri_count-size_we;
								mem_retailer[re_size]->Set_employ(mem_con[jj]->Get_Consumer_no());
								mem_retailer[re_size]->Set_employ_const_wage(mem_con[jj]->Get_constant_wage());
								mem_retailer[re_size]->Set_total_constant_wage(mem_retailer[re_size]->Get_constant_wage()+mem_con[jj]->Get_constant_wage());
								printf("consutwageeeeeeeeeeeeeeeeeeeeeeeee , %d\n",mem_con[jj]->Get_constant_wage());
					printf("check1\n");			mem_retailer[re_size]->Set_total_price_genka(mem_retailer[re_size]->Get_total_price_genka()+mem_con[jj]->Get_constant_wage());
					printf("check2\n");			mem_con[jj]->Set_office(mem_retailer[re_size]->Get_Producer_no());
					printf("check3\n");			mem_con[jj]->Set_office_type(mem_retailer[re_size]->Get_Agent_type());
					printf("check4\n");			risyoku.erase(del_c);
								printf("koyou hitori syuuryou\n");
							}
						}
					}
					printf("koyou syuuryou\n");
					mem_retailer[re_size]->Show_employ();
					printf("test\n");
					
					mem_retailer[re_size]->Set_total_price_genka(mem_retailer[re_size]->Get_constant_wage());
					mem_retailer[re_size]->Re_set_price(newave_price);
					printf("tousansyuuryou\n");

			goto restart;
			*/
		}
		del_pr++;
		
	}
	
}

void CMarket::Set_init_equipment_revel()
{
	int i,j;
	for(i=0;i<int(mem_retailer.size());i++)
	{
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			mem_retailer[i]->Set_init_equipment_revel(j);
		}
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		for(j=0;j<mem_whole[i]->Get_n_class();j++)
		{
			mem_whole[i]->Set_init_equipment_revel(j);
		}
	}

	fprintf(cpara->FI_Get_phenom_writer(),"\n初期設備のレベルの記述\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"retailer_no=%d: , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d ,  %d ,",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_equipment_revel(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"whole_no=%d: , ",mem_whole[i]->Get_Agent_no());
		for(j=0;j<mem_whole[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d ,  %d ,",mem_whole[i]->Get_class_no(j),mem_whole[i]->Get_equipment_revel(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}

}
void CMarket::Cobb_Duclas_production_func()
{
	int i,j;
	int size_r;
	int n_class;
	int q_limit;
	int L,C;
	float k1=0.25,k2=0.75;
	int q_lim_sum=0;
	int q_lim_sum_w=0;
	double b;

	size_r=mem_retailer.size();
	for(i=0;i<size_r;i++)
	{
//		b=9.16;
		n_class=mem_retailer[i]->Get_n_class();
		for(j=0;j<n_class;j++)
		{
			b=mem_retailer[i]->Get_cobb_k(j);
			L=mem_retailer[i]->Get_equipment_revel(j);
			C=mem_retailer[i]->Get_no_employ();
			q_limit=(int)(b*pow((float)L,k1)*pow((float)C,k2));
//			q_limit=(int)(b*L*pow((float)4,k2));				//4のk2乗*A*L
/*			if(mem_retailer[i]->Get_equipment_revel(j)==1)
			{
				q_limit_2=(int)(3*b*L);
			}else{
				q_limit_2=(int)(3*b*(L+L*0.5));
			}*/
	//		printf("q1=%d q2=%d \n",q_limit,q_limit_2);
			mem_retailer[i]->Set_q_limit(q_limit,j,min_q_limit);
			mem_retailer[i]->Adjust_q_init(j);
			mem_retailer[i]->Adjust_q_init(j);
			q_lim_sum+=q_limit;
		}
	}

	for(i=0;i<int(mem_whole.size());i++)
	{
	//	b=80;
		n_class=mem_whole[i]->Get_n_class();
		for(j=0;j<n_class;j++)
		{
			b=mem_whole[i]->Get_cobb_k(j);
			L=mem_whole[i]->Get_equipment_revel(j);
			C=mem_whole[i]->Get_no_employ();
			q_limit=(int)(b*pow((float)L,k1)*pow((float)C,k2));
			mem_whole[i]->Set_q_limit(q_limit,j,min_q_limit);
			mem_whole[i]->Adjust_q_init(j);
			mem_whole[i]->Adjust_q_init(j);
			q_lim_sum_w+=q_limit;
//			printf(" %d\n",q_limit);

		}
	}

	fprintf(cpara->FI_Get_Equipment(),"q_lim_r=%d , q_lim_w=%d\n",q_lim_sum,q_lim_sum_w);

	fprintf(cpara->FI_Get_phenom_writer(),"\n%d生産能力限界\n",i_period);
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"retailer_no=%d: , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d ,  %d ,",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_class_q_limit(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"whole_no=%d: , ",mem_whole[i]->Get_Agent_no());
		for(j=0;j<mem_whole[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d ,  %d ,",mem_whole[i]->Get_class_no(j),mem_whole[i]->Get_class_q_limit(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
}

void CMarket::Sort_income()
{
	vector<int >dummy1;
	vector<int >dummy2;

	sort_static_kyuyo=cf->Sort_NUMvec(statistics_income,sort_static_kyuyo,dummy1,dummy2,0);

//	for(i=0;i<statistics_income.size();i++)	fprintf(Equipment,"%d , %d\n",sort_static_kyuyo[i],statistics_income[i]);

}
void CMarket::Hosyou_shouhisya_kouhukin()
{
	int i,j;
	int yugu_kouhukin;
	int sum_yugu_yosan;
	int kouhu_size=int(sort_static_kyuyo.size()*0.1);//0.05;
	int new_income;
	int check_yosan=0;
	int dumy;

	sum_yugu_yosan=cg->Get_yugu_yosan();
	yugu_kouhukin=sum_yugu_yosan/kouhu_size;
	
//	fprintf(Equipment,"kouhumae\n");
	for(i=0;i<int(statistics_income.size());i++)	fprintf(cpara->FI_Get_Equipment(),"%d , %d\n",sort_static_kyuyo[i],statistics_income[i]);
	fprintf(cpara->FI_Get_Equipment(),"\nkouhu\n\n");
	for(i=0;i<kouhu_size;i++)
	{
//		fprintf(Equipment,"static_no , %d\n",sort_static_kyuyo[i]);
		for(j=0;j<int(mem_con.size());j++)
		{
			if(mem_con[j]->Get_Agent_no()==sort_static_kyuyo[i])
			{
				new_income=yugu_kouhukin;
	//			mem_con[i]->Renew_income(new_income);
	//			printf("\n\nhosyou=  %d , new_income= %d , depo=%d\n\n",hosyou,new_income,depo);
				mem_con[i]->Set_shiwake_syouhisya_kouhukin(i_period,new_income);
//				mem_con[i]->Set_genkin(new_income);//+new_income3
//				statistics_kyuyo.push_back(new_income);
//				kyuyo_no.push_back(mem_con[i]->Get_Agent_no());
				cg->Set_shiwake_syouhisya_kouhukin(i_period,yugu_kouhukin);
				check_yosan+=yugu_kouhukin;
//				cg->Set_genkin(-yugu_kouhukin);
				
				fprintf(cpara->FI_Get_Equipment(),"yuugu= , %d , no= , %d\n",yugu_kouhukin,mem_con[j]->Get_Agent_no());
			}
		}
	}
//	printf("sumuyugu=%d , check_yosan=%d\n ",sum_yugu_yosan,check_yosan);

	if(check_yosan>sum_yugu_yosan || check_yosan<sum_yugu_yosan-100)	//割り切れない場合の誤差を考えて100前後より値が異なる場合に記述
	{
		printf("ERROR CODE CMarket::shouhisya_kouhukin()  予算額と実際に支払った額が異なります");
		scanf_s("%d",&dumy);
	}

	fprintf(gyousei_syouhisya,"%d , ",check_yosan);

}
void CMarket::Yugu_shouhisya_kouhukin()
{
	int i,j;
	int yugu_kouhukin;
	int sum_yugu_yosan;
	int kouhu_size=int(sort_static_kyuyo.size()*0.1);//0.05;
	int new_income;
	int check_yosan=0;
	int dumy;

	sum_yugu_yosan=cg->Get_yugu_yosan();
	yugu_kouhukin=sum_yugu_yosan/kouhu_size;
	
//	fprintf(Equipment,"kouhumae\n");
//	for(i=0;i<statistics_income.size();i++)	fprintf(cpara->FI_Get_Equipment(),"%d , %d\n",sort_static_kyuyo[i],statistics_income[i]);
//	fprintf(Equipment,"\nkouhu\n\n");
	for(i=int(sort_static_kyuyo.size())-1;i>int(sort_static_kyuyo.size())-kouhu_size-1;i--)
	{
//		fprintf(Equipment,"static_no , %d\n",sort_static_kyuyo[i]);
		for(j=0;j<int(mem_con.size());j++)
		{
			if(mem_con[j]->Get_Agent_no()==sort_static_kyuyo[i])
			{
				new_income=yugu_kouhukin;
	//			mem_con[i]->Renew_income(new_income);
	//			printf("\n\nhosyou=  %d , new_income= %d , depo=%d\n\n",hosyou,new_income,depo);
				mem_con[i]->Set_shiwake_syouhisya_kouhukin(i_period,new_income);
//				mem_con[i]->Set_genkin(new_income);//+new_income3
//				statistics_kyuyo.push_back(new_income);
//				kyuyo_no.push_back(mem_con[i]->Get_Agent_no());
				cg->Set_shiwake_syouhisya_kouhukin(i_period,yugu_kouhukin);
				check_yosan+=yugu_kouhukin;
//				cg->Set_genkin(-yugu_kouhukin);
				
//				fprintf(cpara->FI_Get_Equipment(),"yuugu= , %d , no= , %d\n",yugu_kouhukin,mem_con[j]->Get_Agent_no());
			}
		}
	}
//	printf("sumuyugu=%d , check_yosan=%d\n ",sum_yugu_yosan,check_yosan);

	if(check_yosan>sum_yugu_yosan || check_yosan<sum_yugu_yosan-100)	//割り切れない場合の誤差を考えて100前後より値が異なる場合に記述
	{
		printf("ERROR CODE CMarket::shouhisya_kouhukin()  予算額と実際に支払った額が異なります");
		scanf_s("%d",&dumy);
	}

	fprintf(gyousei_syouhisya,"%d , ",check_yosan);
}

void CMarket::Deposit_consumer()
{
	int i;
	int depo;
	int previous_income;
	int sum_depo=0;
	int sum_inco=0;
	int depo_ratio=0;

		//fprintf(cpara->FI_Get_CR_product_relation(),"%d , ",i_period);
	//for(i=0;i<int(mem_con.size());i++)	
	//	{
	//		fprintf(cpara->FI_Get_CR_product_relation(),"%d , ",mem_con[i]->Get_genkin_suitoutyou_zandaka());
	//		sum+=mem_con[i]->Get_genkin_suitoutyou_zandaka();
	//	}

	//fprintf(cpara->FI_Get_CR_product_relation(),"%d\n",sum);

	for(i=0;i<int(mem_con.size());i++)
	{
//		fprintf(Consumer,"%d\n",mem_con[i]->Get_kyuyo_c_out());
		//預金額計算　前期の給料の値をアカウントから持ってくる
		previous_income=mem_con[i]->Get_kyuyo_c_out()-mem_con[i]->Get_tax()+mem_con[i]->Get_kouhukin_out();

		sum_inco+=previous_income;
		mem_con[i]->Set_depo_rate_new3(previous_income);
		depo=int(previous_income*mem_con[i]->Get_depo_rate());
		sum_depo+=depo;
		
		fprintf(cpara->FI_Get_CR_product_relation(),"inco:%d depo:%d, ",previous_income,depo);
//		printf("%lf , depo=%d\n",mem_con[i]->Get_depo_rate() , depo);
//		printf("depo=%d  , depo_rate=%d\n",depo,mem_con[i]->Get_depo_rate());

		//預金処理
		mem_con[i]->Set_shiwake_azuke(i_period,depo);	//預金預け入れ仕分け 消費者
		mem_bank[mem_con[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);//預金預け入れ仕分け　銀行		
	}fprintf(cpara->FI_Get_CR_product_relation(),"suminco:%d , sumdepo:%d\n",sum_inco,sum_depo);
//	fprintf(bank_data,"預金率= , %d , %d\n",sum_depo,sum_inco);
}

void CMarket::Gav_yosan()
{
	int g_money=0,hosyou=0,toushi=0,hozyokin=0,kyuyo=0,yugu=0,koubai=0;
	int s_size=0;
	int kyuyo_yosan=0,kari_kyuyo=0;
	g_money=cg->Get_genkin_suitoutyou_zandaka();
	printf("g_money=%d\n",g_money);
	for(int i=0;i<int(mem_con.size());i++)
	{
		if(mem_con[i]->Get_office_type()==0)	s_size++;
	}

	if(cg->Get_no_employ()>0)		//公務員がいる場合に給与計算
	{
		kyuyo_yosan=int(cg->Get_genkin_suitoutyou_zandaka()*cpara->GET_PARA_wage_yosan_rate());		//給与に使える限度額を計算
		kari_kyuyo=kyuyo_yosan/cg->Get_no_employ();			//仮の一人当たり給与額算定

		if(kari_kyuyo>cg->Get_ave_inc()*cpara->GET_PARA_gav_wage_rate())					//仮の一人当たり給与予算が民間平均より大きい場合
		{
			kyuyo=int(cg->Get_ave_inc()*cg->Get_no_employ()*cpara->GET_PARA_gav_wage_rate());	//民間と同じ額
		}
		else												//仮の一人当たり給与予算が民間平均より小さい場合は予算内で行う
		{
			kyuyo=kyuyo_yosan;
		}
	}
	g_money=g_money-kyuyo;


/*

//	printf("get_ave_inc   =%d\n",cg->Get_ave_inc());
	printf("situgyousya_no %d\n",s_size);
	kyuyo=cg->Get_ave_inc()*cg->Get_no_employ();
	hosyou=(cg->Get_ave_inc()/2)*s_size;		//失業保障金　平均給与の2分の1（これが給付金）×人数分
	printf("ave=%d , kyuyo=%d , hosyou=%d\n",cg->Get_ave_inc(),kyuyo,hosyou);
//	hosyou=0;	//失業補なし償用	

	g_money=g_money-(kyuyo+hosyou);

	printf("ggggggggggggggggmooooooooooooooone  %d\n",g_money);
	if(g_money<0)
	{
		if(s_size>0)
		{
			kyuyo=cg->Get_genkin_suitoutyou_zandaka()*2/3;
			hosyou=cg->Get_genkin_suitoutyou_zandaka()*1/3;
		}
		else  kyuyo=cg->Get_genkin_suitoutyou_zandaka();
			
//		hosyou=0;	//失業補なし償用
		g_money=cg->Get_genkin_suitoutyou_zandaka()-(kyuyo+hosyou);
	}
	*/


//	hosyou=g_money*hosyou_ratio;		//外部入力の割合で保障金決定



	toushi=int(g_money*cpara->GET_PARA_gov_invest_ratio());	//外部入力の割合で投資金決定
	yugu=int(g_money*cpara->GET_PARA_yugu_ratio());			//外部入力の割合で金持ち優遇金決定
	hozyokin=int(g_money*cpara->GET_PARA_kigyou_hozyokin_ratio());	//保障、投資が割合で差し引かれたあとの金が補助金
	koubai=int(g_money*cpara->GET_PARA_g_koubai_ratio());

	fprintf(cpara->FI_Get_Delta_G_writing(),"delta_G %d , delta_g_starat %d , delta_g_end %d\n",cpara->Get_Para_delta_G(),cpara->Get_para_delta_period_start(),cpara->Get_para_delta_period_end());
	if(i_period>=cpara->Get_para_delta_period_start() && i_period<cpara->Get_para_delta_period_start()+cpara->Get_para_delta_period_end())
	{
		fprintf(cpara->FI_Get_Delta_G_writing()," ,  , %d period,  koubai,%d , hozyokin, %d, delta_G , %d\n",i_period,koubai,hozyokin,cpara->Get_Para_delta_G());
		hozyokin+=cpara->Get_Para_delta_G()*cpara->Get_para_DeltaSubsidyRatio();
		koubai+=cpara->Get_Para_delta_G()*cpara->Get_para_DeltaSubsidyRatio();
		fprintf(cpara->FI_Get_Delta_G_writing()," ,  ,   , koubai,%d , hozyokin , %d\n",koubai,hozyokin);
	}
	fprintf(gyousei_syouhisya,"%d , %d , %d , %d , %d , %d , %d , ",kyuyo,g_money+hosyou,hosyou,toushi,yugu,hozyokin,koubai);
	cg->Set_hosyou_yosan(hosyou);
	cg->Set_kyuyo_yosan(kyuyo);
	cg->Set_toushi_yosan(toushi);
	cg->Set_yugu_yosan(yugu);
	cg->Set_hozyokin_yosan(hozyokin);
	cg->Set_koubai_yosan(koubai);
	

	fprintf(cpara->FI_Get_phenom_writer(),"\n%d期 政府予算 , 給与予算 , 政策予算 , 失業補償予算 , 政府投資予算 , 優遇予算 , 企業補助金予算 , 購買予算\n",i_period);
	fprintf(cpara->FI_Get_phenom_writer()," , %d , %d , %d , %d , %d , %d , %d , ",kyuyo,g_money+hosyou,hosyou,toushi,yugu,hozyokin,koubai);
}

void CMarket::Hozyokin_kouhu()
{
	int i;
	int size;
	int g_money;
	int kouhukin;
	size=mem_retailer.size()+mem_whole.size()+mem_equip.size();
	g_money=cg->Get_hozyokin_yosan();
	
//	cg->Set_genkin(-g_money);
	kouhukin=g_money/size;

	for(i=0;i<int(mem_retailer.size());i++)
	{
		mem_retailer[i]->Set_shiwake_hozyokin(i_period,kouhukin);
		mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
		cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
//		mem_retailer[i]->Set_yokin(kouhukin);
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		mem_whole[i]->Set_shiwake_hozyokin(i_period,kouhukin);
		mem_whole[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
		mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
		cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
//		mem_whole[i]->Set_yokin(kouhukin);
	}
	for(i=0;i<int(mem_equip.size());i++)
	{
		mem_equip[i]->Set_shiwake_hozyokin(i_period,kouhukin);
		mem_equip[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
		mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
		cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
//		mem_equip[i]->Set_yokin(kouhukin);
	}

	fprintf(gyousei_syouhisya,"%d , %d\n",g_money , cg->Get_genkin_suitoutyou_zandaka());
		//mem_retailer[i]->Set_genkin(kouhukin);

}

void CMarket::Labor_Hozyokin_kouhu_zyoui()
{
	int i,j;
	int size;
	int g_money;
	int kouhukin=0;
	int sum_uriage=0;
	int zisseki=0;
	double zyoui_rate=0.25;
	
	vector<int > pro_no;
	vector<int > uriage;
	vector<int > dummy1;
	vector<int > dummy2;

//	int kouhu=0;
	size=mem_retailer.size()+mem_whole.size()+mem_equip.size();
	g_money=cg->Get_hozyokin_yosan();
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"yosan , %d , ",g_money);
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"retailer , ");
	for(i=0;i<int(mem_retailer.size());i++) 
	{
		pro_no.push_back(mem_retailer[i]->Get_Agent_no());
		uriage.push_back(mem_retailer[i]->Get_uriage_out());
		sum_uriage+=mem_retailer[i]->Get_uriage_out();
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",mem_retailer[i]->Get_uriage_out());
	}
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"whole , ");
	for(i=0;i<int(mem_whole.size());i++) 
	{
		pro_no.push_back(mem_whole[i]->Get_Agent_no());
		uriage.push_back(mem_whole[i]->Get_uriage_out());
		sum_uriage+=mem_whole[i]->Get_ukerisi_out();
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",mem_whole[i]->Get_uriage_out());
	}
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"equip , ");
	for(i=0;i<int(mem_equip.size());i++)
	{
		pro_no.push_back(mem_equip[i]->Get_Agent_no());
		uriage.push_back(mem_equip[i]->Get_uriage_out());
		sum_uriage+=mem_equip[i]->Get_uriage_out();
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",mem_equip[i]->Get_uriage_out());
	}
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"sum_uriage , %d , ",sum_uriage);


//	for(i=0;i<int(uriage.size());i++) fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"uriage , %d , pro_no , %d\n",uriage[i],pro_no[i]);
//	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"\n");
	pro_no=cf->Sort_NUMvec(uriage,pro_no,dummy1,dummy2,1);
	dummy1.clear();
	uriage=cf->Sort_NUMvec(uriage,dummy1,1);
//	for(i=0;i<int(uriage.size());i++) fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"uriage , %d , pro_no , %d\n",uriage[i],pro_no[i]);

	if(sum_uriage>0)
	{
		sum_uriage=0;
		for(i=0;i<int(double(uriage.size())*zyoui_rate-1);i++)	sum_uriage+=uriage[i];	//0からスタートするため4分の1の数字マイナス1する
//		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"\nsize=%d , sum_uriage=%d\n",int(double(uriage.size())*0.25),sum_uriage);

		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"kouhukin , ");
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"retailer , ");
		for(i=0;i<int(mem_retailer.size());i++)
		{
			kouhukin=0;
			for(j=0;j<int(double(uriage.size())*zyoui_rate-1);j++)
			{
				if(pro_no[j]==mem_retailer[i]->Get_Agent_no())
				{
					kouhukin=int(double(g_money)*(double(mem_retailer[i]->Get_uriage_out())/double(sum_uriage)));
					
//					fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"g_money %d , sumuriage %d , uriage %d\n",g_money , sum_uriage,mem_retailer[i]->Get_uriage_out());
//					fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"pro_no %d , kouhukin %d\n",mem_retailer[i]->Get_Agent_no(),kouhukin);
					mem_retailer[i]->Set_shiwake_hozyokin(i_period,kouhukin);
					mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
					cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
					zisseki+=kouhukin;
				}
			}
			fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"whole , ");
		for(i=0;i<int(mem_whole.size());i++)
		{
			kouhukin=0;
			for(j=0;j<int(double(uriage.size())*zyoui_rate-1);j++)
			{
				if(pro_no[j]==mem_whole[i]->Get_Agent_no())
				{
					kouhukin=int(double(g_money)*(double(mem_whole[i]->Get_uriage_out())/double(sum_uriage)));
					
					mem_whole[i]->Set_shiwake_hozyokin(i_period,kouhukin);
					mem_whole[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
					mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
					cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
					zisseki+=kouhukin;
				}
			}
			fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"equip , ");
		for(i=0;i<int(mem_equip.size());i++)
		{
			kouhukin=0;
			for(j=0;j<int(double(uriage.size())*zyoui_rate-1);j++)
			{
				if(pro_no[j]==mem_equip[i]->Get_Agent_no())
				{
					kouhukin=int(double(g_money)*(double(mem_equip[i]->Get_uriage_out())/double(sum_uriage)));
					
					mem_equip[i]->Set_shiwake_hozyokin(i_period,kouhukin);
					mem_equip[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
					mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
					cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
					zisseki+=kouhukin;
				}
			}
			fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"\n");
		fprintf(gyousei_syouhisya,"%d , %d\n",zisseki , cg->Get_genkin_suitoutyou_zandaka());
	}
	else
	{
		kouhukin=g_money/size;

		for(i=0;i<int(mem_retailer.size());i++)
		{
			mem_retailer[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
	//		mem_retailer[i]->Set_yokin(kouhukin);
		}
		for(i=0;i<int(mem_whole.size());i++)
		{
			mem_whole[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_whole[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
	//		mem_whole[i]->Set_yokin(kouhukin);
		}
		for(i=0;i<int(mem_equip.size());i++)
		{
			mem_equip[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_equip[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
	//		mem_equip[i]->Set_yokin(kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"\n");
		fprintf(gyousei_syouhisya,"%d , %d\n",g_money , cg->Get_genkin_suitoutyou_zandaka());
	}

}


void CMarket::Labor_Hozyokin_kouhu()
{
	int i;
	int size;
	int g_money;
	int kouhukin=0;
	int sum_uriage=0;
	int zisseki=0;
//	int kouhu=0;
	size=mem_retailer.size()+mem_whole.size()+mem_equip.size();
	g_money=cg->Get_hozyokin_yosan();
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"yosan , %d , ",g_money);
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"retailer , ");
	for(i=0;i<int(mem_retailer.size());i++) 
	{
			sum_uriage+=mem_retailer[i]->Get_uriage_out();
			fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",mem_retailer[i]->Get_uriage_out());
	}
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"whole , ");
	for(i=0;i<int(mem_whole.size());i++) 
	{
		sum_uriage+=mem_whole[i]->Get_ukerisi_out();
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",mem_whole[i]->Get_uriage_out());
	}
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"equip , ");
	for(i=0;i<int(mem_equip.size());i++)
	{
		sum_uriage+=mem_equip[i]->Get_uriage_out();
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",mem_equip[i]->Get_uriage_out());
	}
	fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"sum_uriage , %d , ",sum_uriage);

	

	if(sum_uriage>0)
	{
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"kouhukin , ");
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"retailer , ");
		for(i=0;i<int(mem_retailer.size());i++)
		{
			kouhukin=int(double(g_money)*(double(mem_retailer[i]->Get_uriage_out())/double(sum_uriage)));
			fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",kouhukin);
			mem_retailer[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
			zisseki+=kouhukin;
	//		mem_retailer[i]->Set_yokin(kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"whole , ");
		for(i=0;i<int(mem_whole.size());i++)
		{
			kouhukin=int(double(g_money)*(double(mem_whole[i]->Get_uriage_out())/double(sum_uriage)));
			fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",kouhukin);
			mem_whole[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_whole[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
			zisseki+=kouhukin;
	//		mem_whole[i]->Set_yokin(kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"equip , ");
		for(i=0;i<int(mem_equip.size());i++)
		{
			kouhukin=int(double(g_money)*(double(mem_equip[i]->Get_uriage_out())/double(sum_uriage)));
			fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"%d , ",kouhukin);
			mem_equip[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_equip[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
			zisseki+=kouhukin;
	//		mem_equip[i]->Set_yokin(kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"\n");
		fprintf(gyousei_syouhisya,"%d , %d\n",zisseki , cg->Get_genkin_suitoutyou_zandaka());
	}
	else
	{
		kouhukin=g_money/size;

		for(i=0;i<int(mem_retailer.size());i++)
		{
			mem_retailer[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
	//		mem_retailer[i]->Set_yokin(kouhukin);
		}
		for(i=0;i<int(mem_whole.size());i++)
		{
			mem_whole[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_whole[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
	//		mem_whole[i]->Set_yokin(kouhukin);
		}
		for(i=0;i<int(mem_equip.size());i++)
		{
			mem_equip[i]->Set_shiwake_hozyokin(i_period,kouhukin);
			mem_equip[i]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,kouhukin);
			cg->Set_shiwake_kigyou_kouhukin(i_period,kouhukin);
	//		mem_equip[i]->Set_yokin(kouhukin);
		}
		fprintf(cpara->FI_Get_Labor_kigyouhozyo(),"\n");
		fprintf(gyousei_syouhisya,"%d , %d\n",g_money , cg->Get_genkin_suitoutyou_zandaka());
	}

}



void CMarket::Situgyou_hosyou()
{
	int s_size=0;
	int i;
	int sum_hosyou=0;
	int hosyou=0;
	int depo=0;
	int new_income;
	//失業者人数検索
	for(i=0;i<int(mem_con.size());i++)
	{
		if(mem_con[i]->Get_office_type()==0)	s_size++;
	}
	//失業人数検索終了

	//sum_hosyou：合計補償額
	//sum_hosyou=s_size*cg->Get_situgyou_hosyou();
	sum_hosyou=cg->Get_hosyou_yosan();
//	printf("hosyou= %d\n",sum_hosyou);
	//printf("\n\nhosyou= %d\n",sum_hosyou);

	if(hosyou>0)
	{
		hosyou=sum_hosyou/s_size;
		for(i=0;i<int(mem_con.size());i++)
		{

			if(mem_con[i]->Get_office_type()==0)
			{
	//			mem_con[i]->Set_depo_rate_new2(hosyou);
		
			//	printf("%d,%d,%d\n",i_period,mem_con[k]->Get_Consumer_no(),new_income);
			//	total_income1+=new_income;

	//			depo=hosyou*mem_con[i]->Get_depo_rate();
//				new_income=hosyou-depo;
				new_income=hosyou;
				mem_con[i]->Set_depo_rate_new3(new_income);

//				fprintf(depo_ch1," , %d , %d\n",int(mem_con[i]->Get_depo_rate()*new_income),new_income);
				mem_con[i]->Renew_income(new_income);
//				printf("\n\nhosyou=  %d , new_income= %d , depo=%d\n\n",hosyou,new_income,depo);
				mem_con[i]->Set_shiwake_hosyoukin(i_period,new_income);
				cg->Set_shiwake_situgyouhosyou(i_period,new_income);
//支払時側の会計処理					mem_bank[mem_con[k]->Get_bank_no()]->Set_shiwake_kyuyo(i_period,new_income);
			}
		}

	}
	fprintf(gyousei_syouhisya," %d , ",hosyou);

}


void CMarket::Collection_statistics_income()
{
	
	int i,sum_income=0,ave_inc;
	for(i=0;i<int(mem_con.size());i++)
	{
		sum_income+=mem_con[i]->Get_kyuyo_c_out();

	}
	ave_inc=sum_income/mem_con.size();
	cg->Set_ave_inc(ave_inc);


}
void CMarket::Agent_hensai()
{
	int i;
	int size_r,size_w,size_e;
	int loan_s,loan_r,sum_loan_s=0,sum=0;
	int taihi;//預金行為等での残高一時退避用変数
	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	size_e=mem_equip.size();
	for(i=0;i<size_r;i++)
	{
		if(mem_retailer[i]->Get_loan_s_zandaka()+mem_retailer[i]->Get_loan_l_zandaka()==0)
		{
			loan_s=0;loan_r=0;sum_loan_s=0;
		}
		else
		{
			loan_s=mem_retailer[i]->Get_loan_s_zandaka();
			mem_retailer[i]->Set_s_risoku(int(loan_s*(0.01/12)));
			loan_r=mem_retailer[i]->Get_s_risoku_zandaka();
			sum_loan_s=loan_s+loan_r;
			
			if(mem_retailer[i]->Get_yokin_suitoutyou_zandaka()>=sum_loan_s)
			{
				mem_retailer[i]->Set_s_risoku(-loan_r);
			}
			else if(mem_retailer[i]->Get_yokin_suitoutyou_zandaka()>=loan_r)
			{
				loan_s=mem_retailer[i]->Get_yokin_suitoutyou_zandaka()-loan_r;//返済額＝現金＋預金
				mem_retailer[i]->Set_s_risoku(-loan_r);
			}
			else
			{
				loan_s=0;
				loan_r=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
				mem_retailer[i]->Set_s_risoku(-loan_r);
				mem_retailer[i]->Set_bankr_p(mem_retailer[i]->Get_bankr_p()+1);
				if(mem_retailer[i]->Get_bankr_p()==1) mem_retailer[i]->Set_i_period_first(i_period);
			}

		}
		sum=loan_s+loan_r;
		mem_retailer[i]->Set_shiwake_loan_s_hensai(i_period,loan_s,loan_r);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,loan_s,loan_r);
//		mem_retailer[i]->Set_yokin(-sum);
		mem_retailer[i]->Set_loan_s(-loan_s);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s);
//		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_yokin(-sum);
//		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_genkin(sum);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(loan_s);
	}
	for(i=0;i<size_w;i++)
	{
		if(mem_whole[i]->Get_loan_s_zandaka()<=0)
		{
			loan_s=0;loan_r=0;sum_loan_s=0;
		}
		else
		{
			loan_s=mem_whole[i]->Get_loan_s_zandaka();
			mem_whole[i]->Set_s_risoku(int(loan_s*(0.01/12)));
			loan_r=mem_whole[i]->Get_s_risoku_zandaka();
			sum_loan_s=loan_s+loan_r;
//20110224			if(mem_whole[i]->Get_yokin_zandaka()>=sum_loan_s)
			if(mem_whole[i]->Get_yokin_suitoutyou_zandaka()>=sum_loan_s)
			{
			}
//20110224			else if(mem_whole[i]->Get_yokin_zandaka()>=loan_r)
			else if(mem_whole[i]->Get_yokin_suitoutyou_zandaka()>=loan_r)
			{
//20110224				loan_s=mem_whole[i]->Get_yokin_zandaka()-loan_r;//返済額＝現金＋預金
				loan_s=mem_whole[i]->Get_yokin_suitoutyou_zandaka()-loan_r;//返済額＝現金＋預金
				mem_whole[i]->Set_s_risoku(-loan_r);
			}
			else
			{
				loan_s=0;
//20110224				loan_r=mem_whole[i]->Get_yokin_zandaka();
				loan_r=mem_whole[i]->Get_yokin_suitoutyou_zandaka();
				mem_whole[i]->Set_s_risoku(-loan_r);
			}
		}
		sum=loan_s+loan_r;
		mem_whole[i]->Set_shiwake_loan_s_hensai(i_period,loan_s,loan_r);
		mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,loan_s,loan_r);
//		mem_whole[i]->Set_yokin(-sum);
		mem_whole[i]->Set_loan_s(-loan_s);
		mem_bank[mem_whole[i]->Get_bank_no()]->Set_loan_s(-loan_s);
//		mem_bank[mem_whole[i]->Get_bank_no()]->Set_yokin(-sum);
//		mem_bank[mem_whole[i]->Get_bank_no()]->Set_genkin(sum);
		mem_bank[mem_whole[i]->Get_bank_no()]->Set_hensai(loan_s);
	}
	for(i=0;i<size_e;i++)
	{
//20110224		mem_equip[i]->Set_shiwake_yokin_azuke(i_period,mem_equip[i]->Get_genkin_zandaka());
//20110224		mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,mem_equip[i]->Get_genkin_zandaka());
		taihi=mem_equip[i]->Get_genkin_suitoutyou_zandaka();
		mem_equip[i]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
//		mem_bank[mem_equip[i]->Get_bank_no()]->Set_yokin(mem_equip[i]->Get_genkin_zandaka());
//		mem_equip[i]->Set_yokin(mem_equip[i]->Get_genkin_zandaka());
//		mem_equip[i]->Set_genkin(-mem_equip[i]->Get_genkin_zandaka());
		if(mem_equip[i]->Get_loan_s_zandaka()<=0)
		{
			loan_s=0;loan_r=0;
		}
		else
		{
			loan_s=mem_equip[i]->Get_loan_s_zandaka();
			mem_equip[i]->Set_s_risoku(int(loan_s*(0.01/12)));
			loan_r=mem_equip[i]->Get_s_risoku_zandaka();
			sum=loan_s+loan_r;
//20110224			if(mem_equip[i]->Get_yokin_zandaka()<=sum)
			if(mem_equip[i]->Get_yokin_suitoutyou_zandaka()<=sum)
			{
//20110224				if(mem_equip[i]->Get_yokin_zandaka()<loan_r){
				if(mem_equip[i]->Get_yokin_suitoutyou_zandaka()<loan_r){
					loan_s=0;loan_r=0;
				}
//20110224				else if(mem_equip[i]->Get_yokin_zandaka()>=loan_r)
				else if(mem_equip[i]->Get_yokin_suitoutyou_zandaka()>=loan_r)
				{
//20110224					loan_s=mem_equip[i]->Get_yokin_zandaka()-loan_r;//返済額＝現金＋預金
					loan_s=mem_equip[i]->Get_yokin_suitoutyou_zandaka()-loan_r;//返済額＝現金＋預金
					mem_equip[i]->Set_s_risoku(-loan_r);
				}
			}
			else
			{
				mem_equip[i]->Set_s_risoku(-loan_r);
			}
		}
		sum=loan_s+loan_r;
		mem_equip[i]->Set_shiwake_loan_s_hensai(i_period,loan_s,loan_r);
		mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,loan_s,loan_r);
//		mem_equip[i]->Set_yokin(-sum);
		mem_equip[i]->Set_loan_s(-loan_s);
		mem_bank[mem_equip[i]->Get_bank_no()]->Set_loan_s(-loan_s);
//		mem_bank[mem_equip[i]->Get_bank_no()]->Set_yokin(-sum);
//		mem_bank[mem_equip[i]->Get_bank_no()]->Set_genkin(sum);
		mem_bank[mem_equip[i]->Get_bank_no()]->Set_hensai(loan_s);
	}

}

void CMarket::Set_reserve()
{
	//準備金設定
	int i;	int size_b;
	size_b=mem_bank.size();
	for(i=0;i<size_b;i++)
	{
		mem_bank[i]->Set_reserve(int(-mem_bank[i]->Get_yokin_suitoutyou_zandaka()*mem_bank[i]->Get_reserve_rate()));
//		printf("reserve=%d yokin=%d rate=%.1f\n",mem_bank[i]->Get_reserve(),mem_bank[i]->Get_yokin_suitoutyou_zandaka(),cpara->GET_PARA_reserve_rate());
	}
}
void CMarket::Kisyu()
{
	int i,j,k;	int size_em,size_c,size_e,size_b,size_r,size_w;
	int min_kyuyo=0,ave_kyuyo=0;
	int sum_mibarai=0,pay_b_emp;
	int mibarai;
	size_c=mem_con.size();
	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	size_e=mem_equip.size();
	size_b=mem_bank.size();
		//失業補償計算   現在使用していない
/*	for(i=0;i<statistics_kyuyo.size();i++)
	{
		if(i==0)	min_kyuyo=statistics_kyuyo[i];
		if(min_kyuyo > statistics_kyuyo[i]) min_kyuyo=statistics_kyuyo[i]; 
	}
	cg->Set_situgyou_hosyou(min_kyuyo);
	*/
	int sum_inc=0,no=0;

	if(i_period!=0)
	{
		for(i=0;i<int(mem_con.size());i++)
		{
			if(mem_con[i]->Get_office_type()!=99999)
			{
				sum_inc+=mem_con[i]->Get_kyuyo_c_out();
				no++;
			}
		}
		cg->Set_ave_inc(sum_inc/no);
	}
	else	cg->Set_ave_inc(0);
	//	cg->Set_situgyou_hosyou(ave_kyuyo);


	statistics_kyuyo.clear();
	kyuyo_no.clear();
	statistics_income.clear();
	sort_static_kyuyo.clear();

	//失業補償計算終わり


	if(i_period==0) {pay_ave=0;pay_ave0=0;ave9=0;}
	pay_ave0=pay_ave/100;
	ave7=ave9/100;
	printf("ave=%d , ave0=%d , ave9=%d \n",pay_ave,pay_ave0,ave9);
	pay_ave=0;ave9=0;
//	printf("ave=%d , ave0=%d , ave9=%d\n",pay_ave,pay_ave0,ave9);
//	fprintf(total_income,"%d , %d\n",pay_ave0,ave7);


	cg->Reset_genyokin_sutioutyou();				//現金出納帳のリセット

	for(i=0;i<size_e;i++)
	{
		mem_equip[i]->Reset_genyokin_sutioutyou();		//現金出納帳のリセット
		size_em=mem_equip[i]->Get_no_employ();
		for(j=0;j<size_em;j++)
		{

			for(k=0;k<size_c;k++)
			{
				if(mem_equip[i]->Get_employer(j)==mem_con[k]->Get_Consumer_no())
				{
					mibarai=mem_equip[i]->Get_employ_const_wage(j);
					pay_b_emp=mem_equip[i]->Get_bonus();
					mem_equip[i]->Set_shiwake_kisyu(i_period,mibarai,pay_b_emp);
					sum_mibarai+=mibarai;
				}
			}
		}
		mem_equip[i]->Set_koteihi(sum_mibarai);
	}
	sum_mibarai=0;
	for(i=0;i<size_b;i++)
	{
		mem_bank[i]->Reset_genyokin_sutioutyou();	//現金出納帳のリセット
		size_em=mem_bank[i]->Get_no_employ();
		for(j=0;j<size_em;j++)
		{
			for(k=0;k<size_c;k++)
			{
				if(mem_bank[i]->Get_employer(j)==mem_con[k]->Get_Consumer_no())
				{
					mibarai=mem_bank[i]->Get_employ_const_wage(j);
					pay_b_emp=mem_bank[i]->Get_bonus();
					mem_bank[i]->Set_shiwake_kisyu(i_period,mibarai,pay_b_emp);
					sum_mibarai+=mibarai;
				}
			}
		}
		mem_bank[i]->Set_koteihi(sum_mibarai);
	}
	for(i=0;i<size_r;i++)
	{
		mem_retailer[i]->Reset_genyokin_sutioutyou();	//現金出納帳のリセット
		mem_retailer[i]->Set_total_genka();
		mem_retailer[i]->Set_total_price_genka(mem_retailer[i]->Get_constant_wage());
		
		mem_retailer[i]->Labor_reset_keihi();
		mem_retailer[i]->Labor_set_bonus(mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ());
		mem_retailer[i]->Labor_set_koteikyu(mem_retailer[i]->Get_constant_wage());
	}
	for(i=0;i<size_w;i++)
	{
		mem_whole[i]->Reset_genyokin_sutioutyou();	//現金出納帳のリセット
		mem_whole[i]->Set_total_genka();

		mem_whole[i]->Labor_reset_keihi();
		mem_whole[i]->Labor_set_bonus(mem_whole[i]->Get_bonus()*mem_whole[i]->Get_no_employ());
		mem_whole[i]->Labor_set_koteikyu(mem_whole[i]->Get_constant_wage());
	}

	for(i=0;i<int(mem_con.size());i++)	mem_con[i]->Reset_genyokin_sutioutyou();	//現金出納帳のリセット


	if(i_period > 0)	Pay_tax();		//税金支払い関数
	fprintf(gyousei_syouhisya,"%d , ",cg->Get_tax_sum());
	cg->reset_tax_sum();

}

int CMarket::Get_yokin_count(int x)
{
	//銀行総預金額
	int i,gen;
	int size_b;
	size_b=mem_bank.size();
	for(i=0;i<size_b;i++)
	{
//201102224			gen=mem_bank[x]->Get_yokin_zandaka();
		gen=mem_bank[x]->Get_yokin_suitoutyou_zandaka();
	}
	return gen;
}
void CMarket::Kimatu()
{
	cs_2->KM__BK__Suply_inte(mem_con,mem_bank,i_period);
	cs_2->KM__BK__Suply_inte(mem_retailer,mem_bank,i_period);
	cs_2->KM__BK__Suply_inte(mem_whole,mem_bank,i_period);
	cs_2->KM__BK__Suply_inte(mem_equip,mem_bank,i_period);

	cs_2->Inv_KM__BK__Repay_loan_l(mem_retailer,mem_bank,i_period);
	cs_2->Inv_KM__BK__Repay_loan_l(mem_whole,mem_bank,i_period);

}

void CMarket::Kessan_Agent()
{
	int nk;//nkessan && i
	int i,x;	int rieki;
	int size_c,size_w,size_r,size_e,size_b,size_sum;
	int loan_l=0,loan_r2=0;
	int zankin=0;
	int zankin_mainus=0;
	int shihon=0;
	int bonus_limit_wage_rate=1;
	int zankin_sum=0,zankin_minus_sum=0;
	int kisyu_yokin=0;
	int no_employ=0;
	
	size_c=mem_con.size();
	size_w=mem_whole.size();
	size_r=mem_retailer.size();
	size_e=mem_equip.size();
	size_b=mem_bank.size();
	size_sum=size_r+size_w+size_e+size_b;//retailer+wholesaler+equipment+bank
	x=size_c/size_sum;//従業員配分のmin数


	for(i=0;i<size_c;i++)
	{
		if(i<1)
		{
			if(nkessan==0 || nkessan==1)	nk=0;
			else nk=1;
		}
		else nk=1;
		if(nk==0) fprintf(out3,"%d期 Consumer = %d Agent_no=%d\n",i_period,i,mem_con[i]->Get_Agent_no());
		mem_con[i]->Kessan(0,&rieki,i_period);
	}

	cg->Kessan(0,&rieki,i_period);

	for(i=0;i<size_w;i++)
	{
		loan_l=0;
		loan_r2=0;
		if(i<3)
		{
			if(nkessan==0 || nkessan==1)	nk=0;
			else nk=1;
		}
		else nk=1;
		if(nk==0) fprintf(out3,"%d期 Wholesaler = %d Agent_no=%d\n",i_period,i,mem_whole[i]->Get_Agent_no());
		mem_whole[i]->Kessan(0,&rieki,i_period);				
		printf("kisyu_yokin %d\n",kisyu_yokin);

//20111120		loan_l=mem_bank[mem_whole[i]->Get_bank_no()]->Get_repayment_data_w(mem_whole,mem_whole[i]->Get_Producer_no());
//20111120		loan_r2=mem_bank[mem_whole[i]->Get_bank_no()]->Get_inte_w(mem_whole,mem_whole[i]->Get_Producer_no());
		mem_whole[i]->Set_bonus_account_clac();
//		no_employ=mem_whole[i]->Get_no_employ();
//		mem_whole[i]->Calc_bonus(loan_l,loan_r2,no_employ);


		
		//ボーナス計算終了

	}
	for(i=0;i<size_r;i++)
	{
		loan_l=0;
		loan_r2=0;

		if(i<2)
		{
			if(nkessan==0 || nkessan==1)	nk=0;
			else nk=1;
		}
		else nk=1;
		if(0==0) fprintf(out3,"%d期 Retailer = %d Agent_no=%d\n",i_period,i,mem_retailer[i]->Get_Agent_no());
		mem_retailer[i]->Kessan(0,&rieki,i_period);
		mem_retailer[i]->print_shihon();
//20111120		loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
//20111120		loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
		mem_retailer[i]->Set_bonus_account_clac();
//		no_employ=mem_retailer[i]->Get_no_employ();
//		mem_retailer[i]->Calc_bonus(loan_l,loan_r2,no_employ);


//		fprintf(cpara->FI_Get_free_text2(),"ag_no:%d , zankin:%d , zankin_mainus:%d\n",mem_retailer[i]->Get_Agent_no(),zankin,zankin_mainus);
//		printf("pay_bonus %d\n",pay_bonus);
		//ボーナス計算終了
	}
	for(i=0;i<size_e;i++)
	{
		loan_l=0;
		loan_r2=0;
		if(i<2)
		{
			if(nkessan==0 || nkessan==1)	nk=0;
			else nk=1;
		}
		else nk=1;
		if(nk==0) fprintf(out3,"%d期 Equipment = %d Agent_no=%d\n",i_period,i,mem_equip[i]->Get_Agent_no());
		mem_equip[i]->Kessan(0,&rieki,i_period);

//20111120		loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
//20111120		loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
		mem_equip[i]->Set_bonus_account_clac();
		
//		no_employ=mem_equip[i]->Get_no_employ();
//		mem_equip[i]->Calc_bonus(loan_l,loan_r2,no_employ);

		
		}
		for(i=0;i<size_b;i++)
		{
			loan_l=0;
			loan_r2=0;
			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"Bank = %d\n",i);
			mem_bank[i]->Kessan(1,&rieki,i_period);
			mem_bank[i]->Set_bonus_account_clac();

//			no_employ=mem_bank[i]->Get_no_employ();
//			mem_bank[i]->Calc_bonus(loan_l,loan_r2,no_employ);

			//ボーナス計算終了
			fprintf(cpara->FI_Get_Wholesaler(),"ac=%lld , sui=%lld\n",mem_bank[0]->Get_genkin_ac_l(),mem_bank[0]->Get_genkin_suitoutyou_zandaka_l());

		}

//	fprintf(cpara->FI_Get_free_text2(),"zankin , %d , zankin_minus , %d\n",zankin_sum,zankin_minus_sum);

/*
	switch(cpara->GET_PARA_bonus_rule_switch())
	{
	case 1:

		for(i=0;i<size_c;i++)
		{
			if(i<1)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Consumer = %d Agent_no=%d\n",i_period,i,mem_con[i]->Get_Agent_no());
			mem_con[i]->Kessan(0,&rieki,i_period);
		}

		cg->Kessan(0,&rieki,i_period);

		for(i=0;i<size_w;i++)
		{
			if(i<3)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Wholesaler = %d Agent_no=%d\n",i_period,i,mem_whole[i]->Get_Agent_no());
			mem_whole[i]->Kessan(0,&rieki,i_period);	

			loan_l=mem_bank[mem_whole[i]->Get_bank_no()]->Get_repayment_data_w(mem_whole,mem_whole[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_whole[i]->Get_bank_no()]->Get_inte_w(mem_whole,mem_whole[i]->Get_Producer_no());

			//残預金でボーナス決定
			zankin=mem_whole[i]->Get_genkin_suitoutyou_zandaka()+mem_whole[i]->Get_yokin_suitoutyou_zandaka();	//保有残金＝現金＋預金		
			zankin_mainus=-mem_whole[i]->Get_tax()-loan_l-loan_r2-mem_whole[i]->Get_constant_wage()-mem_whole[i]->Get_shihon_ac()-mem_whole[i]->Get_buy_retailer_product_out();			//使用不可残金分＝税金＋長期借入＋固定給
			//売上からボーナス決定
//			zankin=mem_whole[i]->Get_uriage_out();	//保有残金＝売上	
//			zankin_mainus=-mem_whole[i]->Get_tax()-loan_l-loan_r2-mem_whole[i]->Get_constant_wage();			//使用不可残金分＝税金＋長期借入＋固定給
	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_whole[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0)
			{
				pay_bonus=int((zankin+zankin_mainus)*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
//				if(pay_bonus>mem_whole[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_whole[i]->Get_constant_wage()*bonus_limit_wage_rate;
				pay_bonus=int(pay_bonus/mem_whole[i]->Get_no_employ());	
			}
			else{
				pay_bonus=0;
			}
			mem_whole[i]->Set_bonus(pay_bonus);
		
			//ボーナス計算終了

		}
		for(i=0;i<size_r;i++)
		{
			loan_l=0;
			loan_r2=0;

			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(0==0) fprintf(out3,"%d期 Retailer = %d Agent_no=%d\n",i_period,i,mem_retailer[i]->Get_Agent_no());
			mem_retailer[i]->Kessan(0,&rieki,i_period);

			loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());

			//残預金からボーナス決定
			zankin=mem_retailer[i]->Get_genkin_suitoutyou_zandaka()+mem_retailer[i]->Get_yokin_suitoutyou_zandaka();	//保有残金＝現金＋預金		
			zankin_mainus=-mem_retailer[i]->Get_tax()-loan_l-loan_r2-mem_retailer[i]->Get_constant_wage()-mem_retailer[i]->Get_shihon_ac()-mem_retailer[i]->Get_buy_retailer_product_out();			//使用不可残金分＝税金＋長期借入＋固定給
			//売上からボーナス決定
//			zankin=mem_retailer[i]->Get_uriage_out();	//保有残金＝売上	
//			zankin_mainus=-mem_retailer[i]->Get_tax()-loan_l-loan_r2-mem_retailer[i]->Get_constant_wage();			//使用不可残金分＝税金＋長期借入＋固定給

	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_retailer[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0){
				pay_bonus=int((zankin+zankin_mainus)*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
//				if(pay_bonus>mem_retailer[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_retailer[i]->Get_constant_wage()*bonus_limit_wage_rate;
//				printf("rieki %d  , pay_bonus %d\n",(mem_retailer[i]->Get_rieki_out()-mem_retailer[i]->Get_tax()),pay_bonus);
				pay_bonus=int(pay_bonus/mem_retailer[i]->Get_no_employ());	
			}
			else{
				pay_bonus=0;
			}
			mem_retailer[i]->Set_bonus(pay_bonus);
//			printf("pay_bonus %d\n",pay_bonus);
			//ボーナス計算終了
		}
		for(i=0;i<size_e;i++)
		{
			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Equipment = %d Agent_no=%d\n",i_period,i,mem_equip[i]->Get_Agent_no());
			mem_equip[i]->Kessan(0,&rieki,i_period);
	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_equip[i]->Get_loan_s_zandaka()==0 && mem_equip[i]->Get_yokin_suitoutyou_zandaka()-mem_equip[i]->Get_tax()>mem_equip[i]->Get_constant_wage())
			{
				pay_bonus=int((mem_equip[i]->Get_genkin_suitoutyou_zandaka()+mem_equip[i]->Get_yokin_suitoutyou_zandaka()-mem_equip[i]->Get_tax()-mem_equip[i]->Get_shihon_ac())*(cr->sdrand(bonus_rate_min_e,bonus_rate_max_e)));
//				if(pay_bonus>mem_equip[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_equip[i]->Get_constant_wage()*bonus_limit_wage_rate;
				pay_bonus=int(pay_bonus/mem_equip[i]->Get_no_employ());
				if(pay_bonus<0) pay_bonus=0;
//				printf("pay_bo:%d\n",pay_bonus);
			}
			else{
				pay_bonus=0;
			}
			mem_equip[i]->Set_bonus(pay_bonus);
			//ボーナス計算終了
		
		}
		for(i=0;i<size_b;i++)
		{
			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"Bank = %d\n",i);
			mem_bank[i]->Kessan(1,&rieki,i_period);

			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
//			if(nbonus==2 && mem_bank[i]->Get_touki_zyunrieki()-mem_bank[i]->Get_tax()>=mem_bank[i]->Get_no_employ()){
			if(nbonus==2 && mem_bank[i]->Get_touki_zeimae_rieki()-mem_bank[i]->Get_tax()>=mem_bank[i]->Get_no_employ()){
				pay_bonus=int((mem_bank[i]->Get_touki_zyunrieki()-mem_bank[i]->Get_tax())*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
				pay_bonus=int(pay_bonus/mem_bank[i]->Get_no_employ());
				if(pay_bonus<0)	pay_bonus=0;
	//			printf("rieki %d  , tax %d , pay_bou %d\n",mem_bank[i]->Get_rieki_ac(),mem_bank[i]->Get_tax(),pay_bonus);
			}
			else{
				pay_bonus=0;
			}
			mem_bank[i]->Set_bonus(pay_bonus);
			//ボーナス計算終了
		}
		break;


	case 2:
		for(i=0;i<size_c;i++)
		{
			if(i<1)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Consumer = %d Agent_no=%d\n",i_period,i,mem_con[i]->Get_Agent_no());
			mem_con[i]->Kessan(0,&rieki,i_period);
		}

		cg->Kessan(0,&rieki,i_period);

		for(i=0;i<size_w;i++)
		{
			if(i<3)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Wholesaler = %d Agent_no=%d\n",i_period,i,mem_whole[i]->Get_Agent_no());
			mem_whole[i]->Kessan(0,&rieki,i_period);	

			loan_l=mem_bank[mem_whole[i]->Get_bank_no()]->Get_repayment_data_w(mem_whole,mem_whole[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_whole[i]->Get_bank_no()]->Get_inte_w(mem_whole,mem_whole[i]->Get_Producer_no());

			//売上からボーナス決定
			zankin=mem_whole[i]->Get_uriage_out();	//保有残金＝売上	
			zankin_mainus=-mem_whole[i]->Get_tax()-loan_l-loan_r2-mem_whole[i]->Get_constant_wage()-mem_whole[i]->Get_buy_retailer_product_out();			//使用不可残金分＝税金＋長期借入＋固定給
	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_whole[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0)
			{
				pay_bonus=int((zankin+zankin_mainus)*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
//				if(pay_bonus>mem_whole[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_whole[i]->Get_constant_wage()*bonus_limit_wage_rate;
				pay_bonus=int(pay_bonus/mem_whole[i]->Get_no_employ());	
			}
			else{
				pay_bonus=0;
			}
			mem_whole[i]->Set_bonus(pay_bonus);
		
			//ボーナス計算終了

		}
		for(i=0;i<size_r;i++)
		{
			loan_l=0;
			loan_r2=0;

			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(0==0) fprintf(out3,"%d期 Retailer = %d Agent_no=%d\n",i_period,i,mem_retailer[i]->Get_Agent_no());
			mem_retailer[i]->Kessan(0,&rieki,i_period);

			loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());

			//売上からボーナス決定
			zankin=mem_retailer[i]->Get_uriage_out();	//保有残金＝売上	
			zankin_mainus=-mem_retailer[i]->Get_tax()-loan_l-loan_r2-mem_retailer[i]->Get_constant_wage()-mem_retailer[i]->Get_buy_retailer_product_out();			//使用不可残金分＝税金＋長期借入＋固定給

	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_retailer[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0){
				pay_bonus=int((zankin+zankin_mainus)*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
//				if(pay_bonus>mem_retailer[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_retailer[i]->Get_constant_wage()*bonus_limit_wage_rate;
//				printf("rieki %d  , pay_bonus %d\n",(mem_retailer[i]->Get_rieki_out()-mem_retailer[i]->Get_tax()),pay_bonus);
				pay_bonus=int(pay_bonus/mem_retailer[i]->Get_no_employ());	
			}
			else{
				pay_bonus=0;
			}
			mem_retailer[i]->Set_bonus(pay_bonus);

			fprintf(cpara->FI_Get_free_text2(),"ag_no:%d , zankin:%d , zankin_mainus:%d\n",mem_retailer[i]->Get_Agent_no(),zankin,zankin_mainus);
//			printf("pay_bonus %d\n",pay_bonus);
			//ボーナス計算終了
		}
		for(i=0;i<size_e;i++)
		{
			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Equipment = %d Agent_no=%d\n",i_period,i,mem_equip[i]->Get_Agent_no());
			mem_equip[i]->Kessan(0,&rieki,i_period);

			loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());

			//売上からボーナス決定
			zankin=mem_equip[i]->Get_uriage_out();	//保有残金＝売上	
			zankin_mainus=-mem_equip[i]->Get_tax()-loan_l-loan_r2-mem_equip[i]->Get_constant_wage()-mem_equip[i]->Get_buy_retailer_product_out();
			printf("zankin:%d , zankin_minus:%d\n",zankin,zankin_mainus);
	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_equip[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0)
			{
				pay_bonus=int((mem_equip[i]->Get_genkin_suitoutyou_zandaka()+mem_equip[i]->Get_yokin_suitoutyou_zandaka()-mem_equip[i]->Get_tax()-mem_equip[i]->Get_shihon_ac())*(cr->sdrand(bonus_rate_min_e,bonus_rate_max_e)));
//				if(pay_bonus>mem_equip[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_equip[i]->Get_constant_wage()*bonus_limit_wage_rate;
				pay_bonus=int(pay_bonus/mem_equip[i]->Get_no_employ());
				if(pay_bonus<0) pay_bonus=0;
//				printf("pay_bo:%d\n",pay_bonus);
			}
			else{
				pay_bonus=0;
			}
			mem_equip[i]->Set_bonus(pay_bonus);
			//ボーナス計算終了
		
		}
		for(i=0;i<size_b;i++)
		{
			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"Bank = %d\n",i);
			mem_bank[i]->Kessan(1,&rieki,i_period);

			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
//			if(nbonus==2 && mem_bank[i]->Get_touki_zyunrieki()-mem_bank[i]->Get_tax()>=mem_bank[i]->Get_no_employ()){
			if(nbonus==2 && mem_bank[i]->Get_touki_zeimae_rieki()-mem_bank[i]->Get_tax()>=mem_bank[i]->Get_no_employ()){
				pay_bonus=int((mem_bank[i]->Get_touki_zyunrieki()-mem_bank[i]->Get_tax())*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
				pay_bonus=int(pay_bonus/mem_bank[i]->Get_no_employ());
				if(pay_bonus<0)	pay_bonus=0;
	//			printf("rieki %d  , tax %d , pay_bou %d\n",mem_bank[i]->Get_rieki_ac(),mem_bank[i]->Get_tax(),pay_bonus);
			}
			else{
				pay_bonus=0;
			}
			mem_bank[i]->Set_bonus(pay_bonus);
			//ボーナス計算終了
		}
		break;



	case 3:		//利益から供出
		for(i=0;i<size_c;i++)
		{
			if(i<1)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Consumer = %d Agent_no=%d\n",i_period,i,mem_con[i]->Get_Agent_no());
			mem_con[i]->Kessan(0,&rieki,i_period);
		}

		cg->Kessan(0,&rieki,i_period);

		for(i=0;i<size_w;i++)
		{
			if(i<3)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Wholesaler = %d Agent_no=%d\n",i_period,i,mem_whole[i]->Get_Agent_no());
			mem_whole[i]->Kessan(0,&rieki,i_period);				
			printf("kisyu_yokin %d\n",kisyu_yokin);

			loan_l=mem_bank[mem_whole[i]->Get_bank_no()]->Get_repayment_data_w(mem_whole,mem_whole[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_whole[i]->Get_bank_no()]->Get_inte_w(mem_whole,mem_whole[i]->Get_Producer_no());

			//売上からボーナス決定
			zankin=mem_whole[i]->Get_karikashi(0,"預金")+mem_whole[i]->Get_karikashi(1,"一般管理費");//mem_whole[i]->Get_touki_zeimae_rieki();//mem_whole[i]->Get_uriage_out();	//保有残金＝売上	
			zankin_mainus=-mem_whole[i]->Get_tax();//mem_whole[i]->Get_tax()-loan_l-loan_r2-mem_whole[i]->Get_constant_wage()-mem_whole[i]->Get_buy_retailer_product_out();			//使用不可残金分＝税金＋長期借入＋固定給
			zankin_sum+=zankin;
			zankin_minus_sum+=zankin_mainus;

			
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_whole[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0)
			{
				pay_bonus=int((zankin+zankin_mainus)*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
//				if(pay_bonus>mem_whole[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_whole[i]->Get_constant_wage()*bonus_limit_wage_rate;
				pay_bonus=int(pay_bonus/mem_whole[i]->Get_no_employ());	
			}
			else{
				pay_bonus=0;
			}
			mem_whole[i]->Set_bonus(pay_bonus);
		
			//ボーナス計算終了

		}
		for(i=0;i<size_r;i++)
		{
			loan_l=0;
			loan_r2=0;

			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(0==0) fprintf(out3,"%d期 Retailer = %d Agent_no=%d\n",i_period,i,mem_retailer[i]->Get_Agent_no());
			mem_retailer[i]->Kessan(0,&rieki,i_period);

			loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());

			//売上からボーナス決定
			zankin=mem_retailer[i]->Get_karikashi(0,"預金")+mem_retailer[i]->Get_karikashi(1,"一般管理費");//mem_retailer[i]->Get_touki_zeimae_rieki();//Get_uriage_out();	//保有残金＝売上	
			zankin_mainus=-mem_retailer[i]->Get_tax();//-loan_l-loan_r2-mem_retailer[i]->Get_constant_wage()-mem_retailer[i]->Get_buy_retailer_product_out();			//使用不可残金分＝税金＋長期借入＋固定給
			zankin_sum+=zankin;
			zankin_minus_sum+=zankin_mainus;
			printf("zankin:%d , yokin:%d , bonus:%d\n",zankin,mem_retailer[i]->Get_karikashi(0,"預金"),mem_retailer[i]->Get_karikashi(1,"一般管理費"));

	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_retailer[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0){
				pay_bonus=int((zankin+zankin_mainus)*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
//				if(pay_bonus>mem_retailer[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_retailer[i]->Get_constant_wage()*bonus_limit_wage_rate;
//				printf("rieki %d  , pay_bonus %d\n",(mem_retailer[i]->Get_rieki_out()-mem_retailer[i]->Get_tax()),pay_bonus);
				pay_bonus=int(pay_bonus/mem_retailer[i]->Get_no_employ());	
			}
			else{
				pay_bonus=0;
			}
			mem_retailer[i]->Set_bonus(pay_bonus);

			fprintf(cpara->FI_Get_free_text2(),"ag_no:%d , zankin:%d , zankin_mainus:%d\n",mem_retailer[i]->Get_Agent_no(),zankin,zankin_mainus);
//			printf("pay_bonus %d\n",pay_bonus);
			//ボーナス計算終了
		}
		for(i=0;i<size_e;i++)
		{
			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"%d期 Equipment = %d Agent_no=%d\n",i_period,i,mem_equip[i]->Get_Agent_no());
			mem_equip[i]->Kessan(0,&rieki,i_period);

			loan_l=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no());
			loan_r2=mem_bank[mem_retailer[i]->Get_bank_no()]->Get_inte_r(mem_retailer,mem_retailer[i]->Get_Producer_no());

			//売上からボーナス決定
			zankin=mem_equip[i]->Get_touki_zeimae_rieki();;//->Get_uriage_out();	//保有残金＝売上	
			zankin_mainus=-mem_equip[i]->Get_tax();//-loan_l-loan_r2-mem_equip[i]->Get_constant_wage()-mem_equip[i]->Get_buy_retailer_product_out();
			zankin_sum+=zankin;
			zankin_minus_sum+=zankin_mainus;
	
			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
			if(nbonus==2 && mem_equip[i]->Get_loan_s_zandaka()==0 && zankin+zankin_mainus>0)
			{
				pay_bonus=zankin+zankin_mainus;//int((mem_equip[i]->Get_genkin_suitoutyou_zandaka()+mem_equip[i]->Get_yokin_suitoutyou_zandaka()-mem_equip[i]->Get_tax()-mem_equip[i]->Get_shihon_ac())*(cr->sdrand(bonus_rate_min_e,bonus_rate_max_e)));
//				if(pay_bonus>mem_equip[i]->Get_constant_wage()*bonus_limit_wage_rate)	pay_bonus=mem_equip[i]->Get_constant_wage()*bonus_limit_wage_rate;
				pay_bonus=int(pay_bonus/mem_equip[i]->Get_no_employ());
				if(pay_bonus<0) pay_bonus=0;
//				printf("pay_bo:%d\n",pay_bonus);
			}
			else{
				pay_bonus=0;
			}
			mem_equip[i]->Set_bonus(pay_bonus);
			//ボーナス計算終了
		
		}
		for(i=0;i<size_b;i++)
		{
			if(i<2)
			{
				if(nkessan==0 || nkessan==1)	nk=0;
				else nk=1;
			}
			else nk=1;
			if(nk==0) fprintf(out3,"Bank = %d\n",i);
			mem_bank[i]->Kessan(1,&rieki,i_period);

			//ボーナス支払い決定、及び残高計算
			pay_bonus=0;
//			if(nbonus==2 && mem_bank[i]->Get_touki_zyunrieki()-mem_bank[i]->Get_tax()>=mem_bank[i]->Get_no_employ()){
			if(nbonus==2 && mem_bank[i]->Get_touki_zeimae_rieki()-mem_bank[i]->Get_tax()>=mem_bank[i]->Get_no_employ()){
				pay_bonus=int((mem_bank[i]->Get_touki_zyunrieki()-mem_bank[i]->Get_tax())*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
				pay_bonus=int(pay_bonus/mem_bank[i]->Get_no_employ());
				if(pay_bonus<0)	pay_bonus=0;
	//			printf("rieki %d  , tax %d , pay_bou %d\n",mem_bank[i]->Get_rieki_ac(),mem_bank[i]->Get_tax(),pay_bonus);
			}
			else{
				pay_bonus=0;
			}
			mem_bank[i]->Set_bonus(pay_bonus);
			//ボーナス計算終了
		}
		break;




	}

	fprintf(cpara->FI_Get_free_text2(),"zankin , %d , zankin_minus , %d\n",zankin_sum,zankin_minus_sum);
*/

}


void CMarket::Suply_pay_wage_b()
{
	int i,j,k,b=0;
	int vec_checker=0;
	int size_em,size_c,size_b;
	long long res_income,sum_income;
	int new_income;
	int b_m=0,inte=0,pay_b,pay_b_emp,sri_b;
	int check=0;
	int total_income1=0;
	size_c=mem_con.size();
	size_b=mem_bank.size();
	for(i=0;i<size_b;i++)
	{
		sum_income=0;
		size_em=mem_bank[i]->Get_no_employ();
		for(j=0;j<size_em;j++)
		{
			vec_checker=0;
			vec_checker=cf->Comp_AGEvec_VAR(mem_con,mem_bank[i]->Get_employer(j));
			
			if(vec_checker==1)	sum_income+=mem_bank[i]->Get_employ_const_wage(j);
		}
//20110224		res_income=mem_bank[i]->Get_genkin_zandaka();
		res_income=mem_bank[i]->Get_genkin_suitoutyou_zandaka_l();
		printf("bank_genkin_suitou : %lld\n",res_income);
		if(sum_income>res_income)
		{
//			res_income+=mem_bank[i]->Get_yokin_zandaka();
//			mem_bank[i]->Set_genkin(mem_bank[i]->Get_yokin_zandaka());//+yokin
//			mem_bank[i]->Set_yokin(-mem_bank[i]->Get_yokin_zandaka());//0
			check=1;
			//不足時処理どうするのか
	/*		lack_money=sum_income-res_income;
			mem_bank[i]->Set_shiwake_loan(i_period,loan);
	    	mem_bank[i]->Set_shiwake_loan(i_period,loan);
			res_income+=loan;*/
		}
		if(nbonus==0) pay_b=0;
		else{
			pay_b=int(mem_bank[i]->Get_bonus()*mem_bank[i]->Get_no_employ());
		}
		b_m=int(res_income-sum_income-pay_b);
		res_income=sum_income+pay_b;
		
		if(check==0){
//			mem_bank[i]->Set_genkin(-res_income);//-res_income
		}else{
//			mem_bank[i]->Set_genkin(-b_m);//-b_m
//			mem_bank[i]->Set_yokin(b_m);//+b_m
		}
//		printf("Bank : b_m=%d res_income=%.0f pay_b=%d\n",b_m,res_income,pay_b);
		sri_b=int(res_income);
		
		for(j=0;j<size_em;j++)
		{
			k=cf->Comp_AGEvec_VAR_return_no(mem_con,mem_bank[i]->Get_employer(j));
		
			pay_b_emp=int(pay_b/mem_bank[i]->Get_no_employ());
//			printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa , %d\n",pay_b_emp);
			new_income=mem_bank[mem_con[k]->Get_bank_no()]->Get_employ_const_wage(j)+pay_b_emp;
//			fprintf(se_income," , %d , %d\n",mem_con[k]->Get_Consumer_no(),new_income);
			ave9+=new_income;
	

			mem_con[k]->Set_depo_rate_new3(new_income);

//給与支払処理
			mem_con[k]->Renew_income(new_income);
			mem_con[k]->Set_shiwake_kyuyo(i_period,new_income);
			mem_bank[i]->Set_shiwake_kyuyo(i_period,new_income-pay_b_emp);
			mem_bank[i]->Set_shiwake_pay_bonus(i_period,pay_b_emp);
			pay_ave+=new_income;
					
			statistics_income.push_back(new_income);
			sort_static_kyuyo.push_back(mem_con[k]->Get_Agent_no());

			statistics_kyuyo.push_back(new_income);	//20110127給与の平均をとるために作成おそらく不要になる見込み
			kyuyo_no.push_back(mem_con[k]->Get_Agent_no());
				
			
		}
	}
//	fprintf(se_income," , , , , ,%d\n",sri_b);
//	fprintf(se_income_new," , , , , ,%d\n",sri_b);
	//fprintf(total_income,"%d",total_income1);
}
void CMarket::Suply_pay_wage_e()
{
	int i,j,k;
	int vec_checker;
	int size_em,size_c,size_e,size_b;
	double res_income,sum_income,t_sum=0;
	int new_income;//new_income:給与 
	int b_m=0;
	int lack_money,inte=0,loan;
	int pay_b,pay_b_emp;
	int total_income1=0;
	int sri_e;

	size_c=mem_con.size();
	size_e=mem_equip.size();
	size_b=mem_bank.size();
	
	for(i=0;i<size_e;i++)
	{
		sum_income=0;
		size_em=mem_equip[i]->Get_no_employ();
		for(j=0;j<size_em;j++)
		{
			vec_checker=0;
			vec_checker=cf->Comp_AGEvec_VAR(mem_con,mem_equip[i]->Get_employer(j));
			if(vec_checker==1)	sum_income+=mem_equip[i]->Get_employ_const_wage(j);
		}
//20110224		res_income=mem_equip[i]->Get_genkin_zandaka();
		res_income=mem_equip[i]->Get_genkin_suitoutyou_zandaka();
		
		if(sum_income>res_income)
		{
			res_income+=mem_equip[i]->Get_yokin_suitoutyou_zandaka();

			int test=mem_equip[i]->Get_yokin_suitoutyou_zandaka();	//出納帳処理があるため変数に一時残高を退避

			mem_equip[i]->Set_shiwake_yokin_hikidashi(i_period,test);
			mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,test);

			fprintf(cpara->FI_Get_se_income(),"sum_income=%lf , res_income=%lf\n",sum_income,res_income);

			if(sum_income>res_income)
			{
				lack_money=int(sum_income-res_income);
				loan=mem_bank[mem_equip[i]->Get_bank_no()]->loan_check(lack_money);
				if(loan>0){
					mem_equip[i]->Set_shiwake_loan(i_period,loan);
					mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_loan(i_period,loan);
					mem_equip[i]->Set_shiwake_yokin_hikidashi(i_period,loan);
					mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
					res_income+=loan;	
					mem_equip[i]->Set_loan_s(loan);
					new_inmoney.push_back(loan);				
					mem_bank[mem_equip[i]->Get_bank_no()]->Set_loan_s(loan);
					printf("E s=%.0f r=%.0f lack=%d  loan=%d \n",sum_income,res_income,loan,mem_equip[i]->Get_loan_s_zandaka());
				}
				else{
					sum_income=res_income;	
				}
			}
		}
		if(nbonus==0) pay_b=0;
		else{
			pay_b=mem_equip[i]->Get_bonus()*mem_equip[i]->Get_no_employ();
			if(sum_income >= res_income && pay_b != 0)
			{
				pay_b=0;
			}
			else if(res_income<(sum_income+pay_b) && pay_b!=0)
			{
				pay_b=int(res_income-sum_income);
			}
		}
		b_m=int(res_income-sum_income-pay_b);
		res_income=sum_income+pay_b;
		sum_income=sum_income+pay_b;
		mem_equip[i]->Set_koteihi(int(sum_income));
		mem_equip[i]->Set_shiwake_yokin_azuke(i_period,b_m);
		mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,b_m);
		sri_e=int(res_income);
		fprintf(cpara->FI_Get_se_income(),"sum_income=%lf , res_income=%lf , pay_b=%d\n",sum_income,res_income,pay_b);

		for(j=0;j<size_em;j++)
		{
			k=cf->Comp_AGEvec_VAR_return_no(mem_con,mem_equip[i]->Get_employer(j));
			pay_b_emp=int(pay_b/mem_equip[i]->Get_no_employ());
//			if(pay_b_emp<0)printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa , equip\n");
//20110224	if(mem_equip[i]->Get_genkin_zandaka()>=mem_equip[i]->Get_employ_const_wage(j)+pay_b_emp){
			if(mem_equip[i]->Get_genkin_suitoutyou_zandaka()>=mem_equip[i]->Get_employ_const_wage(j)+pay_b_emp){
				new_income=mem_equip[i]->Get_employ_const_wage(j)+pay_b_emp;
			}
			else{
//20110224				new_income=mem_equip[i]->Get_genkin_zandaka();
				new_income=mem_equip[i]->Get_genkin_suitoutyou_zandaka();
			}
//			printf("E new=%d in_c=%d res=%.0f sum=%.0f pay=%d\n",new_income,mem_equip[i]->Get_employ_const_wage(j),res_income,sum_income,pay_b);
//			fprintf(se_income," , %d , %d\n",mem_con[k]->Get_Consumer_no(),new_income);
//			printf("c=%d e=%d ni=%d d=%d\n",k,i,new_income,depo);
			ave9+=new_income;


//20110321	mem_con[k]->Set_depo_rate_new3(new_income2);
			mem_con[k]->Set_depo_rate_new3(new_income);
//			fprintf(depo_ch1," , %d , %d\n",int(mem_con[k]->Get_depo_rate()*new_income2),new_income2);
//			fprintf(all_kyuyo," , %d , %d\n",mem_con[k]->Get_Agent_no(),new_income2);
//fprintf(all_kyuyo," , agn= , %d ,kigyou_no= , %d  , %d\n",mem_con[k]->Get_Agent_no(),mem_con[k]->Get_office_no(),new_income2);
			mem_con[k]->Renew_income(new_income);
			mem_con[k]->Set_shiwake_kyuyo(i_period,new_income);
			mem_equip[i]->Set_shiwake_kyuyo(i_period,new_income-pay_b_emp);
			mem_equip[i]->Set_shiwake_pay_bonus(i_period,pay_b_emp);
			printf("equip pay %d\n",pay_b_emp);
			fprintf(cpara->FI_Get_se_income(),"income=%d\n",new_income);
	//		printf("c=%d  new=%d  new2=%d  depo=%d\n",k,new_income,new_income2,depo);
			pay_ave+=new_income;

			statistics_income.push_back(new_income);
			sort_static_kyuyo.push_back(mem_con[k]->Get_Agent_no());
			statistics_kyuyo.push_back(new_income);
			kyuyo_no.push_back(mem_con[k]->Get_Agent_no());
		}
//		printf("gen=%d yo=%d\n",mem_equip[i]->Get_genkin_zandaka(),mem_equip[i]->Get_yokin_zandaka());
	}
//	fprintf(se_income," , , , , %d\n",sri_e);
//	fprintf(se_income_new," , , , , %d\n",sri_e);
	//fprintf(total_income,", ,%d",total_income1);

}
void CMarket::Suply_pay_wage_g()
{
	int i,j,k,b=0;//,i;
	int size_em,size_c;//size_b;
	double sum_income;//,res_income;
	int new_income;//,new_income2,depo;
	int b_m=0,inte=0,sri_b;//,pay_b,pay_b_emp;
	int check=0; int total_income1=0;
	int test_income=0,res_test_income=0,new_test_income=0,new_test_income3=0;
	size_c=mem_con.size();
	sum_income=0;
	size_em=cg->Get_no_employ();


	res_test_income=cg->Get_genkin_suitoutyou_zandaka();

	sri_b=res_test_income;
	new_income=cg->Get_kyuyo_yosan();
	
	if(new_income>res_test_income) new_income=res_test_income;

	for(j=0;j<size_em;j++)
	{
		k=cf->Comp_AGEvec_VAR_return_no(mem_con,cg->Get_employer(j));

	//	pay_b_emp=int(pay_b/cg->Get_no_employ());
	//	new_test_income=int(new_income/cg->Get_no_employ());
		new_test_income=int(new_income/cg->Get_no_employ());
//20110321		mem_con[k]->Set_depo_rate_new3(new_test_income2);
		mem_con[k]->Set_depo_rate_new3(new_test_income);
//		fprintf(depo_ch1," , %d , %d\n",int(mem_con[k]->Get_depo_rate()*new_test_income2),new_test_income2);
//		fprintf(all_kyuyo," , agn= , %d ,kigyou_no= , %d  , %d\n",mem_con[k]->Get_Agent_no(),cg->Get_Agent_no(),new_test_income2);
		mem_con[k]->Renew_income(new_test_income);
		mem_con[k]->Set_shiwake_kyuyo(i_period,new_test_income);
		cg->Set_shiwake_kyuyo(i_period,new_test_income);

		pay_ave+=new_test_income;
		statistics_income.push_back(new_income);
		sort_static_kyuyo.push_back(mem_con[k]->Get_Agent_no());
		statistics_kyuyo.push_back(new_test_income);
		kyuyo_no.push_back(mem_con[k]->Get_Agent_no());
	}
	fprintf(gyousei_syouhisya," %d , ",new_test_income);
	res_test_income=res_test_income-new_test_income*cg->Get_no_employ();
//	printf("res_test=%d\n",res_test_income);
//	printf("bfore  %d\n",cg->Get_genkin_zandaka());
//	cg->Set_genkin(res_test_income);
//	printf("genkinnzanndaka_GGG %d\n",cg->Get_genkin_zandaka());
//	fprintf(tax,"\n");
//	fprintf(se_income," , , , , ,%d\n",sri_b);
//	fprintf(se_income_new," , , , , ,%d\n",sri_b);
//	fprintf(total_income," %d , %d\n",pay);

	//失業者の給与が0であることを入力
	for(i=0;i<int(mem_con.size());i++)
	{
		if(mem_con[i]->Get_office_type()==0)
		{
			statistics_income.push_back(0);
			sort_static_kyuyo.push_back(mem_con[i]->Get_Agent_no());
		}
	}

}
void CMarket::Suply_pay_wage_r()
{	int i,j,k,l;
	int vec_checker;
	int size_em,size_r,size_c,size_b;
	double res_income,sum_income,t_sum=0;
	int new_income;//new_income:給与
	int b_m;
	int lack_money,inte=0,loan;
	int pay_b,pay_b_emp;
	int sum_repay=0;//,total_income1=0;
//	sri=0;//リテイラーの給与支払額の総額
	size_c=mem_con.size();
	size_r=mem_retailer.size();
	size_b=mem_bank.size();
	for(i=0;i<size_r;i++)
	{
		size_em=mem_retailer[i]->Get_no_employ();//従業員数
		sum_income=0;//従業員に支払う固定給の総額
		for(j=0;j<size_em;j++)
		{
			vec_checker=0;
			vec_checker=cf->Comp_AGEvec_VAR(mem_con,mem_retailer[i]->Get_employer(j));
			if(vec_checker==1)	sum_income+=mem_retailer[i]->Get_employ_const_wage(j);
		}
		res_income=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();
		res_income+=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
		int taihi=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
		mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,taihi);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,taihi);
		

		if(sum_income>res_income)//支払給与＞現金＋預金
		{
			lack_money=int(sum_income-res_income);
			loan=mem_bank[mem_retailer[i]->Get_bank_no()]->loan_check(lack_money);
			if(loan>0)
			{
				mem_retailer[i]->Set_shiwake_loan(i_period,lack_money);
				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan(i_period,lack_money);
		 		mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
				mem_retailer[i]->Set_loan_s(lack_money);//+lack_money
//				mem_retailer[i]->Set_genkin(lack_money);//+lack_money
				new_inmoney.push_back(lack_money);
				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(lack_money);
//				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_genkin(-lack_money);
				res_income+=lack_money;
//				printf("C r=%d s=%.0f res=%.0f lack=%d\n",i,sum_income,res_income,lack_money);
			}
			else{
				sum_income=res_income;
			}
		}
		if(nbonus==0) pay_b=0;
		else{
			if(mem_retailer[i]->Get_new_worker_checker()==1)	pay_b=mem_retailer[i]->Get_bonus()*(mem_retailer[i]->Get_no_employ()-mem_retailer[i]->Get_new_worker_size());
			else pay_b=mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ();
//			printf("A : r=%d  sum=%.0f res=%.0f  pay_b=%d\n",i,sum_income,res_income,pay_b);

			if(sum_income >= res_income && pay_b != 0)		pay_b=0;
			else if(res_income < (sum_income + pay_b) && pay_b != 0)	pay_b=int(res_income-sum_income);
		}
		b_m=int(res_income-sum_income-pay_b);
//		printf("sum=%.0f res=%.0f pay_b=%d b_m=%d\n",sum_income,res_income,pay_b,b_m);
		res_income=sum_income+pay_b;
		mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,b_m);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,b_m);
		mem_retailer[i]->Set_koteihi(int(sum_income));
//		fprintf(se_income," ,  ,  ,  ,  ,  ,  pro_no= , %d , sum_i= , %lf , res_i= , %lf  , res-sum= , %lf\n",mem_retailer[i]->Get_Producer_no(),sum_income,res_income,res_income-sum_income);
		for(j=0;j<size_em;j++)
		{
			k=cf->Comp_AGEvec_VAR_return_no(mem_con,mem_retailer[i]->Get_employer(j));
			pay_b_emp=0;
			//pay_b_emp=int(pay_b/mem_retailer[i]->Get_no_employ());
			if(mem_retailer[i]->Get_new_worker_checker()==1)				//新規雇用者がいる場合
			{
//				vec_checker=cf->Comp_AGEvec_INTvec(mem_con,mem_retailer[i]->Get_new_worker_vec());
//				if(vec_checker==0)	pay_b_emp=int(pay_b/(mem_retailer[i]->Get_no_employ()-mem_retailer[i]->Get_new_worker_size()));
				for(l=0;l<mem_retailer[i]->Get_new_worker_size();l++)
				{
					if(mem_retailer[i]->Get_new_worker_no(l)!=mem_con[k]->Get_Consumer_no())	
					{
						pay_b_emp=int(pay_b/(mem_retailer[i]->Get_no_employ()-mem_retailer[i]->Get_new_worker_size()));
					}
					else
					{
						pay_b_emp=0;
						break;
					}
				}
			}
			else	pay_b_emp=int(pay_b/(mem_retailer[i]->Get_no_employ()-mem_retailer[i]->Get_new_worker_size()));	//新規雇用者がいない場合

			if(mem_retailer[i]->Get_genkin_suitoutyou_zandaka()>=mem_retailer[i]->Get_employ_const_wage(j)+pay_b_emp){
				new_income=mem_retailer[i]->Get_employ_const_wage(j)+pay_b_emp;
			}
			else	new_income=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();
									
			ave9+=new_income;

			mem_con[k]->Set_depo_rate_new3(new_income);
			mem_con[k]->Renew_income(new_income);
			mem_con[k]->Set_shiwake_kyuyo(i_period,new_income);
			mem_retailer[i]->Set_shiwake_kyuyo(i_period,new_income-pay_b_emp);
//			printf("pay_b_emp=%d\n",pay_b_emp);
			mem_retailer[i]->Set_shiwake_pay_bonus(i_period,pay_b_emp);
			sum_repay+=new_income;
			pay_ave+=new_income;

			statistics_income.push_back(new_income);
			sort_static_kyuyo.push_back(mem_con[k]->Get_Agent_no());
			statistics_kyuyo.push_back(new_income);
			kyuyo_no.push_back(mem_con[k]->Get_Agent_no());
		}
	}
//	fprintf(se_income," , , , %d\n",sri);
//	fprintf(se_income_new," , , , %d\n",sri);
//fprintf(total_income,"%d",total_income1);
}
void CMarket::Suply_pay_wage_w()
{
	int i,j,k,b=0;
	int vec_checker=0;
	int sri_w=0;
	int b_m=0;//,total_income1=0;
	int size_em,size_c,size_w;
	double res_income,sum_income,t_sum=0;
	int new_income,pay_b,pay_b_emp;//new_income:給与
	int lack_money,loan;
	size_c=mem_con.size();
	size_w=mem_whole.size();
	for(i=0;i<size_w;i++)
	{
		sum_income=0;
		size_em=mem_whole[i]->Get_no_employ();
		for(j=0;j<size_em;j++)
		{
			vec_checker=0;
			vec_checker=cf->Comp_AGEvec_VAR(mem_con,mem_whole[i]->Get_employer(j));

			if(vec_checker==1)	sum_income+=mem_whole[i]->Get_employ_const_wage(j);
			
		}
//		printf("sum=%.0f total=%d\n",sum_income,mem_whole[i]->Get_total_price_genka());
//20110224		res_income=mem_whole[i]->Get_genkin_zandaka();
		res_income=mem_whole[i]->Get_genkin_suitoutyou_zandaka();
		if(sum_income>res_income)//支払給与＞現金
		{
//20110224			res_income+=mem_whole[i]->Get_yokin_zandaka();
			res_income+=mem_whole[i]->Get_yokin_suitoutyou_zandaka();
			int taihi=mem_whole[i]->Get_yokin_suitoutyou_zandaka();		//預金処理の差異の出納帳管理のため値を退避して仕訳処理

//20110224			mem_whole[i]->Set_shiwake_yokin_hikidashi(i_period,mem_whole[i]->Get_yokin_zandaka());
//20110224			mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,mem_whole[i]->Get_yokin_zandaka());
			mem_whole[i]->Set_shiwake_yokin_hikidashi(i_period,taihi);
			mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,taihi);

			if(sum_income>res_income)//支払給与＞現金＋預金
			{
				lack_money=int(sum_income-res_income);
				loan=mem_bank[mem_whole[i]->Get_bank_no()]->loan_check(lack_money);
				if(loan>0){
					mem_whole[i]->Set_shiwake_loan(i_period,lack_money);
					mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_loan(i_period,lack_money);
					mem_whole[i]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
					mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
					mem_whole[i]->Set_loan_s(lack_money);
					new_inmoney.push_back(lack_money);
					mem_bank[mem_whole[i]->Get_bank_no()]->Set_loan_s(lack_money);
					res_income+=lack_money;
				}
				else{
					sum_income=res_income;
				}
			}
		}
		if(nbonus==0) pay_b=0;
		else{
			pay_b=int(mem_whole[i]->Get_bonus()*mem_whole[i]->Get_no_employ());
			if(sum_income >= res_income && pay_b != 0)
			{
				pay_b=0;
			}
			else if(res_income < (sum_income+pay_b) && pay_b !=0)
			{
				pay_b=int(res_income-sum_income);
			}
		}
		b_m=int(res_income-sum_income-pay_b);
		res_income=sum_income+pay_b;
		mem_whole[i]->Set_shiwake_yokin_azuke(i_period,b_m);
		mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,b_m);
		sri_w+=int(res_income);
		mem_whole[i]->Set_koteihi(int(res_income));
//		fprintf(se_income," ,  ,  ,  ,  ,  ,  pro_no= , %d , sum_i= , %lf , res_i= , %lf  , res-sum= , %lf\n",mem_whole[i]->Get_Producer_no(),sum_income,res_income,res_income-sum_income);
		for(j=0;j<size_em;j++)
		{
			k=cf->Comp_AGEvec_VAR_return_no(mem_con,mem_whole[i]->Get_employer(j));

			pay_b_emp=int(pay_b/mem_whole[i]->Get_no_employ());

//			if(pay_b_emp<0)printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa , whole\n");
//20110224	if(mem_whole[i]->Get_genkin_zandaka()>=mem_whole[i]->Get_employ_const_wage(j)+pay_b_emp){
			if(mem_whole[i]->Get_genkin_suitoutyou_zandaka()>=mem_whole[i]->Get_employ_const_wage(j)+pay_b_emp){
				new_income=mem_whole[i]->Get_employ_const_wage(j)+pay_b_emp;
			}
			else{
//20110224		new_income=mem_whole[i]->Get_genkin_zandaka();
				new_income=mem_whole[i]->Get_genkin_suitoutyou_zandaka();
			}
//			printf("W new=%d in_c=%d res=%.0f sum=%.0f pay=%d\n",new_income,mem_whole[i]->Get_employ_const_wage(j),res_income,sum_income,pay_b);
//			fprintf(se_income," , %d , %d\n",mem_con[k]->Get_Consumer_no(),new_income);
			ave9+=new_income;


//20110321	mem_con[k]->Renew_income(new_income2);
			mem_con[k]->Renew_income(new_income);

			mem_con[k]->Set_shiwake_kyuyo(i_period,new_income);
			mem_whole[i]->Set_shiwake_kyuyo(i_period,new_income-pay_b_emp);
			mem_whole[i]->Set_shiwake_pay_bonus(i_period,pay_b_emp);
			pay_ave+=new_income;

			statistics_income.push_back(new_income);
			sort_static_kyuyo.push_back(mem_con[k]->Get_Agent_no());
			statistics_kyuyo.push_back(new_income);
			kyuyo_no.push_back(mem_con[k]->Get_Agent_no());
		}
	}
//	fprintf(se_income," , , , , , %d , %d\n",sri_w,sri);
////	fprintf(se_income_new," , , , , , %d , %d\n",sri_w,sri);
	//fprintf(total_income," ,%d",total_income1);
}
template <class T> void CMarket::Suply_pay_producer(const T &member)
{
	int i,j,k,l;
	int vec_checker;
	int size_em;
	double res_income,sum_income,t_sum=0;
	int new_income;//new_income:給与
	int b_m;
	int lack_money,inte=0,loan;
	int pay_b,pay_b_emp;
	int sum_repay=0;//,total_income1=0;
//	sri=0;//リテイラーの給与支払額の総額
//	size_c=mem_con.size();
//	size_r=member.size();
//	size_b=mem_bank.size();
	for(i=0;i<int(member.size());i++)
	{
		size_em=member[i]->Get_no_employ();//従業員数
		sum_income=0;//従業員に支払う固定給の総額
		for(j=0;j<size_em;j++)
		{
			vec_checker=0;
			vec_checker=cf->Comp_AGEvec_VAR(mem_con,member[i]->Get_employer(j));
			if(vec_checker==1)	sum_income+=member[i]->Get_employ_const_wage(j);
		}
		res_income=member[i]->Get_genkin_suitoutyou_zandaka();
		res_income+=member[i]->Get_yokin_suitoutyou_zandaka();
		int taihi=member[i]->Get_yokin_suitoutyou_zandaka();
		member[i]->Set_shiwake_yokin_hikidashi(i_period,taihi);
		mem_bank[member[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,taihi);
		

		if(sum_income>res_income)//支払給与＞現金＋預金
		{
			lack_money=int(sum_income-res_income);
			loan=mem_bank[member[i]->Get_bank_no()]->loan_check(lack_money);
			if(loan>0)
			{
				member[i]->Set_shiwake_loan(i_period,lack_money);
				mem_bank[member[i]->Get_bank_no()]->Set_shiwake_loan(i_period,lack_money);
		 		member[i]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
				mem_bank[member[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
				member[i]->Set_loan_s(lack_money);//+lack_money
				new_inmoney.push_back(lack_money);
				mem_bank[member[i]->Get_bank_no()]->Set_loan_s(lack_money);
				res_income+=lack_money;
//				printf("C r=%d s=%.0f res=%.0f lack=%d\n",i,sum_income,res_income,lack_money);
			}
			else{
				sum_income=res_income;
			}
		}
		if(nbonus==0) pay_b=0;
		else{
			if(member[i]->Get_new_worker_checker()==1)	pay_b=member[i]->Get_bonus()*(member[i]->Get_no_employ()-member[i]->Get_new_worker_size());
			else pay_b=member[i]->Get_bonus()*member[i]->Get_no_employ();
//			printf("A : r=%d  sum=%.0f res=%.0f  pay_b=%d\n",i,sum_income,res_income,pay_b);

			if(sum_income >= res_income && pay_b != 0)		pay_b=0;
			else if(res_income < (sum_income + pay_b) && pay_b != 0)	pay_b=int(res_income-sum_income);
		}
		b_m=int(res_income-sum_income-pay_b);
//		printf("sum=%.0f res=%.0f pay_b=%d b_m=%d\n",sum_income,res_income,pay_b,b_m);
		res_income=sum_income+pay_b;
		member[i]->Set_shiwake_yokin_azuke(i_period,b_m);
		mem_bank[member[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,b_m);
		member[i]->Set_koteihi(int(sum_income));
//		fprintf(se_income," ,  ,  ,  ,  ,  ,  pro_no= , %d , sum_i= , %lf , res_i= , %lf  , res-sum= , %lf\n",member[i]->Get_Producer_no(),sum_income,res_income,res_income-sum_income);
		for(j=0;j<size_em;j++)
		{
			k=cf->Comp_AGEvec_VAR_return_no(mem_con,member[i]->Get_employer(j));
			pay_b_emp=0;
			//pay_b_emp=int(pay_b/member[i]->Get_no_employ());
			if(member[i]->Get_new_worker_checker()==1)				//新規雇用者がいる場合
			{
//				vec_checker=cf->Comp_AGEvec_INTvec(mem_con,member[i]->Get_new_worker_vec());
//				if(vec_checker==0)	pay_b_emp=int(pay_b/(member[i]->Get_no_employ()-member[i]->Get_new_worker_size()));
				for(l=0;l<member[i]->Get_new_worker_size();l++)
				{
					if(member[i]->Get_new_worker_no(l)!=mem_con[k]->Get_Consumer_no())	
					{
						pay_b_emp=int(pay_b/(member[i]->Get_no_employ()-member[i]->Get_new_worker_size()));
					}
					else
					{
						pay_b_emp=0;
						break;
					}
				}
				
			}
			else	pay_b_emp=int(pay_b/(member[i]->Get_no_employ()-member[i]->Get_new_worker_size()));	//新規雇用者がいない場合

			if(member[i]->Get_genkin_suitoutyou_zandaka()>=member[i]->Get_employ_const_wage(j)+pay_b_emp){
				new_income=member[i]->Get_employ_const_wage(j)+pay_b_emp;
			}
			else	new_income=member[i]->Get_genkin_suitoutyou_zandaka();
									
			ave9+=new_income;

			mem_con[k]->Set_depo_rate_new3(new_income);
			mem_con[k]->Renew_income(new_income);
			mem_con[k]->Set_shiwake_kyuyo(i_period,new_income);
			member[i]->Set_shiwake_kyuyo(i_period,new_income-pay_b_emp);
//			printf("pay_b_emp=%d\n",pay_b_emp);
			member[i]->Set_shiwake_pay_bonus(i_period,pay_b_emp);
			sum_repay+=new_income;
			pay_ave+=new_income;

			statistics_income.push_back(new_income);
			sort_static_kyuyo.push_back(mem_con[k]->Get_Agent_no());
			statistics_kyuyo.push_back(new_income);
			kyuyo_no.push_back(mem_con[k]->Get_Agent_no());
		}


		int housyu=0;

		//報酬支払
		k=cf->Comp_AGEvec_VAR_return_no(mem_con,member[i]->Get_employer(0));	//報酬支払先は0番目の雇用者
		housyu=member[i]->Labor_Get_housyu();
		mem_con[k]->Set_shiwake_kyuyo(i_period,housyu);
		fprintf(cpara->FI_Get_free_text3(),"%d_%d , ",member[i]->Get_Agent_no(),housyu);
		fprintf(cpara->FI_Get_Labor_housyu_out(),"%d , ",housyu);








	}
//	fprintf(se_income," , , , %d\n",sri);
//	fprintf(se_income_new," , , , %d\n",sri);
	//fprintf(total_income,"%d",total_income1);
}

void CMarket::Bankruptcy(int max_ban)
{
	printf("banker_check\n");
	int i,j;
	int size_rwe,size_we,size,size_c,size_con,size_b;
	int bankr;//,i_first;
	int mo=0;	int nc;
	int loan_s,loan_l,genkin,yokin;
	int loan_s_shi;
	int bankruptcy_count=0;
	int newave_price=0;
	int genshi;
	if(i_period!=0)
	{
//		for(i=0;i<mem_class_statics.size();i++)	newave_price+=mem_class_statics[i]->Get_ave_price();
//		newave_price=newave_price/mem_class_statics.size();
		newave_price=first_price;
	}
	vector <int> risyoku;
	vector<int> ::iterator del_c;
	vector <CRetailer *>::iterator del_pr;
	size=mem_retailer.size();
	size_con=mem_con.size();
	size_b=mem_bank.size();
restart:
	size=mem_retailer.size();
	del_pr=mem_retailer.begin();
	for(i=0;i<size;i++)
	{
		bankr=mem_retailer[i]->Get_bankr_p();//借入時の倒産し数（現在未使用）

		mem_retailer[i]->bankr(max_ban);//廃業処理、売れていない製品を検索して売れていなければ倒産
		nc=mem_retailer[i]->Get_ncr_p();//現在の生産クラスの確認、これが0ならば倒産処理開始		
//		printf("r=%d agent_no=%d size_r=%d bp=%d los=%d lol=%d\n",i,mem_retailer[i]->Get_Agent_no(),size,bankr,mem_retailer[i]->Get_loan_s_zandaka(),mem_retailer[i]->Get_loan_l_zandaka());
		if(nc==0)
		{
				size_c=mem_retailer[i]->Get_no_employ();		//雇用しているエージェント数の取得
				loan_s=mem_retailer[i]->Get_loan_s_zandaka();	//短期借入残高取得
				loan_l=mem_retailer[i]->Get_loan_l_zandaka();	//長期借入残高取得
				printf("=========Bankr=========== r=%d agent=%d yo=%d los=%d lol=%d\n",i,mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_yokin_suitoutyou_zandaka(),loan_s,loan_l);
//				scanf("%d",&dummy);
				genkin=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();//現金残高の取得
				mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,genkin);//現金を預金に編入（銀行側処理）
				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,genkin);//現金処理の仕分け（銀行側）
				yokin=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();//預金を全額引き出し


				if(loan_s<=yokin)	//短期借入が預金より大きければ短期借入を返済する
				{
					mem_retailer[i]->Set_loan_s(-loan_s);//返済処理
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s);	//短期借入残高減算
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,loan_s,0);	//短期借入の返済仕訳処理
					mem_retailer[i]->Set_shiwake_s_hensai(i_period,loan_s);			//短期借入の返済処理
//					printf("bankr : loan_s<=yokin : loan_s=%d yokin=%d\n",loan_s,mem_retailer[i]->Get_yokin_suitoutyou_zandaka());
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(loan_s);	//～おそらく返済残高
					loan_s_shi=0;													//～～不明
					genshi=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();		//～おそらく返済原資、残額を編入
				}
				else		//短期借り入れだけでは返済できない場合
				{//loan_s>yokin
					genshi=0;													//～おそらく返済原資
					mem_retailer[i]->Set_shiwake_s_hensai(i_period,yokin);			//預金残額分だけ返済仕訳（企業側）
					mem_retailer[i]->Set_loan_s(-yokin);							//短期借入残高処理（企業側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-yokin);	//預金分だけ短期借入返済借入残高処理（銀行側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_hensai(i_period,yokin,0);//預金分だけ短期借入返済仕訳処理（銀行側）
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(yokin);
					loan_s_shi=loan_s-yokin;										//短期借入の残額
				}

				if(genshi>0)	//短期借入返済後に残預金があるのであれば長期返済
				{
					if(loan_l-genshi>0)//長期借入が多い場合は残額全額返却
					{
						mem_retailer[i]->Set_loan_l(-genshi);		//長期借入の返済
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-genshi);	//長期借入返済処理
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,genshi,0);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(genshi);	//長期借入返済処理
						mem_retailer[i]->Set_shiwake_l_hensai(i_period,genshi);		//長期借入返済処理（仕分け）
						loan_l=loan_l-genshi;
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
					}
					else//長期借入が残預金より少ない場合は返済後に残金ばらまき（暫定で企業に配布）
					{
						mem_retailer[i]->Set_loan_l(-genshi);		//長期借入の返済
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-genshi);	//長期借入返済処理
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan_l_hensai(i_period,genshi,0);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_hensai(genshi);	//長期借入返済処理
						mem_retailer[i]->Set_shiwake_l_hensai(i_period,genshi);		//長期借入返済処理（仕分け）
						loan_l=0;
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
						mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
						genshi=genshi-loan_l;
						int test_pay=genshi/mem_retailer.size();			

						for(int fx=0;fx<int(mem_retailer.size());fx++)
						{
							mem_retailer[fx]->Set_shiwake_hozyokin(i_period,test_pay);
						}
					}
				}
				else//残金一切なしの場合の処理
				{
	/*				mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_tousan(i_period,loan_l,loan_s_shi);
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(-loan_s_shi);
					mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_l(-loan_l);
					*/
				}
				
			//不良債権分を保管するかどうか
			for(j=0;j<size_c;j++)
			{
				risyoku.push_back(mem_retailer[i]->Get_employer(j));
			}
			fprintf(test,"pn=%d\n",mem_retailer[i]->Get_Producer_no());
				
//銀行に売れ残り製品の販売権を与える（バグの元になっているので使用中止）			mem_bank[mem_retailer[i]->Get_bank_no()]->renew_stock_price_banker(mem_product,mem_retailer[i]->Get_Producer_no());
			
			Del_banker_product(mem_retailer[i]->Get_Producer_no());

			mem_retailer.erase(del_pr);
			goto restart;
		}
		del_pr++;
	}
///////////////////倒産したAgent所属Consumerの再配分
	size_c=risyoku.size();
	size_rwe=mem_whole.size()+mem_retailer.size()+mem_equip.size();
	size_we=mem_whole.size()+mem_equip.size();
	ri_count=0;
	for(i=0;i<size_c;i++)
	{
		del_c=risyoku.begin();
reset:
		ri_count=cr->strand(0,size_rwe-1);
		if(ri_count<=size_rwe-1 && ri_count>size_we-1)
		{
			for(j=0;j<size_con;j++)
			{
				if(risyoku[i]==mem_con[j]->Get_Consumer_no())
				{
					ri_count=ri_count-size_we;
					mem_retailer[ri_count]->Set_employ(mem_con[j]->Get_Consumer_no());
					mem_retailer[ri_count]->Set_employ_const_wage(mem_con[j]->Get_constant_wage());
					mem_retailer[ri_count]->Set_total_constant_wage(mem_retailer[ri_count]->Get_constant_wage()+mem_con[j]->Get_constant_wage());
					mem_retailer[ri_count]->Set_total_price_genka(mem_retailer[ri_count]->Get_total_price_genka()+mem_con[j]->Get_constant_wage());
					mem_con[j]->Set_office(mem_retailer[ri_count]->Get_Producer_no());
					mem_con[j]->Set_office_type(mem_retailer[ri_count]->Get_Agent_type());
				}
			}
		}
		else if(ri_count<=size_we-1 && ri_count>int(mem_equip.size())-1)
		{
			ri_count=ri_count-mem_equip.size();
			if(mem_whole[ri_count]->Get_no_employ()<=4)
			{
				for(j=0;j<size_con;j++)
				{
					if(risyoku[i]==mem_con[j]->Get_Consumer_no())
					{
						mem_whole[ri_count]->Set_employ(mem_con[j]->Get_Consumer_no());
						mem_whole[ri_count]->Set_employ_const_wage(mem_con[j]->Get_constant_wage());
						mem_whole[ri_count]->Set_total_constant_wage(mem_whole[ri_count]->Get_constant_wage()+mem_con[j]->Get_constant_wage());
						mem_whole[ri_count]->Set_total_price_genka(mem_whole[ri_count]->Get_total_price_genka()+mem_con[j]->Get_constant_wage());
						mem_con[j]->Set_office(mem_whole[ri_count]->Get_Producer_no());
						mem_con[j]->Set_office_type(mem_whole[ri_count]->Get_Agent_type());
					}
				}
			}
			else
			{
				goto reset;
			}
		}
		else if(ri_count<=int(mem_equip.size())-1)
		{
			if(mem_equip[ri_count]->Get_no_employ()<=2)
			{
				for(j=0;j<size_con;j++)
				{
					if(risyoku[i]==mem_con[j]->Get_Consumer_no())
					{
						mem_equip[ri_count]->Set_employ(mem_con[j]->Get_Consumer_no());
						mem_equip[ri_count]->Set_employ_const_wage(mem_con[j]->Get_constant_wage());
						mem_equip[ri_count]->Set_total_constant_wage(mem_equip[ri_count]->Get_constant_wage()+mem_con[j]->Get_constant_wage());
						mem_equip[ri_count]->Set_total_price_genka(mem_equip[ri_count]->Get_total_price_genka()+mem_con[j]->Get_constant_wage());
						mem_con[j]->Set_office(mem_equip[ri_count]->Get_Producer_no());
						mem_con[j]->Set_office_type(mem_equip[ri_count]->Get_Agent_type());
					}
				}
			}
			else
			{
				goto reset;
			}
		}
	}
	fprintf(test,"re=%d , who=%d\n",mem_retailer.size(),mem_whole.size());
}



void CMarket::Investment()
{
	int i,j,k,l,m,b=0;
	int size_r,size_w,size_e,size_inw;
	int size_p,size_pw;
	int ni,nicon;
	int c_n,c_q;
	int loan,pro_price;
	int loan_w;
	int cap_b=0,res=0;
	int hensai_t;//返済期間
	double kk;
	int invest_counter=0;
	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	size_e=mem_equip.size();
	vector <int> inw;
	vector <int>::iterator p;
	vector <int> inw_r;
	vector <int> inw_w;
	vector <int> e_uriage;
	for(i=0;i<size_e;i++) e_uriage.push_back(0);
	//------------------------------------
	int no_r=0;//投資retailerの数
	int invest_money_r=0;//retailerの投資金総額
	int no_w=0;//投資wholesalerの数
	int invest_money_w=0;//wholesalerの投資金総額
	//-------------------------------------
	//要求を持つエージェントを集める
/*	
	for(i=0;i<size_r;i++)
	{
		if(mem_retailer[i]->Get_eqw()==1)
		{
			if(mem_retailer[i]->Get_loan_l_zandaka()<=cpara->GET_PARA_invest_money()/2)
			{
				inw.push_back(mem_retailer[i]->Get_Producer_no());
			}
		}
	}
	for(i=0;i<size_w;i++)
	{
		
		if(mem_whole[i]->Get_eqw()==1)
		{
			if(mem_whole[i]->Get_loan_l_zandaka()<=cpara->GET_PARA_invest_money()/2)
			{
				inw.push_back(mem_whole[i]->Get_Producer_no());
			}
		}
	}

	if(inw.size()>0)
	{
		//投資要求のあるエージェントをランダムに選ぶ
		for(j=0;j<invest_max;j++)//一期での選定数
		{
			size_inw=inw.size();
			if(size_inw>0)
			{
				size_p=mem_product.size();
				size_pw=mem_product_whole.size();
				
				ni=cr->strand(0,size_inw-1);
				i=inw[ni];//投資機会のあるエージェント番号
				p=inw.begin();
				nicon=0;
				for(k=0;k<size_inw;k++)
				{
					if(nicon==ni) 
					{
						p=inw.erase(p);
						break;
					}
					p++;nicon++;
				}
				//選ばれたエージェントがホールセラーの場合
				if(i<=mem_whole[size_w-1]->Get_Producer_no())
				{
					inw_w.push_back(i);
					for(l=0;l<size_w;l++)
					{
						if(mem_whole[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_whole[l]->Get_eqw_no();//投資対象の製品種別番号を返す
							c_q=mem_whole[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);//投資後の最大生産量comp_qと投資金額pro_priceを定義する
							pro_price=mem_equip[m]->Get_project_price();//投資に必要なお金の額
							loan_w=pro_price;//借入金の額
							if(mem_whole[l]->Get_loan_l_zandaka()<=cpara->GET_PARA_invest_money()/2)
							{
							//	kk=cr->sdrand(0.5,1.0);//返済期間及び借入金額用乱数
								kk=1;
							//	kk=int(cr->seiki(repay_time_ave,repay_time_bun));printf("kkkkkk:%lf\n",kk);
								hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
						//		hensai_t=(cb->Get_hensai()*kk+0.5);
								pro_price=int(pro_price*kk+0.5);	loan_w=pro_price;//借入金額
								loan=cb->Loan_l_w(mem_whole,mem_whole[l]->Get_Producer_no(),loan_w,hensai_t);
								//（vector<int>loanとvector<int>inteを作成)
							}else
							{
								loan=0;
							}
							no_w++;
							invest_money_w+=loan_w;
							if(loan>0)
							{
								mem_whole[l]->Set_loan_l(loan);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_loan_l(loan);
//								mem_bank[mem_whole[l]->Get_bank_no()]->Set_genkin(loan);
//								mem_whole[l]->s_equip(pro_price);
								
								mem_equip[m]->Set_rieki(loan);
							//	mem_equip[cr->strand(0,size_e-1)]->Set_rieki(loan);
//								mem_whole[l]->Set_q_limit(mem_equip[m]->Get_comp_q(),c_n,min_q_limit);
								mem_whole[l]->Up_equipment_revel(c_n);
								printf("loan=%d pro_price=%d\n",loan,pro_price);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
								mem_whole[l]->Set_shiwake_setubi(i_period,pro_price,loan);
								//mem_equip[m]->Set_shiwake_seisan(i_period,mem_equip[m]->Get_koteihi());
								//mem_equip[m]->Set_shiwake_uriage(i_period,pro_price,mem_equip[m]->Get_koteihi());
								e_uriage[m]+=pro_price;
								mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
								mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
//								mem_equip[m]->Set_yokin(pro_price);//+pro_price
//								mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
//								i_count++;2010/11/24　v0.3.4以降の確認が終わったら削除可
							}								
						}
					}
				}
				else
				{
					inw_r.push_back(i);//選ばれたエージェントがリテイラ
					for(l=0;l<size_r;l++)
					{
	//					printf("r_p=%d,i=%d r_n=%d\n",mem_retailer[l]->Get_Producer_no(),i,l);
						if(mem_retailer[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_retailer[l]->Get_eqw_no();
							c_q=mem_retailer[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);
							pro_price=mem_equip[m]->Get_project_price();
							loan_w=pro_price;
		//					printf("los=%d lol=%d\n",mem_retailer[l]->Get_loan_s_zandaka(),mem_retailer[l]->Get_loan_l_zandaka());
							if(mem_retailer[l]->Get_loan_l_zandaka()<=cpara->GET_PARA_invest_money()/2)
							{
								//kk=cr->sdrand(0.5,1.0);//返済期間及び借入金額用乱数
								kk=1;
								//kk=int(cr->seiki(repay_time_ave,repay_time_bun));printf("kkkkkk:%lf\n",kk);
								hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
							//	hensai_t=(cb->Get_hensai()*kk+0.5);
								pro_price=int(pro_price*kk+0.5);	loan_w=pro_price;//借入金額
								loan=cb->Loan_l_r(mem_retailer,mem_retailer[l]->Get_Producer_no(),loan_w,hensai_t);
								//毎期の返済額および支払利息の集合（vector<int>loanとvector<int>inteを作成,保留中)
							}
							else
							{
								loan=0;
							}
							no_r++;
							invest_money_r+=loan_w;
							if(loan>0)
							{	
								mem_retailer[l]->Set_loan_l(loan);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_loan_l(loan);
//								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_genkin(-loan);

								mem_equip[m]->Set_rieki(loan);
								mem_retailer[l]->Up_equipment_revel(c_n);
		//						mem_retailer[l]->Set_q_limit(mem_equip[m]->Get_comp_q(),c_n,min_q_limit);
		//						printf("q=%d  c_n=%d  c_q=%d  min_q_limit=%d  c_q_re=%d\n",mem_equip[m]->Get_comp_q(),c_n,c_q,min_q_limit,mem_retailer[l]->Get_class_q_limit(c_n));
		//						printf("r=%d a=%d loan=%d pro_price=%d\n",l,mem_retailer[l]->Get_Agent_no(),loan,pro_price);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
								mem_retailer[l]->Set_shiwake_setubi(i_period,pro_price,loan);//長期借入⇒預金引出⇒設備
								//mem_equip[m]->Set_shiwake_seisan(i_period,mem_equip[m]->Get_koteihi());
								//mem_equip[m]->Set_shiwake_uriage(i_period,pro_price,mem_equip[m]->Get_koteihi());
								e_uriage[m]+=pro_price;
//								mem_equip[m]->Set_yokin(pro_price);//+pro_price
								mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
//								mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
								mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
					//			i_count++;	2010/11/24　v0.3.4以降の確認が終わったら削除可

							}								
						}
					}
				}
			}
		}
	}
*/	


	for(i=0;i<size_r;i++)
	{
		if(mem_retailer[i]->Get_eqw()==1)
		{
			if(mem_bank[mem_retailer[i]->Get_bank_no()]->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no())==0)
			{
				inw.push_back(mem_retailer[i]->Get_Producer_no());
			}
		}
	}
	for(i=0;i<size_w;i++)
	{
		
		if(mem_whole[i]->Get_eqw()==1)
		{
			if(mem_bank[mem_whole[i]->Get_bank_no()]->Get_repayment_data_w(mem_whole,mem_whole[i]->Get_Producer_no())==0)
			{
				inw.push_back(mem_whole[i]->Get_Producer_no());
			}
		}
	}

	if(inw.size()>0)
	{
		//投資要求のあるエージェントをランダムに選ぶ
		for(j=0;j<invest_max;j++)//一期での選定数
		{
			size_inw=inw.size();
			if(size_inw>0)
			{
				size_p=mem_product.size();
				size_pw=mem_product_whole.size();
				
				ni=cr->strand(0,size_inw-1);
				i=inw[ni];//投資機会のあるエージェント番号
				p=inw.begin();
				nicon=0;
				for(k=0;k<size_inw;k++)
				{
					if(nicon==ni) 
					{
						p=inw.erase(p);
						break;
					}
					p++;nicon++;
				}
				//選ばれたエージェントがホールセラーの場合
				if(i<=mem_whole[size_w-1]->Get_Producer_no())
				{
					inw_w.push_back(i);
					for(l=0;l<size_w;l++)
					{
						if(mem_whole[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_whole[l]->Get_eqw_no();//投資対象の製品種別番号を返す
							c_q=mem_whole[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);//投資後の最大生産量comp_qと投資金額pro_priceを定義する
							pro_price=mem_equip[m]->Get_project_price();//投資に必要なお金の額
							loan_w=pro_price;//借入金の額
							if(mem_whole[l]->Get_loan_l_zandaka()==0)
							{
							//	kk=cr->sdrand(0.5,1.0);//返済期間及び借入金額用乱数
								kk=1;
							//	kk=int(cr->seiki(repay_time_ave,repay_time_bun));printf("kkkkkk:%lf\n",kk);
								hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
						//		hensai_t=(cb->Get_hensai()*kk+0.5);
								pro_price=int(pro_price*kk+0.5);	loan_w=pro_price;//借入金額
								loan=mem_bank[mem_whole[l]->Get_bank_no()]->Loan_l_w(mem_whole,mem_whole[l]->Get_Producer_no(),loan_w,hensai_t);
								//（vector<int>loanとvector<int>inteを作成)
							}else
							{
								loan=0;
							}
							no_w++;
							invest_money_w+=loan_w;
							if(loan>0)
							{
								mem_whole[l]->Set_loan_l(loan);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_loan_l(loan);
//								mem_bank[mem_whole[l]->Get_bank_no()]->Set_genkin(loan);
//								mem_whole[l]->s_equip(pro_price);
								
								mem_equip[m]->Set_rieki(loan);
							//	mem_equip[cr->strand(0,size_e-1)]->Set_rieki(loan);
//								mem_whole[l]->Set_q_limit(mem_equip[m]->Get_comp_q(),c_n,min_q_limit);
								mem_whole[l]->Up_equipment_revel(c_n);
								printf("loan=%d pro_price=%d\n",loan,pro_price);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
								mem_whole[l]->Set_shiwake_setubi(i_period,pro_price,loan);
								//mem_equip[m]->Set_shiwake_seisan(i_period,mem_equip[m]->Get_koteihi());
								//mem_equip[m]->Set_shiwake_uriage(i_period,pro_price,mem_equip[m]->Get_koteihi());
								e_uriage[m]+=pro_price;
								mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
								mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
//								mem_equip[m]->Set_yokin(pro_price);//+pro_price
//								mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
//								i_count++;2010/11/24　v0.3.4以降の確認が終わったら削除可
							}								
						}
					}
				}
				else
				{
					inw_r.push_back(i);//選ばれたエージェントがリテイラ
					for(l=0;l<size_r;l++)
					{
	//					printf("r_p=%d,i=%d r_n=%d\n",mem_retailer[l]->Get_Producer_no(),i,l);
						if(mem_retailer[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_retailer[l]->Get_eqw_no();
							c_q=mem_retailer[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);
							pro_price=mem_equip[m]->Get_project_price();
							loan_w=pro_price;
		//					printf("los=%d lol=%d\n",mem_retailer[l]->Get_loan_s_zandaka(),mem_retailer[l]->Get_loan_l_zandaka());
							if(mem_retailer[l]->Get_loan_l_zandaka()==0)
							{
								//kk=cr->sdrand(0.5,1.0);//返済期間及び借入金額用乱数
								kk=1;
								//kk=int(cr->seiki(repay_time_ave,repay_time_bun));printf("kkkkkk:%lf\n",kk);
								hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
							//	hensai_t=(cb->Get_hensai()*kk+0.5);
								pro_price=int(pro_price*kk+0.5);	loan_w=pro_price;//借入金額
								loan=mem_bank[mem_retailer[l]->Get_bank_no()]->Loan_l_r(mem_retailer,mem_retailer[l]->Get_Producer_no(),loan_w,hensai_t);
								//毎期の返済額および支払利息の集合（vector<int>loanとvector<int>inteを作成,保留中)
							}
							else
							{
								loan=0;
							}
							no_r++;
							invest_money_r+=loan_w;
							if(loan>0)
							{	
								mem_retailer[l]->Set_loan_l(loan);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_loan_l(loan);
//								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_genkin(-loan);

								mem_equip[m]->Set_rieki(loan);
								mem_retailer[l]->Up_equipment_revel(c_n);
		//						mem_retailer[l]->Set_q_limit(mem_equip[m]->Get_comp_q(),c_n,min_q_limit);
		//						printf("q=%d  c_n=%d  c_q=%d  min_q_limit=%d  c_q_re=%d\n",mem_equip[m]->Get_comp_q(),c_n,c_q,min_q_limit,mem_retailer[l]->Get_class_q_limit(c_n));
		//						printf("r=%d a=%d loan=%d pro_price=%d\n",l,mem_retailer[l]->Get_Agent_no(),loan,pro_price);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
								mem_retailer[l]->Set_shiwake_setubi(i_period,pro_price,loan);//長期借入⇒預金引出⇒設備
								//mem_equip[m]->Set_shiwake_seisan(i_period,mem_equip[m]->Get_koteihi());
								//mem_equip[m]->Set_shiwake_uriage(i_period,pro_price,mem_equip[m]->Get_koteihi());
								e_uriage[m]+=pro_price;
//								mem_equip[m]->Set_yokin(pro_price);//+pro_price
								mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
//								mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
								mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
					//			i_count++;	2010/11/24　v0.3.4以降の確認が終わったら削除可

							}								
						}
					}
				}
			}
		}
	}
	
	
/*
	//要求を持つエージェントを集める
	for(i=0;i<size_r;i++)
	{
		if(mem_retailer[i]->Get_eqw()==1)
		{
			if(cb->Get_repayment_data_r(mem_retailer,mem_retailer[i]->Get_Producer_no())==0)
			{
				inw.push_back(mem_retailer[i]->Get_Producer_no());
			}
		}
	}
	for(i=0;i<size_w;i++)
	{
		
		if(mem_whole[i]->Get_eqw()==1)
		{
			if(cb->Get_repayment_data_w(mem_whole,mem_whole[i]->Get_Producer_no())==0)
			{
				inw.push_back(mem_whole[i]->Get_Producer_no());
			}
		}
	}
	if(inw.size()>0)
	{
		//投資要求のあるエージェントをランダムに選ぶ
		for(j=0;j<invest_max;j++)//一期での選定数
		{
			size_inw=inw.size();
			if(size_inw>0)
			{
				size_p=mem_product.size();
				size_pw=mem_product_whole.size();
				
				ni=cr->strand(0,size_inw-1);
				i=inw[ni];//投資機会のあるエージェント番号
				p=inw.begin();
				nicon=0;
				for(k=0;k<size_inw;k++)
				{
					if(nicon==ni) 
					{
						p=inw.erase(p);
						break;
					}
					p++;nicon++;
				}
				//選ばれたエージェントがホールセラーの場合
				if(i<=mem_whole[size_w-1]->Get_Producer_no())
				{
					inw_w.push_back(i);
					for(l=0;l<size_w;l++)
					{
						if(mem_whole[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_whole[l]->Get_eqw_no();//投資対象の製品種別番号を返す
							c_q=mem_whole[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);//投資後の最大生産量comp_qと投資金額pro_priceを定義する
							pro_price=mem_equip[m]->Get_project_price();//投資に必要なお金の額
							loan_w=pro_price;//借入金の額
							if(mem_whole[l]->Get_loan_l_zandaka()==0)
							{
							//	kk=cr->sdrand(0.5,1.0);//返済期間及び借入金額用乱数
								kk=1;
							//	kk=int(cr->seiki(repay_time_ave,repay_time_bun));printf("kkkkkk:%lf\n",kk);
								hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
						//		hensai_t=(cb->Get_hensai()*kk+0.5);
								pro_price=int(pro_price*kk+0.5);	loan_w=pro_price;//借入金額
								loan=cb->Loan_l_w(mem_whole,mem_whole[l]->Get_Producer_no(),loan_w,hensai_t);
								//（vector<int>loanとvector<int>inteを作成)
							}else
							{
								loan=0;
							}
							no_w++;
							invest_money_w+=loan_w;
							if(loan>0&&mem_whole[l]->Get_yokin_suitoutyou_zandaka()>loan/2)
							{
								mem_whole[l]->Set_loan_l(loan);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_loan_l(loan);
//								mem_bank[mem_whole[l]->Get_bank_no()]->Set_genkin(loan);
//								mem_whole[l]->s_equip(pro_price);
								
								loan=loan+loan/2;
								mem_whole[l]->Set_shiwake_yokin_hikidashi(i_period,loan/2);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan/2);

								mem_equip[m]->Set_rieki(loan);
							//	mem_equip[cr->strand(0,size_e-1)]->Set_rieki(loan);
//								mem_whole[l]->Set_q_limit(mem_equip[m]->Get_comp_q(),c_n,min_q_limit);
								mem_whole[l]->Up_equipment_revel(c_n);
								printf("loan=%d pro_price=%d\n",loan,pro_price);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
								mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
								mem_whole[l]->Set_shiwake_setubi(i_period,pro_price,loan);
								//mem_equip[m]->Set_shiwake_seisan(i_period,mem_equip[m]->Get_koteihi());
								//mem_equip[m]->Set_shiwake_uriage(i_period,pro_price,mem_equip[m]->Get_koteihi());
								e_uriage[m]+=pro_price;
								mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
								mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
//								mem_equip[m]->Set_yokin(pro_price);//+pro_price
//								mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
//								i_count++;2010/11/24　v0.3.4以降の確認が終わったら削除可
							}								
						}
					}
				}
				else
				{
					inw_r.push_back(i);//選ばれたエージェントがリテイラ
					for(l=0;l<size_r;l++)
					{
	//					printf("r_p=%d,i=%d r_n=%d\n",mem_retailer[l]->Get_Producer_no(),i,l);
						if(mem_retailer[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_retailer[l]->Get_eqw_no();
							c_q=mem_retailer[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);
							pro_price=mem_equip[m]->Get_project_price();
							loan_w=pro_price;
		//					printf("los=%d lol=%d\n",mem_retailer[l]->Get_loan_s_zandaka(),mem_retailer[l]->Get_loan_l_zandaka());
							if(mem_retailer[l]->Get_loan_l_zandaka()==0)
							{
								//kk=cr->sdrand(0.5,1.0);//返済期間及び借入金額用乱数
								kk=1;
								//kk=int(cr->seiki(repay_time_ave,repay_time_bun));printf("kkkkkk:%lf\n",kk);
								hensai_t=int(cr->seiki(repay_time_ave,repay_time_bun));//cb->Get_hensai()*kk+0.5);
							//	hensai_t=(cb->Get_hensai()*kk+0.5);
								pro_price=int(pro_price*kk+0.5);	loan_w=pro_price;//借入金額
								loan=cb->Loan_l_r(mem_retailer,mem_retailer[l]->Get_Producer_no(),loan_w,hensai_t);
								//毎期の返済額および支払利息の集合（vector<int>loanとvector<int>inteを作成,保留中)
							}
							else
							{
								loan=0;
							}
							no_r++;
							invest_money_r+=loan_w;
							if(loan>0&&	mem_retailer[l]->Get_yokin_suitoutyou_zandaka()>loan/2)
							{	
								mem_retailer[l]->Set_loan_l(loan);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_loan_l(loan);
//								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_genkin(-loan);

								loan=loan+loan/2;
								mem_retailer[l]->Set_shiwake_yokin_hikidashi(i_period,loan/2);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan/2);

								mem_equip[m]->Set_rieki(loan);
								mem_retailer[l]->Up_equipment_revel(c_n);
		//						mem_retailer[l]->Set_q_limit(mem_equip[m]->Get_comp_q(),c_n,min_q_limit);
		//						printf("q=%d  c_n=%d  c_q=%d  min_q_limit=%d  c_q_re=%d\n",mem_equip[m]->Get_comp_q(),c_n,c_q,min_q_limit,mem_retailer[l]->Get_class_q_limit(c_n));
		//						printf("r=%d a=%d loan=%d pro_price=%d\n",l,mem_retailer[l]->Get_Agent_no(),loan,pro_price);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_loan_long(i_period,loan);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,loan);
								mem_retailer[l]->Set_shiwake_setubi(i_period,pro_price,loan);//長期借入⇒預金引出⇒設備
								//mem_equip[m]->Set_shiwake_seisan(i_period,mem_equip[m]->Get_koteihi());
								//mem_equip[m]->Set_shiwake_uriage(i_period,pro_price,mem_equip[m]->Get_koteihi());
								e_uriage[m]+=pro_price;
//								mem_equip[m]->Set_yokin(pro_price);//+pro_price
								mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
//								mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
								mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
					//			i_count++;	2010/11/24　v0.3.4以降の確認が終わったら削除可

							}								
						}
					}
				}
			}
		}
	}
	*/
	
	for(i=0;i<size_e;i++)
	{
		mem_equip[i]->Set_shiwake_seisan(i_period,mem_equip[i]->Get_koteihi());
		mem_equip[i]->Set_shiwake_uriage(i_period,e_uriage[i],mem_equip[i]->Get_koteihi());
		printf("eq:%d\n",mem_equip[i]->Get_koteihi());
//		printf("cons:%d , bonus:%d\n",mem_equip[i]->Get_total_price_genka(),mem_equip[i]->Get_bonus());
	}

	cs->CM_Show_Investment_top(no_r,no_w,invest_money_r,invest_money_w);//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//	fprintf(invest," , %d, %d , %d, %d,",no_r,no_w,invest_money_r,invest_money_w);上の行と一緒でなければ削除しないこと

	for(i=0;i<int(inw_r.size());i++) cs->CM_Show_Investment_middle(inw_r[i]);//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//		fprintf(invest," %d ,",inw_r[i]);上の行と一緒でなければ削除しないこと

	for(i=0;i<int(inw_w.size());i++) cs->CM_Show_Investment_middle(inw_w[i]);//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//		fprintf(invest," %d ,",inw_w[i]);上の行と一緒でなければ削除しないこと

	cs->CM_Show_Investment_row();//CShowに機能移譲、依存が高くなるなら削除、機能は下の行
//	fprintf(invest,"\n");上の行と一緒でなければ削除しないこと
}


void CMarket::Clear_p_class_buy_w()
{
	int i;
	int size;
	size=mem_whole.size();
	for(i=0;i<size;i++)
	{
		mem_whole[i]->Clear_p_class_w();
	}
}
void CMarket::Clear_p_class_buy()
{
	//各リテーラ毎に各製品種別の販売個数を製品種別毎にmarket_buyに格納する
	int i;
	int size_r;
	size_r=mem_retailer.size();
	for(i=0;i<size_r;i++)
	{
		mem_retailer[i]->Clear_p_class();
	}

}
void CMarket::Erase_mem_statics_w()
{
	int i;
	int size=mem_buy_w.size();
	for(i=0;i<size;i++)
	{
		cp=mem_buy_w[0];
		del_p=mem_buy_w.begin();
		mem_buy_w.erase(del_p);
		delete cp;
	}
	mem_class_statics_w.clear();
	mem_class_stock_statics_w.clear();

}

int CMarket::Get_Product_whole(int i,int j)
{
	//i番目リテーラーからj番目種目の製品の納入をq個うける
	int q;
	int class_no;
	int k;
	int hyouka_genka=0;
		q=mem_whole[i]->Get_q(j);
		class_no=mem_whole[i]->Get_class_no(j);
		for(k=0;k<q;k++)
		{
			cp=mem_whole[i]->Get_product(j,k);
			hyouka_genka+=cp->Get_price_genka();
			mem_product_whole.push_back(cp);
		}
		return hyouka_genka;
}
void CMarket::Production_whole_revised()
{
	int size;
	int i,j;int p_gen2;
	int ncr_p;
	int hyouka_genka;
	int product_before=mem_product_whole.size();
	size=mem_whole.size();
	for(i=0;i<size;i++)
	{
		hyouka_genka=0;
		mem_whole[i]->New_set_price();
		mem_whole[i]->Seisan_plan_revised(q_limit_k,price_increase_rate,max_q_re,min_q_re,Adjustment_Sensitivity);//各製品種別毎に生産量qを決定する
		mem_whole[i]->Renew_stock_price(mem_product_whole);
		mem_whole[i]->Seisan();//各製品種別について製品をq個作る
		//各生産者の製品を市場の倉庫(mem_product)にいれる
		p_gen2=mem_whole[i]->Get_total_price_genka();// printf("w=%d p_gen2=%d\n",i,p_gen2);
		mem_whole[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_whole[i]->Get_bonus()*mem_whole[i]->Get_no_employ());
		mem_whole[i]->Set_shiwake_seisan(i_period,p_gen2);
		ncr_p=mem_whole[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++)
		{
			hyouka_genka+=Get_Product_whole(i,j);
		}	  
		hyouka_genka-=p_gen2;
		printf("aaaa:hyouka_genka:%d,%d\n",hyouka_genka,p_gen2);
		mem_whole[i]->Set_shiwake_seisan(i_period,hyouka_genka);
	}
	cso->Set_price_tag(mem_product_whole,mem_WP_tag);
	cs->CM_Show_Production_whole_revised(mem_product_whole.size()-product_before); //CShowクラスで記述、依存度が高ければ削除
	fprintf(cpara->FI_Get_statistic_product(),"\nW生産後\n");
	cs->Show_Product_tag(mem_WP_tag);
//	for(i=0;i<mem_product_whole.size();i++)	if(mem_whole[2]->Get_Agent_no()==mem_product_whole[i]->Get_Agent_no())	fprintf(cpara->FI_Get_economy(),"ag:%d , class:%d , price:%d\n",mem_product_whole[i]->Get_Agent_no(),mem_product_whole[i]->Get_class_no(),mem_product_whole[i]->Get_price());
//	fprintf(market_product," %d ,",mem_product_whole.size()-product_before);		//上の行と一緒でなければ削除しないこと
}

void CMarket::Employ(int no_c)
{
	//no_c:number of consumer :nconsumer、消費者の総数
	int x,y,i,j,k,kk,l=0;
	int empless=0;
	int shinsu_hutaketa;//リテイラーの数を基とする進数の2桁目
	int shinsu_count=0;//余り振り分けがリテイラーの数を越す階数
	int size_r,size_c,size_w,size_e,size_b;
	int size_sum,const_sum=5;
	int nerror;
	nerror=0;
	int ni,nicon;
	vector <int> mem_ni;//選択可能消費者のmem_con内の順位番号（(i=0,....,size_c)の集合
	vector <int> ::iterator p;
	int size_ni;
	size_c=mem_con.size()-empless;
	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	size_e=mem_equip.size();
	size_b=mem_bank.size();
	size_sum=size_r+size_w+size_e+size_b;
	x=size_c/size_sum;//従業員配分のmin数
	y=size_c%size_sum+(x-cpara->GET_PARA_n_bank_worker());//余った従業員の数。mem_retailer[]に配分する
	shinsu_hutaketa=y/size_r;

//	y=size_c%size_sum+(x-2)*size_w+x;//余った従業員の数。mem_retailer[]に配分する
//	printf("c=%d r=%d w=%d e=%d b=%d sum=%d x=%d y=%d\n",size_c,size_r,size_w,size_e,size_b,size_sum,x,y);
	for(i=0;i<int(mem_con.size());i++) mem_ni.push_back(i);


//	x=2;

	for(j=0;j<empless;j++)
	{
		size_ni=mem_ni.size();

		ni=cr->strand(0,size_ni-1)-1;//配分する消費者をランダムに選択する
		i=mem_ni[ni];

		//選択した消費者をmem_ni集合から除外する
		p=mem_ni.begin();
		nicon=0;
		
		for(kk=0;kk<size_ni;kk++)
		{
//			printf("temptest%d , %d , ni=%d , nic=%d , size=%d\n",j , kk,ni,nicon,mem_ni.size());
			if(nicon==ni)
			{
//				printf("emptest%d , %d\n",j , kk);
				p=mem_ni.erase(p);
				size_ni=mem_ni.size();
//				printf("emptest%d , %d\n",j , kk);
				break;
			}
			else
			{
//			printf("demptest%d , %d\n",j , kk);
			p++;nicon++;
//			printf("ddemptest%d , %d\n",j , kk);
			}
		}

		printf("test , %d,%d\n",i,mem_con.size());
		mem_con[i]->Set_office(10000);	
		mem_con[i]->Set_office_type(0);
		printf("testaaa , %d , %d\n",j,empless);
	}




	//Bankへの従業員agentの配分
	for(j=0;j<size_b;j++)
	{
		for(k=0;k<cpara->GET_PARA_n_bank_worker();k++)
		{
			size_ni=mem_ni.size();
			ni=cr->strand(0,size_ni-1);//配分する消費者をランダムに選択する
			i=mem_ni[ni];
			//選択した消費者をmem_ni集合から除外する
			p=mem_ni.begin();
			nicon=0;
			for(kk=0;kk<size_ni;kk++)
			{
				if(nicon==ni)	
				{
					p=mem_ni.erase(p);
					size_ni=mem_ni.size();
					break;
				}
				p++;nicon++;
				
			}
			mem_bank[j]->Set_employ(mem_con[i]->Get_Consumer_no());
			mem_bank[j]->Set_employ_const_wage(mem_con[i]->Get_constant_wage());
			mem_con[i]->Set_office(mem_bank[j]->Get_Agent_no());
			mem_con[i]->Set_office_type(mem_bank[j]->Get_Agent_type());
			const_sum+=mem_bank[j]->Get_employ_const_wage(k);
		}
		mem_bank[j]->Set_total_constant_wage(const_sum);
		mem_bank[j]->Calc_sum_const_wage();
	}





	//行政エージェントの従業員割り当て
	for(k=0;k<cpara->GET_PARA_n_government_worker();k++)
	{
		size_ni=mem_ni.size();
		ni=cr->strand(0,size_ni-1);//配分する消費者をランダムに選択する
		i=mem_ni[ni];
		//選択した消費者をmem_ni集合から除外する
		p=mem_ni.begin();
		nicon=0;
		for(kk=0;kk<size_ni;kk++)
		{
//			printf("size %d\n",mem_ni.size());
				if(nicon==ni)	
				{
					p=mem_ni.erase(p);
					size_ni=mem_ni.size();
					break;
				}
				p++;nicon++;
				
		}
		cg->Set_employ(mem_con[i]->Get_Consumer_no());
		cg->Set_employ_const_wage(mem_con[i]->Get_constant_wage());
		mem_con[i]->Set_office(cg->Get_Agent_no());
		mem_con[i]->Set_office_type(cg->Get_Agent_type());
//		printf("%d\n",l);l++;
	}
	cg->Calc_sum_const_wage();


	//wholesalerへの従業員agentの配分
	for(j=0;j<size_w;j++)//jは企業の添え字
	{
//		for(k=0;k<2;k++)
		for(k=0;k<cpara->GET_PARA_n_whole_worker();k++)//kは平均雇用数の繰り返し番号（xが平均雇用数鵜）
		{
			size_ni=mem_ni.size();
			ni=cr->strand(0,size_ni-1);//配分する消費者をランダムに選択する
			i=mem_ni[ni];
			//選択した消費者をmem_ni集合から除外する
			p=mem_ni.begin();
			nicon=0;
			for(kk=0;kk<int(mem_ni.size());kk++)
			{
				if(kk==ni) 
				{
					p=mem_ni.erase(p);
					size_ni=mem_ni.size();
					break;
				}
				
				p++;nicon++;
//				printf("testtttttttttttttt , %d , %d , %d\n",mem_ni.size(),nicon,kk);
//				printf("testtttttttttttttt , %d , %d , %d\n",mem_ni.size(),nicon,kk);
			}	
			mem_whole[j]->Set_employ(mem_con[i]->Get_Consumer_no());
			mem_whole[j]->Set_employ_const_wage(mem_con[i]->Get_constant_wage());
			mem_con[i]->Set_office(mem_whole[j]->Get_Producer_no());
			mem_con[i]->Set_office_type(mem_whole[j]->Get_Agent_type());	
	//		printf("%d\n",l);l++;
		}
		mem_whole[j]->Calc_sum_const_wage();
	}

	

	//retailerへの従業員agentの配分
	for(j=0;j<size_r;j++)
	{
		for(k=0;k<cpara->GET_PARA_n_retailer_worker();k++)
		{
			size_ni=mem_ni.size();
			ni=cr->strand(0,size_ni-1);//配分する消費者をランダムに選択する
			i=mem_ni[ni];
			//選択した消費者をmem_ni集合から除外する
			p=mem_ni.begin();
			nicon=0;
			for(kk=0;kk<int(mem_ni.size());kk++)
			{
				if(kk==ni) 
				{
					p=mem_ni.erase(p);
					size_ni=mem_ni.size();
					break;
				}
				p++;nicon++;
			}
			mem_retailer[j]->Set_employ(mem_con[i]->Get_Consumer_no());//mem_employ
				//消費者番号を各producerのmem_employに入れる
			mem_retailer[j]->Set_employ_const_wage(mem_con[i]->Get_constant_wage());
				//固定給の値を各Producerのmem_employ_const_wageにいれる
			mem_con[i]->Set_office(mem_retailer[j]->Get_Producer_no());
				//勤務先Producer番号をoffice_noに入れる
			mem_con[i]->Set_office_type(mem_retailer[j]->Get_Agent_type());
				//勤務先Producer typeをoffice_typeに入れる
	//		printf("%d\n",l);l++;
		}
		mem_retailer[j]->Calc_sum_const_wage();
	}
	
	



	//Equipmentへの従業員agentの配分
	for(j=0;j<size_e;j++)
	{
//		for(k=0;k<x-1;k++)
		for(k=0;k<cpara->GET_PARA_n_equip_worker();k++)
		{
			size_ni=mem_ni.size();
			ni=cr->strand(0,size_ni-1);//配分する消費者をランダムに選択する
			i=mem_ni[ni];
			//選択した消費者をmem_ni集合から除外する
			p=mem_ni.begin();
			nicon=0;
			for(kk=0;kk<int(mem_ni.size());kk++)
			{
				if(nicon==ni) 
				{
					p=mem_ni.erase(p);
					size_ni=mem_ni.size();
					break;
				}
				p++;nicon++;
			}
			mem_equip[j]->Set_employ(mem_con[i]->Get_Consumer_no());
			mem_equip[j]->Set_employ_const_wage(mem_con[i]->Get_constant_wage());
			mem_con[i]->Set_office(mem_equip[j]->Get_Producer_no());
			mem_con[i]->Set_office_type(mem_equip[j]->Get_Agent_type());
		}
		mem_equip[j]->Calc_sum_const_wage();
	}

	//余った従業員はmem_retailer[]に配分する
/*	if(shinsu_hutaketa!=0)//リテイラーの数を超える余りがある場合はまずこちらで割り振り
	{
		for(j=0;j<mem_retailer.size();j++)
		{
			printf("size %d\n",mem_ni.size());
			size_ni=mem_ni.size();
			ni=cr->strand(0,size_ni-1);//配分する消費者をランダムに選択する
			i=mem_ni[ni];
			//選択した消費者をmem_ni集合から除外する
			p=mem_ni.begin();
			nicon=0;
			for(kk=0;kk<mem_ni.size();kk++)
			{
				if(kk==ni) 
				{
					p=mem_ni.erase(p);
					size_ni=mem_ni.size();
					break;
				}
				p++;nicon++;
			}
			mem_retailer[j]->Set_employ(mem_con[i]->Get_Consumer_no());//消費者番号を各producerのmem_employに入れる
			mem_retailer[j]->Set_employ_const_wage(mem_con[i]->Get_constant_wage());
			mem_con[i]->Set_office(mem_retailer[j]->Get_Producer_no());
			printf(" %d\n",mem_ni.size());
		//	printf("%d\n",l);l++;
		}
		shinsu_hutaketa-=1;
		shinsu_count++;
	}

*/


//	printf("ni_size while before %d \n",mem_ni.size());
	j=0;
	while(0<mem_ni.size())
	{
	//	printf("topni_size while before %d \n",mem_ni.size());
		size_ni=mem_ni.size();
		ni=cr->strand(0,size_ni-1);//配分する消費者をランダムに選択する
		i=mem_ni[ni];
		//選択した消費者をmem_ni集合から除外する
		p=mem_ni.begin();
		nicon=0;
		for(kk=0;kk<size_ni;kk++)
		{
			if(nicon==ni) 
			{
				p=mem_ni.erase(p);
				break;
			}
			else{
			p++;nicon++;
			}
		}

		mem_retailer[j]->Set_employ(mem_con[i]->Get_Consumer_no());//消費者番号を各producerのmem_employに入れる
		mem_retailer[j]->Set_employ_const_wage(mem_con[i]->Get_constant_wage());
		mem_con[i]->Set_office(mem_retailer[j]->Get_Producer_no());
		mem_con[i]->Set_office_type(mem_retailer[j]->Get_Agent_type());
		printf(" size %d , j=%d , \n",mem_ni.size(),j);
		mem_retailer[j]->Calc_sum_const_wage();
		if(j<int(mem_retailer.size())-1)	j++;
		else	j=0;
//		printf("down\n");

	}

	fprintf(cpara->FI_Get_phenom_writer(),"雇用行動終了以下確認作業\n　雇用者番号 , 労働者番号\n");
	fprintf(cpara->FI_Get_phenom_writer(),"gov employer %d: , ",cg->Get_Agent_no());
	for(i=0;i<cg->Get_no_employ();i++) fprintf(cpara->FI_Get_phenom_writer(),"%d , ",cg->Get_employer(i));
	fprintf(cpara->FI_Get_phenom_writer(),"\n");

	for(i=0;i<int(mem_bank.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"bank %d: , ",mem_bank[i]->Get_Agent_no());
		for(j=0;j<mem_bank[i]->Get_no_employ();j++) fprintf(cpara->FI_Get_phenom_writer(),"%d , ",mem_bank[i]->Get_employer(j));
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}

	for(i=0;i<int(mem_equip.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"equip %d: , ",mem_equip[i]->Get_Agent_no());
		for(j=0;j<mem_equip[i]->Get_no_employ();j++) fprintf(cpara->FI_Get_phenom_writer(),"%d , ",mem_equip[i]->Get_employer(j));
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}

	for(i=0;i<int(mem_whole.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"whole %d: , ",mem_whole[i]->Get_Agent_no());
		for(j=0;j<mem_whole[i]->Get_no_employ();j++) fprintf(cpara->FI_Get_phenom_writer(),"%d , ",mem_whole[i]->Get_employer(j));
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}

	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"whole %d: , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_no_employ();j++) fprintf(cpara->FI_Get_phenom_writer(),"%d , ",mem_retailer[i]->Get_employer(j));
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}

	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"cons %d: , %d , ",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_office_no());
		if(i%5==0) fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}


}

int CMarket::Get_product_size_wholesaler()
{
	int i,j;int ncon;
	int size;
	size=mem_product.size();
	int size_ncr;
	size_ncr=mem_ncr_w.size();
	ncon=0;
	for(i=0;i<size;i++){
		for(j=0;j<size_ncr;j++){
			if(mem_product[i]->Get_class_no()==mem_ncr_w[j])
				ncon++;
			}
	}
	return ncon;
}
int CMarket::Get_product_size_retailer()
{
	int i,j;int ncon;
	int size;
	size=mem_product.size();
	int size_ncr;
	size_ncr=mem_ncr_r.size();
	ncon=0;
	for(i=0;i<size;i++){
		for(j=0;j<size_ncr;j++){
			if(mem_product[i]->Get_class_no()==mem_ncr_r[j])
				ncon++;
			}
	}
	return ncon;
}
void CMarket::Erase_mem_buy()
{
	int i;
	int size;
	size=mem_buy.size();

	for(i=0;i<size;i++)
	{
		cp=mem_buy[0];
		del_p=mem_buy.begin();
		mem_buy.erase(del_p);
		delete cp;
	}
}
void CMarket::Erase_mem_statics()
{
	int i;
	int size;
	size=mem_class_statics.size();

	for(i=0;i<size;i++)
	{
		del_pc=mem_class_statics.begin();
		mem_class_statics.erase(del_pc);
	}
}
void CMarket::Erase_mem_stock_statics()
{
	int i;
	int size;
	size=mem_class_stock_statics.size();

	for(i=0;i<size;i++)
	{
		del_pc=mem_class_stock_statics.begin();
		mem_class_stock_statics.erase(del_pc);
	}
}
void CMarket::Def_nstock_retailer()
{
	int i;
	int size;
	int size_w;
	size=mem_retailer.size();
	size_w=mem_whole.size();
	for(i=0;i<size;i++)
	{
		mem_retailer[i]->Def_stock(mem_product);
		mem_retailer[i]->Show_stock();
	}
	for(i=0;i<size_w;i++)
	{
		mem_whole[i]->Def_stock(mem_product_whole);
	}
}

void CMarket::Def_statics_mem_product()
{
	int i,j;int k;
	int size;
	size=mem_product.size();
	int size_w;
	size_w=mem_product_whole.size();
	int size_ncr;
	size_ncr=mem_ncr_r.size();
	int size_ncr_w;
	size_ncr_w=mem_ncr_w.size();
	int ncon;
	int sum;
	int max_price,min_price;
	double ave_price=0;
	int i_mem_buy;
	//リテイラー製品
	for(i=0;i<size_ncr;i++)
	{
		ncon=0;sum=0;
		for(j=0;j<size;j++)
		{
			if(mem_product[j]->Get_class_no()==mem_ncr_r[i])
			{
				if(ncon==0)
				{
					max_price=mem_product[j]->Get_price();
					min_price=mem_product[j]->Get_price();
				}
				else 
				{
					if(max_price<mem_product[j]->Get_price()) max_price=mem_product[j]->Get_price();
					if(min_price>mem_product[j]->Get_price()) min_price=mem_product[j]->Get_price();		
				}
				sum+=mem_product[j]->Get_price();
				ncon++;
			}
			
		}//for(j=0...の終わり
		if(ncon==0)
		{
			//同じクラス番号を持つmem_buyメンバーの番号i_mem_buyを探す
			for(k=0;k<int(mem_class_statics.size());k++)
			{
				if(mem_class_statics[k]->Get_class_no()==mem_ncr_r[i]) i_mem_buy=k;
			}
			max_price=mem_class_statics[i_mem_buy]->Get_max_price();
			min_price=max_price;
			ave_price=max_price;
		}
		else ave_price=double(sum)/ncon;


		cps=new CProduct_class;
		cps->Set_max_price_stock(max_price);
		cps->Set_min_price_stock(min_price);
		cps->Set_ave_price_stock(int(ave_price));
		cps->Set_ndata_stock(ncon);
		cps->Set_class_no(mem_ncr_r[i]);
		mem_class_stock_statics.push_back(cps);//製品種別ごとの在庫製品の統計データの集合
	}

	//ホールセラー製品
	for(i=0;i<size_ncr_w;i++)
	{
		ncon=0;sum=0;
		for(j=0;j<size_w;j++)
		{
			if(mem_product_whole[j]->Get_class_no()==mem_ncr_w[i])
			{
				if(ncon==0)
				{
					max_price=mem_product_whole[j]->Get_price();
					min_price=mem_product_whole[j]->Get_price();
				}
				else 
				{
					if(max_price<mem_product_whole[j]->Get_price()) max_price=mem_product_whole[j]->Get_price();
					if(min_price>mem_product_whole[j]->Get_price()) min_price=mem_product_whole[j]->Get_price();		
				}
				sum+=mem_product_whole[j]->Get_price();
				ncon++;
			}
		}//for(j=0...の終わり
		if(ncon==0)
		{
			//同じクラス番号を持つmem_buyメンバーの番号i_mem_buyを探す
			for(k=0;k<int(mem_class_statics_w.size());k++)
			{
				if(mem_class_statics_w[k]->Get_class_no()==mem_ncr_w[i]) i_mem_buy=k;
			}
			max_price=mem_class_statics_w[i_mem_buy]->Get_max_price();
			min_price=max_price;
			ave_price=max_price;
		}
		else ave_price=double(sum)/ncon;

		
		cps=new CProduct_class;
		cps->Set_max_price_stock(max_price);
		cps->Set_min_price_stock(min_price);
		cps->Set_ave_price_stock(int(ave_price));
		cps->Set_ndata_stock(ncon);
		cps->Set_class_no(mem_ncr_w[i]);
		mem_class_stock_statics_w.push_back(cps);//製品種別ごとの在庫製品の統計データの集合
	}
}
void CMarket::Def_statics_mem_buy()
{
	int i,j;
	int size;
	int size_w;
	size=mem_buy.size();
	size_w=mem_buy_w.size();
	int size_ncr;
	int size_ncw;
	size_ncr=mem_ncr_r.size();
	size_ncw=mem_ncr_w.size();
	int ncon;
	int sum;
	int max_price=0,min_price=0;
	double ave_price=0;
	int size_pr,size_pw;
	size_pr=mem_product.size();
	size_pw=mem_product.size();
//リテイラー製品
	for(i=0;i<size_ncr;i++)
	{
		ncon=0;sum=0;ave_price=0;
		for(j=0;j<size;j++)
		{
			
			if(mem_buy[j]->Get_class_no()==mem_ncr_r[i])
			{
				if(ncon==0)
				{
					max_price=mem_buy[j]->Get_price();
					min_price=mem_buy[j]->Get_price();
				}
				else 
				{
					if(max_price<mem_buy[j]->Get_price()) max_price=mem_buy[j]->Get_price();
					if(min_price>mem_buy[j]->Get_price()) min_price=mem_buy[j]->Get_price();		
				}
				sum+=mem_buy[j]->Get_price();
				if(mem_buy[j]->Get_price() > 0) ncon++;
			}	
		}
		ave_price=double(sum)/ncon;

///////////////////nconが0の場合に問題が起きる、此処については相談
		if(ncon==0)
		{
			max_price=0;
			min_price=0;
			ave_price=0;
		}

		cps=new CProduct_class;
		cps->Set_max_price(max_price);
		cps->Set_min_price(min_price);
		cps->Set_ave_price(int(ave_price));
		cps->Set_ndata(ncon);
		cps->Set_class_no(mem_ncr_r[i]);
		mem_class_statics.push_back(cps);//製品種別ごとの統計データの集合
		printf("max=%d min=%d ave=%.0f \n",cps->Get_max_price(),cps->Get_min_price(),cps->Get_ave_price());
	}
//ホールセラー製品
	for(i=0;i<size_ncw;i++)
	{
		ncon=0;sum=0;
		for(j=0;j<size_w;j++)
		{
			if(mem_buy_w[j]->Get_class_no()==mem_ncr_w[i])
			{
				
				if(ncon==0)
				{
					max_price=mem_buy_w[j]->Get_price();
					min_price=mem_buy_w[j]->Get_price();
				}
				else 
				{
					if(max_price<mem_buy_w[j]->Get_price()) max_price=mem_buy_w[j]->Get_price();
					if(min_price>mem_buy_w[j]->Get_price()) min_price=mem_buy_w[j]->Get_price();		
				}
				sum+=mem_buy_w[j]->Get_price();
				ncon++;
			}
		}
		if(ncon==0)	ave_price=0;
		else	ave_price=double(sum)/ncon;
		cps=new CProduct_class;
		cps->Set_max_price(max_price);
		cps->Set_min_price(min_price);
		cps->Set_ave_price(int(ave_price));
		cps->Set_ndata(ncon);
		cps->Set_class_no(mem_ncr_w[i]);
		mem_class_statics_w.push_back(cps);//製品種別ごとの統計データの集合
	}
}

void CMarket::Buy_consumer()
{
	int i,sum=0;
	cs_3->B__BC__Buy_consumer(mem_con,mem_retailer,mem_bank,mem_RP_tag,mem_product,del_p,mem_buy,i_period);


	//fprintf(cpara->FI_Get_CR_product_relation(),"%d , ",i_period);
	//for(i=0;i<int(mem_con.size());i++)	
	//	{
	//		fprintf(cpara->FI_Get_CR_product_relation(),"%d , ",mem_con[i]->Get_genkin_suitoutyou_zandaka());
	//		sum+=mem_con[i]->Get_genkin_suitoutyou_zandaka();
	//	}

	//fprintf(cpara->FI_Get_CR_product_relation(),"%d\n",sum);

/*	int i,j,l,b=0,c_gen=0;
	int k;double rate;
	int depo_r=0;
	int depo_money;
	int check;
	int size,size_product,size_r;
	int buy_c; int p_gen;
	size_r=mem_retailer.size();
	size=mem_con.size();
	size_product=mem_product.size();
	int nerror;
	nerror=0;
	int min_price_product;
	vector <int> mem_ni;//選択可能消費者の集合
	vector <int> ::iterator p;
	cs->CM_Show_Buy_consumer_top(size_product);	//	CShowへプリント機能移転、依存度高ければ削除下の行が内容
	*/
//	fprintf(market_product," , %d , ",size_product);	//上の行と一緒でなければ削除しないこと

//～～～～クラスを別クラスにベクターで渡した時の実験跡
//	for(i=0;i<size;i++) mem_con[i]->Test_our_office(mem_retailer);
//	for(i=0;i<mem_retailer.size();i++) printf("producer_no=%d , test_val=%d\n",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_test_val());
//～～～～クラスを別クラスにベクターで渡した時の実験跡

	
	

/*
	for(i=0;i<size;i++) mem_ni.push_back(i);
	for(k=0;k<size;k++)
	{
		i=cf->Random_choice_int(mem_ni,p,cr);
		rate=cr->sdrand(min_with_drawal_rate,max_with_drawal_rate);
//20110224		depo_money=mem_con[i]->Get_yokin_zandaka()*rate;

		depo_money=int(mem_con[i]->Get_yokin_suitoutyou_zandaka()*rate);

		mem_con[i]->Renew_income(depo_money);	//購入データを初期化している（要機能改善）20110224
		mem_con[i]->Set_shiwake_yokin_hikidashi(i_period,depo_money);
		mem_bank[mem_con[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_money);

//		c_gen=mem_con[i]->Get_genkin_zandaka();	//削除対象20110224
		c_gen=mem_con[i]->Get_genkin_suitoutyou_zandaka();

restart:
//20110224		mem_con[i]->Def_min_price_product(mem_product,&nerror,&min_price_product,mem_con[i]->Get_genkin_zandaka());
		mem_con[i]->Def_min_price_product(mem_product,&nerror,&min_price_product,mem_con[i]->Get_genkin_suitoutyou_zandaka());
		check=0;
		if(nerror==0)
		{
			for(j=0;j<size_product;j++)
			{
				if(j==0) 
				{
					del_p=mem_product.begin();
					if(j==min_price_product)
					{
						//mem_product[j]をmem_buyに入れる
						for(l=0;l<size_r;l++)
						{	
							if(mem_product[j]->Get_Producer_no()==mem_retailer[l]->Get_Producer_no())
							{
								mem_retailer[l]->Set_rieki(mem_product[j]->Get_price(),mem_product[j]->Get_class_no());

								check=1;
								buy_c=mem_product[j]->Get_price();
								p_gen=mem_product[j]->Get_price_genka();
								mem_con[i]->Set_shiwake_konyu_c(i_period,buy_c);
								mem_retailer[l]->Set_shiwake_uriage(i_period,buy_c,p_gen);
								mem_retailer[l]->Set_shiwake_yokin_azuke(i_period,buy_c);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_c);
								mem_retailer[l]->Erase_material();
							}
						}
						if(check==0) cb->In_capital(mem_product[j]->Get_price());
						mem_buy.push_back(mem_product[j]);
						mem_product.erase(del_p);
						break;
					}
				}		
				else if(j<=min_price_product)
				{
					del_p++;
					if(j==min_price_product)
					{
						//mem_product[j]をmem_buyに入れる
						for(l=0;l<size_r;l++)
						{
							if(mem_product[j]->Get_Producer_no()==mem_retailer[l]->Get_Producer_no())
							{
								mem_retailer[l]->Set_rieki(mem_product[j]->Get_price(),mem_product[j]->Get_class_no());	
								check=1;
								buy_c=mem_product[j]->Get_price();
								p_gen=mem_product[j]->Get_price_genka();
								mem_con[i]->Set_shiwake_konyu_c(i_period,buy_c);
								mem_retailer[l]->Set_shiwake_uriage(i_period,buy_c,p_gen);
								mem_retailer[l]->Set_shiwake_yokin_azuke(i_period,buy_c);
								mem_bank[mem_retailer[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_c);
								mem_retailer[l]->Erase_material();
							}
						}
						if(check==0) cb->In_capital(mem_product[j]->Get_price());
						mem_buy.push_back(mem_product[j]);
						mem_product.erase(del_p);
						break;
					}
				}
				else {
					fprintf(test,"  ,  ,  ,  , check_c\n");
				}
			}//for(j=0...の終わり
			goto restart;
		}//if(nerror==0...の終わり
		else 
		{
			//購入対象商品が市場にないか、または予算範囲外のために購入できなかった場合
			//買える商品はすべて購入した
			//mem_con[i]->Show_bought_product();//購入した商品を表示する
			nerror=0;
		}
	}//for(i=0...の終わり
	size_product=mem_product.size();
	int in,sum_in=0;
	for(i=0;i<size;i++){
		in=mem_con[i]->Get_income();
		sum_in+=in;
	}

	cs->CM_Show_Buy_consumer_row(size_product,sum_in);	//	CShowへプリント機能移転、依存度高ければ削除下の行が内容
//	fprintf(market_product," %d , %d  \n",size_product,sum_in);	//上の行と一緒でなければ削除しないこと
*/
	for(i=0;i<int(mem_retailer.size());i++) 	mem_retailer[i]->Reset_buy_p();
}



void CMarket::Define_mem_ncr_w()
{
	//wholesalerの製品種別番号の集合を定義する
	int i,j;
	int ncon=0;
	int ncon_whole=0;
	int size;
	int size_ncr_w;
	int class_no;	
	size=mem_product_whole.size();
	fprintf(out,"size of mem_product produced by wholeseller=,%3d,\n",size);
	for(i=0;i<size;i++)
	{
		//if(mem_product[i]->Get_Producer_type()==30){
		if(mem_product_whole[i]->Get_product_type()==2){
			  //Get_Producer_type==30としても同じ結果となる
			ncon_whole++;
			class_no=mem_product_whole[i]->Get_class_no();
			size_ncr_w=mem_ncr_w.size();
			if(size_ncr_w==0) mem_ncr_w.push_back(class_no);
			else{
				ncon=0;
				for(j=0;j<size_ncr_w;j++){
					if(mem_ncr_w[j]!=class_no) ncon++;
				}
				//class_noが新しいクラス番号であればmem_ncr_wにいれる
				if(ncon==size_ncr_w) mem_ncr_w.push_back(class_no);
			}
		}		
	}

	fprintf(cpara->FI_Get_phenom_writer(),"define mem_ncr_w\n ホールセラーの製品種集合の表示\n mem_ncr_w size=%d , ",mem_ncr_w.size());
	for(i=0;i<int(mem_ncr_w.size());i++)fprintf(cpara->FI_Get_phenom_writer(),"mem_ncr_w no%d: , %d , ",i,mem_ncr_w[i]);
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
}
void CMarket::Define_mem_ncr_r()
{
	//retailerの製品種別番号の集合=consusmerが購入する製品種別番号の集合、を定義する
	int i,j;
	int size_ncr_w;
	int ncon;
	size_ncr_w=mem_ncr_w.size();
	for(i=1;i<n_class;i++){
		ncon=0;
		for(j=0;j<size_ncr_w;j++){
			if(mem_ncr_w[j]!=i) ncon++;
		}
		//iがncr_size_wに含まれていない新しい番号であればmem_ncr_rに入れる.
		if(ncon==size_ncr_w) mem_ncr_r.push_back(i);
	}
	printf("ncr_r.size=%d ncr_w.size=%d\n",mem_ncr_r.size(),mem_ncr_w.size());
	for(i=0;i<int(mem_ncr_r.size());i++)
	{
		printf("size=%d , %d\n",mem_ncr_w.size(),mem_ncr_w[i]);
		mem_ncr_r_m.push_back(mem_ncr_w[i]);
	}

	fprintf(cpara->FI_Get_phenom_writer(),"define mem_ncr_r\n リテイラーの製品種集合の表示\n mem_ncr_r size=%d , ",mem_ncr_r.size());
	for(i=0;i<int(mem_ncr_r.size());i++) fprintf(cpara->FI_Get_phenom_writer(),"mem_ncr_r no%d: , %d , ",i,mem_ncr_r[i]);
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
	fprintf(cpara->FI_Get_phenom_writer(),"define mem_ncr_r_m\n リテイラーの製品種の減量表示\n mem_ncr_r_m size=%d , ",mem_ncr_r_m.size());
	for(i=0;i<int(mem_ncr_r.size());i++) fprintf(cpara->FI_Get_phenom_writer(),"mem_ncr_r_m no%d: , %d , ",i,mem_ncr_r_m[i]);
	fprintf(cpara->FI_Get_phenom_writer(),"\n");

}
void CMarket::Set_qmax_whole(int qmaxmax_w,int qmaxmin_w)
{
	int i,j;
	int size;
	double cob_k;
	size=mem_whole.size();
	//int ncr_p;
	for(i=0;i<size;i++) 
	{
		mem_whole[i]->Set_qmaxmax(qmaxmax_w,qmaxmin_w,min_q_init);
			//各製品種別毎に生産量を決定する。初期：最大生産量、下限生産量定義=0.5
		for(j=0;j<mem_whole[i]->Get_n_class();j++)
		{
//			cob_k=cr->sdrand(200,300);
			cob_k=cr->sdrand(cpara->GET_PARA_cob_alpha_w_down(),cpara->GET_PARA_cob_alpha_w_up());

//			cob_k=cr->sdrand(80,150);
//			cob_k=cr->sdrand(140,280);
			mem_whole[i]->Set_cobb_k(j,cob_k);
			fprintf(cpara->FI_Get_phenom_writer(),"コブダグラスの係数設定ｗ：%d , 上限：%d, 下限：%d, 発生数：%lf , 最終的なｋの値：%lf\n",mem_whole[i]->Get_Agent_no(),cpara->GET_PARA_cob_alpha_w_up(),cpara->GET_PARA_cob_alpha_w_down(),cob_k,mem_whole[i]->Get_cobb_k(j));
		}
	}
}
void CMarket::Set_qmax_retailer(int qmaxmax,int qmaxmin)
{
	int i,j;
	int size;
	double cob_k;
	size=mem_retailer.size();
	for(i=0;i<size;i++)
	{
		mem_retailer[i]->Set_qmaxmax(qmaxmax,qmaxmin,min_q_init);
			//各製品種別毎に生産量を決定する。初期：最大生産量、下限生産量定義=0.5
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			//cob_k=cr->sdrand(8,18);
			cob_k=cr->sdrand(cpara->GET_PARA_cob_alpha_r_down(),cpara->GET_PARA_cob_alpha_r_up());	
//			cob_k=cr->sdrand(14,28);
			mem_retailer[i]->Set_cobb_k(j,cob_k);
			fprintf(cpara->FI_Get_phenom_writer(),"コブダグラスの係数設定r：%d , 上限：%d, 下限：%d, 発生数：%lf , 最終的なｋの値：%lf\n",mem_retailer[i]->Get_Agent_no(),cpara->GET_PARA_cob_alpha_r_up(),cpara->GET_PARA_cob_alpha_r_down(),cob_k,mem_retailer[i]->Get_cobb_k(j));
		}
	}
}
void CMarket::Production_whole()
{
	int size;//	int hendouhi;
	int i,j;	int p_gen2;
	int ncr_p;
	int hyouka_genka=0;
	int product_before=mem_product_whole.size();
	size=mem_whole.size();
	for(i=0;i<size;i++){
		fprintf(seisan,"whole_no=%d agent_no=%d producer_no=%d\n",i,mem_whole[i]->Get_Agent_no(),mem_whole[i]->Get_Producer_no());
		mem_whole[i]->Seisan_plan_w(min_price_w,max_price_w);//生産する製品種別毎に価格を決定する
		mem_whole[i]->Seisan();//各製品種別について製品をq個作る//各生産者の製品を市場の倉庫(mem_product)にいれる	
		p_gen2=mem_whole[i]->Get_total_price_genka();//		printf("w=%d total=%d\n",i,p_gen2);
		mem_whole[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_whole[i]->Get_bonus()*mem_whole[i]->Get_no_employ());
		mem_whole[i]->Set_shiwake_seisan(i_period,p_gen2);
		ncr_p=mem_whole[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++)
		{
			hyouka_genka+=Get_Product_wholesaler(i,j);//市場のwholesaler製品の集合mem_product_wholeに製品を格納する
		}
		hyouka_genka-=p_gen2;
		printf("hyoukagenka          %d\n",hyouka_genka);
		mem_whole[i]->Set_shiwake_seisan(i_period,hyouka_genka);

		fprintf(seisan,"\n-----------------------------------------------------------------------------\n");
	}
	cs->CM_Show_Production_whole_revised(mem_product_whole.size()-product_before);
}
void CMarket::Production_retail()
{
	//初期生産
	int size,size_w,size_b;
	int i,j,k,l,m;int b=0;
	int ncr_p;int p_gen,p_gen2,price_w;
	int size_wp;
	int material_need,depo_m;
	int x,z;
	int capital;
	int loan,lack_money;
	int hyouka_genka=0;
	int ncon=0,min_pro=0,min_id;
		//min_pro:minimum price of product in the market
		//min_id:no of minimum price product in mem_product_whole
	vector <CProduct *>::iterator del_pw;
	size_wp=mem_product_whole.size();
	del_pw=mem_product_whole.begin();
	size=mem_retailer.size();
	size_w=mem_whole.size();
	size_b=mem_bank.size();

//	fprintf(cpara->FI_Get_market_product()," , ");
	cs->CM_Show_Production_retail_top(mem_product_whole.size());//CShow機能移転、依存度が高い場合は削除、下の行が機能内容
//	fprintf(market_product," %d ,",mem_product_whole.size());//上の行と一緒でなければ削除しないこと

	for(i=0;i<size;i++)
	{
		mem_retailer[i]->First_set_q();
		hyouka_genka=0;
		fprintf(seisan,"R , %d , %d , %d , ",i,mem_retailer[i]->Get_Producer_no(),mem_retailer[i]->Get_Agent_no());
		mem_retailer[i]->Set_material_need();
				//各製品種別毎に生産量qを決定する
				//material_need=生産量とする
				//価格の改定は未

		depo_m=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
		capital=mem_retailer[i]->Get_genkin_suitoutyou_zandaka()+depo_m;//売上集計後の所有金額+depo_mを所有金額とする
		mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,depo_m);//預金を全額引き出す
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_m);

		//原料購買活動、原料を購入してをmem_bought_pに格納する
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(k=0;k<ncr_p;k++)
		{
			z=0;
			
			material_need=mem_retailer[i]->Get_material_need(k);
restart:

			del_pw=mem_product_whole.begin();
			size_wp=mem_product_whole.size();
			x=0;//count
			ncon=0;
			if(material_need==0){	mem_retailer[i]->Set_re_buy(z);}
			if(material_need>0 && size_wp>0)
			{	
				//当該製品種別の中で市場にある最低価格の原料を購入する
				//購入した原料をmem_product_wholeから削除する
				//当該製品種別の中で市場にある最低価格の原料を選出する, min_pro, min_idを決定する
				min_pro=9999999;
		
				for(j=0;j<size_wp;j++)
				{
					if(j==0)
					{		
						if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[j]->Get_class_no())	
						{
							min_pro=mem_product_whole[j]->Get_price();
							min_id=j;
							ncon=1;
						}
						
					}
					else
					{
				//	 if(i==13 && k==1) printf("min_pro=%d material_no=%d class_no=%d mem_product_whole[%d]=%d price=%d \n",min_pro,mem_retailer[i]->Get_material_no(k),mem_product_whole[j]->Get_class_no(),j,mem_product_whole[j]->Get_Agent_no(),mem_product_whole[j]->Get_price());
						if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[j]->Get_class_no())
						{
							 if(min_pro > mem_product_whole[j]->Get_price())
							{
								min_pro=mem_product_whole[j]->Get_price();
								min_id=j;
								ncon=1;
							}
						}
					}
				}
				if(ncon==0) {mem_retailer[i]->Set_re_buy(z);}
				if(ncon==1)
				{
					del_pw=mem_product_whole.begin();
					for(m=0;m<size_wp;m++)
					{
						if(m==min_id)
						{
							break;
						}
						del_pw++;
						x++;
					}
					//削除すべき対象をiteraterで指定する
					if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[min_id]->Get_class_no())
					{
						//原料を１個購入し、当該原料の生産者に利益を立てる
//2011024				if(mem_retailer[i]->Get_genkin_zandaka()>=mem_product_whole[min_id]->Get_price())
						if(mem_retailer[i]->Get_genkin_suitoutyou_zandaka()+mem_retailer[i]->Get_yokin_suitoutyou_zandaka()>=mem_product_whole[min_id]->Get_price())
						{
							//所持金があれば購入する
							material_need=material_need-1;
							mem_retailer[i]->Deliv_material(mem_product_whole[min_id]);
								//購入した原料をmem_bought_pに格納する,	mem_bought_p.push_back(cp);
								price_w=mem_product_whole[min_id]->Get_price();
								p_gen=mem_product_whole[min_id]->Get_price_genka();
								mem_retailer[i]->Plus_buy_p(price_w);
								mem_retailer[i]->Set_material(price_w);
								mem_retailer[i]->Set_capital(capital);
								mem_retailer[i]->Set_shiwake_konyu(i_period,price_w);
//								mem_retailer[i]->Set_genkin(-price_w);
							//当該製品の生産者に利益を立てる
							for(l=0;l<size_w;l++)
							{
								if(mem_product_whole[min_id]->Get_Producer_no()==mem_whole[l]->Get_Producer_no())
								{
									mem_whole[l]->Set_rieki(mem_product_whole[min_id]->Get_price(),mem_product_whole[min_id]->Get_class_no());
									mem_whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
									mem_whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
									mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
//									mem_whole[l]->Set_yokin(price_w);
//									mem_bank[mem_whole[l]->Get_bank_no()]->Set_yokin(price_w);
								}
							}
							//売れた原料製品をmem_buy_wに格納し、mem_product_wholeから削除する
							mem_buy_w.push_back(mem_product_whole[min_id]);
							mem_product_whole.erase(del_pw);
							z++;
							goto restart;//material_need>0である限り購入を繰り返す
						}//if(capital>=mem_product_whole[min_id]->Get_price())の終わり
						else
						{
							//所持金が不足
							lack_money=int((material_need*mem_product_whole[min_id]->Get_price())*1.5);
							loan=mem_bank[mem_retailer[i]->Get_bank_no()]->loan_check(lack_money);//lack_money
							if(loan>0)
							{
								//銀行が貸出余力があるので借入れ成功
								//借り入れた資金で原料を購入する
								mem_retailer[i]->Set_shiwake_loan(i_period,lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan(i_period,lack_money);
								mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
//								mem_retailer[i]->Set_genkin(lack_money);
								mem_retailer[i]->Set_loan_s(lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(lack_money);
//								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_genkin(-lack_money);
								material_need=material_need-1;
								mem_retailer[i]->Deliv_material(mem_product_whole[min_id]);//購入した原料をmem_bought_pに格納する,	mem_bought_p.push_back(cp);
								price_w=mem_product_whole[min_id]->Get_price();
								p_gen=mem_product_whole[min_id]->Get_price_genka();
//								mem_retailer[i]->Set_genkin(-price_w);
								mem_retailer[i]->Set_material(price_w);
								mem_retailer[i]->Plus_buy_p(price_w);
								mem_retailer[i]->Set_shiwake_konyu(i_period,price_w);
								for(l=0;l<size_w;l++)
								{
									if(mem_product_whole[min_id]->Get_Producer_no()==mem_whole[l]->Get_Producer_no())
									{
										mem_whole[l]->Set_rieki(mem_product_whole[min_id]->Get_price(),mem_product_whole[min_id]->Get_class_no());
										mem_whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
										mem_whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
										mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
//										mem_whole[l]->Set_yokin(price_w);
//										mem_bank[mem_whole[l]->Get_bank_no()]->Set_yokin(price_w);
									}
									else	fprintf(test,"  ,  ,  ,  , %d , %d , check_r\n",mem_product_whole[min_id]->Get_Producer_no(),mem_whole[l]->Get_Producer_no());
								}
								mem_buy_w.push_back(mem_product_whole[min_id]);
								mem_product_whole.erase(del_pw);	//min_id番目の原料をmem_product_wholeから削除する
								z++;
								goto restart;
							}
							else
							{	//借入ができなかった、資金がないため原料を購入できない
								mem_retailer[i]->Set_capital(capital);//所持金をそのまま所持金とする

							}
						}

					}//if(mem_retailer[i]->Get_material_no(k)...の終わり					
					del_pw++;
					x++;
				}//if(ncon==1)の終わり
				else printf("check_ncon\n");
			}//if(material_need>0 && size_wp>0)の終わり
		}//for(k=0;k<ncr_p;k++),全ての原料について購買行動終了,
		
		//原料購買行動終わり
//		printf("konyuB r=%d gen=%d buy=%d\n",i,mem_retailer[i]->Get_genkin_zandaka(),mem_retailer[i]->Get_buy_p());
		mem_retailer[i]->Set_total_price_genka(mem_retailer[i]->Get_buy_p());
		mem_retailer[i]->Seisan_plan(price_k,first_price);
//20110224		mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,mem_retailer[i]->Get_genkin_zandaka());
//20110224		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,mem_retailer[i]->Get_genkin_zandaka());
		int taihi;
		taihi=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();
		mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,mem_retailer[i]->Get_genkin_suitoutyou_zandaka());
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);



		mem_retailer[i]->Seisan_revised();//各製品種別について製品をq個作る

		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();//生産する製品種別の数
		p_gen2=mem_retailer[i]->Get_total_price_genka()-mem_retailer[i]->Get_buy_p()-mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ();
		price_w=mem_retailer[i]->Get_buy_p();
		mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);
		mem_retailer[i]->Set_shiwake_seisan(i_period,p_gen2+price_w);

		for(j=0;j<ncr_p;j++)
		{
			hyouka_genka+=Get_Product_retailer(i,j);//i番目リテーラーからj番目種目の製品の納入をq個うけ,mem_productに格納する
			//mem_productには同一のリテーラー,製品種別の製品が連番で格納される
		}
		hyouka_genka-=(p_gen2+price_w);
		mem_retailer[i]->Set_shiwake_seisan(i_period,hyouka_genka);	//評価原価の誤差分
		mem_retailer[i]->Erase_retail_buy();
		fprintf(seisan,"\n-----------------------------------------------------------------------------\n");
		
	}

	cs->CM_Show_Production_retail_row(mem_product_whole.size());//CShowに機能移転、依存度が高ければ削除、機能は下の行の通り
	fprintf(cpara->FI_Get_market_product(),",");
	cs->CM_Show_Production_retail_row(mem_product.size());
	
//	fprintf(market_product," %d ",mem_product_whole.size());//上の行と一緒でなければ削除しないこと
}
/*
void CMarket::Production_retail_revised()
{
	int size,size_w;
	int i,j,k,l,m;int b=0;
	int ncr_p;int p_gen,p_gen2;
	int size_wp; int price_w;
	int material_need,depo_m;
	int x;
	int capital;
	int loan,lack_money;
	int ncon=0,min_pro=0,min_id;
	int hyouka_genka=0;
	int product_before=mem_product.size();
	vector <int> retailer_no;
	vector <int> ::iterator del_no;
		//min_pro:minimum price of product in the market
		//min_id:no of minimum price product in mem_product_whole
	vector <CProduct *>::iterator del_pw;
	size_wp=mem_product_whole.size();
	del_pw=mem_product_whole.begin();
	size=mem_retailer.size();
	size_w=mem_whole.size();


	cs->CM_Show_Production_retail_top(mem_product_whole.size());	//CShowに機能移譲、依存度高めなら削除、機能は下の行

	for(i=0;i<int(mem_retailer.size());i++)	retailer_no.push_back(i);
//	for(i=0;i<size;i++)
	int test_i;
	while(retailer_no.size()>0)
	{
		test_i=0;
		i=retailer_no[cr->strand(0,retailer_no.size()-1)];
		del_no=retailer_no.begin();
		for(int y=0;y<int(retailer_no.size());y++)	
		{
			if(retailer_no[y]==i)
			{
				del_no=retailer_no.erase(del_no);
				break;
			}
			test_i++;
			del_no++;
		}
	//	printf("size  %d\n",retailer_no.size());

		hyouka_genka=0;

		mem_retailer[i]->New_set_price();		//価格の決定
		mem_retailer[i]->Seisan_plan_revised(mem_product_whole,max_q_re,min_q_re,Adjustment_Sensitivity);
				//各製品種別毎に生産量qを決定する
		        //在庫がある場合には予定生産量-在庫を新規の生産量とする。
				//material_need=生産量とする
				//価格の改定は未


		depo_m=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
		capital=mem_retailer[i]->Get_yokin_suitoutyou_zandaka()+mem_retailer[i]->Get_genkin_suitoutyou_zandaka();//売上集計後の所有金額+depo_mを所有金額とする
		mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,depo_m);//預金を全額引き出す
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_m);

		//原料購買活動、原料を購入してをmem_bought_pに格納する
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(k=0;k<ncr_p;k++)
		{
			material_need=mem_retailer[i]->Get_material_need(k);
restart:
			del_pw=mem_product_whole.begin();
			size_wp=mem_product_whole.size();
			x=0;//count
			ncon=0;
			if(material_need>0 && size_wp>0)
			{	
				//当該製品種別の中で市場にある最低価格の原料を購入する
				//購入した原料をmem_product_wholeから削除する
				//当該製品種別の中で市場にある最低価格の原料を選出する, min_pro, min_idを決定する
				min_pro=9999999;
				for(j=0;j<size_wp;j++)
				{
					if(j==0)
					{		
						if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[j]->Get_class_no())	
						{
							min_pro=mem_product_whole[j]->Get_price();
							min_id=j;//printf("minid=%d , j=%d ,%d\n",min_id,j,mem_product_whole[min_id]->Get_price());
							ncon=1;
						}
					}
					else
					{
						if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[j]->Get_class_no())
						{
							if(min_pro > mem_product_whole[j]->Get_price())
							{
								min_pro=mem_product_whole[j]->Get_price();
								min_id=j;//printf("minid=%d , j=%d ,%d,min_pro=%d\n",min_id,j,mem_product_whole[min_id]->Get_price(),min_pro);
								ncon=1;
							}
						}
					}
				}

				if(ncon==1)
				{
					del_pw=mem_product_whole.begin();
					for(m=0;m<size_wp;m++)
					{
						if(m==min_id)
						{
							break;
						}
						del_pw++;
						x++;
					}
					//削除すべき対象をiteraterで指定する
					if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[min_id]->Get_class_no())
					{
						//原料を１個購入し、当該原料の生産者に利益を立てる
//20110222				if(mem_retailer[i]->Get_genkin_zandaka()>=mem_product_whole[min_id]->Get_price())
						if(mem_retailer[i]->Get_genkin_suitoutyou_zandaka()+mem_retailer[i]->Get_yokin_suitoutyou_zandaka()>=mem_product_whole[min_id]->Get_price())
						{
							//所持金があれば購入する
							material_need=material_need-1;
							mem_retailer[i]->Deliv_material(mem_product_whole[min_id]);
								//購入した原料をmem_bought_pに格納する,	mem_bought_p.push_back(cp);
								price_w=mem_product_whole[min_id]->Get_price();
								p_gen=mem_product_whole[min_id]->Get_price_genka();
								mem_retailer[i]->Set_material(price_w);
								mem_retailer[i]->Plus_buy_p(price_w);
								mem_retailer[i]->Set_capital(capital);
								mem_retailer[i]->Set_shiwake_konyu(i_period,price_w);
//								mem_retailer[i]->Set_genkin(-price_w);
							//当該製品の生産者に利益を立てる
							for(l=0;l<size_w;l++)
							{
								if(mem_product_whole[min_id]->Get_Producer_no()==mem_whole[l]->Get_Producer_no())
								{
									mem_whole[l]->Set_rieki(mem_product_whole[min_id]->Get_price(),mem_product_whole[min_id]->Get_class_no());
									mem_whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
									mem_whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
									mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
//									mem_whole[l]->Set_yokin(price_w);
//									mem_bank[mem_whole[l]->Get_bank_no()]->Set_yokin(price_w);
								}
							}
							//売れた原料製品をmem_buy_wに格納し、mem_product_wholeから削除する
							mem_buy_w.push_back(mem_product_whole[min_id]);
							mem_product_whole.erase(del_pw);
							goto restart;//material_need>0である限り購入を繰り返す
						}//if(capital>=mem_product_whole[min_id]->Get_price())の終わり
						else
						{
							//所持金が不足
							lack_money=int((material_need*mem_product_whole[min_id]->Get_price())*1.5);
							loan=mem_bank[mem_retailer[i]->Get_bank_no()]->loan_check(lack_money);//lack_money
							if(loan>0)
							{
								//銀行が貸出余力があるので借入れ成功
								//借り入れた資金で原料を購入する
								mem_retailer[i]->Set_shiwake_loan(i_period,lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan(i_period,lack_money);
								mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
//								mem_retailer[i]->Set_genkin(lack_money);
								mem_retailer[i]->Set_loan_s(lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(lack_money);
//								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_genkin(-lack_money);
								material_need=material_need-1;
								mem_retailer[i]->Deliv_material(mem_product_whole[min_id]);//購入した原料をmem_bought_pに格納する,mem_bought_p.push_back(cp);
								price_w=mem_product_whole[min_id]->Get_price();
								p_gen=mem_product_whole[min_id]->Get_price_genka();
//								mem_retailer[i]->Set_genkin(-price_w);
								mem_retailer[i]->Set_material(price_w);
								mem_retailer[i]->Plus_buy_p(price_w);
								mem_retailer[i]->Set_capital(capital);
								mem_retailer[i]->Set_shiwake_konyu(i_period,price_w);
								for(l=0;l<size_w;l++)
								{
									if(mem_product_whole[min_id]->Get_Producer_no()==mem_whole[l]->Get_Producer_no())
									{
										mem_whole[l]->Set_rieki(mem_product_whole[min_id]->Get_price(),mem_product_whole[min_id]->Get_class_no());
										mem_whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
										mem_whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
										mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
//										mem_whole[l]->Set_yokin(price_w);
//										mem_bank[mem_whole[l]->Get_bank_no()]->Set_yokin(price_w);
									}
									else	fprintf(test,"  ,  ,  ,  , %d , %d , check_r\n",mem_product_whole[min_id]->Get_Producer_no(),mem_whole[l]->Get_Producer_no());
								}
								mem_buy_w.push_back(mem_product_whole[min_id]);
								mem_product_whole.erase(del_pw);	//min_id番目の原料をmem_product_wholeから削除する
								goto restart;
							}
							else
							{	//借入ができなかった、資金がないため原料を購入できない
								mem_retailer[i]->Set_capital(capital);//所持金をそのまま所持金とする
							}
						}
					}//if(mem_retailer[i]->Get_material_no(k)...の終わり					
					del_pw++;
					x++;
				}//if(ncon==1)の終わり
			}//if(material_need>0 && size_wp>0)の終わり
		}//for(k=0;k<ncr_p;k++),全ての原料について購買行動終了,
		//原料購買行動終わり
		mem_retailer[i]->Set_total_price_genka(mem_retailer[i]->Get_total_price_genka());
		int taihi;
		taihi=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();
		mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);

		capital=0;
		mem_retailer[i]->Set_capital(capital);
		mem_retailer[i]->Calc_cost(q_limit_k,price_increase_rate,min_price_p,max_price_p,min_price_m,max_price_m);//各製品種別毎に改定価格を定義してpriceを更新する
		mem_retailer[i]->Renew_stock_price(mem_product);//売れ残り商品の価格を改定する
		mem_retailer[i]->Seisan_revised();
		if(mem_retailer[i]->Get_buy_p()==0){
			 p_gen2=mem_retailer[i]->Get_total_price_genka();
		}
		else{
			 p_gen2=mem_retailer[i]->Get_total_price_genka();
		}
		price_w=mem_retailer[i]->Get_buy_p();
		mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);

//		}
		mem_retailer[i]->Set_shiwake_seisan(i_period,p_gen2+mem_retailer[i]->Get_buy_p());
		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++)
		{
			hyouka_genka+=Get_Product_retailer_re(i,j);
		}
		hyouka_genka-=(p_gen2+mem_retailer[i]->Get_buy_p());
		mem_retailer[i]->Set_shiwake_seisan(i_period,hyouka_genka);
		mem_retailer[i]->Reset_buy_p();
	}

	cso->Set_price_tag(mem_product,mem_RP_tag);
	cs->Show_Product_tag(mem_RP_tag);
	cs->CM_Show_Production_retail_top(mem_product_whole.size());//CShowに機能移譲、依存度高めなら削除、機能は下の行
//	fprintf(market_product," %d ,",mem_product_whole.size());//上の行と一緒でなければ削除しないこと

	cs->CM_Show_Production_retail_row(mem_product.size()-product_before);//CShowに機能移譲、依存度高めなら削除、機能は下の行
//	fprintf(market_product," %d ",mem_product.size()-product_before);//上の行と一緒でなければ削除しないこと

/*
	for(i=0;i<size;i++)
	{
		hyouka_genka=0;

		mem_retailer[i]->New_set_price();		//価格の決定
		mem_retailer[i]->Seisan_plan_revised(mem_product_whole,max_q_re,min_q_re,Adjustment_Sensitivity);
				//各製品種別毎に生産量qを決定する
		        //在庫がある場合には予定生産量-在庫を新規の生産量とする。
				//material_need=生産量とする
				//価格の改定は未


		depo_m=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
		capital=mem_retailer[i]->Get_yokin_suitoutyou_zandaka()+mem_retailer[i]->Get_genkin_suitoutyou_zandaka();//売上集計後の所有金額+depo_mを所有金額とする
		mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,depo_m);//預金を全額引き出す
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_m);

		//原料購買活動、原料を購入してをmem_bought_pに格納する
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(k=0;k<ncr_p;k++)
		{
			material_need=mem_retailer[i]->Get_material_need(k);
restart:
			del_pw=mem_product_whole.begin();
			size_wp=mem_product_whole.size();
			x=0;//count
			ncon=0;
			if(material_need>0 && size_wp>0)
			{	
				//当該製品種別の中で市場にある最低価格の原料を購入する
				//購入した原料をmem_product_wholeから削除する
				//当該製品種別の中で市場にある最低価格の原料を選出する, min_pro, min_idを決定する
				min_pro=9999999;
				for(j=0;j<size_wp;j++)
				{
					if(j==0)
					{		
						if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[j]->Get_class_no())	
						{
							min_pro=mem_product_whole[j]->Get_price();
							min_id=j;//printf("minid=%d , j=%d ,%d\n",min_id,j,mem_product_whole[min_id]->Get_price());
							ncon=1;
						}
					}
					else
					{
						if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[j]->Get_class_no())
						{
							if(min_pro > mem_product_whole[j]->Get_price())
							{
								min_pro=mem_product_whole[j]->Get_price();
								min_id=j;//printf("minid=%d , j=%d ,%d,min_pro=%d\n",min_id,j,mem_product_whole[min_id]->Get_price(),min_pro);
								ncon=1;
							}
						}
					}
				}

				if(ncon==1)
				{
					del_pw=mem_product_whole.begin();
					for(m=0;m<size_wp;m++)
					{
						if(m==min_id)
						{
							break;
						}
						del_pw++;
						x++;
					}
					//削除すべき対象をiteraterで指定する
					if(mem_retailer[i]->Get_material_no(k)==mem_product_whole[min_id]->Get_class_no())
					{
						//原料を１個購入し、当該原料の生産者に利益を立てる
//20110222				if(mem_retailer[i]->Get_genkin_zandaka()>=mem_product_whole[min_id]->Get_price())
						if(mem_retailer[i]->Get_genkin_suitoutyou_zandaka()+mem_retailer[i]->Get_yokin_suitoutyou_zandaka()>=mem_product_whole[min_id]->Get_price())
						{
							//所持金があれば購入する
							material_need=material_need-1;
							mem_retailer[i]->Deliv_material(mem_product_whole[min_id]);
								//購入した原料をmem_bought_pに格納する,	mem_bought_p.push_back(cp);
								price_w=mem_product_whole[min_id]->Get_price();
								p_gen=mem_product_whole[min_id]->Get_price_genka();
								mem_retailer[i]->Set_material(price_w);
								mem_retailer[i]->Plus_buy_p(price_w);
								mem_retailer[i]->Set_capital(capital);
								mem_retailer[i]->Set_shiwake_konyu(i_period,price_w);
//								mem_retailer[i]->Set_genkin(-price_w);
							//当該製品の生産者に利益を立てる
							for(l=0;l<size_w;l++)
							{
								if(mem_product_whole[min_id]->Get_Producer_no()==mem_whole[l]->Get_Producer_no())
								{
									mem_whole[l]->Set_rieki(mem_product_whole[min_id]->Get_price(),mem_product_whole[min_id]->Get_class_no());
									mem_whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
									mem_whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
									mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
//									mem_whole[l]->Set_yokin(price_w);
//									mem_bank[mem_whole[l]->Get_bank_no()]->Set_yokin(price_w);
								}
							}
							//売れた原料製品をmem_buy_wに格納し、mem_product_wholeから削除する
							mem_buy_w.push_back(mem_product_whole[min_id]);
							mem_product_whole.erase(del_pw);
							goto restart;//material_need>0である限り購入を繰り返す
						}//if(capital>=mem_product_whole[min_id]->Get_price())の終わり
						else
						{
							//所持金が不足
							lack_money=(material_need*mem_product_whole[min_id]->Get_price())*1.5;
							loan=mem_bank[mem_retailer[i]->Get_bank_no()]->loan_check(lack_money);//lack_money
							if(loan>0)
							{
								//銀行が貸出余力があるので借入れ成功
								//借り入れた資金で原料を購入する
								mem_retailer[i]->Set_shiwake_loan(i_period,lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_loan(i_period,lack_money);
								mem_retailer[i]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
//								mem_retailer[i]->Set_genkin(lack_money);
								mem_retailer[i]->Set_loan_s(lack_money);
								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_loan_s(lack_money);
//								mem_bank[mem_retailer[i]->Get_bank_no()]->Set_genkin(-lack_money);
								material_need=material_need-1;
								mem_retailer[i]->Deliv_material(mem_product_whole[min_id]);//購入した原料をmem_bought_pに格納する,mem_bought_p.push_back(cp);
								price_w=mem_product_whole[min_id]->Get_price();
								p_gen=mem_product_whole[min_id]->Get_price_genka();
//								mem_retailer[i]->Set_genkin(-price_w);
								mem_retailer[i]->Set_material(price_w);
								mem_retailer[i]->Plus_buy_p(price_w);
								mem_retailer[i]->Set_capital(capital);
								mem_retailer[i]->Set_shiwake_konyu(i_period,price_w);
								for(l=0;l<size_w;l++)
								{
									if(mem_product_whole[min_id]->Get_Producer_no()==mem_whole[l]->Get_Producer_no())
									{
										mem_whole[l]->Set_rieki(mem_product_whole[min_id]->Get_price(),mem_product_whole[min_id]->Get_class_no());
										mem_whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
										mem_whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
										mem_bank[mem_whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
//										mem_whole[l]->Set_yokin(price_w);
//										mem_bank[mem_whole[l]->Get_bank_no()]->Set_yokin(price_w);
									}
									else	fprintf(test,"  ,  ,  ,  , %d , %d , check_r\n",mem_product_whole[min_id]->Get_Producer_no(),mem_whole[l]->Get_Producer_no());
								}
								mem_buy_w.push_back(mem_product_whole[min_id]);
								mem_product_whole.erase(del_pw);	//min_id番目の原料をmem_product_wholeから削除する
								goto restart;
							}
							else
							{	//借入ができなかった、資金がないため原料を購入できない
								mem_retailer[i]->Set_capital(capital);//所持金をそのまま所持金とする
							}
						}
					}//if(mem_retailer[i]->Get_material_no(k)...の終わり					
					del_pw++;
					x++;
				}//if(ncon==1)の終わり
			}//if(material_need>0 && size_wp>0)の終わり
		}//for(k=0;k<ncr_p;k++),全ての原料について購買行動終了,
		//原料購買行動終わり
		mem_retailer[i]->Set_total_price_genka(mem_retailer[i]->Get_total_price_genka());
		int taihi;
		taihi=mem_retailer[i]->Get_genkin_suitoutyou_zandaka();
		mem_retailer[i]->Set_shiwake_yokin_azuke(i_period,taihi);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);

		capital=0;
		mem_retailer[i]->Set_capital(capital);
		mem_retailer[i]->Calc_cost(q_limit_k,price_increase_rate,min_price_p,max_price_p,min_price_m,max_price_m);//各製品種別毎に改定価格を定義してpriceを更新する
		mem_retailer[i]->Renew_stock_price(mem_product);//売れ残り商品の価格を改定する
		mem_retailer[i]->Seisan_revised();
		if(mem_retailer[i]->Get_buy_p()==0){
			 p_gen2=mem_retailer[i]->Get_total_price_genka();
		}
		else{
			 p_gen2=mem_retailer[i]->Get_total_price_genka();
		}
		price_w=mem_retailer[i]->Get_buy_p();
		mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);
//		}
		mem_retailer[i]->Set_shiwake_seisan(i_period,p_gen2+mem_retailer[i]->Get_buy_p());
		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++)
		{
			hyouka_genka+=Get_Product_retailer_re(i,j);
		}
		hyouka_genka-=(p_gen2+mem_retailer[i]->Get_buy_p());
		mem_retailer[i]->Set_shiwake_seisan(i_period,hyouka_genka);
		mem_retailer[i]->Reset_buy_p();
	}

	cs->CM_Show_Production_retail_top(mem_product_whole.size());//CShowに機能移譲、依存度高めなら削除、機能は下の行
//	fprintf(market_product," %d ,",mem_product_whole.size());//上の行と一緒でなければ削除しないこと

	cs->CM_Show_Production_retail_row(mem_product.size()-product_before);//CShowに機能移譲、依存度高めなら削除、機能は下の行
//	fprintf(market_product," %d ",mem_product.size()-product_before);//上の行と一緒でなければ削除しないこと


}*/
void CMarket::Production_retail_revised()
{
	int size,size_w;
	int i,j;int b=0;
	int ncr_p;
	int p_gen2;
	int price_w;
	int capital;
	int hyouka_genka=0;
	int product_before=mem_product.size();
	int test_i;
	vector <int> retailer_no;
	vector <int> ::iterator del_no;
	vector <CProduct *>::iterator del_pw;
	del_pw=mem_product_whole.begin();
	size=mem_retailer.size();
	size_w=mem_whole.size();

	cso->Set_price_tag(mem_product_whole,mem_WP_tag);

	cs->CM_Show_Production_retail_top(mem_product_whole.size());	//CShowに機能移譲、依存度高めなら削除、機能は下の行

	for(i=0;i<int(mem_retailer.size());i++)	retailer_no.push_back(i);
	
	
	while(retailer_no.size()>0)
	{
		test_i=0;
		i=cf->Random_choice_int(retailer_no,del_no);

		hyouka_genka=0;

		mem_retailer[i]->New_set_price();		//価格の決定
		mem_retailer[i]->Seisan_plan_revised(mem_product_whole,max_q_re,min_q_re,Adjustment_Sensitivity);
				//各製品種別毎に生産量qを決定する
		        //在庫がある場合には予定生産量-在庫を新規の生産量とする。
				//material_need=生産量とする
				//価格の改定は未

		cs_3->PR__PR__Buy_material_retailer(mem_retailer,mem_whole,mem_bank,mem_WP_tag,mem_product_whole,del_pw,mem_buy_w,i,i_period);


		//原料購買行動終わり
		capital=0;
	//	mem_retailer[i]->Set_capital(capital);
		mem_retailer[i]->Calc_cost(q_limit_k,price_increase_rate,min_price_p,max_price_p,min_price_m,max_price_m);//各製品種別毎に改定価格を定義してpriceを更新する
		mem_retailer[i]->Renew_stock_price(mem_product);//売れ残り商品の価格を改定する
		mem_retailer[i]->Seisan_revised();

		if(mem_retailer[i]->Get_buy_p()==0)	 p_gen2=mem_retailer[i]->Get_total_price_genka();
		else	p_gen2=mem_retailer[i]->Get_total_price_genka();

		price_w=mem_retailer[i]->Get_buy_p();
		mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen2,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);
		mem_retailer[i]->Set_shiwake_seisan(i_period,p_gen2+mem_retailer[i]->Get_buy_p());

		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++)	hyouka_genka+=Get_Product_retailer_re(i,j);
		hyouka_genka-=(p_gen2+mem_retailer[i]->Get_buy_p());
		mem_retailer[i]->Set_shiwake_seisan(i_period,hyouka_genka);
		mem_retailer[i]->Reset_buy_p();
	}

	
	fprintf(cpara->FI_Get_statistic_product(),"\nR購買後（W製品販売）\n");
	cs->Show_Product_tag(mem_WP_tag);

	fprintf(cpara->FI_Get_statistic_product(),"\nR生産後\n");
	cso->Set_price_tag(mem_product,mem_RP_tag);	//リテイラーのプライスタグ作成
	cs->Show_Product_tag(mem_RP_tag);			//作成したプライスタグのプリント


	cs->CM_Show_Production_retail_top(mem_product_whole.size());//CShowに機能移譲、依存度高めなら削除、機能は下の行
//	fprintf(market_product," %d ,",mem_product_whole.size());//上の行と一緒でなければ削除しないこと
	cs->CM_Show_Production_retail_row(mem_product.size()-product_before);//CShowに機能移譲、依存度高めなら削除、機能は下の行
//	fprintf(market_product," %d ",mem_product.size()-product_before);//上の行と一緒でなければ削除しないこと
/*	fprintf(cpara->FI_Get_free_text(),"i_period=%d\n",i_period);
	if(i_period==5)
	{
		for(i=0;i<int(mem_WP_tag.size());i++)	fprintf(cpara->FI_Get_free_text(),"pr=%d , cl=%d , price=%d , nstock=%d\n",mem_WP_tag[i]->Get_Producer_no(),mem_WP_tag[i]->Get_class_no(),mem_WP_tag[i]->Get_price(),mem_WP_tag[i]->Get_nstock());
		for(i=0;i<int(mem_product_whole.size());i++) fprintf(cpara->FI_Get_free_text(),"pr=%d , cl=%d , price=%d\n",mem_product_whole[i]->Get_Producer_no(),mem_product_whole[i]->Get_class_no(),mem_product_whole[i]->Get_price());
	}
*/
}
int CMarket::Get_Product_retailer(int i,int j)
{
	//i番目リテーラーからj番目種目の製品の納入をq個うける
	int q;
	int class_no;
	int k;
	int ncon=0;
	int hyouka_genka=0;
		//q=mem_retailer[i]->Get_nop(j);
		q=mem_retailer[i]->Get_q(j);
		class_no=mem_retailer[i]->Get_class_no(j);
		for(k=0;k<q;k++)
		{
			cp=mem_retailer[i]->Get_product_fi(j,k);
			hyouka_genka+=cp->Get_price_genka();
			mem_product.push_back(cp);
		}
		if(k>0)cs->CM_Show_Get_Product_retailer(mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j),k);//CShowに機能移転、機能は下の行
			//fprintf(product_out," , %d , %d ,%d\n",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j),k-1);上の行と一緒でなければ削除しないこと

		else cs->CM_Show_Get_Product_retailer(mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j),k);//CShowに機能移転
			//fprintf(product_out," , %d , %d ,%d\n",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j),0);上の行と一緒でなければ削除しないこと
		return hyouka_genka;
}
int CMarket::Get_Product_retailer_re(int i,int j)
{
	//i番目リテーラーからj番目種目の製品の納入をq個うける
	int q;
	int class_no;
	int k;
	int total_genka=0;
	int hyouka_genka=0;
		q=mem_retailer[i]->Get_nop(j);
		class_no=mem_retailer[i]->Get_class_no(j);
		for(k=0;k<q;k++)
		{
			cp=mem_retailer[i]->Get_product(j,k);
			hyouka_genka+=cp->Get_price_genka();
			mem_product.push_back(cp);
		}
		if(k==0)k=1;
		cs->CM_Show_Get_Product_retailer(mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j),k-1);//CShowに機能移転、機能は下の行と同じ
//		fprintf(product_out," , %d , %d ,%d\n",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j),k-1);上の行と一緒でなければ削除しないこと
		return hyouka_genka;
}

int CMarket::Get_Product_wholesaler(int i,int j)
{
	//i番目リテーラーからj番目種目の製品の納入をうける
	//市場のwholesaler製品の集合mem_product_wholeに製品を格納する
	int q;
	int class_no;
	int k;
	int hyouka_genka=0;
		q=mem_whole[i]->Get_q(j);
		class_no=mem_whole[i]->Get_class_no(j);
		for(k=0;k<q;k++)
		{
			cp=mem_whole[i]->Get_product(j,k);
			cp->Set_state(1);
			hyouka_genka+=cp->Get_price_genka();
			mem_product_whole.push_back(cp);
		}
		return hyouka_genka;
}

void CMarket:: CReate_Consumer(int nconsumer)
{
	int i,depo;	int i_period=0;	int shihon;
	int size_b;
	size_b=mem_bank.size();
	for(i=0;i<nconsumer;i++)
	{
		Agent_no++;
		co=new CConsumer;
		co->Set_randum(cr);
		co->Set_parameter_class(cpara);
		co->Set_tax_class(cg->Get_CTax_class());

		co->Set_Agent_no(Agent_no);
		co->Set_Agent_type(10);
		co->Set_Consumer_no(Agent_no);
		co->Set_Consumer_type(10);
		co->Set_n_class(cpara->GET_PARA_n_class());
		co->Set_ncr_c(cr->strand(4,cpara->GET_PARA_nmax_c()));
		co->Create_Product_class_c(cpara->GET_PARA_max_memo_time(),cpara->GET_PARA_max_reac_flag());//ncr_c個のProduct_classのインスタンスを生成する
		co->Set_constant_wage(co->Def_income(cpara->GET_PARA_min_constant_wage(),cpara->GET_PARA_max_constant_wage()));
		co->Set_weight_buy();
		co->Set_bank_no(cr->strand(0,size_b-1));
		co->Set_deporate_decision_Coefficient(cpara->GET_PARA_threshold_deposit(),cpara->GET_PARA_deporate_coefficient());
		depo=cr->strand(cpara->GET_PARA_min_init_depo_c(),cpara->GET_PARA_max_init_depo_c());
		shihon=depo+(depo/10);
		co->Set_kisyu_shihon(shihon);
		co->Set_kisyu_zandaka();
		if(co->Get_Agent_no()==90){
			co->Set_nkessan(2);
			co->Set_ncase(2);
		}
		else{
			co->Set_nkessan(cpara->GET_PARA_nkessan());
			co->Set_ncase(cpara->GET_PARA_ncase());
		}
		mem_con.push_back(co);
		mem_con[i]->Set_shiwake_shihon(i_period,depo/10,depo);
		mem_bank[mem_con[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);
	}


	fprintf(cpara->FI_Get_phenom_writer(),"\n消費者の生成\n");
	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"create consumer: , agent_no=%d , agent_type=%d , genkin=%d , yokin=%d , ",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_Agent_type(),mem_con[i]->Get_genkin_suitoutyou_zandaka(),mem_con[i]->Get_yokin_suitoutyou_zandaka());
		fprintf(cpara->FI_Get_phenom_writer(),"class size=%d , ",mem_con[i]->Get_ncr_c());
		fprintf(cpara->FI_Get_phenom_writer(),"\n\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
}
void CMarket::CReate_Wholesaler(int nwholesaler)
{
	//各wholesaler毎に生産製品種別数ncr_p個を定義し、ncr_p個のProduct_classのインスタンスmem_class_pを生成する
	//ncr_p個の製品種別インスタンスに製品種別番号を割りつける
	int i;	int i_period=0;	int shihon;
	int count=0;
	int size_b;int depo;
	size_b=mem_bank.size();
	for(i=0;i<nwholesaler;i++)
	{
		Agent_no++;
		wh=new CWholesaler;
		wh->Set_randum(cr);							//乱数クラスの設定
		wh->Set_parameter_class(cpara);				//パラメータクラスの設定
		wh->Set_tax_class(cg->Get_CTax_class());	//Taxクラスの設定

		wh->Set_IC();//takashima_new
		wh->Set_Agent_no(Agent_no);
		wh->Set_Agent_type(30);//30=生産者向け生産者
		wh->Set_Producer_no(Agent_no);//その製品を生産したエージェントの番号
		wh->Set_Producer_type(30);
		
		wh->Set_n_class(cpara->GET_PARA_n_class());//市場にある製品種別の最大数
		wh->Set_ncr_p(cpara->GET_PARA_nmax_p());//cr->strand(cpara->GET_PARA_nmax_p_min(),cpara->GET_PARA_nmax_p()));//生産種別数
		wh->Set_ncr_c(5);
		wh->Create_mem_buy_retailer_product_data();				//企業の購買情報プロダクトクラスデータの生成
		wh->Create_Product_class_p(cpara->GET_PARA_max_memo_time(),cpara->GET_PARA_max_reac_flag());//ncr_p個のProduct_classのインスタンスmem_class_pを生成する
		
		//wh->Set_class_no_p();//ncr_p個の製品種別インスタンスに製品種別番号を割りつける
		count=wh->Set_class_no_p(count);
		
		wh->Def_hendouhi(cpara->GET_PARA_min_hendouhi(),cpara->GET_PARA_max_hendouhi());//生産者の各製品種別毎に1製品当たりの製造原価 hendouhi の設定、400～500の乱数
		wh->Def_koteihi(cpara->GET_PARA_min_koteihi(),cpara->GET_PARA_max_koteihi());//生産者の各製品種別の1製品当たりの固定費 koteihi の設定、8000～10000の乱数
		wh->Set_bank_no(cr->strand(0,size_b-1));
		
		depo=cr->strand(cpara->GET_PARA_min_init_depo_w(),cpara->GET_PARA_max_init_depo_w());//min_init_depo_w=20000,max_init_depo_w=80000
		shihon=depo+(depo/10);
		wh->Set_kisyu_shihon(shihon);
		wh->Set_kisyu_zandaka();
		wh->Set_bonus(0);
		wh->Labor_reset_keihi();

		if(wh->Get_Agent_no()==4)
		{
			wh->Set_ncase(2);
			wh->Set_nkessan(2);
		}
		else
		{
			wh->Set_ncase(cpara->GET_PARA_ncase());
			wh->Set_nkessan(cpara->GET_PARA_nkessan());
		}
		mem_whole.push_back(wh);
		mem_whole[i]->Set_loan_s(0);
		mem_whole[i]->Set_loan_l(0);
		mem_whole[i]->Set_shiwake_shihon(i_period,depo/10,depo);
		mem_bank[mem_whole[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);
	}
	int size;
	int j;
	size=mem_whole.size();
	fprintf(cpara->FI_Get_phenom_writer(),"\nホールセラーの生成\n");
	for(i=0;i<size;i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"create whole: , agent_no=%d , agent_type=%d , genkin=%d , yokin=%d\n",mem_whole[i]->Get_Agent_no(),mem_whole[i]->Get_Agent_type(),mem_whole[i]->Get_genkin_suitoutyou_zandaka(),mem_whole[i]->Get_yokin_suitoutyou_zandaka());
		fprintf(cpara->FI_Get_phenom_writer(),"class size=%d , ",mem_whole[i]->Get_mem_class_p_size());
		for(j=0;j<mem_whole[i]->Get_mem_class_p_size();j++)	fprintf(cpara->FI_Get_phenom_writer(),"class_no=%d , ",mem_whole[i]->Get_class_no(j));
		fprintf(cpara->FI_Get_phenom_writer(),"\n\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
}
void CMarket::Create_Equipment(int nequipment)
{
	int i,depo;	int i_period=0;	int shihon;
	int size_b;
	size_b=mem_bank.size();
	for(i=0;i<nequipment;i++)
	{
		Agent_no++;
		ce=new CEquipment;
		ce->Set_randum(cr);
		ce->Set_parameter_class(cpara);
		ce->Set_tax_class(cg->Get_CTax_class());
		ce->Set_IC();
		ce->Set_Agent_no(Agent_no);
		ce->Set_Agent_type(40);
		ce->Set_Producer_no(Agent_no);
		ce->Set_Producer_type(40);
		

		ce->Def_hendouhi(cpara->GET_PARA_min_hendouhi(),cpara->GET_PARA_max_hendouhi());
		ce->Def_koteihi(cpara->GET_PARA_min_koteihi(),cpara->GET_PARA_max_koteihi());
		ce->Set_bank_no(cr->strand(0,size_b-1));
		depo=cr->strand(cpara->GET_PARA_min_init_depo_e(),cpara->GET_PARA_max_init_depo_e());
		shihon=depo+(depo/10);
		ce->Set_kisyu_shihon(shihon);	
		ce->Set_kisyu_zandaka();
		ce->Set_ncase(cpara->GET_PARA_ncase());
		ce->Set_nkessan(cpara->GET_PARA_nkessan());

		ce->Set_ncase(2);
		ce->Set_nkessan(2);

		ce->Set_bonus(0);
		mem_equip.push_back(ce);
		mem_equip[i]->Set_shiwake_shihon(i_period,depo/10,depo);
		mem_bank[mem_equip[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);
	}


	fprintf(cpara->FI_Get_phenom_writer(),"\n設備製造の生成\n");
	for(i=0;i<int(mem_equip.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"create equip: , agent_no=%d , agent_type=%d , genkin=%d , yokin=%d\n",mem_equip[i]->Get_Agent_no(),mem_equip[i]->Get_Agent_type(),mem_equip[i]->Get_genkin_suitoutyou_zandaka(),mem_equip[i]->Get_yokin_suitoutyou_zandaka());
		fprintf(cpara->FI_Get_phenom_writer(),"\n\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\n");
}
void CMarket::CReate_Bank(int nbank)
{
	int i; int i_period=0;
	long long bank_capital;//bank資産別変数型化用意
	for(i=0;i<nbank;i++)
	{
		Agent_no++;
		cb=new CBank;
		bank_capital=cr->strand_l(cpara->GET_PARA_min_bank_capital(),cpara->GET_PARA_max_bank_capital());
		cb->Set_tax_class(cg->Get_CTax_class());
		cb->Set_randum(cr);
		cb->Set_parameter_class(cpara);
printf("test\n");
		cb->Set_IC(bank_capital);//銀行初期条件設定
		cb->Set_parameter();
		cb->Set_Agent_no(Agent_no);
		cb->Set_Agent_type(50);	
		

		
		cb->Set_kisyu_shihon_l(bank_capital);
printf("test\n");
		
		if(cb->Get_Agent_no()==1)
		{
			cb->Set_ncase(2);
			cb->Set_nkessan(2);
		}
		else
		{
			cb->Set_ncase(cpara->GET_PARA_ncase());
			cb->Set_nkessan(cpara->GET_PARA_nkessan());
		}

		cb->Set_kisyu_zandaka_l();
		cb->Set_bonus(0);
		mem_bank.push_back(cb);
		mem_bank[i]->Set_shiwake_shihon(i_period,bank_capital,0);
	}printf("test\n");
	for(i=0;i<int(mem_bank.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"create bank: , Agent_no=%d , agent_type=%d , genkin=%d\n",mem_bank[i]->Get_Agent_no(),mem_bank[i]->Get_Agent_type(),mem_bank[i]->Get_genkin_suitoutyou_zandaka());
	}
#if _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
}
void CMarket::CReate_Retailer(int nretailer)
{
	int i,j,depo;	int i_period=0;	int shihon;
	int size_b;
	size_b=mem_bank.size();
	for(i=0;i<nretailer;i++)
	{
		Agent_no++;
		re=new CRetailer;

		re->Set_parameter_class(cpara);	//パラメータクラスのセット
		re->Set_tax_class(cg->Get_CTax_class());
		re->Set_randum(cr);				//ランダムクラスのセット
		
		//共通化可能部分
		re->Set_n_class(cpara->GET_PARA_n_class());
		//
		re->Set_IC();
		re->Set_Agent_no(Agent_no);
		re->Set_Agent_type(20);
		re->Set_Producer_no(Agent_no);
		re->Set_Producer_type(20);
		
		
		re->Def_koteihi(cpara->GET_PARA_min_koteihi(),cpara->GET_PARA_max_koteihi());
		re->Set_bank_no(cr->strand(0,size_b-1));

		re->Set_ncr_p(cpara->GET_PARA_nmax_p());
		re->Set_ncr_c(5);
		re->Create_Product_class_p(cpara->GET_PARA_max_memo_time(),cpara->GET_PARA_max_reac_flag());
		//ncr_p個のProduct_classのインスタンスを生成し、mem_class_pに格納する
		re->Create_mem_buy_retailer_product_data();			//企業の購買情報プロダクトクラスデータの生成
//		if(re->Get_Agent_no()==7 || re->Get_Agent_no()==8)
		if(re->Get_Agent_no()==23)
		{
			re->Set_nkessan(2);
			re->Set_ncase(2);
		}
		else{
			re->Set_nkessan(2);//(cpara->GET_PARA_nkessan());
			re->Set_ncase(2);//(cpara->GET_PARA_ncase());
		}

		depo=cr->strand(cpara->GET_PARA_min_init_depo_r(),cpara->GET_PARA_max_init_depo_r());
		shihon=depo+(depo/10);
		
		re->Set_kisyu_shihon(shihon);
		re->Set_kisyu_zandaka();

		re->Set_bonus(0);
		re->Set_bankr_p(0);
		re->Set_buy_p(0);
		re->Reset_loan_time();
		re->Set_loan_time_limit(cpara->GET_PARA_loan_time_limit());
		re->Labor_reset_keihi();
		mem_retailer.push_back(re);
		mem_retailer[i]->Set_shiwake_shihon(i_period,depo/10,depo);
		mem_bank[mem_retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,depo);
		mem_retailer[i]->Set_shiwake_buy_retailer_product(0,0);
		init_r.push_back(mem_retailer[i]->Get_Producer_no());
	}

	
	fprintf(cpara->FI_Get_phenom_writer(),"\nリテイラーの生成\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"create whole: , agent_no=%d , agent_type=%d , genkin=%d , yokin=%d\n",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_Agent_type(),mem_retailer[i]->Get_genkin_suitoutyou_zandaka(),mem_retailer[i]->Get_yokin_suitoutyou_zandaka());
		fprintf(cpara->FI_Get_phenom_writer(),"class size=%d , ",mem_retailer[i]->Get_mem_class_p_size());
		for(j=0;j<mem_retailer[i]->Get_mem_class_p_size();j++)	fprintf(cpara->FI_Get_phenom_writer(),"class_no=%d , ",mem_retailer[i]->Get_class_no(j));
		fprintf(cpara->FI_Get_phenom_writer(),"\n\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\n");

}
void CMarket::CReate_Government()
{
	cg=new CGovernment;
	cg->Set_IC();
	cg->Set_parameter_class(cpara);
	cg->Set_Agent_no(99999);
	cg->Set_Agent_type(99999);
	cg->Create_tax_class();
	cg->Set_randum(cr);
	cg->Set_ncase(cpara->GET_PARA_ncase());
	cg->Set_nkessan(cpara->GET_PARA_nkessan());
	cg->Set_kisyu_zandaka();
	cg->Set_bonus(0);
//	cg->Set_genkin(20000);
	cg->Set_shiwake_zeisyu(i_period,20000);
	cg->Set_F_show_tax(cpara->FI_Get_show_tax());

	fprintf(cpara->FI_Get_phenom_writer(),"エージェントの生成\n");
	fprintf(cpara->FI_Get_phenom_writer(),"create gobernment: , no:%d , type:%d \n",cg->Get_Agent_no(),cg->Get_Agent_type());
}
void CMarket::Define_seizou()
{
	int i,j;	int size_r,size_c;
	size_r=mem_retailer.size();
	size_c=mem_con.size();
	for(i=0;i<size_r;i++)
	{
//		mem_retailer[i]->Set_class_no_p(mem_ncr_r);//ncr_p個の製品種別インスタンスに製品種別番号を割りつける
//		mem_retailer[i]->Set_material_no(mem_ncr_w);//製品種別毎にmem_ncr_wの中から原料を１つ指定する。
		mem_retailer[i]->Set_class_no_p(mem_ncr_r,mem_ncr_r_m);
	}
	for(i=0;i<size_c;i++)
	{
		mem_con[i]->Set_class_no_c(mem_ncr_r);
	}
	for(i=0;i<size_r;i++)	mem_retailer[i]->Set_class_buy_retailer_data(mem_ncr_r);
	for(i=0;i<int(mem_whole.size());i++)	mem_whole[i]->Set_class_buy_retailer_data(mem_ncr_r);


	//======================phenom===============================
	fprintf(cpara->FI_Get_phenom_writer(),"\nリテイラー生産品種と必要原料\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"retailer_no=%d: , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d ,  必要原料:%d ,",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_material_no(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}

	fprintf(cpara->FI_Get_phenom_writer(),"\n消費者購買品種\n");
	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"cons_no=%d: , ",mem_con[i]->Get_Agent_no());
		for(j=0;j<mem_con[i]->Get_ncr_c();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d , ",mem_con[i]->Get_buy_class_no(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\nリテイラー購買品種\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"retailer_no=%d: , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_class_buy_retailer_data_size();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d , ",mem_retailer[i]->Get_buy_retailer_data_class_no(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
	fprintf(cpara->FI_Get_phenom_writer(),"\nホールセラー購買品種\n");
	for(i=0;i<int(mem_whole.size());i++)
	{
		fprintf(cpara->FI_Get_phenom_writer(),"wholesaler_no=%d: , ",mem_whole[i]->Get_Agent_no());
		for(j=0;j<mem_whole[i]->Get_class_buy_retailer_data_size();j++)
		{
			fprintf(cpara->FI_Get_phenom_writer(),"class=%d , ",mem_whole[i]->Get_buy_retailer_data_class_no(j));
		}
		fprintf(cpara->FI_Get_phenom_writer(),"\n");
	}
	//======================phenom===============================

}



void CMarket::Show_statics_retailer()
{
	int i;
	int size,size_w;
	size=mem_retailer.size();
	for(i=0;i<size;i++)
	{
		mem_retailer[i]->Def_price_statics(mem_class_statics);
		mem_retailer[i]->Def_stock_price_statics(mem_class_stock_statics);
		mem_retailer[i]->Show_price_statics();//生産者の生産量、価格、購入商品の平均価格、在庫商品の最低価格	
	}
	
	size_w=mem_whole.size();
	size=mem_class_statics_w.size();
	for(i=0;i<size_w;i++)
	{
		mem_whole[i]->Def_price_statics(mem_class_statics_w);
		mem_whole[i]->Def_stock_price_statics(mem_class_stock_statics_w);
		mem_whole[i]->Show_price_statics();
	}

}



void CMarket::Pay_tax()
{
	int i;	int tax;
//	printf("tax_dataaaaaaaaaaaaaaaa %d\n",cg->Get_genkin_zandaka());


	for(i=0;i<int(mem_con.size());i++){
//		mem_con[i]->Tax_calc(mem_con[i]->Get_rieki_ac());
		tax=mem_con[i]->Get_tax();
		mem_con[i]->Set_shiwake_syotoku_tax(i_period,tax);
		cg->Collect_tax(tax);
		cg->Set_taxdate(i_period,920,tax);
		cg->Set_shiwake_zeisyu(i_period,tax);
	}

	cs_3->KI__KE__Pay_producer_tax(mem_whole,mem_bank,cg,i_period);
	cs_3->KI__KE__Pay_producer_tax(mem_retailer,mem_bank,cg,i_period);
	cs_3->KI__KE__Pay_producer_tax(mem_equip,mem_bank,cg,i_period);


	for(i=0;i<int(mem_bank.size());i++){
		tax=mem_bank[i]->Get_tax();
		mem_bank[i]->Set_shiwake_houzin_tax(i_period,tax);
		cg->Collect_tax(tax);
		cg->Set_taxdate(i_period,910,tax);
		cg->Set_shiwake_zeisyu(i_period,tax);
	}

	cg->Show_Tax_revenue();
//	cg->tax_change();
	
	//printf("pay_tax\n");
}

void CMarket::Show_tax()
{
	if(i_period==0) cg->Show_Tax_revenue();
}



void CMarket::Gov_investment()
{
	double invest_ratio=gov_invest_ratio;

	int g_genkin=0;
	int g_buy_max_price=0;
	int g_invest_money=0;
	int b_t_i=0;
	int min_price=0;

	int invest_count=0;

	int i,k,l,m,b=0;
	int size_r,size_w,size_e,size_inw;
	int size_p,size_pw;
	int ni,nicon;
	int c_n,c_q;
	int pro_price;
	int cap_b=0,res=0;
	double kk;
	int invest_counter=0;
	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	size_e=mem_equip.size();
	vector <int> inw;
	vector <int>::iterator p;
	vector <int> inw_r;
	vector <int> inw_w;
	vector <int> e_uriage;
	for(i=0;i<size_e;i++) e_uriage.push_back(0);
	//------------------------------------
	int no_r=0;//投資retailerの数
	int invest_money_r=0;//retailerの投資金総額
	int no_w=0;//投資wholesalerの数
	int invest_money_w=0;//wholesalerの投資金総額

	//g_genkin=//cg->Get_genkin_zandaka();
	g_invest_money=cg->Get_toushi_yosan();//g_genkin*invest_ratio;

	printf("g_inv=%d , inv_ratio=%lf\n",g_invest_money,invest_ratio);
//printf("before  g_genkin=%d ,   invest=%d\n",g_genkin,invest_money);
	while(g_invest_money>invest_money)
	{
		
		for(i=0;i<size_r;i++)
		{
			inw.push_back(mem_retailer[i]->Get_Producer_no());
		}
		for(i=0;i<size_w;i++)
		{
			inw.push_back(mem_whole[i]->Get_Producer_no());
		}

		//投資要求のあるエージェントをランダムに選ぶ
	//	for(j=0;j<invest_max;j++)//一期での選定数
	//	{
			size_inw=inw.size();
			if(size_inw>0)
			{

				size_p=mem_product.size();
				size_pw=mem_product_whole.size();
				
				ni=cr->strand(0,size_inw-1);
				i=inw[ni];//投資機会のあるエージェント番号
				p=inw.begin();
				nicon=0;
				for(k=0;k<size_inw;k++)
				{
					if(nicon==ni) 
					{
						inw.erase(p);
					}	
					p++;nicon++;
				}
					//選ばれたエージェントがホールセラーの場合
				if(i<=mem_whole[size_w-1]->Get_Producer_no())
				{
					inw_w.push_back(i);
					for(l=0;l<size_w;l++)
					{
						if(mem_whole[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_whole[l]->Get_g_eqw_no();//投資対象の製品種別番号を返す
							c_q=mem_whole[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);//投資後の最大生産量comp_qと投資金額pro_priceを定義する
							pro_price=mem_equip[m]->Get_project_price();//投資に必要なお金の額
							kk=1;
							no_w++;
							mem_equip[m]->Set_rieki(pro_price);
//							cg->Set_genkin(-pro_price);
							cg->Set_shiwake_invest(i_period,pro_price);
							mem_whole[l]->Set_q_limit(mem_equip[m]->Get_comp_q(),c_n,min_q_limit);
//							printf("loan=%d pro_price=%d\n",loan,pro_price);
							mem_whole[l]->Set_shiwake_setubi(i_period,pro_price,pro_price);
							e_uriage[m]+=pro_price;
							mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
							mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
//							mem_equip[m]->Set_yokin(pro_price);//+pro_price
//							mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
							g_invest_money=g_invest_money-pro_price;
							invest_count++;
//							i_count++;
						}								
					}
				}
				else
				{
					inw_r.push_back(i);//選ばれたエージェントがリテイラ
					for(l=0;l<size_r;l++)
					{
						if(mem_retailer[l]->Get_Producer_no()==i)
						{
							m=cr->strand(0,size_e-1);
							c_n=mem_retailer[l]->Get_g_eqw_no();
							c_q=mem_retailer[l]->Get_class_q_limit(c_n);
							mem_equip[m]->Estimate(c_q,capa_increase_rate,invest_money);
							pro_price=mem_equip[m]->Get_project_price();
							no_r++;
								mem_equip[m]->Set_rieki(pro_price);
								mem_retailer[l]->Up_equipment_revel(c_n);
//								cg->Set_genkin(-pro_price);
								cg->Set_shiwake_invest(i_period,pro_price);
								mem_retailer[l]->Set_shiwake_setubi(i_period,pro_price,pro_price);//長期借入⇒預金引出⇒設備
								e_uriage[m]+=pro_price;
//								mem_equip[m]->Set_yokin(pro_price);//+pro_price
								mem_equip[m]->Set_shiwake_yokin_azuke(i_period,pro_price);
//								mem_bank[mem_equip[m]->Get_bank_no()]->Set_yokin(pro_price);
								mem_bank[mem_equip[m]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,pro_price);
								g_invest_money=g_invest_money-pro_price;
//								i_count++;	
								invest_count++;
	
																
							
						}
					}
				}
		}
	}
	fprintf(gyousei_syouhisya," - , ");

	for(i=0;i<size_e;i++)
	{
		mem_equip[i]->Set_shiwake_seisan(i_period,mem_equip[i]->Get_koteihi());
		mem_equip[i]->Set_shiwake_uriage(i_period,e_uriage[i],mem_equip[i]->Get_koteihi());
	}

//	for(i=0;i<inw_r.size();i++) fprintf(invest," %d ,",inw_r[i]);for(i=0;i<inw_w.size();i++) fprintf(invest," %d ,",inw_w[i]);fprintf(invest,"\n");

}
void CMarket::Buy_government()
{
	switch(cpara->Get_PARA_Labor_assignment_switch())
	{
	case 0:
		cs_3->B__BG__Buy_government(cg,mem_retailer,mem_bank,mem_RP_tag,mem_product,del_p,mem_buy,i_period);
		break;

	case 1:
		cs_3->B__BG__Buy_government_assignment(cg,mem_retailer,mem_bank,mem_RP_tag,mem_product,del_p,mem_buy,i_period);
		break;
	}

}

void CMarket::Suply_pay_wage()
{
	fprintf(cpara->FI_Get_Labor_housyu_out(),"%d , ",i_period);
	Suply_pay_producer(mem_retailer);
	Suply_pay_producer(mem_whole);
	Suply_pay_producer(mem_equip);
	Suply_pay_wage_b();
	Suply_pay_wage_g();

	fprintf(cpara->FI_Get_Labor_housyu_out(),"\n");
}

/*
void CMarket::Buy_government()
{
	int i,j;
	int g_genkin;
	int size_product,size_r;
	int buy_g,p_gen;
	int check;
	int g_buy_max_price=0;
	int buy_no;
	int b_t_i=0;
	int min_price=0;
	size_r=mem_retailer.size();
	size_product=mem_product.size();
	g_genkin=cg->Get_genkin_zandaka();
	printf("uuuuuuuu=%d\n",g_genkin);
	for(i=0;i<size_product;i++)//市場内最大価格の算出
	{
		if(i==0) g_buy_max_price=mem_product[i]->Get_price();
		else{
			if(g_buy_max_price<mem_product[i]->Get_price())
			{
				g_buy_max_price=mem_product[i]->Get_price();
			}
		}
	}
	g_buy_max_price=g_buy_max_price*5;//念のため、市場内最大価格の5倍計算(この金額を行政資金が下回らないように購買)
	printf("buy_max=%d , g_genkin=%d\n",g_buy_max_price,g_genkin);
	check=0;
	while(cg->Get_genkin_zandaka() > g_buy_max_price && mem_product.size()>1)
	{
	//	printf("toppppppp\n");
		b_t_i++;
		buy_no=cr->strand(0,mem_product.size()-1);
		del_p=mem_product.begin();

		for(i=0;i<buy_no;i++)
		{
			del_p++;
		}
		for(j=0;j<mem_retailer.size();j++)
		{
			if(mem_product[buy_no]->Get_Producer_no()==mem_retailer[j]->Get_Producer_no())
			{
				mem_retailer[j]->Set_rieki(mem_product[buy_no]->Get_price(),mem_product[buy_no]->Get_class_no());
				check=1;
				buy_g=mem_product[buy_no]->Get_price();
		//		printf("%d\n",mem_product[buy_no]->Get_price());
				p_gen=mem_product[buy_no]->Get_price_genka();
				mem_retailer[j]->Set_shiwake_uriage(i_period,buy_g,p_gen);
				mem_retailer[j]->Set_shiwake_yokin_azuke(i_period,buy_g);
				mem_bank[mem_retailer[j]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_g);
				mem_retailer[j]->Set_yokin(buy_g);
				mem_bank[mem_retailer[j]->Get_bank_no()]->Set_yokin(buy_g);
				cg->Set_genkin(-buy_g);
				mem_retailer[j]->Erase_material();
			}
		}
		if(check==0) cb->In_capital(mem_product[buy_no]->Get_price());
		mem_buy.push_back(mem_product[buy_no]);
		mem_product.erase(del_p);
		g_genkin=cg->Get_genkin_zandaka();
	//	printf("bot  buy_time=%d , genkin=%d , gbuy=%d , size=$d\n",b_t_i,g_genkin,g_buy_max_price,mem_product.size());
//		if(g_genkin < g_buy_max_price){ break;}
	}

	size_product=mem_product.size();
//	fprintf(market_product," ,%d \n",size_product);
	for(i=0;i<size_r;i++) mem_retailer[i]->Reset_buy_p();
	printf("after_g_buy=====%d\n",cg->Get_genkin_zandaka());

}
*/
/*
void CMarket::Buy_government()
{
	int i,j;
	int g_genkin;
	int size_product,size_r;
	int buy_g,p_gen;
	int check;
	int g_buy_max_price=0;
	int buy_no;
	int b_t_i=0;
	int min_price=0;
	int g_money;
	int sum_buy=0;
	size_r=mem_retailer.size();
	size_product=mem_product.size();
	g_genkin=cg->Get_genkin_zandaka();
	g_money=cg->Get_koubai_yosan();
	printf("uuuuuuuu=%d\n",g_genkin);
	for(i=0;i<size_product;i++)//市場内最大価格の算出
	{
		if(i==0) g_buy_max_price=mem_product[i]->Get_price();
		else{
			if(g_buy_max_price<mem_product[i]->Get_price())
			{
				g_buy_max_price=mem_product[i]->Get_price();
			}
		}
	}
	g_buy_max_price=g_buy_max_price*2;//念のため、市場内最大価格の5倍計算(この金額を行政資金が下回らないように購買)
	printf("buy_max=%d , g_genkin=%d\n",g_buy_max_price,g_genkin);
	
	check=0;
	while(g_money > g_buy_max_price && mem_product.size()>1)
	{
	//	printf("toppppppp\n");
		b_t_i++;
		buy_no=cr->strand(0,mem_product.size()-1);
		del_p=mem_product.begin();

		for(i=0;i<buy_no;i++)
		{
			del_p++;
		}
		for(j=0;j<mem_retailer.size();j++)
		{
			if(mem_product[buy_no]->Get_Producer_no()==mem_retailer[j]->Get_Producer_no())
			{
				mem_retailer[j]->Set_rieki(mem_product[buy_no]->Get_price(),mem_product[buy_no]->Get_class_no());
				check=1;
				buy_g=mem_product[buy_no]->Get_price();
		//		printf("%d\n",mem_product[buy_no]->Get_price());
				p_gen=mem_product[buy_no]->Get_price_genka();
				mem_retailer[j]->Set_shiwake_uriage(i_period,buy_g,p_gen);
				mem_retailer[j]->Set_shiwake_yokin_azuke(i_period,buy_g);
				mem_bank[mem_retailer[j]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_g);
				mem_retailer[j]->Set_yokin(buy_g);
				mem_bank[mem_retailer[j]->Get_bank_no()]->Set_yokin(buy_g);
				cg->Set_genkin(-buy_g);
				g_money=g_money-buy_g;
				sum_buy+=buy_g;
				mem_retailer[j]->Erase_material();
			}
		}
		if(check==0) 	cb->In_capital(mem_product[buy_no]->Get_price());
		
		mem_buy.push_back(mem_product[buy_no]);
		mem_product.erase(del_p);
//		g_genkin=cg->Get_genkin_zandaka();
	//	printf("bot  buy_time=%d , genkin=%d , gbuy=%d , size=$d\n",b_t_i,g_genkin,g_buy_max_price,mem_product.size());
//		if(g_genkin < g_buy_max_price){ break;}
	}

	size_product=mem_product.size();
	fprintf(market_product," ,%d \n",size_product);
	fprintf(gyousei_syouhisya,"%d　, %d\n",sum_buy, cg->Get_genkin_zandaka());
	for(i=0;i<size_r;i++) mem_retailer[i]->Reset_buy_p();
	printf("after_g_buy=====%d\n",cg->Get_genkin_zandaka());
}
*/

////////////////////////現在未使用関数郡/////////////
/*void CMarket::Set_con_money()
{
	int i,j,k,size;
	int p=30000;
	size=mem_con.size();
	for(i=0;i<size;i++){
		mem_con[i]->Set_genkin(-mem_con[i]->Get_genkin_zandaka());
		mem_con[i]->Set_yokin(mem_con[i]->Get_genkin_zandaka());
		if(mem_con[i]->Get_yokin_zandaka() != p)
		{
			j=mem_con[i]->Get_genkin_zandaka()+mem_con[i]->Get_yokin_zandaka();
			k=p-j;
			mem_con[i]->Set_yokin(k);
		}
//		printf("k=%d yokin=%d \n",k,mem_con[i]->Get_yokin_zandaka());
	}
}*/







/*
void CMarket::Show_static_mem_buy_w()
{

	int i;
	int size;
	double sum=0;
	size=mem_class_statics_w.size();
	fprintf(out,"size of mem_class_statics_whole for mem_buy =,%4d, \n",size);
	fprintf(out1,"size of mem_class_statics_whole for mem_buy =,%4d, \n",size);
	for(i=0;i<size;i++)
	{
		fprintf(out,"class_no=,%3d, max_price=,%6d, min_price=,%6d, ave_price=,%6.1f, ndata=,%6d,\n",
			mem_class_statics_w[i]->Get_class_no(),mem_class_statics_w[i]->Get_max_price(),mem_class_statics_w[i]->Get_min_price(),mem_class_statics_w[i]->Get_ave_price(),mem_class_statics_w[i]->Get_ndata());
		fprintf(out1,"class_no=,%3d, max_price=,%6d, min_price=,%6d, ave_price=,%6.1f, ndata=,%6d,\n",
		mem_class_statics_w[i]->Get_class_no(),mem_class_statics_w[i]->Get_max_price(),mem_class_statics_w[i]->Get_min_price(),mem_class_statics_w[i]->Get_ave_price(),mem_class_statics_w[i]->Get_ndata());
//		fprintf(test3,"%d , %d , %d , %.0f , , ",mem_class_statics_w[i]->Get_class_no(),mem_class_statics_w[i]->Get_max_price(),mem_class_statics_w[i]->Get_min_price(),mem_class_statics_w[i]->Get_ave_price());
		fprintf(product_price_w,"%6.1lf,",mem_class_statics_w[i]->Get_ave_price());
		sum+=mem_class_statics_w[i]->Get_ave_price();
	}
//	fprintf(test3,"\n");
	if(size!=0) fprintf(product_price_w,"%6.1lf\n",sum/size);
}
*/
/*void CMarket::Show_statics_mem_buy()
{
	int i;
	int size;
	double sum=0;
	size=mem_class_statics.size();
	fprintf(out,"size of mem_class_statics for mem_buy =%4d \n",size);
	fprintf(out1,"size of mem_class_statics for mem_buy =%4d \n",size);
	for(i=0;i<size;i++)
	{
		fprintf(out,"class_no=,%3d, max_price=,%6d, min_price=,%6d, ave_price=,%6.1f, ndata=,%6d,\n",mem_class_statics[i]->Get_class_no(),mem_class_statics[i]->Get_max_price(),mem_class_statics[i]->Get_min_price(),mem_class_statics[i]->Get_ave_price(),mem_class_statics[i]->Get_ndata());
		fprintf(out1,"class_no=%3d max_price=%6d min_price=%6d ave_price=%6.1f ndata=%6d\n",mem_class_statics[i]->Get_class_no(),mem_class_statics[i]->Get_max_price(),mem_class_statics[i]->Get_min_price(),mem_class_statics[i]->Get_ave_price(),mem_class_statics[i]->Get_ndata());
		fprintf(test3,"%d , %d , %d , %.0f , , ",mem_class_statics[i]->Get_class_no(),mem_class_statics[i]->Get_max_price(),mem_class_statics[i]->Get_min_price(),mem_class_statics[i]->Get_ave_price());
		fprintf(product_price," %6.1lf,",mem_class_statics[i]->Get_ave_price());
		sum+=mem_class_statics[i]->Get_ave_price();
	}
	fprintf(test3,"\n");
	fprintf(product_price,"%6.1lf\n",sum/size);
	
/*	sum=0;
	size=mem_class_statics_w.size();
	fprintf(out,"size of mem_class_statics_whole for mem_buy =%4d \n",size);
	fprintf(out1,"size of mem_class_statics_whole for mem_buy =%4d \n",size);
	for(i=0;i<size;i++)
	{
		fprintf(out,"class_no=%3d max_price=%6d min_price=%6d ave_price=%6.1f ndata=%6d\n",
			mem_class_statics_w[i]->Get_class_no(),mem_class_statics_w[i]->Get_max_price(),mem_class_statics_w[i]->Get_min_price(),mem_class_statics_w[i]->Get_ave_price(),mem_class_statics_w[i]->Get_ndata());
		fprintf(out1,"class_no=%3d max_price=%6d min_price=%6d ave_price=%6.1f ndata=%6d\n",
		mem_class_statics_w[i]->Get_class_no(),mem_class_statics_w[i]->Get_max_price(),mem_class_statics_w[i]->Get_min_price(),mem_class_statics_w[i]->Get_ave_price(),mem_class_statics_w[i]->Get_ndata());
	//	fprintf(test3,"%d , %d , %d , %f , , ",mem_class_statics_w[i]->Get_class_no(),mem_class_statics_w[i]->Get_max_price(),mem_class_statics_w[i]->Get_min_price(),mem_class_statics_w[i]->Get_ave_price());
		fprintf(product_price_w,"%6.1lf,",mem_class_statics_w[i]->Get_ave_price());
		sum+=mem_class_statics_w[i]->Get_ave_price();
	}
	fprintf(test3,"\n");
	fprintf(product_price_w,"%6.1lf\n",sum/size);

}*/
/*
void CMarket::Show_statics_mem_product()
{
	//市場の売れ残り商品の統計データを表示する
	int i;
	int size,size_w;
	double sum=0;
	size=mem_class_stock_statics.size();
	size_w=mem_class_stock_statics_w.size();
	fprintf(out,"size of mem_class_stock_statics =,%4d, \n",size);
	fprintf(out1,"size of mem_class_stock_statics =%4d \n",size);
	fprintf(out,"size of mem_class_stock_statics_whole =,%4d, \n",size_w);
	fprintf(out1,"size of mem_class_stock_statics_whole =%4d \n",size_w);
	for(i=0;i<size;i++)
	{
	//	fprintf(test,"class_no=%3d max_price_stock=%6d min_price_stock=%6d ave_price_stock=%6.1f ndata_stock=%6d\n",
	//		mem_class_stock_statics[i]->Get_class_no(),mem_class_stock_statics[i]->Get_max_price_stock(),mem_class_stock_statics[i]->Get_min_price_stock(),mem_class_stock_statics[i]->Get_ave_price_stock(),mem_class_stock_statics[i]->Get_ndata_stock());
	//	fprintf(out1,"class_no=%3d max_price_stock=%6d min_price_stock=%6d ave_price_stock=%6.1f ndata_stock=%6d\n",
	//		mem_class_stock_statics[i]->Get_class_no(),mem_class_stock_statics[i]->Get_max_price_stock(),mem_class_stock_statics[i]->Get_min_price_stock(),mem_class_stock_statics[i]->Get_ave_price_stock(),mem_class_stock_statics[i]->Get_ndata_stock());

	}
}
*/


















//関数の墓場
/*
void CMarket::Re_Set_constant_wage_r(int i)
{
	int j,k;
	int new_constant_wage;
	int size_c,size_em;
	size_c=mem_con.size();
	size_em=mem_retailer[i]->Get_no_employ();//従業員数
	for(j=0;j<size_em;j++)
	{
		for(k=0;k<size_c;k++)
		{
			if(mem_retailer[i]->Get_employer(j)==mem_con[k]->Get_Consumer_no())
			{
				new_constant_wage=mem_con[k]->Get_constant_wage()*0.95;
				mem_retailer[i]->Set_employ_const_wage(new_constant_wage);
			}
		}
	}
}
void CMarket::Re_Set_constant_wage_w(int i)
{
	int j,k;
	int new_constant_wage;
	int size_c,size_em;
	size_c=mem_con.size();
	size_em=mem_whole[i]->Get_no_employ();//従業員数
	for(j=0;j<size_em;j++)
	{
		for(k=0;k<size_c;k++)
		{
			if(mem_whole[i]->Get_employer(j)==mem_con[k]->Get_Consumer_no())
			{
				new_constant_wage=mem_con[k]->Get_constant_wage()*0.95;
				mem_whole[i]->Set_employ_const_wage(new_constant_wage);
			}
		}
	}
}
void CMarket::Re_Set_constant_wage_e(int i)
{
	int j,k;
	int new_constant_wage;
	int size_c,size_em;
	size_c=mem_con.size();
	size_em=mem_equip[i]->Get_no_employ();//従業員数
	for(j=0;j<size_em;j++)
	{
		for(k=0;k<size_c;k++)
		{
			if(mem_equip[i]->Get_employer(j)==mem_con[k]->Get_Consumer_no())
			{
				new_constant_wage=mem_con[k]->Get_constant_wage()*0.95;
				mem_equip[i]->Set_employ_const_wage(new_constant_wage);
			}
		}
	}
}
void CMarket::Re_Set_constant_wage_b(int i)
{
	int j,k;
	int new_constant_wage;
	int size_c,size_em;
	size_c=mem_con.size();
	size_em=mem_bank[i]->Get_no_employ();//従業員数
	for(j=0;j<size_em;j++)
	{
		for(k=0;k<size_c;k++)
		{
			if(mem_bank[i]->Get_employer(j)==mem_con[k]->Get_Consumer_no())
			{
				new_constant_wage=mem_con[k]->Get_constant_wage()*0.95;
//				mem_bank[i]->Erase_employ_const_wage(i);
				mem_bank[i]->Set_employ_const_wage(new_constant_wage);
			}
		}
	}
}*/








///////ファイル出力系関数　頭文字Show//////////
/*
void CMarket::show_income()
{
	int size;
	int i;
	int c=0;
	int sum=0,sum_r=0,sum_w=0;
	size=mem_con.size();

	for(i=0;i<size;i++)
	{
		sum+=mem_con[i]->Get_income();
		if(mem_con[i]->Get_office_type()==20){ sum_r+=mem_con[i]->Get_income();c++;}
		else{ sum_w+=mem_con[i]->Get_income();}
//		printf("no=%3d income=%7d\n",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_income());
		fprintf(se_con," , , , , , , , , , , , , ,no=%3d income=%7d\n",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_income());
	}
	fprintf(se_income," , , , , , , , , , , , , , , ,sum=%9d  sum_r=%9d  sum_w=%9d\n",sum,sum_r,sum_w);

}

void CMarket::Show_balance()
{
	//現在は全体の大まかな数値表記用
	int i,j;
	int size_p,size_pw,size_c,size_r,size_w,size_e,size_b;
	int size_er=0,size_ew=0,size_ee=0,size_eb=0;
	int in_c,in_r,in_w,in_e,in_b;////各Agent利益額
	int income_c=0,income_r=0,income_w=0,income_e=0,income_b=0;//各Agent総利益額
	int gen_c,gen_r,gen_w,gen_e,gen_b;//各Agent現金額
	int genkin_c=0,genkin_r=0,genkin_w=0,genkin_e=0,genkin_b=0;//各Agent総現金額
	int ba_c=0,ba_r=0,ba_w=0,ba_e=0,ba_b;//各Agent預金額
	int bank_c=0,bank_r=0,bank_w=0,bank_e=0,bank_b=0;//各Agent総預金額
	int income_r_c=0,income_w_c=0,income_e_c=0,income_b_c=0,in_sum_c=0;//各Agentの支払う給与額
	int income_sum,genkin_sum,bank_sum;
	int bank_pro,res=0,sum_res=0;
	int st_r,st_w;
	int loan_s,loan_l,amount;
	int sum_loan_l=0,sum_loan_s=0;
	s_stock_r=0;s_stock_w=0;

	size_p=mem_product.size();
	size_pw=mem_product_whole.size();
	size_c=mem_con.size();
	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	size_e=mem_equip.size();
	size_b=mem_bank.size();

	for(i=0;i<size_p;i++){
		st_r=mem_product[i]->Get_price();
		s_stock_r+=st_r;
//		printf("i=%d size_p=%d stock_r=%d\n",i,size_p,st_r);
	}
	for(i=0;i<size_pw;i++){
		st_w=mem_product_whole[i]->Get_price();
		s_stock_w+=st_w;
//		printf("i=%d size_wp=%d stock_w=%d\n",i,size_pw,st_w);
	}
	printf("s_stock_r=%d , s_stock_w=%d\n",s_stock_r,s_stock_w);
	for(i=0;i<size_c;i++)
	{
		if(i_period==0) in_c=mem_con[i]->Get_income();
		else in_c=mem_con[i]->Get_rieki_ac();
		income_c+=in_c;
		gen_c=mem_con[i]->Get_genkin_zandaka();
		genkin_c+=gen_c;
		ba_c=mem_con[i]->Get_yokin_zandaka();
		bank_c+=ba_c;
//		printf("Agent_no=%d con=%d in_c=%d gen_c=%d ba_c=%d\n",mem_con[i]->Get_Agent_no(),i,in_c,gen_c,ba_c);
//		fprintf(Consumer,"%d, Agent_no=,%d, con=,%d, in_c=,%d, gen_c=,%d, ba_c=,%d\n",i_period,mem_con[i]->Get_Agent_no(),i,in_c,gen_c,ba_c);
	}
	if(i_period == 0) fprintf(loan,",");
	for(i=0;i<size_r;i++)
	{
		if(i_period==0) in_r=mem_retailer[i]->Get_capital();
		else in_r=mem_retailer[i]->Get_rieki_ac();
		income_r+=in_r;
		gen_r=mem_retailer[i]->Get_genkin_zandaka();
		genkin_r+=gen_r;
		ba_r=mem_retailer[i]->Get_yokin_zandaka();
		bank_r+=ba_r;
		loan_s=mem_retailer[i]->Get_loan_s_zandaka();
		loan_l=mem_retailer[i]->Get_loan_l_zandaka();
		sum_loan_l+=loan_l;	sum_loan_s+=loan_s;
		size_er+=mem_retailer[i]->Get_no_employ();
		income_r_c+=(mem_retailer[i]->Get_constant_wage()+mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ());
		if(i_period == 0) fprintf(loan,"%d,",mem_retailer[i]->Get_Agent_no());
//		printf("r=%d em=%d\n",i,size_er);mem_retailer[i]->Show_employ_no();
//		printf("Agent_no=%d retailer=%d in_r=%d gen_r=%d ba_r=%d\n",mem_con[i]->Get_Agent_no(),i,in_r,gen_r,ba_r);
//		fprintf(Retailer,"%d, Agent_no=,%d, retailer=,%d, in_r=,%d, gen_r=,%d, ba_r=,%d, employ=,%d, \n",i_period,mem_con[i]->Get_Agent_no(),i,in_r,gen_r,ba_r,mem_retailer[i]->Get_no_employ());
	}
	if(i_period == 0) fprintf(loan,",,");
	for(i=0;i<size_w;i++)
	{
		if(i_period==0) in_w=mem_whole[i]->Get_rieki();
		else in_w=mem_whole[i]->Get_rieki_ac();
		income_w+=in_w;
		gen_w=mem_whole[i]->Get_genkin_zandaka();
		genkin_w+=gen_w;
		ba_w=mem_whole[i]->Get_yokin_zandaka();
		bank_w+=ba_w;
		loan_s=mem_whole[i]->Get_loan_s_zandaka();
		loan_l=mem_whole[i]->Get_loan_l_zandaka();
		sum_loan_l+=loan_l;	sum_loan_s+=loan_s;
		size_ew+=mem_whole[i]->Get_no_employ();
		income_w_c+=(mem_whole[i]->Get_constant_wage()+mem_whole[i]->Get_bonus()*mem_whole[i]->Get_no_employ());
		if(i_period == 0) fprintf(loan,"%d,",mem_whole[i]->Get_Agent_no());
//		printf("w=%d\n",i);mem_whole[i]->Show_employ_no();
//		printf("Agent_no=%d whole=%d in_w=%d gen_w=%d ba_w=%d\n",mem_con[i]->Get_Agent_no(),i,in_w,gen_w,ba_w);
//		fprintf(Wholesaler,"%d, Agent_no=,%d, whole=,%d, in_w=,%d, gen_w=,%d, ba_w=,%d, employ=,%d,\n",i_period,mem_con[i]->Get_Agent_no(),i,in_w,gen_w,ba_w,mem_whole[i]->Get_no_employ());
	}
	if(i_period == 0) fprintf(loan,",,");
	for(i=0;i<size_e;i++)
	{
		if(i_period==0) in_e=mem_equip[i]->Get_rieki();
		else in_e=mem_equip[i]->Get_rieki_ac();
		income_e+=in_e;if(i_period==0) in_e=mem_equip[i]->Get_rieki();
		else in_e=mem_equip[i]->Get_rieki_ac();
		income_e+=in_e;
		gen_e=mem_equip[i]->Get_genkin_zandaka();
		genkin_e+=gen_e;
		ba_e=mem_equip[i]->Get_yokin_zandaka();
		loan_s=mem_equip[i]->Get_loan_s_zandaka();
		sum_loan_l+=loan_l;	sum_loan_s+=loan_s;
		size_ee+=mem_equip[i]->Get_no_employ();
		income_e_c+=(mem_equip[i]->Get_constant_wage()+mem_equip[i]->Get_bonus()*mem_equip[i]->Get_no_employ());
		if(i_period == 0) fprintf(loan,"%d,",mem_equip[i]->Get_Agent_no());
//		printf("e=%d\n",i);mem_equip[i]->Show_employ_no();
//		printf("Agent_no=%d equip=%d in_e=%d gen_e=%d ba_e=%d\n",mem_con[i]->Get_Agent_no(),i,in_e,gen_e,ba_e);
		fprintf(Equipment,"%d, Agent_no=,%d, equip=,%d, in_e=,%d, gen_e=,%d, ba_e=,%d, employ=,%d,\n",i_period,mem_con[i]->Get_Agent_no(),i,in_e,gen_e,ba_e,mem_equip[i]->Get_no_employ());
		bank_e+=ba_e;
	}
	if(i_period == 0) fprintf(loan,"\n");
	for(i=0;i<size_b;i++)
	{
		if(i_period==0) in_b=0;
		else in_b=mem_bank[i]->Get_rieki_ac();
		income_b+=in_b;
		gen_b=mem_bank[i]->Get_genkin_zandaka();
		genkin_b+=gen_b;
		ba_b=mem_bank[i]->Get_yokin_zandaka();
		bank_b+=ba_b;
		res+=mem_bank[i]->Get_reserve();
		amount=mem_bank[i]->Get_hensai();
		size_eb+=mem_bank[i]->Get_no_employ();
		income_b_c+=(mem_bank[i]->Get_constant_wage()+mem_bank[i]->Get_bonus());
//		printf("b=%d\n",i);mem_bank[i]->Show_employ_no();
//		printf("Agent_no=%d bank=%d in=%d gen=%d ban=%d res=%d\n",mem_bank[i]->Get_Agent_no(),i,in_b,gen_b,ba_b,res);
		fprintf(Bank,"%d, Agent_no=,%d, bank=,%d, in=,%d, gen=,%d, ban=,%d, res=,%d, employ=,%d,\n",i_period,mem_bank[i]->Get_Agent_no(),i,in_b,gen_b,ba_b,res,mem_bank[i]->Get_no_employ());
	}
	income_sum=income_c+income_r+income_w+income_e;
	genkin_sum=genkin_c+genkin_r+genkin_w+genkin_e;
	bank_sum=bank_c+bank_r+bank_w+bank_e;
	bank_pro=bank_r+bank_w+bank_e;
	in_sum_c=income_r_c+income_w_c+income_e_c+income_b_c;

	fprintf(market_data,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",income_c,income_r,income_w,income_e,genkin_c,bank_c,bank_r,bank_w,bank_e,bank_pro,bank_sum,sum_loan_s,sum_loan_l,sum_loan_s+sum_loan_l);
	fprintf(agent_no,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d \n",size_c,size_r,size_w,size_e,size_b,size_er,size_ew,size_ee,size_eb,size_er+size_ew+size_ee+size_eb);
/////////給与&loan
	int nn=0,x=0;
	fprintf(kyuyo,",%d,%d,%d,%d,%d,retailer,",income_r_c,income_w_c,income_e_c,income_b_c,in_sum_c);
	fprintf(loan,"retailer,");
	for(i=0;i<nretailer;i++){
		for(j=5;j<size_r+5;j++){
			if(i+j == mem_retailer[i]->Get_Agent_no()){
				if(i>=nretailer-x) break;
				fprintf(kyuyo,"%d,%d,",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_constant_wage());
				fprintf(loan,"%d,",mem_retailer[i]->Get_loan_s_zandaka());
				x=nn;
				break;
			}
			else{
				nn++;
				if(nn > x){
					fprintf(kyuyo," , ,");	fprintf(loan,"  ,");
				}
			}
		}
			nn=0;
	}
	fprintf(kyuyo,",whole,");	fprintf(loan,",whole,");
	for(i=0;i<size_w;i++){
		for(j=2;j<size_w+2;j++){
			if(i+j == mem_whole[i]->Get_Agent_no()){
				if(i>=nwholesaler-x) break;
				fprintf(kyuyo,"%d,%d,",mem_whole[i]->Get_Agent_no(),mem_whole[i]->Get_constant_wage());
				fprintf(loan,"%d,",mem_whole[i]->Get_loan_s_zandaka());
				x=nn;
				break;
			}
			else{
				nn++;
				if(nn > x){
					fprintf(kyuyo," , ,");	fprintf(loan,"  ,");
				}
			}
		}
			nn=0;
	}
	fprintf(kyuyo,"\n");	fprintf(loan,",equip,");
	for(i=0;i<size_e;i++) 	fprintf(loan,"%d,",mem_equip[i]->Get_loan_s_zandaka());
	fprintf(loan,"\n");
/////////

	printf("r_em=%d w_em=%d e_em=%d b_em=%d Employer= %d\n",size_er,size_ew,size_ee,size_eb,size_er+size_ew+size_ee+size_eb);
	printf("Consumer= %d , Retailer= %d , Wholesaler= %d , Equipment= %d , Bank= %d\n",size_c,size_r,size_w,size_e,size_b);
	printf("　　　 	   　　  利益　,　現金 ,  預金\n"); 
	printf("消費者		%3d , %3d , %3d\n",income_c,genkin_c,bank_c); 
	printf("リテイラー	%3d , %3d , %3d\n",income_r,genkin_r,bank_r); 
	printf("ホール		%3d , %3d , %3d\n",income_w,genkin_w,bank_w); 
	printf("設備		%3d , %3d , %3d\n",income_e,genkin_e,bank_e); 
	printf("銀行		%3d , %3d , %3d\n",income_b,genkin_b,bank_b);
//	printf("回数		%d\n",i_count);
	printf("消預%d , 企預%d , 預合%d ,短貸合%d , 長貸合%d , 総貸合%d\n",bank_c,bank_pro,bank_sum,sum_loan_s,sum_loan_l,sum_loan_s+sum_loan_l);
	printf("返合%d , 資金%d , 預金%d 銀行準備金%d\n",amount,genkin_b,bank_sum,res);
	printf("市場内総資金%d\n",genkin_sum+bank_sum+genkin_b);
//	printf("Agent預金%d , bank預金%d , \n",bank_sum,bank_b);//確認用

//	printf("引き出し%d , 預金=%d\n",mo_sum,ou_sum);mo_sum=0;ou_sum=0;
//	fprintf(bank_data," ,  ,  ,  ,  , %d , %d , %d , %d , %d , %d , %d , %d\n",sum_c,sum_p,sum,sum_loan,capital,sum_interest,p_loan,p_amount);
}

void CMarket::Show_bought_product_class()
{
	//購入された商品を製品種別毎に表示する
	//-------------------------------------
	int bought_sum_r;//その期に購入された小売製品の購入金額の合計（消費者需要）
	bought_sum_r=0;
	int bought_sum_w;//その期に購入された卸製品の購入金額の合計（原料需要）
	bought_sum_w=0;
	//-------------------------------------
	int i,j;
	int size_ncr;
	size_ncr=mem_ncr_r.size();//市場にある小売用製品種別番号の集合のサイズ
	int size;
	size=mem_buy.size();//その期に購入されたリテイラー商品の集合
//		fprintf(out,"size_ncr=%3d　mem_product.size=%3d \n",size_ncr,size);
//		fprintf(out,"size_product_wholesaler=%4d size_product_retailer=%4d \n",Get_product_size_wholesaler(),Get_product_size_retailer());
	int ncon;
	int njcon;
	int sum=0;
	for(i=0;i<size_ncr;i++)
	{
		ncon=0;//同一生産者同一製品種別の商品数のカウンター
		njcon=0;
		sum=0;
		for(j=0;j<size;j++)
		{
			if(mem_buy[j]->Get_class_no()==mem_ncr_r[i])
			{
				sum++;
			}
		}
	//	if(mem_ncr_r[i]==20)fprintf(test3,"%d , %d\n",mem_ncr_r[i],sum);
	}

	size_ncr=mem_ncr_r.size();
		fprintf(bought_pro,"size_ncr=%3d　mem_product.size=%3d \n",size_ncr,size);
		fprintf(bought_pro,"size_product_wholesaler=%4d size_product_retailer=%4d \n",Get_product_size_wholesaler(),Get_product_size_retailer());
	int size_r;
	int k;
	size_r=mem_retailer.size();
	for(i=0;i<size_r;i++)
	{
		size_ncr=mem_retailer[i]->Get_ncr_p();//各生産者が生産する製品種別の数
		for(j=0;j<size_ncr;j++)//市場にある小売用製品種別番号の集合のサイズ
		{
			ncon=0;
			for(k=0;k<size;k++)//size:その期に購入されたリテイラー商品の集合
			{
				if(mem_retailer[i]->Get_Producer_no()==mem_buy[k]->Get_Producer_no())
				{
					if(mem_retailer[i]->Get_class_no(j)==mem_buy[k]->Get_class_no())
						ncon++;//同一生産者、同一製品種別の購入製品数の合計
				}
			}
			bought_sum_r+=mem_retailer[i]->Get_price(j)*ncon;
			fprintf(bought_pro," producer_no= %3d  class_no= %6d price=%6d  genka= %3d  商品個数= %3d  material= %4d  q_limit= %3d  q=  %3d\n",mem_retailer[i]->Get_Producer_no(),mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_price(j),mem_retailer[i]->Get_genka(j),ncon,mem_retailer[i]->Get_material_no(j),mem_retailer[i]->Get_class_q_limit(j),mem_retailer[i]->Get_nop(j));
		}
	}
	size=mem_buy_w.size();
	size_r=mem_whole.size();
	for(i=0;i<size_r;i++)
	{
		size_ncr=mem_whole[i]->Get_ncr_p();
		for(j=0;j<size_ncr;j++)
		{
			ncon=0;
			for(k=0;k<size;k++)
			{
				if(mem_whole[i]->Get_Producer_no()==mem_buy_w[k]->Get_Producer_no())
				{
					if(mem_whole[i]->Get_class_no(j)==mem_buy_w[k]->Get_class_no())	ncon++;
				}
			}
			bought_sum_w+=mem_whole[i]->Get_price(j)*ncon;
			fprintf(bought_pro," producer_no= %3d  class_no= %6d price=%6d  genka= %3d  商品個数= %3d  material= %4d\n",mem_whole[i]->Get_Producer_no(),mem_whole[i]->Get_class_no(j),mem_whole[i]->Get_price(j),mem_whole[i]->Get_genka(j),ncon,mem_whole[i]->Get_material_no(j));
		}
	}
	fprintf(bought_money,",%d, %d, %d \n",bought_sum_r,bought_sum_w,bought_sum_r+bought_sum_w);
}

void CMarket::Show_economy()
{
	int i;
	int size;
	int eco=0;
	int mo;
	int ri;
	size=mem_con.size();
	for(i=0;i<size;i++)
	{
		eco+=mem_con[i]->Get_income();
	//	eco+=mem_con[i]->Get_yokin_zandaka();
	}
	size=mem_retailer.size();
	for(i=0;i<size;i++)
	{
		eco+=mem_retailer[i]->Get_capital();
	//	eco+=mem_retailer[i]->Get_yokin_zandaka();
	}
	size=mem_whole.size();
	for(i=0;i<size;i++)
	{
		ri=mem_whole[i]->Suply_pay_w();
		eco+=ri;
		mem_whole[i]->Set_rieki(ri);
	}
	size=mem_equip.size();
	for(i=0;i<size;i++)
	{
		ri=mem_equip[i]->Suply_pay_w();
		eco+=ri;
		mem_equip[i]->Set_rieki(ri);
	}
	mo=eco+cb->Get_capital();
//	printf("bank=%d\n",cb->Get_capital());
	fprintf(economy,"%d , %d\n",eco,mo);

	int p_size=mem_product.size();
	int size_r=mem_retailer.size();
	vector <int> ban_r;
	int j;
	bool checker=false;

	for(i=0;i<init_r.size();i++)
	{
		checker=false;
		for(j=0;j<mem_retailer.size();j++)
		{
			if(init_r[i]==mem_retailer[j]->Get_Producer_no()) checker=true;
		}
		if(checker==false) ban_r.push_back(init_r[i]);
	}

	for(i=0;i<ban_r.size();i++)
	{
		for(j=0;j<p_size;j++)
		{
//			printf("j:%d\n",j);
			if(mem_product[j]->Get_Producer_no()==ban_r[i]) fprintf(Retailer,"%d:%d\n",mem_product[i]->Get_Producer_no(),mem_product[i]->Get_price());
		}
	}

}





void CMarket::Show_gdp()
{
	int size_r,size_w,size_e,size_b,size_c,i;

	int uriage_total=0,zaiko_total_r=0,zaiko_total_w=0,zaiko_total=0;

	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	size_e=mem_equip.size();
	size_b=mem_bank.size();
	size_c=mem_con.size();

	int z;z=0;
	int uri_r=0,uri_e=0,uri_w=0,uri_b=0;
	int zaiko_r=0,zaiko_w=0;
	int ky_r=0,ky_w=0,ky_e=0,ky_b=0,ky_c=0;
	int bou_r=0,bou_w=0,bou_e=0,bou_b=0;
	int ri_r=0,ri_w=0,ri_b=0,ri_e=0;
	int genryou=0,setubi_r=0,setubi_w=0;
	int ukerisi_r=0,ukerisi_w=0,ukerisi_e=0,ukerisi_b=0,ukerisi_c=0;
	int siharisi_r=0,siharisi_w=0,siharisi_e=0,siharisi_b=0;
	int syoukyaku_r=0,syoukyaku_w=0;

//	fprintf(Retailer," ,  売上 , 製品在庫 , 左辺合計 ,  , 支払利息 , 原料 , 労務費 , 一般管理費 , 減価償却費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	uriage_total=0;
	zaiko_total_r=0;
	zaiko_total_w=0;
	int a,b,c,d,e,f,g,h,y;//a：給与,b：ボーナス、c：原料、d：設備、e、売上,
				        //f：受け取り利息、g：支払利息、h：減価償却、y：利益z：在庫
	for(i=0;i<size_r;i++)
	{
//		ky_r+=(mem_retailer[i]->Get_constant_wage()+mem_retailer[i]->Get_bonus());
		a=mem_retailer[i]->Get_kyuyo_out();
		ky_r+=a;
		b=mem_retailer[i]->Get_bonus_out();
		bou_r+=b;
		c=mem_retailer[i]->Get_genryou_out();
		genryou+=c;
//		genryou+=mem_retailer[i]->Get_genryou();
		d=mem_retailer[i]->Get_setubi_out();
		setubi_r+=d;
//		uri_r+=mem_retailer[i]->Get_uriagetotal();
		e=mem_retailer[i]->Get_uriage_out();
		uri_r+=e;
		z=mem_retailer[i]->Get_zaiko();
		zaiko_total_r+=z;
		f=mem_retailer[i]->Get_ukerisi_out();
		ukerisi_r+=f;
		g=mem_retailer[i]->Get_siharisi_out();
		siharisi_r+=g;
		h=mem_retailer[i]->Get_genkasyoukyaku_out();
		syoukyaku_r+=h;
//		if(i_period==0) ri_r+=mem_retailer[i]->Get_capital();
//		else ri_r+=mem_retailer[i]->Get_rieki_ac();
		y=mem_retailer[i]->Get_rieki_out();
		ri_r+=y;
		fprintf(ac_data1,"%d\n",y);
//		fprintf(Retailer,"%d , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d , %d ,  , %d\n",mem_retailer[i]->Get_Producer_no(),e,z,e+z,g-f,c,a,b,h,y,g-f+c+a+b+h+y,e+z-(g-f+c+a+b+h+y));
	}
//	fprintf(Retailer," , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d , %d ,  , %d\n",uri_r,zaiko_total_r,uri_r+zaiko_total_r,siharisi_r-ukerisi_r,genryou,ky_r,bou_r,syoukyaku_r,ri_r,siharisi_r-ukerisi_r+genryou+ky_r+bou_r+syoukyaku_r+ri_r,uri_r+zaiko_total_r-(siharisi_r-ukerisi_r+genryou+ky_r+bou_r+syoukyaku_r+ri_r));

//	fprintf(Retailer,"\n w \n ,  売上 , 製品在庫 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 減価償却費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	for(i=0;i<size_w;i++) 
	{
	//	ky_w+=(mem_whole[i]->Get_constant_wage()+mem_whole[i]->Get_bonus());
		a=mem_whole[i]->Get_kyuyo_out();
		ky_w+=a;
		b=mem_whole[i]->Get_bonus_out();
		bou_w+=b;
		z=mem_whole[i]->Get_zaiko_out();
		zaiko_total_w+=z;
	//	uri_w+=mem_whole[i]->Get_uriagetotal();
		e=mem_whole[i]->Get_uriage_out();
		uri_w+=e;
		d=mem_whole[i]->Get_setubi_out();
		setubi_w+=d;
		f=mem_whole[i]->Get_ukerisi_out();
		ukerisi_w+=f;
		g=mem_whole[i]->Get_siharisi_out();
		siharisi_w+=g;
		h=mem_whole[i]->Get_genkasyoukyaku_out();
		syoukyaku_w+=h;
//		if(i_period==0) ri_w+=mem_whole[i]->Get_rieki();
//		else ri_w=mem_whole[i]->Get_rieki_ac();
		y=mem_whole[i]->Get_rieki_out();
		ri_w+=y;
//		fprintf(Retailer,"%d , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d ,  , %d\n",mem_whole[i]->Get_Producer_no(),e,z,e+z,g-f,a,b,h,y,g-f+a+b+h+y,e+z-(g-f+a+b+h+y));
		
	}
//	fprintf(Retailer," , %d , %d , %d ,   , %d , %d , %d , %d , %d , %d ,  , %d\n",uri_w,zaiko_total_w,uri_w+zaiko_total_w,siharisi_w-ukerisi_w,ky_w,bou_w,syoukyaku_w,ri_w,siharisi_w-ukerisi_w+ky_w+bou_w+syoukyaku_w+ri_w,uri_w+zaiko_total_w-(siharisi_w-ukerisi_w+ky_w+bou_w+syoukyaku_w+ri_w));

//	fprintf(Retailer,"\n e \n ,  売上 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	for(i=0;i<size_e;i++)
	{
		a=mem_equip[i]->Get_kyuyo_out()-mem_equip[i]->Get_bonus_out();
		ky_e+=a;
		b=mem_equip[i]->Get_bonus_out();
		bou_e+=b;

	//	uri_e+=mem_equip[i]->Get_uriagetotal();
		e=mem_equip[i]->Get_uriage_out();
		uri_e+=e;
	//	ky_e+=(mem_equip[i]->Get_constant_wage()+mem_equip[i]->Get_bonus());
		f=mem_equip[i]->Get_ukerisi_out();
		ukerisi_e+=f;
		g=mem_equip[i]->Get_siharisi_out();
		siharisi_e+=g;
//		if(i_period==0) ri_e=mem_equip[i]->Get_rieki();
//		else ri_e+=mem_equip[i]->Get_rieki_ac();
		y=mem_equip[i]->Get_rieki_out();
		ri_e+=y;
//		fprintf(Retailer,"%d , %d , %d ,  , %d , %d , %d , %d , %d ,  , %d\n",mem_equip[i]->Get_Producer_no(),e,e,g-f,a,b,y,g-f+a+b+y,e-(g-f+a+b+y));
	}
//	fprintf(Retailer," , %d , %d ,  , %d , %d , %d  , %d , %d ,  , %d\n",uri_e,uri_e,siharisi_e-ukerisi_e,ky_e,bou_e,ri_e,siharisi_e-ukerisi_e+ky_e+bou_e+ri_e,uri_e-(siharisi_e-ukerisi_e+ky_e+bou_e+ri_e));

//	fprintf(Retailer,"\n b \n ,  売上 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 営業余剰 , 右辺合計 , , 右辺左辺合計\n");
	for(i=0;i<size_b;i++)
	{
		a=mem_bank[i]->Get_kyuyo_out();
		ky_b+=a;
		b=mem_bank[i]->Get_bonus_out();
		bou_b+=b;
	//	uri_b+=mem_bank[i]->Get_uriagetotal();
		e=mem_bank[i]->Get_uriage_out();
		uri_b+=e;
	//	ky_b+=(mem_bank[i]->Get_constant_wage()+mem_bank[i]->Get_bonus());
		f=mem_bank[i]->Get_ukerisi_out();
		ukerisi_b+=f;
		g=mem_bank[i]->Get_siharisi_out();
		siharisi_b+=g;
//		if(i_period==0) ri_b+=0;
//		else ri_b+=mem_bank[i]->Get_rieki_ac();
		y=mem_bank[i]->Get_rieki_out();
		ri_b+=y;
//		fprintf(Retailer,"b , %d , %d ,  , %d , %d , %d , %d , %d ,  , %d\n",f,f,g,a,b,y,g+a+b+y,f-(g+a+b+y));
	}
//	fprintf(Retailer," , %d , %d ,   , %d , %d , %d  , %d , %d ,  , %d\n",ukerisi_b,ukerisi_b,siharisi_b,ky_b,bou_b,ri_b,siharisi_b+ky_b+bou_b+ri_b,ukerisi_b-(siharisi_b+ky_b+bou_b+ri_b));
//	fprintf(Retailer,"\n\n");
/*
	for(i=0;i<size_c;i++)
	{
		ukerisi_c+=mem_con[i]->Get_ukerisi_out();
		fprintf(ac_data2,"%d\n",mem_con[i]->Get_kyuyo_c_out());
	}


	uriage_total=uri_r+uri_e-ukerisi_c;
	zaiko_total=zaiko_total_r+zaiko_total_w;
	fprintf(GDP,"%d,%d,%d\n",uriage_total,zaiko_total_r+zaiko_total_w,uriage_total+zaiko_total_r+zaiko_total_w);


	fprintf(zyunkandata," , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d\n",uri_r,zaiko_total_r,siharisi_r-ukerisi_r,genryou,ky_r,bou_r,syoukyaku_r,ri_r,uri_w,zaiko_total_w,siharisi_w-ukerisi_w,ky_w,bou_w,syoukyaku_w,ri_w,uri_e,siharisi_e-ukerisi_e,ky_e,bou_e,ri_e,ukerisi_b,siharisi_b,ky_b,bou_b,ri_b);	
//	fprintf(zyunkandata," ,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",uri_r,zaiko_total_r,ky_r,ukerisi_r,siharisi_r,ri_r,genryou,setubi_r,uri_w,zaiko_total_w,ky_w,ukerisi_w,siharisi_w,ri_w,setubi_w,uri_e,ky_e,ukerisi_e,siharisi_e,ri_e,uri_b,ky_b,ukerisi_b,siharisi_b,ri_b);

	int r_tyukanzyuyou=0,r_saisyuzyuyou=uri_r+zaiko_total_r;
	int r_tyukantounyu=genryou+siharisi_r-ukerisi_r,r_arahukakati=ky_r+bou_r+ri_r+syoukyaku_r;
	int w_tyukanzyuyou=genryou,w_saisyuzyuyou=zaiko_total_w;
	int w_tyukantounyu=siharisi_w-ukerisi_w,w_arahukakati=ky_w+bou_w+ri_w+syoukyaku_w;
	int e_tyukanzyuyou=0,e_saisyuzyuyou=uri_e;
	int e_tyukantounyu=siharisi_e-ukerisi_e,e_arahukakati=ky_e+bou_e+ri_e;
	int b_tyukanzyuyou=-ukerisi_r-ukerisi_w-ukerisi_e+siharisi_r+siharisi_w+siharisi_e,b_saisyuzyuyou=-ukerisi_c;
	int b_tyukantounyu=0,
		b_arahukakati=ky_b+bou_b+ri_b;
	int tyukan_kei;
	int saisyuzyuyou_kei=r_saisyuzyuyou+w_saisyuzyuyou+e_saisyuzyuyou+b_saisyuzyuyou;
	int arahukakati_kei=r_arahukakati+w_arahukakati+e_arahukakati+b_arahukakati;	
	if(r_tyukantounyu+w_tyukantounyu+e_tyukantounyu==r_tyukanzyuyou+w_tyukanzyuyou+e_tyukanzyuyou+b_tyukanzyuyou) tyukan_kei=r_tyukantounyu+w_tyukantounyu+e_tyukantounyu;
	else tyukan_kei=0;
	int zyuyou_gdp=tyukan_kei+saisyuzyuyou_kei;
	int tounyu_gdp=tyukan_kei+arahukakati_kei;
//                             r ,  w ,  e ,  b , 中 , 支 , 消 , 資 , 在 , 最 , 計
	fprintf(zyunkanhyou," r ,  - ,  - ,  - ,  - , %d ,  - , %d ,  - , %d , %d , %d \n",r_tyukanzyuyou,uri_r,zaiko_total_r,r_saisyuzyuyou,r_tyukanzyuyou+r_saisyuzyuyou);
	fprintf(zyunkanhyou," w , %d ,  - ,  - ,  - , %d ,  - ,  - ,  - , %d , %d , %d \n",genryou,w_tyukanzyuyou,zaiko_total_w,w_saisyuzyuyou,w_tyukanzyuyou+w_saisyuzyuyou);
	fprintf(zyunkanhyou," e ,  - ,  - ,  - ,  - , %d ,  - ,  - , %d ,  - , %d , %d \n",e_tyukanzyuyou,uri_e,e_saisyuzyuyou,e_tyukanzyuyou+e_saisyuzyuyou);
	fprintf(zyunkanhyou," b , %d , %d , %d ,  - , %d ,  - , %d ,  - ,  - , %d , %d \n",-ukerisi_r+siharisi_r,-ukerisi_w+siharisi_w,-ukerisi_e+siharisi_e,b_tyukanzyuyou,-ukerisi_c,b_saisyuzyuyou,b_saisyuzyuyou+b_tyukanzyuyou);
	fprintf(zyunkanhyou," 中間需要/計 , %d , %d , %d ,  - , %d ,  - ,  - ,  - ,  - , %d , %d \n",r_tyukantounyu,w_tyukantounyu,e_tyukantounyu,tyukan_kei,saisyuzyuyou_kei,zyuyou_gdp);
	fprintf(zyunkanhyou," 支出 ,  - ,  - ,  - ,  - ,  - \n",siharisi_r,siharisi_w,siharisi_e,siharisi_b,ukerisi_c);
	fprintf(zyunkanhyou," 雇用所得 , %d , %d , %d , %d  \n",ky_r+bou_r,ky_w+bou_w,ky_e+bou_e,ky_b+bou_b);
	fprintf(zyunkanhyou," 営業余剰 , %d , %d , %d , %d  \n",ri_r,ri_w,ri_e,ri_b);
	fprintf(zyunkanhyou," 減価償却費 , %d , %d ,  - ,  -  \n",syoukyaku_r,syoukyaku_w);
	fprintf(zyunkanhyou," 粗付加価値 , %d , %d , %d , %d , %d \n",r_arahukakati,w_arahukakati,e_arahukakati,b_arahukakati,arahukakati_kei);
	fprintf(zyunkanhyou," 計 ,  %d ,  %d ,  %d ,  %d , %d \n",r_tyukantounyu+r_arahukakati,w_tyukantounyu+w_arahukakati,e_tyukantounyu+e_arahukakati,b_tyukantounyu+b_arahukakati,tounyu_gdp );
	fprintf(zyunkanhyou,"\n goukei:%d\n",zyuyou_gdp-tounyu_gdp);


}

void CMarket::Show_kimatu_zandaka(int Agent_type)
{
	int size;int i;
	if(Agent_type==10){//Consumer
		size=mem_con.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_con[i]->Get_Agent_no());
			mem_con[i]->Show_kimatu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==20){//Retailer
		size=mem_retailer.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_retailer[i]->Get_Agent_no());
			mem_retailer[i]->Show_kimatu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==30){//Wholesaler
		size=mem_whole.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_whole[i]->Get_Agent_no());
			mem_whole[i]->Show_kimatu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==40){//Equipment
		size=mem_equip.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_equip[i]->Get_Agent_no());
			mem_equip[i]->Show_kimatu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==50){//Bank
		size=mem_bank.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_bank[i]->Get_Agent_no());
			mem_bank[i]->Show_kimatu_zandaka(Agent_type,out3);
		}
	}
	else
		fprintf(out3,"該当するエージェントが存在しません、Agent_typeを見直してください\n");
}

void CMarket::Show_kisyu_zandaka(int Agent_type)
{
	int size;int i;
	if(Agent_type==10){//Consumer
		size=mem_con.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_con[i]->Get_Agent_no());
			mem_con[i]->Show_kisyu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==20){//Retailer
		size=mem_retailer.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_retailer[i]->Get_Agent_no());
			mem_retailer[i]->Show_kisyu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==30){//Wholesaler
		size=mem_whole.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_whole[i]->Get_Agent_no());
			mem_whole[i]->Show_kisyu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==40){//Equipment
		size=mem_equip.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_equip[i]->Get_Agent_no());
			mem_equip[i]->Show_kisyu_zandaka(Agent_type,out3);
		}
	}
	else if(Agent_type==50){//Bank
		size=mem_bank.size();
		for(i=0;i<size;i++){
			fprintf(out3,"Agent_no=%3d ",mem_bank[i]->Get_Agent_no());
			mem_bank[i]->Show_kisyu_zandaka(Agent_type,out3);
		}
	}
	else
		fprintf(out3,"該当するエージェントが存在しません、Agent_typeを見直してください\n");
}


void CMarket::Show_market_product()
{

	int i,j;
	int size,p_size;
	double sum=0;
	size=mem_product_whole.size();
	p_size=mem_ncr_w.size();
	for(i=0;i<p_size;i++)
	{
		for(j=0;j<size;j++)
		{
		//	if(i==mem_product_whole[j]->Get_class_no())	fprintf(test,"class_no=%3d pro_no=%3d,price=%6d \n",mem_product[j]->Get_class_no(),mem_product[j]->Get_Producer_no(),mem_product[j]->Get_price());
		}
	}
}

void CMarket::Show_mem_ncr_r()
{
	int i;
	int size;
	size=mem_ncr_r.size();
	fprintf(out,"size=,%3d, mem_ncr_r= ",size);
	for(i=0;i<size;i++) fprintf(out,",%3d ",mem_ncr_r[i]);
	fprintf(out,"\n");
}

void CMarket::Show_mem_ncr_w()
{
	int i;
	int size;
	size=mem_ncr_w.size();
	fprintf(out,"size=,%3d, mem_ncr_w= ",size);
	for(i=0;i<size;i++)//9_11 printf("%3d ",mem_ncr_w[i]);
	for(i=0;i<size;i++) fprintf(out,",%3d, ",mem_ncr_w[i]);
	fprintf(out,"\n");
}

void CMarket::show_no_buy_code()
{
	int size,i;
	size=mem_con.size();
	for(i=0;i<size;i++) mem_con[i]->Get_no_buy_code();
}


void CMarket::Show_Product()
{
	int size;
	//int nsize;
	size=mem_product.size();
	int i;
//	int n_class;
	//int class_no;
	int Producer_no_old;
	int Producer_no_new;
//	int q;
	fprintf(out,"in show_product() size=%3d\n",size);
	for(i=0;i<size;i++)
	{
		if(i==0) Producer_no_old=mem_product[i]->Get_Producer_no();
		Producer_no_new=mem_product[i]->Get_Producer_no();
		if(Producer_no_new!=Producer_no_old)//9_11 printf("\n");
		fprintf(out,"Producer_no=,%3d ,ncr_p=,%3d, Producer_type=,%3d, class_no=,%3d, price=,%6d, lot_no=,%3d,",mem_product[i]->Get_Producer_no(),mem_product[i]->Get_ncr_p(),mem_product[i]->Get_Producer_type(),mem_product[i]->Get_class_no(),mem_product[i]->Get_price(),mem_product[i]->Get_lot_no());
		fprintf(out,"\n");
		Producer_no_old=Producer_no_new;
	}
}

void CMarket::Show_product_class()
{
	//製品種別ごとに製品の番号、価格、製造者番号をプリントアウトする。
	int i,j;
	int size_ncr;
	size_ncr=mem_ncr_r.size();
	int size;
	size=mem_product.size();
		//mem_productには同一のリテーラー,製品種別の製品が連番で格納されている
		fprintf(out,"size_ncr=,%3d,　mem_product.size=,%3d, \n",size_ncr,size);
		fprintf(out,"size_product_wholesaler=,%4d, size_product_retailer=,%4d, \n",Get_product_size_wholesaler(),Get_product_size_retailer());
	int producer_no0;
	int producer_no;
	int ncon;
	int njcon;
	int nj;
	fprintf(out,"inside Show_product_class size_ncr=,%d,\n",size_ncr);
	for(i=0;i<size_ncr;i++)//size_ncr=mem_ncr_r.size();
	{
		ncon=0;//同一生産者同一製品種別の商品数のカウンター
		njcon=0;
		for(j=0;j<size;j++)//size=mem_product.size();
		{
			if(mem_product[j]->Get_class_no()==mem_ncr_r[i])
			{
				
				njcon++;
				producer_no=mem_product[j]->Get_Producer_no();
				if(ncon==0)
				{
					producer_no0=producer_no;
				}
				if(producer_no==producer_no0)
				{
					ncon++;
					producer_no0=producer_no;
					nj=j;
					//if(i==0)	fprintf(out,"  j=%3d  class_no=%3d price=%6d price_genka=%6d producer=%3d 商品個数=%3d rieki=%7d njcon=%4d\n",j,mem_product[nj]->Get_class_no(),mem_product[nj]->Get_price(),mem_product[nj]->Get_price_genka(),mem_product[nj]->Get_Producer_no(),ncon,(mem_product[nj]->Get_price()-mem_product[nj]->Get_price_genka())*ncon,njcon);

					if(j==mem_product.size()-1 )
					{
						fprintf(out,"A class_no=,%3d, price=,%6d, price_genka=,%6d, producer=,%3d, 商品個数=,%3d, rieki=,%7d, njcon=,%4d\n",mem_product[nj]->Get_class_no(),mem_product[nj]->Get_price(),mem_product[nj]->Get_price_genka(),mem_product[nj]->Get_Producer_no(),ncon,(mem_product[nj]->Get_price()-mem_product[nj]->Get_price_genka())*ncon,njcon);
					}
				}
				else 
				{
					producer_no0=producer_no;
					fprintf(out,"B class_no=,%3d, price=,%6d, price_genka=,%6d, producer=,%3d, 商品個数=,%3d, rieki=,%7d, material_no=,%d\n",mem_product[nj]->Get_class_no(),mem_product[nj]->Get_price(),mem_product[nj]->Get_price_genka(),mem_product[nj]->Get_Producer_no(),ncon,(mem_product[nj]->Get_price()-mem_product[nj]->Get_price_genka())*ncon,mem_product[nj]->Get_material_no());
					ncon=1;
					nj=j;
					//if(i==0)	fprintf(out,"  j=%3d  class_no=%3d price=%6d price_genka=%6d producer=%3d 商品個数=%3d rieki=%7d njcon=%4d\n",j,mem_product[nj]->Get_class_no(),mem_product[nj]->Get_price(),mem_product[nj]->Get_price_genka(),mem_product[nj]->Get_Producer_no(),ncon,(mem_product[nj]->Get_price()-mem_product[nj]->Get_price_genka())*ncon,njcon);

				}
			}
			else if(j==mem_product.size()-1 && ncon!=0)
			{
					fprintf(out,"C class_no=,%3d, price=,%6d, price_genka=,%6d, producer=,%3d, 商品個数=,%3d, rieki=,%7d, material_no=,%d, njcon=,%4d\n",mem_product[nj]->Get_class_no(),mem_product[nj]->Get_price(),mem_product[nj]->Get_price_genka(),mem_product[nj]->Get_Producer_no(),ncon,(mem_product[nj]->Get_price()-mem_product[nj]->Get_price_genka())*ncon,mem_product[nj]->Get_material_no(),njcon);

			}
		}//for(j=0;j<size;j++)の終わり//size=mem_product.size();
	}//for(i=0;i<size_ncr;i++)の終わり
}

void CMarket::Show_retailer()
{
	//producer no,製品種別数、製品種別番号、それぞれの生産量、をﾌﾟﾘﾝﾄｱｳﾄする
	int size;
	int i,j;
	size=mem_retailer.size();
	for(i=0;i<size;i++) {
		fprintf(out,"producer_no=,%3d, ",mem_retailer[i]->Get_Agent_no());
		fprintf(out,"ncr_p=,%2d,   class_no= ",mem_retailer[i]->Get_ncr_p());
		for(j=0;j<mem_retailer[i]->Get_mem_class_p_size();j++){
			fprintf(out,",%2d, ",mem_retailer[i]->Get_class_no(j));
		}
		fprintf(out,"amount= ");
		for(j=0;j<mem_retailer[i]->Get_mem_class_p_size();j++){
			fprintf(out,",%d, ",mem_retailer[i]->Get_q(j));
		}
		fprintf(out,"price= ");
		for(j=0;j<mem_retailer[i]->Get_mem_class_p_size();j++){
			fprintf(out,",%d, ",mem_retailer[i]->Get_price(j));
		}
		fprintf(out,"\n");
	}
}
void CMarket::Show_termly_change(int i)
{
	//i番目期間の計算結果をプリントする
	int total_nstock;   //市場のトータル在庫 
	total_nstock=mem_product.size()-Get_product_size_wholesaler();
	if(i==0) fprintf(out2,"   i    total_nstock\n");
	fprintf(out2,"i=,%3d, zaiko=,%4d  \n",i,total_nstock);

}

void CMarket::Show_test(int x)
{
	int i,j;
	int size_ncr;
	size_ncr=mem_ncr_r.size();
	int size;
	size=mem_product.size();
	int ncon;
	int sum=0;
	if(x==0)
	{
		fprintf(test2," ,");
		for(i=0;i<size_ncr;i++)
		{
			fprintf(test2,"%3d,",mem_ncr_r[i]);
		}
		fprintf(test2,"\n");
	}
	fprintf(test2,"%d,",x);
	for(i=0;i<size_ncr;i++)
	{
		ncon=0;//同一生産者同一製品種別の商品数のカウンター
//		njcon=0;
		for(j=0;j<size;j++)
		{
			if(mem_product[j]->Get_class_no()==mem_ncr_r[i])
			{
				ncon++;
			}
		}
		fprintf(test2,"%3d,",ncon);
		sum+=ncon;
	}
	fprintf(test2,"%3d,",sum);
	fprintf(test2,"\n");
}

void CMarket::Show_test_2(int x)
{
	int i,j;
	int size_ncr;
	size_ncr=mem_ncr_r.size();
	int size;
	size=mem_product.size();
	int ncon;
	int sum=0;
	if(x==0)
	{
		fprintf(test4," ,");
		for(i=0;i<size_ncr;i++)
		{
			fprintf(test4,"%3d,",mem_ncr_r[i]);
		}
		fprintf(test4,"\n");
	}
	fprintf(test4,"%d,",x);
	for(i=0;i<size_ncr;i++)
	{
		ncon=0;//同一生産者同一製品種別の商品数のカウンター
//		njcon=0;
		for(j=0;j<size;j++)
		{
			if(mem_product[j]->Get_class_no()==mem_ncr_r[i])
			{
				ncon++;
			}
		}
		fprintf(test4,"%3d,",ncon);
		sum+=ncon;
	}
	printf("noooooooooooooo %d\n",mem_product.size());
	fprintf(test4,"%3d,",sum);
	fprintf(test4,"\n");
}


void CMarket::Show_wholesaler()
{
	int size;
	int i,j;
	fprintf(out,"inside Show_wholesaler\n");
	size=mem_whole.size();
	for(i=0;i<size;i++) {
		fprintf(out,",%d, ",mem_whole[i]->Get_Agent_no());
		fprintf(out,"ncr_p=,%d,   class_no= ",mem_whole[i]->Get_ncr_p());
		for(j=0;j<mem_whole[i]->Get_mem_class_p_size();j++){
			fprintf(out,",%d, ",mem_whole[i]->Get_class_no(j));
		}
		fprintf(out,"amount= ");
		for(j=0;j<mem_whole[i]->Get_mem_class_p_size();j++){
			fprintf(out,",%d, ",mem_whole[i]->Get_q(j));
		}
		fprintf(out,"price= ");
		for(j=0;j<mem_whole[i]->Get_mem_class_p_size();j++){
			fprintf(out,",%d, ",mem_whole[i]->Get_price(j));
//			printf("w=%d p=%d\n",i,mem_whole[i]->Get_price(j));
		}
		fprintf(out,"\n");
	}
}

void CMarket::Show_bought_product_consumer()
{
	int i;
	int size;
	size=mem_con.size();
	for(i=0;i<size;i++){
		mem_con[i]->Show_bought_product();
	}
}


*/


/*
void CMarket::Production_retailer_not_whole()
{
	//使ってない
	int size;
	int i,j;int p_gen,price_w;
	int ncr_p;
	size=mem_retailer.size();
	for(i=0;i<size;i++)
	{
		mem_retailer[i]->Seisan_plan_revised(q_limit_k,price_increase_rate,max_q_re,min_q_re,Adjustment_Sensitivity);//各製品種別毎に生産量qを決定する
		mem_retailer[i]->Renew_stock_price(mem_product);
		mem_retailer[i]->Seisan();//各製品種別について製品をq個作る
		p_gen=cp->Get_price_genka();//		printf("k=%d\n",k);
		price_w=0;
		mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);
		mem_retailer[i]->Set_shiwake_seisan(i_period,(p_gen+price_w));
		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++)
		{
			Get_Product_retailer(i,j);

		}	  
	}
}*/
/*void CMarket::Production()
{
	//使ってない
	int size;
	int i,j;int p_gen,price_w;
	int ncr_p;
	size=mem_whole.size();
	for(i=0;i<size;i++){
		//mem_whole[i]->Create_Product_class_p();
		mem_whole[i]->Seisan_plan(price_k,first_price);//各製品種別毎に生産量qを決定する
		mem_whole[i]->Seisan();//各製品種別について製品をq個作る
		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_whole[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++){
			Get_Product_wholesaler(i,j);
			p_gen=cp->Get_price_genka();
			mem_whole[i]->Set_shiwake_seisan_k(i_period,p_gen,mem_whole[i]->Get_bonus()*mem_whole[i]->Get_no_employ());
			mem_whole[i]->Set_shiwake_seisan(i_period,p_gen);
		}	  
	}
	size=mem_retailer.size();
	for(i=0;i<size;i++){
		//mem_retailer[i]->Create_Product_class_p();
		mem_retailer[i]->Seisan_plan(price_k,first_price);//各製品種別毎に生産量qを決定する
		mem_retailer[i]->Seisan();//各製品種別について製品をq個作る
		//各生産者の製品を市場の倉庫(mem_product)にいれる	
		ncr_p=mem_retailer[i]->Get_ncr_p();
		for(j=0;j<ncr_p;j++){
			Get_Product_retailer(i,j);
			p_gen=cp->Get_price_genka();//		printf("p_gen=%d\n",p_gen);
			price_w=0;
			mem_retailer[i]->Set_shiwake_seisan_k(i_period,p_gen,mem_retailer[i]->Get_bonus()*mem_retailer[i]->Get_no_employ(),price_w);
			mem_retailer[i]->Set_shiwake_seisan(i_period,(p_gen+price_w));
		}	  
	}
}*/

/*
void CMarket::Pay_interest()
{
	int inte,i,size,inte_sum=0;
	size=mem_con.size();//consumer size
	for(i=0;i<size;i++)
	{
		inte=cb->suply_inte_c(mem_con,mem_con[i]->Get_Consumer_no(),100000);
		mem_con[i]->s_interest(inte);
		inte_sum+=inte;
		printf("inte=%d s_inte=%d\n",inte,inte_sum);
	}
	cb->suply_inte_aft();

}*/

/*
void CMarket::Calc_bonus()
{
	int i,x;	int pay_bonus;
	int size_c,size_w,size_r,size_e,size_b,size_sum;
	size_c=mem_con.size();
	size_w=mem_whole.size();
	size_r=mem_retailer.size();
	size_e=mem_equip.size();
	size_b=mem_bank.size();
	size_sum=size_r+size_w+size_e+size_b;//retailer+wholesaler+equipment+bank
	x=size_c/size_sum;//従業員配分のmin数

	for(i=0;i<size_w;i++)
	{
		pay_bonus=0;
//20110224		if(nbonus==2 && mem_whole[i]->Get_loan_s_zandaka()==0 && mem_whole[i]->Get_yokin_zandaka()-mem_whole[i]->Get_tax()>mem_whole[i]->Get_constant_wage()){
		if(nbonus==2 && mem_whole[i]->Get_loan_s_zandaka()==0 && mem_whole[i]->Get_yokin_suitoutyou_zandaka()-mem_whole[i]->Get_tax()>mem_whole[i]->Get_constant_wage()){
//20110224			pay_bonus=int((mem_whole[i]->Get_genkin_zandaka()+mem_whole[i]->Get_yokin_zandaka()-mem_whole[i]->Get_tax())*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
			pay_bonus=int((mem_whole[i]->Get_genkin_suitoutyou_zandaka()+mem_whole[i]->Get_yokin_suitoutyou_zandaka()-mem_whole[i]->Get_tax())*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
			pay_bonus=int(pay_bonus/mem_whole[i]->Get_no_employ());
		}
		else{
			pay_bonus=0;
		}
		mem_whole[i]->Set_bonus(pay_bonus);
	}

	for(i=0;i<size_r;i++)
	{
		pay_bonus=0;
		//ボーナス支払い決定、及び残高計算
		//		if(nbonus==2 && rieki>=mem_retailer[i]->Get_no_employ() && mem_retailer[i]->Get_loan_s_zandaka()==0 && mem_retailer[i]->Get_yokin_zandaka()>mem_retailer[i]->Get_constant_wage()){
//		if(nbonus==2 && mem_retailer[i]->Get_loan_s_zandaka()==0 && mem_retailer[i]->Get_yokin_suitoutyou_zandaka()-mem_retailer[i]->Get_tax()>mem_retailer[i]->Get_constant_wage()){
		if(nbonus==2 && mem_retailer[i]->Get_loan_s_zandaka()==0 && mem_retailer[i]->Get_rieki_out()-mem_retailer[i]->Get_tax()>0){
			pay_bonus=int((mem_retailer[i]->Get_rieki_out()-mem_retailer[i]->Get_tax())*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
			pay_bonus=int(pay_bonus/mem_retailer[i]->Get_no_employ());
		}
		else{
			pay_bonus=0;
//			Re_Set_constant_wage_r(i);
		}
		mem_retailer[i]->Set_bonus(pay_bonus);
/*		//if(nbonus==2 && mem_retailer[i]->Get_loan_s_zandaka()==0 && mem_retailer[i]->Get_yokin_zandaka()>mem_retailer[i]->Get_constant_wage())
		if(nbonus==2 && mem_retailer[i]->Get_touki_zyunrieki() > 0)
		{
			pay_bonus=int(mem_retailer[i]->Get_touki_zyunrieki())*(cr->sdrand(bonus_rate_min,bonus_rate_max));
			pay_bonus=int(pay_bonus/mem_retailer[i]->Get_no_employ());
		}
		else{
			pay_bonus=0;
		}
		mem_retailer[i]->Set_bonus(pay_bonus);
*/
		//ボーナス計算終了
/*	}



	for(i=0;i<size_e;i++)
	{
		pay_bonus=0;
//20110224		if(nbonus==2 && mem_equip[i]->Get_loan_s_zandaka()==0 && mem_equip[i]->Get_yokin_zandaka()-mem_equip[i]->Get_tax()>mem_equip[i]->Get_constant_wage()){
		if(nbonus==2 && mem_equip[i]->Get_loan_s_zandaka()==0 && mem_equip[i]->Get_yokin_suitoutyou_zandaka()-mem_equip[i]->Get_tax()>mem_equip[i]->Get_constant_wage()){
//20110224			pay_bonus=int((mem_equip[i]->Get_genkin_zandaka()+mem_equip[i]->Get_yokin_zandaka()-mem_equip[i]->Get_tax())*(cr->sdrand(bonus_rate_min_e,bonus_rate_max_e)));
			pay_bonus=int((mem_equip[i]->Get_genkin_suitoutyou_zandaka()+mem_equip[i]->Get_yokin_suitoutyou_zandaka()-mem_equip[i]->Get_tax())*(cr->sdrand(bonus_rate_min_e,bonus_rate_max_e)));
			pay_bonus=int(pay_bonus/mem_equip[i]->Get_no_employ());
			printf("pay_bo:%d\n",pay_bonus);
		}
		else{
			pay_bonus=0;
		}
		mem_equip[i]->Set_bonus(pay_bonus);
	}

	for(i=0;i<size_b;i++)
	{
		pay_bonus=0;
		if(nbonus==2 && mem_bank[i]->Get_rieki_ac()-mem_bank[i]->Get_tax()>=mem_bank[i]->Get_no_employ()){
			pay_bonus=int((mem_bank[i]->Get_rieki_ac()-mem_bank[i]->Get_tax())*(cr->sdrand(bonus_rate_min,bonus_rate_max)));
			pay_bonus=int(pay_bonus/mem_bank[i]->Get_no_employ());
		}
		else{
			pay_bonus=0;
		}
		mem_bank[i]->Set_bonus(pay_bonus);
	}
}
*/
/*  20111128
void CMarket::Calc_tax()
{
	int i;	int tax;

	for(i=0;i<int(mem_whole.size());i++)
	{
		mem_whole[i]->Tax_calc(mem_whole[i]->Get_rieki_ac());
		tax=mem_whole[i]->Get_tax();
	}
	for(i=0;i<int(mem_retailer.size());i++)
	{
		mem_retailer[i]->Tax_calc(mem_retailer[i]->Get_rieki_ac());
		tax=mem_retailer[i]->Get_tax();
	}
	for(i=0;i<int(mem_equip.size());i++){
		mem_equip[i]->Tax_calc(mem_equip[i]->Get_rieki_ac());
		tax=mem_equip[i]->Get_tax();

	}
	for(i=0;i<int(mem_bank.size());i++){
		mem_bank[i]->Tax_calc(mem_bank[i]->Get_rieki_ac());
		tax=mem_bank[i]->Get_tax();
	}
}
*/

/*
void CMarket::Set_pay_rate(double x)
{
	int i,size_r,size_w;
	size_r=mem_retailer.size();
	size_w=mem_whole.size();
	for(i=0;i<size_r;i++)
	{
		mem_retailer[i]->Set_pay_rate(x);
	}
	for(i=0;i<size_w;i++)
	{
		mem_whole[i]->Set_pay_rate(x);
	}
}
*/
/*
template<class T> void CMarket::Pay_producer_tax(const T &member)
{
	int i,tax;
	for(i=0;i<int(member.size());i++)
	{
		//消費税の支払い
		tax=member[i]->Get_shouhi_tax();
		member[i]->Set_shiwake_yokin_hikidashi(i_period,tax);
		mem_bank[member[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,tax);
		member[i]->Set_shiwake_shouhi_tax(i_period,tax);

		cg->Collect_tax(tax);
		cg->Set_taxdate(i_period,930,tax);
		cg->Set_shiwake_zeisyu(i_period,tax);

		//法人税の支払い
		tax=member[i]->Get_tax();
		member[i]->Set_shiwake_yokin_hikidashi(i_period,tax);
		mem_bank[member[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,tax);
		member[i]->Set_shiwake_houzin_tax(i_period,tax);
		cg->Collect_tax(tax);
		cg->Set_taxdate(i_period,910,tax);
		cg->Set_shiwake_zeisyu(i_period,tax);
	}
}
*/


#endif
