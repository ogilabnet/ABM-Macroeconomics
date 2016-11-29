//CConsumer.h
#ifndef INC_CCONSUMER
#define INC_CCONSUMER
#include "CRandum.h"
#include "CProduct_class.h"
#include "CProduct.h"
#include "CFunction.h"
#include <vector>
using namespace std;
class CConsumer :public CAgent
{
	int Consumer_no;
	int Consumer_type;
	int n_class;
	int office_no;
	int office_type;
protected:
	int threshold_deposit;		//貯蓄率決定用変数、貯蓄開始給与額の閾値
	double deporate_coefficient;	//貯蓄率決定用変数、貯蓄率決定係数c
	int income;//買い余力(surplus_money)可処分所得
	int income0;//固定給与
	int constant_wage;//固定給与
	int save;
	CProduct_class *pc;
	CFunction *cf;
	vector <CProduct_class *> mem_class_c;//consumer情報保持用のプロダクトクラスobject
public:
	void Print_mem_buy(){
		fprintf(cpara->FI_Get_free_text(),"agent = %d\n",Get_Agent_no());
		for(int i=0;i<int(mem_buy.size());i++)	fprintf(cpara->FI_Get_free_text(),"%d_%d_%d , ",mem_buy[i]->Get_Producer_no(),mem_buy[i]->Get_class_no(),mem_buy[i]->Get_price());
		fprintf(cpara->FI_Get_free_text(),"\n");
	};
	void Reset_mem_buy(){mem_buy.clear();};
	double Get_with_drawal_rate(){return cr->sdrand(cpara->GET_PARA_min_with_drawal_rate(),cpara->GET_PARA_max_with_drawal_rate());};
	void Set_deporate_decision_Coefficient(int threshold,double cofficient){threshold_deposit=threshold;deporate_coefficient=cofficient;};
	void Renew_income();
	int Get_nbuy(){return mem_buy.size();};
	void Create_Product_class_c(int max_memo_time,int max_reac_flag);
	void Set_Consumer_no(int Consumer_no1){Consumer_no=Consumer_no1;};
	int Get_Consumer_no(){return Consumer_no;};
	void Set_Consumer_type(int Consumer_type1){Consumer_type=Consumer_type1;};
	int Get_Consumer_type(){return Consumer_type;};
	void Set_class_no_c(vector <int> mem_ncr_r);
	void Set_class_no_c();
	void Def_min_price_product(vector <CProduct *> mem_product,int *nerror,int *min_price_product,int con_depo);
	template<class T,class U>void Def_min_price_product_new(T &tag,U &mem_product,int *nerror,int *min_price_product1,int con_depo);

	void Set_income(int income1){income=income1;};
	int Def_income(int min,int max);
	void Set_constant_wage(int const_wage){constant_wage=const_wage;};
	int Get_income(){return income;};
	int Get_constant_wage(){return constant_wage;};
	void Set_weight_buy();
	double Get_utility_increment(int q);
	void Show_misbuy_product();
	void Set_office(int no){office_no=no;};
	void Renew_income(int in);
	int Get_income0(){return income0;};
	int Get_save(){return save;};
	void Set_office_type(int type){office_type=type;};
	int Get_office_type(){return office_type;};
	int Get_office_no(){return office_no;};
	void Get_no_buy_code();

	void Set_depo_rate_new(double x){depo_rate=x;};
	void Set_depo_rate_new(double x,int new_income,int kyuyo[]);
	void Set_depo_rate_new2(int new_income);
	void Set_depo_rate_new3(int new_income);
	int Get_buy_class_no(int j){return mem_ncr_c[j];};

	int CR_Get_class_no_c(int x){return mem_class_c[x]->Get_class_no();};


	template<class T> void Laboer_Choice_Producer(T & job_info);

