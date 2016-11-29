//CShow.h
#ifndef INC_CSHOW
#define INC_CSHOW
#include <stdio.h>
#include <vector>
//#include <stdlib.h>>
#include <algorithm>
#include"CFunction.h"
#include"CRandum.h"
using namespace std;

class CShow
{
	double time;
	int Agent_type;
           //Agent_type=10; 一般消費者
		   //Agent_type=20; 一般消費者向け生産者
	       //Agent_tuype=30;生産者向け生産者（原料を生産する)
	int Agent_no;
	int n_class;//市場にある製品種別の最大数
	int nmax_p;//各生産者が生産する製品種別の最大数
	int nmax_p_min;
	int nmax_c;//各消費者が購入する製品種別の最大数
	int nbonus;
	int turn;//期数
	double income_tax_rate;
	int i_period;
	int min_constant_wage,max_constant_wage;
	double bonus_rate_min;//ボーナスを給与に還元する場合のmin比率（例：0.2なら利益の0.2倍をmin還元量とする）
	double bonus_rate_max;
	double bonus_rate_min_e;//equip
	double bonus_rate_max_e;
	double depo_rate_c;
	double depo_rate_p;
	int repay_time_ave,repay_time_bun;
	int first_price;

	int invest_max;
	int sri;//給与を見るための変数
	int ri_count;
	int s_stock_r;	int s_stock_w;
	int i_count;
	int min_init_depo_c;		int max_init_depo_c;		int min_init_depo_w;		int max_init_depo_w;
	int min_init_depo_r;		int max_init_depo_r;		int min_init_depo_e;		int max_init_depo_e;
	long long min_bank_capital;		long long max_bank_capital;		//各エージェントの初期銀行預金

	double min_with_drawal_rate;	double max_with_drawal_rate;//

	int repay_period;	double max_q_re;	double min_q_re;
	int min_koteihi;	int max_koteihi;	int min_hendouhi;	int max_hendouhi;
	int min_price_w;	int max_price_w;
	double Adjustment_Sensitivity;
	double min_price_p;	double max_price_p;	double min_price_m;	double max_price_m;
	double bank_increase_rate;		double min_q_init;
	int max_e_flag;	int max_equip_end;	int max_memo_time;	int max_reac_flag;
	double capa_increase_rate;	int invest_money;	int min_q_limit;
	double q_limit_k;	double price_increase_rate;	double price_k;
	double reserve_rate;	int nbank_con;
	int ncase;	int mibarai;
	int nkessan;

/*	struct sangyourenkan{
			

	}
	*/
	CFunction *cf;
	CRandum *cr;

	/////////FILEの生成/////////
	FILE *out;		FILE *out1;		FILE *out2;  
	FILE *test;		FILE *test2;	FILE *test3;	FILE *test4;
	FILE *product_price;	FILE *product_price_w;
	FILE *se_income;	FILE *se_con;
	FILE *product_out;	FILE *bought_pro;
	FILE *market_product;	FILE *retai;
	FILE *bank_data;	
	FILE *economy;
	FILE *Consumer;	FILE *Retailer;	FILE *Wholesaler;
	FILE *Equipment;	FILE *Bank;
	FILE *producer_no;
	FILE *se_income_new;	FILE *tax;		FILE *invest;  FILE *bought_money;
	FILE *shiwake;   FILE *out3;   FILE *out3_csv;	FILE *loan;
	FILE *employ_FILE;	FILE *seisan;	FILE *agent_no; FILE *kyuyo; FILE *market_data;
	FILE *eqw;	FILE *GDP; FILE *seihin_price;
	FILE *zyunkanhyou; FILE *zyunkandata;
	FILE *ac_data1; FILE *ac_data2;
	FILE *gyousei_syouhisya;
	FILE *producer_data;
	FILE *producer_uriage_kyuyo;


	vector <CConsumer *> mem_con;
	vector <CWholesaler *> mem_whole;
	vector <CRetailer *> mem_retailer;
	vector <CEquipment *> mem_equip;
	vector <CBank *> mem_bank;

	vector <CProduct *> mem_product;//市場にあるリテイラー商品の集合
	vector <CProduct *> mem_product_whole;//市場にあるホールセラー商品集合
	vector <CProduct *> mem_buy;//その期に購入されたリテイラー商品の集合
	vector <CProduct *> mem_buy_w;//その期に購入されたホールセラー商品集合

	vector <CProduct_class *> mem_class_statics;//市場の消費者の購入製品別統計データの集合
	vector <CProduct_class *> mem_class_statics_w;//ホールセラーの購入製品別統計データ集合
	vector <CProduct_class *> mem_class_stock_statics;//市場のリテイラー在庫製品別統計データの集合
	vector <CProduct_class *> mem_class_stock_statics_w;//市場のホールセラー在庫製品別統計データ集合

	vector <int> mem_ncr_w;//市場にある卸用製品種別の種別番号の集合
	vector <int> mem_ncr_r;//市場にある小売用製品種別番号の集合
	vector <int> init_r;//初期生産リテイラーエージェントno

	vector <int> producer_seihin;

	CGovernment *cg;
	CParameter *cpara;



public:
	void Write_periodfast(int i);	//期初に記述するプログラム
//～～～～～～～パラメータクラス受け渡し
	void Set_Parameter_class(CParameter * cpar){cpara=cpar;};
//	void Set_CFunction_class(){cr=new CRandum; cf=new CFunction(cr);};
	void Set_output_FILE();


//～～～～～～～マーケットクラス内の保有データアドレス受け渡し
//～～～～～～～受け渡しはアドレスのみ、また絶対に変数を処理しないこと
	//エージェントベクター
	void set_consumer_add(vector <CConsumer *> cx){mem_con= cx;};
	void set_retailer_add(vector <CRetailer *> cx){mem_retailer= cx;};
	void set_wholesaler_add(vector <CWholesaler *> cx){mem_whole= cx;};
	void set_equipment_add(vector <CEquipment *> cx){mem_equip= cx;};
	void set_bank_add(vector <CBank *> cx){mem_bank= cx;};
	void set_government_add(CGovernment *cx){cg=cx;};

	//プロダクトベクター
	void set_mem_product(vector <CProduct *> cx){mem_product=cx;};
	void set_mem_product_w(vector <CProduct *> cx){mem_product_whole=cx;};
	void set_mem_buy(vector <CProduct *> cx){mem_buy=cx;};
	void set_mem_buy_w(vector <CProduct *> cx){mem_buy_w=cx;};

	//プロダクトクラスベクター
	void set_mem_class_statics(vector <CProduct_class *> cx){mem_class_statics=cx;};
	void set_mem_class_statics_w(vector <CProduct_class *> cx){mem_class_statics_w=cx;};
	void set_mem_class_stock_statics(vector <CProduct_class *> cx){mem_class_stock_statics=cx;};
	void set_mem_class_stock_statics_w(vector <CProduct_class *> cx){mem_class_stock_statics_w=cx;};


	//他のベクター	
	void set_mem_ncr_w(vector <int> cx){mem_ncr_w=cx;};
	void set_mem_ncr_r(vector <int> cx){mem_ncr_r=cx;};


//～～～～～マーケットクラス変数アドレス受け渡し終了


//～～～～CAppliプリント関数～～～～～～～～～

	void print_test();
	void Show_gdp();
	void show_income();
	void Show_bought_product_class();
	void Show_kimatu_zandaka(int Agent_type);
	void Show_kisyu_zandaka(int Agent_type);
	void Show_market_product();
	void Show_ncr_r();
	void Show_mem_ncr_w();
	void Show_no_buy_code();
	void Show_Product();
	void Show_product_class();
	void Show_retailer();
	void Show_termly_change(int i);
	void Show_test(int x);
	void Show_test2(int x);
	void Show_Wholesaler();
	void Show_mem_ncr_r();
	void show_no_buy_code();
	void Show_test_2(int x);
	void Show_wholesaler();
	void Show_bought_product_consumer();
	void Show_statics_mem_buy();
	void Show_static_mem_buy_w();
	void Show_statics_mem_product();
	void Show_bank(){int i,size;size=mem_bank.size();for(i=0;i<size;i++){mem_bank[i]->Show_bank(mem_con);}};
	void Show_zikoshihonhiritu();
	void Show_rieki_loan();
	void Show_rieki_loan_first();
	void Show_gdp_buy_pro_not_gdp();
	void zini();
	void Show_Zini();
	void Show_employ();

	template<class T>void Show_Product_tag(T &mem_pro);

//～～～～～～～～aida　追加～～～～～～～～
	void Show_personal_income();
	void Show_consumer_asset();
	void Show_employ_c();
	void Show_employ_producer_asset();
	void Show_price();
	void Show_price_w();
	void Show_seisan_class_no();
	void Show_seisan_class_no_w();
	void Show_producer_equip_lv();
	void Show_corp_capital();
	void Show_producer_asset();
	void Show_producer_employ();
	void Show_producer_uriage();
	void Show_producer_labor_cost();
	void Show_producer_seisan_amount();
	void Show_producer_genryo_price();
	void Show_print_data();
//～～～～～～～～ ここまで ～～～～～～～～

//～～～～～～～CAppliプリント関数終了～～～～～～～～



//～～～～CMarketプリント関数～～～～～～～～～
	//　CM_Show_　は識別のために先頭に表記、CM_Show_以降の名前は実際に呼び出し元となっているCMarketの関数
	//market_productに記述
	void CM_Show_Production_whole_revised(int size){fprintf(market_product," %d ,",size);};
	void CM_Show_Buy_consumer_top(int x){fprintf(market_product," , %d , ",x);};
	void CM_Show_Buy_consumer_row(int x1,int x2){fprintf(market_product," %d , %d  , ",x1,x2);};
	void CM_Show_Production_retail_top(int x){fprintf(market_product," %d ,",x);};
	void CM_Show_Production_retail_row(int x){fprintf(market_product," %d ",x);};

	//investに記述
	void CM_Show_Investment_top(int x1,int x2,int x3,int x4){fprintf(invest," , %d, %d , %d, %d,",x1,x2,x3,x4);};
	void CM_Show_Investment_middle(int x){fprintf(invest," %d ,",x);};
	void CM_Show_Investment_row(){fprintf(invest,"\n");};

	//product_outに記述
	void CM_Show_Get_Product_retailer(int x1,int x2,int x3){fprintf(product_out," , %d , %d ,%d\n",x1,x2,x3);};//Get_Product_retailer_reでも使用
	


