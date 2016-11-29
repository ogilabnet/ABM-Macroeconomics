//CSpace_threetype　CSpaceの継承
#ifndef INC_CSPACE_THREETYPE
#define INC_CSPACE_THREETYPE
#include <stdio.h> 
#include <vector>
using namespace std;

class CSpace_threetype : public CSpace
{
	

public:

	void Set_Parameter_class(CParameter * cpar,CFunction *c){cpara=cpar;	cf=c;};
	void Set_CShow(CShow * cla_x){cs=cla_x;};


	//命名規則、（大枠時間）__（時間名）__（関数名）

	template<class T,class U,class V,class W,class X,class Y,class Z> void B__BC__Buy_consumer(T &consumer,U &retailer,V &bank,W &tag,X &mem_product,Y &del_p,Z &mem_buy,int i_period); //購買期_消費者購買_消費者購買
	template<class T,class U,class V,class W,class X,class Y,class Z> void B__BG__Buy_government(T &government, U &retailer, V &bank, W &tag, X &mem_product, Y &del_p, Z &mem_buy, int i_period);		//購買期_政府購買_政府購買
	template<class T,class U,class V,class W,class X,class Y,class Z> void B__BG__Buy_government_assignment(T &government, U &retailer, V &bank, W &tag, X &mem_product, Y &del_p, Z &mem_buy, int i_period);		//指定企業 購買期_政府購買_政府購買
	template<class T,class U,class V,class W,class X,class Y,class Z> void PR__PR__Buy_material_retailer(T &retailer,U &whole,V &bank,W &tag, X &mem_product,Y &del_p,Z &mem_buy,int i,int i_period);		//生産期_リテイラー生産_リテイラー原料購買
	template<class T,class U,class V> void KI__KE__Pay_producer_tax(T &producer,U &bank,V &government,int i_period);
	

	template<class T,class U,class V,class W,class X,class Y,class Z> void CR_B__BC__Buy_consumer(T &consumer,U &retailer,V &bank,W &tag,X &mem_product,Y &del_p,Z &mem_buy,int i_period); //CR_購買期_消費者購買_消費者購買
	
};

