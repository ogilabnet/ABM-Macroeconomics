//CFunciton.h
//乱数での選択、一致の確認等の小行動関数の集まり
#ifndef INC_CFUNCTION
#define INC_CFUNCTION
#include <stdio.h>
#include <vector>
#include "CRandum.h"
using namespace std;

class CFunction
{
	
	CRandum *cr;

public:
	CFunction(CRandum *x);

// 乱数選択系～　ベクター内の数字をランダムに選択
	//乱数ベクタ生成系～乱数選択系を使用する前に必ずこちらに落として番号ベクタを作ってそれを再度入力すること
	template<class T> vector<int> Cr_random_INTvector_INT(const T& member);	//INT型のベクタ生成、引数にINTのベクタが必要
	template<class T> vector<int> Cr_random_INTvector_AGE(const T& member);	//INT型のベクタ生成、引数にエージェントベクタが必要、エージェントナンバーから生成
		//乱数選択系_
	template<class T,class U> int Random_choice_int( T& member, U& ite);	//入れられたベクターの中から乱数で番号を選んでその値を取り出す＿int型用
	template<class T,class U,class V> int Random_choice_int( T& member, U& ite,V& cra);	//入れられたベクターの中から乱数で番号を選んでその値を取り出す＿int型用、乱数クラス同時利用版


//比較系～ベクタ内に該当するベクタがあるかどうかを判断する
	//比較系_エージェントベクタ
	template<class T,class U> int Comp_AGEvec_VAR(const T& agevec, const U& varia);		//左側がAGEvecで右側が変数の場合の比較、ベクターからナンバーを取り出す一致することがある場合は１を返す
	template<class T,class U> int Comp_AGEvec_VAR_return_no(const T& agevec,const U& varia);//左側がAGEvecで右側が変数の場合の比較、該当の添え字番号を返す
	template<class T,class U> int Comp_AGEvec_AGEvec(const T& vect, const U& vecgt2);		//左側がAGEvecで右側がAGEvecの場合の比較、ベクターからナンバーを取り出す一致することがある場合は１を返す
	template<class T,class U> int Comp_AGEvec_AGEvec_return_no(const T& vect,const U& vect2);//左側がAGEvecで右側がAGEvecの場合の比較、該当の添え字番号を返す
	template<class T,class U> int Comp_AGEvec_INTvec(const T& vect, const U& vect2);		//左側がAGEvecで右側がAGEvecの場合の比較、ベクターからナンバーを取り出す一致することがある場合は１を返す
	template<class T,class U> int Comp_AGEvec_INTvec_return_no(const T& vect,const U& vect2);//左側がAGEvecで右側がAGEvecの場合の比較、該当の添え字番号を返す

	//比較系_変数ベクタ
	template<class T,class U> int Comp_INTvec_VAR(const T& vect, const U& varia);		//左側がINTvecで右側が変数の場合の比較、一致することがある場合は１を返す
	template<class T,class U> int Comp_INTvec_VAR_return_no(const T& vect,const U& varia);//左側がINTvecで右側が変数の場合の比較、該当の添え字番号を返す
	template<class T,class U> int Comp_INTvec_INTvec(const T& vect, const U& varia);		//左側がINTvecで右側がINTvecの場合の比較、一致することがある場合は１を返す
	template<class T,class U> int Comp_INTvec_INTvec_return_no(const T& vect,const U& varia);//左側がINTvecで右側がINTvecの場合の比較、該当の添え字番号を返す

//ソート系
	template<class T,class U> vector<int> Sort_NUMvec(const T &vec, U &member,int code);	//数字型ベクターのソート
	template<class T,class U,class V,class W> vector<int> Sort_NUMvec(const T &vec, const U &vec2, V &member, W &no_member,int code);	//数字型ベクターのソート
};

CFunction::CFunction(CRandum *x)
{
	cr=x;	//乱数の引き渡し
}


