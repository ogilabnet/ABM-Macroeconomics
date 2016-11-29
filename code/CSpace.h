//CSpace

#ifndef INC_CSPACE
#define INC_CSPACE
#include <stdio.h>
#include <vector>
#include "CRandum.h"
#include "CParameter.h"
#include "CShow.h"
#include "CFunction.h"
#include "CSellowner.h"
using namespace std;

class CSpace
{
	

public:
	CParameter *cpara;
	CRandum *cr;
	CShow *cs;
	CSellowner *cso;
	CFunction *cf;



};

#endif