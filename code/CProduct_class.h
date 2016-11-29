//CProduct_class.h
#ifndef INC_CPRODUCT_CLASS
#define INC_CPRODUCT_CLASS
#include<stdio.h>
#include<math.h>
#include "CProduct.h"
#include "CRandum.h"
#include "CParameter.h"
#include "CEquip.h"
class CProduct_class
{
	int class_no;//製品種別
	int Producer_no;//その製品を生産したエージェントの番号
	int Producer_type;
	int Consumer_no;
	int Consumer_type;
	int Agent_no;
	int Agent_type;
	int ncr_p;
	int ncr_c;
	int q_init;//初期の生産量
	int q_limit;//生産上限数
	int q_limit_d;//生産下限数
	int q;//生産量
	int qmax;//生産能力
	int q_buy;//購入量
	int nstock;//売れ残り（在庫）の商品数
	int price;
	int price_genka;
	double price_genka_d;//会計処理用に端数使用可能原価
	int koteihi;
	int hendouhi;
	int bankr;
	double weight_buy;
	int max_price;
	int min_price;
	double ave_price;
	int ndata;//購入されたncr_p_i番目製品種別商品の市場全体の数
	int max_price_stock;
	int min_price_stock;
	double ave_price_stock;
	int ndata_stock;
	int rieki;//今期の利益
	int f_up;//価格上昇フラグ
	int f_down;//価格下降フラグ
	int reac_flag;//フラグでの反応値
	int memo_time;//売れ行きの記憶時間
	int buy;//該当製品の自社販売数
	int material_no;//原材料番号
	int material_need;//生産に必要な資材数
	int nop;//実際生産数
	int eqw;//設備投資要求フラグ
	int equipment_revel;	//設備レベルを表す変数
	int limit_genka;		//価格改定用、許容生産量での労務費のかかり方
	int koatari_genryouhi;	//一個当たり原料費
	int no_buy_code[3];
	   //no_buy_code=0:正常に購入
	   //no_buy_code=1:市場に製品がないために購入できなかった
	   //no_buy_code=2:可処分所得の範囲外のため購入できなかった

	double cobb_k;	//コブダグラス型生産関数の計数kの値

	int CR_koatari_genryouhi;//CR用、個当たり原料費所与の値の保管変数、毎期、Calc_costの後に更新で呼び出し


	CProduct *pr;
	CRandum *cr;
	CParameter *cpara;
	
	vector <CProduct *> mem_seihin;
	vector <CProduct *>::iterator del_p;
	vector <int>market_buy;//市場で購入された製品数記憶集合
	
	vector <CEquip *> mem_equip;	//当該クラス用設備群

