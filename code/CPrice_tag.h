//CPrice_tag @‰¿Ši•\“™‚ÌŠÇ—Ò
#ifndef INC_CPRICE_TAG
#define INC_CPRICE_TAG
#include <stdio.h> 
#include <vector>
using namespace std;

class CPrice_tag	: public CProduct_class
{

	int presence_of_stock;
	vector <int> mem_product_no;

public:

	void Set_presence_of_stock(int x);
	void Set_mem_product_no_vec(int x){mem_product_no.push_back(x);};


	int Get_presence_of_stock(){return presence_of_stock;};	
	int Get_mem_product_no_top();

};
void CPrice_tag::Set_presence_of_stock(int x)
{
	if(x>0)		presence_of_stock=1;
	else		presence_of_stock=0;
}
int CPrice_tag::Get_mem_product_no_top()
{
	int out=0;
	vector <int>::iterator ite;
	out=mem_product_no[0];
	ite=mem_product_no.begin();
	return out;
}

#endif