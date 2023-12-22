
// Exp6View.h : CExp6View ��Ľӿ�
//

#pragma once


class CExp6View : public CView
{
protected: // �������л�����
	CExp6View();
	DECLARE_DYNCREATE(CExp6View)

// ����
public:
	CExp6Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CExp6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	HDC hMemDC;


	int dx;
	int dy;

	int m_ok;
	int m_Start;
	CArray<CPoint> m_Points;

public:

	void CExp6View::bez_to_points(HDC hDC, const CArray<CPoint>& Points);
	void CExp6View::decas(HDC hDC, float t, const CArray<CPoint>& Points);

	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // Exp6View.cpp �еĵ��԰汾
inline CExp6Doc* CExp6View::GetDocument() const
   { return reinterpret_cast<CExp6Doc*>(m_pDocument); }
#endif