	//～～～～クラスを別クラスにベクターで渡した時の実験跡
//	void Test_our_products(vector <CProduct *> mem_product);
//	template <class T> void Test_our_office(T & mem_retailer);
	//～～～～クラスを別クラスにベクターで渡した時の実験跡

//	void Show_con();
/////Shiwake用関数/////////////////////////////////
	void Set_shiwake_konyu_c(int i_period,int buy_c);
	void Set_shiwake_kyuyo(int i_period,int new_income);
	void Set_shiwake_azuke(int i_period,int depo);
	void Set_shiwake_yokin_hikidashi(int i_period,int depo_money);
	void Set_shiwake_shihon(int i_period,int genkin,int yokin);
	
	void Set_shiwake_hosyoukin(int i_period,int hosyoukin);
	void Set_shiwake_syouhisya_kouhukin(int i_period,int amount);
	int Get_kouhukin_out(){return cac.Get_kouhukin_out();};
///////////////////////////////////////////////////
};

template<class T> void CConsumer::Laboer_Choice_Producer(T & job_info)
{
	int i;
	int max_sal=0,checker=0,Labor_vote_producer_no=99999,max_zyouyo=0;

	switch(cpara->Get_PARA_Labor_choice_office_switch())
	{
	case 0:
		fprintf(cpara->FI_Get_Labor_writer(),"消費者企業選好_高給与余順_起動\n");
		for(i=0;i<int(job_info.size());i++)
		{
			if(job_info[i]->Get_vote_number()<2)		//応募者が2以下の企業を探す
			{
				if(job_info[i]->Get_fixed_salary()>max_sal)	//固定給が高ければ高い企業を選別する
				{
					max_sal=job_info[i]->Get_fixed_salary();
					Labor_vote_producer_no=job_info[i]->Get_producer_no();
					checker=1;
				}
			}
			if(checker==0)	Labor_vote_producer_no=99999;
		}
		break;

	case 1:
		fprintf(cpara->FI_Get_Labor_writer(),"消費者企業選好_高利益剰余順_起動\n");
		for(i=0;i<int(job_info.size());i++)
		{
			if(job_info[i]->Get_vote_number()<2)		//応募者が2以下の企業を探す
			{
				if(job_info[i]->Get_Producer_rieki_zyouyo()>max_zyouyo)	//固定給が高ければ高い企業を選別する
				{
					max_zyouyo=job_info[i]->Get_Producer_rieki_zyouyo();
					Labor_vote_producer_no=job_info[i]->Get_producer_no();
					checker=1;
				}
			}
			if(checker==0)	Labor_vote_producer_no=99999;
		}
		fprintf(cpara->FI_Get_Labor_writer(),"agent_no:%d , producer_no:%d , rieki_zyouyo:%d\n",Agent_no,Labor_vote_producer_no,max_zyouyo);
		break;
	}



	fprintf(cpara->FI_Get_Labor_writer(),"consumer_no:%d , office_type:%d , bote_producer:%d\n",Get_Agent_no(),Get_office_type(),Labor_vote_producer_no);
	for(i=0;i<int(job_info.size());i++)
	{
		if(job_info[i]->Get_producer_no()==Labor_vote_producer_no)
		{
			job_info[i]->Vote(Get_Agent_no());
		}
	}

}
void CConsumer::Set_depo_rate_new(double x,int new_income,int kyuyo_c[])
{
	depo_rate=x+(double)new_income/(double)kyuyo_c[Consumer_no]*10;
	if(depo_rate>1) depo_rate=0.2;
}
void CConsumer::Set_depo_rate_new2(int new_income)
{
	int x=32771/3;	//profit_under_line
	if(new_income<x)
		depo_rate=0;
	else if(x<=new_income && new_income<x*3)
		depo_rate=double(new_income)*0.2/(x*3);

	else if(x*3<=new_income && new_income<x*7.5)
		depo_rate=0.2+double(new_income)*0.3/(x*7.5);

	else
		depo_rate=0.5;
}

void CConsumer::Set_depo_rate_new3(int new_income)
{
	double a=cpara->Get_PARA_Keynes_a();
	double x0,x;
	double c;
	x0=double(threshold_deposit);
	x=double(new_income);
	c=deporate_coefficient;
	
	if(x0>new_income)
	{
		depo_rate=0;
	}
	else
	{
		depo_rate=(a/x0)*(1-x0/x);
	}
	fprintf(cpara->FI_Get_loan(),"final   depo_rate=%lf\n",depo_rate);
}



