// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_User(_T("admin"))
{
	m_pUserData = ReadUserData("user.dat");//��ȡ�û�����
}

CLoginDlg::~CLoginDlg()
{
	//��������.
	WriteUserData("user.dat", m_pUserData);
	//�ͷ���������.
	dellist(m_pUserData);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_User);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������
void CLoginDlg::OnBnClickedOk()
{
	UpdateData();
	if (m_User.GetLength() == 0 || m_Password.GetLength() == 0)
	{
		MessageBox(L"�˺Ż�����Ϊ��",L"tips",MB_OK|MB_ICONASTERISK);
		return;
	}

	UserData Target;
	strcpy(Target.szPassword, CW2A(m_Password));
	strcpy(Target.szUserName, CW2A(m_User));
	//��¼.
	if (!Login(m_pUserData, &Target))
	{
		MessageBox(L"�û������������!", L"tips", MB_OK | MB_ICONASTERISK);
		return;
	}
	CDialogEx::OnOK();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	HICON hIcon = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