	FILE *out;
	FILE *test;
public:
	void Set_parameter_class(CParameter * cpar){cpara=cpar;}
	void Set_test(FILE *test0){test=test0;};
	void Set_price_genka(int price_genka1){price_genka=price_genka1;};
	int Get_price_genka(){return price_genka;};
	void Set_out(FILE *out1){out=out1;};
	void Set_nstock(int nstock1){nstock=nstock1;};
	int Get_nstock(){return nstock;};
	void Set_no_buy_code(int code1);
	void Set_q_buy(int q_buy1){q_buy=q_buy1;};
	int Get_q_buy(){return q_buy;};
	void Set_weight_buy(double weight_buy1){weight_buy=weight_buy1;};
	double Get_weight_buy(){return weight_buy;};
	void Set_Producer_no(int Producer_no1){Producer_no=Producer_no1;};
	int Get_Producer_no(){return Producer_no;};
	void Set_Producer_type(int Producer_type1){Producer_type=Producer_type1;};
	int Get_Producer_type(){return Producer_type;};
	void Set_ncr_p(int ncr_p1){ncr_p=ncr_p1;};
	int Get_ncr_p(){return ncr_p;};
	void Set_Consumer_no(int Consumer_no1){Consumer_no=Consumer_no1;};
	int Get_Consumer_no(){return Consumer_no;};
	void Set_Consumer_type(int Consumer_type1){Consumer_type=Consumer_type1;};
	int Get_Consumer_type(){return Consumer_type;};
	void Set_ncr_c(int ncr_c1){ncr_c=ncr_c1;};
	int Get_ncr_c(){return ncr_c;};
	void Set_Agent_no(int Agent_no1){Agent_no=Agent_no1;};
	int Get_Agent_no(){return Agent_no;};
	void Set_price(int price1){price=price1;};
	int Get_price(){return price;};
	void Set_q(int q1){q=q1;};
	int Get_q(){return q;};
	void Set_q_init(int q1){q_init=q1;};
	int Get_q_init(){return q_init;};
	void Set_qmax(int qmax1){qmax=qmax1;};
	int Get_qmax(){return qmax;};
	void Set_koteihi(int koteihi1){koteihi=koteihi1;};
	int Get_koteihi(){return koteihi;};
	void Set_hendouhi(int hendouhi1){hendouhi=hendouhi1;};
	int Get_hendouhi(){return hendouhi;};
	void Set_class_no(int class_no1){class_no=class_no1;};//特定の製品種別に製品種別番号をつける
	int Get_class_no(){return class_no;};
	void Create_product();
	virtual CProduct* Get_product(int i){return mem_seihin[i];};
	void Set_max_price(int max_price1){max_price=max_price1;};
	void Set_min_price(int min_price1){min_price=min_price1;};
	void Set_ave_price(int ave_price1){ave_price=ave_price1;};
	int Get_max_price(){return max_price;};
	int Get_min_price(){return min_price;};
	double Get_ave_price(){return ave_price;};
	void Set_ndata(int ndata1){ndata=ndata1;};
	int Get_ndata(){return ndata;};
	void Erase_mem_seihin();
	void Set_max_price_stock(int max_price_stock1){max_price_stock=max_price_stock1;};
	void Set_min_price_stock(int min_price_stock1){min_price_stock=min_price_stock1;};
	void Set_ave_price_stock(int ave_price_stock1){ave_price_stock=ave_price_stock1;};
	int Get_max_price_stock(){return max_price_stock;};
	int Get_min_price_stock(){return min_price_stock;};
	double Get_ave_price_stock(){return ave_price_stock;};
	void Set_ndata_stock(int ndata_stock1){ndata_stock=ndata_stock1;};
	int Get_ndata_stock(){return ndata_stock;};
	void Watcher();
	void Set_material_no(int no1){material_no=no1;/* printf("%d\n",material_no);*/};
	int Get_material_no(){return material_no;};
	void Set_material_need(int x){material_need=x;};
	int Get_material_need(){return material_need;};
	void Create_product_revised(int i);
	void Set_nop(int x){nop=x;};
	int Get_nop(){return nop;};
	void Set_q_limit(int x){q_limit=x;};
	void Set_q_limit_d(int x){q_limit_d=x;};
	int Get_q_limit(){return q_limit;};
	int Get_q_limit_d(){return q_limit_d;};
	int Expectation();
	int Safe_q();
	void Set_market_buy(int x){market_buy.push_back(x);};
	void Set_buy(){buy=buy+1;}
	void clear_buy();
	void Set_IC(int max_memo_time,int max_reac_flag,int max_e_flag);
	void show_no_buy_code();
	void Flag_up(){f_up++;};
	void Flag_down(){f_down++;};
	int Get_flag();
	int Get_buy(){return buy;};
	void Set_eqw(int x)
	{
		eqw+=x;
		if(eqw<int(double(cpara->GET_PARA_max_e_flag())*double(-1))) eqw=int(double(cpara->GET_PARA_max_e_flag())*double(-1));
		if(eqw>int(double(cpara->GET_PARA_max_e_flag())*double(1.5)))	eqw=int(double(cpara->GET_PARA_max_e_flag())*double(1.5));
	};
	void Reset_eqw(){eqw=0;};
	int Get_eqw(){return eqw;};
	void Set_rieki(int x){rieki=x;};
	int Get_rieki(){return rieki;};
	void Set_bankrup(){bankr++;};
	void Set_bankrup_d(){bankr=bankr-1;};
	int Get_bankrup(){return bankr;};
	void Set_randum(CRandum *cr1){cr=cr1;};
	int Get_equipment_revel(){return equipment_revel;};
	void Set_init_equipment_revel(){equipment_revel=1;};
	void Up_equipment_revel(){equipment_revel++;};
	void Set_limit_genka(int amount){limit_genka=amount;};
	int Get_limit_genka(){return limit_genka;};
	void Set_koatari_genryouhi(int amount){koatari_genryouhi=amount;};
	int Get_koatari_genryouhi(){return koatari_genryouhi;};
	void Set_cobb_k(double amount){cobb_k=amount;};
	double Get_cobb_k(){return cobb_k;}; 
	int Get_last_buy_number(){return market_buy[market_buy.size()-1];};

