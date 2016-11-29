//CAppli.h
#ifndef INC_CAPPLICATIONS
#define INC_CAPPLICATIONS
#include <stdio.h>
#include <vector>
#include "CMarket.h"
#include "CShow.h"
#include "CParameter.h"
#include "CVector_owner.h"
#include "CFunction.h"
//#include "CAccount.h"
using namespace std;

class CAppli
{
	public:
	CMarket *cm;
	CShow *cs;
	CParameter *cpara;
	CVector_owner *cvo;
	CFunction *cf;
	int Agent_type;
			//Agent_type=10; 一般消費者
			//Agent_type=20; 一般消費者向け生産者
			//Agent_type=30; 生産者向け生産者（原料を生産)
			//Agent_type=40; 生産者向け生産者（設備を拡充)
			//Agent_type=50; 銀行
	int nconsumer;		//一般消費者の数
	int nretailer;		//一般消費者向け生産者
	int nwholesaler;	//生産者向け生産者（原料を生産する)
	int nequipment;		//設備製造者数
	int nbank;			//銀行数
	int n_class;		//市場にある製品種別の最大数
						//製品種別番号は1からn_classの数
	int qmaxmax;		//生産者の生産能力の最大値
	int qmaxmin;		//生産者の生産能力の最小値
	int qmaxmax_w;		//ホールセラーの生産能力の最大値
	int qmaxmin_w;		//ホールセラーの生産能力の最小値
	int period_max;			//期数
	int nbonus;			//nbonus=0 when without bonus
						//nbonus=1 half bonus
						//nbonus=2 when with bonus
	int max_ban;//最大廃業指数

	int genkin_kisyu_zandaka; int yokin_kisyu_zandaka;	int loan_kisyu_zandaka;


	/////////////計算結果書き込み用ファイルの宣言//////////////////


///////////////////パラメータ入力用ファイル宣言//////////////////////

	

	void Set_Parameter();	//初期パラメータの設定
	void Create_Agent();	//エージェントクラスの生成
	void Create_Market(){cs=new CShow; cm=new CMarket(cs);};		//マーケットクラスの生成
	void Create_file();		//書き込み用ファイルの初期設定

	void Market();
	void Write_periodfast(int i);//期初の改行、期数表示の入力関数
	void Show_member_renew();	//showのメンバーのアドレスを更新する
	void Create_Assumption(){cpara=new CParameter;	};	//パラメータクラスの生成

	void Labor_limit_up(int i);
	void Labor_kimatu(int i);
	void Labor_gov_yosan(int i);
};


void CAppli::Set_Parameter()
{
	//CParameterのCSVファイル読み込み
	cpara->FILE_set_parameter();	//CParameter内でパラメータファイルを読み込む

	//CAppli内での使用する変数（たいていはCMarket内関数の引数で使用）
	nconsumer	=	cpara->GET_PARA_nconsumer();	
	nretailer	=	cpara->GET_PARA_nretailer();	
	nwholesaler	=	cpara->GET_PARA_nwholesaler();	
	n_class	=	cpara->GET_PARA_n_class();			
	qmaxmax	=	cpara->GET_PARA_qmaxmax();			
	qmaxmax_w	=	cpara->GET_PARA_qmaxmax_w();	
	period_max	=	cpara->GET_PARA_period_max();	
	nbonus	=	cpara->GET_PARA_nbonus();			
	max_ban	=	cpara->GET_PARA_max_ban();			
	nbank	=	cpara->GET_PARA_nbank();	
	nequipment	=	cpara->GET_PARA_nequipment();
	qmaxmin	=	cpara->GET_PARA_qmaxmin();
	qmaxmin_w	=	cpara->GET_PARA_qmaxmin_w();
}

void CAppli::Create_file()
{
	cpara->FILE_set_printfile();	//////ファイルのオープン//////////
	cm->Set_Parameter_class(cpara);	//CMarketクラスにCParameterのポインタ引き渡し
	cm->Set_seed();
	cs->Set_Parameter_class(cpara);	//CShowにCParameterのポインタ引き渡し
	cm->Set_FILE_output();			//CMarketクラスでCParameterクラスからファイルアドレスを取得
	cs->Set_output_FILE();			//CShowクラスでCParameterクラスからファイルアドレスを取得
}