template<class T,class U,class V,class W> vector<int> CFunction::Sort_NUMvec(const T &vec, const U &vec2, V &member, W &no_member, int code)
{
	//引数で投入したベクターのソートを行う、戻り値は2つ目のベクターのソート結果
	//3つ目、4つ目はソートをする時のダミーベクタ、呼び出すときに一つ目、二つ目とそれぞれ同じ変数型のベクタを入れること
	//（これによってINT、DOUBLEなどの型によらず本関数の利用が可能となる）
	//一つ目の投入ベクターを基準にソート、二つ目の投入ベクターは一つ目のソートに合わせてソート
	//給与などの順位を知る場合に、一つ目に給与の集合、二つ目にその給与のエージェントナンバー集合を入れると、給与の順にエージェントナンバーがソートされてアウトプットされる
	//コードによって昇順、降順が異なる
	//code:		0=昇順にソート
	//			1=降順にソート

	int i, j, temp,temp2;
	
	for(i=0;i<int(vec.size());i++)
	{
		member.push_back(vec[i]);
		no_member.push_back(vec2[i]);
	}

	switch(code)
	{

	case 0:			//昇順
//		printf("shou\n");
 
		for (i = 0; i < int(member.size()) - 1; i++) 
		{
		
		    for (j = member.size()-1; j > i; j--) 
			{
		         if (member[j-1] > member[j])
				 {		//	x[j - 1] > x[j]) {  /* 前の要素の方が大きかったら */
		    //	    printf("%d , %d\n",statistics_income[j-1],statistics_income[j]);
					temp=member[j-1];							//	temp = x[j];        /* 交換する */
					member[j-1]=member[j];		//	x[j] = x[j - 1];
	                member[j]=temp;							//	x[j - 1]= temp;	

					temp2=no_member[j-1];
					no_member[j-1]=no_member[j];
					no_member[j]=temp2;
				}
	        }
	    }
		break;

	case 1:			//降順
//		printf("kou\n");
		for (i = 0; i < int(member.size()) - 1; i++) 
		{
		
		    for (j = member.size()-1; j > i; j--) 
			{
		         if (member[j-1] < member[j])
				 {		//	x[j - 1] > x[j]) {  /* 前の要素の方が大きかったら */
		    //	    printf("%d , %d\n",statistics_income[j-1],statistics_income[j]);
					temp=member[j];							//	temp = x[j];        /* 交換する */
					member[j]=member[j-1];		//	x[j] = x[j - 1];
	                member[j-1]=temp;							//	x[j - 1]= temp;	

					temp2=no_member[j];
					no_member[j]=no_member[j-1];
					no_member[j-1]=temp2;
				}
	        }
	    }
		break;
	}

	return no_member;
}

template<class T,class U> vector<int> CFunction::Sort_NUMvec(const T &vec, U &member, int code)
{
	//引数で投入したベクターのソートを行う、
	//2つ目はソートをする時のダミーベクタ、呼び出すときに一つ目、二つ目とそれぞれ同じ変数型のベクタを入れること
	//（これによってINT、DOUBLEなどの型によらず本関数の利用が可能となる）
	//コードによって昇順、降順が異なる
	//code:		0=降順にソート
	//			1=昇順にソート

	int i, j, temp;
	
	for(i=0;i<int(vec.size());i++)
	{
		member.push_back(vec[i]);
	}

	switch(code)
	{

	case 0:			//昇順
 
		for (i = 0; i < int(member.size()) - 1; i++) 
		{
		
		    for (j = member.size()-1; j > i; j--) 
			{
		         if (member[j-1] > member[j])
				 {		//	x[j - 1] > x[j]) {  /* 前の要素の方が大きかったら */
		    //	    printf("%d , %d\n",statistics_income[j-1],statistics_income[j]);
					temp=member[j-1];							//	temp = x[j];        /* 交換する */
					member[j-1]=member[j];		//	x[j] = x[j - 1];
	                member[j]=temp;							//	x[j - 1]= temp;	
				}
	        }
	    }
		break;

	case 1:			//降順
		
		for (i = 0; i < int(member.size()) - 1; i++) 
		{
		
		    for (j = member.size()-1; j > i; j--) 
			{
		         if (member[j-1] < member[j])
				 {		//	x[j - 1] > x[j]) {  /* 前の要素の方が大きかったら */
		    //	    printf("%d , %d\n",statistics_income[j-1],statistics_income[j]);
					temp=member[j];							//	temp = x[j];        /* 交換する */
					member[j]=member[j-1];		//	x[j] = x[j - 1];
	                member[j-1]=temp;							//	x[j - 1]= temp;	
				}
	        }
	    }
		break;

		
	}

	return member;
}