	void CR_Set_koatari_genryouhi(int x){CR_koatari_genryouhi=x;};
	int CR_Get_koatari_genryouhi(){return CR_koatari_genryouhi;};
	
	

	struct limit_upper_data
	{
		int genkin;		//現在の利益剰余
		int decision;			//フラグによる意思決定　0:フラグ未達　1:フラグ閾値超え
		int price;				//価格
		int koatari_genryouhi;	//個当り原料費
		double cob_k;				//生産係数
		int worker_no;			//労働者数
		int equipment_revel;	//設備数
		int sum_fixed_salary;	//固定給与合計
		double loan_rate_period;	//期当たり利率
		int invest_price;		//設備価格
		int repay_time;			//返済期間
		int repayment_term;		//返済年限
		int loan_state;			//現在の長期借入状況　0:長期借入なし、Get_loan_data()から返済回数が返ってくるので0以外の数では長期借入中
		int loan_state_number;	//現在返済中の件数
		int new_fixed_salary;	//新規雇用者の予定固定給与
		int delta_rieki_emp;	//雇用による利益
		int flag_emp;			//雇用フラグ	0:Δ利益がマイナス→　投資選択肢として考えない　1:投資選択肢として考える
		int delta_rieki_inv;	//設備による利益
		int flag_inv;			//設備フラグ	0:Δ利益がマイナス or 回収年限に満たない→　投資選択肢として考えない　1:投資選択肢として考える
		int keihi;
		int genkasyoukyaku;		//減価償却に関わるコスト　設備投資が複数回条件時のみ発動
	} *limit_up_data;

	void Labor_limit_up_conf(int q){
		if(Get_eqw()>q) limit_up_data->decision=1; 
		else limit_up_data->decision=0;
	};
	void Labor_set_repay_time(int time){limit_up_data->repay_time=time;};
	void Labor_set_genkin(int amount){limit_up_data->genkin=amount;};
	void Labor_set_invest_price(int inv_price){limit_up_data->invest_price=inv_price;};
	void Labor_set_loan_rate_period(double rate){limit_up_data->loan_rate_period=rate;};
	void Labor_set_product_class_data();
	void Labor_set_koatari_genryouhi();
	void Labor_set_worker_no(int no){limit_up_data->worker_no=no;};
	void Labor_set_sum_fixed_salary(int sum){limit_up_data->sum_fixed_salary=sum;};
	void Labor_set_repayment_term(int term){limit_up_data->repayment_term=term;};
	void Labor_set_loan_state(int state){limit_up_data->loan_state=state;};
	void Labor_set_loan_state_number(int state){printf("number=%d\n",state);limit_up_data->loan_state_number=state;};

	void Labor_output_data();
	void Labor_set_data();
	void Labor_set_unemployment_data(int new_salary){limit_up_data->new_fixed_salary=new_salary;};
	void Labor_set_inside_data()
	{
		limit_up_data->koatari_genryouhi=price_genka;
		limit_up_data->genkasyoukyaku=Inv_get_depreciation();	//20120618減価償却費の費用化
		limit_up_data->price=price;
		limit_up_data->cob_k=cobb_k;
		limit_up_data->equipment_revel=equipment_revel;

	};

	void Labor_set_keihi(int a){limit_up_data->keihi=a;}


	void Labor_calc_decision();


