//CAccount.h
#ifndef INC_CAccount
#define INC_CAccount
#include <stdio.h>
#include <vector>
#include"CParameter.h"
#include"CTax.h"
#include"CRandum.h"
using namespace std;

class CAccount
{
/*	struct debt{
		double i_rate;
		double A;//初期借入額
		double ar
	}*/
	struct shiwake {
		char date[20],karikata[50],tekiyo[50],kashikata[50];
		long long kari,kashi;
		int kari_code,kashi_code;
		int aite_Agent_no;
	}*sh;
	struct kanjyo_kamoku
		{
		char kamoku[50];
		long long karikata_total;
		long long kashikata_total;
		long long zandaka;
		long long kisyu_zandaka;
		long long kimatu_zandaka;
		int code;//=0:資産科目,=1:経費科目,=2:負債科目,=3：売上科目
	}*km,*kmr;
	struct shisan_kamoku
	{
		char kamoku[50];
	}*shisan_km;
	struct keihi_kamoku
	{
		char kamoku[50];
	}*keihi_km;
	struct husai_kamoku
	{
		char kamoku[50];
	}*husai_km;
	struct uriage_kamoku
	{
		char kamoku[50];
	}*uriage_km;
	struct genyokin_suitou			//現金預金出納帳並列型　一応保存
	{
		int i_period;	//期数
		char tekiyou[50];	//摘要
		char tekiyou_aite[50];	//摘要の相手
		char kamoku[50];
		long long kari_yokin;		//預金収入
		long long kashi_yokin;	//預金支出
		long long yokin_zandaka;	//預金残高

		long long kari_genkin;	//現金収入
		long long kashi_genkin;	//現金支出
		long long genkin_zandaka;	//預金残高
		int code;			//現預金出納コード　1:現金収入,2:現金支出,3:預金収入,4:預金支出
	}*genyo_suitou;

	struct suitoutyou			//現金、預金出納帳構造体、内容は同じなので構造体は同一のものを使用
	{
		int i_period;			//期数
		char tekiyou[50];		//摘要
		char tekiyou_aite[50];	//摘要相手
		char kamoku[50];		//相手科目
		long long kari;				//借方（収入）
		long long kashi;				//貸方（支出）
		long long zandaka;			//残高
		int code;				//現金出納帳コード
	}*genkin_suitou,*yokin_suitou;

	struct ather_kamoku			//科目で期末決算時等特殊なタイミングでのみ使用するデータ変数
	{
		long long zeimae_soneki;		//税引き前利益
		long long minus_soneki;		//ボーナス計算時に行うマイナス分損益の補てん

		long long touki_zyun_soneki;	//当期純利益
		long long mibarai_zei;		//期中の支払われた未払税
		long long touki_mibarai_zei;	//当期計算未払税
		long long kisyu_mibarai_zei;	//期首未払税
		long long kimatu_mibarai_zei;	//期末未払税

		long long mibarai_shouhi_zei;			//期中の支払われた未払い消費税
		long long touki_mibarai_shouhi_zei;	//当期計算未払消費税
		long long kisyu_mibarai_shouhi_zei;	//期首未払い消費税
		long long kimatu_mibarai_shouhi_zei;	//期末未払い消費税

		long long rieki_zyouyo;		//利益剰余金
		long long kisyu_rieki_zyouyo;	//期首利益剰余金
		long long kimatu_rieki_zyouyo;//期末利益剰余金

		long long mibarai_bonus;			//
		long long touki_mibarai_bonus;	//
		long long kisyu_mibarai_bonus;	//
		long long kimatu_mibarai_bonus;	//

		long long mibarai_housyu;
		long long touki_miabrai_housyu;
		long long kisyu_mibarai_housyu;
		long long kiamtu_mibarai_housyu;

	}*at_km;

	struct out_kessan_data		//費用、売上等、期末処理で消失するデータの保管庫
	{
		long long genryou_out;	
		long long setubi_out; 
		long long ukerisi_out; 
		long long siharisi_out;
		long long kyuyo_out;		
		long long bonus_out;	
		long long uriage_out;	
		long long rieki_out;
		long long zaiko_zandaka_t_1; 
		long long genkasyoukyaku_out;	
		long long zaiko_out;
		long long kyuyo;
		long long kyuyo_c;
		long long houzin_zei;
		long long syotoku_zei;
		long long yakuin_housyu;
		long long syoumouhin;
		long long kigyou_hozyokin;		//受け取る企業側の企業補助金
		long long kigyou_hozyokin_g;		//支払う政府側の企業補助金
		long long syouhisya_kouhukin;		//受け取る消費者側の交付金
		long long syouhisya_kouhukin_g;	//支払う政府側の交付金
		long long touki_zeigo_rieki;
		long long touki_zyunsoneki;
	}*out_data;


	int i_period;
	int Agent_no;
	int ndata;
	int nkamoku;
	int nshisan_kamoku;
	int nkeihi_uriage_kamoku;
	int nkeihi_kamoku;
	int nuriage_kamoku;
	int nhusai_kamoku;
	int loan_point;			//短期借入増加確認
	long long zeimae_rieki;		//税引き前利益
	long long touki_soneki;		//税引き後利益、当期純利益
	long long pl_rieki;			//
	long long bl_rieki;			//
	long long rieki;
	int agent_type;			//Agent_type=10; 一般消費者
							//Agent_type=20; 一般消費者向け生産者
							//Agent_type=30; 生産者向け生産者（原料を生産)
							//Agent_type=40; 生産者向け生産者（設備を拡充)
							//Agent_type=50; 銀行
							//Agent_type=9999;	政府



	long long genkin_kisyu_zandaka;			long long genkin_kimatu_zandaka;
	long long yokin_kisyu_zandaka;			long long yokin_kimatu_zandaka;
	long long yokin_b_kisyu_zandaka;		long long yokin_b_kimatu_zandaka;
	long long loan_s_kisyu_zandaka;			long long loan_s_kimatu_zandaka;
	long long loan_s_b_kisyu_zandaka;		long long loan_s_b_kimatu_zandaka;
	long long loan_l_kisyu_zandaka;			long long loan_l_kimatu_zandaka;
	long long loan_l_b_kisyu_zandaka;		long long loan_l_b_kimatu_zandaka;
	long long shihon_kisyu_zandaka;			long long shihon_kimatu_zandaka;
	long long mibarai_kisyu_zandaka;		long long mibarai_kimatu_zandaka;
	long long seihin_kisyu_zandaka;			long long seihin_kimatu_zandaka;
	long long genryouhi_kisyu_zandaka;		long long genryouhi_kimatu_zandaka;
	long long setubi_kisyu_zandaka;			long long setubi_kimatu_zandaka;
	long long chingin_kisyu_zandaka;		long long chingin_kimatu_zandaka;
	long long rounuhi_kisyu_zandaka;		long long rounuhi_kimatu_zandaka;
	long long bonus_kisyu_zandaka;			long long bonus_kimatu_zandaka;
	long long kanrihi_kisyu_zandaka;		long long kanrihi_kimatu_zandaka;
	long long uriage_genka_kisyu_zandaka;	long long uriage_genka_kimatu_zandaka;
	long long uriage_kisyu_zandaka;			long long uriage_kimatu_zandaka;
	long long syoukyaku_kisyu_zandaka;		long long syoukyaku_kimatu_zandaka;
	long long kari_risoku_s_kisyu_zandaka;	long long kari_risoku_s_kimatu_zandaka;
	long long kari_risoku_l_kisyu_zandaka;	long long kari_risoku_l_kimatu_zandaka;
	long long bank_risoku_u_kisyu_zandaka;	long long bank_risoku_u_kimatu_zandaka;
	long long genzairyo_kisyu_zandaka;		long long genzairyo_kimatu_zandaka;
	long long kyuyo_kisyu_zandaka;			long long kyuyo_kimatu_zandaka;


	long long kashi_risoku_s_kisyu_zandaka;	long long kashi_risoku_s_kimatu_zandaka;
	long long kashi_risoku_l_kisyu_zandaka;	long long kashi_risoku_l_kimatu_zandaka;
	long long bank_risoku_h_kisyu_zandaka;	long long bank_risoku_h_kimatu_zandaka;
	long long genryou_out;			long long setubi_out;			long long ukerisi_out;	long long siharisi_out;
	long long kyuyo_out;			long long bonus_out;			long long uriage_out;	long long rieki_out;
	long long zaiko_zandaka_t_1;	long long genkasyoukyaku_out;	long long zaiko_out;
	long long kyuyo_c_out;
	long long houzin_zei_out;		//法人税の期中決算保存用
	long long syoumouhin_out;		//消耗品の期中決算保存用
	long long kigyou_hozyokin_out;//企業補助金の期中決算保存用
	long long yakuin_housyu_out;
	long long hozyokin_out;		//受け取り補助金の期中決算保存用
	long long kouhukin_out;		//消費者向け交付金（優遇政策等で使用）の期中決算保存用
	long long buy_retailer_product_out;	//企業のリテイラ製品の購買額
	long long out_touki_zyouyo;
	long long touki_keihi_soukei;		//当期の経費総計


	vector <struct shiwake *> mem_sh;
	vector <struct shisan_kamoku *> mem_shisan_km;
	vector <struct keihi_kamoku *> mem_keihi_km;
	vector <struct husai_kamoku *> mem_husai_km;
	vector <struct uriage_kamoku *> mem_uriage_km;
	vector <struct kanjyo_kamoku *> mem_km;
	vector <struct kanjyo_kamoku *> mem_kmr;
	vector <long long > mem_riekizyouyo;					//累積赤字が存在する場合の税処理のため
//	vector <struct genyokin_suitou *> mem_suitou;	現金預金出納帳並列型　一応保存
	vector <struct suitoutyou *> mem_genkin_suitou;	//現金出納帳　構造体は預金と同様のものを使用
	vector <struct suitoutyou *> mem_yokin_suitou;	//預金出納帳　構造体は現金と同様のものを使用

	CParameter *cpara;
	CTax *cta;

//	FILE *shiwake;	FILE *out3;	FILE *out3_csv;	FILE *loan;
	FILE *seihin_price;

	FILE *suitoutyou;
	FILE *yokin;
	int nkessan;//nkessan=0：out3へのプリントアウト
				//nkessan=1：out3への部分的プリントアウト
				//nkessan!=0or1:out3へのプリントアウトをしない
	CRandum *cr;

public:
	CAccount();
	void Set_parameter_class(CParameter * cpar){cpara=cpar;};
	void Set_CTax_class(CTax *ct){cta=ct;};
	void Set_Agent_type(int agtype){agent_type=agtype;};

	__int64 Tyotiku_get_zeigorieki(){return out_data->touki_zeigo_rieki;};
	__int64 tyotiku_get_zyunneki(){return out_data->touki_zyunsoneki;};

	//出納帳
	void Set_genyokin_suitoutyou(int i_period,char *tekiyou,char *tekiyou_aite,char *kamoku,int amount,int code);
	void Set_genkin_suitoutyou(int i_period,char *tekiyou,char *tekiyou_aite,char *kamoku,long long amount,int code);
	void Set_yokin_suitoutyou(int i_period,char *tekiyou,char *tekiyou_aite,char *kamoku,long long amount,int code);
	void Reset_genyokin_suitoutyou();
	int Get_genkin_suitoutyou_zandaka(){return int(mem_genkin_suitou[mem_genkin_suitou.size()-1]->zandaka);};
	int Get_yokin_suitoutyou_zandaka(){return int(mem_yokin_suitou[mem_yokin_suitou.size()-1]->zandaka);};
//long long型対応
	__int64 Get_genkin_suitoutyou_zandaka_l(){return mem_genkin_suitou[mem_genkin_suitou.size()-1]->zandaka;};
	__int64 Get_yokin_suitoutyou_zandaka_l(){return mem_yokin_suitou[mem_yokin_suitou.size()-1]->zandaka;};
//～～～～～～～～～～

	//出納帳終わり

	//決算用関数
	void Kessan(int i_period,int ncase,FILE *out3,FILE *out3_csv);	//以下の決算用関数を管理する

