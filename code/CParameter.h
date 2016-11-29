
//CParameter.h
//パラメータ、出力ファイルの変換用：.



#ifndef INC_CPARAMETER
#define INC_CPARAMETER
#include <stdio.h>
#include <vector>
using namespace std;

class CParameter
{
	int Agent_type;
			//Agent_type=10; 一般消費者
			//Agent_type=20; 一般消費者向け生産者
			//Agent_type=30; 生産者向け生産者（原料を生産)
			//Agent_type=40; 生産者向け生産者（設備を拡充)
			//Agent_type=50; 銀行
			//Agent_type=99999;	政府
	int nconsumer;		//一般消費者の数
	int nretailer;		//一般消費者向け生産者
	int nwholesaler;	//生産者向け生産者（原料を生産する)
	int nequipment;		//設備製造者数
	int nbank;			//銀行数

	int n_retailer_worker;		//リテイラー一社当たり労働者数
	int n_whole_worker;			//ホールセラー一社当たり労働者数
	int n_equip_worker;			//設備製造一社当たり労働者数
	int n_bank_worker;			//銀行一社当たり労働者数
	int n_government_worker;		//行政の労働者数
	int n_max_employee;			//一社当たりの雇用上限人数

	int n_class;		//市場にある製品種別の最大数
						//製品種別番号は1からn_classの数
	int nmax_p;			//各生産者が生産する製品種別の最大数
	int nmax_p_min;
	int nmax_c;			//各消費者が購入する製品種別の最大数
	int qmaxmax;		//生産者の生産能力の最大値
	int qmaxmin;		//生産者の生産能力の最小値
	int qmaxmax_w;		//ホールセラーの生産能力の最大値
	int qmaxmin_w;		//ホールセラーの生産能力の最小値

	int cob_alpha_r_up;		//コブダグラスの生産関数の係数、ｒの上限
	int cob_alpha_r_down;	//コブダグラスの生産関数の係数、ｒの下限
	int cob_alpha_w_up;		//コブダグラスの生産関数の係数、ｗの上限
	int cob_alpha_w_down;	//コブダグラスの生産関数の係数、ｗの下限
	double price_up_rate;	//価格の上昇割合
	double price_down_rate;	//価格の下降割合
	double price_change_upper_rate;	//迎合段階型で最初に売値の最高価格＊Xに価格を合わせる際のX

	int pricing_switch;		//CProducer::new_set_priceで用いる価格決定ルールのスイッチ
							//4：混合型、5：混合型_変動幅事前乱数固定、6：混合型
	int bonus_rule_switch;	//CMaket::kessan_agentで用いるボーナス決定ルールのスイッチ
	int buy_producer_switch;//CMarket::buy_producerで用いる購買ルールのスイッチ
	int syotokuzei_switch;	//CTax::calc_syotoku_taxで用いる所得税の固定税率か累進課税かのスイッチ

	int period_max;			//期数
	double depo_rate_c;		//消費者貯蓄率
	double depo_rate_p;		//生産者貯蓄率
	int nbonus;			//nbonus=0 when without bonus
						//nbonus=1 half bonus
						//nbonus=2 when with bonus
	double bonus_rate_min;	double bonus_rate_max;			//ボーナス幅
	double bonus_rate_min_e;	double bonus_rate_max_e;	//設備製造ボーナス幅
	int min_constant_wage;	int max_constant_wage;			//固定給幅
	int min_init_depo_c;		int max_init_depo_c;		int min_init_depo_w;		int max_init_depo_w;
	int min_init_depo_r;		int max_init_depo_r;		int min_init_depo_e;		int max_init_depo_e;
	long long min_bank_capital;		long long max_bank_capital;		//各エージェントの初期銀行預金

	double min_with_drawal_rate;	double max_with_drawal_rate;//銀行預金引出額係数
	int repay_period;//返済期間
	double capa_increase_rate;	int invest_money;			//最大生産量増加割合//投資必要金額
	int min_koteihi;int max_koteihi;	int min_hendouhi;	int max_hendouhi;//固定費幅//変動費幅
	int min_price_w;	int max_price_w; //Wholeの価格幅
	int max_ban;//最大廃業指数
	int max_e_flag;//最大設備投資フラグ
	int max_equip_end;//最大設備耐久
	int max_memo_time;//売れ行き記憶期間
	int max_reac_flag;//在庫調整フラグ
	int repay_time_ave,repay_time_bun;//支払い期間、正規分布入力数値
	double bank_increase_rate;//利率
	double min_price_p;	double max_price_p;	double min_price_m;	double max_price_m;//価格改定幅
	double Adjustment_Sensitivity;//調整感度
	double max_q_re;	double min_q_re;//生産上・下限係数
	double min_q_init;//初期生産下限
	double q_limit_k;
	double price_increase_rate;
	int min_q_limit;//生産下限係数
	double price_k;//価格=製造*price_k
	double reserve_rate;//準備金率
	int ncase;//ncase=0:総勘定元帳をout3へのプリントアウト
			  //ncase!=0:総勘定元帳をプリントアウトしない
	int nkessan;//nkessan=0：out3へのプリントアウト
				//nkessan=1：out3への部分的プリントアウト
				//nkessan!=0or1:out3へのプリントアウトをしない

	int equip_end;//設備耐久
	int invest_max;//期当たり設備投資上限
	int nbank_con;//銀行従業員
	int first_price;//リテイラー製品初期価格
	int loan_time_limit;//短期借入を連続で行うことのできる期数（これを超えた場合は借入をやめて一人解雇）

	int genkin_kisyu_zandaka; int yokin_kisyu_zandaka;	int loan_kisyu_zandaka;

	int profit_under_line;		//利益の下限値（所得税を決定するときに利用する）


	double income_tax_rate;		//所得税
	double sales_tax_rate;		//消費税
	double corp_tax_rate;		//法人税率
	double wage_yosan_rate;		//政府給与予算率 

	double gov_invest_ratio;	//政府投資率
	double hosyou_ratio;		//失業者補償率
	double yugu_ratio;			//金持ち優遇率
	double kigyou_hozyokin_ratio;	//企業補助金割合
	double g_koubai_ratio;		//政府購買割合

	int threshold_deposit;		//貯蓄率決定用変数、貯蓄開始給与額の閾値
	double deporate_coefficient;	//貯蓄率決定用変数、貯蓄率決定係数c
	int min_genka_whole;		//ホールセラー用の最小変動費
	int government_price_rate;	//政府が購買するときの価格の倍化 
	int buy_producer_amount;	//企業同士の購買を固定数購買にしたときの購買数
	double gav_wage_rate;			//行政消費者の給与レベル　1なら平均と同様1以下なら平均以下、1以上なら平均以上

	int CR_fixed_q_limit_up;			//C-R用、所与固定生産上限の乱数設定時の上限値
	int CR_fixed_q_limit_down;			//C-R用、所与固定生産上限の乱数設定時の下限値
	int CR_fixed_income;				//C-R用、所与固定給与
	int CR_limit_genka_up;				//C-R用、所与固定原価_乱数設定上限
	int CR_limit_genka_down;			//C-R用、所与固定原価_乱数設定下限
	int CR_kurikosi_switch;				//C-R用、消費者の資金繰越有無しのswitch
	int CR_q_limit_down_line_switch;	//C-R用、生産計画時の生産量下限値のon,offswitch
	int CR_maxqre_decision_switch;		//C-R用、生産量改訂時の変化方法の決定方法switch 0:初期に全員同値で固定、1:初期にエージェント毎に乱数で固定、2:価格決定時に乱数で固定
	int CR_stock_decision_switch;		//C-R用、生産量の意思決定モデルの決定switch 0:max_q_re,min_q_re使用　1:品切れ許容の在庫モデルのみ利用

