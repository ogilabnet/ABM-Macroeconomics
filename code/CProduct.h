//CProduct.h
#ifndef INC_CPRODUCT
#define INC_CPRODUCT
#include <vector>
using namespace std;
class CProduct
{
	int lot_no;
	int Producer_no;//その製品を生産したエージェントの番号
	int Producer_type;
	int Agent_no;//その製品を購入したエージェントの番号
	int Agent_type;
	int class_no;//製品種別
	int ncr_p;//その製品を生産したエージェントの生産する製品種別の数
	int product_type;//retail製品1、whlesale製品2
	int state;
	    //state=0; at producer
	    //state=1; in the market for sale
	    //state=2; at consumer (after being sold)
	int price;
	int price_genka;
	int surplus_money;
	int material_no;
	int hendouhi;

public:
	void Set_hendouhi(int hen1){hendouhi=hen1;};
	int Get_hendouhi(){return hendouhi;};
	void Set_price_genka(int price_genka1){price_genka=price_genka1;};
	int Get_price_genka(){return price_genka;};
	void Set_surplus_money(int surplus_money1){surplus_money=surplus_money1;};
	int Get_surplus_money(){return surplus_money;};
	void Set_product_type();
	int Get_product_type(){return product_type;};
	void Set_Producer_no(int Producer_no1){Producer_no=Producer_no1;};
	int Get_Producer_no(){return Producer_no;};
	void Set_Producer_type(int Producer_type1){Producer_type=Producer_type1;};
	int Get_Producer_type(){return Producer_type;};
	void Set_Agent_no(int Agent_no1){Agent_no=Agent_no1;};
	int Get_Agent_no(){return Agent_no;};
	void Set_Agent_type(int Agent_type1){Agent_type=Agent_type1;};
	int Get_Agent_type(){return Agent_type;};
	void Set_ncr_p(int ncr_p1){ncr_p=ncr_p1;};
	int Get_ncr_p(){return ncr_p;};
	void Set_price(int price1){price=price1;};
	int Get_price(){return price;};
	void Set_lot_no(int lot_no1){lot_no=lot_no1;};
	int Get_lot_no(){return lot_no;};
	void Set_class_no(int class_no1){class_no=class_no1;};
	int Get_class_no(){return class_no;};
	void Set_state(int state1){state=state1;};
	void Set_material_no(int x){material_no=x;};
	int Get_material_no(){return material_no;};

	
};
void CProduct::Set_product_type()
{
	//product_type=1 for retail product、=2 for wholesale product
	int agent_type;
	agent_type=Get_Producer_type();
	if(agent_type==20) product_type=1;
	else if(agent_type==30) product_type=2;
	else product_type=0;//producer_typeの設定に誤りがあります。
}

#endif