	int Labor_Get_decision(){return limit_up_data->decision;};
	int Labor_Get_new_fixed_salary(){return limit_up_data->new_fixed_salary;}
	int Labor_Get_riek_zyouyo(){return limit_up_data->genkin;};
	int Labor_Get_flag_emp(){return limit_up_data->flag_emp;};
	int Labor_Get_flag_inv(){return limit_up_data->flag_inv;};
	int Labor_Get_delta_rieki_emp(){return limit_up_data->delta_rieki_emp;};
	int Labor_Get_delta_rieki_inv(){return limit_up_data->delta_rieki_inv;};
	void Labor_Reset_limit_up_data();
	void Labor_test_up_point(){eqw=20;};
	//ここから設備複数化用関数群
	
	const vector<CEquip *> Inv_Get_mem_equip(){return mem_equip;};	//テスト用

	void Inv_equipment_level_update(){equipment_revel=mem_equip.size();};	//mem_equipmentのサイズをequipment_levelに
	int Inv_get_loan_l_data();			//mem_equipのrepay_principalのサイズ合計（複数の場合あり）を返す
	int Inv_get_loan_l_number();		//mem_equipのrepay_principalに数がある場合その合計を返す
	void Inv_set_equipment(CEquip *ce){mem_equip.push_back(ce);};	//設備をmem_equipに格納
	int Inv_get_loan_amount();			//各mem_equipのrepay_principal[0]を返す
	int Inv_get_inte();					//各mem_equipのrepay_intereset[0]を返す
	void Inv_repayment();				//各mem_equipのrepay_principal[0]とrepay_interest[0]を消す
	int Inv_get_depreciation();			//各mem_equipのdepreciation[0]の値を取り出す
	void Inv_depreciation();			//各mem_equipのdepreciation[0]を消す

	void Inv_Labor_calc_decision();

};

void CProduct_class::Inv_Labor_calc_decision()
{
	//投資と雇用の利益の計算
	double p,c,k,L,K,w,alpha,r0,N0,A0;
	double rieki_zyouyo,rieki_rate;

	int limit=cpara->Get_PARA_Inv_invest_time();		//同時借入の限界数

	p=limit_up_data->price;
	c=limit_up_data->koatari_genryouhi;
	k=limit_up_data->cob_k;
	L=limit_up_data->worker_no;
	K=limit_up_data->equipment_revel;
	w=limit_up_data->new_fixed_salary;
	alpha=0.75;
	r0=limit_up_data->loan_rate_period;
	N0=limit_up_data->repay_time;
	A0=limit_up_data->invest_price;
	rieki_zyouyo=limit_up_data->genkin;
	rieki_rate=cpara->Get_PARA_Labor_invest_capital_rate();

//	printf("p=%lf , c=%lf , k=%lf ,L=%lf \n K=%lf , w=%lf , alpha=0.75 , r0=%lf , N0=%lf , A0=%lf\n",p,c,k,L,K,w,r0,N0,A0);

	if(w==0)	limit_up_data->delta_rieki_emp=0;		//新規雇用者固定給=0=失業者が居ない
	else		limit_up_data->delta_rieki_emp=int(double((p-c)*k*pow(K,1-alpha)*pow(L,alpha)*(pow((1+1/L),alpha)-1)-w));

	switch(cpara->Get_PARA_Labor_invest_capital_switch())
	{
	case 0:
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用しない\n");
		if(limit_up_data->loan_state_number>=limit) limit_up_data->delta_rieki_inv=0;	//loan_stateが0以外　=　長期借入中
		else limit_up_data->delta_rieki_inv=int(double((p-c)*k*pow(L,alpha)*pow(K,1-alpha)*(pow((1+1/K),1-alpha)-1)-(r0+1/N0)*A0)-limit_up_data->genkasyoukyaku);	//20120618減価償却費の費用化
		break;

	case 1:
		fprintf(cpara->FI_Get_Labor_writer(),"p=%lf , c=%lf , k=%lf ,L=%lf \n K=%lf , w=%lf , alpha=0.75 , r0=%lf , N0=%lf , A0=%lf\n",p , c , k ,L , K , w, r0 , N0 , A0);
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用\n");
		if(A0<rieki_zyouyo*rieki_rate) A0=0;
		else if(rieki_zyouyo>0)A0=A0-rieki_zyouyo*rieki_rate;

		fprintf(cpara->FI_Get_Labor_writer(),"設備投資の借入額＝%lf , 利益剰余=%lf , 剰余利用率=%lf\n",A0,rieki_zyouyo,rieki_rate);
		if(limit_up_data->loan_state_number>=limit) limit_up_data->delta_rieki_inv=0;	//loan_stateが0以外　=　長期借入中
		else limit_up_data->delta_rieki_inv=int(double((p-c)*k*pow(L,alpha)*pow(K,1-alpha)*(pow((1+1/K),1-alpha)-1)-(r0+1/N0)*A0));
		break;
	case 2:
		fprintf(cpara->FI_Get_Labor_writer(),"p=%lf , c=%lf , k=%lf ,L=%lf \n K=%lf , w=%lf , alpha=0.75 , r0=%lf , N0=%lf , A0=%lf\n",p , c , k ,L , K , w, r0 , N0 , A0);
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用2\n");
		if(int(double(A0)*double(cpara->Get_PARA_owncash_rate_inv()))>rieki_zyouyo-limit_up_data->keihi) limit_up_data->delta_rieki_inv=0;
		else
		{
			A0=int(double(A0)*double(cpara->Get_PARA_owncash_rate_inv()));
			fprintf(cpara->FI_Get_Labor_writer(),"設備投資の借入額＝%lf , 利益剰余=%lf , 剰余利用率=%lf\n",A0,rieki_zyouyo,rieki_rate);
			
			if(limit_up_data->loan_state_number>=limit) limit_up_data->delta_rieki_inv=0;	//loan_stateが0以外　=　長期借入中
			else limit_up_data->delta_rieki_inv=int(double((p-c)*k*pow(L,alpha)*pow(K,1-alpha)*(pow((1+1/K),1-alpha)-1)-(r0+1/N0)*A0)-limit_up_data->genkasyoukyaku);	//20120618減価償却費の費用化

			if(Producer_no==27) fprintf(cpara->FI_Get_free_text(),"企業番号：%d , 製品番号：%d , 利益：%d,limit_up:%d , limit:%d\n",Producer_no,class_no,limit_up_data->delta_rieki_inv,limit_up_data->loan_state_number,limit);
		}
		break;

	}
	fprintf(cpara->FI_Get_free_text(),"\n");
	fprintf(cpara->FI_Get_Labor_writer(),"class no:%d , delta_rieki_emp:%d , delta_rieki_inv:%d\n" , class_no,limit_up_data->delta_rieki_emp,limit_up_data->delta_rieki_inv);
}