	void Define_km();		//科目コード
	void Re_define_km();	//
	void Shisan_table(int i_period,int ncase,FILE *out3,FILE *out3_csv);	//仕分けをすべて科目に振り分け
	void PLsheet_table(FILE *out3,FILE *out3_csv);		//PLシートに必要な数値を計算	税引き前利益確定
	void Balance_table(FILE *out3,FILE *out3_csv);		//バランステーブルに必要な数値を計算　税引き前利益確定
	void Calculation_tax();								//税金額の計算、未払税金計上、当期利益確定
	void Calculation_touki_soneki();					//当期の損益を計算する
	void Soneki_hurikae();								//当期損益を資本に編入する
	void Show_kimatu_zandaka(int x,FILE *out3);			//
	void Convert_kimatu_kisyu();						//期末数値を期首数値に移し替え（期末の最終処理）
	void Loan_s_check();								//短期借入の状態チェック
	void Erase_mem_sh();								//仕分けを前削除

	//決算用関数終了

	void Print_balance_table(FILE *out3,FILE *out3_csv);//
	void Print_pLsheet_table(FILE *out3,FILE *out3_csv);//


	//税金関連
	int Get_mibarai_tax(){return int(at_km->kisyu_mibarai_zei);};
	int Get_mibarai_shouhi_tax(){return int(at_km->kisyu_mibarai_shouhi_zei);};
	void Set_shiharai_tax(int pay_tax){at_km->mibarai_zei=at_km->mibarai_zei-pay_tax;};//printf("未払税　：　期首%d , 期中%d , 期末%d\n",at_km->kisyu_mibarai_zei,at_km->mibarai_zei,at_km->kisyu_mibarai_zei);};
	void Set_shiharai_bonus(int pay_bonus){at_km->mibarai_bonus=at_km->mibarai_bonus-pay_bonus;};
	void Set_shiharai_shouhi_tax(int pay_tax){at_km->mibarai_shouhi_zei=at_km->mibarai_shouhi_zei-pay_tax;};
	void Calc_bonus();
	void Calc_shouhi_tax();

	//税金関連終了

	//報酬関連
	int Get_mibarai_housyu(){return int(at_km->kisyu_mibarai_housyu);};
	void Set_shiarai_housyu(int pay_housyu){at_km->mibarai_housyu=at_km->mibarai_housyu-pay_housyu;};
	void Set_mibarai_housyu(int mibarai){at_km->kisyu_mibarai_housyu+=mibarai;};
	void kessan_housyu();
	void calc_housyu();

	//報酬関連終了


	void Set_seihin_price(FILE *fi){seihin_price=fi;};
	void Set_nkessan(int nkessan1){nkessan=nkessan1;};	
	int Get_kamoku(int index,char *kamoku);
	long long Get_kamoku_l(int index,char *kamoku);
	void Set_kisyu_re();
	void Set_kimatu_re();
	void Set_Agent_no(int Agent_no1){Agent_no=Agent_no1;};
	void Get_kimatu_zandaka(int *genkin,int *yokin,int *loan_s,int *loan_l,int *shihon,int *mibarai,int *seihin,int *genryouhi,int *setubi);
	int Get_rieki(){return int(at_km->touki_zyun_soneki);};
	void Set_kisyu_zandaka(int genkin,int yokin,int loan_s,int loan_l,int shihon,int mibarai,int seihin,int genryouhi,int setubi);
	void Set_kisyu_zandaka_l(long long genkin,int yokin,int loan_s,int loan_l,long long shihon,int mibarai,int seihin,int genryouhi,int setubi);
	void Set_km_code(int i,int code){mem_km[i]->code=code;};
	void Set_kmr_code(int i,int code){mem_kmr[i]->code=code;};
	int Get_km_code(int i){return mem_km[i]->code;};
	int Get_kmr_code(int i){return mem_kmr[i]->code;};
	void Set_km_zandaka(int i,int zandaka){mem_km[i]->zandaka=zandaka;};
	void Set_km_kisyu_zandaka(int i,int zandaka){mem_km[i]->kisyu_zandaka=zandaka;};
	int Get_km_zandaka(int i){return int(mem_km[i]->zandaka);};
	struct shiwake* Get_sh(int i){return mem_sh[i];};
	void Set_km(struct kanjyo_kamoku *km1){km=km1;};
	void Set_km_kamoku(int i,char *kamoku){strcpy_s(mem_km[i]->kamoku,_countof(mem_km[i]->kamoku),kamoku);};
	void Set_kmr_kamoku(int i,char *kamoku){strcpy_s(mem_kmr[i]->kamoku,_countof(mem_kmr[i]->kamoku),kamoku);};
	void Set_shisan_kamoku(int i,char *kamoku){	strcpy_s(mem_shisan_km[i]->kamoku,_countof(mem_shisan_km[i]->kamoku),kamoku);};
	struct kanjyo_kamoku* Get_km(int i){return mem_km[i];};
	struct kanjyo_kamoku* Get_kmr(int i){return mem_kmr[i];};
	struct shisan_kamoku* Get_shisan_km(int i){return mem_shisan_km[i];};
	struct keihi_kamoku* Get_keihi_km(int i){return mem_keihi_km[i];};
	struct uriage_kamoku* Get_uriage_km(int i){return mem_uriage_km[i];};
	struct husai_kamoku* Get_husai_km(int i){return mem_husai_km[i];};
	void Shisan_table(struct shiwake *sh,struct kanjyo_kamoku *km,FILE *out);
	
	

	
	int strcmp(char *s1,char *s2);
	void Set_shiwake(int i_period,int kari,char *karikata,char *tekiyo,char *kashikata,int kashi,int kari_code,int kashi_code);
	template<class T,class U> void Set_shiwake_T(const T&i_period,const U&kari,char *karikata,char *tekiyo,char *kashikata,const U&kashi,const T&kari_code,const T&kashi_code);
	void Check_km(char *kamoku,int code);
	
	int Get_nkamoku(){nkamoku=mem_km.size();return nkamoku;};
	void Print_kamoku();
	void Set_ndata(int ndata1);
	
	
	
	void Show_kisyu_zandaka(int x,FILE *out3);
	int Get_uriage_total();
	int Get_zaiko();
	int Get_genka();
	int Get_bonus();
	int Get_uriagegenka();
	int Get_syoukyaku();
	int Get_ippankanri();
	int Get_toukirieki();
	int Get_genryou_out(){return int(genryou_out);};
	int Get_setubi_out(){return int(setubi_out);};
	int Get_ukerisi_out(){return int(ukerisi_out);};
	int Get_siharisi_out(){return int(siharisi_out);};
	int Get_kyuyo_out(){return int(kyuyo_out);};
	int Get_bonus_out(){return int(bonus_out);};
	int Get_uriage_out(){return int(uriage_out);};
	int Get_rieki_out(){return int(rieki_out);};
	int Get_genkasyoukyaku_out(){return int(genkasyoukyaku_out);};
	int Get_zaiko_out(){return int(zaiko_out);};
	int Get_kyuyo_c_out(){return int(kyuyo_c_out);};
	int Get_genkin_zandaka(){return int(genkin_kimatu_zandaka);};
	int Get_yokin_zandaka(){return int(yokin_kimatu_zandaka);};
	int Get_loan_l_kimatu_zandaka(){return int(loan_l_kimatu_zandaka);};
	int Get_loan_s_kimatu_zandaka(){return int(loan_s_kimatu_zandaka);};
	int Get_syoumouhin_out(){return int(syoumouhin_out);};
	int Get_houzinzei_out(){return int(houzin_zei_out);};
	int Get_yakuin_housyu_out(){return int(yakuin_housyu_out);};
	int Get_loan_point(){return loan_point;};
	int Get_kimatu_riekizyouyo(){return int(at_km->kimatu_rieki_zyouyo);};
	int Get_kisyu_riekizyouyo(){return int(at_km->kisyu_rieki_zyouyo);};
	int Get_touki_riekizyouyo(){return int(out_touki_zyouyo);};
	int Get_kigyou_hozyokin_out(){return int(kigyou_hozyokin_out);};			//政府側の企業補助金出力
	int Get_hozyokin_out(){return int(hozyokin_out);};						//受け取り側の補助金出力
	int Get_kouhukin_out(){return int(kouhukin_out);};

	int Get_hozyokin_out_g();
	int Get_shihon_out();
	void Shisan_tableW(int i_period,int ncase,FILE *out3,FILE *out3_csv);
	void Show_genyokin_suitou(FILE *suitoutyou,FILE *yokin);
	int Get_touki_zeimae_rieki(){return int(at_km->zeimae_soneki);};
	int Get_buy_retailer_out(){return int(buy_retailer_product_out);};
	int Get_karikashi_ac(int index,char *kamoku);
	int Get_kisyu_ac(int index,char *kamoku);
	int Get_kimatu_mibarai_bonus(){return int(at_km->kimatu_mibarai_bonus);};
	int Get_touki_mibarai_bonus(){return int(at_km->touki_mibarai_bonus);};
	int Get_mibarai_bouns(){return int(at_km->mibarai_bonus);};
	void Kessan2(int i_period,int ncase,FILE *out3,FILE *out3_csv);
	__int64 Get_kisyu_shihon_zandaka(){return shihon_kisyu_zandaka;};
	int Get_touki_zyunsoneki(){return at_km->touki_zyun_soneki;}
	int Get_touki_keihi_soukei(){return touki_keihi_soukei;};

