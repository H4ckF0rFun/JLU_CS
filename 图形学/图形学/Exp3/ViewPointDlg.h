#pragma once


// CViewPointDlg �Ի���

class CViewPointDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewPointDlg)

public:
	CViewPointDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewPointDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString m_X;
	CString m_Y;
	CString m_Z;
	afx_msg void OnBnClickedOk();
};
