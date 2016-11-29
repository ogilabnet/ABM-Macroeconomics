//CSellowner 　価格表等の管理者
#ifndef INC_CSellowner
#define INC_CSellowner
#include <stdio.h> 
#include <vector>
#include "CProduct_class.h"
#include "CPrice_tag.h"
using namespace std;

class CSellowner
{

public:
	template <class T,class U> void Set_price_tag(T &mem_pro,U &tag);
	template <class T> int Extraction_tag_indexno_highprice(T &tag);		//プライスタグ用、最高価格の添え字を選別する
	template <class T> int Extraction_tag_price_highprice(T &tag);			//プライスタグ用、最高価格の価格を選別する
	template <class T> int Extraction_tag_indexno_lowprice(T &tag);			//プライスタグ用、最低価格の添え字を選別する
	template <class T> int Extraction_tag_price_lowprice(T &tag);			//プライスタグ用、最低価格の価格を選別する
	template <class T,class U> void Buy_set_price_tag(T &tag,U &mem_product,int mem_pro_no);	//プライスタグ用、1個販売時のプライスタグの在庫値の設定調整



};
template<class T, class U> void CSellowner::Buy_set_price_tag(T &tag, U &mem_product, int mem_pro_no)
{
	for(int m=0;m<int(tag.size());m++)
	{
		if(mem_product[mem_pro_no]->Get_Producer_no()==tag[m]->Get_Producer_no() && mem_product[mem_pro_no]->Get_class_no()==tag[m]->Get_class_no())
		{
			tag[m]->Set_nstock(tag[m]->Get_nstock()-1);
			tag[m]->Set_presence_of_stock(tag[m]->Get_nstock());
			break;
		}
	}
}


template<class T> int CSellowner::Extraction_tag_indexno_highprice(T &tag)
{
	int price=0,no=0,checker=0;
	for(int i=0;i<int(tag.size());i++)
	{
		if(tag[i]->Get_presence_of_stock()==1)
		{
			if(checker==0)
			{
				price=tag[i]->Get_price();
				no=i;
				checker=1
			}

			if(price<tag[i]->Get_price())
			{
				price=tag[i]->Get_price();
				no=i;
			}
		}
	}
	return no;
}
template<class T> int CSellowner::Extraction_tag_price_highprice(T &tag)
{
	int price,checker=0;
	for(int i=0;i<int(tag.size());i++)
	{
		if(tag[i]->Get_presence_of_stock()==1)
		{
			if(checker==0)
			{
				price=tag[i]->Get_price();
				checker=1;
			}

			if(price<tag[i]->Get_price())
			{
				price=tag[i]->Get_price();
			}
		}
	}
	printf("price=%d\n",price);

	return price;
}
template<class T> int CSellowner::Extraction_tag_indexno_lowprice(T &tag)
{
	int price=0,no=0;
	for(int i=0;i<int(tag.size());i++)
	{
		if(i==0)
		{
			price=tag[i]->Get_price();
			no=i;
		}

		if(price>tag[i]->Get_price())
		{
			price=tag[i]->Get_price();
			no=i;
		}
	}
	return no;
}

template<class T> int CSellowner::Extraction_tag_price_lowprice(T &tag)
{
	int price=0;
	for(int i=0;i<int(tag.size());i++)
	{
		if(i==0)
		{
			price=tag[i]->Get_price();
		}

		if(price>tag[i]->Get_price())
		{
			price=tag[i]->Get_price();
		}
	}
	return price;
}

template <class T,class U> void CSellowner::Set_price_tag(T &mem_pro,U &tag)
{
	int stock=0,price=0;
	for(int i=0;i<int(tag.size());i++)
	{
		stock=0;
		price=0;
		for(int j=0;j<int (mem_pro.size());j++)
		{
			if(tag[i]->Get_Producer_no()==mem_pro[j]->Get_Producer_no()&&tag[i]->Get_class_no()==mem_pro[j]->Get_class_no())
			{
				stock++;
				price=mem_pro[j]->Get_price();
			}
		}
		tag[i]->Set_nstock(stock);
		tag[i]->Set_presence_of_stock(tag[i]->Get_nstock());
		tag[i]->Set_price(price);
		
	}
}


#endif