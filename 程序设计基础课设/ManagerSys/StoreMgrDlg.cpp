// StoreMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "StoreMgrDlg.h"
#include "afxdialogex.h"
#include "SortDlg.h"
#include "MainFrame.h"
#include "AddGoodsDlg.h"
#include "ChangeGoodsDlg.h"

#include "PurcsDlg.h"
#include "SellDlg.h"
// CStoreMgrDlg �Ի���

IMPLEMENT_DYNAMIC(CStoreMgrDlg, CDialogEx)

CStoreMgrDlg::CStoreMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStoreMgrDlg::IDD, pParent)
	, m_Filter(_T(""))
{
	//��ȡ�����Ϣ.
	m_pStockList = ReadStockData("stock.dat");
}

CStoreMgrDlg::~CStoreMgrDlg()
{
	WriteStockData("stock.dat", m_pStockList);
	dellist(m_pStockList);
}

void CStoreMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_COMBO1, m_DropList);
	DDX_Text(pDX, IDC_EDIT1, m_Filter);
}


BEGIN_MESSAGE_MAP(CStoreMgrDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStoreMgrDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStoreMgrDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CStoreMgrDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CStoreMgrDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CStoreMgrDlg::OnNMRClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CStoreMgrDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStoreMgrDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CStoreMgrDlg::OnEnChangeEdit1)
	ON_COMMAND(ID_OPERATION_32776, &CStoreMgrDlg::OnOperation32776)
	ON_COMMAND(ID_OPERATION_32777, &CStoreMgrDlg::OnOperation32777)
	ON_BN_CLICKED(IDC_BUTTON4, &CStoreMgrDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CStoreMgrDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CStoreMgrDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CStoreMgrDlg ��Ϣ�������


void CStoreMgrDlg::OnBnClickedOk()
{
}


void CStoreMgrDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CStoreMgrDlg::OnCbnSelchangeCombo1()
{
	UpdateStockListView();
}


BOOL CStoreMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ѡ��,������,һ��ѡ������.
	ModifyStyle(0, WS_CHILD);

	m_List.SetExtendedStyle((~LVS_EX_CHECKBOXES)&(m_List.GetExStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES));
	
	m_List.InsertColumn(0, L"���", LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, L"����", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, L"Ʒ��", LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, L"��λ", LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, L"����", LVCFMT_LEFT, 100);
	m_List.InsertColumn(5, L"�ۼ�", LVCFMT_LEFT, 100);
	m_List.InsertColumn(6, L"�����", LVCFMT_LEFT, 100);
	m_List.InsertColumn(7, L"������", LVCFMT_LEFT, 100);

	//����ѡ�
	m_DropList.InsertString(0, L"���");
	m_DropList.InsertString(1, L"����");
	m_DropList.InsertString(2, L"Ʒ��");
	m_DropList.InsertString(3, L"����");
	m_DropList.InsertString(4, L"�ۼ�");
	//
	m_DropList.SetCurSel(0);
	//��ʾ��Ʒ��Ϣ

	UpdateStockListView();
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//����
void CStoreMgrDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CSortDlg dlg(0);
	if (IDOK == dlg.DoModal())
	{
		unsigned int key = dlg.m_SortType >> 16;
		unsigned int ascending = dlg.m_SortType & 0xffff;
		SortStock(m_pStockList, key, ascending);
		UpdateStockListView();
	}
}


void CStoreMgrDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CMenu menu;
	POINT pt;
	GetCursorPos(&pt);
	menu.LoadMenuW(IDR_MENU1);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
		pt.x, pt.y,this);
}