void CAppli::Write_periodfast(int i)
{
	cs->Write_periodfast(i);	//期首ファイルプリント用（期数等）

	cs->set_consumer_add(cm->PrintDataGet_consumer_add());
	cs->set_retailer_add(cm->PrintDataGet_Retailer_add());
	cs->set_wholesaler_add(cm->PrintDataGet_Wholesaler_add());
	cs->set_equipment_add(cm->PrintDataGet_Equipment_add());
	cs->set_bank_add(cm->PrintDataGet_Bank_add());
	cs->set_government_add(cm->PrintDataGet_Governament());
	cs->Set_i_period(i);		//CShowクラス内に期数入力
	printf("期数：%d\n",i);
}
void CAppli::Show_member_renew()
{
	cs->set_consumer_add(cm->PrintDataGet_consumer_add());
	cs->set_retailer_add(cm->PrintDataGet_Retailer_add());
	cs->set_wholesaler_add(cm->PrintDataGet_Wholesaler_add());
	cs->set_equipment_add(cm->PrintDataGet_Equipment_add());
	cs->set_bank_add(cm->PrintDataGet_Bank_add());
	cs->set_government_add(cm->PrintDataGet_Governament());
}


void CAppli::Create_Agent()
{


	//////初期値の設定//////	////////会計処理判定用//////
	cm->Set_parameter();	//CMarketクラス内でCParameterからすべての使用関数の初期パラメータ受取

	
	///////エージェントの生成////////
	cm->CReate_Government();//行政エージェントの生成
	cm->CReate_Bank(nbank);//銀行オブジェクトの初期値設定
	cm->CReate_Wholesaler(nwholesaler);//Agent_no=1,....,nwholesalerを生成	
				//各wholesaler毎に生産製品種別数ncr_p個を定義し、ncr_p個のProduct_classのインスタンスmem_class_pを生成する
				//ncr_p個の製品種別インスタンスに製品種別番号を割りつける
				//初期生産量は未定義
	cm->Set_qmax_whole(qmaxmax_w,qmaxmin_w);//ホールセラーの生産能力の最大値の設定（qmaxmax_w)
				//各製品種別毎に初期生産量q,q_initの決定（int(0.5*qmax)～qmaxの乱数)
				// q_limit;//生産上限数(初期生産量）q_limit_d;//生産下限数の設定(q_limit*0.5)


	cm->CReate_Retailer(nretailer);//Agent_no=nwholesaler+1,...nwholesaler+nretailerを生成
				//ncr_p個のProduct_classのインスタンスを生成し、mem_class_pに格納する
				//ncr_p個の製品種別インスタンスに製品種別番号を割りつける
	cm->Set_qmax_retailer(qmaxmax,qmaxmin);//リテイラーの生産能力の最大値の設定,この中で初期の生産量も決定
							 //初期の生産能力は皆同じ、生産量は0.5qmx～qmxの間で乱数で決定
	fprintf(cpara->FI_Get_out(),"Before Create Equipment\n");
	cm->Create_Equipment(nequipment);	//設備販売会社（１社）Agent_no=nwholesaler+nretailer+1
										//Agent_no=nwholesaler+nretailer+1,....nwholesaler+nretailer+nconsumerを生成
	cm->CReate_Consumer(nconsumer);		//Consumerの生成
	cm->Employ(nconsumer);				//Consumerを従業員としてproducerへ配分する
//	cm->Set_init_equipment_revel();		//企業の設備レベルの初期設定
	cm->Inv_set_init_equipment_level();
	cm->Cobb_Duclas_production_func();	//設備レベルと労働者から生産量を決定

	cs->show_income();					//cm->show_income();//消費者のincomeをse_conに表示し、producer_type別の合計をse_incomeに表示する										
	cs->Show_employ();					//プリント用データ受け渡し

	cm->Create_CSpace();				//取引空間のオブジェクト生成、及びParameter,Showの引き渡し


}