template<class T,class U,class V,class W,class X,class Y,class Z> void CSpace_threetype::PR__PR__Buy_material_retailer(T &retailer, U &whole, V &bank, W &tag, X &mem_product, Y &del_p, Z &mem_buy,int i, int i_period)
{
	int k,l,m;int b=0;
	int ncr_p;int p_gen;
	int price_w;
	int material_need,depo_m;
	int x;
	int capital;
	int loan,lack_money;
	int ncon=0,min_pro=0,min_id;
	int sum_buy_amount=0;
	depo_m=retailer[i]->Get_yokin_suitoutyou_zandaka();
	capital=retailer[i]->Get_yokin_suitoutyou_zandaka()+retailer[i]->Get_genkin_suitoutyou_zandaka();//売上集計後の所有金額+depo_mを所有金額とする
	retailer[i]->Set_shiwake_yokin_hikidashi(i_period,depo_m);//預金を全額引き出す
	bank[retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_m);

	//原料購買活動、原料を購入してをmem_bought_pに格納する
	ncr_p=retailer[i]->Get_ncr_p();
	for(k=0;k<ncr_p;k++)
	{
		material_need=retailer[i]->Get_material_need(k);
restart:
		del_p=mem_product.begin();
		x=0;//count
		ncon=0;
		if(material_need>0 && int(mem_product.size())>0)
		{	
			//当該製品種別の中で市場にある最低価格の原料を購入する
			//購入した原料をmem_productから削除する
			//当該製品種別の中で市場にある最低価格の原料を選出する, min_pro, min_idを決定する
			min_pro=9999999;
			min_id=retailer[i]->Decide_buy_material_product_no(tag,mem_product,retailer[i]->Get_material_no(k),i_period);
			if(min_id>-1)
			{
				min_pro=mem_product[min_id]->Get_price();
				ncon=1;
			}
			if(ncon==1)
			{
				del_p=mem_product.begin();
				for(m=0;m<min_id;m++)	del_p++;

				//削除すべき対象をiteraterで指定する
				if(retailer[i]->Get_material_no(k)==mem_product[min_id]->Get_class_no())
				{
					//原料を１個購入し、当該原料の生産者に利益を立てる
					if(retailer[i]->Get_genkin_suitoutyou_zandaka()+retailer[i]->Get_yokin_suitoutyou_zandaka()>=mem_product[min_id]->Get_price())
					{
						//所持金があれば購入する
						material_need=material_need-1;
						retailer[i]->Deliv_material(mem_product[min_id]);
						//購入した原料をmem_bought_pに格納する,	mem_bought_p.push_back(cp);
						price_w=mem_product[min_id]->Get_price();
						p_gen=mem_product[min_id]->Get_price_genka();
						retailer[i]->Set_material(price_w);
						retailer[i]->Plus_buy_p(price_w);
						retailer[i]->Set_capital(capital);
						retailer[i]->Set_shiwake_konyu(i_period,price_w);
						sum_buy_amount+=price_w;
						//当該製品の生産者に利益を立てる
						l=cf->Comp_AGEvec_VAR_return_no(whole,mem_product[min_id]->Get_Producer_no());
						whole[l]->Set_rieki(mem_product[min_id]->Get_price(),mem_product[min_id]->Get_class_no());
						whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
						whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
						bank[whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
						//売れた原料製品をmem_buyに格納し、mem_productから削除する
						mem_buy.push_back(mem_product[min_id]);
						cso->Buy_set_price_tag(tag,mem_product,min_id);	//該当製品タグの在庫表示を変換
						mem_product.erase(del_p);
						goto restart;//material_need>0である限り購入を繰り返す
					}//if(capital>=mem_product[min_id]->Get_price())の終わり
					else
					{
						//所持金が不足
						lack_money=int((material_need*mem_product[min_id]->Get_price())*1.5);
						loan=bank[retailer[i]->Get_bank_no()]->loan_check(lack_money);//lack_money
						if(loan>0)
						{
							//銀行が貸出余力があるので借入れ成功
							//借り入れた資金で原料を購入する
							retailer[i]->Set_shiwake_loan(i_period,lack_money);
							bank[retailer[i]->Get_bank_no()]->Set_shiwake_loan(i_period,lack_money);
							retailer[i]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
							bank[retailer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,lack_money);
							retailer[i]->Set_loan_s(lack_money);
							bank[retailer[i]->Get_bank_no()]->Set_loan_s(lack_money);
							material_need=material_need-1;
							retailer[i]->Deliv_material(mem_product[min_id]);//購入した原料をmem_bought_pに格納する,mem_bought_p.push_back(cp);
							price_w=mem_product[min_id]->Get_price();
							p_gen=mem_product[min_id]->Get_price_genka();
							retailer[i]->Set_material(price_w);
							retailer[i]->Plus_buy_p(price_w);
							retailer[i]->Set_capital(capital);
							retailer[i]->Set_shiwake_konyu(i_period,price_w);
							sum_buy_amount+=price_w;
							//ホールセラーに売上金を添付
							l=cf->Comp_AGEvec_VAR_return_no(whole,mem_product[min_id]->Get_Producer_no());
							whole[l]->Set_rieki(mem_product[min_id]->Get_price(),mem_product[min_id]->Get_class_no());
							whole[l]->Set_shiwake_uriage(i_period,p_gen,price_w);
							whole[l]->Set_shiwake_yokin_azuke(i_period,price_w);
							bank[whole[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,price_w);
							mem_buy.push_back(mem_product[min_id]);

							cso->Buy_set_price_tag(tag,mem_product,min_id);	//該当製品タグの在庫表示を変換
							mem_product.erase(del_p);	//min_id番目の原料をmem_productから削除する
							goto restart;
						}
						else
						{	//借入ができなかった、資金がないため原料を購入できない
							retailer[i]->Set_capital(capital);//所持金をそのまま所持金とする
						}
					}
				}//if(retailer[i]->Get_material_no(k)...の終わり					
				del_p++;
				x++;
			}//if(ncon==1)の終わり
		}//if(material_need>0 && size_wp>0)の終わり
	}//for(k=0;k<ncr_p;k++),全ての原料について購買行動終了,
	retailer[i]->Set_total_price_genka(retailer[i]->Get_total_price_genka());
	int taihi;
	taihi=retailer[i]->Get_genkin_suitoutyou_zandaka();
	retailer[i]->Set_shiwake_yokin_azuke(i_period,taihi);
	bank[retailer[i]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,taihi);
	retailer[i]->Labor_set_genryou(sum_buy_amount);
}

template<class T,class U,class V,class W,class X,class Y,class Z> void CSpace_threetype::B__BG__Buy_government(T &government, U &retailer, V &bank, W &tag, X &mem_product, Y &del_p, Z &mem_buy, int i_period) 
{
	int price_keisu=cpara->GET_PARA_government_price_rate();
	int i,j;
	int g_genkin=0;
	int buy_g,p_gen;
	int check;
	int g_buy_max_price=0;
	int buy_no;
	int b_t_i=0;
	int min_price=0;
	int g_money=0;
	int sum_buy=0;
	int price=0;
	int min_price_no=0;
	cso->Set_price_tag(mem_product,tag);
	g_money=government->Get_koubai_yosan();
	fprintf(cpara->FI_Get_market_product()," %d , ",mem_product.size());

	g_buy_max_price=cso->Extraction_tag_price_highprice(tag);
	g_buy_max_price=g_buy_max_price*2;//念のため、市場内最大価格の2倍計算(この金額を行政資金が下回らないように購買)
	
	
	check=0;
	while(g_money > g_buy_max_price && mem_product.size()>1)
	{	
		buy_no=government->Decide_buy_retailer_product_no(tag,mem_product);		//購買する最低価格製品の決定
		
			price=mem_product[buy_no]->Get_price();
			del_p=mem_product.begin();
			

			for(i=0;i<buy_no;i++)	del_p++;		//製品削除用のイテレータ

			if(cf->Comp_AGEvec_VAR(retailer,mem_product[buy_no]->Get_Producer_no())==1)				//購買予定製品とリテイラー番号が一致するか調査
			{
				j=cf->Comp_AGEvec_VAR_return_no(retailer,mem_product[buy_no]->Get_Producer_no());	//購買予定製品とリテイラー番号が一致するときの添え字ナンバー取得

				retailer[j]->Set_rieki(mem_product[buy_no]->Get_price()*price_keisu,mem_product[buy_no]->Get_class_no());
				check=1;
				buy_g=mem_product[buy_no]->Get_price()*price_keisu;
				p_gen=mem_product[buy_no]->Get_price_genka();
				retailer[j]->Set_shiwake_uriage(i_period,buy_g,p_gen);
				retailer[j]->Set_shiwake_yokin_azuke(i_period,buy_g);
				bank[retailer[j]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_g);
				government->Set_shiwake_koubai(i_period,buy_g);
				g_money=g_money-buy_g;
				sum_buy+=buy_g;
				retailer[j]->Erase_material();
				
				cso->Buy_set_price_tag(tag,mem_product,buy_no);
				mem_buy.push_back(mem_product[buy_no]);
				mem_product.erase(del_p);
			}
			if(check==0) 	bank[0]->In_capital(mem_product[buy_no]->Get_price());
	}


	fprintf(cpara->FI_Get_market_product()," %d , ",mem_product.size());
	fprintf(cpara->FI_Get_gyousei_syouhisya(),"%d　, ",sum_buy);
	for(i=0;i<int(retailer.size());i++) retailer[i]->Reset_buy_p();
	for(i=0;i<int(mem_product.size());i++)
	{
		if(mem_product[i]->Get_price()>100000) fprintf(cpara->FI_Get_free_text(),"ag=%d  , pro=%d , %d \n",mem_product[i]->Get_Agent_no(),mem_product[i]->Get_class_no(),mem_product[i]->Get_price());
	}
}
template<class T,class U,class V,class W,class X,class Y,class Z> void CSpace_threetype::B__BG__Buy_government_assignment(T &government, U &retailer, V &bank, W &tag, X &mem_product, Y &del_p, Z &mem_buy, int i_period) 
{
	double price_keisu=cpara->GET_PARA_government_price_rate();
	int i,j;
	int g_genkin=0;
	int buy_g,p_gen;
	int check;
	int g_buy_max_price=0;
	int buy_no;
	int b_t_i=0;
	int min_price=0;
	int g_money=0;
	int sum_buy=0;
	int price=0;
	int min_price_no=0;
	cso->Set_price_tag(mem_product,tag);
	g_money=government->Get_koubai_yosan();
	fprintf(cpara->FI_Get_market_product()," %d , ",mem_product.size());

	g_buy_max_price=cso->Extraction_tag_price_highprice(tag);
	g_buy_max_price=g_buy_max_price*2;//念のため、市場内最大価格の2倍計算(この金額を行政資金が下回らないように購買)
	printf("teeeest g_money:%d , g_buy_max_price:%d, mem_product_size:%d",g_money,g_buy_max_price,mem_product.size());
	check=0;
	while(g_money > g_buy_max_price && mem_product.size()>1)
	{	
		buy_no=government->Decide_buy_retailer_product_no_assignment(tag,mem_product);		//購買する最低価格製品の決定
		printf("buy_no  %d\n",buy_no);
		if(buy_no>-1)
		{
		
			price=mem_product[buy_no]->Get_price();
			del_p=mem_product.begin();

			for(i=0;i<buy_no;i++)	del_p++;		//製品削除用のイテレータ

			if(cf->Comp_AGEvec_VAR(retailer,mem_product[buy_no]->Get_Producer_no())==1)				//購買予定製品とリテイラー番号が一致するか調査
			{
				j=cf->Comp_AGEvec_VAR_return_no(retailer,mem_product[buy_no]->Get_Producer_no());	//購買予定製品とリテイラー番号が一致するときの添え字ナンバー取得

				retailer[j]->Set_rieki(int(double(mem_product[buy_no]->Get_price())*price_keisu),mem_product[buy_no]->Get_class_no());
				check=1;
				buy_g=int(double(mem_product[buy_no]->Get_price())*price_keisu);
				p_gen=mem_product[buy_no]->Get_price_genka();
				retailer[j]->Set_shiwake_uriage(i_period,buy_g,p_gen);
				retailer[j]->Set_shiwake_yokin_azuke(i_period,buy_g);
				bank[retailer[j]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_g);
				government->Set_shiwake_koubai(i_period,buy_g);
				g_money=g_money-buy_g;
				sum_buy+=buy_g;
				retailer[j]->Erase_material();
				fprintf(cpara->FI_Get_free_text(),"政府購買： , %d\n",mem_product[buy_no]->Get_Producer_no());
				cso->Buy_set_price_tag(tag,mem_product,buy_no);
				mem_buy.push_back(mem_product[buy_no]);
				mem_product.erase(del_p);
			}
			if(check==0) 	bank[0]->In_capital(mem_product[buy_no]->Get_price());
		}
		else break;
	}

	fprintf(cpara->FI_Get_market_product()," %d , ",mem_product.size());
	fprintf(cpara->FI_Get_gyousei_syouhisya(),"%d　, ",sum_buy);
	for(i=0;i<int(retailer.size());i++) retailer[i]->Reset_buy_p();
	for(i=0;i<int(mem_product.size());i++)
	{
		if(mem_product[i]->Get_price()>100000) fprintf(cpara->FI_Get_free_text(),"ag=%d  , pro=%d , %d \n",mem_product[i]->Get_Agent_no(),mem_product[i]->Get_class_no(),mem_product[i]->Get_price());
	}
}

template<class T,class U,class V> void CSpace_threetype::KI__KE__Pay_producer_tax(T &producer, U &bank, V &government,int i_period)
{
	int i,tax;
	for(i=0;i<int(producer.size());i++)
	{
		//消費税の支払い
		tax=producer[i]->Get_shouhi_tax();
		producer[i]->Set_shiwake_yokin_hikidashi(i_period,tax);
		bank[producer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,tax);
		producer[i]->Set_shiwake_shouhi_tax(i_period,tax);

		government->Collect_tax(tax);
		government->Set_taxdate(i_period,930,tax);
		government->Set_shiwake_zeisyu(i_period,tax);

		//法人税の支払い
		tax=producer[i]->Get_tax();
		producer[i]->Set_shiwake_yokin_hikidashi(i_period,tax);
		bank[producer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,tax);
		producer[i]->Set_shiwake_houzin_tax(i_period,tax);
		government->Collect_tax(tax);
		government->Set_taxdate(i_period,910,tax);
		government->Set_shiwake_zeisyu(i_period,tax);
	}
}


template<class T,class U,class V,class W,class X,class Y,class Z> void CSpace_threetype::CR_B__BC__Buy_consumer(T &consumer, U &retailer, V &bank, W &tag, X &mem_product,Y &del_p,Z &mem_buy,int i_period)
{
	int i,j,l,b=0,c_gen=0;
	int k;double rate;
	int depo_money;
	int check;
	int buy_c; int p_gen;
	int nerror=0;
	int min_price_product;
	vector <int> mem_ni;//選択可能消費者の集合
	vector <int> ::iterator p;
	cs->CM_Show_Buy_consumer_top(int(mem_product.size()));	//	CShowへプリント機能移転、依存度高ければ削除下の行が内容
	for(i=0;i<int(consumer.size());i++) mem_ni.push_back(i);



	for(k=0;k<int(consumer.size());k++)
	{
		i=cf->Random_choice_int(mem_ni,p,cr);
		consumer[i]->Reset_mem_buy();
		rate=consumer[i]->Get_with_drawal_rate();

		depo_money=int(consumer[i]->Get_yokin_suitoutyou_zandaka()*rate);

		consumer[i]->Renew_income(depo_money);	//購入データを初期化している（要機能改善）20110224
		consumer[i]->Set_shiwake_yokin_hikidashi(i_period,depo_money);
		bank[consumer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_money);

		c_gen=consumer[i]->Get_genkin_suitoutyou_zandaka();
		if(k%10==0)fprintf(cpara->FI_Get_phenom_writer(),"consumer=%d , money=%d\n",consumer[i]->Get_Agent_no(),c_gen);


restart:
//		printf("%d , i=%d\n",consumer[i]->Get_Agent_no(),i);
		consumer[i]->Def_min_price_product_new(tag,mem_product,&nerror,&min_price_product,consumer[i]->Get_genkin_suitoutyou_zandaka());
		check=0;
		
		if(nerror==0)
		{
			for(j=0;j<int(mem_product.size());j++)
			{
				if(j==0) 
				{
					del_p=mem_product.begin();
					if(j==min_price_product)
					{
						//mem_product[j]をmem_buyに入れる
						if(cf->Comp_AGEvec_VAR(retailer,mem_product[j]->Get_Producer_no())==1)
						{
							l=cf->Comp_AGEvec_VAR_return_no(retailer,mem_product[j]->Get_Producer_no());
							retailer[l]->Set_rieki(mem_product[j]->Get_price(),mem_product[j]->Get_class_no());
							check=1;
							buy_c=mem_product[j]->Get_price();
							p_gen=mem_product[j]->Get_price_genka();
							consumer[i]->Set_shiwake_konyu_c(i_period,buy_c);
							retailer[l]->Set_shiwake_uriage(i_period,buy_c,p_gen);
							retailer[l]->Set_shiwake_yokin_azuke(i_period,buy_c);
							bank[retailer[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_c);
						}
						if(check==0) bank[0]->In_capital(mem_product[j]->Get_price());
						mem_buy.push_back(mem_product[j]);

						cso->Buy_set_price_tag(tag,mem_product,j);	//該当製品タグの在庫表示を変換
						mem_product.erase(del_p);
						break;
					}
				}		
				else if(j<=min_price_product)
				{
					del_p++;
					if(j==min_price_product)
					{
						if(cf->Comp_AGEvec_VAR(retailer,mem_product[j]->Get_Producer_no())==1)
						{
							l=cf->Comp_AGEvec_VAR_return_no(retailer,mem_product[j]->Get_Producer_no());
							retailer[l]->Set_rieki(mem_product[j]->Get_price(),mem_product[j]->Get_class_no());	
							check=1;
							buy_c=mem_product[j]->Get_price();
							p_gen=mem_product[j]->Get_price_genka();
							consumer[i]->Set_shiwake_konyu_c(i_period,buy_c);
							retailer[l]->Set_shiwake_uriage(i_period,buy_c,p_gen);
							retailer[l]->Set_shiwake_yokin_azuke(i_period,buy_c);
							bank[retailer[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_c);
						}
						if(check==0) bank[0]->In_capital(mem_product[j]->Get_price());
						mem_buy.push_back(mem_product[j]);
						
						cso->Buy_set_price_tag(tag,mem_product,j);	//該当製品タグの在庫表示を変換
						mem_product.erase(del_p);
						break;
					}
				}
				else {
//					fprintf(test,"  ,  ,  ,  , check_c\n");
				}
			}
			goto restart;
		}
		else 
		{
			//購入対象商品が市場にないか、または予算範囲外のために購入できなかった場合
			//買える商品はすべて購入した
			//consumer[i]->Show_bought_product();//購入した商品を表示する
			nerror=0;
		}
	}
	int in,sum_in=0;
	for(i=0;i<int(consumer.size());i++){
		in=consumer[i]->Get_income();
		sum_in+=in;
	}

	cs->CR_CM_Show_Buy_consumer_row(int(mem_product.size()),sum_in);	//	CShowへプリント機能移転、依存度高ければ削除下の行が内容

	for(i=0;i<int(retailer.size());i++) 	retailer[i]->Reset_buy_p();
}



template<class T,class U,class V,class W,class X,class Y,class Z> void CSpace_threetype::B__BC__Buy_consumer(T &consumer, U &retailer, V &bank, W &tag, X &mem_product,Y &del_p,Z &mem_buy,int i_period)
{
	int i,j,l,b=0,c_gen=0;
	int k;double rate;
	int depo_money;
	int check;
	int buy_c; int p_gen;
	int nerror=0;
	int min_price_product;
	vector <int> mem_ni;//選択可能消費者の集合
	vector <int> ::iterator p;
	cs->CM_Show_Buy_consumer_top(int(mem_product.size()));	//	CShowへプリント機能移転、依存度高ければ削除下の行が内容
	for(i=0;i<int(consumer.size());i++) mem_ni.push_back(i);


	for(k=0;k<int(consumer.size());k++)
	{
		i=cf->Random_choice_int(mem_ni,p,cr);
		consumer[i]->Reset_mem_buy();
		rate=consumer[i]->Get_with_drawal_rate();

		depo_money=int(consumer[i]->Get_yokin_suitoutyou_zandaka()*rate);

		consumer[i]->Renew_income(depo_money);	//購入データを初期化している（要機能改善）20110224
		consumer[i]->Set_shiwake_yokin_hikidashi(i_period,depo_money);
		bank[consumer[i]->Get_bank_no()]->Set_shiwake_yokin_hikidashi(i_period,depo_money);
		c_gen=consumer[i]->Get_genkin_suitoutyou_zandaka();

restart:
//		printf("%d , i=%d\n",consumer[i]->Get_Agent_no(),i);
		consumer[i]->Def_min_price_product_new(tag,mem_product,&nerror,&min_price_product,consumer[i]->Get_genkin_suitoutyou_zandaka());
		check=0;
		
		if(nerror==0)
		{
			for(j=0;j<int(mem_product.size());j++)
			{
				if(j==0) 
				{
					del_p=mem_product.begin();
					if(j==min_price_product)
					{
						//mem_product[j]をmem_buyに入れる
						if(cf->Comp_AGEvec_VAR(retailer,mem_product[j]->Get_Producer_no())==1)
						{
							l=cf->Comp_AGEvec_VAR_return_no(retailer,mem_product[j]->Get_Producer_no());
							retailer[l]->Set_rieki(mem_product[j]->Get_price(),mem_product[j]->Get_class_no());
							check=1;
							buy_c=mem_product[j]->Get_price();
							p_gen=mem_product[j]->Get_price_genka();
							consumer[i]->Set_shiwake_konyu_c(i_period,buy_c);
							retailer[l]->Set_shiwake_uriage(i_period,buy_c,p_gen);
							retailer[l]->Set_shiwake_yokin_azuke(i_period,buy_c);
							bank[retailer[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_c);
							retailer[l]->Erase_material();
						}
						if(check==0) bank[0]->In_capital(mem_product[j]->Get_price());
						mem_buy.push_back(mem_product[j]);

						cso->Buy_set_price_tag(tag,mem_product,j);	//該当製品タグの在庫表示を変換
						mem_product.erase(del_p);
						break;
					}
				}		
				else if(j<=min_price_product)
				{
					del_p++;
					if(j==min_price_product)
					{
						if(cf->Comp_AGEvec_VAR(retailer,mem_product[j]->Get_Producer_no())==1)
						{
							l=cf->Comp_AGEvec_VAR_return_no(retailer,mem_product[j]->Get_Producer_no());
							retailer[l]->Set_rieki(mem_product[j]->Get_price(),mem_product[j]->Get_class_no());	
							check=1;
							buy_c=mem_product[j]->Get_price();
							p_gen=mem_product[j]->Get_price_genka();
							consumer[i]->Set_shiwake_konyu_c(i_period,buy_c);
							retailer[l]->Set_shiwake_uriage(i_period,buy_c,p_gen);
							retailer[l]->Set_shiwake_yokin_azuke(i_period,buy_c);
							bank[retailer[l]->Get_bank_no()]->Set_shiwake_yokin_azuke(i_period,buy_c);
							retailer[l]->Erase_material();
						}
						if(check==0) bank[0]->In_capital(mem_product[j]->Get_price());
						mem_buy.push_back(mem_product[j]);
						
						cso->Buy_set_price_tag(tag,mem_product,j);	//該当製品タグの在庫表示を変換
						mem_product.erase(del_p);
						break;
					}
				}
				else {
//					fprintf(test,"  ,  ,  ,  , check_c\n");
				}
			}
			goto restart;
		}
		else 
		{
			//購入対象商品が市場にないか、または予算範囲外のために購入できなかった場合
			//買える商品はすべて購入した
			//consumer[i]->Show_bought_product();//購入した商品を表示する
			nerror=0;
		}
	}
	int in,sum_in=0;
	for(i=0;i<int(consumer.size());i++){
		in=consumer[i]->Get_income();
		sum_in+=in;
	}

	cs->CM_Show_Buy_consumer_row(int(mem_product.size()),sum_in);	//	CShowへプリント機能移転、依存度高ければ削除下の行が内容


	for(i=0;i<int(retailer.size());i++) 	retailer[i]->Reset_buy_p();
}











#endif