
// Exp2View.h : CExp2View ��Ľӿ�
//

#pragma once


class CExp2View : public CView
{
protected: // �������л�����
	CExp2View();
	DECLARE_DYNCREATE(CExp2View)

// ����
public:
	CExp2Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CExp2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HBRUSH m_Brush;
	BOOL   m_finish;
	CArray<CPoint> m_Points;


	void EdgeMarkFill(HDC hDC,COLORREF color);

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exp2View.cpp �еĵ��԰汾
inline CExp2Doc* CExp2View::GetDocument() const
   { return reinterpret_cast<CExp2Doc*>(m_pDocument); }
#endif