void CConsumer::Set_shiwake_shihon(int i_period,int genkin,int yokin)
{
	cac.Set_shiwake(i_period,genkin,"現金","初期保持金","株主資本",genkin,0,2);
	cac.Set_shiwake(i_period,yokin,"預金","初期保持金","株主資本",yokin,0,2);
}
void CConsumer::Set_shiwake_hosyoukin(int i_period,int hosyoukin)
{
	cac.Set_shiwake(i_period,hosyoukin,"現金","補償金","給与",hosyoukin,0,3);
}
void CConsumer::Set_shiwake_syouhisya_kouhukin(int i_period,int amount)
{
	cac.Set_shiwake(i_period,amount,"現金","優遇交付金交付","優遇交付金",amount,0,3);
}
void CConsumer::Set_shiwake_konyu_c(int i_period,int buy_c)
{
	cac.Set_shiwake(i_period,buy_c,"消耗品","製品購入","現金",buy_c,1,0);
}
void CConsumer::Set_shiwake_kyuyo(int i_period,int new_income)
{
	cac.Set_shiwake(i_period,new_income,"現金","給与支払い","給与",new_income,0,3);
}
void CConsumer::Set_shiwake_azuke(int i_period,int depo)
{
	cac.Set_shiwake(i_period,depo,"預金","預け入れ","現金",depo,0,0);
}
void CConsumer::Set_shiwake_yokin_hikidashi(int i_period,int depo_money)
{
	cac.Set_shiwake(i_period,depo_money,"現金","預金引出","預金",depo_money,0,0);
}

void CConsumer::Get_no_buy_code()
{
	int size,i;
	size=mem_class_c.size();
	for(i=0;i<size;i++)
	{
		mem_class_c[i]->show_no_buy_code();
	}
	fprintf(cpara->FI_Get_test(),"\n");
}
void CConsumer::Renew_income()
{
	
	int i;
	int size;
	size=mem_class_c.size();
	income=income0;
	for(i=0;i<size;i++)
	{
		mem_class_c[i]->Set_q_buy(0);
	}
}
void CConsumer::Renew_income(int in)
{
	//
	income+=in;
	int i;
	int size;
	size=mem_class_c.size();
	for(i=0;i<size;i++)
	{
		mem_class_c[i]->Set_q_buy(0);
			//consumer情報保持用のプロダクトクラスobject
			//全ての製品種別製品の購入量を0とする。q_buy;//購入量
	}
}

double CConsumer::Get_utility_increment(int q)
{
	if(q==0) return 1.0;
	else if(q==1) return 0.2;
	else if(q==2) return 0.05;
	else return 0;
}
void CConsumer::Set_weight_buy()
{
	int i;
	int size;
	double crr;
	size=mem_class_c.size();
	for(i=0;i<size;i++)
	{
		crr=0.3+0.8*cr->strand();
		mem_class_c[i]->Set_weight_buy(crr);
	}
}