void CAppli::Market()
{
	int i;
	

	for(i=0;i<period_max;i++)
	{
		fprintf(cpara->FI_Get_all_money(),"期首 , ");cm->Print_allmoney();

		cm->Labor_housyu();					//役員報酬決定ロジック
		
		fprintf(cpara->FI_Get_all_money(),"期首2, ");cm->Print_allmoney();
		if(i==cpara->Get_PARA_change_time())
		{
			switch(cpara->Get_PARA_tax_change_switch())
			{
			case 0:

				break;

			case 1:
				cpara->change_income_tax_rate();
				cpara->change_e_flag();
				break;

			case 2:
				cpara->change_corp_tax_rate();
				cpara->change_e_flag();
				break;
			}
			
		}

		fprintf(cpara->FI_Get_phenom_writer(),"\n-------------------%d期スタート-------------\n\n",i);
		printf("-------------------%d期開始-------------------\n",i);
		Write_periodfast(i);		//期初の改行、期数表示の入力関数
		cm->Set_i_period(i);//期数のマーケットへの入力
		cm->Kisyu();		//期首会計処理
		fprintf(cpara->FI_Get_all_money(),"期首処理後 , ");cm->Print_allmoney();
		///政府行動1予算決定
		Labor_gov_yosan(i);
		fprintf(cpara->FI_Get_all_money(),"生産前 , ");cm->Print_allmoney();
		//～～～～～～～～生産活動 Pro～～～～～～～～～
		if(i==0)
		{
			cm->Labor_choice_producer();
			//cm->Labor_Reset_limit_up_data();
			printf("製造開始\n");
			cm->Production_whole();
			//生産する製品種別毎に価格を決定する
			//各製品種別について製品をq個作る。各生産者の製品を各生産者の倉庫(mem_product_whole)に格納する
			cm->Define_mem_ncr_w();//wholesalerの製品種別番号の集合を定義する
			//cm->Show_mem_ncr_w();//上の表示
			cm->Define_mem_ncr_r();//retailerの製品種別番号の集合=consusmerが購入する製品種別番号の集合を定義する
			//cm->Show_mem_ncr_r();//上の表示
			cm->Define_seizou();
			//製品種別毎にmem_ncr_wの中から原料をランダムに１つ指定する。
			cm->Production_retail();
			//各製品種別毎に生産量q、価格priceを決定し、各製品種別について製品をq個作る。各生産者の製品を市場の倉庫(mem_product)にいれる
			cm->Create_price_tag();

			//Show用ベクター受け渡し
			cs->set_mem_buy(cm->PrintDataGet_mem_buy());					//CS:購買履歴ベクタ転送	
			cs->set_mem_buy_w(cm->PrintDataGet_mem_buy_w());				//CS:購買履歴ベクタWを転送
			cs->set_mem_product(cm->PrintDataGet_mem_product());			//CS:製品ベクタ転送
			cs->set_mem_product_w(cm->PrintDataGet_mem_product_whole());	//CS:製品ベクタWを転送
			cs->set_mem_ncr_r(cm->PrintdataGet_mem_ncr_r());				//CS:ncr_rを転送
			cs->set_mem_ncr_w(cm->PrintDataGet_mem_ncr_w());				//CS:ncr_wを転送

			cs->Show_mem_ncr_w();
			cs->Show_mem_ncr_r();
		}
		else
		{
			printf("製造開始\n");
			cm->Production_whole_revised();
			fprintf(cpara->FI_Get_all_money(),"W生産後 , ");cm->Print_allmoney();
			cm->Production_retail_revised();	//原料購入
			fprintf(cpara->FI_Get_all_money(),"R生産後 , ");cm->Print_allmoney();
			cs->set_mem_buy_w(cm->PrintDataGet_mem_buy_w());				//CS:購買履歴ベクタをCSに転送
			cs->set_mem_product(cm->PrintDataGet_mem_product());			//CS:製品ベクタをCSに転送
			cs->set_mem_product_w(cm->PrintDataGet_mem_product_whole());	//CS:製品ベクタ_WをCSに転送
		}
		printf("製造終了\n");
		//～～～～～～～～～生産活動終了 Pro～～～～～～～
		fprintf(cpara->FI_Get_all_money(),"生産後 , ");cm->Print_allmoney();

		//～～～～～～生産活動後状況表示～～～～～～～～
		cs->Show_test_2(i);	//製品種別生産数
		cs->Show_retailer();
		//producer no,製品種別数、製品種別番号、それぞれの生産量、をﾌﾟﾘﾝﾄｱｳﾄする
		//原料製品生産量は未定,価格は決定済み,price=cost*alpha;
		//fprintf(producer_no,"%d",i); cm->Show_producer_no();
		cs->Show_product_class();//製品種別ごとに製品の番号、価格、製造者番号をプリントアウトする。
		fprintf(cpara->FI_Get_out(),"consumer の購入する製品種別番号の定義 in Set_class_no_c\n");//file出力;
	//	cs->Show_balance();//行動前つまり期首			

		//～～～～～～生産活動後状況表示終了～～～～～～～～


		cm->Set_reserve();//来期準備金設定//率をかける前

		
		//～～～～～～～～購買活動 B～～～～～～～～
		cm->Calc_R_koubai_yosan();
		printf("購買開始\n");
		cm->Buy_consumer();		//全ての消費者が可処分所得の範囲内で最低価格の製品を購入する。
		cm->buy_checker();
fprintf(cpara->FI_Get_free_text2(),"消費者\n");		cm->Buy_government();	//政府購買
fprintf(cpara->FI_Get_free_text2(),"政府\n");		cm->Buy_producer();		//リテイラー、ホールセラーの市場購買
fprintf(cpara->FI_Get_free_text2(),"企業\n");		printf("購買終了\n");

		
		fprintf(cpara->FI_Get_all_money(),"購買後 , ");cm->Print_allmoney();

		//～～～～～～購買活動終了～～～～～～～～～～

		cs->set_mem_product(cm->PrintDataGet_mem_product());			//CS:製品ベクタをCSに転送
		cs->set_mem_buy(cm->PrintDataGet_mem_buy());					//CS:購買履歴ベクタ転送	
		cs->Show_bought_product_class();	fprintf(cpara->FI_Get_out(),"売れ残り商品リスト\n");
		cs->Show_product_class();
		cs->Show_test(i);//製品種別在庫
//		fprintf(cpara->FI_Get_product_price(),"%d,",i);
		cm->Def_statics_mem_buy();		//cm->Show_statics_mem_buy();
		cs->set_mem_class_statics(cm->PrintDataGet_mem_class_statics());//CS:商品種状況ベクタ（R)を転送
		cs->Show_statics_mem_buy();

		cm->Def_statics_mem_product();//売れ残り商品の統計データの定義
		cs->set_mem_class_stock_statics(cm->PrintDataGet_mem_class_stock_statics());	//CS:商品種別在庫状況ベクタ（R)を転送
		cs->set_mem_class_stock_statics_w(cm->PrintDataGet_mem_class_stock_statics_w());//CS:商品種別在庫状況ベクタ（W)を転送
		cs->Show_statics_mem_product();
		cs->Show_termly_change(i);
		cm->Clear_p_class_buy();//今期購入された製品数の記憶層への移し変えと保有
		cs->set_mem_class_statics_w(cm->PrintDataGet_mem_class_statics_w());	//CS:商品種状況ベクタ（W）を転送
		if(i>=1)cs->Show_static_mem_buy_w();	//cm->Show_static_mem_buy_w();
		fprintf(cpara->FI_Get_out(),"retailer毎のクラス別市場統計データの表示\n");
		cm->Show_statics_retailer();//producerに統計情報データを受け渡し、それを表示する
	    //この時点でmem_class_pに統計データが入力される
		fprintf(cpara->FI_Get_out(),"retailerの在庫情報\n");
		cm->Def_nstock_retailer(); 
	
		cm->Erase_mem_statics_w();
		cm->Clear_p_class_buy_w();
	
		cm->Agent_hensai();//各R,W,Eの短期返済行動
		printf("データ集計終了\n");
		fprintf(cpara->FI_Get_all_money(),"データ集計後 , ");cm->Print_allmoney();

		////給与支払い行動//
		cm->Suply_pay_wage();
		fprintf(cpara->FI_Get_all_money(),"給与支払い後 , ");cm->Print_allmoney();
		cm->Labor_situgyouhosyou();
		fprintf(cpara->FI_Get_all_money(),"失業補償後 , ");cm->Print_allmoney();
		cm->Sort_income();			//給与のソート
		printf("給料終了\n");

		
		/////政府政策////////
		cm->Cobb_Duclas_production_func();
		cm->Hosyou_shouhisya_kouhukin();	//貧乏人優遇
		


		Labor_limit_up(i); //生産能力拡大系　パラメータ選択式のため別関数移動
		fprintf(cpara->FI_Get_all_money(),"拡大後 , ");cm->Print_allmoney();

		if(cpara->Get_PARA_Labor_assignment_switch()==0)
		{
			switch(cpara->Get_PARA_Labor_hozyokin_switch())
			{
			case 0:
				cm->Hozyokin_kouhu();	//企業補助金
				break;
			case 1:
				cm->Labor_Hozyokin_kouhu();
				break;
			case 2:
				cm->Labor_Hozyokin_kouhu_zyoui();
				break;
			}
		}
		else if(cpara->Get_PARA_Labor_assignment_switch()==1)
		{
			cm->Labor_Hozyokin_kouhu_assignment();
		}
		printf("政府終了\n");
		fprintf(cpara->FI_Get_all_money(),"補助金交付後 , ");cm->Print_allmoney();

		/////期末処理////////
		Labor_kimatu(i);

		if(cpara->Get_PARA_Labor_recognition_riekiritu_switch()==1) cm->Labor_recognition_riekiritu();
		
		fprintf(cpara->FI_Get_all_money(),"期末処理後 , ");cm->Print_allmoney();

		
		switch(cpara->Get_PARA_calc_gdp_switch())
		{
		case 0:
			cs->Show_gdp_buy_pro_not_gdp();
			break;
			
		case 1:
			cs->Show_gdp();
			break;
		}
		if(i==0)	cs->Show_rieki_loan_first();
		cs->Show_rieki_loan();	//期末利益剰余と短期借入の表示
		cs->Tyotikuprint();
		cs->Show_Zini();		//ジニ係数計算

		cs->Show_print_data();	//aida//csv出力統括

		cs->Show_zikoshihonhiritu();
		cs->Show_market_product();
		cm->Erase_mem_buy();
		cm->Erase_mem_statics();
		cm->Erase_mem_stock_statics();
		cm->Show_tax();
		cm->Labor_Print_fixed_wage();
		cm->PrintProducer_yokin_suitoutyou();
		printf("-------------------%d期終了-------------------\n",i);
		fprintf(cpara->FI_Get_phenom_writer(),"\n-------------------%d期終了-------------\n\n",i);
		fprintf(cpara->FI_Get_all_money(),"最後 , ");cm->Print_allmoney();
		fprintf(cpara->FI_Get_all_money(),"\n");cm->Print_allmoney();

	}
}