	void print_test(){
		for(int i=0;i<int(mem_km.size());i++)
		{
			
		}
	}
	

};
//CAccount.cpp
CAccount::CAccount()
{
	ndata=0;
	genryou_out=0;
	setubi_out=0;
	ukerisi_out=0;
	siharisi_out=0;
	kyuyo_out=0;
	bonus_out=0;
	uriage_out=0;
	zeimae_rieki=0;
	touki_soneki=0;
	rieki_out=0;
	genkasyoukyaku_out=0;
	zaiko_out=0;
	kyuyo_c_out=0;
	zaiko_zandaka_t_1=0;
	houzin_zei_out=0;
	yakuin_housyu_out=0;
	syoumouhin_out=0;
	kigyou_hozyokin_out=0;
	hozyokin_out=0;
	kouhukin_out=0;
	buy_retailer_product_out=0;
	out_touki_zyouyo=0;
	touki_keihi_soukei=0;
	
	//出納帳系初期設定
	genkin_suitou=new struct suitoutyou;
	genkin_suitou->zandaka=0;	
	mem_genkin_suitou.push_back(genkin_suitou);

	yokin_suitou=new struct suitoutyou;
	yokin_suitou->zandaka=0;
	mem_yokin_suitou.push_back(yokin_suitou);

	//出納帳系初期設定終了


	//その他科目（決算時使用）初期設定
	at_km=new struct ather_kamoku;
	at_km->kimatu_mibarai_zei=0;
	at_km->kiamtu_mibarai_housyu=0;
	at_km->kimatu_rieki_zyouyo=0;
	at_km->kisyu_mibarai_zei=0;
	at_km->kisyu_mibarai_housyu=0;
	at_km->kisyu_rieki_zyouyo=0;
	at_km->mibarai_zei=0;
	at_km->mibarai_housyu=0;
	at_km->rieki_zyouyo=0;
	at_km->touki_zyun_soneki=0;
	at_km->zeimae_soneki=0;
	at_km->touki_mibarai_zei=0;
	at_km->touki_miabrai_housyu=0;
	at_km->kisyu_mibarai_bonus=0;
	at_km->touki_mibarai_bonus=0;
	at_km->mibarai_bonus=0;
	at_km->kimatu_mibarai_bonus=0;
	at_km->minus_soneki=0;
	at_km->mibarai_shouhi_zei=0;
	at_km->touki_mibarai_shouhi_zei=0;
	at_km->kimatu_mibarai_shouhi_zei=0;
	at_km->kisyu_mibarai_shouhi_zei=0;

	for(int i=0;i<7;i++)	mem_riekizyouyo.push_back(0);

	//その他科目初期設定終了

	//出力用データ初期設定
	out_data=new struct out_kessan_data;
	out_data->bonus_out=0;
	out_data->genkasyoukyaku_out=0;
	out_data->genryou_out=0;
	out_data->houzin_zei=0;
	out_data->yakuin_housyu=0;
	out_data->kigyou_hozyokin=0;
	out_data->kigyou_hozyokin_g=0;
	out_data->kyuyo=0;
	out_data->kyuyo_c=0;
	out_data->kyuyo_out=0;
	out_data->rieki_out=0;
	out_data->setubi_out=0;
	out_data->siharisi_out=0;
	out_data->syotoku_zei=0;
	out_data->syouhisya_kouhukin=0;
	out_data->syouhisya_kouhukin_g=0;
	out_data->syoumouhin=0;
	out_data->ukerisi_out=0;
	out_data->uriage_out=0;
	out_data->zaiko_out=0;
	out_data->zaiko_zandaka_t_1=0;
	out_data->touki_zeigo_rieki=0;
	out_data->touki_zyunsoneki=0;
	//出力用データ初期設定 終了


}
void CAccount::Kessan(int i_period,int ncase,FILE *out3,FILE *out3_csv)
{	

	if(agent_type==10)								//消費者エージェント
	{
		Define_km();								//科目コード
		if(nkessan==0) Print_kamoku();
		Re_define_km();	//
		Shisan_table(i_period,ncase,out3,out3_csv);	//仕分けをすべて科目に振り分け仮作業（tyukan_switch=0）で税前利益を確定
		PLsheet_table(out3,out3_csv);				//PLシートに必要な数値を計算
		Balance_table(out3,out3_csv);				//バランステーブルに必要な数値を計算
		Calculation_tax();
		Calculation_touki_soneki();					//損益計算、税引き後利益確定
		
		Print_pLsheet_table(out3,out3_csv);
		Print_balance_table(out3,out3_csv);

		Show_kimatu_zandaka(ncase,out3);			//
		Convert_kimatu_kisyu();						//期末数値を期首数値に移し替え（期末の最終処理）
		Erase_mem_sh();	
	}
	else if(agent_type==99999)						//行政エージェント
	{
		Define_km();								//科目コード
		if(nkessan==0) Print_kamoku();
		Re_define_km();	//
		Shisan_table(i_period,ncase,out3,out3_csv);	//仕分けをすべて科目に振り分け仮作業（tyukan_switch=0）で税前利益を確定
		PLsheet_table(out3,out3_csv);				//PLシートに必要な数値を計算
		Balance_table(out3,out3_csv);				//バランステーブルに必要な数値を計算
		Print_pLsheet_table(out3,out3_csv);
		Print_balance_table(out3,out3_csv);

		Show_kimatu_zandaka(ncase,out3);			//
		Convert_kimatu_kisyu();						//期末数値を期首数値に移し替え（期末の最終処理）
		Erase_mem_sh();	
	}
	else											//企業エージェント系
	{	
		Define_km();								//科目コード

		if(nkessan==0) Print_kamoku();
		Re_define_km();	//
		Shisan_table(i_period,ncase,out3,out3_csv);	//仕分けをすべて科目に振り分け仮作業（tyukan_switch=0）で税前利益を確定
		PLsheet_table(out3,out3_csv);				//PLシートに必要な数値を計算
		Balance_table(out3,out3_csv);				//バランステーブルに必要な数値を計算
		if(agent_type==20)Calc_shouhi_tax();		//消費税の計算
		Calc_bonus();								//ボーナス計算
		Calculation_tax();							//税前利益から税額を計算して経常
		calc_housyu();
		Calculation_touki_soneki();					//損益計算、税引き後利益確定

		
		Print_pLsheet_table(out3,out3_csv);
		Print_balance_table(out3,out3_csv);	
		Loan_s_check();								//短期借入が前期より上回っているかチェック
		Show_kimatu_zandaka(ncase,out3);			//
		Convert_kimatu_kisyu();						//期末数値を期首数値に移し替え（期末の最終処理）
		Erase_mem_sh();	
		

	}
}
void CAccount::calc_housyu()
{
	long long zeibikigo_rieki=at_km->zeimae_soneki-at_km->minus_soneki-at_km->kimatu_mibarai_zei;	//計算用税前利益変数　zeimae_riekiはPLsheet_tableで計算済み
	long long kurikoshi_soneki=0;		//関数内、以前までの損益の使用変数
	long long housyu_temp=0;	//関数内、支払い義務がある利益額用変数
	long long calctax	=0;			//計算した税金用変数
	int i;

	//～～～～～～今期税金計算処理
//		printf("agentno=%d , zeimaesoneki=%d , ",Agent_no,ca_rieki);
	if(zeibikigo_rieki>0)		//税前利益が存在する場合
	{
		housyu_temp=int(double(zeibikigo_rieki)*double(cpara->Get_PARA_housyu_rate()));
	}
		
	at_km->touki_miabrai_housyu=housyu_temp;
	at_km->kiamtu_mibarai_housyu=at_km->kisyu_mibarai_housyu+at_km->mibarai_housyu+at_km->touki_miabrai_housyu;

}


void CAccount::Loan_s_check()
{//現在未使用
	fprintf(cpara->FI_Get_se_con(),"agent %d , size=%d\n",Agent_no,mem_km.size());
	for(int i=0;i<int(mem_km.size());i++)
	{
		if(strcmp(mem_km[i]->kamoku,"短期借入金")==0)
		{
			fprintf(cpara->FI_Get_se_con(),"agent no %d , kisyu %d , kimatu %d\n",Agent_no,mem_km[i]->kisyu_zandaka,mem_km[i]->kimatu_zandaka);
			if(mem_km[i]->kisyu_zandaka<mem_km[i]->kimatu_zandaka)
			{
				loan_point=1;
			}
			else
			{
				loan_point=-1;
			}
		}
	}
}
void CAccount::Calc_shouhi_tax()
{
	int i;
	long long uriage=0;
	long long tax=0;

	for(i=0;i<int(mem_km.size());i++)
	{
		if(strcmp(mem_km[i]->kamoku,"売上額")==0)	uriage=mem_km[i]->zandaka;//karikata_total-mem_km[i]->kashikata_total;
	}

	tax=cta->Calc_shouhi_tax(uriage);
	
	at_km->touki_mibarai_shouhi_zei=tax;
	at_km->kimatu_mibarai_shouhi_zei=at_km->kisyu_mibarai_shouhi_zei+at_km->mibarai_shouhi_zei+at_km->touki_mibarai_shouhi_zei;

	
	//	printf("touki_mibarai %d\n",at_km->kimatu_mibarai_bonus);
	//利益の再修正
	at_km->zeimae_soneki=at_km->zeimae_soneki-at_km->touki_mibarai_shouhi_zei;



}
void CAccount::Calc_bonus()
{
	long long calc_bonus;
	long long ca_rieki=at_km->zeimae_soneki;
	long long loan=0;
	long long kisyu_riekizyouyo=0;
	long long minus_soneki=0;
	at_km->minus_soneki=0;

	kisyu_riekizyouyo=at_km->kisyu_rieki_zyouyo;

	if(at_km->zeimae_soneki>0)
	{
		
		if(kisyu_riekizyouyo<0)
		{
			if(-kisyu_riekizyouyo<at_km->zeimae_soneki)
			{
				at_km->minus_soneki=-kisyu_riekizyouyo;
				calc_bonus=long long((at_km->zeimae_soneki-at_km->minus_soneki)*cr->sdrand(cpara->GET_PARA_bonus_rate_min(),cpara->GET_PARA_bonus_rate_max()));
			}
			else	
			{
				calc_bonus=0;
				at_km->minus_soneki=at_km->zeimae_soneki;
			}
		}
		else	calc_bonus=long long((at_km->zeimae_soneki-at_km->minus_soneki)*cr->sdrand(cpara->GET_PARA_bonus_rate_min(),cpara->GET_PARA_bonus_rate_max()));//calc_bonus=at_km->zeimae_soneki*cpara->GET_PARA_bonus_rate_max();
		
	}
	else 	calc_bonus=0;

	at_km->touki_mibarai_bonus=calc_bonus;
	at_km->kimatu_mibarai_bonus=at_km->kisyu_mibarai_bonus+at_km->mibarai_bonus+at_km->touki_mibarai_bonus;
//		printf("kimatu_mibarai_bonus=%d, kisyu_mibarai_bonus=%d, touki_mibarai=%d, mibarai_bonus=%d\n",at_km->kimatu_mibarai_bonus,at_km->kisyu_mibarai_bonus,at_km->touki_mibarai_bonus,at_km->mibarai_bonus);
	//利益の再修正
	at_km->zeimae_soneki=at_km->zeimae_soneki-at_km->touki_mibarai_bonus;


}
void CAccount::Calculation_touki_soneki()
{
	int checker=0;
	if(agent_type==10)		//消費者エージェントの場合
	{
		at_km->touki_zyun_soneki=at_km->zeimae_soneki-at_km->kimatu_mibarai_zei;
	}
	else
	{

		if(at_km->touki_mibarai_zei>=0)
		{
			at_km->touki_zyun_soneki=at_km->zeimae_soneki-at_km->touki_mibarai_zei-at_km->touki_miabrai_housyu;
		}
		else
		{
			at_km->touki_zyun_soneki=at_km->zeimae_soneki;
		}		
	}

	at_km->rieki_zyouyo=at_km->touki_zyun_soneki;
	out_touki_zyouyo=at_km->rieki_zyouyo;
	at_km->kimatu_rieki_zyouyo=at_km->kisyu_rieki_zyouyo+at_km->rieki_zyouyo;
	
	out_data->touki_zyunsoneki=at_km->rieki_zyouyo;

	
}
void CAccount::kessan_housyu()
{
	at_km->kiamtu_mibarai_housyu=at_km->kisyu_mibarai_housyu+at_km->mibarai_housyu+at_km->touki_miabrai_housyu;
}
void CAccount::Calculation_tax()		//税金計算
{
	long long ca_rieki=at_km->zeimae_soneki-at_km->minus_soneki;	//計算用税前利益変数　zeimae_riekiはPLsheet_tableで計算済み
	long long kurikoshi_soneki=0;		//関数内、以前までの損益の使用変数
	long long zeimubun_rieki=0;	//関数内、支払い義務がある利益額用変数
	long long calctax	=0;			//計算した税金用変数
	int i;


	if(agent_type==10)		//消費者エージェントの場合
	{
		for(i=0;i<int(mem_km.size());i++)	if(strcmp(mem_km[i]->kamoku,"給与")==0)	zeimubun_rieki=mem_km[i]->zandaka;
		calctax+=cta->Calc_syotoku_tax(zeimubun_rieki);
//		at_km->touki_mibarai_zei=calctax;
		at_km->mibarai_zei+=calctax;		//ather_kamokuの未払税に値を入れる
		at_km->kimatu_mibarai_zei=at_km->kisyu_mibarai_zei+at_km->mibarai_zei;	//期末の未払税＝期首未払税＋今期未払税
	}
	else		//企業系エージェントの場合
	{
		//～～～～～～今期税金計算処理
//		printf("agentno=%d , zeimaesoneki=%d , ",Agent_no,ca_rieki);
		if(ca_rieki>0)		//税前利益が存在する場合
		{
			zeimubun_rieki=ca_rieki;

		}
		else		//税前利益がない場合
		{
			zeimubun_rieki=0;
		}
		calctax+=cta->Calc_houzin_tax(zeimubun_rieki);
//		printf("calctax=%d\n",calctax);
		
		at_km->touki_mibarai_zei=calctax;
		at_km->kimatu_mibarai_zei=at_km->kisyu_mibarai_zei+at_km->mibarai_zei+at_km->touki_mibarai_zei;	//期末の未払税＝期首未払税＋今期未払税

		out_data->touki_zeigo_rieki=at_km->zeimae_soneki-at_km->touki_mibarai_zei;
		//～～～～～～今期税金計算処理終了

	}




}


