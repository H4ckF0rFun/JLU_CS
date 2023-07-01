#pragma once
#include "AddGoodsDlg.h"
#include "stock.h"
#include "resource.h"
class CChangeGoodsDlg :
	public CAddGoodsDlg
{
public:
	CChangeGoodsDlg(Goods&	goods);
	~CChangeGoodsDlg();
	virtual BOOL OnInitDialog();
};