void CAppli::Labor_gov_yosan(int i)
{
	switch(cpara->Get_PARA_Labor_limit_up_type_switch())
	{
	case 0:				//判断基準　売上個数	&　拡大方法　設備のみ　（旧ESSAルール）
		cm->Gav_yosan();
		break;

	case 1:				//判断基準　売上個数　	&　拡大方法　設備と雇用　～～～これは現在利用不可～～～
		
		break;

	case 2:				//判断基準　利益		&　拡大方法　設備のみ
		cm->Gav_yosan();
		break;

	case 3:				//判断基準　利益		&　拡大補法　設備雇用

		cm->Labor_government_yosan();
		break;

	}

}

void CAppli::Labor_limit_up(int i)
{
	
	switch(cpara->Get_PARA_Labor_limit_up_type_switch())
	{
	case 0:				//判断基準　売上個数	&　拡大方法　設備のみ　（旧ESSAルール）
		cm->Investment();		
		cm->Cobb_Duclas_production_func();	
		break;

	case 1:				//判断基準　売上個数　	&　拡大方法　設備と雇用　～～～これは現在利用不可～～～

		break;

	case 2:				//判断基準　利益		&　拡大方法　設備のみ
				fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～確認、eqwの数値の変化確認後～～～\n\n");
		cm->Labor_print_eqw();

		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～意思決定～～～\n\n");
		cm->Inv_labor_decide_inv_not_emp();
		printf("decide_emp_inv_end\n");
		

		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～雇用～～～\n\n");
//		cm->Labor_Recruitment_activity();
		printf("recrutiment_end\n");
//fprintf(cpara->FI_Get_employ(),"01 : ");cs->Show_employ_c();

		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～確認、eqwの数値の変化確認後～～～\n\n");
		cm->Labor_print_eqw();

		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～設備投資～～～\n\n");
		cm->Labor_Investment();
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～確認、eqwの数値の変化確認後～～～\n\n");
		cm->Labor_print_eqw();

		cm->Cobb_Duclas_production_func();	
	
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～%d期目処理後生産能力～～～\n\n\n",i);
		cm->Labor_print_production_power();
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n\n\n～～～%d期目処理終了～～～\n\n\n",i);
		cm->Labor_Reset_limit_up_data();
		break;

	case 3:				//判断基準　利益		&　拡大補法　設備雇用
	
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～確認、eqwの数値の変化確認後～～～\n\n");
		cm->Labor_print_eqw();

		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～意思決定～～～\n\n");
		cm->Inv_labor_decide_emp_inv();
		
		printf("decide_emp_inv_end\n");
		
		

		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～雇用～～～\n\n");
		cm->Labor_Recruitment_activity();

		printf("recrutiment_end\n");
//fprintf(cpara->FI_Get_employ(),"01 : ");cs->Show_employ_c();

		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～確認、eqwの数値の変化確認後～～～\n\n");
		cm->Labor_print_eqw();
		
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～設備投資～～～\n\n");
		cm->Labor_Investment();
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～確認、eqwの数値の変化確認後～～～\n\n");
		
		
		
		cm->Labor_print_eqw();

		cm->Cobb_Duclas_production_func();	
	
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n～～～%d期目処理後生産能力～～～\n\n\n",i);
		cm->Labor_print_production_power();
		fprintf(cpara->FI_Get_Labor_writer(),"\n\n\n\n～～～%d期目処理終了～～～\n\n\n",i);
		cm->Labor_Reset_limit_up_data();


		break;
	}
}