void CAccount::Set_yokin_suitoutyou(int i_period,char *tekiyou,char *tekiyou_aite,char *kamoku,long long amount,int code)
{
	//code=1:預金増加
	//code=2:預金減少
	int ent;
//	genyo_suitou=new struct genyokin_suitou;
	yokin_suitou=new struct suitoutyou;

	yokin_suitou->i_period=i_period;
	strcpy_s(yokin_suitou->tekiyou,_countof(yokin_suitou->tekiyou),tekiyou);
	strcpy_s(yokin_suitou->tekiyou_aite,_countof(yokin_suitou->tekiyou_aite),tekiyou_aite);
	strcpy_s(yokin_suitou->kamoku,_countof(yokin_suitou->kamoku),kamoku);
	yokin_suitou->code=code;

	
	switch(code)
	{
	case 1:
		yokin_suitou->kari=amount;
		yokin_suitou->zandaka=mem_yokin_suitou[mem_yokin_suitou.size()-1]->zandaka+amount;
		break;

	case 2:
		yokin_suitou->kashi=amount;
		yokin_suitou->zandaka=mem_yokin_suitou[mem_yokin_suitou.size()-1]->zandaka-amount;
		break;

		default:
		printf("error CAccount::Set_genkin_suitoutyou\n please key");
		scanf_s("%d",&ent);
	}

	mem_yokin_suitou.push_back(yokin_suitou);


}
void CAccount::Set_genkin_suitoutyou(int i_period,char *tekiyou,char *tekiyou_aite,char *kamoku,long long amount,int code)
{
	//code=1:現金増加
	//code=2:現金減少
	int ent;
	genkin_suitou=new struct suitoutyou;

	genkin_suitou->i_period=i_period;
	strcpy_s(genkin_suitou->tekiyou,_countof(genkin_suitou->tekiyou),tekiyou);
	strcpy_s(genkin_suitou->tekiyou_aite,_countof(genkin_suitou->tekiyou_aite),tekiyou_aite);
	strcpy_s(genkin_suitou->kamoku,_countof(genkin_suitou->kamoku),kamoku);
	genkin_suitou->code=code;
	
	switch(code)
	{
	case 1:
		genkin_suitou->kari=amount;
		genkin_suitou->zandaka=mem_genkin_suitou[mem_genkin_suitou.size()-1]->zandaka+amount;
		break;

	case 2:
		genkin_suitou->kashi=amount;
		genkin_suitou->zandaka=mem_genkin_suitou[mem_genkin_suitou.size()-1]->zandaka-amount;
		break;

	default:
		printf("error CAccount::Set_genkin_suitoutyou\n please key");
		scanf_s("%d",&ent);
	}

	mem_genkin_suitou.push_back(genkin_suitou);


}
void CAccount::Show_genyokin_suitou(FILE *suitoutyou,FILE *yokin)
{
	int i,code;

	for(i=0;i<int(mem_genkin_suitou.size());i++)
	{
		code=mem_genkin_suitou[i]->code;
		switch(code)
		{
		case 0://繰越
			fprintf(suitoutyou,"%d , %s ,  ,  ,  ,  , %d\n",mem_genkin_suitou[i]->i_period,mem_genkin_suitou[i]->tekiyou,mem_genkin_suitou[i]->zandaka);
			break;
		case 1://現金収入
			fprintf(suitoutyou,"%d , %s , %s , %s , %d ,  , %d\n",mem_genkin_suitou[i]->i_period,mem_genkin_suitou[i]->tekiyou,mem_genkin_suitou[i]->tekiyou_aite,mem_genkin_suitou[i]->kamoku,mem_genkin_suitou[i]->kari,mem_genkin_suitou[i]->zandaka);
			break;
	
		case 2://現金支出
			fprintf(suitoutyou,"%d , %s , %s , %s ,  , %d , %d\n",mem_genkin_suitou[i]->i_period,mem_genkin_suitou[i]->tekiyou,mem_genkin_suitou[i]->tekiyou_aite,mem_genkin_suitou[i]->kamoku,mem_genkin_suitou[i]->kashi,mem_genkin_suitou[i]->zandaka);
		break;
		}
	}
	for(i=0;i<int(mem_yokin_suitou.size());i++)
	{
		code=mem_yokin_suitou[i]->code;
		switch(code)
		{
		case 0://繰越
			fprintf(yokin,"%d , %s ,  ,  ,  ,  , %d \n",mem_yokin_suitou[i]->i_period,mem_yokin_suitou[i]->tekiyou,mem_yokin_suitou[i]->zandaka);
			break;
		case 1://現金収入
			fprintf(yokin,"%d , %s , %s , %s , %d ,  , %d\n",mem_yokin_suitou[i]->i_period,mem_yokin_suitou[i]->tekiyou,mem_yokin_suitou[i]->tekiyou_aite,mem_yokin_suitou[i]->kamoku,mem_yokin_suitou[i]->kari,mem_yokin_suitou[i]->zandaka);
			break;
	
		case 2://現金支出
			fprintf(yokin,"%d , %s , %s , %s ,  , %d , %d\n",mem_yokin_suitou[i]->i_period,mem_yokin_suitou[i]->tekiyou,mem_yokin_suitou[i]->tekiyou_aite,mem_yokin_suitou[i]->kamoku,mem_yokin_suitou[i]->kashi,mem_yokin_suitou[i]->zandaka);
		break;
		}
	}

//	printf("%d\n",mem_suitou.size());


}

void CAccount::Reset_genyokin_suitoutyou()
{
	int i;
	int next_period;
	long long zandaka;
	//現金出納帳繰越
	zandaka=mem_genkin_suitou[mem_genkin_suitou.size()-1]->zandaka;
	next_period=mem_genkin_suitou[mem_genkin_suitou.size()-1]->i_period+1;
//	printf("zandaka=%d\n",zandaka);

	i=mem_genkin_suitou.size()-1;
	while(mem_genkin_suitou.size()>0)
	{
//		printf("test , %d , %d\n",i,mem_genkin_suitou.size());
		genkin_suitou=mem_genkin_suitou[i];		//printf("utusikae size=%d\n",mem_genkin_suitou.size());
		mem_genkin_suitou.pop_back();			//printf("pop_back size=%d\n",mem_genkin_suitou.size());
		delete genkin_suitou;					//printf("delete size=%d\n",mem_genkin_suitou.size());
		i=i-1;
//		printf("test\n");		
	}

	genkin_suitou=new struct suitoutyou;
	genkin_suitou->i_period=next_period;
	strcpy_s(genkin_suitou->tekiyou,_countof(genkin_suitou->tekiyou),"繰越");
	strcpy_s(genkin_suitou->tekiyou_aite,_countof(genkin_suitou->tekiyou_aite)," ");
	strcpy_s(genkin_suitou->kamoku,_countof(genkin_suitou->kamoku)," ");
	genkin_suitou->code=0;
	genkin_suitou->zandaka=zandaka;

	mem_genkin_suitou.push_back(genkin_suitou);



	//預金出納帳繰越
	zandaka=0;
	zandaka=mem_yokin_suitou[mem_yokin_suitou.size()-1]->zandaka;
	next_period=mem_yokin_suitou[mem_yokin_suitou.size()-1]->i_period+1;

	i=mem_yokin_suitou.size()-1;
	while(mem_yokin_suitou.size()>0)
	{
//		printf("test , %d , %d\n",i,mem_genkin_suitou.size());
		yokin_suitou=mem_yokin_suitou[i];		//printf("utusikae size=%d\n",mem_genkin_suitou.size());
		mem_yokin_suitou.pop_back();			//printf("pop_back size=%d\n",mem_genkin_suitou.size());
		delete yokin_suitou;					//printf("delete size=%d\n",mem_genkin_suitou.size());
		i=i-1;
//		printf("test\n");		
	}

	yokin_suitou=new struct suitoutyou;
	yokin_suitou->i_period=next_period;
	strcpy_s(yokin_suitou->tekiyou,_countof(yokin_suitou->tekiyou),"繰越");
	strcpy_s(yokin_suitou->tekiyou_aite,_countof(yokin_suitou->tekiyou_aite)," ");
	strcpy_s(yokin_suitou->kamoku,_countof(yokin_suitou->kamoku)," ");
	yokin_suitou->code=0;
	yokin_suitou->zandaka=zandaka;

	mem_yokin_suitou.push_back(yokin_suitou);



}

int CAccount::Get_genka()
{
	int nkamoku;
	long long zaiko;
	int i;
	nkamoku=mem_km.size();
	zaiko=0;
	for(i=0;i<nkamoku;i++)
	{
		if(strcmp(mem_km[i]->kamoku,"原材料費")==0)
		{
			zaiko+=mem_km[i]->zandaka;
		}
	}
	return int(zaiko);
}


int CAccount::Get_zaiko()
{
	int nkamoku;
	long long zaiko;
	int i;
	nkamoku=mem_km.size();
	zaiko=0;
	for(i=0;i<nkamoku;i++)
	{
		if(strcmp(mem_km[i]->kamoku,"製品")==0)
		{
			zaiko=mem_km[i]->zandaka-zaiko_zandaka_t_1;
			zaiko_zandaka_t_1=mem_km[i]->zandaka;
		}
	}
	return int(zaiko);
}


int CAccount::Get_uriage_total()
{
	int nkamoku;
	long long uriage_total;
	int i;
	nkamoku=mem_km.size();
	uriage_total=0;
	for(i=0;i<nkamoku;i++)
	{
		if(mem_km[i]->code==3)
		{
			uriage_total+=mem_km[i]->zandaka;
		}
	}
	return int(uriage_total);
}
void CAccount::Set_kisyu_re()
{	//Createのときのみ使用される
	//kisyu_kimatuに数値なしの場合の滅茶苦茶な数値の返答阻止
	genkin_kisyu_zandaka=0;		chingin_kisyu_zandaka=0;		bank_risoku_u_kisyu_zandaka=0;
	yokin_kisyu_zandaka=0;		rounuhi_kisyu_zandaka=0;		genzairyo_kisyu_zandaka=0;
	loan_s_kisyu_zandaka=0;		bonus_kisyu_zandaka=0;			kyuyo_kisyu_zandaka=0;
	loan_l_kisyu_zandaka=0;		kanrihi_kisyu_zandaka=0;		loan_s_b_kisyu_zandaka=0;
	shihon_kisyu_zandaka=0;		uriage_genka_kisyu_zandaka=0;	loan_l_b_kisyu_zandaka=0;
	mibarai_kisyu_zandaka=0;	uriage_kisyu_zandaka=0;
	seihin_kisyu_zandaka=0;		syoukyaku_kisyu_zandaka=0;
	genryouhi_kisyu_zandaka=0;	kari_risoku_s_kisyu_zandaka=0;
	setubi_kisyu_zandaka=0;		kari_risoku_l_kisyu_zandaka=0;
	yokin_b_kisyu_zandaka=0;
	
}
void CAccount::Set_kimatu_re()
{	//Createのときのみ使用される
	genkin_kimatu_zandaka=0;	loan_s_b_kimatu_zandaka=0;
	yokin_kimatu_zandaka=0;		loan_l_b_kimatu_zandaka=0;
	loan_s_kimatu_zandaka=0;
	loan_l_kimatu_zandaka=0;
	shihon_kimatu_zandaka=0;
	mibarai_kimatu_zandaka=0;
	seihin_kimatu_zandaka=0;
	genryouhi_kimatu_zandaka=0;
	setubi_kimatu_zandaka=0;
	yokin_b_kisyu_zandaka=0;
}