	double Labor_limit_up_basis;		//投資・雇用時の予想利益/株主資本の判断基準の係数
	int Labor_limit_up_decision_switch;	//０：利益予測がマイナスなら生産拡大しない方式
										//１：予想利益/株主資本がLabor_limit_up_basis以下なら生産拡大しない方式
										//２：予想利益/"初期"株主資本がLabor_limit_up_basis以下なら生産拡大しない方式

	int Labor_salary_change_switch;		//０：固定給を変化させない
										//１：固定給を変化させる

	int Labor_limit_up_type_switch;		//０：判断基準　売上個数	&　拡大方法　設備のみ　（旧ESSAルール）
										//１：判断基準　売上個数　	&　拡大方法　設備と雇用　～～～これは現在利用不可～～～
										//２：判断基準　利益		&　拡大方法　設備のみ
										//３：判断基準　利益		&　拡大補法　設備雇用
	
	double Labor_situgyouhosyou_rate;	//失業保障に利用する係数

	int Labor_choice_office_switch;		//０：求人票応募意思決定、固定給が高額
										//１：利益剰余が高い順

	int Labor_invest_capital_switch;	//０：設備投資の際に自己資金を利用しない
										//１：～～～こちらは現在使用不可～～～設備投資の際に自己資金を利用する
										//２：設備投資の際に自己資金を利用する

	double Labor_invest_capital_rate;	//設備投資の際に自己資金を利用する場合の利用割合

	int Labor_hozyokin_switch;		//０：企業補助金を均等配分
									//１：起業補助金を売上別配分
									//２：上位25%だけに売上別配分

	double after_tax_rate;			//シミュレーション中に変更する税率
	int after_e_flag;				//シミュレーション中に変更する設備投資フラグ
	int seed;						//乱数シード
	double housyu_rate;				//役員報酬割合

	int change_time;				//シミュレーション中で税率と生産拡大フラグを変更する場合の変更期数	
	int tax_change_switch;			//シミュレーション中で税率と生産拡大フラグを変更するかのスイッチ
									//０：変更を行わない
									//１：所得税を変更する
									//２：法人税を変更する
	int calc_gdp_switch;			//０：企業間取引をGDPに含まない
									//１：企業間取引をGDPに含む

	double R_koubai_yosan_rate;		//企業のリテイラー製品（少額固定資本）購買予算割合　利益で計算する場合）

	int Labor_recognition_riekiritu_switch;	//０：当期純損益利益率によって生産拡大フラグを変更しない
											//１：当期純損益利益率によって生産拡大フラグを変更する
	double Labor_riekiritu;			//生産拡大フラグを増加させる際の上限意思決定利益率

	int Labor_assignment_switch;			//０：政府が購買、補助等に指定を設けない
										//１：政府が購買、補助等に指定を設ける
	int Labor_assignment_size;			//政府指定の企業数（対象企業からしか購買しない）
	
	int Labor_R_buy_profit_switch;	//０：企業間購買利益依存時（buy_producer_switch=4,14)(税引後利益-役員報酬)*R_koubai_yosan_rate
									//１：企業間購買利益依存時（buy_producer_switch=4,14)(税引剰余-役員報酬)*R_koubai_yosan_rate

	int Inv_invest_time;			//設備投資（長期借入）の限界回数

	int Keynes_a;					//ケインズの消費関数（貯金額設定）のa

	double owncash_rate_inv;	//投資の際の自己資本利用率
	
	int delta_G;			//20150417 政府予算のΔ増加分
	int delta_period_start;	//20150417 政府予算のΔ増加開始期
	int delta_period_end;	//20150417 政府予算のΔ増加終了期
	double DeltaPurchaseRatio;		//20150601 政府予算のΔ増加分の市場購買率
	double DeltaSubsidyRatio;		//20150601 政府予算のΔ増加分の企業補助率



	/////////////計算結果書き込み用ファイルの宣言//////////////////
	FILE *OUTPUT_GDP;
	FILE *OUTPUT_Deposit;


	FILE *out;	FILE *out1;	FILE *out2;	FILE *test;	FILE *test2;	FILE *test3;	FILE *test4;
 	FILE *product_price;	FILE *product_price_w;	FILE *market_product;	FILE *se_income;
 	FILE *se_con;	FILE *product_out;	FILE *bank_data;
	FILE *economy;	FILE *bought_pro;	FILE *retai;
	FILE *Consumer;   FILE *Retailer;	FILE *Wholesaler;	FILE *Equipment;	FILE *Bank;
    FILE *producer_no;	FILE *se_income_new;	FILE *invest;   FILE *bought_money;	FILE *tax;
	FILE *employ_file;	FILE *seisan;	FILE *agent_no; FILE *kyuyo; FILE *market_data;
	FILE *eqw;

	FILE *shiwake;	FILE *out3;	FILE *out3_csv;	FILE *loan;
	FILE *GDP; FILE *seihin_price;
	FILE *zyunkanhyou; FILE *zyunkandata;
	FILE *parameter;
	FILE *ac_data1; FILE *ac_data2;
	FILE *show_tax;
	FILE *gyousei_syouhisya;
	FILE *producer_data;
	FILE *producer_uriage_kyuyo;
	FILE *producer_uriage;

	FILE *phenom_writer;
	FILE *free_text;
	FILE *price_check;
	FILE *price_check_w;
	FILE *free_text2;
	FILE *rieki_out;
	FILE *loan_out;
	FILE *deposit_out;
	FILE *number_employee;
	FILE *personal_income;
	FILE *corp_capital;
	FILE *seisan_class_no;
	FILE *seisan_class_no_w;

	FILE *consumer_asset;
	FILE *producer_asset;
	FILE *toukei;
	FILE *lorenz;
	FILE *employ;
	FILE *producer_equipment_level;
	FILE *producer_labor_cost;
	FILE *producer_seisan_amount;
	FILE *producer_genryo_price;
	FILE *producer_genryo_no;
	FILE *employ_producer_asset_C;
	FILE *employ_producer_asset_R;
	FILE *statistic_product;
	FILE *CR_product_relation;		//製品種と企業、製品と消費者の関係
	FILE *CR_syubetu_koubaimae_seihinsu;
	FILE *CR_syubetu_seisansu;
	FILE *Labor_writer;
	FILE *Labor_employ_time;
	FILE *Labor_parameter_fixed_wage;
	FILE *Labor_kigyouhozyo;
	FILE *Producer_Genkin_suitoutyou;
	FILE *all_money;
	FILE *free_text3;
	FILE *touki_zyunrieki;
	FILE *Labor_housyu_out;
	FILE *Labor_retailer_uriage_rank;
	FILE *Labor_koteishihon;
	FILE *Labor_keihi_soukei;
	FILE *Labor_keihi_toukisonekiritu;

	FILE *Tyotikuritu_pro;
	FILE *Tyotikuritu_uriage_rieki;
	FILE *Tyotikuritu_consumer;
	FILE *Delta_G_writing;

///////////////////パラメータ入力用ファイル宣言//////////////////////

	FILE *Experimental_file;	FILE *Other_file;	FILE *Initial_file;	FILE *Variable_file;	FILE *Parameter_FILE_5;
	FILE *Parameter_FILE_6;	FILE *Parameter_FILE_7;	FILE *Parameter_FILE_8;	FILE *Parameter_FILE_9;	

public:
	void FILE_set_parameter();
	void FILE_set_printfile();