	void CR_CM_Show_Buy_consumer_row(int x1,int x2){fprintf(market_product," %d , %d\n",x1,x2);};
	void CR_Show_product_relation();

//～～～～～～～CMarketプリント関数終了～～～～～～～～	



//～～～～～～～～～～～～その他～～～～～～～～
	void Set_i_period(int ip){i_period=ip;};
	int Get_product_size_retailer();	//Show_bought_product_class()で使用
	int Get_product_size_wholesaler();	//Show_bought_product_class_w()で使用

//～～～～～～～その他終了～～～～～～～～
	void Tyotikuprint()
	{
		int i,s_sum_zeigo=0,s_sum_zyouyo=0;
		int sum_zeigo=0,sum_zyouyo=0;
		double m_r_ty=0,m_w_ty=0,m_e_ty=0;
		double m_ty=0;
		double tyotikuritu=0;
		for(i=0;i<int(mem_retailer.size());i++)
		{
			if(mem_retailer[i]->Tyotiku_touki_zeigorieki()>0&&mem_retailer[i]->Tyotiku_touki_zyunsoneki()>0)
			{
				m_ty=0;
				s_sum_zeigo+=mem_retailer[i]->Tyotiku_touki_zeigorieki();
				s_sum_zyouyo+=mem_retailer[i]->Tyotiku_touki_zyunsoneki();
				m_ty=double(double(mem_retailer[i]->Tyotiku_touki_zyunsoneki())/double(mem_retailer[i]->Tyotiku_touki_zeigorieki()));
				fprintf(cpara->FI_Get_free_text(),"%d:%d  %d  %lf , ",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Tyotiku_touki_zyunsoneki(),mem_retailer[i]->Tyotiku_touki_zeigorieki(),m_ty);
			}
			
			if(m_r_ty<m_ty) m_r_ty=m_ty;
		}
		if(s_sum_zyouyo>0&&s_sum_zeigo>0)	tyotikuritu=double(double(s_sum_zyouyo)/double(s_sum_zeigo));
		else tyotikuritu=0;
		sum_zeigo+=s_sum_zeigo;
		sum_zyouyo+=s_sum_zyouyo;

		fprintf(cpara->FI_Get_Tyotikuritu_pro(),"%d , %d , %lf , ",s_sum_zeigo,s_sum_zyouyo,tyotikuritu);
		fprintf(cpara->FI_Get_free_text(),"\n");

		s_sum_zeigo=0;
		s_sum_zyouyo=0;
		for(i=0;i<int(mem_whole.size());i++)
		{
			if(mem_whole[i]->Tyotiku_touki_zeigorieki()>0&&mem_retailer[i]->Tyotiku_touki_zyunsoneki()>0)
			{
				m_ty=0;
				s_sum_zeigo+=mem_whole[i]->Tyotiku_touki_zeigorieki();
				s_sum_zyouyo+=mem_whole[i]->Tyotiku_touki_zyunsoneki();
				m_ty=double(double(mem_whole[i]->Tyotiku_touki_zyunsoneki())/double(mem_whole[i]->Tyotiku_touki_zeigorieki()));
			}
			if(m_w_ty<m_ty) m_w_ty=m_ty;
		}
		if(s_sum_zyouyo>0&&s_sum_zeigo>0)	tyotikuritu=double(double(s_sum_zyouyo)/double(s_sum_zeigo));
		else tyotikuritu=0;
		sum_zeigo+=s_sum_zeigo;
		sum_zyouyo+=s_sum_zyouyo;

		fprintf(cpara->FI_Get_Tyotikuritu_pro(),"%d , %d , %lf , ",s_sum_zeigo,s_sum_zyouyo,tyotikuritu);

		s_sum_zeigo=0;
		s_sum_zyouyo=0;
		for(i=0;i<int(mem_equip.size());i++)
		{
			if(mem_equip[i]->Tyotiku_touki_zeigorieki()>0&&mem_equip[i]->Tyotiku_touki_zyunsoneki()>0)
			{
				m_ty=0;
				s_sum_zeigo+=mem_equip[i]->Tyotiku_touki_zeigorieki();
				s_sum_zyouyo+=mem_equip[i]->Tyotiku_touki_zyunsoneki();
				m_ty=double(double(mem_equip[i]->Tyotiku_touki_zyunsoneki())/double(mem_equip[i]->Tyotiku_touki_zeigorieki()));
			}
			if(m_r_ty<m_ty) m_e_ty=m_ty;
		}
		if(s_sum_zyouyo>0&&s_sum_zeigo>0)	tyotikuritu=double(double(s_sum_zyouyo)/double(s_sum_zeigo));
		else tyotikuritu=0;
		sum_zeigo+=s_sum_zeigo;
		sum_zyouyo+=s_sum_zyouyo;

		fprintf(cpara->FI_Get_Tyotikuritu_pro(),"%d , %d , %lf , ",s_sum_zeigo,s_sum_zyouyo,tyotikuritu);

		if(sum_zyouyo>0&&sum_zeigo>0)	tyotikuritu=double(double(sum_zyouyo)/double(sum_zeigo));
		else tyotikuritu=0;
		
		fprintf(cpara->FI_Get_Tyotikuritu_pro(),"%d , %d , %lf , %lf , %lf , %lf\n",sum_zeigo,sum_zyouyo,tyotikuritu,m_r_ty,m_w_ty,m_e_ty);

	}

};
void CShow::CR_Show_product_relation()
{
	int i,j,k;
	int count=0;
	fprintf(cpara->FI_Get_CR_product_relation(),"製品種ごとに買うことが可能な消費者の数\n");
	
	for(i=0;i<int(mem_ncr_r.size());i++)	fprintf(cpara->FI_Get_CR_product_relation(),"製品番号%d , ",mem_ncr_r[i]);
	fprintf(cpara->FI_Get_CR_product_relation(),"\n");
	for(i=0;i<int(mem_ncr_r.size());i++)
	{
		count=0;
		for(j=0;j<int(mem_con.size());j++)
		{
			for(k=0;k<mem_con[j]->Get_ncr_c();k++)
			{
				if(mem_ncr_r[i]==mem_con[j]->CR_Get_class_no_c(k))	count++;
			}
		}
		fprintf(cpara->FI_Get_CR_product_relation(),"%d , ",count);
	}
	fprintf(cpara->FI_Get_CR_product_relation(),"\n\n\n\n\n");



	fprintf(cpara->FI_Get_CR_product_relation(),"製品種ごとに生産が可能な生産者の数\n");
	for(i=0;i<int(mem_ncr_r.size());i++)	fprintf(cpara->FI_Get_CR_product_relation(),"製品番号%d , ",mem_ncr_r[i]);
	fprintf(cpara->FI_Get_CR_product_relation(),"\n");
	for(i=0;i<int(mem_ncr_r.size());i++)
	{
		count=0;
		for(j=0;j<int(mem_retailer.size());j++)
		{
			for(k=0;k<mem_retailer[i]->Get_ncr_p();k++)
			{
				if(mem_ncr_r[i]==mem_retailer[j]->CR_Get_class_no_p(k))	count++;
			}
		}
		fprintf(cpara->FI_Get_CR_product_relation(),"%d , ",count);
	}
	fprintf(cpara->FI_Get_CR_product_relation(),"\n\n\n");

	fprintf(cpara->FI_Get_CR_product_relation(),"企業_製品種ごとの生産可能数\n");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_CR_product_relation(),"企業番号:%d , ",mem_retailer[i]->Get_Agent_no());
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			fprintf(cpara->FI_Get_CR_product_relation(),"製品番号%d番 , 生産数 , %d , ",mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_q_limit(j));
		}
		fprintf(cpara->FI_Get_CR_product_relation(),"\n");
	}

}
void CShow::Show_employ()
{
	//Show the list of consumer no and the employer no
	int size_w,size_r,size_e,size_b,size_c;
	size_w=mem_whole.size();
	size_r=mem_retailer.size();
	size_e=mem_equip.size();
	size_c=mem_con.size();
	size_b=mem_bank.size();
	int i;
	for(i=0;i<size_w;i++){
		fprintf(employ_FILE,"wholesaler_no=%3d ",mem_whole[i]->Get_Producer_no());
		mem_whole[i]->Show_employ();
		fprintf(employ_FILE,"\n");
	}
	for(i=0;i<size_r;i++){
		fprintf(employ_FILE,"retailer_no=%3d ",mem_retailer[i]->Get_Producer_no());
		mem_retailer[i]->Show_employ();
		fprintf(employ_FILE,"\n");
	}
	for(i=0;i<size_e;i++){
		fprintf(employ_FILE,"equipment_no=%3d ",mem_equip[i]->Get_Producer_no());
		mem_equip[i]->Show_employ();
		fprintf(employ_FILE,"\n");
	}
	for(i=0;i<size_b;i++){
		fprintf(employ_FILE,"bank_no=%3d ",mem_bank[i]->Get_Agent_no());
		mem_bank[i]->Show_employ();
		fprintf(employ_FILE,"\n");
	}
	for(i=0;i<size_c;i++){
		fprintf(employ_FILE,"consumer_no=%3d Producer_no=%3d constant_wage=%5d \n",mem_con[i]->Get_Agent_no(),mem_con[i]->Get_office_no(),mem_con[i]->Get_constant_wage());
	}
}
void CShow::Write_periodfast(int i)
{

	fprintf(cpara->FI_GET_OUTPUT_Deposit(),"%d,",i);
	fprintf(cpara->FI_GET_OUTPUT_GDP(),"%d,",i);


	///////期初の改行、期数表示の入力関数////////
	fprintf(product_out,"%d\n",i);
	fprintf(test,"%d\n",i);
	fprintf(test3,"%d , ",i);
	fprintf(market_product,"%d,",i);
	fprintf(bank_data,"%d\n",i);
	fprintf(bought_pro,"%d\n",i);
	fprintf(se_income,"%d , ",i);
	fprintf(retai,"%d\n",i);
	fprintf(invest,"%d",i);
	fprintf(bought_money,"%d",i);
	fprintf(tax,"%d\n",i);
	fprintf(out,"第%3d 期 市場の期首生産者別商品リスト\n",i);//file出力
	fprintf(out1,"第%3d 期 市場の購入商品の生産種別統計データ\n",i);
	fprintf(out3,"%d ==================================================================================================\n",i);
	fprintf(shiwake,"%d ==================================================================================================\n",i);
	fprintf(out3_csv,"%d\n",i);
	fprintf(seisan,"%d ==================================================================================================\n",i);
	fprintf(agent_no,"%d,",i);
	fprintf(market_data,"%d,",i);
	fprintf(eqw,"%d,",i);
	fprintf(GDP,"%d,",i);
	fprintf(Wholesaler,"%d期\n",i);
	fprintf(zyunkandata,"%d期  ",i);
	fprintf(Retailer,"%d期\n",i);
	fprintf(ac_data1,"%d期\n",i);
	fprintf(ac_data2,"%d期\n",i);
	fprintf(zyunkanhyou,"\n\n\n\n\n%d期\n\n",i);
	fprintf(cpara->FI_Get_statistic_product(),"%d期\n",i);
	
	fprintf(gyousei_syouhisya,"%d , ",i);
	fprintf(Consumer,"%d\n",i);
	fprintf(producer_data,"%d , ",i);
	fprintf(producer_uriage_kyuyo,"%d , ",i);
	fprintf(cpara->FI_Get_free_text(),"%d\n",i);
	fprintf(cpara->FI_Get_show_tax(),"%d , ",i);
	fprintf(cpara->FI_Get_se_income_new(),"%d \n",i);
	if(i!=0) fprintf(cpara->FI_Get_rieki_out(),"%d , ",i);
	if(i!=0) fprintf(cpara->FI_Get_loan_out(),"%d, ",i);
	if(i!=0) fprintf(cpara->FI_Get_deposit_out(),"%d, ",i);
	fprintf(cpara->FI_Get_Labor_writer(),"\n\n\n%d期目\n\n",i);

	fprintf(cpara->FI_Get_Tyotikuritu_pro(),"%d , ",i); 
	fprintf(cpara->FI_Get_Tyotikuritu_consumer(),"%d , ",i);
	fprintf(cpara->FI_Get_Tyotikuritu_uriage_rieki(),"%d , ",i);
}
void CShow::Set_output_FILE()
{
	out=cpara->FI_Get_out();
	out1=cpara->FI_Get_out1();
	out2=cpara->FI_Get_out2();
	test=cpara->FI_Get_test();
	test2=cpara->FI_Get_test2();
	test3=cpara->FI_Get_test3();
	test4=cpara->FI_Get_test4();
    product_price=cpara->FI_Get_product_price();
	product_price_w=cpara->FI_Get_product_price_w();
	market_product=cpara->FI_Get_market_product();
	se_income=cpara->FI_Get_se_income();
    se_con=cpara->FI_Get_se_con();
	product_out=cpara->FI_Get_product_out();
	bank_data=cpara->FI_Get_bank_data();
	economy=cpara->FI_Get_economy();
	bought_pro=cpara->FI_Get_bought_pro();
	retai=cpara->FI_Get_retai();
	Consumer=cpara->FI_Get_Consumer();
	Retailer=cpara->FI_Get_Retailer();
	Wholesaler=cpara->FI_Get_Wholesaler();
	Equipment=cpara->FI_Get_Equipment();
	Bank=cpara->FI_Get_Bank();
    producer_no=cpara->FI_Get_producer_no();
	se_income_new=cpara->FI_Get_se_income_new();
	invest=cpara->FI_Get_invest();
	bought_money=cpara->FI_Get_bought_money();
	tax=cpara->FI_Get_tax();
	employ_FILE=cpara->FI_Get_employ_file();
	seisan=cpara->FI_Get_seisan();
	agent_no=cpara->FI_Get_agent_no();
	kyuyo=cpara->FI_Get_kyuyo();
	market_data=cpara->FI_Get_market_data();
	eqw=cpara->FI_Get_eqw();
	shiwake=cpara->FI_Get_shiwake();
	out3=cpara->FI_Get_out3();
	out3_csv=cpara->FI_Get_out3_csv();
	loan=cpara->FI_Get_loan();
	GDP=cpara->FI_Get_GDP();
	seihin_price=cpara->FI_Get_seihin_price();
	zyunkanhyou=cpara->FI_Get_zyunkanhyou();
	zyunkandata=cpara->FI_Get_zyunkandata();
	ac_data1=cpara->FI_Get_ac_data1();
	ac_data2=cpara->FI_Get_ad_data2();
	gyousei_syouhisya=cpara->FI_Get_gyousei_syouhisya();
	producer_data=cpara->FI_Get_producer_data();
	producer_uriage_kyuyo=cpara->FI_Get_producer_uriage_kyuyo();
}

template<class T>void CShow::Show_Product_tag(T &mem_pro)
{
	int pro_no=-10;
	for(int i=0;i<int(mem_pro.size());i++)
	{
		if(pro_no!=mem_pro[i]->Get_Producer_no())
		{
			pro_no=mem_pro[i]->Get_Producer_no();
			fprintf(cpara->FI_Get_statistic_product(),"\n producer_no=%d , ",pro_no);
		}

		fprintf(cpara->FI_Get_statistic_product(),"class_no=%d , price=%d , stock=%d ,  , ",mem_pro[i]->Get_class_no(),mem_pro[i]->Get_price(),mem_pro[i]->Get_nstock());

	}
}