void CAccount::Convert_kimatu_kisyu()
{
	
	int i;

	genkin_kisyu_zandaka=genkin_kimatu_zandaka;
	yokin_kisyu_zandaka=yokin_kimatu_zandaka;
	loan_s_kisyu_zandaka=loan_s_kimatu_zandaka;
	loan_l_kisyu_zandaka=loan_l_kimatu_zandaka;
	shihon_kisyu_zandaka=shihon_kimatu_zandaka;
	mibarai_kisyu_zandaka=mibarai_kimatu_zandaka;
	seihin_kisyu_zandaka=seihin_kimatu_zandaka;
	genryouhi_kisyu_zandaka=genryouhi_kimatu_zandaka;
	setubi_kisyu_zandaka=setubi_kimatu_zandaka;
	yokin_b_kisyu_zandaka=yokin_b_kimatu_zandaka;
	loan_s_b_kisyu_zandaka=loan_s_b_kimatu_zandaka;
	loan_l_b_kisyu_zandaka=loan_l_b_kimatu_zandaka;

//	printf("\n");
	for(i=0;i<int(mem_km.size());i++)
	{
		if(mem_km[i]->code==0||mem_km[i]->code==2)
		{
//			if(Agent_no==23)		fprintf(cpara->FI_Get_free_text(),"%s、期首:%d、期中:%d、期末:%d、",mem_km[i]->kamoku,mem_km[i]->kisyu_zandaka,mem_km[i]->zandaka,mem_km[i]->kimatu_zandaka);
//			printf("%s、期首:%d、期中:%d、期末:%d、",mem_km[i]->kamoku,mem_km[i]->kisyu_zandaka,mem_km[i]->zandaka,mem_km[i]->kimatu_zandaka);
			mem_km[i]->kisyu_zandaka=mem_km[i]->kimatu_zandaka;
//			printf("新期首:%d\n",mem_km[i]->kisyu_zandaka);
//			if(Agent_no==23)		fprintf(cpara->FI_Get_free_text(),"新期末:%d\n",mem_km[i]->kisyu_zandaka);
		}
		else
		{
//			if(Agent_no==23)		fprintf(cpara->FI_Get_free_text(),"%s、期首:%d、期中:%d、期末:%d、",mem_km[i]->kamoku,mem_km[i]->kisyu_zandaka,mem_km[i]->zandaka,mem_km[i]->kimatu_zandaka);
			mem_km[i]->kisyu_zandaka=0;
//	if(Agent_no==23)		fprintf(cpara->FI_Get_free_text(),"新期末:%d\n",mem_km[i]->kisyu_zandaka);
		}
	}

	at_km->kisyu_mibarai_zei=at_km->kimatu_mibarai_zei;
	at_km->kisyu_mibarai_housyu=at_km->kiamtu_mibarai_housyu;
	at_km->kisyu_mibarai_shouhi_zei=at_km->kimatu_mibarai_shouhi_zei;
	at_km->kisyu_mibarai_bonus=at_km->kimatu_mibarai_bonus;
	at_km->kisyu_rieki_zyouyo=at_km->kimatu_rieki_zyouyo;

	at_km->rieki_zyouyo=0;
	at_km->mibarai_zei=0;
	at_km->mibarai_housyu=0;
	at_km->mibarai_shouhi_zei=0;
	at_km->mibarai_bonus=0;

}
void CAccount::Set_kisyu_zandaka(int genkin,int yokin,int loan_s,int loan_l,int shihon,int mibarai,int seihin,int genryouhi,int setubi)
{	//Createのときのみ使用される
	shihon_kisyu_zandaka=shihon;//資本金
}
void CAccount::Set_kisyu_zandaka_l(long long genkin,int yokin,int loan_s,int loan_l,long long shihon,int mibarai,int seihin,int genryouhi,int setubi)
{	//Createのときのみ使用される
	shihon_kisyu_zandaka=shihon;//資本金
}
void CAccount::Get_kimatu_zandaka(int *genkin,int *yokin,int *loan_s,int *loan_l,int *shihon,int *mibarai,int *seihin,int *genryouhi,int *setubi)
{
	*genkin=int(genkin_kimatu_zandaka);
	*yokin=int(yokin_kimatu_zandaka);
	*loan_s=int(loan_s_kimatu_zandaka);
	*loan_l=int(loan_l_kimatu_zandaka);
	*shihon=int(shihon_kimatu_zandaka);
	*mibarai=int(mibarai_kimatu_zandaka);
	*seihin=int(seihin_kimatu_zandaka);
	*genryouhi=int(genryouhi_kimatu_zandaka);
	*setubi=int(setubi_kimatu_zandaka);
//	printf("gen=%d yo=%d los=%d lol=%d\n",genkin_kimatu_zandaka,yokin_kimatu_zandaka,loan_s_kisyu_zandaka,loan_l_kisyu_zandaka);
}

void CAccount::Print_kamoku()
{
	int i;
	fprintf(cpara->FI_Get_out3(),"資産科目：\n");
	for(i=0;i<int(mem_shisan_km.size());i++){
		fprintf(cpara->FI_Get_out3(),"test %s ",Get_shisan_km(i)->kamoku);fprintf(cpara->FI_Get_out3(),"\n"); 
	}
	fprintf(cpara->FI_Get_out3(),"経費科目：\n");
	for(i=0;i<int(mem_keihi_km.size());i++){
		fprintf(cpara->FI_Get_out3()," %s ",Get_keihi_km(i)->kamoku);fprintf(cpara->FI_Get_out3(),"\n"); 
	}
	fprintf(cpara->FI_Get_out3(),"負債科目：\n");
	for(i=0;i<int(mem_husai_km.size());i++){
		fprintf(cpara->FI_Get_out3()," %s ",Get_husai_km(i)->kamoku);fprintf(cpara->FI_Get_out3(),"\n"); 
	}
	fprintf(cpara->FI_Get_out3(),"売上科目：\n");
	for(i=0;i<int(mem_uriage_km.size());i++){
		fprintf(cpara->FI_Get_out3()," %s ",Get_uriage_km(i)->kamoku);fprintf(cpara->FI_Get_out3(),"\n"); 
	}
}
void CAccount::Set_shiwake(int i_period,int kari,char *karikata,char *tekiyo,char *kashikata,int kashi,int kari_code,int kashi_code)
{
	int size;
	size=mem_sh.size();
	sh=new struct shiwake;
	mem_sh.push_back(sh);
	strcpy_s(mem_sh[size]->karikata,_countof(mem_sh[size]->karikata),karikata);
	strcpy_s(mem_sh[size]->kashikata,_countof(mem_sh[size]->kashikata),kashikata);
	strcpy_s(mem_sh[size]->tekiyo,_countof(mem_sh[size]->tekiyo),tekiyo);
	mem_sh[size]->kari=long long(kari);
	mem_sh[size]->kashi=long long(kashi);
	mem_sh[size]->kari_code=kari_code;
	mem_sh[size]->kashi_code=kashi_code;
	Check_km(karikata,kari_code);
	Check_km(kashikata,kashi_code);


	//現金預金出納帳管理

	//仕分け関数内で使用することを強制されたため、摘要の相手が記述不能、
	//必要になった場合に備えて関数、構造体は維持をしてスペースを入力することとする
	if(strcmp(karikata,"現金")==0)	Set_genkin_suitoutyou(i_period,tekiyo," ",karikata,kari,1);
	else if(strcmp(karikata,"預金")==0)	Set_yokin_suitoutyou(i_period,tekiyo," ",karikata,kari,1);
	if(strcmp(kashikata,"現金")==0) Set_genkin_suitoutyou(i_period,tekiyo," ",kashikata,kashi,2);
	else if(strcmp(kashikata,"預金")==0) Set_yokin_suitoutyou(i_period,tekiyo," ",kashikata,kashi,2);

}
template<class T,class U> void CAccount::Set_shiwake_T(const T&i_period,const U&kari,char *karikata,char *tekiyo,char *kashikata,const U&kashi,const T&kari_code,const T&kashi_code)
{
	int size;
	size=mem_sh.size();
	sh=new struct shiwake;
	mem_sh.push_back(sh);
	strcpy_s(mem_sh[size]->karikata,_countof(mem_sh[size]->karikata),karikata);
	strcpy_s(mem_sh[size]->kashikata,_countof(mem_sh[size]->kashikata),kashikata);
	strcpy_s(mem_sh[size]->tekiyo,_countof(mem_sh[size]->tekiyo),tekiyo);
	mem_sh[size]->kari=kari;
	mem_sh[size]->kashi=kashi;
	mem_sh[size]->kari_code=kari_code;
	mem_sh[size]->kashi_code=kashi_code;
	Check_km(karikata,kari_code);
	Check_km(kashikata,kashi_code);

	//現金預金出納帳管理
	//仕分け関数内で使用することを強制されたため、摘要の相手が記述不能、
	//必要になった場合に備えて関数、構造体は維持をしてスペースを入力することとする
	if(strcmp(karikata,"現金")==0)	Set_genkin_suitoutyou(i_period,tekiyo," ",karikata,kari,1);
	else if(strcmp(karikata,"預金")==0)	Set_yokin_suitoutyou(i_period,tekiyo," ",karikata,kari,1);
	if(strcmp(kashikata,"現金")==0) Set_genkin_suitoutyou(i_period,tekiyo," ",kashikata,kashi,2);
	else if(strcmp(kashikata,"預金")==0) Set_yokin_suitoutyou(i_period,tekiyo," ",kashikata,kashi,2);
}
void CAccount::Check_km(char *kamoku,int code)
{
	int size;int i;
	int np;
	if(code==0)//資産科目
	{
		size=mem_shisan_km.size();
		if(size==0){
			shisan_km=new struct shisan_kamoku;
			mem_shisan_km.push_back(shisan_km);
			strcpy_s(mem_shisan_km[size]->kamoku,_countof(mem_shisan_km[size]->kamoku),kamoku);
	//		fprintf(out3,"inside check_km mem_shisan_km[%d]=%s \n",size,mem_shisan_km[size]);
		}
		else{
			np=0;
			for(i=0;i<size;i++){
				if(strcmp(kamoku,Get_shisan_km(i)->kamoku)==0){np=1;break;}
			}
			if(np==0){
				shisan_km=new struct shisan_kamoku;
				mem_shisan_km.push_back(shisan_km);
				strcpy_s(mem_shisan_km[size]->kamoku,_countof(mem_shisan_km[size]->kamoku),kamoku);
	//			fprintf(out3,"inside check_km mem_shisan_km[%d]=%s \n",size,mem_shisan_km[size]);	
			}
		}
	}
	else if(code==1)//経費科目
	{
		size=mem_keihi_km.size();
		if(size==0){
			keihi_km=new struct keihi_kamoku;
			mem_keihi_km.push_back(keihi_km);
			strcpy_s(mem_keihi_km[size]->kamoku,_countof(mem_keihi_km[size]->kamoku),kamoku);
	//		printf("inside check_km mem_keihi_km[%d]=%s \n",size,mem_keihi_km[size]);
	//		fprintf(out3,"inside check_km mem_keihi_km[%d]=%s \n",size,mem_keihi_km[size]);
		}
		else{
			np=0;
			for(i=0;i<size;i++){
				if(strcmp(kamoku,Get_keihi_km(i)->kamoku)==0){np=1;break;}
			}
			if(np==0){
				keihi_km=new struct keihi_kamoku;
				mem_keihi_km.push_back(keihi_km);
				strcpy_s(mem_keihi_km[size]->kamoku,_countof(mem_keihi_km[size]->kamoku),kamoku);
	//			fprintf(out3,"inside check_km mem_keihi_km[%d]=%s \n",size,mem_keihi_km[size]);
			}
		}
	}
	else if(code==2)//負債科目
	{
		size=mem_husai_km.size();
		if(size==0){
			husai_km=new struct husai_kamoku;
			mem_husai_km.push_back(husai_km);
			strcpy_s(mem_husai_km[size]->kamoku,_countof(mem_husai_km[size]->kamoku),kamoku);
	//		fprintf(out3,"inside check_km mem_husai_km[%d]=%s \n",size,mem_husai_km[size]);
		}
		else{
			np=0;
			for(i=0;i<size;i++){
				if(strcmp(kamoku,Get_husai_km(i)->kamoku)==0){np=1;break;}
			}
			if(np==0){
				husai_km=new struct husai_kamoku;
				mem_husai_km.push_back(husai_km);
				strcpy_s(mem_husai_km[size]->kamoku,_countof(mem_husai_km[size]->kamoku),kamoku);
	//			fprintf(out3,"inside check_km mem_husai_km[%d]=%s \n",size,mem_husai_km[size]);
			}
		}
	}
	else if(code==3) //売上科目
	{
		size=mem_uriage_km.size();
		if(size==0){
			uriage_km=new struct uriage_kamoku;
			mem_uriage_km.push_back(uriage_km);
			strcpy_s(mem_uriage_km[size]->kamoku,_countof(mem_uriage_km[size]->kamoku),kamoku);
	//		fprintf(out3,"inside check_km mem_uriage_km[%d]=%s \n",size,mem_uriage_km[size]);
		}
		else{
			np=0;
			for(i=0;i<size;i++){
				if(strcmp(kamoku,Get_uriage_km(i)->kamoku)==0){np=1;break;}
			}
			if(np==0){
				uriage_km=new struct uriage_kamoku;
				mem_uriage_km.push_back(uriage_km);
				strcpy_s(mem_uriage_km[size]->kamoku,_countof(mem_uriage_km[size]->kamoku),kamoku);
	//			fprintf(out3,"inside check_km mem_uriage_km[%d]=%s \n",size,mem_uriage_km[size]);
			}
		}
	}
	else printf("code異常です\n");
}
void CAccount::Define_km()	//勘定科目mem_km作成場所、ここ以外ではmem_kmにpush.backをしない
{
	int size,size_km;
	size=mem_sh.size();
	int i,j,np;
	//借方勘定科目をmem_kmにいれる
	for(i=0;i<size;i++){
		size_km=mem_km.size();
		if(size_km==0){					//科目が一つもない場合に作成する
			km=new struct kanjyo_kamoku;
			km->kisyu_zandaka=0;
			km->kimatu_zandaka=0;
			mem_km.push_back(km);
			strcpy_s(mem_km[size_km]->kamoku,_countof(mem_km[size_km]->kamoku),mem_sh[i]->karikata);
			Set_km_code(size_km,mem_sh[i]->kari_code);
//			printf("kamoku=%s karikata=%s c=%d\n",mem_km[size_km]->kamoku,mem_sh[i]->karikata,mem_sh[i]->kari_code);
		}
		else{				//科目が１つでもある場合はこちらを実行
			np=0;
			for(j=0;j<size_km;j++){			//現在ある科目と仕訳帳を比較し、存在しない科目がある場合は新規に作成
				if(strcmp(mem_sh[i]->karikata,Get_km(j)->kamoku)==0){np=1;break;}
			}
			if(np==0){
				km=new struct kanjyo_kamoku;
				km->kisyu_zandaka=0;
				km->kimatu_zandaka=0;
				mem_km.push_back(km);
				strcpy_s(mem_km[size_km]->kamoku,_countof(mem_km[size_km]->kamoku),mem_sh[i]->karikata);
				Set_km_code(size_km,mem_sh[i]->kari_code);
//				printf("kamoku=%s karikata=%s c=%d\n",mem_km[size_km]->kamoku,mem_sh[i]->karikata,mem_sh[i]->kari_code);
			}
		}//elseの終わり

	}
	//貸方勘定科目をmem_kmにいれる
	for(i=0;i<size;i++){
		size_km=mem_km.size();
		if(size_km==0){
			km=new struct kanjyo_kamoku;
			km->kisyu_zandaka=0;
			km->kimatu_zandaka=0;
			mem_km.push_back(km);
			strcpy_s(mem_km[size_km]->kamoku,_countof(mem_km[size_km]->kamoku),mem_sh[i]->kashikata);
			Set_km_code(size_km,mem_sh[i]->kashi_code);
//			printf("kamoku=%s kashikata=%s c=%d\n",mem_km[size_km]->kamoku,mem_sh[i]->kashikata,mem_sh[i]->kashi_code);
		}
		else{
			np=0;
			for(j=0;j<size_km;j++){
				if(strcmp(mem_sh[i]->kashikata,Get_km(j)->kamoku)==0){np=1;break;}
			}
			if(np==0){
				km=new struct kanjyo_kamoku;
				km->kisyu_zandaka=0;
				km->kimatu_zandaka=0;
				mem_km.push_back(km);
				strcpy_s(mem_km[size_km]->kamoku,_countof(mem_km[size_km]->kamoku),mem_sh[i]->kashikata);
				Set_km_code(size_km,mem_sh[i]->kashi_code);
//				printf("kamoku=%s kashikata=%s c=%d\n",mem_km[size_km]->kamoku,mem_sh[i]->kashikata,mem_sh[i]->kashi_code);
			}
		}//elseの終わり
	}
}