//���Ӽ�¼.
void CStoreMgrDlg::OnBnClickedButton1()
{
	Goods goods = { 0 };
	goods.Stock = 0;
	goods.Sell = 0;
	CAddGoodsDlg dlg(goods);
	if (IDOK == dlg.DoModal())
	{
		if (!AddStockRecord(m_pStockList,&goods))
		{
			MessageBox(L"��Ʒ��ų�ͻ", L"Error", MB_OK | MB_ICONASTERISK);
			return;
		}
		//д���ļ�
		WriteStockData("stock.dat", m_pStockList);
		//��ӵ��б�ؼ���.
		InsertGoods(goods);
	}
}


bool CStoreMgrDlg::Filter(Goods&goods)
{
	//������.
	CString Text;
	if (m_Filter.GetLength() == 0)
		return false;

	unsigned int ID;
	switch (m_DropList.GetCurSel())
	{
	case 0:		//���
		ID = atoi(CW2A(m_Filter));
		return goods.nID != ID;
	case 1:													//����
		return 0 == strstr(goods.szName, CW2A(m_Filter));
	case 2:													//Ʒ��
		return 0 == strstr(goods.szType, CW2A(m_Filter));
	case 3:
		Text.Format(L"%.2lf", goods.Purchaseprice);
		return 0 == wcsstr(Text, m_Filter);
	case 4:
		Text.Format(L"%.2lf", goods.Sellingprice);
		return 0 == wcsstr(Text, m_Filter);

	default:
		return false;
	}
}

void CStoreMgrDlg::UpdateStockListView()
{
	UpdateData();
	m_List.DeleteAllItems();
	m_List.SetRedraw(0);
	for (Node*pIt = m_pStockList->Head.next; pIt != &m_pStockList->Head; pIt = pIt->next)
	{
		//���뵽ListCtrl����
		Goods* pGoods = (Goods*)pIt;
		if (!Filter(*pGoods))
			InsertGoods(*pGoods);
	}
	m_List.SetRedraw(1);
}

void CStoreMgrDlg::InsertGoods(Goods&goods)
{
	CString  Text;
	Text.Format(L"%d", goods.nID);
	m_List.InsertItem(0, Text);
	//����
	m_List.SetItemText(0, 1, CA2W(goods.szName));
	//Ʒ��
	m_List.SetItemText(0, 2, CA2W(goods.szType));
	//��λ
	m_List.SetItemText(0, 3, goods.nUnit == 0 ? L"��" : L"��");
	//����
	Text.Format(L"%.2lf Ԫ", goods.Purchaseprice);
	m_List.SetItemText(0, 4, Text);
	//�ۼ�
	Text.Format(L"%.2lf Ԫ", goods.Sellingprice);
	m_List.SetItemText(0, 5, Text);
	//���
	Text.Format(L"%.2lf", goods.Stock);
	m_List.SetItemText(0, 6, Text);
	//����
	Text.Format(L"%.2lf", goods.Sell);
	m_List.SetItemText(0, 7, Text);
}

void CStoreMgrDlg::OnBnClickedButton2()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL || IDYES != MessageBox(L"ȷ��Ҫɾ��ѡ�м�¼��?(ɾ���󲻿ɻָ�)", L"Warning", MB_YESNO | MB_ICONWARNING))
	{
		return;
	}
	while (pos)
	{
		//�����б�ؼ��е�ѡ����
		int idx = m_List.GetNextSelectedItem(pos);
		CString ID = m_List.GetItemText(idx, 0);
		//ɾ�������еļ�¼.
		DeleteStockRecord(m_pStockList, atoi(CW2A(ID)));
	}
	//д���ļ�
	WriteStockData("stock.dat", m_pStockList);
	UpdateStockListView();
}


void CStoreMgrDlg::OnEnChangeEdit1()
{
	UpdateStockListView();
}

