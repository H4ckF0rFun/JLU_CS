// AboutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "AboutDlg.h"
#include "afxdialogex.h"


// CAboutDlg �Ի���

IMPLEMENT_DYNAMIC(CAboutDlg, CDialogEx)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAboutDlg::IDD, pParent)
{

}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAboutDlg ��Ϣ�������


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	WCHAR szBuffer[0x1000];
	LoadString(GetModuleHandle(NULL), IDS_ABOUT, szBuffer, 0x1000);
	GetDlgItem(IDC_STATIC)->SetWindowTextW(szBuffer);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