void CAppli::Labor_kimatu(int i)
{
	switch(cpara->Get_PARA_Labor_limit_up_type_switch())
	{
	case 0:				//判断基準　売上個数	&　拡大方法　設備のみ　（旧ESSAルール）
		/////期末処理////////
		cm->Kimatu();//期末会計処理
		cm->Bankruptcy(max_ban);//倒産処理
		printf("倒産終了\n");

		cm->Kessan_Agent();
		cm->Deposit_consumer();//消費者の前期の給与からの預金行動
		cm->Dismiss();		//解雇行動
		Show_member_renew();
		printf("解雇終了\n");
		break;

	case 1:				//判断基準　売上個数　	&　拡大方法　設備と雇用　～～～これは現在利用不可～～～

		break;

	case 2:				//判断基準　利益		&　拡大方法　設備のみ
		/////期末処理////////
		cm->Kimatu();//期末会計処理
		cm->Bankruptcy(max_ban);//倒産処理
		printf("倒産終了\n");

		cm->Kessan_Agent();
		cm->Deposit_consumer();//消費者の前期の給与からの預金行動
		cm->Dismiss();		//解雇行動
		Show_member_renew();
		printf("解雇終了\n");
		cm->Dismiss();		//解雇行動
		break;

	case 3:				//判断基準　利益		&　拡大補法　設備雇用
		/////期末処理////////
		cm->Kimatu();//期末会計処理
		cm->Labor_Bankruptcy(max_ban);
//		cm->Bankruptcy(max_ban);//倒産処理
		printf("倒産終了\n");
		cm->Kessan_Agent();
		cm->Deposit_consumer();//消費者の前期の給与からの預金行動

		cm->Labor_Dismiss();	//解雇行動　パラメータ選択式のため別関数移動

		Show_member_renew();
		printf("解雇終了\n");


		
		break;
	}
}


#endif