void CProduct_class::Inv_depreciation()
{
	for(int i=0;i<int(mem_equip.size());i++)
		mem_equip[i]->Inv_depreciation();
}
int CProduct_class::Inv_get_depreciation()
{
	int i,sum=0;
	for(i=0;i<int(mem_equip.size());i++)
	{
		sum=mem_equip[i]->Inv_get_depreciation();
	}
	return sum;
}

void CProduct_class::Inv_repayment()
{
	for(int i=0;i<int(mem_equip.size());i++)
		mem_equip[i]->Inv_repayment();
}
int CProduct_class::Inv_get_loan_amount()
{
	int i,sum=0;
	for(i=0;i<int(mem_equip.size());i++)
	{
		sum+=mem_equip[i]->Inv_get_loan_amount();
	}
	return sum;

}

int CProduct_class::Inv_get_inte()
{
	int i,sum=0;
	for(i=0;i<int(mem_equip.size());i++)
	{
		sum+=mem_equip[i]->Inv_get_inte();
	}
	return sum;
}


int CProduct_class::Inv_get_loan_l_data()
{
	int i,sum=0;
	for(i=0;i<int(mem_equip.size());i++)	sum+=mem_equip[i]->Inv_get_loan_l_data();
	return sum;
}
int CProduct_class::Inv_get_loan_l_number()
{
	int i,sum=0;
	for(i=0;i<int(mem_equip.size());i++)	
	{
		sum+=mem_equip[i]->Inv_get_loan_l_number();
	}
	
	if(sum>cpara->GET_PARA_loan_time_limit()) 
	{
		printf("CProduct_class Inve_get_loan_lnumberでサイズが規定以上になっています\n");scanf_s("%d",&i);
	}
	return sum;
}
void CProduct_class::Labor_Reset_limit_up_data()
{
	limit_up_data->decision=0;
	limit_up_data->delta_rieki_emp=0;
	limit_up_data->delta_rieki_inv=0;
	limit_up_data->equipment_revel=0;
	limit_up_data->flag_emp=0;
	limit_up_data->flag_inv=0;
	limit_up_data->invest_price=0;
	limit_up_data->koatari_genryouhi=0;
	limit_up_data->loan_rate_period=0;
	limit_up_data->loan_state=0;
	limit_up_data->new_fixed_salary=0;
	limit_up_data->price=0;
	limit_up_data->repayment_term=0;
	limit_up_data->sum_fixed_salary=0;
	limit_up_data->worker_no=0;
	limit_up_data->keihi=0;
	limit_up_data->genkasyoukyaku=0;

}
void CProduct_class::Labor_output_data()
{
	fprintf(cpara->FI_Get_Labor_writer(),"製品種番号　%d　番のlimit_up_data情報\n",class_no);
	fprintf(cpara->FI_Get_Labor_writer(),"decision:%d , price:%d , koatari_genryouhi:%d , cob_k:%lf\n",limit_up_data->decision,limit_up_data->price,limit_up_data->koatari_genryouhi,limit_up_data->cob_k);
	fprintf(cpara->FI_Get_Labor_writer(),"worker_no:%d , equipment_revel:%d , sum_fixed_salary:%d , loan_rate_period:%lf\n",limit_up_data->worker_no,limit_up_data->equipment_revel,limit_up_data->sum_fixed_salary,limit_up_data->loan_rate_period);	
	fprintf(cpara->FI_Get_Labor_writer(),"invest_price:%d , repay_time:%d , repayment_term:%d , new_fixed_salary:%d\n",limit_up_data->invest_price,limit_up_data->repay_time,limit_up_data->repayment_term,limit_up_data->new_fixed_salary);
	fprintf(cpara->FI_Get_Labor_writer(),"delta_rieki_emp:%d , flag_emp:%d , delta_rieki_inv:%d , flag_inv:%d\n",limit_up_data->delta_rieki_emp,limit_up_data->flag_emp,limit_up_data->delta_rieki_inv,limit_up_data->flag_inv);
}
void CProduct_class::Labor_calc_decision()
{
	//投資と雇用の利益の計算
	double p,c,k,L,K,w,alpha,r0,N0,A0;
	double rieki_zyouyo,rieki_rate;

	p=limit_up_data->price;
	c=limit_up_data->koatari_genryouhi;
	k=limit_up_data->cob_k;
	L=limit_up_data->worker_no;
	K=limit_up_data->equipment_revel;
	w=limit_up_data->new_fixed_salary;
	alpha=0.75;
	r0=limit_up_data->loan_rate_period;
	N0=limit_up_data->repay_time;
	A0=limit_up_data->invest_price;
	rieki_zyouyo=limit_up_data->genkin;
//	rieki_zyouyo=
	rieki_rate=cpara->Get_PARA_Labor_invest_capital_rate();

//	printf("p=%lf , c=%lf , k=%lf ,L=%lf \n K=%lf , w=%lf , alpha=0.75 , r0=%lf , N0=%lf , A0=%lf\n",p,c,k,L,K,w,r0,N0,A0);

	if(w==0)	limit_up_data->delta_rieki_emp=0;		//新規雇用者固定給=0=失業者が居ない
	else		limit_up_data->delta_rieki_emp=int(double((p-c)*k*pow(K,1-alpha)*pow(L,alpha)*(pow((1+1/L),alpha)-1)-w));

	switch(cpara->Get_PARA_Labor_invest_capital_switch())
	{
	case 0:
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用しない\n");
		if(limit_up_data->loan_state_number>=1) limit_up_data->delta_rieki_inv=0;	//loan_stateが0以外　=　長期借入中
		else limit_up_data->delta_rieki_inv=int(double((p-c)*k*pow(L,alpha)*pow(K,1-alpha)*(pow((1+1/K),1-alpha)-1)-(r0+1/N0)*A0));
		break;

	case 1:
		fprintf(cpara->FI_Get_Labor_writer(),"p=%lf , c=%lf , k=%lf ,L=%lf \n K=%lf , w=%lf , alpha=0.75 , r0=%lf , N0=%lf , A0=%lf\n",p , c , k ,L , K , w, r0 , N0 , A0);
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用\n");
		if(A0<rieki_zyouyo*rieki_rate) A0=0;
		else if(rieki_zyouyo>0)A0=A0-rieki_zyouyo*rieki_rate;

		fprintf(cpara->FI_Get_Labor_writer(),"設備投資の借入額＝%lf , 利益剰余=%lf , 剰余利用率=%lf\n",A0,rieki_zyouyo,rieki_rate);
		if(limit_up_data->loan_state_number>=1) limit_up_data->delta_rieki_inv=0;	//loan_stateが0以外　=　長期借入中
		else limit_up_data->delta_rieki_inv=int(double((p-c)*k*pow(L,alpha)*pow(K,1-alpha)*(pow((1+1/K),1-alpha)-1)-(r0+1/N0)*A0));
		break;
	case 2:
		fprintf(cpara->FI_Get_Labor_writer(),"p=%lf , c=%lf , k=%lf ,L=%lf \n K=%lf , w=%lf , alpha=0.75 , r0=%lf , N0=%lf , A0=%lf\n",p , c , k ,L , K , w, r0 , N0 , A0);
		fprintf(cpara->FI_Get_Labor_writer(),"設備投資利益計算_自己資本使用2\n");
		if(A0*double(cpara->Get_PARA_owncash_rate_inv())>rieki_zyouyo-limit_up_data->keihi) limit_up_data->delta_rieki_inv=0;
		else
		{
			A0=int(double(A0)*double(cpara->Get_PARA_owncash_rate_inv()));
			fprintf(cpara->FI_Get_Labor_writer(),"設備投資の借入額＝%lf , 利益剰余=%lf , 剰余利用率=%lf\n",A0,rieki_zyouyo,rieki_rate);
			if(limit_up_data->loan_state_number>=1) limit_up_data->delta_rieki_inv=0;	//loan_stateが0以外　=　長期借入中
			else limit_up_data->delta_rieki_inv=int(double((p-c)*k*pow(L,alpha)*pow(K,1-alpha)*(pow((1+1/K),1-alpha)-1)-(r0+1/N0)*A0));
		}
		break;

	}

	fprintf(cpara->FI_Get_Labor_writer(),"class no:%d , delta_rieki_emp:%d , delta_rieki_inv:%d\n" , class_no,limit_up_data->delta_rieki_emp,limit_up_data->delta_rieki_inv);
}