template<class T,class U> int CFunction::Comp_AGEvec_VAR(const T &agevec, const U &varia)
{
	int i;
	int checker=0;

	for(i=0;i<int(agevec.size());i++)
	{
		if(agevec[i]->Get_Agent_no()==varia)	
		{
			checker=1;
			break;
		}
	}
	return checker;
}
template<class T,class U> int CFunction::Comp_AGEvec_VAR_return_no(const T &agevec, const U &varia)
{
	int i;
	int no;
	bool checker=false;

	for(i=0;i<int(agevec.size());i++)
	{
		if(agevec[i]->Get_Agent_no()==varia)	
		{
			no=i;
			checker=true;
			break;
		}
	}

	if(checker==false) 	{printf("error CFunction::Comp_agentvec_var_return_no\n"); scanf_s("%d",&no);}

	return no;
}
template<class T,class U> int CFunction::Comp_AGEvec_AGEvec(const T &vect, const U &vect2)
{
	int i,j;
	int checker=0;
	for(i=0;vect.size();i++)
	{
		for(j=0;vect2.size();j++)
		{
			if(vect[i]->Get_Agent_no()==vect2[i]->Get_Agent_no)	checker=1;
		}
	}
	return checker;
}

template <class T,class U> int CFunction::Comp_AGEvec_AGEvec_return_no(const T &vect, const U &vect2)
{
	int i;
	int no;
	bool checker=false;
	for(i=0;vect.size();i++)
	{
		for(i=0;i<int(vect2.size());j++)
		{
			if(vect[i]->Get_Agent_no()==vect2[i]->Get_Agent_no)	
			{
				no=i;
				checker=true;
			}
		}
	}
	
	if(checker==false) 	{printf("error CFunction::Comp_agentvec_var_return_no\n"); scanf("%d",&no);}
	return no;
}

template<class T,class U> int CFunction::Comp_AGEvec_INTvec(const T &vect, const U &vect2)
{
	int i,j;
	int checker=0;
	for(i=0;vect.size();i++)
	{
		for(j=0;vect2.size();j++)
		{
			if(vect[i]->Get_Agent_no()==vect2[i])	checker=1;
		}
	}
	return checker;
}

template<class T,class U> int CFunction::Comp_AGEvec_INTvec_return_no(const T &vect, const U &vect2)
{
	int i;
	int no;
	bool checker=false;
	for(i=0;vect.size();i++)
	{
		for(j=0;vect2.size();j++)
		{
			if(vect[i]->Get_Agent_no()==vect2)	
			{
				no=i;
				checker=true;
			}
		}
	}
	
	if(checker==false) 	{printf("error CFunction::Comp_agentvec_var_return_no\n"); scanf_s("%d",&no);}
	return no;
}



template<class T,class U> int CFunction::Comp_INTvec_VAR(const T &vect, const U &varia)
{
	int i;
	int checker=0;

	for(i=0;i<vect.size();i++)
	{
		if(vect[i]==varia)	checker=1;
	}
	return checker;
}
template<class T,class U> int CFunction::Comp_INTvec_VAR_return_no(const T &vect, const U &varia)
{
	int i;
	int no;
	bool checker=false;

	for(i=0;i<int(vect.size());i++)
	{
		if(vect[i]==varia)	
		{
			no=i;
			checker=true;
		}
	}

	if(checker==false) {printf("error CFunction::Comp_agentvec_var_return_no\n"); scanf_s("%d",&no);}
	return no;
}





template<class T,class U> int CFunction::Random_choice_int( T& member, U& ite)
{
//	vector <int >::iterator dl_re;
	int ni,re_no,j;
	ni=cr->strand(0,member.size()-1);
	re_no=member[ni];
//	dl_re=member.begin();
	ite=member.begin();
	for(j=0;j<int(member.size());j++)
	{
		if(j==ni)
		{
			ite=member.erase(ite);//dl_re);
			break;
		}
		ite++;//dl_re++;
	}
	return re_no;
}

template<class T,class U,class V> int CFunction::Random_choice_int( T& member, U& ite,V& cra)
{
//	vector <int >::iterator dl_re;
	int ni,re_no,j;
	ni=cra->strand(0,member.size()-1);
	re_no=member[ni];
//	dl_re=member.begin();
	ite=member.begin();
	for(j=0;j<int(member.size());j++)
	{
		if(j==ni)
		{
			ite=member.erase(ite);//dl_re);
			break;
		}
		ite++;//dl_re++;
	}
	return re_no;
}

template<class T> vector<int> CFunction::Cr_random_INTvector_INT(const T &member)
{
	int i;
	vector <int> random_vector;
	for(i=0;i<int(member.size());i++)
	{
		random_vector.push_back(member[i]);
	}
	return random_vector;

}
template<class T> vector<int> CFunction::Cr_random_INTvector_AGE(const T &member)
{
	int i;
	vector <int> random_vector;
	for(i=0;i<int(member.size());i++)
	{
		random_vector.push_back(member[i]->Get_Agent_no());
	}
	return random_vector;

}

#endif