//�۳�
void CStoreMgrDlg::OnOperation32776()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_List.GetNextSelectedItem(pos);
		int ID = atoi(CW2A(m_List.GetItemText(idx, 0)));

		Goods Target;
		Target.nID = ID;
		Node*p = search(m_pStockList, m_pStockList->Head.next, CompareById, (Node*)&Target);

		if (p)
		{
			Goods*pGoods = (Goods*)p;
			CSellDlg dlg(*pGoods);
			if (dlg.DoModal() == IDOK)
			{
				//д���ļ�
				WriteStockData("stock.dat", m_pStockList);
				//���ۼ�¼��Ϣ.
				Record*pRecord = (Record*)malloc(sizeof(Record));
				pRecord->ID = pGoods->nID;
				strcpy(pRecord->szName, pGoods->szName);
				strcpy(pRecord->szType, pGoods->szType);
				pRecord->Sell = atof(CW2A(dlg.m_SellCount));
				pRecord->Unit = pGoods->nUnit;
				pRecord->Purchaseingprice = pGoods->Purchaseprice;
				pRecord->Sellingprice = pGoods->Sellingprice;
				strcpy(pRecord->szTime, CW2A(CTime::GetTickCount().Format(L"%H:%M:%S")));
				strcpy(pRecord->szComment, CW2A(dlg.m_Comment));
				pRecord->m_Rate = atof(CW2A(dlg.m_Rate));

				//������ۼ�¼.
				char szDate[256];
				strcpy(szDate, CW2A(CTime::GetTickCount().Format(L"%Y-%m-%d")));
				ListContext*pSaleRecords = ((CMainFrame*)GetParent())->m_SaleDlg.m_pSaleRecords;
				//��ȡ����ļ�¼����
				SaleRecords*pRecordList = GetRecord(szDate, pSaleRecords, "SaleRecords");
				//���뵽����.
				insertback(pRecordList->m_pRecordList, (Node*)pRecord);
				//ˢ�½���
				((CMainFrame*)GetParent())->m_SaleDlg.UpdateSaleRecordListView();
				
				//д���ۼ�¼���ļ�
				char szFileName[256];
				sprintf(szFileName, "SaleRecords\\%s", szDate);

				WriteRecord(szFileName, pRecordList->m_pRecordList);
				UpdateStockListView();
			}
		}
	}
}

//����
void CStoreMgrDlg::OnOperation32777()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_List.GetNextSelectedItem(pos);
		int ID = atoi(CW2A(m_List.GetItemText(idx, 0)));

		Goods Target;
		Target.nID = ID;
		Node*p = search(m_pStockList, m_pStockList->Head.next, CompareById, (Node*)&Target);

		if (p)
		{
			Goods*pGoods = (Goods*)p;
			//����.
			CPurcsDlg dlg(*pGoods);
			if (IDOK == dlg.DoModal())
			{
				//д���ļ�
				WriteStockData("stock.dat", m_pStockList);
				////������¼��Ϣ.
				Record*pRecord = (Record*)malloc(sizeof(Record));

				pRecord->ID = pGoods->nID;
				strcpy(pRecord->szName, pGoods->szName);
				strcpy(pRecord->szType, pGoods->szType);
				pRecord->Sell = atof(CW2A(dlg.m_SellCount));		//����ʱ����ǽ�����
				pRecord->Unit = pGoods->nUnit;
				pRecord->Purchaseingprice = pGoods->Purchaseprice;
				pRecord->Sellingprice = pGoods->Sellingprice;
				strcpy(pRecord->szTime, CW2A(CTime::GetTickCount().Format(L"%H:%M:%S")));
				strcpy(pRecord->szComment, CW2A(dlg.m_Comment));

				////��ӽ�����¼.
				char szDate[256];
				strcpy(szDate, CW2A(CTime::GetTickCount().Format(L"%Y-%m-%d")));
				//��ȡ�����¼����
				ListContext*pPurchaseRecord = ((CMainFrame*)GetParent())->m_PurchaseDlg.m_pPurchaseRecords;
				SaleRecords* pRecordList =  GetRecord(szDate, pPurchaseRecord, "PurchaseRecords");
				//
				insertback(pRecordList->m_pRecordList, (Node*)pRecord);
				//ˢ�½���
				((CMainFrame*)GetParent())->m_PurchaseDlg.UpdatePurchaseRecordListView();
				//д���ۼ�¼���ļ�
				char szFileName[256];
				sprintf(szFileName, "PurchaseRecords\\%s", szDate);
				WriteRecord(szFileName, pRecordList->m_pRecordList);
				UpdateStockListView();
			}
		}
	}
	
}