	//パラメータ出力GET関数
	int GET_PARA_n_retailer_worker(){return n_retailer_worker;};
	int GET_PARA_n_whole_worker(){return n_whole_worker;};
	int GET_PARA_n_equip_worker(){return n_equip_worker;};
	int GET_PARA_n_bank_worker(){return n_bank_worker;};
	int GET_PARA_n_government_worker(){return n_government_worker;};
	double	GET_PARA_Adjustment_Sensitivity(){return Adjustment_Sensitivity;};
	double	GET_PARA_bank_increase_rate(){return bank_increase_rate;};
	double	GET_PARA_bonus_rate_max(){return bonus_rate_max;};
	double	GET_PARA_bonus_rate_min(){return bonus_rate_min;};
	double  GET_PARA_bonus_rate_max_e(){return bonus_rate_max_e;};
	double  GET_PARA_bonus_rate_min_e(){return bonus_rate_min_e;};
	double	GET_PARA_capa_increase_rate(){return capa_increase_rate;};
	double	GET_PARA_corp_tax_rate(){return corp_tax_rate;};
	double	GET_PARA_depo_rate_c(){return depo_rate_c;};
	double	GET_PARA_depo_rate_p(){return depo_rate_p;};
	int	GET_PARA_first_price(){return first_price;};
	double	GET_PARA_income_tax_rate(){return income_tax_rate;};
	int	GET_PARA_invest_money(){return invest_money;};
	int GET_PARA_invest_max(){return invest_max;};
	int	GET_PARA_max_ban(){return max_ban;};
	long long	GET_PARA_max_bank_capital(){return max_bank_capital;};
	int	GET_PARA_max_constant_wage(){return max_constant_wage;};
	int	GET_PARA_max_e_flag(){return max_e_flag;};
	int	GET_PARA_max_equip_end(){return max_equip_end;};
	int	GET_PARA_max_hendouhi(){return max_hendouhi;};
	int	GET_PARA_max_init_depo_c(){return max_init_depo_c;};
	int	GET_PARA_max_init_depo_e(){return max_init_depo_e;};
	int	GET_PARA_max_init_depo_r(){return max_init_depo_r;};
	int	GET_PARA_max_init_depo_w(){return max_init_depo_w;};
	int	GET_PARA_max_koteihi(){return max_koteihi;};
	int	GET_PARA_max_memo_time(){return max_memo_time;};
	double	GET_PARA_max_price_m(){return max_price_m;};
	double	GET_PARA_max_price_p(){return max_price_p;};
	double	GET_PARA_max_q_re(){return max_q_re;};
	int	GET_PARA_max_reac_flag(){return max_reac_flag;};
	double	GET_PARA_max_with_drawal_rate(){return max_with_drawal_rate;};
	long long	GET_PARA_min_bank_capital(){return min_bank_capital;};
	int	GET_PARA_min_constant_wage(){return min_constant_wage;};
	int	GET_PARA_min_hendouhi(){return min_hendouhi;};
	int	GET_PARA_min_init_depo_c(){return min_init_depo_c;};
	int	GET_PARA_min_init_depo_e(){return min_init_depo_e;};
	int	GET_PARA_min_init_depo_r(){return min_init_depo_r;};
	int	GET_PARA_min_init_depo_w(){return min_init_depo_w;};
	int	GET_PARA_min_koteihi(){return min_koteihi;};
	double	GET_PARA_min_price_m(){return min_price_m;};
	double	GET_PARA_min_price_p(){return min_price_p;};
	double	GET_PARA_min_q_init(){return min_q_init;};
	int	GET_PARA_min_q_limit(){return min_q_limit;};
	double	GET_PARA_min_q_re(){return min_q_re;};
	double	GET_PARA_min_with_drawal_rate(){return min_with_drawal_rate;};
	int	GET_PARA_n_class(){return n_class;};
	int	GET_PARA_nbank(){return nbank;};
	int GET_PARA_nbank_con(){return nbank_con;};
	int	GET_PARA_nbonus(){return nbonus;};
	int GET_PARA_ncase(){return ncase;};
	int	GET_PARA_nconsumer(){return nconsumer;};
	int	GET_PARA_nequipment(){return nequipment;};
	int	GET_PARA_nmax_c(){return nmax_c;};
	int	GET_PARA_nmax_p(){return nmax_p;};
	int	GET_PARA_nmax_p_min(){return nmax_p_min;};
	int GET_PARA_nkessan(){return nkessan;};
	int	GET_PARA_nretailer(){return nretailer;};
	int	GET_PARA_nwholesaler(){return nwholesaler;};
	int	GET_PARA_period_max(){return period_max;};
	double	GET_PARA_price_increase_rate(){return price_increase_rate;};
	double	GET_PARA_price_k(){return price_k;};
	double	GET_PARA_q_limit_k(){return q_limit_k;};
	int	GET_PARA_qmaxmax(){return qmaxmax;};
	int	GET_PARA_qmaxmax_w(){return qmaxmax_w;};
	int	GET_PARA_qmaxmin(){return qmaxmin;};
	int	GET_PARA_qmaxmin_w(){return qmaxmin_w;};
	int	GET_PARA_repay_period(){return repay_period;};
	int	GET_PARA_repay_time_ave(){return repay_time_ave;};
	int	GET_PARA_repay_time_bun(){return repay_time_bun;};
	double	GET_PARA_reserve_rate(){return reserve_rate;};
	double	GET_PARA_sales_tax_rate(){return sales_tax_rate;};
	double GET_PARA_gov_invest_ratio(){return gov_invest_ratio;};
	double GET_PARA_hosyou_ratio(){return hosyou_ratio;};
	double GET_PARA_yugu_ratio(){return yugu_ratio;};
	double GET_PARA_kigyou_hozyokin_ratio(){return kigyou_hozyokin_ratio;};
	double GET_PARA_g_koubai_ratio(){return g_koubai_ratio;};
	int GET_PARA_threshold_deposit(){return threshold_deposit;};
	double GET_PARA_deporate_coefficient(){return deporate_coefficient;};
	int GET_PARA_profit_under_line(){return profit_under_line;};
	int GET_PARA_loan_time_limit(){return loan_time_limit;};
	double GET_PARA_wage_yosan_rate(){return wage_yosan_rate;};
	int GET_PARA_min_genka_whole(){return min_genka_whole;};
	int GET_PARA_cob_alpha_r_up(){return cob_alpha_r_up;};
	int GET_PARA_cob_alpha_r_down(){return cob_alpha_r_down;};
	int GET_PARA_cob_alpha_w_up(){return cob_alpha_w_up;};
	int GET_PARA_cob_alpha_w_down(){return cob_alpha_w_down;};
	int GET_PARA_pricing_switch(){return pricing_switch;};
	double GET_PARA_price_up_rate(){return price_up_rate;};
	double GET_PARA_price_down_rate(){return price_down_rate;};
	double GET_PARA_price_change_upper_rate(){return price_change_upper_rate;};	
	int GET_PARA_bonus_rule_switch(){return bonus_rule_switch;};
	int GET_PARA_buy_producer_switch(){return buy_producer_switch;};
	int GET_PARA_government_price_rate(){return government_price_rate;};
	int GET_PARA_buy_producer_amount(){return buy_producer_amount;};
	int GET_PARA_syotokuzei_switch(){return syotokuzei_switch;};
	double GET_PARA_gav_wage_rate(){return gav_wage_rate;};
	int GET_PARA_max_employee(){return n_max_employee;};

	int GET_PARA_CR_fixed_q_limit_up(){return CR_fixed_q_limit_up;};
	int GET_PARA_CR_fixed_q_limit_down(){return CR_fixed_q_limit_down;};
	int GET_PARA_CR_fixed_income(){return CR_fixed_income;};
	int GET_PARA_CR_limit_genka_up(){return CR_limit_genka_up;};
	int GET_PARA_CR_limit_genka_down(){return CR_limit_genka_down;};
	int GET_PARA_CR_kurikosi_switch(){return CR_kurikosi_switch;};
	int GET_PARA_CR_q_limit_down_line_switch(){return CR_q_limit_down_line_switch;};	
	int GET_PARA_CR_maxqre_decision_switch(){return CR_maxqre_decision_switch;};		
	int GET_PARA_CR_stock_decision_switch(){return CR_stock_decision_switch;};		