int CConsumer::Def_income(int min,int max)
{
	income=cr->strand(min,max);
	income0=income;//初期の可処分所得
	constant_wage=income;
	return income;
}
void CConsumer::Def_min_price_product(vector <CProduct *> mem_product,int *nerror,int *min_price_product1,int con_depo)
{
	//可処分所得の範囲内で購入できる最大効用製品の内で最低価格の製品を選択する。nerror=0
	//なければnerror=999を返す
	int size,size_pro;
	int i,j;
	int max_utility_pro_no;
	int max_utility_class_no;
	double max_utility;
	size=mem_class_c.size();
	size_pro=mem_product.size();
	int *min_producer=new int[size];//各製品種別毎に最低価格生産者の番号
	int *min_price=new int[size];//各製品種別毎に製品の最低価格
	int *pro_no=new int[size];//各製品種別毎に最低価格の製品番号
	int ncon;
	int nprocon;
	int q_buy;
	int x;//no_buy_codeの記憶用
	
	nprocon=0;//最大効用増分を満たすproduct番号をみつけるためのカウンター
	for(i=0;i<size;i++)
	{
		ncon=0;x=0;
		for(j=0;j<size_pro;j++)
		{
			if(mem_product[j]->Get_class_no()==mem_class_c[i]->Get_class_no())
			{
				if(ncon==0)
				{
					min_price[i]=mem_product[j]->Get_price();
					min_producer[i]=mem_product[j]->Get_Producer_no();
					pro_no[i]=j;
					ncon++;
				}
				else if(min_price[i]>mem_product[j]->Get_price())
				{
					min_price[i]=mem_product[j]->Get_price();
					min_producer[i]=mem_product[j]->Get_Producer_no();
					pro_no[i]=j;
					ncon++;
				}
			}//if(mem_product...の終わり
		}//for(j=0....の終わり
		if(ncon==0)
		{
			//対象とする製品種別番号の商品が市場に存在しない＝購入できない
			min_price[i]=0;
			mem_class_c[i]->Set_no_buy_code(1);
			x=1;
		}
		//購入製品を決定する//		printf("cd=%d\n",con_depo);
		if(min_price[i]!=0 && min_price[i]<con_depo)
		{
			//i番目製品種別について、購入すべき製品が市場に存在しその価格は可処分所得の範囲内にあるので購入する。
			mem_class_c[i]->Set_no_buy_code(0);
			if(nprocon==0)
			{
				max_utility_pro_no=pro_no[i];
				max_utility=mem_class_c[i]->Get_weight_buy()*Get_utility_increment(mem_class_c[i]->Get_q_buy());
				max_utility_class_no=i;
				nprocon++;
			}
			else if(max_utility<mem_class_c[i]->Get_weight_buy()*Get_utility_increment(mem_class_c[i]->Get_q_buy()))
			{
				max_utility_pro_no=pro_no[i];
				max_utility=mem_class_c[i]->Get_weight_buy()*Get_utility_increment(mem_class_c[i]->Get_q_buy());
				max_utility_class_no=i;
				nprocon++;
			}
		}//if(min_price...の終わり
		else if(x!=1) mem_class_c[i]->Set_no_buy_code(2);
	}//if(i=0...の終わり
	if(nprocon==0)
	{	
//		printf("Consumer_no=%3d 購入できる商品はありません、すべての製品種別についてq_buyに変化はありません\n",Consumer_no);
		*nerror=999;
		*min_price_product1=99999;
	}
	else
	{
		//max_utility_pro_noの製品を１個購入します
		q_buy=mem_class_c[max_utility_class_no]->Get_q_buy();
		q_buy++;
		mem_class_c[max_utility_class_no]->Set_q_buy(q_buy);
		mem_buy.push_back(mem_product[max_utility_pro_no]);				//エージェントが保有しているmem_buy
		mem_class_c[max_utility_class_no]->Set_price(mem_product[max_utility_pro_no]->Get_price());
		income=income-mem_class_c[max_utility_class_no]->Get_price();
		mem_product[max_utility_pro_no]->Set_surplus_money(con_depo);
		*nerror=0;
		*min_price_product1=max_utility_pro_no;
	}
	delete [] min_producer;
	delete [] min_price;
	delete [] pro_no;
}
template<class T,class U>void CConsumer::Def_min_price_product_new(T &tag,U &mem_product,int *nerror,int *min_price_product1,int con_depo)
{
	//可処分所得の範囲内で購入できる最大効用製品の内で最低価格の製品を選択する。nerror=0
	//なければnerror=999を返す
	int i,j;
	int max_utility_pro_no;
	int max_utility_class_no;
	int max_utility_tag_no;
	double max_utility;
	vector <int> min_producer;
	vector <int> min_price;
	vector <int> tag_no;
	int ncon;
	int nprocon;
	int q_buy;
	int x;//no_buy_codeの記憶用
	nprocon=0;//最大効用増分を満たすproduct番号をみつけるためのカウンター

	
	for(i=0;i<int(mem_class_c.size());i++)
	{
		min_producer.push_back(0);
		min_price.push_back(0);
		tag_no.push_back(0);
	}

	//タグから各製品種の最低価格を選出
	for(i=0;i<int(mem_class_c.size());i++)
	{
		ncon=0;x=0;
		for(j=0;j<int(tag.size());j++)
		{
			if(tag[j]->Get_presence_of_stock()==1&&tag[j]->Get_class_no()==mem_class_c[i]->Get_class_no())
			{
				if(ncon==0)
				{
					min_price[i]=tag[j]->Get_price();
					min_producer[i]=tag[j]->Get_Producer_no();
					tag_no[i]=j;
					ncon++;
				}
				else if(min_price[i]>tag[j]->Get_price())
				{
					min_price[i]=tag[j]->Get_price();
					min_producer[i]=tag[j]->Get_Producer_no();
					tag_no[i]=j;
					ncon++;
				}
			}//if(mem_product...の終わり
		}//for(j=0....の終わり
		if(ncon==0)
		{
			//対象とする製品種別番号の商品が市場に存在しない＝購入できない
			min_price[i]=0;
			tag_no[i]=0;
			min_producer[i]=0;
			mem_class_c[i]->Set_no_buy_code(1);
			x=1;
		}
		
	}
	
	
	//製品の購入決定
	for(i=0;i<int(mem_class_c.size());i++)
	{
		//購入製品を決定する//		printf("cd=%d\n",con_depo);
		if(min_price[i]!=0 && min_price[i]<con_depo)
		{
			//i番目製品種別について、購入すべき製品が市場に存在しその価格は可処分所得の範囲内にあるので購入する。
			mem_class_c[i]->Set_no_buy_code(0);
			if(nprocon==0)
			{
				max_utility_tag_no=tag_no[i];
				max_utility=double(mem_class_c[i]->Get_weight_buy())*double(Get_utility_increment(mem_class_c[i]->Get_q_buy()))/double(min_price[i]);
				max_utility_class_no=i;
				nprocon++;
			}
			else if(max_utility<mem_class_c[i]->Get_weight_buy()*Get_utility_increment(mem_class_c[i]->Get_q_buy()))
			{
				max_utility_tag_no=tag_no[i];
				max_utility=double(mem_class_c[i]->Get_weight_buy())*double(Get_utility_increment(mem_class_c[i]->Get_q_buy()))/double(min_price[i]);
				max_utility_class_no=i;
				nprocon++;
			}
		}//if(min_price...の終わり
		else if(x!=1) mem_class_c[i]->Set_no_buy_code(2);
	}

	//製品メンバーから該当製品の添え字を検出
//	fprintf(cpara->FI_Get_free_text(),"\n\n\n\n");
	int checker_p=0;
	if(nprocon!=0)
	{
		for(i=0;i<int(mem_product.size());i++)
		{
//		fprintf(cpara->FI_Get_free_text(),"pro %d==%d , cla  %d==%d\n",mem_product[i]->Get_Producer_no(),tag[max_utility_tag_no]->Get_Producer_no() , mem_product[i]->Get_class_no(),tag[max_utility_tag_no]->Get_class_no());	
			if(mem_product[i]->Get_Producer_no()==tag[max_utility_tag_no]->Get_Producer_no() && mem_product[i]->Get_class_no()==tag[max_utility_tag_no]->Get_class_no())
			{
				max_utility_pro_no=i;
				checker_p=1;
				break;
			}
		}
		if(checker_p==0)
		{
			printf("error\n");
//			fprintf(cpara->FI_Get_free_text(),"Agent=%d\n",Get_Agent_no());
			scanf_s("%d",checker_p);
		}
	}

	
	if(nprocon==0||checker_p==0)
	{
//		printf("Consumer_no=%3d 購入できる商品はありません、すべての製品種別についてq_buyに変化はありません\n",Consumer_no);
		*nerror=999;
		*min_price_product1=99999;
	}
	else
	{
		//max_utility_pro_noの製品を１個購入します
		q_buy=mem_class_c[max_utility_class_no]->Get_q_buy();
		q_buy++;
		mem_class_c[max_utility_class_no]->Set_q_buy(q_buy);
		mem_buy.push_back(mem_product[max_utility_pro_no]);						//エージェントが保有しているmem_buy
		mem_class_c[max_utility_class_no]->Set_price(mem_product[max_utility_pro_no]->Get_price());
		income=income-mem_class_c[max_utility_class_no]->Get_price();
//		cba.set_buy(mem_class_c[max_utility_class_no]->Get_price());
		mem_product[max_utility_pro_no]->Set_surplus_money(con_depo);
		*nerror=0;
		*min_price_product1=max_utility_pro_no;
	}
	min_producer.clear();
	min_price.clear();
	tag_no.clear();
}