//�޸ļ�¼.
void CStoreMgrDlg::OnBnClickedButton5()
{
	//
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (!pos)
		return;
	//
	int idx = m_List.GetNextSelectedItem(pos);
	Goods goods = { 0 };
	//��ȡ�ؼ��ϵ�����
	goods.nID = atoll(CW2A(m_List.GetItemText(idx, 0)));		//ID
	strcpy(goods.szName, CW2A(m_List.GetItemText(idx, 1)));		//Name
	strcpy(goods.szType, CW2A(m_List.GetItemText(idx, 2)));		//type
	goods.nUnit = m_List.GetItemText(idx, 3) == L"��" ? 0 : 1;	//unit
	goods.Purchaseprice = atof(CW2A(m_List.GetItemText(idx, 4)));//����
	goods.Sellingprice = atof(CW2A(m_List.GetItemText(idx, 5)));

	CChangeGoodsDlg dlg(goods);
	if (IDOK == dlg.DoModal())
	{
		if (!ModifyStockInfo(m_pStockList, goods.nID, &goods))
		{
			MessageBox(L"�޸�ʧ��", L"tips", MB_OK);
			return;
		}
		//д���ļ�
		WriteStockData("stock.dat", m_pStockList);
		//�޸Ŀؼ��ϵ���ʾ
		CString  Text;
		m_List.SetItemText(idx, 1, CA2W(goods.szName));
		//Ʒ��
		m_List.SetItemText(idx, 2, CA2W(goods.szType));
		//��λ
		m_List.SetItemText(idx, 3, goods.nUnit == 0 ? L"��" : L"��");
		//����
		Text.Format(L"%.2lf Ԫ", goods.Purchaseprice);
		m_List.SetItemText(idx, 4, Text);
		//�ۼ�
		Text.Format(L"%.2lf Ԫ", goods.Sellingprice);
		m_List.SetItemText(idx, 5, Text);
		//���
		Text.Format(L"%.2lf", goods.Stock);
		m_List.SetItemText(idx, 6, Text);
		//����
		Text.Format(L"%.2lf", goods.Sell);
		m_List.SetItemText(idx, 7, Text);
		//
		MessageBox(L"�޸ĳɹ�", L"tips", MB_OK);	
	}
}

//���ļ�����
void CStoreMgrDlg::OnBnClickedButton4()
{
	CFileDialog FileDlg(TRUE, L"*.txt", L"", NULL, L"�ı��ĵ�(*.txt)|*.txt", this);

	if (IDOK == FileDlg.DoModal())
	{
		int nTotal = 0, nSuccess = 0;
		CString FileName = FileDlg.GetPathName();
		ImportFromFile(m_pStockList, CW2A(FileName), &nTotal, &nSuccess);
		//
		CString Text;
		Text.Format(L"��ȡ���\r\n���ҵ�:%d ����¼\r\n��ӳɹ�:%d ����¼\r\n", nTotal, nSuccess);
		MessageBox(Text);
		UpdateStockListView();
	}

}
//�������.
void CStoreMgrDlg::OnBnClickedButton6()
{
	CFileDialog FileDlg(FALSE, L"*.txt", L"", NULL, L"�ı��ĵ�(*.txt)|*.txt", this);

	if (IDOK == FileDlg.DoModal())
	{
		if (ExportStockReport(m_pStockList, CW2A(FileDlg.GetPathName()).m_psz))
		{
			MessageBox(L"����ɹ�");
		}
		else
			MessageBox(L"����ʧ��");
	}
}
