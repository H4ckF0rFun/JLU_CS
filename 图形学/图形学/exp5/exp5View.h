
// exp5View.h : Cexp5View ��Ľӿ�
//

#pragma once


class Cexp5View : public CView
{
protected: // �������л�����
	Cexp5View();
	DECLARE_DYNCREATE(Cexp5View)

// ����
public:
	Cexp5Doc* GetDocument() const;

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
	virtual ~Cexp5View();

	void DrawHermite(CDC* pDC);

	void bez_to_points(CDC * pDC);
	
	void decas(CDC * pDC, float t);


	//
	void bspline_to_points(CDC * pDC, int k, float knot[]);
	void deboor(CDC * pDC, int i, int k, float knot[], float u);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int			   m_state;
	int			   m_type;

	CArray<CPoint> m_Points;


// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDraw();
	afx_msg void OnB();
	afx_msg void OnBezier();
	afx_msg void OnHermite();
	afx_msg void OnClear();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // exp5View.cpp �еĵ��԰汾
inline Cexp5Doc* Cexp5View::GetDocument() const
   { return reinterpret_cast<Cexp5Doc*>(m_pDocument); }
#endif