class CProduct_class_system : public CProduct_class
{
	int max_price;
	int min_price;
	double ave_price;
	int ndata;
public:
	void Set_max_price(int max_price1){max_price=max_price1;};
	void Set_min_price(int min_price1){min_price=min_price1;};
	void Set_ave_price(double ave_price1){ave_price=ave_price1;};
	int Get_max_price(){return max_price;};
	int Get_min_price(){return min_price;};
	double Get_ave_price(){return ave_price;};
	void Set_ndata(int ndata1){ndata=ndata1;};
	int Get_ndata(){return ndata;};


	
};
void CProduct_class::Set_IC(int max_memo_time,int max_reac_flag,int max_e_flag)
{
	memo_time=max_memo_time;//需要予測に用いる期数
		//CProduct_class::clear_buy()にてmarket_buyを定義するのに使用
	      //market_buy.size>memo_timeなら、最初の要素を消去する
	reac_flag=max_reac_flag;//critical_index_price
		//CProduct_class::Get_flag()にて使用
	bankr=0;
	int i;
	buy=0;
////初期設備投資感度
	eqw=0;

	for(i=0;i<3;i++)
	{
		no_buy_code[i]=0;
	}
	f_up=0;
	f_down=0;

	limit_up_data= new limit_upper_data;
}
int CProduct_class::Get_flag()
{
	if(reac_flag<=f_up)//reac_flag:フラグでの反応値
	{
		f_up=0;
		f_down=0;
		return 1;//flag=1、在庫増産調整を数度行っているため価格を上げる
	}
	else if(reac_flag<=f_down)
	{
		f_down=0;
		f_up=0;
		return 2;//flag=2、在庫縮小調整を数度行っているため価格を下げる
	}
	else return 0;
}
void CProduct_class::clear_buy()
{
	int size;//buy:該当製品の自社販売数
	market_buy.push_back(buy);
	
	buy=0;
	size=market_buy.size();
	vector <int>::iterator del_p;
	del_p=market_buy.begin();
	if(size>memo_time)
	{
		market_buy.erase(del_p);
	}
}
int CProduct_class::Safe_q()//安全在庫製品数を返す
{
	int size;
	int n=0,sum=0;
	double ave=0,dec=0,var,sq;
	size=market_buy.size();
	fprintf(test,"market_buy.size()=%d ",size);
	
	ave=double(Expectation());//生産者１人当たりの平均販売数を返す
	fprintf(cpara->FI_Get_free_text2()," ave:%lf , ",ave);
	n=0;
	dec+=(double(market_buy[market_buy.size()-1])-ave)*(double(market_buy[market_buy.size()-1])-ave);
	
	var=sqrt(dec);//var:sigma
	sq=1.65*(var+0.5);
	fprintf(cpara->FI_Get_free_text2(),"dec: %lf , safe:%lf",dec,sq);
	return int(sq);//1.65sigmaを安全在庫と定義する

}
int CProduct_class::Expectation()//販売予測を立てる
{
	//生産者１人当たりの平均販売数を返す
	int size,i,ex,sum=0,n=0;
	size=market_buy.size();
	for(i=0;i<size;i++)
	{
		sum+=market_buy[i];
		n++;
	}
	//sum:当該製品種別の市場全体の生産者毎の売れた製品数（合計）
	//n:当該製品種別の製品を売っている生産者の総数
	ex=sum/n;//生産者１人当たりの平均販売数
	return ex;
}

