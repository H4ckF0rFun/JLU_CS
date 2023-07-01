// ParchaseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "PurchaseDlg.h"
#include "afxdialogex.h"
#include "SortDlg.h"

// CParchaseDlg �Ի���

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
		//����ÿһ��ļ�¼
		PurchaseRecords*pPurchaseRecord = (PurchaseRecords*)it;
		char szFileName[256];
		sprintf(szFileName, "PurchaseRecords\\%s", pPurchaseRecord->szDate);
		WriteRecord(szFileName, pPurchaseRecord->m_pRecordList);
		//ɾ��ÿһ��ļ�¼
		dellist(pPurchaseRecord->m_pRecordList);
	}
	//ɾ������
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


// CParchaseDlg ��Ϣ�������


BOOL CPurchaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyle(0, WS_CHILD);

	CreateDirectory(L"PurchaseRecords", NULL);
	//


	//
	m_FilterList.AddString(L"���");
	m_FilterList.AddString(L"����");
	m_FilterList.AddString(L"Ʒ��");
	m_FilterList.AddString(L"ʱ��");
	m_FilterList.SetCurSel(0);


	//
	m_PurchaseList.InsertColumn(0, L"���", LVCFMT_LEFT, 120);
	m_PurchaseList.InsertColumn(1, L"����", LVCFMT_LEFT, 120);
	m_PurchaseList.InsertColumn(2, L"Ʒ��", LVCFMT_LEFT, 120);
	m_PurchaseList.InsertColumn(3, L"��λ", LVCFMT_LEFT, 75);
	m_PurchaseList.InsertColumn(4, L"����", LVCFMT_LEFT, 75);
	m_PurchaseList.InsertColumn(5, L"����", LVCFMT_LEFT, 80);
	m_PurchaseList.InsertColumn(6, L"�ۼ�", LVCFMT_LEFT, 80);
	m_PurchaseList.InsertColumn(7, L"���", LVCFMT_LEFT, 100);
	m_PurchaseList.InsertColumn(8, L"ʱ��", LVCFMT_LEFT, 100);

	m_PurchaseList.InsertColumn(9, L"��ע", LVCFMT_LEFT, 100);

	m_PurchaseList.SetExtendedStyle((~LVS_EX_CHECKBOXES)&(m_PurchaseList.GetExStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT));

	//�����б�.
	CTime time;
	m_DateCtrl.GetTime(time);
	//���Ѿ����ص������в��ҵ���ļ�¼
	//���տ����Ի����ʱ��,�Ͱѵ���ļ�¼��ȡ����.
	m_pCurRecord = GetRecord(CW2A(time.Format(L"%Y-%m-%d")), m_pPurchaseRecords,"PurchaseRecords");
	
	UpdatePurchaseRecordListView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CPurchaseDlg::OnBnClickedButton1()
{
	//ɾ����¼
	POSITION pos = m_PurchaseList.GetFirstSelectedItemPosition();
	if (pos == NULL || IDYES != MessageBox(L"ȷ��Ҫɾ��ѡ�м�¼��?(ɾ���󲻿ɻָ�)", L"Warning", MB_YESNO | MB_ICONWARNING))
		return;

	while (pos)
	{
		int idx = m_PurchaseList.GetNextSelectedItem(pos);
		//ɾ��ָ����¼
		ListContext*pList = m_pCurRecord->m_pRecordList;
		DeleteCurDateRecord(pList, CW2A(m_PurchaseList.GetItemText(idx, 8)));
	}

	//д���ļ�.
	char szFileName[256];
	sprintf(szFileName, "PurchaseRecords\\%s", m_pCurRecord->szDate);
	WriteRecord(szFileName, m_pCurRecord->m_pRecordList);
	//ˢ����ʾ.
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnBnClickedButton2()
{
	//��ռ�¼
	if (IDYES != MessageBox(L"ȷ��ɾ�������¼��?(ɾ���󲻿ɻָ�)", L"Warning", MB_YESNO | MB_ICONWARNING))
		return;
	ListContext*pList = m_pCurRecord->m_pRecordList;
	//ɾ������ļ�¼
	DeleteCurDateAllRecord(pList);
	//
	//д���ļ�.
	char szFileName[256];
	sprintf(szFileName, "PurchaseRecords\\%s", m_pCurRecord->szDate);
	WriteRecord(szFileName, m_pCurRecord->m_pRecordList);
	//
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnBnClickedButton3()
{
	//����
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
		//���뵽ListCtrl����
		Record*pRecord = (Record*)pIt;

		if (!Filter(*pRecord))
			InsertRecord(*pRecord);
	}
	m_PurchaseList.SetRedraw(1);
}


void CPurchaseDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//
	CTime time;
	m_DateCtrl.GetTime(time);
	//���ڸı�ʱˢ������.
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
	m_PurchaseList.SetItemText(0, 3, record.Unit ? L"��" : L"��");

	Text.Format(L"%.2lf", record.Sell);
	m_PurchaseList.SetItemText(0, 4, Text);
	//����
	Text.Format(L"%.2lf Ԫ", record.Purchaseingprice);
	m_PurchaseList.SetItemText(0, 5, Text);
	//�ۼ�
	Text.Format(L"%.2lf Ԫ", record.Sellingprice);
	m_PurchaseList.SetItemText(0, 6, Text);
	//�������
	double m = record.Sell * record.Purchaseingprice;
	Text.Format(L"%.2lf Ԫ", m);
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnEnChangeEdit1()
{
	UpdatePurchaseRecordListView();
}


void CPurchaseDlg::OnBnClickedButton6()
{
	CFileDialog FileDlg(FALSE, L"*.txt", L"", NULL, L"�ı��ĵ�(*.txt)|*.txt", this);

	if (IDOK == FileDlg.DoModal())
	{
		if (ExportCurDatePurchaseReport(m_pCurRecord->m_pRecordList, m_pCurRecord->szDate, CW2A(FileDlg.GetPathName()).m_psz))
		{
			MessageBox(L"����ɹ�");
		}
		else
		{
			MessageBox(L"����ʧ��");
		}
	}
}


void CPurchaseDlg::OnOK()
{
}