void CAccount::Set_ndata(int ndata1)
{
	ndata=ndata1;
}
void CAccount::Re_define_km()
{

	int i,j;
	int p=0,p0=0;//int np;
	int nshisan,nhusai,nuriage,nkeihi;
	nshisan=0;nhusai=0;nuriage=0;nkeihi=0;
	p=0;p0=0;
	
	nkamoku=mem_km.size();
	//資産科目の定義--------------------  
	for(i=0;i<nkamoku;i++){
		if(Get_km(i)->code==0) nshisan++;
	}
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"nshisan_kamoku=%d ",nshisan);
	for(j=0;j<nshisan;j++){
		for(i=0;i<nkamoku;i++){
			if(strcmp(Get_km(i)->kamoku,Get_shisan_km(j)->kamoku)==0)
			{
				kmr=new struct kanjyo_kamoku;
				mem_kmr.push_back(kmr);
				Set_kmr_kamoku(p,Get_km(i)->kamoku);
				Set_kmr_code(p,Get_km_code(i));
				p++;
			}
		}
	}
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"資産科目数=%d p=%d ",nshisan,p-p0);
	for(i=0;i<p-p0;i++) if(nkessan==0) fprintf(cpara->FI_Get_out3()," %s ",Get_kmr(i)->kamoku);
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"\n"); 
	p0=p;

	//負債科目の定義-----------------
	for(i=0;i<nkamoku;i++){
//		printf("%s\n",mem_km[i]->kamoku);
		if(Get_km(i)->code==2) nhusai++;
	}
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"nhusai_kamoku=%d ",nhusai);
	for(j=0;j<nhusai;j++){
		for(i=0;i<nkamoku;i++){//printf("ac %d %s,%d\n",i,Get_km(i),j);
			if(strcmp(Get_km(i)->kamoku,Get_husai_km(j)->kamoku)==0)
			{//printf("aac %d,%d\n",i,j);
				kmr=new struct kanjyo_kamoku;
				mem_kmr.push_back(kmr);
				Set_kmr_kamoku(p,Get_km(i)->kamoku);
				Set_kmr_code(p,Get_km_code(i));
				p++;
			}
		}
	}

	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"負債科目数=%d p=%d ",nhusai,p-p0);
	for(i=p0;i<p;i++) if(nkessan==0) fprintf(cpara->FI_Get_out3()," %s ",Get_kmr(i)->kamoku);
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"\n"); 
	p0=p;
	//売上科目の定義--------------------
	for(i=0;i<nkamoku;i++){
		if(Get_km(i)->code==3) nuriage++;
	}
//	printf("nuriage_kamoku=%d ",nuriage);
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"nuriage_kamoku=%d ",nuriage);
	for(j=0;j<nuriage;j++){
		for(i=0;i<nkamoku;i++){
			if(strcmp(Get_km(i)->kamoku,Get_uriage_km(j)->kamoku)==0)
			{
				kmr=new struct kanjyo_kamoku;
				mem_kmr.push_back(kmr);
				Set_kmr_kamoku(p,Get_km(i)->kamoku);
				Set_kmr_code(p,Get_km_code(i));
				p++;
			}
		}
	}

	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"売上科目数=%d p=%d ",nuriage,p-p0);
//	printf("売上科目数=%d p=%d \n",nuriage,p-p0);
	for(i=p0;i<p;i++) if(nkessan==0) fprintf(cpara->FI_Get_out3()," %s ",Get_kmr(i)->kamoku);
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"\n"); 
	p0=p;

	//経費科目の再定義--------------------
	for(i=0;i<nkamoku;i++){
		if(Get_km(i)->code==1) nkeihi++;
	}
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"nkeihi_kamoku=%d ",nkeihi);
	for(j=0;j<nkeihi;j++){
		for(i=0;i<nkamoku;i++){
			if(strcmp(Get_km(i)->kamoku,Get_keihi_km(j)->kamoku)==0)
			{
				kmr=new struct kanjyo_kamoku;
				mem_kmr.push_back(kmr);
				Set_kmr_kamoku(p,Get_km(i)->kamoku);
				Set_kmr_code(p,Get_km_code(i));
				p++;
			}
		}
	}
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"経費科目数=%d p=%d \n",nkeihi,p-p0);
	for(i=p0;i<p;i++) if(nkessan==0) fprintf(cpara->FI_Get_out3()," %s ",Get_kmr(i)->kamoku);
	if(nkessan==0) fprintf(cpara->FI_Get_out3(),"\n"); 
	//kmrの確認
	for(i=0;i<nkamoku;i++){
		if(nkessan==0) fprintf(cpara->FI_Get_out3(),"km[%3d] %20s  code=%3d  kmr[%3d] %20s code=%3d\n",i,Get_km(i)->kamoku,Get_km_code(i),i,Get_kmr(i)->kamoku,Get_kmr_code(i));
	}
	for(i=0;i<nkamoku;i++){//printf("checckeraaaa  %s、期首:%d、期中:%d、期末:%d\n",mem_km[i]->kamoku,mem_km[i]->kisyu_zandaka,mem_km[i]->zandaka,mem_km[i]->kimatu_zandaka);
		Set_km_kamoku(i,Get_kmr(i)->kamoku);
		Set_km_code(i,Get_kmr_code(i));
		//printf("checckeraaaa  %s、期首:%d、期中:%d、期末:%d\n",mem_km[i]->kamoku,mem_km[i]->kisyu_zandaka,mem_km[i]->zandaka,mem_km[i]->kimatu_zandaka);
	}
	for(i=0;i<nkamoku;i++){
//		printf("km[%3d] %20s  code=%3d  kmr[%3d] %20s code=%3d\n",i,Get_km(i)->kamoku,Get_km_code(i),i,Get_kmr(i)->kamoku,Get_kmr_code(i));
	}

}
int CAccount::strcmp(char *s1,char *s2)
{
	int i=0,p=0;
	while(s1[i]){  //s1[i]がNULLになるまで繰り返す
		if(s1[i]==s2[i]) p++;
		i++;
	}
	if(p==i) return 0;//文字列s1と文字列s2が同じであれば0を返す
	else return 1;
}

void CAccount::Shisan_table(int i_period,int ncase,FILE *out3,FILE *out3_csv)
{

	//ncase=0;//printed out
	//ncase=1;//total only printed out
	//ncase=2;//not printed out

	int i,j;
	long long kari_total=0,kashi_total=0;
	long long zandaka=0;
	int pp=0;
	ndata=mem_sh.size();
	if(ncase==0) fprintf(out3,"ndata=%d nkamoku=%d \n",ndata,nkamoku);
//	printf("ndata=%d nkamoku=%d \n",ndata,nkamoku);
	for(j=0;j<nkamoku;j++){		
	//---------
			//期首残高(前期繰越金）の設定

		if(mem_km[j]->code==0){
			if(strcmp(mem_km[j]->kamoku,"現金")==0){ 
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"預金")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"設備")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"原料")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"製品")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"低額固定資本形成")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"短期貸出金")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"長期貸出金")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
		}
		else if(mem_km[j]->code==2){
			if(strcmp(mem_km[j]->kamoku,"短期借入金")==0) {
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"長期借入金")==0){
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"預金_Bank")==0) {
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"株主資本")==0) {
				if(i_period==0){
					mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
				}
				else{
					mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
				}
			}
			else if(strcmp(mem_km[j]->kamoku,"未払費用")==0) {
				mem_km[j]->zandaka=mem_km[j]->kisyu_zandaka;
			}
		}
		else{
			mem_km[j]->kisyu_zandaka=0;
			mem_km[j]->zandaka=0;
		}
