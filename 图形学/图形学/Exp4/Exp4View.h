
// Exp4View.h : CExp4View ��Ľӿ�
//

#pragma once


class CExp4View : public CView
{
protected: // �������л�����
	CExp4View();
	DECLARE_DYNCREATE(CExp4View)

// ����
public:
	CExp4Doc* GetDocument() const;

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
	virtual ~CExp4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	int m_state;
	CArray<CPoint> m_Shape;

	CPoint m_rect_p0;
	CPoint m_rect_p1;

	HPEN   m_Pen0;
	HPEN   m_Pen1;
	HPEN   m_Pen2;


	

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // Exp4View.cpp �еĵ��԰汾
inline CExp4Doc* CExp4View::GetDocument() const
   { return reinterpret_cast<CExp4Doc*>(m_pDocument); }
#endif

