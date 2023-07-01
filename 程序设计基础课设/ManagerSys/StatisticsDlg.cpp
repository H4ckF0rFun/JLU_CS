// StatisticsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "StatisticsDlg.h"
#include "afxdialogex.h"


// CStatisticsDlg 对话框

IMPLEMENT_DYNAMIC(CStatisticsDlg, CDialogEx)

CStatisticsDlg::CStatisticsDlg(SaleRecords*pRecord, CString Today, CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisticsDlg::IDD, pParent)
{
	m_Today = Today;
	m_pRecord = pRecord;
}

CStatisticsDlg::~CStatisticsDlg()
{
}

void CStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CStatisticsDlg, CDialogEx)
END_MESSAGE_MAP()


// CStatisticsDlg 消息处理程序


BOOL CStatisticsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.SetExtendedStyle((~LVS_EX_CHECKBOXES)&(m_List.GetExStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES));
	m_List.InsertColumn(0, L"编号", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, L"名称", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, L"品种", LVCFMT_LEFT, 80);
	m_List.InsertColumn(3, L"单位", LVCFMT_LEFT, 60);
	m_List.InsertColumn(4, L"销量", LVCFMT_LEFT, 80);
	m_List.InsertColumn(5, L"利润", LVCFMT_LEFT, 80);

	//
	//显示到列表中:
	ListContext*pTempList = createlist();
	
	ListContext*pRecordList = m_pRecord->m_pRecordList;
	//遍历当天记录
	for (Node*p = pRecordList->Head.next; p != &pRecordList->Head; p = p->next)
	{
		//查找统计列表里面有没有这个记录.
		Node*it = NULL;
		for (it = pTempList->Head.next; it != &pTempList->Head; it = it->next)
		{
			if (((Record*)p)->ID == ((Record*)it)->ID)
				break;
		}
		if (it == &pTempList->Head)
		{
			Record *pNewRecord = (Record*)malloc(sizeof(Record));
			memset(pNewRecord, 0, sizeof(Record));

			pNewRecord->ID = ((Record*)p)->ID;					
			strcpy(pNewRecord->szName, ((Record*)p)->szName);
			strcpy(pNewRecord->szType, ((Record*)p)->szType);
			pNewRecord->Sell = 0;
			pNewRecord->Sellingprice = 0;
			pNewRecord->Unit = ((Record*)p)->Unit;
			//插入到TempList中
			insertback(pTempList,(Node*)pNewRecord);
			it = (Node*)pNewRecord;
		}

		//找到了.
		((Record*)it)->Sell += ((Record*)p)->Sell;//加上销量
		((Record*)it)->Sellingprice += ((Record*)p)->Sell * (((Record*)p)->Sellingprice * ((Record*)p)->m_Rate - ((Record*)p)->Purchaseingprice);
	}
	
	double TotalMoney = 0;
	//显示到列表中
	for (Node*p = pTempList->Head.next; p != &pTempList->Head; p = p->next)
	{
		Record*pRecord = (Record*)p;
		CString Text;
		Text.Format(L"%d", pRecord->ID);
		int idx = m_List.GetItemCount();
		
		m_List.InsertItem(idx, Text);
		m_List.SetItemText(idx, 1, CA2W(pRecord->szName));
		m_List.SetItemText(idx, 2, CA2W(pRecord->szType));

		m_List.SetItemText(idx, 3, pRecord->Unit ? L"斤" : L"个");

		Text.Format(L"%.2llf", pRecord->Sell);
		m_List.SetItemText(idx, 4, Text);

		Text.Format(L"%.2llf", pRecord->Sellingprice);
		m_List.SetItemText(idx, 5, Text);

		TotalMoney += pRecord->Sellingprice;
	}
	dellist(pTempList);

	//设置当前日期.
	CString Date;
	Date.Format(L"日期: %s", m_Today.GetBuffer());
	GetDlgItem(IDC_TODAY)->SetWindowTextW(Date);
	//设置总利润
	CString Total;
	Total.Format(L"总利润: %.2llf", TotalMoney);
	GetDlgItem(IDC_TOTAL)->SetWindowTextW(Total);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