//-----------------------------------期首残高(前期繰越金）の設定終了
	}//for(j=0;...の終わり

	
	//総勘定元帳の計算
	for(j=0;j<nkamoku;j++)
	{
		zandaka=Get_km_zandaka(j);
		pp=0;
		mem_km[j]->karikata_total=0;
		mem_km[j]->kashikata_total=0;
		if(ncase==0 ){
			fprintf(out3,"\n");
			fprintf(out3,"          -------------------------------\n");
			fprintf(out3,"                     %s \n",mem_km[j]->kamoku);
			fprintf(out3,"          -------------------------------\n");
			fprintf(out3,"               相手科目　                              　　  　借方　　　　貸方        残高\n");
			fprintf(out3_csv,"\n");
			fprintf(out3_csv,"   ,     ,  -------------------------------,\n");
			fprintf(out3_csv,"   ,     ,               %s          ,\n",mem_km[j]->kamoku);
			fprintf(out3_csv,"    ,    ,  -------------------------------,\n");
			fprintf(out3_csv,"          ,     相手科目　,                              　　  ,　借方　,　　　貸方    ,    残高\n");
		}

		
		for(i=0;i<ndata;i++)
		{

			if(i==0) 
			{
				if(Get_km_code(j)==0)
				{
					if(ncase==0)
					{
						fprintf(out3,"           　　　 　　　　　　　　　　前期繰越　　　　　　　%10lld    　　 　　　　%10lld\n",Get_km_zandaka(j),Get_km_zandaka(j));
						fprintf(out3_csv,"       ,　　　,　　g前期繰越,　　%10lld ,  　,%10lld\n",Get_km_zandaka(j),Get_km_zandaka(j));
					}
				}
				else if( Get_km_code(j)==2)
				{
					if(ncase==0)
					{
						fprintf(out3,"         　　　　  　　　 　　　　　　前期繰越 　　　 　　　　　　　　  %10lld     %10lld\n",Get_km_zandaka(j),Get_km_zandaka(j));
						fprintf(out3_csv,"  　,　　　,　g前期繰越 ,  ,%10lld,     %10lld\n",Get_km_zandaka(j),Get_km_zandaka(j));
					}
				}	
			}//if(i==0の終わり
			if(strcmp(mem_sh[i]->karikata,mem_km[j]->kamoku)==0 && strcmp(mem_km[j]->kamoku,mem_sh[i]->karikata)==0)
			{
				if(mem_km[j]->code==0 || mem_km[j]->code==1) {
					mem_km[j]->zandaka+=mem_sh[i]->kari;
				}
				else {
					mem_km[j]->zandaka-=mem_sh[i]->kari;
				}
				if(ncase==0){
					fprintf(out3,"%12d %12s %30s  %10d           %10d\n",i_period,mem_sh[i]->kashikata,mem_sh[i]->tekiyo,mem_sh[i]->kari,mem_km[j]->zandaka);
					fprintf(out3_csv,"%12d, %12s, %30s,  %10d,           ,%10d\n",i_period,mem_sh[i]->kashikata,mem_sh[i]->tekiyo,mem_sh[i]->kari,mem_km[j]->zandaka);
				}
				mem_km[j]->karikata_total+=mem_sh[i]->kari;
				

			}
			else if(strcmp(mem_sh[i]->kashikata,mem_km[j]->kamoku)==0 && strcmp(mem_km[j]->kamoku,mem_sh[i]->kashikata)==0)
			{
				if(mem_km[j]->code==0 || mem_km[j]->code==1) mem_km[j]->zandaka-=mem_sh[i]->kashi;
				else mem_km[j]->zandaka+=mem_sh[i]->kashi;
				if(ncase==0){
					fprintf(out3,"%12d %12s %30s           %10d  %10d \n",i_period,mem_sh[i]->karikata,mem_sh[i]->tekiyo,mem_sh[i]->kashi,mem_km[j]->zandaka);
					fprintf(out3_csv,"%12d, %12s, %30s,           ,%10d,  %10d\n",i_period,mem_sh[i]->karikata,mem_sh[i]->tekiyo,mem_sh[i]->kashi,mem_km[j]->zandaka);
				}
				mem_km[j]->kashikata_total+=long long(mem_sh[i]->kashi);
				

			}
			

		}//for(i=0;...の終わり
		if(ncase==0){
			fprintf(out3,"            ----------------------------------------\n");
			fprintf(out3,"                合計                                        %8d  %8d\n",mem_km[j]->karikata_total,mem_km[j]->kashikata_total);
			fprintf(out3_csv,"            ,----------------------------------------\n");
			fprintf(out3_csv,"            ,    合計  ,        ,  %8lld , %8lld\n",mem_km[j]->karikata_total,mem_km[j]->kashikata_total);
		}

	
	if(strcmp(mem_km[j]->kamoku,"原料")==0) genryou_out=mem_km[j]->karikata_total;	
	if(strcmp(mem_km[j]->kamoku,"労務費")==0) kyuyo_out=mem_km[j]->karikata_total;
	if(strcmp(mem_km[j]->kamoku,"賃金")==0) kyuyo_out=mem_km[j]->karikata_total;
	if(strcmp(mem_km[j]->kamoku,"ボーナス給")==0) bonus_out=mem_km[j]->karikata_total;
	if(strcmp(mem_km[j]->kamoku,"給与")==0) kyuyo_c_out=mem_km[j]->kashikata_total;	
	if(strcmp(mem_km[j]->kamoku,"優遇交付金")==0) kouhukin_out=mem_km[j]->kashikata_total;
	if(strcmp(mem_km[j]->kamoku,"企業補助金")==0) out_data->kigyou_hozyokin_g=mem_km[j]->kashikata_total;
	if(strcmp(mem_km[j]->kamoku,"消耗品")==0) syoumouhin_out=mem_km[j]->karikata_total;
	if(strcmp(mem_km[j]->kamoku,"リテイラー製品")==0)buy_retailer_product_out=mem_km[j]->karikata_total;
	}//for(j=0;...の終わり

	if(ncase==0 || ncase==1){
		fprintf(out3_csv,"agent_type=%d    agent_no=%d\n",agent_type,Agent_no);
		fprintf(out3,"\n");
		fprintf(out3,"           勘定科目　  コード　 　借方　  　貸方\n");
		fprintf(out3_csv,"\n");
		fprintf(out3_csv,"    ,      , 勘定科目　, 　借方　,  　貸方\n");
	}
	for(j=0;j<nkamoku;j++)
	{
		if(ncase==0 || ncase==1){
			fprintf(out3," %20s %4d      %8d  %8d \n",mem_km[j]->kamoku,mem_km[j]->code,mem_km[j]->karikata_total,mem_km[j]->kashikata_total);
			fprintf(out3_csv," ,  ,%20s,  %8lld , %8lld\n",mem_km[j]->kamoku,mem_km[j]->karikata_total,mem_km[j]->kashikata_total);
		}
		kari_total+=mem_km[j]->karikata_total;
		kashi_total+=mem_km[j]->kashikata_total;
	}

		if(ncase==0 || ncase==1){
			fprintf(out3," 役員報酬	         %8lld \n",at_km->mibarai_housyu);
			fprintf(out3_csv," ,  ,役員報酬,   , %8lld\n",at_km->mibarai_housyu);
			fprintf(out3," 消費税	         %8lld \n",at_km->mibarai_shouhi_zei);
			fprintf(out3_csv," ,  ,消費税,   , %8lld\n",at_km->mibarai_shouhi_zei);
			fprintf(out3," 法人税	         %8lld \n",at_km->mibarai_zei);
			fprintf(out3_csv," ,  ,法人税,   , %8lld\n",at_km->mibarai_zei);
			fprintf(out3," ボーナス	         %8d \n",at_km->mibarai_bonus);
			fprintf(out3_csv," ,  ,ボーナス,   , %8lld\n",at_km->mibarai_bonus);
		}
		kashi_total+=at_km->mibarai_zei+at_km->mibarai_shouhi_zei+at_km->mibarai_housyu;
		kashi_total+=at_km->mibarai_bonus;

	if(ncase==0 || ncase==1){
		fprintf(out3,"            ----------------------------------------\n");
		fprintf(out3,"            合計                %8d  %8d\n",kari_total,kashi_total);
		fprintf(out3_csv,"    ,        ,----------------------------------------\n");
		fprintf(out3_csv,"    ,   ,     合計      ,   %8lld , %8lld\n",kari_total,kashi_total);
		fprintf(out3,"\n");
		fprintf(out3_csv,"\n");
	}


	for(j=0;j<nkamoku;j++)
	{
		//期末残高(次期繰越金）の設定
		if(mem_km[j]->code==0){
			if(strcmp(mem_km[j]->kamoku,"現金")==0){ 
				genkin_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"預金")==0){
				yokin_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"設備")==0){
				setubi_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"原料")==0){
				genryouhi_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"製品")==0){
				seihin_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"短期貸出金")==0){
				loan_s_b_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"長期貸出金")==0){
				loan_l_b_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else
			{
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
		}
		else if(mem_km[j]->code==2){
			if(strcmp(mem_km[j]->kamoku,"短期借入金")==0) {
				loan_s_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"長期借入金")==0) {
				loan_l_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"預金_Bank")==0) {
				yokin_b_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"株主資本")==0) {
				shihon_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else if(strcmp(mem_km[j]->kamoku,"未払費用")==0) {
				mibarai_kimatu_zandaka=mem_km[j]->zandaka;
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
			else
			{
				mem_km[j]->kimatu_zandaka=mem_km[j]->zandaka;
			}
		}
	}//for(j=0;...の終わり
}
void CAccount::Show_kimatu_zandaka(int x,FILE *out3)
{
	//x=0;//not bank
	//x=1;//bank
	shihon_kimatu_zandaka=shihon_kisyu_zandaka+rieki;
	if(shihon_kimatu_zandaka<0) shihon_kimatu_zandaka=0;

	if(nkessan==0 || nkessan==1){
		fprintf(out3,"期末残高　現金=%d　預金=%d　短期借入金=%d　長期借入金=%d　株主資本=%d 製品=%d 原料=%d 設備=%d 未払費用=%d\n",genkin_kimatu_zandaka,yokin_kimatu_zandaka,loan_s_kimatu_zandaka,loan_l_kimatu_zandaka,shihon_kimatu_zandaka,seihin_kimatu_zandaka,genryouhi_kimatu_zandaka,setubi_kimatu_zandaka,mibarai_kimatu_zandaka);
		if(x==1)  fprintf(out3,"          預金_Bank=%d 短期借入金=%d　長期借入金=%d\n",yokin_b_kimatu_zandaka,loan_s_b_kimatu_zandaka,loan_l_b_kimatu_zandaka);
		fprintf(out3,"\n");
	}

}
void CAccount::Show_kisyu_zandaka(int x,FILE *out3)
{
	//x=0;//not bank
	//x=1;//bank
	if(nkessan==0 || nkessan==1){
		fprintf(out3,"期首残高　現金=%d　預金=%d　短期借入金=%d　長期借入金=%d　株主資本=%d 製品=%d 原料=%d 設備=%d 未払費用=%d\n",genkin_kisyu_zandaka,yokin_kisyu_zandaka,loan_s_kisyu_zandaka,loan_l_kisyu_zandaka,shihon_kisyu_zandaka,seihin_kisyu_zandaka,genryouhi_kisyu_zandaka,setubi_kisyu_zandaka,mibarai_kisyu_zandaka);
		if(x==1) fprintf(out3,"          預金_Bank=%d 短期借入金=%d　長期借入金=%d\n",yokin_b_kisyu_zandaka,loan_s_b_kisyu_zandaka,loan_l_b_kisyu_zandaka);
		fprintf(out3,"\n");
	}
}

