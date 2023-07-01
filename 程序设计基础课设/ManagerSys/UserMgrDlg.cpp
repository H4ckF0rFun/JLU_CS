// UserMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "UserMgrDlg.h"
#include "afxdialogex.h"


// CUserMgrDlg �Ի���

IMPLEMENT_DYNAMIC(CUserMgrDlg, CDialogEx)

CUserMgrDlg::CUserMgrDlg(ListContext*pUserData,CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserMgrDlg::IDD, pParent)
	, m_UserName(_T(""))
{
	m_pUserData = pUserData;
}

CUserMgrDlg::~CUserMgrDlg()
{
}

void CUserMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK3, m_ChangePass);
	DDX_Control(pDX, IDOK2, m_DelUser);
	DDX_Control(pDX, IDOK4, m_AddUsers);
	DDX_Control(pDX, IDC_LIST2, m_UserList);
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
	DDX_Text(pDX, IDC_EDIT3, m_Password2);
}


BEGIN_MESSAGE_MAP(CUserMgrDlg, CDialogEx)
	ON_BN_CLICKED(IDOK4, &CUserMgrDlg::OnBnClickedOk4)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CUserMgrDlg::OnNMClickList2)
	ON_BN_CLICKED(IDOK3, &CUserMgrDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK2, &CUserMgrDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CUserMgrDlg ��Ϣ�������


BOOL CUserMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_hIconPass = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
	m_hIconAdd = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ADD));
	m_hIconDel = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DELETE));

	m_ChangePass.SetIcon(m_hIconPass);
	m_AddUsers.SetIcon(m_hIconAdd);
	m_DelUser.SetIcon(m_hIconDel);
	
	//
	m_UserList.SetExtendedStyle((m_UserList.GetExStyle() | LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES)&(~LVS_EX_CHECKBOXES));
	m_UserList.InsertColumn(0, L"�û���",LVCFMT_LEFT,120);
	m_UserList.InsertColumn(1, L"����", LVCFMT_LEFT, 120);
	//
	m_UserList.DeleteAllItems();
	m_UserList.SetRedraw(0);
	int idx = 0;
	for (Node*pIt = m_pUserData->Head.next; pIt != &m_pUserData->Head; pIt = pIt->next)
	{
		UserData*pUser = (UserData*)pIt;
		m_UserList.InsertItem(idx, CA2W(pUser->szUserName));
		m_UserList.SetItemText(idx, 1, CA2W(pUser->szPassword));
	}
	m_UserList.SetRedraw(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//������û�
void CUserMgrDlg::OnBnClickedOk4()
{
	//����Ƿ����и��û�
	UpdateData();
	//
	if (m_UserName.GetLength() == 0)
		return;

	Node*pIt = NULL;
	//
	UserData NewUser;
	strcpy(NewUser.szUserName, CW2A(m_UserName));
	//
	UserData*pUser = (UserData*)search(m_pUserData, m_pUserData->Head.next, Compare, (UserData*)&NewUser);
	if (pUser)
	{
		MessageBox(L"���û��Ѵ���", L"Error", MB_OK | MB_ICONASTERISK);
		return;
	}
	//
	if (m_Password != m_Password2)
	{
		MessageBox(L"�������벻��ͬ", L"Error", MB_OK | MB_ICONASTERISK);
		return;
	}
	//���뵽������.
	UserData*pNewUser = (UserData*)malloc(sizeof(UserData));
	strcpy(pNewUser->szUserName, CW2A(m_UserName));
	strcpy(pNewUser->szPassword, CW2A(m_Password));
	insertback(m_pUserData, (Node*)pNewUser);
	//
	WriteUserData("user.dat", m_pUserData);
	//
	int idx = m_UserList.GetItemCount();
	m_UserList.InsertItem(idx, m_UserName);
	m_UserList.SetItemText(idx, 1, m_Password);
}


void CUserMgrDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	if (m_UserList.GetItemCount() == 0)
		return;
	//
	POSITION pos = m_UserList.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_UserList.GetNextSelectedItem(pos);

		m_UserName = m_UserList.GetItemText(idx, 0);
		m_Password = m_UserList.GetItemText(idx, 1);
		m_Password2 = m_UserList.GetItemText(idx, 1);
		UpdateData(FALSE);
	}
}

//�޸�����
void CUserMgrDlg::OnBnClickedOk3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//����Ƿ����и��û�
	UpdateData();
	//
	if (m_UserName.GetLength() == 0)
		return;
	//�����û�.
	UserData Target;
	strcpy(Target.szUserName, CW2A(m_UserName));

	UserData*pUser = (UserData*)search(m_pUserData, m_pUserData->Head.next, Compare, (Node*)&Target);
	//
	if (pUser)
	{
		if (m_Password != m_Password2)
		{
			MessageBox(L"�������벻��ͬ", L"Error", MB_OK | MB_ICONASTERISK);
			return;
		}
		//�޸������ڵĶ���
		strcpy(pUser->szPassword, CW2A(m_Password));

		//�޸��б���ʾ������.
		POSITION pos = m_UserList.GetFirstSelectedItemPosition();
		while (pos)
		{
			int idx = m_UserList.GetNextSelectedItem(pos);
			if (m_UserList.GetItemText(idx, 0) == m_UserName)
			{
				m_UserList.SetItemText(idx, 1, m_Password);
				break;
			}
		}
		//
		WriteUserData("user.dat", m_pUserData);
		return;
	}
}

//ɾ���û�
void CUserMgrDlg::OnBnClickedOk2()
{
	POSITION pos = m_UserList.GetFirstSelectedItemPosition();
	if (!pos)
		return;
	int idx = m_UserList.GetNextSelectedItem(pos);
	//ɾ���б�����.
	m_UserList.DeleteItem(idx);

	//ɾ����������.
	UserData Target;
	strcpy(Target.szUserName, CW2A(m_UserName));
	//
	UserData*pUser = (UserData*)search(m_pUserData, m_pUserData->Head.next, Compare, (Node*)&Target);
	if (pUser)
	{
		delnode(m_pUserData, (Node*)pUser);
		//
		WriteUserData("user.dat", m_pUserData);
	}
}