	double Get_PARA_Labor_Labor_limit_up_basis(){return Labor_limit_up_basis;};
	int Get_PARA_Labor_limit_up_decision_switch(){return Labor_limit_up_decision_switch;};
	int Get_PARA_Labor_salary_change_switch(){return Labor_salary_change_switch;};
	int Get_PARA_Labor_limit_up_type_switch(){return Labor_limit_up_type_switch;};
	double Get_PARA_Labor_situgyouhosyou_rate(){return Labor_situgyouhosyou_rate;};
	int Get_PARA_Labor_choice_office_switch(){return Labor_choice_office_switch;};
	int Get_PARA_Labor_invest_capital_switch(){return Labor_invest_capital_switch;};
	double Get_PARA_Labor_invest_capital_rate(){return Labor_invest_capital_rate;};
	int Get_PARA_Labor_hozyokin_switch(){return Labor_hozyokin_switch;};

	void change_income_tax_rate(){income_tax_rate=after_tax_rate;};
	void change_corp_tax_rate(){corp_tax_rate=after_tax_rate;};
	void change_e_flag(){max_e_flag=after_e_flag;};
	int Get_PARA_seed(){return seed;};
	double Get_PARA_housyu_rate(){return housyu_rate;};
	int Get_PARA_change_time(){return change_time;};
	int Get_PARA_tax_change_switch(){return tax_change_switch;}
	int Get_PARA_calc_gdp_switch(){return calc_gdp_switch;}
	double Get_PARA_R_koubai_yosan_rate(){return R_koubai_yosan_rate;};

	double Get_PARA_Labor_riekiritu(){return Labor_riekiritu;}
	int Get_PARA_Labor_recognition_riekiritu_switch(){return Labor_recognition_riekiritu_switch;}

	int Get_PARA_Labor_assignment_switch(){return Labor_assignment_switch;};
	int Get_PARA_Labor_assignment_size(){return Labor_assignment_size;};
	int Get_PARA_Labor_R_buy_profit_switch(){return Labor_R_buy_profit_switch;};
	int Get_PARA_Inv_invest_time(){return Inv_invest_time;};
	int Get_PARA_Keynes_a(){return Keynes_a;};
	double Get_PARA_owncash_rate_inv(){return owncash_rate_inv;};

	int Get_Para_delta_G(){return delta_G;}
	int Get_para_delta_period_start(){return	delta_period_start;}
	int Get_para_delta_period_end(){return delta_period_end;}	
	double Get_para_DeltaPurchaseRatio(){return DeltaPurchaseRatio;};
	double Get_para_DeltaSubsidyRatio(){return DeltaSubsidyRatio;}; 



	//出力用ファイルアドレス受け渡しアドレスGET関数群
	FILE* FI_Get_out(){return out;};
	FILE* FI_Get_out1(){return out1;};
	FILE* FI_Get_out2(){return out2;};
	FILE* FI_Get_test(){return test;};
	FILE* FI_Get_test2(){return test2;};
	FILE* FI_Get_test3(){return test3;};
	FILE* FI_Get_test4(){return test4;};
	FILE* FI_Get_product_price(){return product_price;};
	FILE* FI_Get_product_price_w(){return product_price_w;};
	FILE* FI_Get_market_product(){return market_product;};
	FILE* FI_Get_se_income(){return se_income;};
	FILE* FI_Get_se_con(){return se_con;};
	FILE* FI_Get_product_out(){return product_out;};
	FILE* FI_Get_bank_data(){return bank_data;};
	FILE* FI_Get_economy(){return economy;};
	FILE* FI_Get_bought_pro(){return bought_pro;};
	FILE* FI_Get_retai(){return retai;};
	FILE* FI_Get_Consumer(){return Consumer;};
	FILE* FI_Get_Retailer(){return Retailer;};
	FILE* FI_Get_Wholesaler(){return Wholesaler;};
	FILE* FI_Get_Equipment(){return Equipment;};
	FILE* FI_Get_Bank(){return Bank;};
	FILE* FI_Get_producer_no(){return producer_no;};
	FILE* FI_Get_se_income_new(){return se_income_new;};
	FILE* FI_Get_invest(){return invest;};
	FILE* FI_Get_bought_money(){return bought_money;};
	FILE* FI_Get_tax(){return tax;};
	FILE* FI_Get_employ_file(){return employ_file;};
	FILE* FI_Get_seisan(){return seisan;};
	FILE* FI_Get_agent_no(){return agent_no;};
	FILE* FI_Get_kyuyo(){return kyuyo;};
	FILE* FI_Get_market_data(){return market_data;};
	FILE* FI_Get_eqw(){return eqw;};
	FILE* FI_Get_shiwake(){return shiwake;};
	FILE* FI_Get_out3(){return out3;};
	FILE* FI_Get_out3_csv(){return out3_csv;};
	FILE* FI_Get_loan(){return loan;};
	FILE* FI_Get_GDP(){return GDP;};
	FILE* FI_Get_seihin_price(){return seihin_price;};
	FILE* FI_Get_zyunkanhyou(){return zyunkanhyou;};
	FILE* FI_Get_zyunkandata(){return zyunkandata;};
	FILE* FI_Get_parameter(){return parameter;};
	FILE* FI_Get_ac_data1(){return ac_data1;};
	FILE* FI_Get_ad_data2(){return ac_data2;};
	FILE* FI_Get_show_tax(){return show_tax;};
	FILE* FI_Get_gyousei_syouhisya(){return gyousei_syouhisya;};
	FILE* FI_Get_producer_data(){return producer_data;};
	FILE* FI_Get_producer_uriage_kyuyo(){return producer_uriage_kyuyo;};
	FILE* FI_Get_producer_uriage(){return producer_uriage;};
	FILE* FI_Get_free_text(){return free_text;};
	FILE* FI_Get_phenom_writer(){return phenom_writer;};
	FILE* FI_Get_price_check(){return price_check;};
	FILE* FI_Get_price_check_w(){return price_check_w;};
	FILE* FI_Get_free_text2(){return free_text2;};
	FILE* FI_Get_rieki_out(){return rieki_out;};
	FILE* FI_Get_loan_out(){return loan_out;};
	FILE* FI_Get_deposit_out(){return deposit_out;};
	FILE* FI_Get_number_employee(){return number_employee;};
	FILE* FI_Get_personal_income(){return personal_income;};
	FILE* FI_Get_corp_capital(){return corp_capital;};
	FILE* FI_Get_seisan_class_no(){return seisan_class_no;};
	FILE* FI_Get_seisan_class_no_w(){return seisan_class_no_w;};
	FILE* FI_Get_consumer_asset(){return consumer_asset;};
	FILE* FI_Get_producer_asset(){return producer_asset;};
	FILE* FI_Get_toukei(){return toukei;};
	FILE* FI_Get_lorenz(){return lorenz;};
	FILE* FI_Get_employ(){return employ;};
	FILE* FI_Get_equipment_level(){return producer_equipment_level;};
	FILE* FI_Get_labor_cost(){return producer_labor_cost;};
	FILE* FI_Get_seisan_amount(){return producer_seisan_amount;};
	FILE* FI_Get_genryo_price(){return producer_genryo_price;};
	FILE* FI_Get_genryo_no(){return producer_genryo_no;};
	FILE* FI_Get_employ_producer_asset_C(){return employ_producer_asset_C;};
	FILE* FI_Get_employ_producer_asset_R(){return employ_producer_asset_R;};
	FILE* FI_Get_statistic_product(){return statistic_product;};
	FILE* FI_Get_CR_product_relation(){return CR_product_relation;};
	FILE* FI_Get_CR_syubetu_koubaimae_seihinsu(){return CR_syubetu_koubaimae_seihinsu;};
	FILE* FI_get_CR_syubetu_seisansu(){return CR_syubetu_seisansu;};
	FILE* FI_Get_Labor_writer(){return Labor_writer;};
	FILE* FI_Get_Labor_employ_time(){return Labor_employ_time;};
	FILE* FI_Get_Labor_parameter_fixed_wage(){return Labor_parameter_fixed_wage;};
	FILE* FI_Get_Labor_kigyouhozyo(){return Labor_kigyouhozyo;};
	FILE* FI_Get_Producer_Genkin_suitoutyou(){return Producer_Genkin_suitoutyou;};
	FILE* FI_Get_all_money(){return all_money;};
	FILE* FI_Get_free_text3(){return free_text3;};
	FILE* FI_Get_touki_zyunrieki(){return touki_zyunrieki;};
	FILE* FI_Get_Labor_housyu_out(){return Labor_housyu_out;};
	FILE* FI_Get_Labor_retailer_uriage_rank(){return Labor_retailer_uriage_rank;};
	FILE* FI_Get_Labor_koteishihon(){return Labor_koteishihon;};
	FILE* FI_Get_Labor_keihi_soukei(){return Labor_keihi_soukei;};
	FILE* FI_Get_Labor_keihi_toukisonekiritu(){return Labor_keihi_toukisonekiritu;}
	FILE* FI_Get_Tyotikuritu_pro(){return Tyotikuritu_pro;};
	FILE* FI_Get_Tyotikuritu_uriage_rieki(){return Tyotikuritu_uriage_rieki;};
	FILE* FI_Get_Tyotikuritu_consumer(){return Tyotikuritu_consumer;};