void CShow::Show_rieki_loan()
{
	int i,r_sum_rieki=0,r_sum_loan=0,w_sum_rieki=0,w_sum_loan=0,e_sum_rieki=0,e_sum_loan=0;
	int w_sum_depo=0,r_sum_depo=0,e_sum_depo=0;

	fprintf(cpara->FI_Get_rieki_out()," , whole , ");
	fprintf(cpara->FI_Get_loan_out()," , whole , ");
	fprintf(cpara->FI_Get_deposit_out()," , whole , ");
	for(i=0;i<int(mem_whole.size());i++)
	{
		w_sum_rieki+=mem_whole[i]->Get_kimatu_riekizyouyo();
		w_sum_loan+=mem_whole[i]->Get_loan_s_ac();
		w_sum_depo+=mem_whole[i]->Get_yokin_ac();
		fprintf(cpara->FI_Get_rieki_out(),"%d , ",mem_whole[i]->Get_kimatu_riekizyouyo());
		fprintf(cpara->FI_Get_loan_out(),"%d , ",mem_whole[i]->Get_loan_s_ac());
		fprintf(cpara->FI_Get_deposit_out(),"%d , ",mem_whole[i]->Get_yokin_ac());
	}
	fprintf(cpara->FI_Get_rieki_out(),"%d , ",w_sum_rieki);
	fprintf(cpara->FI_Get_loan_out(),"%d , ",w_sum_loan);
	fprintf(cpara->FI_Get_deposit_out(),"%d , ",w_sum_depo);


	fprintf(cpara->FI_Get_rieki_out()," , retailer , ");
	fprintf(cpara->FI_Get_loan_out()," , retailer , ");
	fprintf(cpara->FI_Get_deposit_out()," , retailer , ");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		r_sum_rieki+=mem_retailer[i]->Get_kimatu_riekizyouyo();
		r_sum_loan+=mem_retailer[i]->Get_loan_s_ac();
		r_sum_depo+=mem_retailer[i]->Get_yokin_ac();
		fprintf(cpara->FI_Get_rieki_out(),"%d , ",mem_retailer[i]->Get_kimatu_riekizyouyo());
		fprintf(cpara->FI_Get_loan_out(),"%d , ",mem_retailer[i]->Get_loan_s_ac());
		fprintf(cpara->FI_Get_deposit_out(),"%d , ",mem_retailer[i]->Get_yokin_ac());
	}
	fprintf(cpara->FI_Get_rieki_out(),"%d , ",r_sum_rieki);
	fprintf(cpara->FI_Get_loan_out(),"%d , ",r_sum_loan);
	fprintf(cpara->FI_Get_deposit_out(),"%d , ",r_sum_depo);


	fprintf(cpara->FI_Get_rieki_out()," , equip , ");
	fprintf(cpara->FI_Get_loan_out()," , equip , ");
	fprintf(cpara->FI_Get_deposit_out()," , equip , ");
	for(i=0;i<int(mem_equip.size());i++)
	{
		e_sum_rieki+=mem_equip[i]->Get_kimatu_riekizyouyo();
		e_sum_loan+=mem_equip[i]->Get_loan_s_ac();
		e_sum_depo+=mem_equip[i]->Get_yokin_ac();
		fprintf(cpara->FI_Get_rieki_out(),"%d , ",mem_equip[i]->Get_kimatu_riekizyouyo());
		fprintf(cpara->FI_Get_loan_out(),"%d , ",mem_equip[i]->Get_loan_s_ac());
		fprintf(cpara->FI_Get_deposit_out(),"%d , ",mem_equip[i]->Get_yokin_ac());
	}
	fprintf(cpara->FI_Get_rieki_out(),"%d , ",e_sum_rieki);
	fprintf(cpara->FI_Get_loan_out(),"%d , ",e_sum_loan);
	fprintf(cpara->FI_Get_deposit_out(),"%d , ",e_sum_depo);

	fprintf(cpara->FI_Get_rieki_out(),"%d , ",r_sum_rieki+w_sum_rieki+e_sum_rieki);
	fprintf(cpara->FI_Get_loan_out(),"%d , ",r_sum_loan+w_sum_loan+e_sum_loan);
	fprintf(cpara->FI_Get_deposit_out(),"%d , ",r_sum_depo+w_sum_depo+e_sum_depo);

	fprintf(cpara->FI_Get_rieki_out(),"\n");
	fprintf(cpara->FI_Get_loan_out(),"\n");
	fprintf(cpara->FI_Get_deposit_out(),"\n");

}
void CShow::Show_rieki_loan_first()
{
	int i;
	fprintf(cpara->FI_Get_rieki_out()," , whole , ");
	fprintf(cpara->FI_Get_loan_out()," , whole , ");
	fprintf(cpara->FI_Get_deposit_out()," , whole , ");

	for(i=0;i<int(mem_whole.size());i++)
	{
		fprintf(cpara->FI_Get_rieki_out(),"%d , ",mem_whole[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_loan_out(),"%d , ",mem_whole[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_deposit_out(),"%d , ",mem_whole[i]->Get_Agent_no());
	}
	fprintf(cpara->FI_Get_rieki_out(),"w_sum , ");
	fprintf(cpara->FI_Get_loan_out(),"w_sum , ");
	fprintf(cpara->FI_Get_deposit_out(),"w_sum , ");

	fprintf(cpara->FI_Get_rieki_out()," , retailer , ");
	fprintf(cpara->FI_Get_loan_out()," , retailer , ");
	fprintf(cpara->FI_Get_deposit_out()," , retailer , ");
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_rieki_out(),"%d , ",mem_retailer[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_loan_out(),"%d , ",mem_retailer[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_deposit_out(),"%d , ",mem_retailer[i]->Get_Agent_no());
	}
	fprintf(cpara->FI_Get_rieki_out(),"r_sum , ");
	fprintf(cpara->FI_Get_loan_out(),"r_sum , ");
	fprintf(cpara->FI_Get_deposit_out(),"r_sum , ");
	fprintf(cpara->FI_Get_rieki_out()," , equip , ");
	fprintf(cpara->FI_Get_loan_out()," , equip , ");
	fprintf(cpara->FI_Get_deposit_out()," , equip , ");
	for(i=0;i<int(mem_equip.size());i++)
	{
		fprintf(cpara->FI_Get_rieki_out(),"%d , ",mem_equip[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_loan_out(),"%d , ",mem_equip[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_deposit_out(),"%d , ",mem_equip[i]->Get_Agent_no());
	}
	fprintf(cpara->FI_Get_rieki_out(),"e_sum , ");
	fprintf(cpara->FI_Get_loan_out(),"e_sum , ");
	fprintf(cpara->FI_Get_deposit_out(),"e_sum , ");

	fprintf(cpara->FI_Get_rieki_out(),"all_sum , ");
	fprintf(cpara->FI_Get_loan_out(),"all_sum , ");
	fprintf(cpara->FI_Get_deposit_out(),"all_sum , ");

	fprintf(cpara->FI_Get_rieki_out(),"\n0,");
	fprintf(cpara->FI_Get_loan_out(),"\n0,");
	fprintf(cpara->FI_Get_deposit_out(),"\n0,");
}
void CShow::print_test()
{
	printf("test      aaaaaaaaaaaaaaaaaaaa          %d\n",mem_con.size());
	printf("mem_id %d\n",mem_con[0]->Get_Agent_no());
}
void CShow::Show_zikoshihonhiritu()
{
	int shihon=0,kariire=0, zyouyo=0;
	double hiritu;
	int i;

	for(i=0;i<int(mem_retailer.size());i++)
	{
		shihon+=mem_retailer[i]->Get_shihon_ac();
		kariire+=mem_retailer[i]->Get_loan_l_zandaka()+mem_retailer[i]->Get_loan_s_zandaka();
		zyouyo+=mem_retailer[i]->Get_rieki_zyouyo();
	}

	
	hiritu=double(shihon+zyouyo)/double(kariire+shihon+zyouyo);

	fprintf(producer_data,"%d , %d , %d , %d\n",shihon,zyouyo,kariire,hiritu);


}

void CShow::Show_gdp()
{
	int size_r,size_w,size_e,size_b,size_c,i;

	int uriage_total=0,zaiko_total_r=0,zaiko_total_w=0,zaiko_total=0;
	int kansetuzei=0;

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
	int r_kansetuzei=0,w_kansetuzei=0,e_kansetuzei=0,b_kansetuzei=0;
	int r_hozyokin=0,w_hozyokin=0,e_hozyokin=0;
	int c_syoumouhin=0,g_syoumouhin=0;
	int g_kigyouhozyokin=0;
	int buy_r_r=0,buy_r_w=0;

	int c_genkinzan=0, c_yokinzan=0;
	int r_yokinzan=0,w_yokinzan=0,e_yokinzan=0,b_yokinzan=0;
	long long b_genkinzan=0;
	int loan_l_zan=0,loan_s_zan=0;
	int c_kyuyo=0;

//	fprintf(Retailer," ,  売上 , 製品在庫 , 左辺合計 ,  , 支払利息 , 原料 , 労務費 , 一般管理費 , 減価償却費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	uriage_total=0;
	zaiko_total_r=0;
	zaiko_total_w=0;
	int a,b,c,d,e,f,g,h,y;//a：給与,b：ボーナス、c：原料、d：設備、e、売上,
				        //f：受け取り利息、g：支払利息、h：減価償却、y：利益z：在庫
	for(i=0;i<size_r;i++)
	{
		a=mem_retailer[i]->Get_kyuyo_out();
		ky_r+=a;
		b=mem_retailer[i]->Get_touki_mibarai_bonus()+mem_retailer[i]->Get_mibarai_housyu();;
		bou_r+=b;
		c=mem_retailer[i]->Get_genryou_out();
		genryou+=c;
		d=mem_retailer[i]->Get_setubi_out();
		setubi_r+=d;
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
		y=mem_retailer[i]->Get_touki_rieki_zyouyo();
		ri_r+=y;
		r_yokinzan+=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
		r_kansetuzei+=mem_retailer[i]->Get_tax();
		r_hozyokin-=mem_retailer[i]->Get_hozyokin_out();
		buy_r_r+=mem_retailer[i]->Get_buy_retailer_product_out();
		fprintf(ac_data1,"%d\n",y);
		fprintf(producer_uriage_kyuyo,"%d , %d ,  , ",e+f-r_hozyokin,a+b);
		fprintf(cpara->FI_Get_se_income(),"agentno=%d , %d ,", mem_retailer[i]->Get_Agent_no(),e);
		
//		fprintf(Retailer,"%d , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d , %d ,  , %d\n",mem_retailer[i]->Get_Producer_no(),e,z,e+z,g-f,c,a,b,h,y,g-f+c+a+b+h+y,e+z-(g-f+c+a+b+h+y));
	}
	fprintf(cpara->FI_Get_se_income(),"\n");
	fprintf(producer_uriage_kyuyo,"\n");
//	fprintf(Retailer," , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d , %d ,  , %d\n",uri_r,zaiko_total_r,uri_r+zaiko_total_r,siharisi_r-ukerisi_r,genryou,ky_r,bou_r,syoukyaku_r,ri_r,siharisi_r-ukerisi_r+genryou+ky_r+bou_r+syoukyaku_r+ri_r,uri_r+zaiko_total_r-(siharisi_r-ukerisi_r+genryou+ky_r+bou_r+syoukyaku_r+ri_r));
//	fprintf(Retailer,"\n w \n ,  売上 , 製品在庫 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 減価償却費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	for(i=0;i<size_w;i++) 
	{
		a=mem_whole[i]->Get_kyuyo_out();
		ky_w+=a;
		b=mem_whole[i]->Get_touki_mibarai_bonus()+mem_whole[i]->Get_mibarai_housyu();
		bou_w+=b;
		z=mem_whole[i]->Get_zaiko_out();
		zaiko_total_w+=z;
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
		y=mem_whole[i]->Get_touki_rieki_zyouyo();
		ri_w+=y;
		w_yokinzan+=mem_whole[i]->Get_yokin_suitoutyou_zandaka();
		w_kansetuzei+=mem_whole[i]->Get_tax();
		w_hozyokin-=mem_whole[i]->Get_hozyokin_out();
		buy_r_w+=mem_whole[i]->Get_buy_retailer_product_out();
//		fprintf(Retailer,"%d , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d ,  , %d\n",mem_whole[i]->Get_Producer_no(),e,z,e+z,g-f,a,b,h,y,g-f+a+b+h+y,e+z-(g-f+a+b+h+y));
		
	}
//	fprintf(Retailer," , %d , %d , %d ,   , %d , %d , %d , %d , %d , %d ,  , %d\n",uri_w,zaiko_total_w,uri_w+zaiko_total_w,siharisi_w-ukerisi_w,ky_w,bou_w,syoukyaku_w,ri_w,siharisi_w-ukerisi_w+ky_w+bou_w+syoukyaku_w+ri_w,uri_w+zaiko_total_w-(siharisi_w-ukerisi_w+ky_w+bou_w+syoukyaku_w+ri_w));

//	fprintf(Retailer,"\n e \n ,  売上 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	for(i=0;i<size_e;i++)
	{
		a=mem_equip[i]->Get_kyuyo_out()-mem_equip[i]->Get_bonus_out();
		ky_e+=a;
		b=mem_equip[i]->Get_touki_mibarai_bonus()+mem_equip[i]->Get_mibarai_housyu();
		bou_e+=b;

		e=mem_equip[i]->Get_uriage_out();
		uri_e+=e;
		f=mem_equip[i]->Get_ukerisi_out();
		ukerisi_e+=f;
		g=mem_equip[i]->Get_siharisi_out();
		siharisi_e+=g;
		y=mem_equip[i]->Get_touki_rieki_zyouyo();
		ri_e+=y;
		e_yokinzan+=mem_equip[i]->Get_yokin_suitoutyou_zandaka();
		e_kansetuzei+=mem_equip[i]->Get_tax();
		e_hozyokin-=mem_equip[i]->Get_hozyokin_out();
//		fprintf(Retailer,"%d , %d , %d ,  , %d , %d , %d , %d , %d ,  , %d\n",mem_equip[i]->Get_Producer_no(),e,e,g-f,a,b,y,g-f+a+b+y,e-(g-f+a+b+y));
	}
//	fprintf(Retailer," , %d , %d ,  , %d , %d , %d  , %d , %d ,  , %d\n",uri_e,uri_e,siharisi_e-ukerisi_e,ky_e,bou_e,ri_e,siharisi_e-ukerisi_e+ky_e+bou_e+ri_e,uri_e-(siharisi_e-ukerisi_e+ky_e+bou_e+ri_e));

//	fprintf(Retailer,"\n b \n ,  売上 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 営業余剰 , 右辺合計 , , 右辺左辺合計\n");
	for(i=0;i<size_b;i++)
	{
		a=mem_bank[i]->Get_kyuyo_out();
		ky_b+=a;
		b=mem_bank[i]->Get_touki_mibarai_bonus();
		bou_b+=b;
		e=mem_bank[i]->Get_uriage_out();
		uri_b+=e;
		f=mem_bank[i]->Get_ukerisi_out();
		ukerisi_b+=f;
		g=mem_bank[i]->Get_siharisi_out();
		siharisi_b+=g;
		y=mem_bank[i]->Get_touki_rieki_zyouyo();
		ri_b+=y;
		loan_s_zan=mem_bank[i]->Get_loan_s_zandaka();
		loan_l_zan=mem_bank[i]->Get_loan_l_zandaka();
		b_genkinzan=mem_bank[i]->Get_genkin_ac_l();			//処理の関係で出納帳にずれが生じるため、こちらを使用
		b_kansetuzei+=mem_bank[i]->Get_tax();
//		fprintf(Retailer,"b , %d , %d ,  , %d , %d , %d , %d , %d ,  , %d\n",f,f,g,a,b,y,g+a+b+y,f-(g+a+b+y));
	}
//	fprintf(Retailer," , %d , %d ,   , %d , %d , %d  , %d , %d ,  , %d\n",ukerisi_b,ukerisi_b,siharisi_b,ky_b,bou_b,ri_b,siharisi_b+ky_b+bou_b+ri_b,ukerisi_b-(siharisi_b+ky_b+bou_b+ri_b));
//	fprintf(Retailer,"\n\n");

	int minkan_kyuyo=0,koumuin_kyuyo=0;
	
	for(i=0;i<size_c;i++)
	{
		ukerisi_c+=mem_con[i]->Get_ukerisi_out();
		c_yokinzan+=mem_con[i]->Get_yokin_ac();
		c_genkinzan+=mem_con[i]->Get_genkin_ac();
		c_kyuyo+=mem_con[i]->Get_kyuyo_c_out();
		c_syoumouhin+=mem_con[i]->Get_syoumouhin_out();
		fprintf(ac_data2,"%d\n",mem_con[i]->Get_kyuyo_c_out());
//		fprintf(cpara->FI_Get_free_text(),"kaikei:,%d , suitou:,%d\n",mem_con[i]->Get_yokin_ac(),mem_con[i]->Get_yokin_suitoutyou_zandaka());
		if(mem_con[i]->Get_office_no()!=99999)	minkan_kyuyo+=mem_con[i]->Get_kyuyo_c_out();
		else	koumuin_kyuyo+=mem_con[i]->Get_kyuyo_c_out();

	}

	g_syoumouhin=cg->Get_syoumouhin_out();
	//GDPの計算
	uriage_total=c_syoumouhin+g_syoumouhin+uri_e-ukerisi_c+buy_r_r+buy_r_w;	//企業同士購買をGDPに含む
	zaiko_total=zaiko_total_r+zaiko_total_w;
	kansetuzei=r_kansetuzei+w_kansetuzei+e_kansetuzei+b_kansetuzei;
	fprintf(cpara->FI_GET_OUTPUT_GDP(),"%d\n",uriage_total+zaiko_total_r+zaiko_total_w);
	fprintf(cpara->FI_GET_OUTPUT_Deposit(),"%d\n",c_yokinzan,r_yokinzan+w_yokinzan+e_yokinzan);




	fprintf(GDP,"%d,%d,%d , %d , %d , %d , %d\n",uriage_total,zaiko_total_r+zaiko_total_w,uriage_total+zaiko_total_r+zaiko_total_w,c_syoumouhin,g_syoumouhin,uri_e,buy_r_r+buy_r_w);
	fprintf(cpara->FI_Get_phenom_writer(),"リテイラー売上計上額： , %d , 各エージェント需要合計： , %d , 消費者購買額： , %d , リテイラー購買額 , %d , ホールセラー購買額 , %d , 政府購買額: , %d\n",uri_r,c_syoumouhin+g_syoumouhin+buy_r_r+buy_r_w,c_syoumouhin,buy_r_r,buy_r_w,g_syoumouhin);
	fprintf(cpara->FI_Get_Labor_koteishihon(),"%d , %d\n",i_period,uri_e+buy_r_r+buy_r_w);
	fprintf(market_data,"%d , %d , %d ,  %d , %d , %d , %d , %d , %d , %lld , %d , %d , %d \n",c_kyuyo,minkan_kyuyo,koumuin_kyuyo,c_genkinzan,c_yokinzan,r_yokinzan,w_yokinzan,e_yokinzan,r_yokinzan+w_yokinzan+e_yokinzan,b_genkinzan,loan_s_zan,loan_l_zan,loan_s_zan+loan_l_zan);
	fprintf(agent_no,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d \n",mem_con.size(),mem_retailer.size(),mem_whole.size(),mem_equip.size(),mem_bank.size());
	fprintf(zyunkandata," , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d\n",uri_r,zaiko_total_r,siharisi_r-ukerisi_r,genryou,ky_r,bou_r,syoukyaku_r,buy_r_r,r_hozyokin,ri_r,uri_w,zaiko_total_w,siharisi_w-ukerisi_w,ky_w,bou_w,syoukyaku_w,buy_r_w,w_hozyokin,ri_w,uri_e,siharisi_e-ukerisi_e,ky_e,bou_e,e_hozyokin,ri_e,ukerisi_b,siharisi_b,ky_b,bou_b,ri_b);	
	fprintf(cpara->FI_Get_touki_zyunrieki(),"%d , %d\n",i_period,y);
//	fprintf(zyunkandata," ,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",uri_r,zaiko_total_r,ky_r,ukerisi_r,siharisi_r,ri_r,genryou,setubi_r,uri_w,zaiko_total_w,ky_w,ukerisi_w,siharisi_w,ri_w,setubi_w,uri_e,ky_e,ukerisi_e,siharisi_e,ri_e,uri_b,ky_b,ukerisi_b,siharisi_b,ri_b);

	int r_tyukanzyuyou=0,r_saisyuzyuyou=c_syoumouhin+g_syoumouhin+zaiko_total_r+buy_r_r+buy_r_w;
	int r_tyukantounyu=genryou+siharisi_r-ukerisi_r+buy_r_r,r_arahukakati=ky_r+bou_r+ri_r+syoukyaku_r+r_kansetuzei+r_hozyokin;
	int w_tyukanzyuyou=genryou,w_saisyuzyuyou=zaiko_total_w;
	int w_tyukantounyu=siharisi_w-ukerisi_w+buy_r_w,w_arahukakati=ky_w+bou_w+ri_w+syoukyaku_w+w_kansetuzei+w_hozyokin;
	int e_tyukanzyuyou=0,e_saisyuzyuyou=uri_e;
	int e_tyukantounyu=siharisi_e-ukerisi_e,e_arahukakati=ky_e+bou_e+ri_e+e_kansetuzei+e_hozyokin;
	int b_tyukanzyuyou=-ukerisi_r-ukerisi_w-ukerisi_e+siharisi_r+siharisi_w+siharisi_e,b_saisyuzyuyou=-ukerisi_c;
	int b_tyukantounyu=0,
		b_arahukakati=ky_b+bou_b+ri_b+b_kansetuzei;
	int tyukan_kei;
	int saisyuzyuyou_kei=r_saisyuzyuyou+w_saisyuzyuyou+e_saisyuzyuyou+b_saisyuzyuyou;
	int arahukakati_kei=r_arahukakati+w_arahukakati+e_arahukakati+b_arahukakati;	
	if(r_tyukantounyu+w_tyukantounyu+e_tyukantounyu==r_tyukanzyuyou+w_tyukanzyuyou+e_tyukanzyuyou+b_tyukanzyuyou) tyukan_kei=r_tyukantounyu+w_tyukantounyu+e_tyukantounyu;
	else tyukan_kei=0;
	int zyuyou_gdp=tyukan_kei+saisyuzyuyou_kei;
	int tounyu_gdp=tyukan_kei+arahukakati_kei;

	fprintf(zyunkanhyou,"   ,  r ,  w ,  e ,  b , 中間需要/計 , 支出 , 民間消費 , 政府消費 , 資本形成 , 在庫 , 最終需要 , 計 \n");
//                             r ,  w ,  e ,  b , 中 , 支 , 民 , 政 , 資 , 在 , 最 , 計
	fprintf(zyunkanhyou," r , %d , %d ,  - ,  - , %d ,  - , %d , %d ,  %d , %d , %d , %d \n",0,0,r_tyukanzyuyou,c_syoumouhin,g_syoumouhin,buy_r_r+buy_r_w,zaiko_total_r,r_saisyuzyuyou,r_tyukanzyuyou+r_saisyuzyuyou);
	fprintf(zyunkanhyou," w , %d ,  - ,  - ,  - , %d ,  - ,  - ,  - ,  - , %d , %d , %d \n",genryou,w_tyukanzyuyou,zaiko_total_w,w_saisyuzyuyou,w_tyukanzyuyou+w_saisyuzyuyou);
	fprintf(zyunkanhyou," e ,  - ,  - ,  - ,  - , %d ,  - ,  - ,  - , %d ,  - , %d , %d \n",e_tyukanzyuyou,uri_e,e_saisyuzyuyou,e_tyukanzyuyou+e_saisyuzyuyou);
	fprintf(zyunkanhyou," b , %d , %d , %d ,  - , %d ,  - , %d ,  - ,  - ,  - , %d , %d \n",-ukerisi_r+siharisi_r,-ukerisi_w+siharisi_w,-ukerisi_e+siharisi_e,b_tyukanzyuyou,-ukerisi_c,b_saisyuzyuyou,b_saisyuzyuyou+b_tyukanzyuyou);
	fprintf(zyunkanhyou," 中間需要/計 , %d , %d , %d ,  - , %d ,  - ,  - ,  - ,  - ,  - , %d , %d \n",r_tyukantounyu,w_tyukantounyu,e_tyukantounyu,tyukan_kei,saisyuzyuyou_kei,zyuyou_gdp);
	fprintf(zyunkanhyou," 支出 ,   - ,   - ,  - ,  - ,  - \n");
	fprintf(zyunkanhyou," 雇用所得 , %d , %d , %d , %d  \n",ky_r+bou_r,ky_w+bou_w,ky_e+bou_e,ky_b+bou_b);
	fprintf(zyunkanhyou," 営業余剰 , %d , %d , %d , %d  \n",ri_r,ri_w,ri_e,ri_b);
	fprintf(zyunkanhyou," 減価償却費 , %d , %d ,  - ,  -  \n",syoukyaku_r,syoukyaku_w);
	fprintf(zyunkanhyou," 間接税 , %d , %d , %d , %d  \n",r_kansetuzei,w_kansetuzei,e_kansetuzei,b_kansetuzei);
	fprintf(zyunkanhyou," 補助金 , %d , %d , %d ,  - \n",r_hozyokin,w_hozyokin,e_hozyokin);
	fprintf(zyunkanhyou," 粗付加価値 , %d , %d , %d , %d , %d \n",r_arahukakati,w_arahukakati,e_arahukakati,b_arahukakati,arahukakati_kei);
	fprintf(zyunkanhyou," 計 ,  %d ,  %d ,  %d ,  %d , %d \n",r_tyukantounyu+r_arahukakati,w_tyukantounyu+w_arahukakati,e_tyukantounyu+e_arahukakati,b_tyukantounyu+b_arahukakati,tounyu_gdp );
	fprintf(zyunkanhyou,"\n goukei:%d\n",zyuyou_gdp-tounyu_gdp);

	//貯蓄率の算出

	int c_syunyu=c_kyuyo+ukerisi_c,c_sisyutu=c_syoumouhin;
	int r_syunyu=0,r_sisyutu=0,w_syunyu=0,w_sisyutu=0,e_syunyu=0,e_sisyutu=0;
	int r_zyouyo=0;
	int sum_syunyu=0,sum_sisyutu=0;
	for(i=0;i<int(mem_retailer.size());i++)
	{
		if(mem_retailer[i]->Get_rieki_zyouyo()>0)
		{
		r_syunyu+=mem_retailer[i]->Get_uriage_out()+mem_retailer[i]->Get_ukerisi_out()+mem_retailer[i]->Get_hozyokin_out();
		r_sisyutu+=mem_retailer[i]->Get_kyuyo_out()+mem_retailer[i]->Get_touki_mibarai_bonus()+mem_retailer[i]->Get_mibarai_housyu()+mem_retailer[i]->Get_genryou_out()+mem_retailer[i]->Get_siharisi_out()+mem_retailer[i]->Get_genkasyoukyaku_out();
		}
	}
	for(i=0;i<int(mem_whole.size());i++)
	{
		if(mem_whole[i]->Get_rieki_zyouyo()>0)
		{
		w_syunyu+=mem_whole[i]->Get_uriage_out()+mem_whole[i]->Get_ukerisi_out()+mem_whole[i]->Get_hozyokin_out();
		w_sisyutu+=mem_whole[i]->Get_kyuyo_out()+mem_whole[i]->Get_touki_mibarai_bonus()+mem_whole[i]->Get_mibarai_housyu()+mem_whole[i]->Get_genryou_out()+mem_whole[i]->Get_siharisi_out()+mem_whole[i]->Get_genkasyoukyaku_out();
		}
	}
	for(i=0;i<int(mem_equip.size());i++)
	{
		if(mem_equip[i]->Get_rieki_zyouyo()>0)
		{
		e_syunyu+=mem_equip[i]->Get_uriage_out()+mem_equip[i]->Get_ukerisi_out()+mem_equip[i]->Get_hozyokin_out();
		e_sisyutu+=mem_equip[i]->Get_kyuyo_out()+mem_equip[i]->Get_touki_mibarai_bonus()+mem_equip[i]->Get_mibarai_housyu()+mem_equip[i]->Get_genryou_out()+mem_equip[i]->Get_siharisi_out()+mem_equip[i]->Get_genkasyoukyaku_out();
		}
	}

	sum_syunyu=r_syunyu+w_syunyu+e_syunyu;
	sum_sisyutu=r_sisyutu+w_sisyutu+e_sisyutu;

	fprintf(cpara->FI_Get_Tyotikuritu_consumer()," %d , %d , %lf\n",c_kyuyo,c_syoumouhin,double(double(c_kyuyo-c_syoumouhin)/double(c_kyuyo)));
	fprintf(cpara->FI_Get_Tyotikuritu_uriage_rieki(),"%d , %d , %lf , ",r_syunyu,r_sisyutu,double(double(r_syunyu-r_sisyutu)/double(r_syunyu)));
	fprintf(cpara->FI_Get_Tyotikuritu_uriage_rieki(),"%d , %d , %lf , ",w_syunyu,w_sisyutu,double(double(w_syunyu-w_sisyutu)/double(w_syunyu)));
	fprintf(cpara->FI_Get_Tyotikuritu_uriage_rieki(),"%d , %d , %lf , ",e_syunyu,e_sisyutu,double(double(e_syunyu-e_sisyutu)/double(e_syunyu)));
	fprintf(cpara->FI_Get_Tyotikuritu_uriage_rieki(),"%d , %d , %lf , %d\n",sum_syunyu,sum_sisyutu,double(double(sum_syunyu-sum_sisyutu)/double(sum_syunyu)),r_zyouyo);

}
void CShow::Show_gdp_buy_pro_not_gdp()
{
	int size_r,size_w,size_e,size_b,size_c,i;

	int uriage_total=0,zaiko_total_r=0,zaiko_total_w=0,zaiko_total=0;
	int kansetuzei=0;

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
	int r_kansetuzei=0,w_kansetuzei=0,e_kansetuzei=0,b_kansetuzei=0;
	int r_hozyokin=0,w_hozyokin=0,e_hozyokin=0;
	int c_syoumouhin=0,g_syoumouhin=0;
	int g_kigyouhozyokin=0;
	int buy_r_r=0,buy_r_w=0;

	int c_genkinzan=0, c_yokinzan=0;
	int r_yokinzan=0,w_yokinzan=0,e_yokinzan=0,b_yokinzan=0;
	long long b_genkinzan=0;
	int loan_l_zan=0,loan_s_zan=0;
	int c_kyuyo=0;

//	fprintf(Retailer," ,  売上 , 製品在庫 , 左辺合計 ,  , 支払利息 , 原料 , 労務費 , 一般管理費 , 減価償却費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	uriage_total=0;
	zaiko_total_r=0;
	zaiko_total_w=0;
	int a,b,c,d,e,f,g,h,y;//a：給与,b：ボーナス、c：原料、d：設備、e、売上,
				        //f：受け取り利息、g：支払利息、h：減価償却、y：利益z：在庫
	for(i=0;i<size_r;i++)
	{
		a=mem_retailer[i]->Get_kyuyo_out();
		ky_r+=a;
		b=mem_retailer[i]->Get_touki_mibarai_bonus();
		bou_r+=b;
		c=mem_retailer[i]->Get_genryou_out();
		genryou+=c;
		d=mem_retailer[i]->Get_setubi_out();
		setubi_r+=d;
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
		y=mem_retailer[i]->Get_touki_rieki_zyouyo();
		ri_r+=y;
		r_yokinzan+=mem_retailer[i]->Get_yokin_suitoutyou_zandaka();
		r_kansetuzei+=mem_retailer[i]->Get_tax();
		r_hozyokin-=mem_retailer[i]->Get_hozyokin_out();
		buy_r_r+=mem_retailer[i]->Get_buy_retailer_product_out();
		fprintf(ac_data1,"%d\n",y);
		fprintf(producer_uriage_kyuyo,"%d , %d ,  , ",e+f-r_hozyokin,a+b);
		fprintf(cpara->FI_Get_se_income(),"agentno=%d , %d ,", mem_retailer[i]->Get_Agent_no(),e);
		
//		fprintf(Retailer,"%d , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d , %d ,  , %d\n",mem_retailer[i]->Get_Producer_no(),e,z,e+z,g-f,c,a,b,h,y,g-f+c+a+b+h+y,e+z-(g-f+c+a+b+h+y));
	}
	fprintf(cpara->FI_Get_se_income(),"\n");
	fprintf(producer_uriage_kyuyo,"\n");
//	fprintf(Retailer," , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d , %d ,  , %d\n",uri_r,zaiko_total_r,uri_r+zaiko_total_r,siharisi_r-ukerisi_r,genryou,ky_r,bou_r,syoukyaku_r,ri_r,siharisi_r-ukerisi_r+genryou+ky_r+bou_r+syoukyaku_r+ri_r,uri_r+zaiko_total_r-(siharisi_r-ukerisi_r+genryou+ky_r+bou_r+syoukyaku_r+ri_r));
//	fprintf(Retailer,"\n w \n ,  売上 , 製品在庫 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 減価償却費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	for(i=0;i<size_w;i++) 
	{
		a=mem_whole[i]->Get_kyuyo_out();
		ky_w+=a;
		b=mem_whole[i]->Get_touki_mibarai_bonus();
		bou_w+=b;
		z=mem_whole[i]->Get_zaiko_out();
		zaiko_total_w+=z;
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
		y=mem_whole[i]->Get_touki_rieki_zyouyo();
		ri_w+=y;
		w_yokinzan+=mem_whole[i]->Get_yokin_suitoutyou_zandaka();
		w_kansetuzei+=mem_whole[i]->Get_tax();
		w_hozyokin-=mem_whole[i]->Get_hozyokin_out();
		buy_r_w+=mem_whole[i]->Get_buy_retailer_product_out();
//		fprintf(Retailer,"%d , %d , %d , %d ,  , %d , %d , %d , %d , %d , %d ,  , %d\n",mem_whole[i]->Get_Producer_no(),e,z,e+z,g-f,a,b,h,y,g-f+a+b+h+y,e+z-(g-f+a+b+h+y));
		
	}
//	fprintf(Retailer," , %d , %d , %d ,   , %d , %d , %d , %d , %d , %d ,  , %d\n",uri_w,zaiko_total_w,uri_w+zaiko_total_w,siharisi_w-ukerisi_w,ky_w,bou_w,syoukyaku_w,ri_w,siharisi_w-ukerisi_w+ky_w+bou_w+syoukyaku_w+ri_w,uri_w+zaiko_total_w-(siharisi_w-ukerisi_w+ky_w+bou_w+syoukyaku_w+ri_w));

//	fprintf(Retailer,"\n e \n ,  売上 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 営業余剰 , 右辺合計 ,  , 右辺左辺差\n");
	for(i=0;i<size_e;i++)
	{
		a=mem_equip[i]->Get_kyuyo_out()-mem_equip[i]->Get_bonus_out();
		ky_e+=a;
		b=mem_equip[i]->Get_touki_mibarai_bonus();
		bou_e+=b;

		e=mem_equip[i]->Get_uriage_out();
		uri_e+=e;
		f=mem_equip[i]->Get_ukerisi_out();
		ukerisi_e+=f;
		g=mem_equip[i]->Get_siharisi_out();
		siharisi_e+=g;
		y=mem_equip[i]->Get_touki_rieki_zyouyo();
		ri_e+=y;
		e_yokinzan+=mem_equip[i]->Get_yokin_suitoutyou_zandaka();
		e_kansetuzei+=mem_equip[i]->Get_tax();
		e_hozyokin-=mem_equip[i]->Get_hozyokin_out();
//		fprintf(Retailer,"%d , %d , %d ,  , %d , %d , %d , %d , %d ,  , %d\n",mem_equip[i]->Get_Producer_no(),e,e,g-f,a,b,y,g-f+a+b+y,e-(g-f+a+b+y));
	}
//	fprintf(Retailer," , %d , %d ,  , %d , %d , %d  , %d , %d ,  , %d\n",uri_e,uri_e,siharisi_e-ukerisi_e,ky_e,bou_e,ri_e,siharisi_e-ukerisi_e+ky_e+bou_e+ri_e,uri_e-(siharisi_e-ukerisi_e+ky_e+bou_e+ri_e));

//	fprintf(Retailer,"\n b \n ,  売上 , 左辺合計 ,  , 支払利息 , 労務費 , 一般管理費 , 営業余剰 , 右辺合計 , , 右辺左辺合計\n");
	for(i=0;i<size_b;i++)
	{
		a=mem_bank[i]->Get_kyuyo_out();
		ky_b+=a;
		b=mem_bank[i]->Get_touki_mibarai_bonus();
		bou_b+=b;
		e=mem_bank[i]->Get_uriage_out();
		uri_b+=e;
		f=mem_bank[i]->Get_ukerisi_out();
		ukerisi_b+=f;
		g=mem_bank[i]->Get_siharisi_out();
		siharisi_b+=g;
		y=mem_bank[i]->Get_touki_rieki_zyouyo();
		ri_b+=y;
		loan_s_zan=mem_bank[i]->Get_loan_s_zandaka();
		loan_l_zan=mem_bank[i]->Get_loan_l_zandaka();
		b_genkinzan=mem_bank[i]->Get_genkin_ac_l();			//処理の関係で出納帳にずれが生じるため、こちらを使用
		b_kansetuzei+=mem_bank[i]->Get_tax();
//		fprintf(Retailer,"b , %d , %d ,  , %d , %d , %d , %d , %d ,  , %d\n",f,f,g,a,b,y,g+a+b+y,f-(g+a+b+y));
	}
//	fprintf(Retailer," , %d , %d ,   , %d , %d , %d  , %d , %d ,  , %d\n",ukerisi_b,ukerisi_b,siharisi_b,ky_b,bou_b,ri_b,siharisi_b+ky_b+bou_b+ri_b,ukerisi_b-(siharisi_b+ky_b+bou_b+ri_b));
//	fprintf(Retailer,"\n\n");

	int minkan_kyuyo=0,koumuin_kyuyo=0;
	
	for(i=0;i<size_c;i++)
	{
		ukerisi_c+=mem_con[i]->Get_ukerisi_out();
		c_yokinzan+=mem_con[i]->Get_yokin_ac();
		c_genkinzan+=mem_con[i]->Get_genkin_ac();
		c_kyuyo+=mem_con[i]->Get_kyuyo_c_out();
		c_syoumouhin+=mem_con[i]->Get_syoumouhin_out();
		fprintf(ac_data2,"%d\n",mem_con[i]->Get_kyuyo_c_out());
//		fprintf(cpara->FI_Get_free_text(),"kaikei:,%d , suitou:,%d\n",mem_con[i]->Get_yokin_ac(),mem_con[i]->Get_yokin_suitoutyou_zandaka());
		if(mem_con[i]->Get_office_no()!=99999)	minkan_kyuyo+=mem_con[i]->Get_kyuyo_c_out();
		else	koumuin_kyuyo+=mem_con[i]->Get_kyuyo_c_out();

	}

	g_syoumouhin=cg->Get_syoumouhin_out();
	//GDPの計算
	uriage_total=c_syoumouhin+g_syoumouhin+uri_e-ukerisi_c;	//企業同士購買をGDPに含まない
	zaiko_total=zaiko_total_r+zaiko_total_w;
	kansetuzei=r_kansetuzei+w_kansetuzei+e_kansetuzei+b_kansetuzei;

	fprintf(GDP,"%d,%d,%d , %d , %d\n",uriage_total,zaiko_total_r+zaiko_total_w,uriage_total+zaiko_total_r+zaiko_total_w,c_syoumouhin,g_syoumouhin);
	fprintf(cpara->FI_Get_phenom_writer(),"リテイラー売上計上額： , %d , 各エージェント需要合計： , %d , 消費者購買額： , %d , リテイラー購買額 , %d , ホールセラー購買額 , %d , 政府購買額: , %d\n",uri_r,c_syoumouhin+g_syoumouhin+buy_r_r+buy_r_w,c_syoumouhin,buy_r_r,buy_r_w,g_syoumouhin);

	fprintf(market_data,"%d , %d , %d ,  %d , %d , %d , %d , %d , %d , %lld , %d , %d , %d \n",c_kyuyo,minkan_kyuyo,koumuin_kyuyo,c_genkinzan,c_yokinzan,r_yokinzan,w_yokinzan,e_yokinzan,r_yokinzan+w_yokinzan+e_yokinzan,b_genkinzan,loan_s_zan,loan_l_zan,loan_s_zan+loan_l_zan);
	fprintf(agent_no,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d \n",mem_con.size(),mem_retailer.size(),mem_whole.size(),mem_equip.size(),mem_bank.size());
	fprintf(zyunkandata," , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d\n",uri_r,zaiko_total_r,siharisi_r-ukerisi_r,genryou,ky_r,bou_r,syoukyaku_r,buy_r_r,r_hozyokin,ri_r,uri_w,zaiko_total_w,siharisi_w-ukerisi_w,ky_w,bou_w,syoukyaku_w,buy_r_w,w_hozyokin,ri_w,uri_e,siharisi_e-ukerisi_e,ky_e,bou_e,e_hozyokin,ri_e,ukerisi_b,siharisi_b,ky_b,bou_b,ri_b);	
	fprintf(cpara->FI_Get_touki_zyunrieki(),"%d , %d\n",i_period,y);
//	fprintf(zyunkandata," ,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",uri_r,zaiko_total_r,ky_r,ukerisi_r,siharisi_r,ri_r,genryou,setubi_r,uri_w,zaiko_total_w,ky_w,ukerisi_w,siharisi_w,ri_w,setubi_w,uri_e,ky_e,ukerisi_e,siharisi_e,ri_e,uri_b,ky_b,ukerisi_b,siharisi_b,ri_b);

	int r_tyukanzyuyou=buy_r_r+buy_r_w,r_saisyuzyuyou=c_syoumouhin+g_syoumouhin+zaiko_total_r;
	int r_tyukantounyu=genryou+siharisi_r-ukerisi_r+buy_r_r,r_arahukakati=ky_r+bou_r+ri_r+syoukyaku_r+r_kansetuzei+r_hozyokin;
	int w_tyukanzyuyou=genryou,w_saisyuzyuyou=zaiko_total_w;
	int w_tyukantounyu=siharisi_w-ukerisi_w+buy_r_w,w_arahukakati=ky_w+bou_w+ri_w+syoukyaku_w+w_kansetuzei+w_hozyokin;
	int e_tyukanzyuyou=0,e_saisyuzyuyou=uri_e;
	int e_tyukantounyu=siharisi_e-ukerisi_e,e_arahukakati=ky_e+bou_e+ri_e+e_kansetuzei+e_hozyokin;
	int b_tyukanzyuyou=-ukerisi_r-ukerisi_w-ukerisi_e+siharisi_r+siharisi_w+siharisi_e,b_saisyuzyuyou=-ukerisi_c;
	int b_tyukantounyu=0,
		b_arahukakati=ky_b+bou_b+ri_b+b_kansetuzei;
	int tyukan_kei;
	int saisyuzyuyou_kei=r_saisyuzyuyou+w_saisyuzyuyou+e_saisyuzyuyou+b_saisyuzyuyou;
	int arahukakati_kei=r_arahukakati+w_arahukakati+e_arahukakati+b_arahukakati;	
	if(r_tyukantounyu+w_tyukantounyu+e_tyukantounyu==r_tyukanzyuyou+w_tyukanzyuyou+e_tyukanzyuyou+b_tyukanzyuyou) tyukan_kei=r_tyukantounyu+w_tyukantounyu+e_tyukantounyu;
	else tyukan_kei=0;
	int zyuyou_gdp=tyukan_kei+saisyuzyuyou_kei;
	int tounyu_gdp=tyukan_kei+arahukakati_kei;

	fprintf(zyunkanhyou,"   ,  r ,  w ,  e ,  b , 中間需要/計 , 支出 , 民間消費 , 政府消費 , 資本形成 , 在庫 , 最終需要 , 計 \n");
//                             r ,  w ,  e ,  b , 中 , 支 , 民 , 政 , 資 , 在 , 最 , 計
	fprintf(zyunkanhyou," r , %d , %d ,  - ,  - , %d ,  - , %d , %d ,  - , %d , %d , %d \n",buy_r_r,buy_r_w,r_tyukanzyuyou,c_syoumouhin,g_syoumouhin,zaiko_total_r,r_saisyuzyuyou,r_tyukanzyuyou+r_saisyuzyuyou);
	fprintf(zyunkanhyou," w , %d ,  - ,  - ,  - , %d ,  - ,  - ,  - ,  - , %d , %d , %d \n",genryou,w_tyukanzyuyou,zaiko_total_w,w_saisyuzyuyou,w_tyukanzyuyou+w_saisyuzyuyou);
	fprintf(zyunkanhyou," e ,  - ,  - ,  - ,  - , %d ,  - ,  - ,  - , %d ,  - , %d , %d \n",e_tyukanzyuyou,uri_e,e_saisyuzyuyou,e_tyukanzyuyou+e_saisyuzyuyou);
	fprintf(zyunkanhyou," b , %d , %d , %d ,  - , %d ,  - , %d ,  - ,  - ,  - , %d , %d \n",-ukerisi_r+siharisi_r,-ukerisi_w+siharisi_w,-ukerisi_e+siharisi_e,b_tyukanzyuyou,-ukerisi_c,b_saisyuzyuyou,b_saisyuzyuyou+b_tyukanzyuyou);
	fprintf(zyunkanhyou," 中間需要/計 , %d , %d , %d ,  - , %d ,  - ,  - ,  - ,  - ,  - , %d , %d \n",r_tyukantounyu,w_tyukantounyu,e_tyukantounyu,tyukan_kei,saisyuzyuyou_kei,zyuyou_gdp);
	fprintf(zyunkanhyou," 支出 ,   - ,   - ,  - ,  - ,  - \n");
	fprintf(zyunkanhyou," 雇用所得 , %d , %d , %d , %d  \n",ky_r+bou_r,ky_w+bou_w,ky_e+bou_e,ky_b+bou_b);
	fprintf(zyunkanhyou," 営業余剰 , %d , %d , %d , %d  \n",ri_r,ri_w,ri_e,ri_b);
	fprintf(zyunkanhyou," 減価償却費 , %d , %d ,  - ,  -  \n",syoukyaku_r,syoukyaku_w);
	fprintf(zyunkanhyou," 間接税 , %d , %d , %d , %d  \n",r_kansetuzei,w_kansetuzei,e_kansetuzei,b_kansetuzei);
	fprintf(zyunkanhyou," 補助金 , %d , %d , %d ,  - \n",r_hozyokin,w_hozyokin,e_hozyokin);
	fprintf(zyunkanhyou," 粗付加価値 , %d , %d , %d , %d , %d \n",r_arahukakati,w_arahukakati,e_arahukakati,b_arahukakati,arahukakati_kei);
	fprintf(zyunkanhyou," 計 ,  %d ,  %d ,  %d ,  %d , %d \n",r_tyukantounyu+r_arahukakati,w_tyukantounyu+w_arahukakati,e_tyukantounyu+e_arahukakati,b_tyukantounyu+b_arahukakati,tounyu_gdp );
	fprintf(zyunkanhyou,"\n goukei:%d\n",zyuyou_gdp-tounyu_gdp);

}
void CShow::show_income()
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
//	fprintf(se_income," , , , , , , , , , , , , , , ,sum=%9d  sum_r=%9d  sum_w=%9d\n",sum,sum_r,sum_w);削除対象、おそらく現在未使用、不要と考えられる2010/11/25

}

void CShow::Show_bought_product_class()
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
					{
						ncon++;//同一生産者、同一製品種別の購入製品数の合計
	//					printf("i=%d c1=%d c2=%d k=%d mem_buy_price=%d\n",i,mem_retailer[i]->Get_class_no(j),mem_buy[k]->Get_class_no(),k,mem_buy[k]->Get_price());
					}
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


void CShow::Show_kimatu_zandaka(int Agent_type)
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

void CShow::Show_kisyu_zandaka(int Agent_type)
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

void CShow::Show_market_product()
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

void CShow::Show_mem_ncr_r()
{
	int i;
	int size;
	size=mem_ncr_r.size();
	fprintf(out,"size=,%3d, mem_ncr_r= ",size);
	for(i=0;i<size;i++) fprintf(out,",%3d ",mem_ncr_r[i]);
	fprintf(out,"\n");
}

void CShow::Show_mem_ncr_w()
{
	int i;
	int size;
	size=mem_ncr_w.size();
	fprintf(out,"size=,%3d, mem_ncr_w= ",size);
	for(i=0;i<size;i++)//9_11 printf("%3d ",mem_ncr_w[i]);
	for(i=0;i<size;i++) fprintf(out,",%3d, ",mem_ncr_w[i]);
	fprintf(out,"\n");
}

void CShow::show_no_buy_code()
{
	int size,i;
	size=mem_con.size();
	for(i=0;i<size;i++) mem_con[i]->Get_no_buy_code();
}

void CShow::Show_Product()
{
	int size;
	//int nsize;
	size=mem_product.size();
	int i;
	int Producer_no_old;
	int Producer_no_new;
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

void CShow::Show_product_class()
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

void CShow::Show_retailer()
{
	//producer no,製品種別数、製品種別番号、それぞれの生産量、価格をﾌﾟﾘﾝﾄｱｳﾄする
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

void CShow::Show_termly_change(int i)
{
	//i番目期間の計算結果をプリントする
	int total_nstock;   //市場のトータル在庫 
	total_nstock=mem_product.size()-Get_product_size_wholesaler();
	if(i==0) fprintf(out2,"   i    total_nstock\n");
	fprintf(out2,"i=,%3d, zaiko=,%4d  \n",i,total_nstock);

}

void CShow::Show_test(int x)
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

void CShow::Show_test_2(int x)
{
	int i,j;
	int size_ncr;
	size_ncr=mem_ncr_r.size();
	int size;
	size=mem_product.size();
	int ncon;
	int sum=0;
	printf("aaaaaaaaaaaaaaaaa %d\n",mem_product.size());
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
		for(j=0;j<size;j++)
		{
			//printf("%d , %d\n",size,j);
			if(mem_product[j]->Get_class_no()==mem_ncr_r[i])
			{
				ncon++;
			}
		}
		fprintf(test4,"%3d,",ncon);
		sum+=ncon;
	}
	fprintf(test4,"%3d,",sum);
	fprintf(test4,"\n");
}


void CShow::Show_wholesaler()
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

void CShow::Show_bought_product_consumer()
{
	int i;
	int size;
	size=mem_con.size();
	for(i=0;i<size;i++){
		mem_con[i]->Show_bought_product();
	}
}

int CShow::Get_product_size_wholesaler()
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
int CShow::Get_product_size_retailer()
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

void CShow::Show_statics_mem_buy()
{
	int i;
	int size,count=0;
	double sum=0;
	size=mem_class_statics.size();
	fprintf(out,"size of mem_class_statics for mem_buy =%4d \n",size);
	fprintf(out1,"size of mem_class_statics for mem_buy =%4d \n",size);

	if(i_period==0){
		for(i=0;i<size;i++){
		//	fprintf(product_price,"Re_製品No.%d,",i+1);
			fprintf(product_price,"Re_製品No.%d,",mem_class_statics[i]->Get_class_no());
			if(i+1==size) fprintf(product_price,"Re_製品平均価格\n");
		}
	}	fprintf(product_price,"%d,",i_period);

	for(i=0;i<size;i++)
	{
		fprintf(out,"class_no=,%3d, max_price=,%6d, min_price=,%6d, ave_price=,%6.1f, ndata=,%6d,\n",mem_class_statics[i]->Get_class_no(),mem_class_statics[i]->Get_max_price(),mem_class_statics[i]->Get_min_price(),mem_class_statics[i]->Get_ave_price(),mem_class_statics[i]->Get_ndata());
		fprintf(out1,"class_no=%3d max_price=%6d min_price=%6d ave_price=%6.1f ndata=%6d\n",mem_class_statics[i]->Get_class_no(),mem_class_statics[i]->Get_max_price(),mem_class_statics[i]->Get_min_price(),mem_class_statics[i]->Get_ave_price(),mem_class_statics[i]->Get_ndata());
		fprintf(test3,"%d , %d , %d , %.0f , , ",mem_class_statics[i]->Get_class_no(),mem_class_statics[i]->Get_max_price(),mem_class_statics[i]->Get_min_price(),mem_class_statics[i]->Get_ave_price());
		fprintf(product_price," %6.1lf,",mem_class_statics[i]->Get_ave_price());
		if(mem_class_statics[i]->Get_ave_price() > 0){
			sum+=mem_class_statics[i]->Get_ave_price();
			count=count+1;
		}
	}
	fprintf(test3,"\n");
	fprintf(product_price,"%6.1lf\n",sum/count);
	
}

void CShow::Show_static_mem_buy_w()
{

	int i;
	int size;
	double sum=0;
	size=mem_class_statics_w.size();
	fprintf(out,"size of mem_class_statics_whole for mem_buy =,%4d, \n",size);
	fprintf(out1,"size of mem_class_statics_whole for mem_buy =,%4d, \n",size);

	if(i_period==1){
		for(i=0;i<size;i++){
//			fprintf(product_price_w,"Wh_製品No.%d,",i+1);
			fprintf(product_price_w,"Wh_製品No.%d,",mem_class_statics_w[i]->Get_class_no());
			if(i+1==size) fprintf(product_price_w,"Wh_製品平均価格\n");
		}
		fprintf(product_price_w,"%d,",i_period-1);
		for(i=0;i<size;i++){
			fprintf(product_price_w,"0,");
			if(i+1==size) fprintf(product_price_w,"0\n");
		}
	}	fprintf(product_price_w,"%d,",i_period);

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
void CShow::Show_statics_mem_product()
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
		fprintf(test,"class_no=%3d max_price_stock=%6d min_price_stock=%6d ave_price_stock=%6.1f ndata_stock=%6d\n",
			mem_class_stock_statics[i]->Get_class_no(),mem_class_stock_statics[i]->Get_max_price_stock(),mem_class_stock_statics[i]->Get_min_price_stock(),mem_class_stock_statics[i]->Get_ave_price_stock(),mem_class_stock_statics[i]->Get_ndata_stock());
		fprintf(out1,"class_no=%3d max_price_stock=%6d min_price_stock=%6d ave_price_stock=%6.1f ndata_stock=%6d\n",
			mem_class_stock_statics[i]->Get_class_no(),mem_class_stock_statics[i]->Get_max_price_stock(),mem_class_stock_statics[i]->Get_min_price_stock(),mem_class_stock_statics[i]->Get_ave_price_stock(),mem_class_stock_statics[i]->Get_ndata_stock());

	}
}
void CShow::Show_Zini()
{
//	ジニ計数
	vector <int > zitudata;			//各消費者所得額
	vector <double > con_ruiseki;	//世帯数累積比率
	vector <double > sho_ruiseki;	//所得額累積比率

	int i;	int sum1=0,sum2=0;	int size=mem_con.size();
	int cons_asset,cons_asset_all=0,shotoku_ruiseki=0;
	double zini1=0,zini2=0;

//	出力ファイルタイトル付け
	if(i_period==0){
		fprintf(cpara->FI_Get_toukei(),"ジニ係数\n");
		for(i=0;i<int(mem_con.size());i++)	fprintf(cpara->FI_Get_lorenz(),"Consumer%d,",mem_con[i]->Get_Consumer_no());
		fprintf(cpara->FI_Get_lorenz(),"\n");
	}	fprintf(cpara->FI_Get_toukei(),"%d,",i_period);	fprintf(cpara->FI_Get_lorenz(),"%d,累積世帯比率,",i_period);

//	現金+預金を別vectorへ格納
	for(i=0;i<int(mem_con.size());i++)
	{
		cons_asset=mem_con[i]->Get_genkin_suitoutyou_zandaka()+mem_con[i]->Get_yokin_suitoutyou_zandaka();
		zitudata.push_back(cons_asset);		cons_asset_all+=cons_asset;
	}	stable_sort(zitudata.begin(),zitudata.end());	//所得額：昇順ソート

//	階層の構成及び他の配列初期化
	for(i=0;i<int(mem_con.size());i++)
	{
		con_ruiseki.push_back(0);
		sho_ruiseki.push_back(0);
	}

//	世帯数、累積世帯数、累積世帯比率
	for(i=0;i<int(con_ruiseki.size());i++)
	{
		con_ruiseki[i]=(double)(i+1)/mem_con.size();
//		fprintf(cpara->FI_Get_toukei(),"%d,",1);				//世帯数
//		fprintf(cpara->FI_Get_toukei(),"%d,",i+1);				//累積世帯数
		if(i==0)	fprintf(cpara->FI_Get_lorenz(),"0,");
		fprintf(cpara->FI_Get_lorenz(),"%6.5f,",con_ruiseki[i]);//累積世帯比率
	}	fprintf(cpara->FI_Get_lorenz(),"\n%d,累積所得比率,",i_period);

//	所得額、累積所得額、累積所得比率
	for(i=0;i<int(sho_ruiseki.size());i++)
	{
		sho_ruiseki[i]=(double)(shotoku_ruiseki+=zitudata[i])/cons_asset_all;
//		fprintf(cpara->FI_Get_toukei(),"%d,",zitudata[i]);		//所得額
//		fprintf(cpara->FI_Get_toukei(),"%d,",shotoku_ruiseki);	//累積所得額
		if(i==0)	fprintf(cpara->FI_Get_lorenz(),"0,");
		fprintf(cpara->FI_Get_lorenz(),"%6.5f,",sho_ruiseki[i]);//累積所得比率
	}	fprintf(cpara->FI_Get_lorenz(),"\n");

//	ジニ係数計算
	for(i=0;i<int(sho_ruiseki.size());i++)
	{
		if(i==0)	zini1+=((con_ruiseki[i]*sho_ruiseki[i])/2);
		else		zini1+=(((con_ruiseki[i]+con_ruiseki[i-1])*(sho_ruiseki[i]-sho_ruiseki[i-1]))/2);
	}	zini1=abs(1-zini1*2);
	fprintf(cpara->FI_Get_toukei(),"%lf\n",zini1);

	zitudata;
	con_ruiseki;
	sho_ruiseki;
}

void CShow::zini()
{
	vector <int > zitudata;
	vector <int > hindo;
	vector <int > kaisou;
	vector <double > hindo_kousei;
	vector <double > kaisou_kousei;
	vector <double > kaisou_ruiseki;

	int i,j,kankaku=5000,max_asset=0,cons_asset;
	int checker=0;
	double zini=0;

	for(i=0;i<int(mem_con.size());i++)
	{
		cons_asset=mem_con[i]->Get_genkin_suitoutyou_zandaka()+mem_con[i]->Get_yokin_suitoutyou_zandaka();
		zitudata.push_back(cons_asset);
		if(max_asset<cons_asset) max_asset=cons_asset;
	}


	//もうひとつのジニ係数計算
	double sagoukei=0,sa,ave_sa,ave,sum=0;
	for(i=0;i<int(zitudata.size());i++)
	{
		sum+=zitudata[i];
		for(j=0;j<int(zitudata.size());j++)
		{
			sa=zitudata[i]-zitudata[j];
			if(sa<0)	sa=sa*(-1);
			sagoukei+=sa;
		}
	}
	ave_sa=sagoukei/zitudata.size();
	ave=sum/zitudata.size();
	zini=ave_sa/(ave*2)/100;

	fprintf(cpara->FI_Get_toukei(),"%lf\n",zini);
	zitudata;
	hindo;
	kaisou;
	hindo_kousei;
	kaisou_kousei;
	kaisou_ruiseki;
}

void CShow::Show_personal_income()
{
	//消費者個人所得
	int i,sum_wage=0;
	for(i=0;i<int(mem_con.size());i++)
	{
		if(i_period==0){
			fprintf(cpara->FI_Get_personal_income(),",消費者%d",mem_con[i]->Get_Consumer_no());
			if(i+1==mem_con.size()) fprintf(cpara->FI_Get_personal_income(),",個人所得平均\n");
		}
	}
	fprintf(cpara->FI_Get_personal_income(),"%d",i_period);
	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_personal_income(),", %d",mem_con[i]->Get_kyuyo_c_out());
		sum_wage+=mem_con[i]->Get_kyuyo_c_out();
	}
	fprintf(cpara->FI_Get_personal_income(),",%d\n",sum_wage/mem_con.size());
}
void CShow::Show_consumer_asset()
{
	//消費者の資産（預金＋現金）
	int i;
	if(i_period==0){
		for(i=0;i<int(mem_con.size());i++)	fprintf(cpara->FI_Get_consumer_asset(),"消費者No.%d,",mem_con[i]->Get_Consumer_no());
		fprintf(cpara->FI_Get_consumer_asset(),"\n");
	}fprintf(cpara->FI_Get_consumer_asset(),"%d,",i_period);
	for(i=0;i<int(mem_con.size());i++)
	{
		fprintf(cpara->FI_Get_consumer_asset(),"%d,",mem_con[i]->Get_genkin_suitoutyou_zandaka()+mem_con[i]->Get_yokin_suitoutyou_zandaka());
	}	fprintf(cpara->FI_Get_consumer_asset(),"\n");
}
void CShow::Show_employ_c()
{
	//所属Agent表記
	int i,size_c,unemp_no=0;
	size_c=mem_con.size();
	if(i_period==0){
		for(i=0;i<size_c;i++)	fprintf(cpara->FI_Get_employ(),"消費者%d,",mem_con[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_employ(),"失業者数 ,");
		fprintf(cpara->FI_Get_employ(),"\n");
	}	
	
	fprintf(cpara->FI_Get_employ(),"%d,",i_period);
	
	for(i=0;i<size_c;i++){
		fprintf(cpara->FI_Get_employ(),"%d,",mem_con[i]->Get_office_no());
		if(mem_con[i]->Get_office_no()==-99999) unemp_no++;
	}	
	fprintf(cpara->FI_Get_employ(),"%d",unemp_no);
	fprintf(cpara->FI_Get_employ(),"\n");
}
void CShow::Show_employ_producer_asset()
{
	//消費者C毎の所属企業Rの従業員一人当り売上高
	int i,j,x;
	int sum=0,sum_m=0,sum_c=0;
	if(i_period==0){
		for(i=0;i<int(mem_con.size());i++){
			for(j=0;j<int(mem_retailer.size());j++){
				if(mem_con[i]->Get_office_no()==mem_retailer[j]->Get_Agent_no())
				{
					fprintf(cpara->FI_Get_employ_producer_asset_C(),"消費者%d資産,",mem_con[i]->Get_Agent_no());
				}
			}
		}
		for(i=0;i<int(mem_con.size());i++){
			for(j=0;j<int(mem_retailer.size());j++){
				if(mem_con[i]->Get_office_no()==mem_retailer[j]->Get_Agent_no())
				{
					fprintf(cpara->FI_Get_employ_producer_asset_R(),"消費者%d所属企業従業員一人当たり売上高,",mem_con[i]->Get_Agent_no());
				}
			}
		}
		fprintf(cpara->FI_Get_employ_producer_asset_R(),"消費者平均資産,所属企業の従業員一人当たり売上高");
	}	fprintf(cpara->FI_Get_employ_producer_asset_C(),"\n%d,",i_period);	fprintf(cpara->FI_Get_employ_producer_asset_R(),"\n%d,",i_period);
	for(i=0;i<int(mem_con.size());i++)
	{		
		for(j=0;j<int(mem_retailer.size());j++){
			if(mem_con[i]->Get_office_no()==mem_retailer[j]->Get_Agent_no())
			{
				fprintf(cpara->FI_Get_employ_producer_asset_C(),"%d,",mem_con[i]->Get_genkin_suitoutyou_zandaka()+mem_con[i]->Get_yokin_suitoutyou_zandaka());
				sum+=1; sum_m+=(mem_con[i]->Get_genkin_suitoutyou_zandaka()+mem_con[i]->Get_yokin_suitoutyou_zandaka());
			}
		}
	}
	for(i=0;i<int(mem_con.size());i++){
		for(j=0;j<int(mem_retailer.size());j++){
			if(mem_con[i]->Get_office_no()==mem_retailer[j]->Get_Agent_no())
			{
				x=int(mem_retailer[j]->Get_uriage_out()/mem_retailer[j]->Get_no_employ());
				fprintf(cpara->FI_Get_employ_producer_asset_R(),"%d,",x);
				sum_c+=x;
			}
		}
	}

	fprintf(cpara->FI_Get_employ_producer_asset_R(),"%d,",sum_m/sum);
	fprintf(cpara->FI_Get_employ_producer_asset_R(),"%d,",sum_c/sum);
}
void CShow::Show_price()
{
	//製品種別価格差
	int i,k=0;
	int sa,count=0;
	double sum_max=0,sum_min=0,sum_ave=0,sum_sa=0,sum_per=0;
	if(i_period==0)
	{
		for(i=0;i<int(mem_class_statics.size());i++)	fprintf(cpara->FI_Get_price_check(),"製品No.%d最高価格,",mem_class_statics[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check(),"製品平均最高価格,");
		for(i=0;i<int(mem_class_statics.size());i++)	fprintf(cpara->FI_Get_price_check(),"製品No.%d最低価格,",mem_class_statics[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check(),"製品平均最低価格,");
		for(i=0;i<int(mem_class_statics.size());i++)	fprintf(cpara->FI_Get_price_check(),"製品No.%d平均価格,",mem_class_statics[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check(),"製品平均価格,");
		for(i=0;i<int(mem_class_statics.size());i++)	fprintf(cpara->FI_Get_price_check(),"製品No.%d価格差,",mem_class_statics[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check(),"製品平均価格差,");
		for(i=0;i<int(mem_class_statics.size());i++)	fprintf(cpara->FI_Get_price_check(),"Re_製品No.%d格差率,",mem_class_statics[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check(),"製品平均価格差格差率\n");
	}	fprintf(cpara->FI_Get_price_check(),"%d,",i_period);

	for(i=0;i<int(mem_class_statics.size());i++)
	{	
		fprintf(cpara->FI_Get_price_check(),"%d,",mem_class_statics[i]->Get_max_price());
		sum_max+=mem_class_statics[i]->Get_max_price();
	}	fprintf(cpara->FI_Get_price_check(),"%6.0f,",sum_max/mem_class_statics.size());
	for(i=0;i<int(mem_class_statics.size());i++)
	{	
		fprintf(cpara->FI_Get_price_check(),"%d,",mem_class_statics[i]->Get_min_price());
		sum_min+=mem_class_statics[i]->Get_min_price();
	}	fprintf(cpara->FI_Get_price_check(),"%6.0f,",sum_min/mem_class_statics.size());
	for(i=0;i<int(mem_class_statics.size());i++)
	{	
		if(mem_class_statics[i]->Get_ave_price() > 0){
			fprintf(cpara->FI_Get_price_check(),"%lf,",mem_class_statics[i]->Get_ave_price());
			sum_ave+=mem_class_statics[i]->Get_ave_price();
			count=count+1;
		}else fprintf(cpara->FI_Get_price_check(),"0,");
	}	fprintf(cpara->FI_Get_price_check(),"%6.0f,",sum_ave/count); count=0;
	for(i=0;i<int(mem_class_statics.size());i++)
	{
		fprintf(cpara->FI_Get_price_check(),"%d,",mem_class_statics[i]->Get_max_price()-mem_class_statics[i]->Get_min_price());
		sum_sa+=(mem_class_statics[i]->Get_max_price()-mem_class_statics[i]->Get_min_price());
	}	fprintf(cpara->FI_Get_price_check(),"%6.0f,",sum_sa/mem_class_statics.size());
	for(i=0;i<int(mem_class_statics.size());i++)
	{
		sa=mem_class_statics[i]->Get_max_price()-mem_class_statics[i]->Get_min_price();
		fprintf(cpara->FI_Get_price_check(),"%lf,",sa/mem_class_statics[i]->Get_ave_price());
		sum_per+=sa/mem_class_statics[i]->Get_ave_price();
	}	fprintf(cpara->FI_Get_price_check(),"%lf\n",sum_per/mem_class_statics.size());
}
void CShow::Show_seisan_class_no()
{
	//製品No別生産者数及び消費者購買可能製品分布
	int i,j,k,cno,sum=0;
	for(i=0;i<int(mem_class_statics.size());i++)	fprintf(cpara->FI_Get_seisan_class_no(),"製品No.%d生産者,",mem_class_statics[i]->Get_class_no());
	for(i=0;i<int(mem_class_statics.size());i++)	fprintf(cpara->FI_Get_seisan_class_no(),"製品No.%d消費者,",mem_class_statics[i]->Get_class_no());
	for(i=0;i<int(mem_retailer.size());i++){
		for(j=0;j<mem_retailer[i]->Get_n_class();j++){
			fprintf(cpara->FI_Get_seisan_class_no(),"生産者No.%d製品No.%d,",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j));
		}
	}	fprintf(cpara->FI_Get_seisan_class_no(),"\n%d,",i_period);

	for(k=0;k<int(mem_class_statics.size());k++)
	{
		cno=mem_class_statics[k]->Get_class_no();
		for(i=0;i<int(mem_retailer.size());i++)
		{
			for(j=0;j<mem_retailer[i]->Get_ncr_p();j++)	if(cno==mem_retailer[i]->Get_class_no(j)) sum+=1;
		}
		fprintf(cpara->FI_Get_seisan_class_no(),"%d,",sum);sum=0;
	}
	for(k=0;k<int(mem_class_statics.size());k++)
	{	
		cno=mem_class_statics[k]->Get_class_no();
		for(i=0;i<int(mem_con.size());i++)
		{
			for(j=0;j<mem_con[i]->Get_ncr_c();j++)	if(cno==mem_con[i]->Get_buy_class_no(j))	sum+=1;
		}
		fprintf(cpara->FI_Get_seisan_class_no(),"%d,",sum);sum=0;
	}//	fprintf(cpara->FI_Get_seisan_class_no(),"\n");
}
void CShow::Show_price_w()
{
	//製品種別価格差
	int i,sa;
	double sum_max=0,sum_min=0,sum_ave=0,sum_sa=0,sum_per=0;
	if(i_period==0){
		for(i=0;i<int(mem_class_statics_w.size());i++)	fprintf(cpara->FI_Get_price_check_w(),"製品No.%d最高価格,",mem_class_statics_w[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check_w(),"製品平均最高価格,");
		for(i=0;i<int(mem_class_statics_w.size());i++)	fprintf(cpara->FI_Get_price_check_w(),"製品No.%d最低価格,",mem_class_statics_w[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check_w(),"製品平均最低価格,");
		for(i=0;i<int(mem_class_statics_w.size());i++)	fprintf(cpara->FI_Get_price_check_w(),"製品No.%d平均価格,",mem_class_statics_w[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check_w(),"製品平均価格,");
		for(i=0;i<int(mem_class_statics_w.size());i++)	fprintf(cpara->FI_Get_price_check_w(),"製品No.%d価格差,",mem_class_statics_w[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check_w(),"製品平均価格差,");
		for(i=0;i<int(mem_class_statics_w.size());i++)	fprintf(cpara->FI_Get_price_check_w(),"Re_製品No.%d格差率,",mem_class_statics_w[i]->Get_class_no());
		fprintf(cpara->FI_Get_price_check_w(),"製品平均価格差格差率\n");
	}	fprintf(cpara->FI_Get_price_check_w(),"%d,",i_period);
	for(i=0;i<int(mem_class_statics_w.size());i++)
	{	
		fprintf(cpara->FI_Get_price_check_w(),"%d,",mem_class_statics_w[i]->Get_max_price());
		sum_max+=mem_class_statics_w[i]->Get_max_price();
	}	fprintf(cpara->FI_Get_price_check_w(),"%6.0f,",sum_max/mem_class_statics_w.size());
	for(i=0;i<int(mem_class_statics_w.size());i++)
	{	
		fprintf(cpara->FI_Get_price_check_w(),"%d,",mem_class_statics_w[i]->Get_min_price());
		sum_min+=mem_class_statics_w[i]->Get_min_price();
	}	fprintf(cpara->FI_Get_price_check_w(),"%6.0f,",sum_min/mem_class_statics_w.size());
	for(i=0;i<int(mem_class_statics_w.size());i++)
	{	
		fprintf(cpara->FI_Get_price_check_w(),"%lf,",mem_class_statics_w[i]->Get_ave_price());
		sum_ave+=mem_class_statics_w[i]->Get_ave_price();
	}	fprintf(cpara->FI_Get_price_check_w(),"%6.0f,",sum_ave/mem_class_statics_w.size());
	for(i=0;i<int(mem_class_statics_w.size());i++)
	{
		fprintf(cpara->FI_Get_price_check_w(),"%d,",mem_class_statics_w[i]->Get_max_price()-mem_class_statics_w[i]->Get_min_price());
		sum_sa+=(mem_class_statics_w[i]->Get_max_price()-mem_class_statics_w[i]->Get_min_price());
	}	fprintf(cpara->FI_Get_price_check_w(),"%6.0f,",sum_sa/mem_class_statics_w.size());
	for(i=0;i<int(mem_class_statics_w.size());i++)
	{
		sa=mem_class_statics_w[i]->Get_max_price()-mem_class_statics_w[i]->Get_min_price();
		fprintf(cpara->FI_Get_price_check_w(),"%lf,",sa/mem_class_statics_w[i]->Get_ave_price());
		sum_per+=sa/mem_class_statics_w[i]->Get_ave_price();
	}	fprintf(cpara->FI_Get_price_check_w(),"%lf\n",sum_per/mem_class_statics_w.size());
}
void CShow::Show_seisan_class_no_w()
{
	//原料製品No別生産者数及び消費者購買可能製品分布
	int i,j,k,cno,sum=0;
	for(i=0;i<int(mem_class_statics_w.size());i++)	fprintf(cpara->FI_Get_seisan_class_no_w(),"原料No.%d生産者,",mem_class_statics_w[i]->Get_class_no());
	for(i=0;i<int(mem_class_statics_w.size());i++)	fprintf(cpara->FI_Get_seisan_class_no_w(),"原料No.%d購入者,",mem_class_statics_w[i]->Get_class_no());
	fprintf(cpara->FI_Get_seisan_class_no_w(),"\n%d,",i_period);

	for(k=0;k<int(mem_class_statics_w.size());k++)
	{
		cno=mem_class_statics_w[k]->Get_class_no();
		for(i=0;i<int(mem_whole.size());i++)
		{
			for(j=0;j<mem_whole[i]->Get_ncr_p();j++)	if(cno==mem_whole[i]->Get_class_no(j)) sum+=1;
		}
		fprintf(cpara->FI_Get_seisan_class_no_w(),"%d,",sum);sum=0;
	}
	for(k=0;k<int(mem_class_statics_w.size());k++)
	{	
		cno=mem_class_statics_w[k]->Get_class_no();
		for(i=0;i<int(mem_retailer.size());i++)
		{
			for(j=0;j<mem_retailer[i]->Get_ncr_p();j++)	if(cno==mem_retailer[i]->Get_material_no(j))	sum+=1;
		}
		fprintf(cpara->FI_Get_seisan_class_no_w(),"%d,",sum);sum=0;
	}//	fprintf(cpara->FI_Get_seisan_class_no_w(),"\n");
}

void CShow::Show_corp_capital()
{
	//企業資本金
	int i;	int size_r,size_w,size_e,size_b;
	int sum_wage_r=0,sum_wage_w=0,sum_wage_e=0;
	size_r=mem_retailer.size();	size_w=mem_whole.size();
	size_e=mem_equip.size();	size_b=mem_bank.size();
	if(i_period==0){
		for(i=0;i<size_r;i++){
			fprintf(cpara->FI_Get_corp_capital(),",Re_%d",mem_retailer[i]->Get_Agent_no());
			if(i+1==size_r) fprintf(cpara->FI_Get_corp_capital(),",Re平均\n");
		}
		for(i=0;i<size_w;i++){
			fprintf(cpara->FI_Get_corp_capital(),",Wh_%d",mem_whole[i]->Get_Agent_no());
			if(i+1==size_w) fprintf(cpara->FI_Get_corp_capital(),",Wh平均\n");
		}
		for(i=0;i<size_e;i++){
			fprintf(cpara->FI_Get_corp_capital(),",Eq_%d",mem_equip[i]->Get_Agent_no());
			if(i+1==size_e) fprintf(cpara->FI_Get_corp_capital(),",3企業平均\n");
		}
		for(i=0;i<size_b;i++){
			fprintf(cpara->FI_Get_corp_capital(),",Ba_%d",mem_bank[i]->Get_Agent_no());
		}
	}
	fprintf(cpara->FI_Get_corp_capital(),"%d",i_period);
	for(i=0;i<size_r;i++){
		fprintf(cpara->FI_Get_corp_capital(),", %d",mem_retailer[i]->Get_shihon_ac());
		sum_wage_r+=mem_retailer[i]->Get_shihon_ac();
	}	fprintf(cpara->FI_Get_corp_capital(),",%d\n",sum_wage_r/size_r);
	for(i=0;i<size_w;i++){
		fprintf(cpara->FI_Get_corp_capital(),", %d",mem_whole[i]->Get_shihon_ac());
		sum_wage_w+=mem_whole[i]->Get_shihon_ac();
	}	fprintf(cpara->FI_Get_corp_capital(),",%d\n",sum_wage_w/size_w);
	for(i=0;i<size_e;i++){
		fprintf(cpara->FI_Get_corp_capital(),", %d",mem_equip[i]->Get_shihon_ac());
		sum_wage_e+=mem_equip[i]->Get_shihon_ac();
	}	fprintf(cpara->FI_Get_corp_capital(),",%d\n",(sum_wage_r+sum_wage_w+sum_wage_e)/(size_r+size_w+size_e));
	for(i=0;i<size_b;i++){
		fprintf(cpara->FI_Get_corp_capital(),", %d",mem_bank[i]->Get_shihon_ac());
	}
}
void CShow::Show_producer_asset()
{
	//各リテイラーの資産（預金＋現金）
	int i;
	if(i_period==0){
		for(i=0;i<int(mem_retailer.size());i++)	fprintf(cpara->FI_Get_producer_asset(),"リテイラーNo.%d,",mem_retailer[i]->Get_Producer_no());
		fprintf(cpara->FI_Get_producer_asset(),"\n");
	}
	fprintf(cpara->FI_Get_producer_asset(),"%d,",i_period);
	for(i=0;i<int(mem_retailer.size());i++)
	{
		fprintf(cpara->FI_Get_producer_asset(),"%d,",mem_retailer[i]->Get_genkin_suitoutyou_zandaka()+mem_retailer[i]->Get_yokin_suitoutyou_zandaka());
	}	fprintf(cpara->FI_Get_producer_asset(),"\n");
}
void CShow::Show_producer_employ()
{
	//各リテイラーの雇用人数
	int i;
	if(i_period==0){
		for(i=0;i<int(mem_retailer.size());i++)	fprintf(cpara->FI_Get_number_employee(),"リテイラーNo.%d,",mem_retailer[i]->Get_Producer_no());
		fprintf(cpara->FI_Get_number_employee(),"\n");
	}
	fprintf(cpara->FI_Get_number_employee(),"%d,%d,",i_period,mem_retailer.size());
	for(i=0;i<int(mem_retailer.size());i++)
	{	
		fprintf(cpara->FI_Get_number_employee(),"%d,",mem_retailer[i]->Get_no_employ());
	}	fprintf(cpara->FI_Get_number_employee(),"\n");
}
void CShow::Show_producer_equip_lv()
{
	//生産者設備レベル
	int i,j,k=0;// int l;
	int count=0;
	double sum_max=0,sum_min=0,sum_ave=0,sum_sa=0,sum_per=0;
	if(i_period==0){

		for(i=0;i<int(mem_retailer.size());i++)	fprintf(cpara->FI_Get_equipment_level(),"生産者No.%d,",mem_retailer[i]->Get_Agent_no());
		fprintf(cpara->FI_Get_equipment_level(),"\n");
	}
	//コブ・ダグラス型生産関数の生産者別係数算出
	for(i=0;i<int(mem_retailer.size());i++)
	{	//生産者の各製品種別で設備レベルを算出
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			if(i_period==0)	fprintf(cpara->FI_Get_seisan_class_no(),"%f,",mem_retailer[i]->Get_cobb_k(j));
		}
	}
	for(i=0;i<int(mem_retailer.size());i++)
	{	//生産者単位で設備レベルを合計して算出
		k=0;
		for(j=0;j<mem_retailer[i]->Get_n_class();j++) k+=mem_retailer[i]->Get_equipment_revel(j);
		fprintf(cpara->FI_Get_equipment_level(),"%d,",k);
	}	fprintf(cpara->FI_Get_equipment_level(),"\n");
	producer_seihin;
}
void CShow::Show_producer_uriage()
{
	//各リテイラーの売上高(総計)
	int i,j;
//	int k,n;
	if(i_period==0){
		for(i=0;i<int(mem_retailer.size());i++)	fprintf(cpara->FI_Get_producer_uriage(),"リテイラーNo.%d,",mem_retailer[i]->Get_Producer_no());
		for(i=0;i<int(mem_retailer.size());i++){
			for(j=0;j<mem_retailer[i]->Get_n_class();j++){
				fprintf(cpara->FI_Get_producer_uriage(),"リテイラーNo.%d製品No.%d,",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j));
			}
		}
	}fprintf(cpara->FI_Get_producer_uriage(),"\n%d,",i_period);
	for(i=0;i<int(mem_retailer.size());i++){	
		fprintf(cpara->FI_Get_producer_uriage(),"%d,",mem_retailer[i]->Get_uriage_out());
	}


	vector<int > mem_uriage;
	vector<int > mem_no;
	vector<int >dummy1;
	vector<int >dummy2;


	if(i_period==0)
	{
		fprintf(cpara->FI_Get_Labor_retailer_uriage_rank(),"期数 , ");
		for(i=0;i<int(mem_retailer.size());i++)	fprintf(cpara->FI_Get_Labor_retailer_uriage_rank(),"リテイラーNo.%d,",mem_retailer[i]->Get_Producer_no());
		fprintf(cpara->FI_Get_Labor_retailer_uriage_rank(),"\n");	
	}
	for(i=0;i<int(mem_retailer.size());i++){	
		mem_uriage.push_back(mem_retailer[i]->Get_uriage_out());
		mem_no.push_back(mem_retailer[i]->Get_Agent_no());
	}


	mem_no=cf->Sort_NUMvec(mem_uriage,mem_no,dummy1,dummy2,1);
//	for(i=0;i<int(mem_no.size());i++)fprintf(cpara->FI_Get_Labor_retailer_uriage_rank(),"%d , ",mem_no[i]);
	fprintf(cpara->FI_Get_Labor_retailer_uriage_rank(),"%d , ",i_period);
	for(i=0;i<int(mem_retailer.size());i++)
	{
			fprintf(cpara->FI_Get_Labor_retailer_uriage_rank(),"%d , ",cf->Comp_INTvec_VAR_return_no(mem_no,mem_retailer[i]->Get_Agent_no())*-1);
	}
	fprintf(cpara->FI_Get_Labor_retailer_uriage_rank(),"\n");



}
void CShow::Show_producer_labor_cost()
{
	//各生産者人件費
	int i,j,sum_wage;
	if(i_period==0){
		fprintf(cpara->FI_Get_labor_cost(),"期数,");
		for(i=0;i<int(mem_retailer.size());i++)	fprintf(cpara->FI_Get_labor_cost(),"リテイラーNo.%d,",mem_retailer[i]->Get_Producer_no());
	}	fprintf(cpara->FI_Get_labor_cost(),"\n%d,",i_period);
	for(i=0;i<int(mem_retailer.size());i++)
	{
		sum_wage=0;
		for(j=0;j<int(mem_con.size());j++)
		{
			if(mem_retailer[i]->Get_Producer_no()==mem_con[j]->Get_office_no())	sum_wage+=mem_con[j]->Get_kyuyo_c_out();
		}	fprintf(cpara->FI_Get_labor_cost(),"%d,",sum_wage);
	}
}
void CShow::Show_producer_seisan_amount()
{
	//各リテイラー製品種別生産量
	int i,j,sum;
	if(i_period==0){	
		fprintf(cpara->FI_Get_seisan_amount(),"期数,");
		for(i=0;i<int(mem_retailer.size());i++){
			for(j=0;j<mem_retailer[i]->Get_n_class();j++){
				fprintf(cpara->FI_Get_seisan_amount(),"リテイラーNo.%d製品No.%d,",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j));
			}
		}
		for(i=0;i<int(mem_retailer.size());i++)	fprintf(cpara->FI_Get_seisan_amount(),"リテイラーNo.%d,",mem_retailer[i]->Get_Producer_no());
	}	fprintf(cpara->FI_Get_seisan_amount(),"\n%d,",i_period);

	for(i=0;i<int(mem_retailer.size());i++)
	{
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)	fprintf(cpara->FI_Get_seisan_amount(),"%d,",mem_retailer[i]->Get_q(j));
	}
	for(i=0;i<int(mem_retailer.size());i++)
	{
		sum=0;
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)	sum+=mem_retailer[i]->Get_q(j);
		fprintf(cpara->FI_Get_seisan_amount(),"%d,",sum);
	}
}
void CShow::Show_producer_genryo_price()
{
	//各リテイラー原料価格
	int i,j,k,sum;
	if(i_period==0){	
		fprintf(cpara->FI_Get_genryo_price(),"期数,"); fprintf(cpara->FI_Get_genryo_no(),"期数,");
		for(i=0;i<int(mem_retailer.size());i++)
		{
			for(j=0;j<mem_retailer[i]->Get_n_class();j++){
				fprintf(cpara->FI_Get_genryo_no(),"R-No.%d製品No.%d,",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j));
				fprintf(cpara->FI_Get_genryo_price(),"R-No.%d製品No.%d:原料No.%d,",mem_retailer[i]->Get_Agent_no(),mem_retailer[i]->Get_class_no(j),mem_retailer[i]->Get_material_no(j));
			}
		}
	}	fprintf(cpara->FI_Get_genryo_price(),"\n%d,",i_period);	fprintf(cpara->FI_Get_genryo_no(),"\n%d,",i_period);

	for(i=0;i<int(mem_retailer.size());i++)
	{
		for(j=0;j<mem_retailer[i]->Get_n_class();j++){
			fprintf(cpara->FI_Get_genryo_price(),"%d,",mem_retailer[i]->Get_material_no(j));
		}
	}
	for(i=0;i<int(mem_retailer.size());i++)
	{
		sum=0;
		for(j=0;j<mem_retailer[i]->Get_n_class();j++)
		{
			for(k=0;k<int(mem_class_statics_w.size());k++)
			{	
				if(mem_retailer[i]->Get_material_no(j)==mem_class_statics_w[k]->Get_class_no())
				{
					fprintf(cpara->FI_Get_genryo_price(),"%6.0f,",mem_class_statics_w[k]->Get_ave_price());
					sum+=int(mem_class_statics_w[k]->Get_ave_price());
				}
			}
		}//	fprintf(cpara->FI_Get_genryo_price(),"%6.0f,",sum/mem_class_statics_w.size());
	}
}

void CShow::Show_print_data()
{
	//消費者の各種csv出力統括
//	Show_personal_income();			//各消費者所得
	Show_consumer_asset();			//各消費者資産(現金+預金)
	Show_employ_c();				//各消費者の雇用先企業
	Show_employ_producer_asset();	//各消費者の雇用先企業Rの従業員一人当たり売上高

	//製品種別csv出力統括
	Show_price();					//リテイラー製品種各価格
	Show_price_w();					//ホールセラー製品種各価格
	if(i_period==0){
		Show_seisan_class_no();		//リテイラー生産製品番号及び各製品効用消費者数
		Show_seisan_class_no_w();	//ホールセラー生産製品番号及び各製品生産者数
	}

	//生産者（現在はリテイラーのみ）の各種csv出力統括
	Show_producer_asset();			//各リテイラー資産
	Show_producer_employ();			//各リテイラー雇用人数
	Show_producer_labor_cost();		//各リテイラー人件費
	Show_producer_genryo_price();	//各リテイラー購入原料価格及び原料平均価格
	Show_producer_seisan_amount();	//各リテイラー製品種別生産量
	Show_producer_equip_lv();		//各リテイラー設備レベル
	Show_producer_uriage();			//各リテイラー売上高(総計,生産品種別)

}

#endif
