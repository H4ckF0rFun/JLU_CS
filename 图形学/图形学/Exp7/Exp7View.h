
// Exp7View.h : CExp7View ��Ľӿ�
//

#pragma once

struct Point
{
	double x;
	double y;
	double z;
};

class CExp7View : public CView
{
protected: // �������л�����
	CExp7View();
	DECLARE_DYNCREATE(CExp7View)

// ����
public:
	CExp7Doc* GetDocument() const;

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
	virtual ~CExp7View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	int m_state;
	CArray<CPoint> m_Points;
	CArray<CPoint> m_TmpPoints;

	COLORREF m_colors[3];
	COLORREF m_CurrentColor;

// ���ɵ���Ϣӳ�亯��
protected:
	void CExp7View::deboor(CDC * pDC, int i, int k, float knot[], float u);
	void CExp7View::bspline_to_points(CDC * pDC, int k, float knot[]);

	void CExp7View::deboor3(CDC * pDC, int i, int k, float knot[], float u);
	void CExp7View::bspline_to_points3(CDC * pDC, int k, float knot[]);

	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void On43b();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDuichen();
	afx_msg void On3d();
	afx_msg void OnClear();
};

#ifndef _DEBUG  // Exp7View.cpp �еĵ��԰汾
inline CExp7Doc* CExp7View::GetDocument() const
   { return reinterpret_cast<CExp7Doc*>(m_pDocument); }
#endif