	FILE* FI_Get_Delta_G_writing(){return Delta_G_writing;};

	FILE* FI_GET_OUTPUT_GDP(){return OUTPUT_GDP;};
	FILE* FI_GET_OUTPUT_Deposit(){return OUTPUT_Deposit;};
};

void CParameter::FILE_set_parameter()
{
	
	fopen_s(&Initial_file,"..\\parameter\\01Experimental_file.csv","r");	
	fopen_s(&Experimental_file,"..\\parameter\\02Initial_file.csv","r");
	fopen_s(&Variable_file,"..\\parameter\\03Variable_file.csv","r");
	fopen_s(&Other_file,"..\\parameter\\04Other_file.csv","r");

	fscanf_s(Experimental_file,"%d			,%d			,%d			,%d				,%d			,%d		,%lf					,%lf					,%lf				,%lf			,%lf			,%lf			,%d			,%d			,%d					,%d					,%d					,%lf			,%lf				,%d				,%d				,%d			,%d			,%d			"
							,&period_max	,&nconsumer	,&nretailer	,&nwholesaler	,&nequipment,&nbank	,&min_with_drawal_rate	,&max_with_drawal_rate	,&bank_increase_rate,&bonus_rate_min,&bonus_rate_max,&housyu_rate	,&n_class	,&Keynes_a	,&threshold_deposit	,&min_constant_wage	,&max_constant_wage	,&price_up_rate	,&price_down_rate	,&repay_time_ave,&invest_money	,&max_ban	,&nmax_p	,&nmax_c	);
	
	
	fscanf_s(Initial_file,"%d,%d			,%d						,%d					,%d			,%lf				,%lf"
				,&Inv_invest_time,&max_e_flag	,&delta_period_start	,&delta_period_end	,&delta_G	,&DeltaPurchaseRatio,&DeltaSubsidyRatio);


	fscanf_s(Variable_file,"%d				,%d					,%d					,%d					,%d					,%d					,%d					,%d					,%lld				,%lld"
							,&min_init_depo_c	,&max_init_depo_c	,&min_init_depo_w	,&max_init_depo_w	,&min_init_depo_r	,&max_init_depo_r	,&min_init_depo_e	,&max_init_depo_e	,&min_bank_capital	,&max_bank_capital);


	fscanf_s(Other_file,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%lf,%d,%lf,%d,%d,%d,%d,%d,%lf,%lf,%d,%d,%d,%d,%d,%lf,%d,%lf,%d,%d,%d,%d,%lf,%d,%lf,%lf,%lf,%lf,%d,%lf,%lf,%lf,%lf,%lf,%lf,%d,%lf,%lf,%d,%lf,%d,%d"
						,&repay_time_bun,&pricing_switch,&buy_producer_switch,&syotokuzei_switch,&ncase,&nkessan,&nbonus,&n_retailer_worker,&n_whole_worker,&n_equip_worker,&n_bank_worker,&n_government_worker,&seed,&qmaxmax,&qmaxmax_w,&qmaxmin,&qmaxmin_w,&min_price_w,&max_price_w,&first_price,&min_koteihi,&max_koteihi,&min_hendouhi,&max_hendouhi,&cob_alpha_r_up,&cob_alpha_r_down	,&cob_alpha_w_up,&cob_alpha_w_down	,&min_q_limit	,&q_limit_k	,&min_q_init,&min_price_p	,&max_price_p	,&min_price_m	,&max_price_m	,&Adjustment_Sensitivity,&max_q_re	,&min_q_re	,&price_increase_rate	,&price_k	,&loan_time_limit	,&min_genka_whole	,&price_change_upper_rate	,&repay_period	,&capa_increase_rate	,&nmax_p_min	,&invest_max	,&max_memo_time	,&max_reac_flag	,&buy_producer_amount	,&reserve_rate	,&Labor_limit_up_basis	,&Labor_limit_up_decision_switch	,&Labor_salary_change_switch	,&Labor_limit_up_type_switch	,&Labor_choice_office_switch	,&Labor_invest_capital_switch	,&Labor_invest_capital_rate	,&Labor_hozyokin_switch	,&after_tax_rate	,&after_e_flag	,&tax_change_switch	,&change_time	,&calc_gdp_switch	,&R_koubai_yosan_rate	,&Labor_R_buy_profit_switch	,&owncash_rate_inv	,&income_tax_rate	,&sales_tax_rate,&corp_tax_rate	,&profit_under_line	,&gov_invest_ratio	,&hosyou_ratio	,&yugu_ratio	,&kigyou_hozyokin_ratio	,&g_koubai_ratio,&wage_yosan_rate	,&government_price_rate	,&gav_wage_rate	,&Labor_situgyouhosyou_rate	,&Labor_recognition_riekiritu_switch	,&Labor_riekiritu	,&Labor_assignment_switch	,&Labor_assignment_size);




	nbank_con=0;
	n_max_employee=0;
	bonus_rule_switch=0;
	bonus_rate_min_e=0;
	bonus_rate_max_e=0;
	deporate_coefficient=0;
	CR_fixed_q_limit_up=0;CR_fixed_q_limit_down=0;CR_fixed_income=0;CR_limit_genka_up=0;CR_limit_genka_down=0;CR_kurikosi_switch=0;
	max_equip_end=0;
	depo_rate_c=0;
	depo_rate_p=0;


	fclose(Experimental_file);	fclose(Other_file);	fclose(Initial_file);	fclose(Variable_file);	
	printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",nconsumer,nretailer,nwholesaler,nequipment,nbank,n_class,nmax_p,nmax_c,qmaxmax,qmaxmax_w,period_max,nbonus,nmax_p_min);
	printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",min_constant_wage,max_constant_wage,min_init_depo_c,max_init_depo_c,min_init_depo_w,max_init_depo_w,min_init_depo_r,max_init_depo_r);

	fopen_s(&parameter,"..\\data\\parameter.csv","w");
	fprintf(parameter,"Experimental_file\n");
	fprintf(parameter,"period_max(d),nconsumer(d),nretailer(d),nwholesaler(d),nequipment(d),nbank(d),ncase(d),nkessan(d),nbonus(d),nbank_con(d),n_retailer_worker(d),n_whole_woker(d),n_equip_woker(d),n_bank_woker(d),n_government_woker(d),n_max_employee(d),seed(d)\n");
	fprintf(parameter,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",period_max,nconsumer,nretailer,nwholesaler,nequipment,nbank,ncase,nkessan,nbonus,nbank_con,n_retailer_worker,n_whole_worker,n_equip_worker,n_bank_worker,n_government_worker,n_max_employee,seed);
	
	fprintf(parameter,"Other_file\n");
	fprintf(parameter,"n_class(d),nmax_p(d),nmax_c(d),repay_time_ave(d),repay_time_bun(d),max_ban(d),pricing_switch(d),bonus_rule_switch(d),buy_producer_switch(d),syotokuzei_switch(d)\n");
	fprintf(parameter,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",n_class,nmax_p,nmax_c,repay_time_ave,repay_time_bun,max_ban,pricing_switch,bonus_rule_switch,buy_producer_switch,syotokuzei_switch);

	fprintf(parameter,"Initial_file\n");
	fprintf(parameter,"min_constant_wage(d),max_constant_wage(d),bonus_rate_min(lf),bonus_rate_max(lf),bonus_rate_min_e(lf),bonus_rate_max_e(lf),min_with_drawal_rate(lf),max_with_drawal_rate(lf),threshold_deposit,deporate_coefficient\n");
	fprintf(parameter,"%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%d,%lf\n",min_constant_wage,max_constant_wage,bonus_rate_min,bonus_rate_max,bonus_rate_min_e,bonus_rate_max_e,min_with_drawal_rate,max_with_drawal_rate,threshold_deposit,deporate_coefficient);
	
	fprintf(parameter,"Variable_file\n");
	fprintf(parameter,"min_init_depo_c(d),max_init_depo_c(d),min_init_depo_w(d),max_init_depo_w(d),min_init_depo_r(d),max_init_depo_r(d),min_init_depo_e(d),max_init_depo_e(d),min_bank_capital(d),max_bank_capital(d)\n");
	fprintf(parameter,"%d,%d,%d,%d,%d,%d,%d,%d,%lld,%lld\n",min_init_depo_c,max_init_depo_c,min_init_depo_w,max_init_depo_w,min_init_depo_r,max_init_depo_r,min_init_depo_e,max_init_depo_e,min_bank_capital,max_bank_capital);
	
	fprintf(parameter,"parameter_FILE_5\n");
	fprintf(parameter,"qmaxmax(d),qmaxmax_w(d),qmaxmin(d),qmaxmin_w(d),min_price_w(d),max_price_w(d),first_price(d),min_koteihi(d),max_koteihi(d),min_hendouhi(d),max_hendouhi(d),cob_alpha_r_up(d),cob_alpha_r_down(d),cob_alpha_w_up(d),cob_alpha_w_down(d)\n");
	fprintf(parameter,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",qmaxmax,qmaxmax_w,qmaxmin,qmaxmin_w,min_price_w,max_price_w,first_price,min_koteihi,max_koteihi,min_hendouhi,max_hendouhi,cob_alpha_r_up,cob_alpha_r_down,cob_alpha_w_up,cob_alpha_w_down);
	
	fprintf(parameter,"parameter_FILE_6\n");
	fprintf(parameter,"min_q_limit(d),q_limit_k(lf),min_q_init(lf),min_price_p(lf),max_price_p(lf),min_price_m(lf),max_price_m(lf),Adjustment Sensitivity(lf),max_q_re(lf),min_q_re(lf),price_increase_rate(lf),price_k(lf),loan_time_limit(d),min_genka_whole(d),price_up_rate(lf),price_down_rate(lf),price_change_upper_rate(lf)\n");
	fprintf(parameter,"%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%lf,%lf,%lf\n",min_q_limit,q_limit_k,min_q_init,min_price_p,max_price_p,min_price_m,max_price_m,Adjustment_Sensitivity,max_q_re,min_q_re,price_increase_rate,price_k,loan_time_limit,min_genka_whole,price_up_rate,price_down_rate,price_change_upper_rate);
	
	fprintf(parameter,"parameter_FILE_7\n");
	fprintf(parameter,"repay_period(d),capa_increase_rate(lf),invest_money(d),nmax_p_min(d),invest_max(d),max_e_flag(d),max_equip_end (d),max_memo_time(d),max_reac_flag(d),buy_producer_amount(d),CR_fixed_q_limit_up(d),CR_fixed_q_limit_down(d),CR_fixed_income(d),CR_limit_genka(d),CR_limit_genka(d),CR_kurikosi_switch(d)\n");
	fprintf(parameter,"%d,%lf,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",repay_period,capa_increase_rate,invest_money,nmax_p_min,invest_max,max_e_flag,max_equip_end,max_memo_time,max_reac_flag,buy_producer_amount,CR_fixed_q_limit_up,CR_fixed_q_limit_down,CR_fixed_income,CR_limit_genka_up,CR_limit_genka_down,CR_kurikosi_switch);
	
	fprintf(parameter,"parameter_FILE_8\n");
	fprintf(parameter,"reserve_rate(lf),bank_increase_rate(lf),depo_rate_c(lf),depo_rate_p(lf),Labor_limit_up_basis(lf),Labor_switchng_limit_up(d),Labor_salary_change_switch(d),Labor_limit_up_type_switch(d),Labor_choice_office_switch(d),Labor_invest_capital_switch(d) , Labor_invest_capital_rate(lf),Labor_hozyokin_switch(d),after_tax_rate(lf),after_e_flag(d),housyu_rate(lf),tax_change_switch(d),&change_time(d),calc_gdp_switc(d),R_koubai_yosan_rate(lf),Labor_R_buy_profit_switch(d),owncash_rate_inv\n");
	fprintf(parameter,"%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d,%lf,%d,%lf,%d,%lf,%d,%d,%d,%lf,%d,%lf\n",reserve_rate,bank_increase_rate,depo_rate_c,depo_rate_p,Labor_limit_up_basis,Labor_limit_up_decision_switch,Labor_salary_change_switch,Labor_limit_up_type_switch,Labor_choice_office_switch,Labor_invest_capital_switch,Labor_invest_capital_rate,Labor_hozyokin_switch,after_tax_rate,after_e_flag,housyu_rate,tax_change_switch,change_time,calc_gdp_switch,R_koubai_yosan_rate,Labor_R_buy_profit_switch,owncash_rate_inv);
	
	fprintf(parameter,"parameter_FILE_9\n");
	fprintf(parameter,"income_tax_rate (lf),sales_tax_rate (lf),corp_tax_rate(lf),profit_under_line(d),gov_invest_ratio(lf),hosyou_ratio(lf),yugu_ratio(lf),kigyou_hozyokin_ratio(lf),g_koubai_ratio(lf),wage_yosan_rate(lf),government_price_rate(d),gov_wage_rate(lf),Labor_situgyouhosyou_rate(lf),Labor_recognition_riekiritu_switch(d),Labor_riekiritu(lf),Inv_invest_time(d),Keynes_a(d),delta_G,delta_period_start,delta_period_end,DeltaPurchaseRatio,DeltaSubsidyRatio\n");
	fprintf(parameter,"%lf,%lf,%lf,%d,%lf,%lf,%lf,%lf,%lf,%lf,%d,%lf,%lf%d,%lf,%d,%d,%d,%d,%lf,%lf\n",income_tax_rate,sales_tax_rate,corp_tax_rate,profit_under_line,gov_invest_ratio,hosyou_ratio,yugu_ratio,kigyou_hozyokin_ratio,g_koubai_ratio,wage_yosan_rate,government_price_rate,gav_wage_rate,Labor_situgyouhosyou_rate,Labor_recognition_riekiritu_switch,Labor_riekiritu,Labor_assignment_switch,Labor_assignment_size,Inv_invest_time,Keynes_a,delta_G,delta_period_start,delta_period_end,DeltaPurchaseRatio,DeltaSubsidyRatio);
}

void CParameter::FILE_set_printfile()
{
		//////ファイルのオープン//////////
	fopen_s(&OUTPUT_GDP,"..\\data\\01OUTPUT_GDP.csv","w");
	fopen_s(&OUTPUT_Deposit,"..\\data\\02OUTPUT_Deposit.csv","w");

	fopen_s(&employ_file,"..\\data\\employ.txt","w");
	fopen_s(&out,"..\\data\\out.txt","w");							//各エージェントの個別情報
	fopen_s(&out1,"..\\data\\out1.txt","w");						//市場の購入商品の生産種別統計データ
	fopen_s(&out2,"..\\data\\retailer_zaiko.csv","w");						//市場の在庫総数
	fopen_s(&test,"..\\data\\test.txt","w");
	fopen_s(&test2,"..\\data\\product_zaiko.csv","w");
	fopen_s(&test3,"..\\data\\class_price.csv","w");
	fopen_s(&test4,"..\\data\\product_seisan.csv","w");						//製品種別番号別のmax,min,ave
	fopen_s(&product_price,"..\\data\\product_ave_price.csv","w");		//show mem_buyで変われた物の価格集計
	fopen_s(&product_price_w,"..\\data\\product_ave_price_w.csv","w");	//wholesalerの項目別価格推移?
	fopen_s(&market_product,"..\\data\\market_product.csv","w");	//期首・期末　リテイラー＆ホールセラー推移
	fopen_s(&se_income,"..\\data\\se_income.txt","w");				//各Agentの給与
	fopen_s(&se_con,"..\\data\\se_con.txt","w");					//各消費者別所得
	fopen_s(&product_out,"..\\data\\product_out.txt","w");			//各リテイラーの製品種別生産数
	fopen_s(&bank_data,"..\\data\\bank_data.txt","w");				//期別 消費者,生産者,預金残高,借入金残高,消費者預金総額,企業預金総額,預金総額,借入金総額
	fopen_s(&economy,"..\\data\\economy.txt","w");
	fopen_s(&bought_pro,"..\\data\\bought_pro.txt","w");			//生産者別 価格、原価、商品個数、原料、最大生産量、下限生産量
	fopen_s(&retai,"..\\data\\retai.txt","w");
	fopen_s(&Consumer,"..\\data\\Consumer.txt","w");				//消費者
	fopen_s(&Retailer,"..\\data\\Retailer.txt","w");				//リテイラー
	fopen_s(&Wholesaler,"..\\data\\Wholesaler.txt","w");				//ホールセラー
	fopen_s(&Equipment,"..\\data\\Equipment.txt","w");				//設備生産
	fopen_s(&Bank,"..\\data\\Bank.txt","w");				//銀行
	fopen_s(&producer_no,"..\\data\\producer_no.txt","w");
	fopen_s(&se_income_new,"..\\data\\se_income_new.txt","w");
	fopen_s(&invest,"..\\data\\invest.csv","w");
	fopen_s(&bought_money,"..\\data\\bought_money.csv","w");
	fopen_s(&tax,"..\\data\\tax.txt","w");//税金
	fopen_s(&seisan,"..\\data\\seisan.txt","w");
	fopen_s(&agent_no,"..\\data\\agent_no.csv","w");//残Agent数
	fopen_s(&kyuyo,"..\\data\\kyuyo.csv","w");//企業別給与
	fopen_s(&market_data,"..\\data\\market_data.csv","w");//市場データ各種
	fopen_s(&eqw,"..\\data\\eqw.csv","w");//各企業別製品種別設備投資フラグ
	fopen_s(&shiwake,"..\\data\\shiwake.txt","w");	fprintf(shiwake,"Agebt_no , 期数 , 金額 , 借方 , 摘要 , 貸方 , 金額 , kari_code , kashi_code\n");
	fopen_s(&out3,"..\\data\\out_genkin.txt","w");
	fopen_s(&out3_csv,"..\\data\\out_genkin.csv","w");
	fopen_s(&loan,"..\\data\\loan.csv","w");
	fopen_s(&GDP,"..\\data\\GDP.csv","w");
	fopen_s(&seihin_price,"..\\data\\seihin_price.csv","w");
	fopen_s(&zyunkanhyou,"..\\data\\zyunkanhyou.csv","w");
	fopen_s(&zyunkandata,"..\\data\\zyunkandata.csv","w");
	fopen_s(&ac_data1,"..\\data\\ac_data1.csv","w");
	fopen_s(&ac_data2,"..\\data\\ac_data2.csv","w");
	fopen_s(&gyousei_syouhisya,"..\\data\\gyousei_syouhisya.csv","w");
	fopen_s(&show_tax,"..\\data\\show_tax.csv","w");
	fopen_s(&producer_data,"..\\data\\producer_data.csv","w");
	fopen_s(&producer_uriage_kyuyo,"..\\data\\producer_uriage_kyuyo.csv","w");
	fopen_s(&producer_uriage,"..\\data\\producer_uriage.csv","w");
	fopen_s(&free_text,"..\\data\\free_text.csv","w");
	fopen_s(&phenom_writer,"..\\data\\phenom_writer.csv","w");
	fopen_s(&price_check,"..\\data\\price_check.csv","w");
	fopen_s(&price_check_w,"..\\data\\price_check_w.csv","w");
	fopen_s(&free_text2,"..\\data\\free_text2.csv","w");
	fopen_s(&rieki_out,"..\\data\\rieki_out.csv","w");
	fopen_s(&loan_out,"..\\data\\loan_out.csv","w");
	fopen_s(&deposit_out,"..\\data\\deposit_out.csv","w");
	fopen_s(&number_employee,"..\\data\\number_employee.csv","w");
	fopen_s(&personal_income,"..\\data\\personal_income.csv","w");
	fopen_s(&corp_capital,"..\\data\\corp_capital.csv","w");
	fopen_s(&seisan_class_no,"..\\data\\seisan_class_no.csv","w");
	fopen_s(&seisan_class_no_w,"..\\data\\seisan_class_no_w.csv","w");
	fopen_s(&consumer_asset,"..\\data\\consumer_asset.csv","w");
	fopen_s(&producer_asset,"..\\data\\producer_asset.csv","w");
	fopen_s(&toukei,"..\\data\\toukei.csv","w");
	fopen_s(&lorenz,"..\\data\\lorenz.csv","w");
	fopen_s(&employ,"..\\data\\employ.csv","w");
	fopen_s(&producer_equipment_level,"..\\data\\producer_equipment_level.csv","w");
	fopen_s(&producer_labor_cost,"..\\data\\producer_labor_cost.csv","w");
	fopen_s(&producer_seisan_amount,"..\\data\\producer_seisan_amount.csv","w");
	fopen_s(&producer_genryo_price,"..\\data\\producer_genryo_price.csv","w");
	fopen_s(&producer_genryo_no,"..\\data\\producer_genryo_no.csv","w");
	fopen_s(&employ_producer_asset_C,"..\\data\\employ_producer_asset_C.csv","w");
	fopen_s(&employ_producer_asset_R,"..\\data\\employ_producer_asset_R.csv","w");
	fopen_s(&statistic_product,"..\\data\\statistic_product.csv","w");
	fopen_s(&CR_product_relation,"..\\data\\CR_product_relation.csv","w");
	fopen_s(&CR_syubetu_koubaimae_seihinsu,"..\\data\\CR_syubetu_koubaimae_seihinsu.csv","w");
	fopen_s(&CR_syubetu_seisansu,"..\\data\\CR_syubetu_seisansu.csv","w");

	fopen_s(&Labor_writer,"..\\data\\Labor_writer.csv","w");
	fopen_s(&Labor_employ_time,"..\\data\\Labor_employ_time.csv","w");
	fopen_s(&Labor_parameter_fixed_wage,"..\\data\\Labor_parameter_fixed_wage.csv","w");
	fopen_s(&Labor_kigyouhozyo,"..\\data\\Labor_kigyouhozyo.csv","w");
	fopen_s(&Producer_Genkin_suitoutyou,"..\\data\\Producer_Genkin_suitoutyou.csv","w");
	fopen_s(&all_money,"..\\data\\all_money.csv","w");
	fopen_s(&free_text3,"..\\data\\free_text3.csv","w");
	fopen_s(&touki_zyunrieki,"..\\data\\touki_zyunrieki.csv","w");
	fopen_s(&Labor_housyu_out,"..\\data\\Labor_housyu_out.csv","w");
	fopen_s(&Labor_retailer_uriage_rank,"..\\data\\Labor_retailer_uriage_rank.csv","w");
	fopen_s(&Labor_koteishihon,"..\\data\\Labor_koteishihon.csv","w");
	fopen_s(&Labor_keihi_soukei,"..\\data\\Labor_keihi_soukei.csv","w");
	fopen_s(&Labor_keihi_toukisonekiritu,"..\\data\\Labor_keihi_toukisonekiritu.csv","w");

	fopen_s(&Tyotikuritu_pro,"..\\data\\tyotikuritu_pro.csv","w");
	fopen_s(&Tyotikuritu_uriage_rieki,"..\\data\\Tyotikuritu_uriage_rieki.csv","w");
	fopen_s(&Tyotikuritu_consumer,"..\\data\\Tyotikuritu_consumer.csv","w");

	fopen_s(&Delta_G_writing,"..\\data\\Delta_G_writing.csv","w");


	


	
	

	////識別の為の初期出力/////////
	fprintf(OUTPUT_Deposit,"t,Consumer_Deposit,Producer_Deposit\n");
	fprintf(OUTPUT_GDP,"t,GDP\n");


	fprintf(test3,"期数,クラスナンバ,マックス,ミニ,アベ\n");//file出力
	fprintf(product_out,"リテイラー,製品種,生産数\n");//file出力
	fprintf(bank_data,"期数,コンシュマナンバー,プロデューサナンバー,預金残高,借入金残高,消費者預金総額,企業預金総額,預金総額,借入金総額\n");//file出力
	fprintf(market_product,"期数,wh生産数,wh購買前製品数,wh購買後製品数,re_生産数,re_消費者購買前製品数,re_消費者購買後製品数,incomen,re_政府購買前製品数,re_政府購買後製品数,re_企業購買前製品数,re_企業購買後製品数\n");//file出力
	fprintf(se_income,"期数,ナンバー,給与,リテイラー合計,設備合計,ホールセラー合計,合計\n");//file出力
	fprintf(producer_no,"期数,リテイラ数,ホールセラー数\n");
	fprintf(bought_money,"期数,bought_sum_r,bought_sum_w,bought_sum\n");
	fprintf(tax,"期数,所得税,企業別所得税,所得税合計\n");
	fprintf(seisan,"Prodcer_type,Type_no,Producer_no,price_genka,price,sumq,q,ncr_p,sum_price_genka,total_price_genka\n");
	fprintf(agent_no,"期数,Consumer,Retailer,Wholesaler,Equipment,Bank,R_employ,W_employ,E_employ,B_employ,Employ\n");
	fprintf(kyuyo,"期数,R_給与合計,W_給与合計,E_給与合計,B_給与合計,給与総合計\n");
	fprintf(eqw,"期数,企業別製品種別設備投資フラグ\n");
	fprintf(GDP,"期数,売上,在庫,GDP,消費者需要,政府需要,設備投資,少額固定資本形成,乗数\n");
	fprintf(seihin_price,"期数,エージェント,在庫\n");
	fprintf(zyunkandata,"期数,r売上,r在庫,r支払利息,r原料,r労務費,r一般管理費,r減価償却費,rr製品購買,r給付金,r営業余剰,w売上,w在庫,w支払利子,w労務費,w一般管理費,w減価償却,wr製品購買,w給付金,w営業余剰,e売上,e支払利子,e労務費,一般管理費,e給付金,e営業余剰,b売上,b支払利息,b労務費,b一般管理費,b利益\n");
	fprintf(gyousei_syouhisya,"期数,税収,給与予算,政策予算,失業補償予算,政府投資予算,優遇予算,企業補助金予算,購買予算,政府購買,行政消費者一人当たり給与,失業保障一人当たり支給金,政府投資額,優遇補助,企業補助金,政府残金\n");
	fprintf(market_data,"期数,消費者給与総計,民間給与総計,公務員給与総計,消費者現金,消費者預金,r預金,w預金,e預金,企業預金総計,b現金,短期借入,長期借入,借入合計\n");
	fprintf(show_tax,"期数,法人税,所得税,消費税,合計\n");
	fprintf(invest,"期数,Re_設備投資回数,Wh_設備投資回数,Re_設備投資金額,Wh_設備投資金額\n");
	fprintf(rieki_out,"期数,");
	fprintf(loan_out,"期数,");
	fprintf(deposit_out,"期数,");
	fprintf(product_price,"期数,");
	fprintf(product_price_w,"期数,");
	fprintf(number_employee,"期数,retailer,");
	fprintf(personal_income,"期数");
	fprintf(corp_capital,"期数");
	fprintf(price_check,"期数,");
	fprintf(price_check_w,"期数,");
	fprintf(seisan_class_no,"期数,");
	fprintf(seisan_class_no_w,"期数,");
	fprintf(consumer_asset,"期数,");
	fprintf(producer_asset,"期数,");
	fprintf(toukei,"期数,");
	fprintf(lorenz,"期数,,");
	fprintf(producer_uriage,"期数,");
	fprintf(employ,"期数,");
	fprintf(employ_producer_asset_C,"期数,");
	fprintf(employ_producer_asset_R,"期数,");
	fprintf(Labor_writer,"労働・設備製造に関する意思決定関係の記述");
	fprintf(Labor_employ_time,"期数 , 雇用回数 ,  , ～～～～各企業の雇用行動実現時の期毎の回数\n");
	fprintf(Labor_parameter_fixed_wage,"期数 , パラメータ固定給 , ～～～～消費者が状態変数として固有している固定給のパラメータ\n");
	fprintf(Labor_kigyouhozyo,"期数 , \n");
	fprintf(all_money,"タイミング , 期数 , 合計 , 消費者現金 , 消費者預金 , R現金 , R預金 , W現金 , W預金 , E現金 , E預金 , B現金 , B預金 , G現金 , 現金のみ合計 , 現金+預金（銀行除く） \n");
	fprintf(touki_zyunrieki,"期数 , 税引き後純利益\n");
	fprintf(Labor_housyu_out,"期数 \n");
	fprintf(Labor_koteishihon,"期数 , 資本固定額\n");
	fprintf(Labor_keihi_soukei,"期数 , ");
	fprintf(Labor_keihi_toukisonekiritu,"期数 , ");
	fprintf(Tyotikuritu_pro,"期数 , リテイラー税後利益 , リテイラー剰余 , リテイラー貯蓄率 , ホールセラー税後利益 , ホールセラー剰余 , ホールセラー貯蓄率 , 設備税後利益 , 設備剰余 , 設備貯蓄率 , 企業税後利益 , 企業剰余 , 企業貯蓄率,リテイラー貯蓄率最大値 , ホールセラー貯蓄率最大値 , 設備貯蓄率最大値\n");
	fprintf(Tyotikuritu_uriage_rieki,"期数 , リテイラー売上 , リテイラー支出 , リテイラー貯蓄率 , ホールセラー売上 , ホールセラー支出 , ホールセラー貯蓄率 , 設備税後売上 , 設備支出 , 設備貯蓄率 , 企業税後売上 , 企業支出 , 企業貯蓄率\n");
	fprintf(Tyotikuritu_consumer,"期数 , 収入 , 支出 , 貯蓄率\n");

}






#endif