void CAccount::PLsheet_table(FILE *out3,FILE *out3_csv)
{
	int j;
	long long kari_total=0,kashi_total=0;
	int nkamoku=mem_km.size();
	
	//収入科目の記載
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==3)
		{
			kashi_total+=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			if(strcmp(mem_km[j]->kamoku,"売上額")==0) uriage_out=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			if(strcmp(mem_km[j]->kamoku,"受取利息")==0) ukerisi_out=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			if(strcmp(mem_km[j]->kamoku,"補助金")==0) hozyokin_out=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
		}
	}
	//経費科目の記載
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==1)
		{
			kari_total+=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(strcmp(mem_km[j]->kamoku,"減価償却費")==0) genkasyoukyaku_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(strcmp(mem_km[j]->kamoku,"支払利息")==0) siharisi_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(strcmp(mem_km[j]->kamoku,"企業補助金")==0)kigyou_hozyokin_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(strcmp(mem_km[j]->kamoku,"法人税")==0) houzin_zei_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(strcmp(mem_km[j]->kamoku,"役員報酬")==0) yakuin_housyu_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
		}
	}
	
	rieki=kashi_total-kari_total;
	pl_rieki=kashi_total-kari_total;
	at_km->zeimae_soneki=kashi_total-kari_total;
	//if(Agent_no==7) 	printf("rieki %d\n",rieki);


}
void CAccount::Balance_table(FILE *out3,FILE *out3_csv)
{
	int j;
	long long kari_total=0,kashi_total=0;
	long long kari_kashi=0,kashi_kari=0;
	int nkamoku=mem_km.size();
	int dumy;	//エラーコード時のscanf待機用関数

	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==0)
		{
			kari_kashi=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			kari_total+=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(strcmp(mem_km[j]->kamoku,"製品")==0) zaiko_out=kari_kashi;
			if(strcmp(mem_km[j]->kamoku,"設備")==0) setubi_out=mem_km[j]->karikata_total;
		}
		if(mem_km[j]->code==2)
		{
			kashi_kari=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			kashi_total+=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
		}

	}


	kashi_total+=at_km->mibarai_zei+at_km->mibarai_shouhi_zei;
	kashi_total+=at_km->mibarai_bonus;
	kashi_total+=at_km->mibarai_housyu;
	rieki=kari_total-kashi_total;
	rieki_out=rieki;
	bl_rieki=kari_total-kashi_total;
	zeimae_rieki=bl_rieki;
	
	if(rieki!=at_km->zeimae_soneki)
	{
		printf("\n\n PLとBLで計算された税前利益の内容が異なります。適当なキーを入力してください\n");
		printf("ag_no:%d , BL:%d , PL%d , zei:%d\n",Agent_no,rieki , at_km->zeimae_soneki,at_km->mibarai_zei);
		scanf_s("%d",&dumy);
	}

}
void CAccount::Print_pLsheet_table(FILE *out3,FILE *out3_csv)
{
	int j;
	long long kari_total=0,kashi_total=0;
	int nkamoku=mem_km.size();
	if(nkessan==0||nkessan==1){
		fprintf(out3,"損益計算書\n");
		fprintf(out3,"           勘定科目　  コード　 　借方　  　貸方\n");
		fprintf(out3_csv,"損益計算書\n");
		fprintf(out3_csv,"   ,      ,  勘定科目, 　借方　,  　貸方\n");
	}
	//収入科目の記載
	for(j=0;j<nkamoku;j++){
			if(mem_km[j]->code==3){
				if(nkessan==0 || nkessan==1){
					fprintf(out3," %20s %4d                 %8d\n",mem_km[j]->kamoku,mem_km[j]->code,mem_km[j]->kashikata_total-mem_km[j]->karikata_total);
		//			printf("j=%d %20s %4d                 %8d\n",j,mem_km[j]->kamoku,mem_km[j]->code,mem_km[j]->kashikata_total-mem_km[j]->karikata_total);
					fprintf(out3_csv,"  ,   ,%20s ,         ,  %8lld\n",mem_km[j]->kamoku,mem_km[j]->kashikata_total-mem_km[j]->karikata_total);
				}
			kashi_total+=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			if(strcmp(mem_km[j]->kamoku,"売上額")==0) uriage_out=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			if(strcmp(mem_km[j]->kamoku,"受取利息")==0) ukerisi_out=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;	
		}
	}
	//経費科目の記載
	for(j=0;j<nkamoku;j++){
			if(mem_km[j]->code==1)
			{
				if(strcmp(mem_km[j]->kamoku,"税等調整額")!=0)
				{
					if(nkessan==0 || nkessan==1){
						fprintf(out3," %20s %4d     %8d\n",mem_km[j]->kamoku,mem_km[j]->code,mem_km[j]->karikata_total-mem_km[j]->kashikata_total);
//						printf("j=%d %20s %4d     %8d\n",j,mem_km[j]->kamoku,mem_km[j]->code,mem_km[j]->karikata_total-mem_km[j]->kashikata_total);
						fprintf(out3_csv,"  ,  ,%20s,  %8lld\n",mem_km[j]->kamoku,mem_km[j]->karikata_total-mem_km[j]->kashikata_total);
					}
				kari_total+=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
				if(strcmp(mem_km[j]->kamoku,"減価償却費")==0) genkasyoukyaku_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
				if(strcmp(mem_km[j]->kamoku,"支払利息")==0) siharisi_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
				if(strcmp(mem_km[j]->kamoku,"法人税")==0) houzin_zei_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
				if(strcmp(mem_km[j]->kamoku,"役員報酬")==0) yakuin_housyu_out=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
				}
		}
	}


	
	
	
//	rieki=kashi_total-kari_total;
	if(nkessan==0 || nkessan==1){
		fprintf(out3,"            未払ボーナス       %8d\n",at_km->touki_mibarai_bonus);
		fprintf(out3,"            当期利益           %8d\n",at_km->zeimae_soneki);
		fprintf(out3,"            ----------------------------------------\n");
		fprintf(out3,"            合計               %8d    %8d\n",kari_total+at_km->zeimae_soneki+at_km->touki_mibarai_bonus,kashi_total);
		fprintf(out3_csv,"     ,     ,  当期ボーナス   ,        %8lld\n",at_km->touki_mibarai_bonus);
		fprintf(out3_csv,"     ,     ,  税引き前利益   ,        %8lld\n",at_km->zeimae_soneki);
		fprintf(out3_csv,"     ,       ,----------------------------------------\n");
		fprintf(out3_csv,"     ,      , 合計 ,              %8lld  ,  %8lld\n",kari_total+at_km->zeimae_soneki+at_km->touki_mibarai_bonus,kashi_total);
		fprintf(out3,"\n");
		fprintf(out3_csv,"\n");
	}

	touki_keihi_soukei=kari_total+at_km->touki_mibarai_bonus;

}
void CAccount::Print_balance_table(FILE *out3,FILE *out3_csv)
{
	int j;
	long long kari_total=0,kashi_total=0;
	long long kari_kashi=0,kashi_kari=0;
	long long kimatu_kashi=0,kimatu_kari=0;
	long long yozyou=0;
	int nkamoku=mem_km.size();
	if(nkessan==0 || nkessan==1){
		fprintf(out3_csv,"agent_type=%d    agent_no=%d\n",agent_type,Agent_no);
		fprintf(out3,"貸借対照表\n");
		fprintf(out3,"           勘定科目　  コード　 　借方　  　貸方\n");
		fprintf(out3_csv,"貸借対照表\n");
		fprintf(out3_csv,"  ,  ,勘定科目 ,借方期首残高,貸方期首残高, 借方 , 貸方 , 借方期末残高 ,貸方期末残高\n");
	}
	//資本科目の記述
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==0)
		{
			kari_kashi=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(nkessan==0 || nkessan==1){
				fprintf(out3," %20s %4d     %8d\n",mem_km[j]->kamoku,mem_km[j]->code,kari_kashi);
				fprintf(out3_csv," , ,%20s, %8lld,  , %8lld ,  ,  %8lld\n",mem_km[j]->kamoku,mem_km[j]->kisyu_zandaka,kari_kashi,mem_km[j]->kisyu_zandaka+kari_kashi);
			}
			kari_total+=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			kimatu_kari+=mem_km[j]->kisyu_zandaka+mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
			if(strcmp(mem_km[j]->kamoku,"製品")==0) zaiko_out=kari_kashi;
			if(strcmp(mem_km[j]->kamoku,"設備")==0) setubi_out=mem_km[j]->karikata_total;
		}
	}


	//負債科目の記述
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==2)
		{
			kashi_kari=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			if(nkessan==0 || nkessan==1){
				fprintf(out3," %20s %4d                 %8d\n",mem_km[j]->kamoku,mem_km[j]->code,kashi_kari);
				fprintf(out3_csv," , ,%20s, , %8lld ,  , %8lld ,  ,%8lld\n",mem_km[j]->kamoku,mem_km[j]->kisyu_zandaka,kashi_kari,mem_km[j]->kisyu_zandaka+kashi_kari);
			}
			kashi_total+=mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
			kimatu_kashi+=mem_km[j]->kisyu_zandaka+mem_km[j]->kashikata_total-mem_km[j]->karikata_total;
		}
		
	}

	if(nkessan==0 || nkessan==1){
		fprintf(out3," 未払ボーナス 0                 %8d\n",at_km->kisyu_mibarai_bonus+at_km->touki_mibarai_bonus);
		fprintf(out3_csv," , ,未払ボーナス, , %8lld ,  , %8lld ,  ,%8lld\n",at_km->kisyu_mibarai_bonus,at_km->mibarai_bonus+at_km->touki_mibarai_bonus,at_km->kimatu_mibarai_bonus);
		fprintf(out3," 未払消費税 0                 %8d\n",at_km->kisyu_mibarai_zei+at_km->touki_mibarai_zei);
		fprintf(out3_csv," , ,未払消費税, , %8lld ,  , %8lld ,  ,%8lld\n",at_km->kisyu_mibarai_shouhi_zei,at_km->mibarai_shouhi_zei+at_km->touki_mibarai_shouhi_zei,at_km->kimatu_mibarai_shouhi_zei);	
		fprintf(out3," 未払税 0                 %8d\n",at_km->kisyu_mibarai_zei+at_km->touki_mibarai_zei);
		fprintf(out3_csv," , ,未払税, , %8lld ,  , %8lld ,  ,%8lld\n",at_km->kisyu_mibarai_zei,at_km->mibarai_zei+at_km->touki_mibarai_zei,at_km->kimatu_mibarai_zei);	
		fprintf(out3," 役員報酬 0                 %8d\n",at_km->kisyu_mibarai_housyu+at_km->touki_miabrai_housyu);
		fprintf(out3_csv," , ,役員報酬, , %8lld ,  , %8lld ,  ,%8lld\n",at_km->kisyu_mibarai_housyu,at_km->mibarai_housyu+at_km->touki_miabrai_housyu,at_km->kiamtu_mibarai_housyu);	
	}
	kashi_total+=at_km->mibarai_zei+at_km->touki_mibarai_zei+at_km->mibarai_housyu+at_km->touki_miabrai_housyu+at_km->mibarai_bonus+at_km->touki_mibarai_bonus;
	kimatu_kashi+=at_km->kimatu_mibarai_zei+at_km->kiamtu_mibarai_housyu+at_km->kimatu_mibarai_bonus;
	
	if(nkessan==0 || nkessan==1){
	fprintf(out3," 利益剰余 0                 %8d\n",at_km->rieki_zyouyo);
	fprintf(out3_csv," , ,利益剰余, , %8lld ,  , %8lld ,  ,%8lld\n",at_km->kisyu_rieki_zyouyo,at_km->rieki_zyouyo,at_km->kimatu_rieki_zyouyo);
	}
	kashi_total+=at_km->rieki_zyouyo;
	kimatu_kashi+=at_km->kimatu_rieki_zyouyo;


	if(nkessan==0 || nkessan==1){

		fprintf(out3,"            合計               %8d    %8d\n",kari_total,kashi_total+touki_soneki);
		fprintf(out3_csv,"      ,      ,------------------------------------------------------------------\n");
		fprintf(out3_csv,"      ,      ,合計 ,  ,  , %8lld , %8lld  ,  %8lld , %8lld\n",kari_total,kashi_total,kimatu_kari,kimatu_kashi);
		fprintf(out3,"\n");
		fprintf(out3_csv,"\n");
	}


}
int CAccount::Get_kamoku(int index,char *kamoku)
{
	//取り出し全般
	int j;	long long kimatu=0;
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==index){
			if(strcmp(mem_km[j]->kamoku,kamoku)==0)	kimatu=mem_km[j]->zandaka;
//			printf("xxxx1 j=%d n=%d k1=%d k2=%d  || %d\n",j,nkamoku,kimatu,strcmp(mem_km[j]->kamoku,kamoku));
		}
	}
	return int(kimatu);
}
long long CAccount::Get_kamoku_l(int index,char *kamoku)
{
	//取り出し全般
	int j;	long long kimatu=0;
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==index){
			if(strcmp(mem_km[j]->kamoku,kamoku)==0)	kimatu=mem_km[j]->zandaka;
//			printf("xxxx1 j=%d n=%d k1=%d k2=%d  || %d\n",j,nkamoku,kimatu,strcmp(mem_km[j]->kamoku,kamoku));
		}
	}
	return kimatu;
}
int CAccount::Get_karikashi_ac(int index,char *kamoku)
{
	//取り出し全般
	int j;	long long kimatu=0;
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==index){
			if(strcmp(mem_km[j]->kamoku,kamoku)==0){ 
				kimatu=mem_km[j]->karikata_total-mem_km[j]->kashikata_total;
	//			printf("ki=%d kamoku=%s nkamoku=%d\n",mem_km[j]->zandaka,kamoku,j);
			}
		}
	}
	return int(kimatu);
}
int CAccount::Get_kisyu_ac(int index,char *kamoku)
{
	//取り出し全般
	int j;	long long kimatu=0;
	for(j=0;j<nkamoku;j++)
	{
		if(mem_km[j]->code==index){
			if(strcmp(mem_km[j]->kamoku,kamoku)==0){ 
				kimatu=mem_km[j]->kisyu_zandaka;
	//			printf("ki=%d kamoku=%s nkamoku=%d\n",mem_km[j]->zandaka,kamoku,j);
			}
		}
	}
	return int(kimatu);
}
void CAccount::Erase_mem_sh()
{
	int i=0;
	int size_sh,size_shisan,size_keihi,size_husai,size_uriage,size_km,size_kmr;
	size_sh=mem_sh.size();
	size_shisan=mem_shisan_km.size();
	size_keihi=mem_keihi_km.size();
	size_husai=mem_husai_km.size();
	size_uriage=mem_uriage_km.size();
	size_km=mem_km.size();
	size_kmr=mem_kmr.size();
//	printf("before s_sh=%d s_shisan=%d s_keihi=%d s_husai=%d s_uriage=%d s_km,s_kmr=%d \n",mem_sh.size(),mem_shisan_km.size(),mem_keihi_km.size(),mem_husai_km.size(),mem_uriage_km.size(),mem_km.size(),mem_kmr.size());
	i=mem_sh.size()-1;
	while(mem_sh.size()>0)
	{
		sh=mem_sh[i];
		mem_sh.pop_back();
		delete sh;
		i=i-1;
	}


//	printf("after s_sh=%d s_shisan=%d s_keihi=%d s_husai=%d s_uriage=%d s_km,s_kmr=%d \n",mem_sh.size(),mem_shisan_km.size(),mem_keihi_km.size(),mem_husai_km.size(),mem_uriage_km.size(),mem_km.size(),mem_kmr.size());
}
#endif