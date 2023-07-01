// ParchaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "PurchaseDlg.h"
#include "afxdialogex.h"
#include "SortDlg.h"

// CParchaseDlg 对话框

IMPLEMENT_DYNAMIC(CPurchaseDlg, CDialogEx)

CPurchaseDlg::CPurchaseDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CPurchaseDlg::IDD, pParent)
, m_Filter(_T(""))
{
	m_pPurchaseRecords = createlist();
	m_pCurRecord = NULL;
}

CPurchaseDlg::~CPurchaseDlg()
{
	for (Node*it = m_pPurchaseRecords->Head.next; it != &m_pPurchaseRecords->Head; it = it->next)
	{
		//保存每一天的记录
		PurchaseRecords*pPurchaseRecord = (PurchaseRecords*)it;
		char szFileName[256];
		sprintf(szFileName, "PurchaseRecords\\%s", pPurchaseRecord->szDate);
		WriteRecord(szFileName, pPurchaseRecord->m_pRecordList);
		//删除每一天的记录
		dellist(pPurchaseRecord->m_pRecordList);
	}
	//删除链表
	dellist(m_pPurchaseRecords);
}

void CPurchaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PurchaseList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_FilterList);
	DDX_Text(pDX, IDC_EDIT1, m_Filter);
}


BEGIN_MESSAGE_MAP(CPurchaseDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPurchaseDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPurchaseDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPurchaseDlg::OnBnClickedButton3)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CPurchaseDlg::OnDtnDatetimechangeDatetimepicker1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CPurchaseDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CPurchaseDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON6, &CPurchaseDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CParchaseDlg 消息处理程序


