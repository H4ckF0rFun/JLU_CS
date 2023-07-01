#pragma once
#include "SellDlg.h"

class CPurcsDlg :
	public CSellDlg
{
public:
	CPurcsDlg(Goods&goods);
	~CPurcsDlg();

	void OnEnChangeEdit4();

	virtual BOOL OnInitDialog();
	virtual void OnOK();
};