void CConsumer::Create_Product_class_c(int max_memo_time,int max_reac_flag)
{
	//ncr_p個のProduct_classのインスタンスを生成する
	int i;
	for(i=0;i<ncr_c;i++){
		pc=new CProduct_class;
		//pc->Set_class_no(cr->strand(1,10));
		pc->Set_Consumer_no(Get_Consumer_no());
		pc->Set_Consumer_type(Get_Consumer_type());
		pc->Set_ncr_c(ncr_c);
		pc->Set_q_buy(0);
		pc->Set_test(cpara->FI_Get_test());
		pc->Set_IC(max_memo_time,max_reac_flag,0);//0=max_e_flag//consumerなので0
		mem_class_c.push_back(pc);
	}
}
void CConsumer::Set_class_no_c(vector <int> mem_ncr_r)
{
	int i,j;
	int ncount;
	int size;
	int crr;
	int size_ncr;
	size_ncr=mem_ncr_r.size();
	size=mem_ncr_c.size();
	if(size!=0){
		for(i=0;i<size;i++) mem_ncr_c.pop_back();
	}
	for(i=0;i<ncr_c;i++){
		size=mem_ncr_c.size();
		ncount=0;
restart:
		crr=cr->strand(0,size_ncr-1);
		//同じ乱数でないことを確認し同じ乱数なら生成しなおす。
		for(j=0;j<size;j++){
			if(mem_ncr_r[crr]==mem_ncr_c[j] && ncount<1000) {
				ncount++;
				goto restart;
			}
		}
		mem_ncr_c.push_back(mem_ncr_r[crr]);
		mem_class_c[i]->Set_class_no(mem_ncr_r[crr]);
		if(i==ncr_c-1){
			fprintf(cpara->FI_Get_out(),"Consumer no=,%3d, size of mem_ncr_c=,%d, member of mem_ncr_c= ",Consumer_no,mem_ncr_c.size());
			for(j=0;j<int(mem_ncr_c.size());j++) {
				fprintf(cpara->FI_Get_out()," ,%3d, ",mem_ncr_c[j]);
			}
			fprintf(cpara->FI_Get_out(),"\n");
		}
	}
}
void CConsumer::Set_class_no_c()
{
	int i,j;
	int ncount;
	int size;
	int crr;
	size=mem_ncr_c.size();
	if(size!=0){
		for(i=0;i<size;i++) mem_ncr_c.pop_back();
	}
	for(i=0;i<ncr_p;i++){
		size=mem_ncr_c.size();
		ncount=0;
restart:
		crr=cr->strand(1,n_class);
		//同じ乱数でないことを確認し同じ乱数なら生成しなおす。
		for(j=0;j<size;j++){
			if(crr==mem_ncr_c[j] && ncount<1000) {
				ncount++;
				goto restart;
			}
		}
		mem_ncr_c.push_back(crr);
		mem_class_c[i]->Set_class_no(crr);
		if(i==ncr_p-1){
			for(j=0;j<int(mem_ncr_c.size());j++){}//9_11 printf(" %3d ",mem_ncr_c[j]);
		}
	}
}


#endif