BOOL CPurchaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ModifyStyle(0, WS_CHILD);

	CreateDirectory(L"PurchaseRecords", NULL);
	//


	//
	m_FilterList.AddString(L"编号");
	m_FilterList.AddString(L"名称");
	m_FilterList.AddString(L"品种");
	m_FilterList.AddString(L"时间");
	m_FilterList.SetCurSel(0);


	//
	m_PurchaseList.InsertColumn(0, L"编号", LVCFMT_LEFT, 120);
	m_PurchaseList.InsertColumn(1, L"名称", LVCFMT_LEFT, 120);
	m_PurchaseList.InsertColumn(2, L"品种", LVCFMT_LEFT, 120);
	m_PurchaseList.InsertColumn(3, L"单位", LVCFMT_LEFT, 75);
	m_PurchaseList.InsertColumn(4, L"数量", LVCFMT_LEFT, 75);
	m_PurchaseList.InsertColumn(5, L"进价", LVCFMT_LEFT, 80);
	m_PurchaseList.InsertColumn(6, L"售价", LVCFMT_LEFT, 80);
	m_PurchaseList.InsertColumn(7, L"金额", LVCFMT_LEFT, 100);
	m_PurchaseList.InsertColumn(8, L"时间", LVCFMT_LEFT, 100);

	m_PurchaseList.InsertColumn(9, L"备注", LVCFMT_LEFT, 100);

	m_PurchaseList.SetExtendedStyle((~LVS_EX_CHECKBOXES)&(m_PurchaseList.GetExStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT));

	//加载列表.
	CTime time;
	m_DateCtrl.GetTime(time);
	//在已经加载的链表中查找当天的记录
	//当刚开启对话框的时候,就把当天的记录读取出来.
	m_pCurRecord = GetRecord(CW2A(time.Format(L"%Y-%m-%d")), m_pPurchaseRecords,"PurchaseRecords");
	
	UpdatePurchaseRecordListView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CPurchaseDlg::OnBnClickedButton1()
{
	//删除记录
	POSITION pos = m_PurchaseList.GetFirstSelectedItemPosition();
	if (pos == NULL || IDYES != MessageBox(L"确定要删除选中记录吗?(删除后不可恢复)", L"Warning", MB_YESNO | MB_ICONWARNING))
		return;

	while (pos)
	{
		int idx = m_PurchaseList.GetNextSelectedItem(pos);
		//删除指定记录
		ListContext*pList = m_pCurRecord->m_pRecordList;
		DeleteCurDateRecord(pList, CW2A(m_PurchaseList.GetItemText(idx, 8)));
	}

	//写到文件.
	char szFileName[256];
	sprintf(szFileName, "PurchaseRecords\\%s", m_pCurRecord->szDate);
	WriteRecord(szFileName, m_pCurRecord->m_pRecordList);
	//刷新显示.
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnBnClickedButton2()
{
	//清空记录
	if (IDYES != MessageBox(L"确定删除该天记录吗?(删除后不可恢复)", L"Warning", MB_YESNO | MB_ICONWARNING))
		return;
	ListContext*pList = m_pCurRecord->m_pRecordList;
	//删除当天的记录
	DeleteCurDateAllRecord(pList);
	//
	//写到文件.
	char szFileName[256];
	sprintf(szFileName, "PurchaseRecords\\%s", m_pCurRecord->szDate);
	WriteRecord(szFileName, m_pCurRecord->m_pRecordList);
	//
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnBnClickedButton3()
{
	//排序
	CSortDlg dlg(2);
	if (dlg.DoModal() == IDOK)
	{
		unsigned int key = dlg.m_SortType >> 16;
		unsigned int ascending = dlg.m_SortType & 0xffff;
		SortCurDatePurchaseRecord(m_pCurRecord->m_pRecordList, key, ascending);
		UpdatePurchaseRecordListView();
	}
}

void CPurchaseDlg::UpdatePurchaseRecordListView()
{
	UpdateData();
	m_PurchaseList.DeleteAllItems();
	m_PurchaseList.SetRedraw(0);
	ListContext*pList = m_pCurRecord->m_pRecordList;

	for (Node*pIt = pList->Head.next; pIt != &pList->Head; pIt = pIt->next)
	{
		//插入到ListCtrl里面
		Record*pRecord = (Record*)pIt;

		if (!Filter(*pRecord))
			InsertRecord(*pRecord);
	}
	m_PurchaseList.SetRedraw(1);
}


void CPurchaseDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	//
	CTime time;
	m_DateCtrl.GetTime(time);
	//日期改变时刷新链表.
	m_pCurRecord = GetRecord(CW2A(time.Format(L"%Y-%m-%d")).m_szBuffer, m_pPurchaseRecords,"PurchaseRecords");
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::InsertRecord(Record&record)
{
	CString Text;
	Text.Format(L"%d", record.ID);

	m_PurchaseList.InsertItem(0, Text);
	m_PurchaseList.SetItemText(0, 1, CA2W(record.szName));
	m_PurchaseList.SetItemText(0, 2, CA2W(record.szType));
	m_PurchaseList.SetItemText(0, 3, record.Unit ? L"斤" : L"个");

	Text.Format(L"%.2lf", record.Sell);
	m_PurchaseList.SetItemText(0, 4, Text);
	//进价
	Text.Format(L"%.2lf 元", record.Purchaseingprice);
	m_PurchaseList.SetItemText(0, 5, Text);
	//售价
	Text.Format(L"%.2lf 元", record.Sellingprice);
	m_PurchaseList.SetItemText(0, 6, Text);
	//进货金额
	double m = record.Sell * record.Purchaseingprice;
	Text.Format(L"%.2lf 元", m);
	m_PurchaseList.SetItemText(0, 7, Text);
	//
	m_PurchaseList.SetItemText(0, 8, CA2W(record.szTime));

	m_PurchaseList.SetItemText(0, 9, CA2W(record.szComment));
}

bool CPurchaseDlg::Filter(Record&record)
{
	CString Text;
	unsigned int ID = 0;
	if (m_Filter.GetLength() == 0)
		return false;;
	switch (m_FilterList.GetCurSel())
	{
	case 0:
		ID = atoi(CW2A(m_Filter));
		return ID!=record.ID;
	case 1:
		return 0 == strstr(record.szName, CW2A(m_Filter));
	case 2:
		return 0 == strstr(record.szType, CW2A(m_Filter));
	case 3:
		return 0 == strstr(record.szTime, CW2A(m_Filter));
	}
	return false;
}


void CPurchaseDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnEnChangeEdit1()
{
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnBnClickedButton6()
{
	CFileDialog FileDlg(FALSE, L"*.txt", L"", NULL, L"文本文档(*.txt)|*.txt", this);

	if (IDOK == FileDlg.DoModal())
	{
		if (ExportCurDatePurchaseReport(m_pCurRecord->m_pRecordList, m_pCurRecord->szDate, CW2A(FileDlg.GetPathName()).m_psz))
		{
			MessageBox(L"保存成功");
		}
		else
		{
			MessageBox(L"保存失败");
		}
	}
}


void CPurchaseDlg::OnOK()
{
}
