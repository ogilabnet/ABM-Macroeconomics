#include <stdio.h>
#include "CAppli.h"


void main()
{
	CAppli *cap;
	cap=new CAppli;
		
	cap->Create_Assumption();	//パラメータクラスの生成
	cap->Set_Parameter();		//パラメータのセット
	cap->Create_Market();		//Showクラス、マーケットクラスの生成
	cap->Create_file();			//書き込み用FILEの生成
	cap->Create_Agent();		//エージェントの生成、初期値設定
	cap->Market();		//実際の実行

}