void CProduct_class::Erase_mem_seihin()
{
	int i;
	int size;
	size=mem_seihin.size();
	for(i=0;i<size;i++)
	{
		del_p=mem_seihin.begin();
		mem_seihin.erase(del_p);
	}
}
void CProduct_class::Set_no_buy_code(int code1)
{
	int code,i,x;
	code=code1;
	for(i=0;i<3;i++)
	{
		if(code==i)
		{
			x=no_buy_code[i];
			no_buy_code[i]=1+x;
		}
	}
}
void CProduct_class::show_no_buy_code()
{
	int i;
	fprintf(test,"con_n=%d , class_n=%d , ",Consumer_no,class_no);
	for(i=0;i<3;i++)
	{
		fprintf(test,"code_n=%d=code_sum=%d , ",i,no_buy_code[i]);
	}
	fprintf(test,"\n");
}
void CProduct_class::Create_product()
{
	//製品をq個生産してCProduct_classのmem_seihinに格納する
	int i;
	Erase_mem_seihin();
	for(i=0;i<q;i++)
	{
		pr=new CProduct;
		pr->Set_lot_no(i);
		pr->Set_Producer_no(Get_Producer_no());
		pr->Set_Agent_no(Get_Agent_no());
		pr->Set_Producer_type(Get_Producer_type());
		pr->Set_class_no(Get_class_no());
		pr->Set_ncr_p(Get_ncr_p());
		pr->Set_product_type();
		pr->Set_price(Get_price());
		pr->Set_price_genka(Get_price_genka());
		pr->Set_state(0);
				    //state=0; at producer
					 //state=1; in the market for sale
					//state=2; at consumer (after being sold)
		pr->Set_material_no(material_no);
		mem_seihin.push_back(pr);
	}
}
void CProduct_class::Create_product_revised(int i)
{
	////////////////

		pr=new CProduct;
		pr->Set_lot_no(i);
		pr->Set_Producer_no(Get_Producer_no());
		pr->Set_Agent_no(Get_Agent_no());
		pr->Set_Producer_type(Get_Producer_type());
		pr->Set_class_no(Get_class_no());
		pr->Set_ncr_p(Get_ncr_p());
		pr->Set_product_type();
		pr->Set_price(Get_price());
		pr->Set_price_genka(Get_price_genka());
		pr->Set_state(0);
		pr->Set_material_no(material_no);
		mem_seihin.push_back(pr);

}
#endif